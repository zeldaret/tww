#!/usr/bin/env python3

# Compares used inlines for a TU in the decomp compared to the official debug maps.
# Checks for missing inline usages, fake inline usages, and inlines being the wrong size.
# NOTE: You must mark the TU as "Matching" in configure.py, even if it doesn't match! Otherwise this script won't work properly.

from pathlib import Path
import re
import subprocess
import argparse
from collections import defaultdict

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
  object_name = object_name.split(".", 1)[0]
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

class Symbol:
  def __init__(self, name: str, size: int, sym_type: str | None = None, linkage: str | None = None):
    self.name = name
    self.size = size
    self.sym_type = sym_type
    self.linkage = linkage

def get_main_symbols(framework_map_contents: str, valid_obj_names = None):
  symbols = {}
  matches = re.findall(r"^  [0-9a-f]{8} ([0-9a-f]{6}) (?:[0-9a-f]{8})(?: +\d+)? (.+?)(?: \(entry of [^)]+\))? \t(?:\S+\.a )?([^\s\.]+)\.\S+ ?$", framework_map_contents, re.IGNORECASE | re.MULTILINE)
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
    
    symbols[name] = Symbol(name, size)
  if len(symbols) == 0:
    raise Exception("Failed to find object matching the given name")
  return symbols

def get_rel_symbols(rel_map_data: str):
  rel_map_lines = rel_map_data.splitlines()
  
  line = rel_map_lines.pop(0)
  assert line == "Link map of _prolog"
  symbol_name_to_type_linkage_obj = {}
  while True:
    line = rel_map_lines.pop(0)
    if line == "":
      # End of link map
      break
    if line.startswith(">>> SYMBOL NOT FOUND: "):
      continue
    linker_symbol_match = re.search(r"^  +(\d+)\] (\S+) found as linker generated symbol$", line)
    if linker_symbol_match:
      continue
    normal_symbol_match = re.search(r"^  +(\d+)\] (\S+) \((section|func|object|notype),(global|local|weak)\) found in (\S+) $", line)
    assert normal_symbol_match is not None, f"Unknown line: {repr(line)}"
    link_map_depth = int(normal_symbol_match.group(1))
    symbol_name = normal_symbol_match.group(2)
    symbol_type = normal_symbol_match.group(3)
    linkage = normal_symbol_match.group(4)
    object_name = normal_symbol_match.group(5)
    assert symbol_name not in symbol_name_to_type_linkage_obj
    symbol_name_to_type_linkage_obj[symbol_name] = (symbol_type, linkage, object_name)
  
  # found_memory_map = False
  # next_section_index = 0
  # section_name_to_section_index = {}
  # for line in rel_map_lines:
  #   if line.strip() == "Memory map:":
  #     found_memory_map = True
  #   if found_memory_map:
  #     section_match = re.search(r"^ +\.(text|ctors|dtors|rodata|data|bss)  [0-9a-f]{8} ([0-9a-f]{8}) [0-9a-f]{8}$", line)
  #     if section_match:
  #       section_name = section_match.group(1)
  #       section_size = int(section_match.group(2), 16)
  #       if section_size > 0:
  #         section_name_to_section_index[section_name] = next_section_index
  #         next_section_index += 1
  # if not found_memory_map:
  #   raise Exception("Failed to find memory map")
  
  symbols = {}
  # current_section_name = None
  localstatic_counters = defaultdict(int)
  for line in rel_map_lines:
    # section_header_match = re.search(r"^\.(text|ctors|dtors|rodata|data|bss) section layout$", line)
    # if section_header_match:
    #   current_section_name = section_header_match.group(1)
    # if current_section_name != "text":
    #     continue
    symbol_entry_match = re.search(r"^  ([0-9a-f]{8}|UNUSED  ) ([0-9a-f]{6}) ([0-9a-f]{8}|\.{8})(?: +\d+)? (.+?)(?: \(entry of [^)]+\))? \t?(\S+)", line, re.IGNORECASE)
    if symbol_entry_match:
      symbol_address = symbol_entry_match.group(1)
      symbol_size = symbol_entry_match.group(2)
      symbol_size = int(symbol_size, 16)
      symbol_offset = symbol_entry_match.group(3)
      if symbol_address == "UNUSED  ":
        assert symbol_offset == "........"
      if symbol_offset == "........":
        assert symbol_address == "UNUSED  "
        symbol_offset = None
      else:
        symbol_offset = int(symbol_offset, 16)
      symbol_name = symbol_entry_match.group(4)
      object_name = symbol_entry_match.group(5)
      
      if object_name in ["executor.o", "global_destructor_chain.o"]:
        continue
      if re.search(r"^@\d+$", symbol_name):
        continue
      if localstatic_match := re.search(r"^([^\s\$]+)\$\d+$", symbol_name):
        localstatic_name = localstatic_match.group(1)
        localstatic_counters[localstatic_name] += 1
        symbol_name = f"{localstatic_name}${localstatic_counters[localstatic_name]}"
      
      if symbol_name in symbol_name_to_type_linkage_obj:
        symbol_type, linkage, object_name = symbol_name_to_type_linkage_obj[symbol_name]
      else:
        symbol_type = linkage = object_name = None
      symbols[symbol_name] = Symbol(symbol_name, symbol_size, sym_type=symbol_type, linkage=linkage)
      #print("%08X  %s" % (symbol_offset, symbol_name))
  
  #print(rel_symbol_names)
  
  return symbols

def is_debug_only_symbol(symbol_name: str):
  if "__11JORMContextF" in symbol_name:
    return True
  return False

if is_rel:
  target_symbols = get_rel_symbols(target_map_path.read_text())
  base_symbols = get_rel_symbols(base_map_path.read_text())
else:
  obj_names = [object_name]
  target_symbols = get_main_symbols(target_map_path.read_text(), valid_obj_names=obj_names)
  base_symbols = get_main_symbols(base_map_path.read_text(), valid_obj_names=obj_names)

print(len(target_symbols), len(base_symbols))

symbol_size_diffs = []
total_missing = 0
total_fake = 0
total_right_size = 0
total_wrong_size = 0
total_wrong_linkage = 0

for symbol_name, target_symbol in target_symbols.items():
  if target_symbol.size == 0:
    continue
  if symbol_name not in base_symbols:
    base_size = 0
  else:
    base_size = base_symbols[symbol_name].size
  size_diff = abs(target_symbol.size - base_size)
  ratio = size_diff / target_symbol.size
  if size_diff != 0:
    total_wrong_size += 1
  symbol_size_diffs.append((symbol_name, target_symbol.size, base_size, ratio))

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
  elif ratio < 0.05 and size_diff <= 0x10:
    prefix = "CLOSE: "
  else:
    prefix = "WRONG: "
  print(prefix + symbol_name, "0x%X" % target_size, "0x%X" % base_size, ratio)
  
for symbol_name, base_symbol in base_symbols.items():
  if symbol_name in target_symbols:
    continue
  print("FAKE:", symbol_name)
  total_fake += 1

for symbol_name, target_size, base_size, ratio in symbol_size_diffs:
  prefix = ""
  if base_size == 0:
    if is_debug_only_symbol(symbol_name):
      continue
    prefix = "MISSING: "
    total_missing += 1
    print(prefix + symbol_name, "0x%X" % target_size)

for symbol_name, target_symbol in target_symbols.items():
  if target_symbol.size == 0:
    continue
  if symbol_name not in base_symbols:
    continue
  base_symbol = base_symbols[symbol_name]
  if target_symbol.linkage != base_symbol.linkage:
    total_wrong_linkage += 1
    print(f"LINKAGE: {symbol_name} (should be {target_symbol.linkage}, is {base_symbol.linkage})")

print("==================================================")
print(f"Total right size: {total_right_size}")
print(f"Total wrong size: {total_wrong_size}")
print(f"Total fake: {total_fake}")
print(f"Total missing: {total_missing}")
print(f"Total wrong linkage: {total_wrong_linkage}")
