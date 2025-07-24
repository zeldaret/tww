#!/usr/bin/env python3

from pathlib import Path
import re
import subprocess
import argparse

arg_parse = argparse.ArgumentParser()
arg_parse.add_argument("name", help="Name of the object to compare, e.g d_a_bridge")
args = arg_parse.parse_args()

project_root = Path(__file__).parent.parent
rel_name = args.name

if True:
  target_map_path = Path(project_root / "orig" / "debug_maps" /  f"{rel_name}D.map")
  base_map_path = Path(project_root / "build" / "D44J01" / rel_name / f"{rel_name}.plf.MAP")
else:
  target_map_path = Path(project_root / "orig" / "debug_maps" / "frameworkD.map")
  base_map_path = Path(project_root / "build" / "D44J01" / "framework.elf.MAP")

print(f"Root: {project_root}")
print(f"rel_name: {rel_name}")
print(f"target_map_path: {target_map_path}")
print(f"base_map_path: {base_map_path}")

retcode = subprocess.call(["python", "configure.py", "--version", "D44J01", "--debug", "--map"], cwd=project_root)
retcode = subprocess.call(["ninja", base_map_path.relative_to(project_root)], cwd=project_root)
assert retcode == 0

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
    symbol_entry_match = re.search(r"^  [0-9a-f]{8} ([0-9a-f]{6}) ([0-9a-f]{8})(?: +\d+)? (.+?)(?: \(entry of [^)]+\))? \t", line, re.IGNORECASE)
    if symbol_entry_match:
      symbol_size = symbol_entry_match.group(1)
      symbol_size = int(symbol_size, 16)
      symbol_offset = symbol_entry_match.group(2)
      symbol_offset = int(symbol_offset, 16)
      symbol_name = symbol_entry_match.group(3)
      symbols[symbol_name] = symbol_size
      #print("%08X  %s" % (symbol_offset, symbol_name))
  
  #print(rel_symbol_names)
  
  return symbols

if True:
  target_symbols = get_rel_symbols(target_map_path.read_text())
  base_symbols = get_rel_symbols(base_map_path.read_text())
else:
  # obj_names = ["d_a_player_main.o"]
  obj_names = None
  target_symbols = get_main_symbols(target_map_path.read_text(), valid_obj_names=obj_names)
  base_symbols = get_main_symbols(base_map_path.read_text(), valid_obj_names=obj_names)

print(len(target_symbols), len(base_symbols))

symbol_size_diffs = []
for symbol_name, target_size in target_symbols.items():
    if target_size == 0:
      continue
    if symbol_name not in base_symbols:
      # continue
      base_size = 0
    else:
    #   continue
      base_size = base_symbols[symbol_name]
    size_diff = abs(target_size - base_size)
    # print(symbol_name, size_diff)
    # if size_diff < 4:
    #   continue
    ratio = size_diff / target_size
    # if ratio < 0.5:
    #   continue
    # if not re.search("__\\d+J3D", symbol_name):
    #   continue
    # if not re.search("\\dTVec3<f>", symbol_name):
    #   continue
    symbol_size_diffs.append((symbol_name, target_size, base_size, ratio))

symbol_size_diffs.sort(key=lambda x: x[-1])
for symbol_name, target_size, base_size, ratio in symbol_size_diffs:
  prefix = ""
  if base_size == 0:
    prefix = "MISSING: "
  print(prefix + symbol_name, "0x%X" % target_size, "0x%X" % base_size, ratio)
  
for symbol_name, base_size in base_symbols.items():
  if symbol_name in target_symbols:
    continue
  # if "fop" not in symbol_name:
  #   continue
  print("FAKE:", symbol_name)
