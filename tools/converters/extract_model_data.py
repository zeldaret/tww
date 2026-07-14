#!/usr/bin/env python3

from argparse import ArgumentParser
import struct
import os
from enum import Enum
from binary_funcs import read_f32, read_u8

def write_array_declaration(c_file, symbol_name: str, scope: str, type: str):
    if scope == "local":
        var_def_prefix = "static "
    else:
        var_def_prefix = ""

    c_file.write(f"{var_def_prefix}{type} {symbol_name}[] = {{\n")

def format_float_array(elements: list[tuple[float, ...]]) -> str:
    if len(elements) == 0:
        return ""

    num_components: int = len(elements[0])

    # Get the longest float for each component
    longest_components: list[int] = [0] * num_components
    for element in elements:
        for i, component in enumerate(element):
            length = len(f"{component:f}".rstrip('0'))
            if f"{component:f}".rstrip('0').endswith('.'):
                length += 1
            longest_components[i] = max(length, longest_components[i])

    result: str = ""
    for element in elements:
        # Open each array element
        result += "    {"
        for i, component in enumerate(element):
            # Remove all the trailing 0s (unless the value would end with the decimal point)
            value = f'{component:f}'.rstrip('0')
            if value.endswith('.'):
                value += '0'

            # Only add the comma + minimum 1 space if this isn't the last element
            if i != len(element) - 1:
                result += f"{f'{value}f, ':<{longest_components[i] + 3}}"
            else:
                result += f"{f'{value}f':<{longest_components[i] + 1}}"

        result += "},\n"

    return result

def convert_binary_to_Vec_c_source(src_path: str, dest_path: str, symbol_name: str, scope: str):
    # Load data
    with open(src_path, "rb") as binary_file, open(dest_path, "w") as c_file:

        c_file.write('#include "dolphin/mtx/vec.h"\n\n')

        write_array_declaration(c_file, symbol_name, scope, "Vec")

        elements: list[tuple[float, ...]] = []
        while True:
            try:
                x, y, z = read_f32(binary_file), read_f32(binary_file), read_f32(binary_file)
            except EOFError:
                break

            elements.append((x, y, z))

        lines = format_float_array(elements)
        c_file.write(lines)

        c_file.write("};\n")

def convert_binary_to_cXy_c_source(src_path: str, dest_path: str, symbol_name: str, scope: str):
    # Load data
    with open(src_path, "rb") as binary_file, open(dest_path, "w") as c_file:

        c_file.write('#include "SSystem/SComponent/c_xyz.h"\n\n')

        write_array_declaration(c_file, symbol_name, scope, "cXy")

        elements: list[tuple[float, ...]] = []
        while True:
            try:
                x, y = read_f32(binary_file), read_f32(binary_file)
            except EOFError:
                break

            elements.append((x, y))

        lines = format_float_array(elements)
        c_file.write(lines)

        c_file.write("};\n")

def convert_binary_to_GXColor_c_source(src_path: str, dest_path: str, symbol_name: str, scope: str):
    # Load data
    with open(src_path, "rb") as binary_file, open(dest_path, "w") as c_file:

        c_file.write('#include "dolphin/gx/GXStruct.h"\n\n')
        
        write_array_declaration(c_file, symbol_name, scope, "GXColor")
        
        while True:
            try:
                r, g, b, a = read_u8(binary_file), read_u8(binary_file), read_u8(binary_file), read_u8(binary_file)
            except EOFError:
                break

            c_file.write("    " + f"{{0x{r:02X}, 0x{g:02X}, 0x{b:02X}, 0x{a:02X}}}" + ",\n")
        
        c_file.write("};\n")


def main():
    parser = ArgumentParser(
        description="Converts a binary file containing vertex data to an array of the specified type"
    )
    parser.add_argument("src_path", type=str, help="Binary source file path")
    parser.add_argument("dest_path", type=str, help="Destination C include file path")
    parser.add_argument(
        "--type",
        type=str,
        help="Data type",
    )
    parser.add_argument(
        "--symbol",
        type=str,
        help="Symbol name",
    )
    parser.add_argument(
        "--scope",
        choices=["global", "local"],
        default="local",
        help="The scope of the symbol",
    )

    args = parser.parse_args()

    if args.type == "Vec":
        convert_binary_to_Vec_c_source(args.src_path, args.dest_path, args.symbol, args.scope)
    elif args.type == "cXy":
        convert_binary_to_cXy_c_source(args.src_path, args.dest_path, args.symbol, args.scope)
    elif args.type == "GXColor":
        convert_binary_to_GXColor_c_source(args.src_path, args.dest_path, args.symbol, args.scope)
    else:
        raise Exception(f"Unknown data type: {args.type}")


if __name__ == "__main__":
    main()
