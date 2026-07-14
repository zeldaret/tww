#!/usr/bin/env python3

# Compares used inlines for a TU in the decomp compared to the official debug maps.
# Checks for missing inline usages, fake inline usages, and inlines being the wrong size.
# NOTE: You must mark the TU as "Matching" in configure.py, even if it doesn't match! Otherwise this script won't work properly.

# To use this script, pass the name of the TU as the only argument. Examples:
# ./tools/utilities/debug_map_diff.py d_a_andsw0
# ./tools/utilities/debug_map_diff.py d_a_npc_fa1

from pathlib import Path
import re
import subprocess
import argparse
from collections import defaultdict

arg_parse = argparse.ArgumentParser()
arg_parse.add_argument("object_name", help="Name of the object to compare, e.g. d_a_bridge or d_a_npc_fa1")
args = arg_parse.parse_args()
target_object_name: str = args.object_name
assert "/" not in target_object_name and "." not in target_object_name, "The object name should not contain slashes or dots"

debug_maps_root_path = Path("orig/D44J01/files/maps")
decomp_root_path = Path(".")

retcode = subprocess.call(["python", "configure.py", "--version", "D44J01", "--debug", "--map", "--non-matching"], cwd=decomp_root_path)
assert retcode == 0, "Failed to configure"

all_ninja_outputs = []
for ninja_target in subprocess.check_output(["ninja", "-t", "targets", "all"]).decode("utf-8").splitlines():
  ninja_output, ninja_rule = ninja_target.split(":", 1)
  all_ninja_outputs.append(ninja_output)

target_map_path_dol = debug_maps_root_path / "frameworkD.map"
target_map_path_rel = debug_maps_root_path / f"{target_object_name}D.map"
if target_map_path_rel.exists():
  target_is_rel = True
  target_map_path = target_map_path_rel
else:
  assert target_map_path_dol.exists()
  target_is_rel = False
  target_map_path = target_map_path_dol
del target_map_path_dol
del target_map_path_rel

base_map_path_dol = decomp_root_path / "build/D44J01/framework.elf.MAP"
base_map_path_rel = decomp_root_path / f"build/D44J01/{target_object_name}/{target_object_name}.plf.MAP"
if str(base_map_path_rel) in all_ninja_outputs:
  base_is_rel = True
  base_map_path = base_map_path_rel
else:
  assert str(base_map_path_dol) in all_ninja_outputs
  base_is_rel = False
  base_map_path = base_map_path_dol
del base_map_path_dol
del base_map_path_rel

retcode = subprocess.call(["ninja", base_map_path.relative_to(decomp_root_path)], cwd=decomp_root_path)
assert retcode == 0, "Ninja build call failed"

class Symbol:
  def __init__(self, name: str, size: int, sym_type: str | None = None, linkage: str | None = None, stripped: bool | None = None):
    self.name = name
    self.size = size
    self.sym_type = sym_type
    self.linkage = linkage
    self.stripped = stripped
  
  def __repr__(self):
    return f"Symbol(name={self.name}, size={self.size}, sym_type={self.sym_type}, linkage={self.linkage}, stripped={self.stripped})"

def get_symbols_from_linker_map(map_contents: str, missing_tree_and_stripped=False):
  map_lines = map_contents.splitlines()
  
  object_name_to_ext = {}
  def remove_object_ext(object_name: str):
    object_name, object_ext = object_name.split(".", 1)
    if object_name in object_name_to_ext:
      # Check to be sure we never have two objects with the same name but different extensions
      assert object_name_to_ext[object_name] == object_ext
    else:
      object_name_to_ext[object_name] = object_ext
    return object_name
  
  object_name_to_symbol_name_to_type_and_linkage = defaultdict(dict)
  localstatic_counters = defaultdict(lambda: defaultdict(int))
  unref_dupe_symbol_names_to_object_name_to_type_linkage = {}
  if not missing_tree_and_stripped:
    line = map_lines.pop(0)
    assert line == "Link map of _prolog" or line == "Link map of __start"
    curr_unref_dupe_symbol_name = None
    while True:
      line = map_lines.pop(0)
      if line == "":
        # End of link map
        break
      
      unref_dupe_symbol_match = re.search(r"^  +(\d+)\] >>> UNREFERENCED DUPLICATE (\S+)$", line)
      if unref_dupe_symbol_match:
        link_map_depth = int(unref_dupe_symbol_match.group(1))
        curr_unref_dupe_symbol_name = unref_dupe_symbol_match.group(2)
        assert curr_unref_dupe_symbol_name not in unref_dupe_symbol_names_to_object_name_to_type_linkage
        unref_dupe_symbol_names_to_object_name_to_type_linkage[curr_unref_dupe_symbol_name] = {}
        continue
      unref_dupe_linkage_match = re.search(r"^  +(\d+)\] >>> \((func|object),(weak)\) found in (\S+) $", line)
      if unref_dupe_linkage_match:
        assert curr_unref_dupe_symbol_name is not None
        link_map_depth = int(unref_dupe_linkage_match.group(1))
        symbol_type = unref_dupe_linkage_match.group(2)
        linkage = unref_dupe_linkage_match.group(3)
        object_name = remove_object_ext(unref_dupe_linkage_match.group(4))
        
        # A symbol shouldn't be duplicates multiple times in the same object, but it's possible for multiple objects to have the exact same name.
        # e.g. getRaw__Q37JGadget6binary10TParseDataCFv is in 5 different TUs named control.o
        # Not really any way to detect this, so just ignore it and check that the types all match.
        # assert object_name not in unref_dupe_symbol_names_to_object_name_to_type_linkage[curr_unref_dupe_symbol_name]
        if object_name in unref_dupe_symbol_names_to_object_name_to_type_linkage[curr_unref_dupe_symbol_name]:
          assert (symbol_type, linkage) == unref_dupe_symbol_names_to_object_name_to_type_linkage[curr_unref_dupe_symbol_name][object_name]
        
        unref_dupe_symbol_names_to_object_name_to_type_linkage[curr_unref_dupe_symbol_name][object_name] = (symbol_type, linkage)
        continue
      else:
        curr_unref_dupe_symbol_name = None
      
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
      object_name = remove_object_ext(normal_symbol_match.group(5))
      
      if localstatic_match := re.search(r"^([^\s\$]+)\$\d+$", symbol_name):
        localstatic_name = localstatic_match.group(1)
        localstatic_counters[object_name][localstatic_name] += 1
        symbol_name = f"{localstatic_name}${localstatic_counters[object_name][localstatic_name]}"
      
      assert symbol_name not in object_name_to_symbol_name_to_type_and_linkage[object_name], f"Duplicate symbol: {repr(symbol_name)}"
      object_name_to_symbol_name_to_type_and_linkage[object_name][symbol_name] = (symbol_type, linkage)
  
  symbols: dict[str, dict[str, Symbol]] = defaultdict(dict)
  localstatic_counters = defaultdict(lambda: defaultdict(int))
  unref_dupe_symbol_names_already_added = set()
  for line in map_lines:
    symbol_entry_match = re.search(r"^  ([0-9a-f]{8}|UNUSED  ) ([0-9a-f]{6}) ([0-9a-f]{8}|\.{8})(?: +\d+)? (.+?)(?: \(entry of [^)]+\))? \t?(\S+)", line, re.IGNORECASE)
    if symbol_entry_match:
      symbol_offset = symbol_entry_match.group(1)
      symbol_size = symbol_entry_match.group(2)
      symbol_size = int(symbol_size, 16)
      symbol_address = symbol_entry_match.group(3)
      if symbol_offset == "UNUSED  ":
        assert symbol_address == "........"
      if symbol_address == "........":
        assert symbol_offset == "UNUSED  "
        symbol_address = None
        stripped = True
      else:
        symbol_address = int(symbol_address, 16)
        stripped = False
      symbol_name = symbol_entry_match.group(4)
      object_name = remove_object_ext(symbol_entry_match.group(5))
      
      if symbol_name.startswith(".") or symbol_name in ["extab", "extabindex"]:
        # e.g. Section symbol (.text) or pool symbol (...data)
        continue
      if re.search(r"^@\d+$", symbol_name):
        continue
      if localstatic_match := re.search(r"^([^\s\$]+)\$\d+$", symbol_name):
        localstatic_name = localstatic_match.group(1)
        localstatic_counters[object_name][localstatic_name] += 1
        symbol_name = f"{localstatic_name}${localstatic_counters[object_name][localstatic_name]}"
      
      if symbol_name in object_name_to_symbol_name_to_type_and_linkage[object_name]:
        symbol_type, linkage = object_name_to_symbol_name_to_type_and_linkage[object_name][symbol_name]
      else:
        assert stripped or missing_tree_and_stripped, f"Symbol {repr(symbol_name)} is missing linkage information in object {repr(object_name)}"
        symbol_type = linkage = None
      symbols[object_name][symbol_name] = Symbol(symbol_name, symbol_size, sym_type=symbol_type, linkage=linkage, stripped=stripped)
      
      if symbol_name in unref_dupe_symbol_names_to_object_name_to_type_linkage and symbol_name not in unref_dupe_symbol_names_already_added:
        for other_object_name in unref_dupe_symbol_names_to_object_name_to_type_linkage[symbol_name]:
          symbol_type, linkage = unref_dupe_symbol_names_to_object_name_to_type_linkage[symbol_name][other_object_name]
          assert stripped == False, "Shouldn't reach a stripped duplicate here"
          symbols[other_object_name][symbol_name] = Symbol(symbol_name, symbol_size, sym_type=symbol_type, linkage=linkage, stripped=stripped)
        unref_dupe_symbol_names_already_added.add(symbol_name)
  
  return symbols

def is_debug_only_symbol(symbol_name: str):
  if "__11JORMContextF" in symbol_name:
    return True
  return False

target_missing_tree_and_stripped = not target_is_rel

all_target_symbols = get_symbols_from_linker_map(target_map_path.read_text(), missing_tree_and_stripped=target_missing_tree_and_stripped)
target_symbols = all_target_symbols[target_object_name]
if len(target_symbols) == 0:
  raise Exception("Failed to find object matching the given name (check for typos)")

all_base_symbols = get_symbols_from_linker_map(base_map_path.read_text())
base_symbols = all_base_symbols[target_object_name]
if len(base_symbols) == 0:
  raise Exception("Failed to find object matching the given name (check for typos)")

print(len(target_symbols), len(base_symbols))

target_symbol_names_in_previous_objects = set()
if target_missing_tree_and_stripped:
  # This handles the logic for checking if a symbol already appeared earlier on in framework.map.
  # Note: I'm not sure if the logic here is 100% accurate for edge cases since it just relies on dict insertion order.
  # Might need to add more robust logic later that keeps track of symbol section, address, or line number within the map file...?
  for object_name, symbols in all_target_symbols.items():
    if object_name == target_object_name:
      break
    for symbol_name, symbol in symbols.items():
      target_symbol_names_in_previous_objects.add(symbol.name)

symbol_size_diffs = []
total_missing = 0
total_fake = 0
total_maybe_fake = 0
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
  if symbol_name in base_symbols and size_diff != 0:
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
  
maybe_fake_symbols = []
fake_symbols = []
for symbol_name, base_symbol in base_symbols.items():
  if symbol_name in target_symbols:
    continue
  if target_missing_tree_and_stripped and (base_symbol.stripped or symbol_name in target_symbol_names_in_previous_objects):
    maybe_fake_symbols.append(base_symbol)
  else:
    fake_symbols.append(base_symbol)

for base_symbol in maybe_fake_symbols:
    print("FAKE?:", base_symbol.name, "0x%X" % base_symbol.size)
    total_maybe_fake += 1

for base_symbol in fake_symbols:
    print("FAKE:", base_symbol.name, "0x%X" % base_symbol.size)
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
  wrong_linkage = False
  if target_symbol.linkage is None and base_symbol.sym_type == "object":
    # The official framework.map for main.dol doesn't include linkage, but we can guess it based off of certain symbol name prefixes.
    if base_symbol.name.startswith("l_") and base_symbol.linkage != "local":
      wrong_linkage = True
      target_linkage = "local"
    elif base_symbol.name.startswith("g_") and base_symbol.linkage != "global":
      wrong_linkage = True
      target_linkage = "global"
  elif target_symbol.linkage is not None and target_symbol.linkage != base_symbol.linkage:
    wrong_linkage = True
    target_linkage = target_symbol.linkage
  if wrong_linkage:
    total_wrong_linkage += 1
    print(f"LINKAGE: {symbol_name} (should be {target_linkage}, is {base_symbol.linkage})")

print("==================================================")
print(f"Total right size: {total_right_size}")
print(f"Total wrong size: {total_wrong_size}")
print(f"Total fake: {total_fake}")
print(f"Total maybe fake: {total_maybe_fake}")
print(f"Total missing: {total_missing}")
print(f"Total wrong linkage: {total_wrong_linkage}")
