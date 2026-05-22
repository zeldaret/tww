#!/usr/bin/env python3

# Compares used inlines for a TU in the decomp compared to the official debug maps.
# Checks for missing inline usages, fake inline usages, and inlines being the wrong size.
# NOTE: You must mark the TU as "Matching" in configure.py, even if it doesn't match! Otherwise this script won't work properly.

from pathlib import Path
import re
import subprocess
import argparse

arg_parse = argparse.ArgumentParser()
arg_parse.add_argument("object_name", help="Name of the object to compare, e.g. d_a_bridge for a REL, or main/d_a_npc_fa1 for a main.dol object")
args = arg_parse.parse_args()
object_name: str = args.object_name

debug_maps_root_path = Path("orig/D44J01/files/maps")
decomp_root_path = Path(".")

is_rel: bool
if object_name.startswith("main/"):
  is_rel = False
  object_name = object_name.split("/", 1)[1]
  target_map_path = debug_maps_root_path / "frameworkD.map"
  base_map_path = decomp_root_path / "build/D44J01/framework.elf.MAP"
else:
  is_rel = True
  target_map_path = debug_maps_root_path / f"{object_name}D.map"
  base_map_path = decomp_root_path / f"build/D44J01/{object_name}/{object_name}.plf.MAP"
assert "/" not in object_name and "." not in object_name

retcode = subprocess.call(["python", "configure.py", "--version", "D44J01", "--debug", "--map", "--non-matching"], cwd=decomp_root_path)
assert retcode == 0, "Failed to configure"
retcode = subprocess.call(["ninja", base_map_path.relative_to(decomp_root_path)], cwd=decomp_root_path)
assert retcode == 0, "Ninja build call failed"

def get_main_symbols(framework_map_contents: str, valid_obj_names = None):
  symbols = {}
  matches = re.findall(r"^  [0-9a-f]{8} ([0-9a-f]{6}) (?:[0-9a-f]{8})(?: +\d+)? (.+?)(?: \(entry of [^)]+\))? \t(\S+)", framework_map_contents, re.IGNORECASE | re.MULTILINE)
  for match in matches:
    size, name, obj_name = match
    size = int(size, 16)
    
    if name.startswith("@"):
      continue
    if name.startswith("."):
      continue
    if "$" in name:
      name = name[:name.index("$")+1]
    if valid_obj_names is not None and obj_name not in valid_obj_names:
      continue
    
    symbols[name] = size
  return symbols

def get_rel_symbols(rel_map_data: str):
  rel_map_lines = rel_map_data.splitlines()
  found_memory_map = False
  next_section_index = 0
  section_name_to_section_index = {}
  for line in rel_map_lines:
    if line.strip() == "Memory map:":
      found_memory_map = True
    if found_memory_map:
      section_match = re.search(r"^ +\.(text|ctors|dtors|rodata|data|bss)  [0-9a-f]{8} ([0-9a-f]{8}) [0-9a-f]{8}$", line)
      if section_match:
        section_name = section_match.group(1)
        section_size = int(section_match.group(2), 16)
        if section_size > 0:
          section_name_to_section_index[section_name] = next_section_index
          next_section_index += 1
  if not found_memory_map:
    raise Exception("Failed to find memory map")
  
  symbols = {}
  current_section_name = None
  for line in rel_map_lines:
    section_header_match = re.search(r"^\.(text|ctors|dtors|rodata|data|bss) section layout$", line)
    if section_header_match:
      current_section_name = section_header_match.group(1)
    if current_section_name != "text":
        continue
    symbol_entry_match = re.search(r"^  [0-9a-f]{8} ([0-9a-f]{6}) ([0-9a-f]{8})(?: +\d+)? (.+?)(?: \(entry of [^)]+\))? \t(\S+)", line, re.IGNORECASE)
    if symbol_entry_match:
      symbol_size = symbol_entry_match.group(1)
      symbol_size = int(symbol_size, 16)
      symbol_offset = symbol_entry_match.group(2)
      symbol_offset = int(symbol_offset, 16)
      symbol_name = symbol_entry_match.group(3)
      object_name = symbol_entry_match.group(4)
      if object_name in ["global_destructor_chain.o"]:
        continue
      symbols[symbol_name] = symbol_size
      #print("%08X  %s" % (symbol_offset, symbol_name))
  
  #print(rel_symbol_names)
  
  return symbols

if is_rel:
  target_symbols = get_rel_symbols(target_map_path.read_text())
  base_symbols = get_rel_symbols(base_map_path.read_text())
else:
  obj_names = [f"{object_name}.o"]
  target_symbols = get_main_symbols(target_map_path.read_text(), valid_obj_names=obj_names)
  base_symbols = get_main_symbols(base_map_path.read_text(), valid_obj_names=obj_names)

print(len(target_symbols), len(base_symbols))

symbol_size_diffs = []
total_missing = 0
total_fake = 0
total_right_size = 0
total_wrong_size = 0
for symbol_name, target_size in target_symbols.items():
    if target_size == 0:
      continue
    if symbol_name not in base_symbols:
      base_size = 0
    else:
      base_size = base_symbols[symbol_name]
    size_diff = abs(target_size - base_size)
    ratio = size_diff / target_size
    if size_diff != 0:
      total_wrong_size += 1
    symbol_size_diffs.append((symbol_name, target_size, base_size, ratio))

symbol_size_diffs.sort(key=lambda x: x[-1])

for symbol_name, target_size, base_size, ratio in symbol_size_diffs:
  prefix = ""
  size_diff = abs(target_size - base_size)
  if base_size == 0:
    # Print missing inlines last so they're obvious
    continue
  elif size_diff == 0:
    prefix = "GOOD: "
    total_right_size += 1
  elif ratio < 0.03:
    prefix = "CLOSE: "
  else:
    prefix = "WRONG: "
  print(prefix + symbol_name, "0x%X" % target_size, "0x%X" % base_size, ratio)
  
for symbol_name, base_size in base_symbols.items():
  if symbol_name in target_symbols:
    continue
  print("FAKE:", symbol_name)
  total_fake += 1

for symbol_name, target_size, base_size, ratio in symbol_size_diffs:
  prefix = ""
  if base_size == 0:
    prefix = "MISSING: "
    total_missing += 1
    print(prefix + symbol_name, "0x%X" % target_size)

print("==================================================")
print(f"Total right size: {total_right_size}")
print(f"Total wrong size: {total_wrong_size}")
print(f"Total fake: {total_fake}")
print(f"Total missing: {total_missing}")
