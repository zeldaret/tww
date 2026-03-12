# Dumps structure members to C format with comments and names
#@Pheenoh / Taka / LagoLunatic
#@category #Decomp
#@keybinding 
#@menupath 
#@toolbar 

import re

dtm = currentProgram.getDataTypeManager();

type_name = askString("Generate Struct Members", "Enter a data type name: ")
struct_path = type_name.replace("::", "/")
struct = dtm.getDataType("/" + struct_path)
if struct is None:
    struct = dtm.getDataType("/Demangler/" + struct_path)
if struct is None:
    raise Exception("Could not find struct with name: %s" % type_name)

size = struct.getLength()
size_str = str("{:X}".format(size))

offset_pad_size = len(size_str)

check = False
start_address = ""
member_name = ""
undefined_member_name = ""

datatype_remaps = {
    'byte': 'u8',
    'uchar': 'u8',
    'sbyte': 's8',
    'short': 's16',
    'ushort': 'u16',
    'undefined1': 'u8',
    'undefined2': 'u16',
    'undefined4': 'u32',
    'undefined1 *': 'u8*',
    'undefined2 *': 'u16*',
    'undefined4 *': 'u32*',
    #'int': 's32', # Breaks matches sometimes
    'long': 's32',
    'unsigned int': 'uint',
    'ulong': 'u32',
    'float': 'f32',
    'pointer': 'void*',
    'MTX34': 'Mtx',
    'MTX34 *': 'MtxP',
    #'PTMF': 
    'TVec3<float>': 'JGeometry::TVec3<f32>',
    '_GXColor': 'GXColor',
    '_GXColorS10': 'GXColorS10',
}

undefined_member_name_prefix = "field_0x"
# undefined_member_name_prefix = "m"

out_lines = []
for i in range (struct.getNumComponents()):
    data_type = str(struct.getComponent(i).getDataType().getName())
    offset = struct.getComponent(i).getOffset()
    hex_offset_string = str("%0*X" % (offset_pad_size, offset))
    
    if struct.getComponent(i).getFieldName() is not None:
        member_name = str(struct.getComponent(i).getFieldName())
    else:
        member_name = undefined_member_name_prefix+hex_offset_string
    
    if member_name in ["parent", "base"] and data_type in ['fopAc_ac_c', 'dBgS_MoveBgActor', 'fopNpc_npc_c', 'fopEn_enemy_c', 'daPy_py_c', 'daPy_npc_c']:
      # Not a member, inheritance
      continue
    
    # if undefined member
    if data_type == 'undefined' or check == True:
        if data_type == 'undefined':
            if check == False:
                check = True
                start_address = hex_offset_string
            continue
        
        check = False
        undefined_member_name = undefined_member_name_prefix+start_address+"[0x"+hex_offset_string+" - 0x"+start_address+"]"
    
    if undefined_member_name != "":
        undefined_member_name = "    /* 0x" +start_address+" */ u8 "+undefined_member_name+";"
        out_lines.append(undefined_member_name)
        undefined_member_name = ""
    
    print(data_type)
    data_type = str(data_type)
    
    if data_type in datatype_remaps:
        data_type = datatype_remaps[data_type]
    
    if "[" in data_type:
        # move array to member name
        array_start_idx = data_type.find("[")
        array = data_type[array_start_idx:]
        data_type = data_type[0:array_start_idx]
        if data_type in datatype_remaps:
            data_type = datatype_remaps[data_type]
        member_name = member_name+array
    elif data_type == "char":
        data_type = "s8"
    
    if data_type == "PTMF": # Pointer to member function
        match = re.search("^mCurr?(\S+Func)$", member_name)
        if match:
          data_type = match.group(1)
        else:
          # Just guess at the return type and parameters
          data_type = "int"
          member_name = "("+type_name+"::*"+member_name+")()"
    
    member_string = "    /* 0x" +hex_offset_string+" */ "+str(data_type).replace(" ","")+" "+member_name+";"
    out_lines.append(member_string)

hex_end_offset_string = str("%0*X" % (offset_pad_size, struct.getLength()))
if check:
    undefined_member_name = undefined_member_name_prefix+start_address+"[0x"+hex_end_offset_string+" - 0x"+start_address+"]"
    member_string = "    /* 0x" +start_address+" */ "+"u8"+" "+undefined_member_name+";"
    out_lines.append(member_string)

out_lines.append("};  // Size: 0x%s" % hex_end_offset_string)

out_str = "\n".join(out_lines)
print(out_str)

# Copy to clipboard
from docking.dnd import GClipboard
from java.awt.datatransfer import Clipboard, StringSelection
clipboard = GClipboard.getSystemClipboard()
data = StringSelection(out_str)
clipboard.setContents(data, None)
