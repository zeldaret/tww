"""
Automatically writes source structs for colliders.
"""
from dataclasses import dataclass
from pathlib import Path
import collections
import json
import re
import struct
import textwrap
import sys


PROJ_DIR = Path(__file__).parent.parent
ASM_DIR = PROJ_DIR / 'build' / 'GZLE01'
INCLUDE_DIR = PROJ_DIR / 'include'
SRC_DIR = PROJ_DIR / 'src'


def strip_namespace_mangled_name(name):
    # Convert `m_sph_src__13daObj_Ikada_c` to `m_sph_src`.
    #         `body_co_cyl_src$6067` to `body_co_cyl_src`.
    #         `M_sph_data__10daObjHha_c` to `m_sph_data`.
    return name.split('__')[0].split('$')[0].lower()


def read_src_objects_from_asm_files(object_name) -> dict[str, bytes]:
    objects = collections.defaultdict(bytearray)

    for asm_file in ASM_DIR.glob('**/*.s'):
        if not object_name in str(asm_file):
            continue
        with asm_file.open('r') as f:
            obj_name = None
            for line in f:
                if line.startswith('.obj '):
                    obj_name = line.split()[1].replace(',', '').strip()
                    # Quick filter to skip non-collider objects.
                    if ('src' not in obj_name) and ('sph' not in obj_name) and ('cyl' not in obj_name):
                        obj_name = None
                        continue
                    obj_name = strip_namespace_mangled_name(obj_name)
                    obj_name = asm_file.stem + '::' + obj_name
                    continue
                elif line.startswith('.endobj '):
                    obj_name = None
                    continue

                if obj_name is None:
                    continue
                if not line.startswith('\t.4byte '):
                    continue
                hex_value = line.split()[-1]
                hex_value = int(hex_value, 16)
                objects[obj_name].extend(hex_value.to_bytes(4, 'big'))

    return objects


def main(object_name, type, addr):
    collider_src_obj_bytes = read_src_objects_from_asm_files(object_name)
    if len(collider_src_obj_bytes) == 0:
        print(f"No object found with the name {object_name}")
        exit()

    assert len(collider_src_obj_bytes) == 1

    for k, v in collider_src_obj_bytes.items():
        src_obj_data = v
        break;

    # Maps class and namespace names to their corresponding header files.
    class_to_src_file = {}
    # Maps source file names like `d_a_bst` to their corresponding source files.
    src_file_names = {}

    struct = generate_src_object(type, src_obj_data)
    print(struct)


def add_struct_to_file(src_file: Path, caller: str, src_obj_name: str, struct: str):
    with src_file.open('r', encoding='utf8') as f:
        src = f.read()

    new_src = modify_source_for_file(src, caller, src_obj_name, struct)

    with src_file.open('w', encoding='utf8') as f:
        new_src = '\n'.join(new_src)
        # If the file ends with a newline, we want to keep it.
        if src.endswith('\n'):
            new_src += '\n'
        f.write(new_src)


def modify_source_for_file(src: str, caller: str, src_obj_name: str, struct: str) -> list[str]:
    new_src = src.splitlines()

    last_include_line = None
    for i, line in enumerate(src.splitlines()):
        if line.startswith('#include '):
            last_include_line = i
    # Check if the include is already present, if not, add it.
    if '#include "d/d_cc_d.h"' not in src:
        new_src.insert(last_include_line + 1, '#include "d/d_cc_d.h"')
        last_include_line += 1

    # If there isn't a dollar in the src_obj_name, we just add it after the
    # includes.
    if '$' not in src_obj_name:
        struct = f'\n{struct}\n'
        new_src[last_include_line + 1:last_include_line + 1] = struct.splitlines()
        return new_src

    func_line = None
    # First, look for the line that the function is defined in.
    for i, line in enumerate(new_src):
        match = re.search(r"^.* (\S*)\(.*\) {", line)
        if match and match.group(1) == caller:
            func_line = i
            break
    # Okay, let's try just the function name without the namespaces.
    if func_line is None:
        func_name = caller.split('::')[-1]
        for i, line in enumerate(new_src):
            match = re.search(r"^.* (\S*)\(.*\) {", line)
            if match and match.group(1) == func_name:
                func_line = i
                break

    if func_line is None:
        raise ValueError(f"Could not find function {caller}")

    # Check if the next line is a nonmatching statement, if so we want to
    # insert after that.
    if 'nonmatching' in new_src[func_line + 1].lower():
        func_line += 1

    struct = textwrap.indent(struct, '    ')
    new_src[func_line + 1:func_line + 1] = struct.splitlines()

    return new_src


@dataclass
class dCcD_SrcGObjInf:
    Flags: int  # Flags
    SrcObjAt_Type: int # SrcObjAt  Type
    SrcObjAt_Atp: int  # SrcObjAt  Atp
    SrcObjAt_SPrm: int # SrcObjAt  SPrm
    SrcObjTg_Type: int # SrcObjTg  Type
    SrcObjTg_SPrm: int # SrcObjTg  SPrm
    SrcObjCo_SPrm: int # SrcObjCo  SPrm
    SrcGObjAt_Se: int   # SrcGObjAt Se
    SrcGObjAt_HitMark: int # SrcGObjAt HitMark
    SrcGObjAt_Spl: int # SrcGObjAt Spl
    SrcGObjAt_Mtrl: int # SrcGObjAt Mtrl
    SrcGObjAt_SPrm: int # SrcGObjAt SPrm
    SrcGObjTg_Se: int  # SrcGObjTg Se
    SrcGObjTg_HitMark: int # SrcGObjTg HitMark
    SrcGObjTg_Spl: int # SrcGObjTg Spl
    SrcGObjTg_Mtrl: int # SrcGObjTg Mtrl
    SrcGObjTg_SPrm: int # SrcGObjTg SPrm
    SrcGObjCo_SPrm: int # SrcGObjCo SPrm

    def _from_bytes(b: bytes):
        return dCcD_SrcGObjInf(
            *struct.unpack(
                (
                    '>' # big-endian
                    'I' # flags, u32
                    'I' # at_type, u32
                    'b' # at_atp, u8
                    'xxx' # three padding bytes
                    'I' # at_sprm, u32
                    'I' # tg_type, u32
                    'I' # tg_sprm, u32
                    'I' # co_sprm, u32
                    'B' # at_se, u8
                    'B' # at_hitmark, u8
                    'B' # at_spl, u8
                    'B' # at_mtrl, u8
                    'I' # at_sprm, u32
                    'B' # tg_se, u8
                    'B' # tg_hitmark, u8
                    'B' # tg_spl, u8
                    'B' # tg_mtrl, u8
                    'I' # tg_sprm, u32
                    'I' # co_sprm, u32
                ),
                b
            )
        )


class BitMask:
    JOINT_VALUES = {}

    @classmethod
    def to_bitmask(cls, value: int, allow_zero: bool = False):
        if value == 0 and not allow_zero:
            raise ValueError(f"Value for {cls} cannot be zero.")
        if value == 0:
            return '0'

        # First see if any joint values apply,
        if value in cls.JOINT_VALUES:
            return cls.JOINT_VALUES[value]

        bit_values = []
        bit_string = bin(value)[2:]  # Get binary representation without '0b' prefix
        for i, bit in enumerate(reversed(bit_string), start=1):
            if bit == '1':
                if i not in cls.ENUM_VALS:
                    raise ValueError(f"Bit position {i} not defined in {cls}.")
                bit_values.append(cls.ENUM_VALS[i])
        return ' | '.join(bit_values)

# enum cCcD_AtSPrm_e - Possible values for `SrcObjAt  SPrm`
class AtSprm_enum(BitMask):
    ENUM_VALS = {
        1: 'cCcD_AtSPrm_Set_e',
        2: 'cCcD_AtSPrm_VsEnemy_e',
        3: 'cCcD_AtSPrm_VsPlayer_e',
        4: 'cCcD_AtSPrm_VsOther_e',
        5: 'cCcD_AtSPrm_NoTgHitInfSet_e'
    }
    JOINT_VALUES = {
        0xE: 'cCcD_AtSPrm_GrpAll_e'
    }

# enum cCcD_TgSPrm_e - Possible values for `SrcObjTg  SPrm`
class TgSprm_enum(BitMask):
    ENUM_VALS = {
        1: 'cCcD_TgSPrm_Set_e',
        2: 'cCcD_TgSPrm_IsEnemy_e',
        3: 'cCcD_TgSPrm_IsPlayer_e',
        4: 'cCcD_TgSPrm_IsOther_e',
        5: 'cCcD_TgSPrm_NoAtHitInfSet_e'
    }
    JOINT_VALUES = {
        0xE: 'cCcD_TgSPrm_GrpAll_e'
    }

# enum cCcD_CoSPrm_e - Possible values for `SrcObjCo  SPrm`
class CoSprm_enum(BitMask):
    ENUM_VALS = {
        1: 'cCcD_CoSPrm_Set_e',
        2: 'cCcD_CoSPrm_IsEnemy_e',
        3: 'cCcD_CoSPrm_IsPlayer_e',
        4: 'cCcD_CoSPrm_IsOther_e',
        5: 'cCcD_CoSPrm_VsEnemy_e',
        6: 'cCcD_CoSPrm_VsPlayer_e',
        7: 'cCcD_CoSPrm_VsOther_e',
        8: 'cCcD_CoSPrm_Sph3DCrr_e',
        9: 'cCcD_CoSPrm_NoCrr_e',
        10: 'cCcD_CoSPrm_NoCoHitInfSet_e'
    }
    JOINT_VALUES = {
        0xE: 'cCcD_CoSPrm_IGrpAll_e',
        0x70: 'cCcD_CoSPrm_VsGrpAll_e',
    }

# enum dCcG_AtSPrm_e - Possible values for `SrcGObjAt SPrm`
class G_AtSPrm_enum(BitMask):
    ENUM_VALS = {
        1: 'dCcG_AtSPrm_NoConHit_e',
        2: 'dCcG_AtSPrm_NoHitMark_e',
        3: 'dCcG_AtSPrm_StopNoConHit_e',
        4: 'dCcG_AtSPrm_NoMass_e',
    }

# enum dCcG_TgSPrm_e - Possible values for `SrcGObjTg SPrm`
class G_TgSprm_enum(BitMask):
    ENUM_VALS = {
        1: 'dCcG_TgSPrm_Shield_e',
        2: 'dCcG_TgSPrm_NoConHit_e',
        3: 'dCcG_TgSPrm_NoHitMark_e',
        4: 'dCcG_TgSPrm_ShieldFrontRange_e',
    }

# enum dCcD_ObjAtType
class ObjAtType_enum(BitMask):
    ENUM_VALS = {
        2: 'AT_TYPE_SWORD',
        4: 'AT_TYPE_UNK8',
        6: 'AT_TYPE_BOMB',
        7: 'AT_TYPE_BOOMERANG',
        8: 'AT_TYPE_BOKO_STICK',
        9: 'AT_TYPE_WATER',
        10: 'AT_TYPE_FIRE',
        11: 'AT_TYPE_MACHETE',
        12: 'AT_TYPE_UNK800',
        13: 'AT_TYPE_SPIKE',
        14: 'AT_TYPE_UNK2000',
        15: 'AT_TYPE_NORMAL_ARROW',
        16: 'AT_TYPE_HOOKSHOT',
        17: 'AT_TYPE_SKULL_HAMMER',
        18: 'AT_TYPE_UNK20000',
        19: 'AT_TYPE_FIRE_ARROW',
        20: 'AT_TYPE_ICE_ARROW',
        21: 'AT_TYPE_LIGHT_ARROW',
        22: 'AT_TYPE_WIND',
        23: 'AT_TYPE_UNK400000',
        24: 'AT_TYPE_LIGHT',
        25: 'AT_TYPE_STALFOS_MACE',
        26: 'AT_TYPE_UNK2000000',
        27: 'AT_TYPE_DARKNUT_SWORD',
        28: 'AT_TYPE_GRAPPLING_HOOK',
        29: 'AT_TYPE_MOBLIN_SPEAR',
        30: 'AT_TYPE_PGANON_SWORD',
    }

class ObjAtType_negated_enum(BitMask):
    ENUM_VALS = {
        k: f"~{v}"
        for k, v in ObjAtType_enum.ENUM_VALS.items()
    }


def attack_type_mask(type: int) -> str:
    """Return damage/collision type as a string."""
    if type == 0:
        return '0'
    if type == 0xFFFFFFFF:
        return 'AT_TYPE_ALL'

    # 27 total attack types. As a heuristic if more than 17 are in use we
    # negate from AT_TYPE_ALL instead.
    if bin(type).count('1') <= 17:
        return ObjAtType_enum.to_bitmask(type)

    negated_type = 0xFFFFFFFF & ~type
    bit_mask = ObjAtType_negated_enum.to_bitmask(negated_type).replace('|', '&')
    return 'AT_TYPE_ALL & ' + bit_mask


# enum dCcG_hitSe
hitSe_enum = {
    0: '0',
    1: 'dCcG_SE_UNK1',
    2: 'dCcG_SE_UNK2',
    4: 'dCcG_SE_UNK4',
    5: 'dCcG_SE_UNK5',
    6: 'dCcG_SE_UNK6',
    7: 'dCcG_SE_ARROW',
    8: 'dCcG_SE_HOOKSHOT',
    0x23: 'dCcG_SE_UNK23',
    0x25: 'dCcG_SE_UNK25',
}

# enum CcG_At_HitMark
At_HitMark_enum = {
    0: 'dCcG_AtHitMark_None_e',
    1: 'dCcG_AtHitMark_Unk1_e',
    0xD: 'dCcG_AtHitMark_Nrm_e',
    0xF: 'dCcG_AtHitMark_Big_e',
}
# enum CcG_Tg_HitMark
Tg_HitMark_enum = {
    0: '0',
    1: 'dCcG_TgHitMark_Unk1_e',
    0xC: 'dCcg_TgHitMark_Purple_e',
    0xD: 'dCcG_TgHitMark_Nrm_e',
    0xFF: 'dCcG_TgHitMark_Unk255_e', # Added by us.
}
# enum dCcG_At_Spl
At_Spl_enum = {
    0: 'dCcG_At_Spl_UNK0',
    1: 'dCcG_At_Spl_UNK1',
    2: 'dCcG_At_Spl_UNK2', # Added by us.
    3: 'dCcG_At_Spl_UNK3',
    5: 'dCcG_At_Spl_UNK5',
    6: 'dCcG_At_Spl_UNK6',
    7: 'dCcG_At_Spl_UNK7',
    8: 'dCcG_At_Spl_UNK8',
    9: 'dCcG_At_Spl_UNK9',
    0xA: 'dCcG_At_Spl_UNKA',
    0xB: 'dCcG_At_Spl_UNKB',
}
# enum dCcG_Tg_Spl
Tg_Spl_enum = {
    0: 'dCcG_Tg_Spl_UNK0',
    1: 'dCcG_Tg_Spl_UNK1',
}


TYPE_STRUCT_MAP = {
    'dCcD_Sph': 'dCcD_SrcSph',
    'dCcD_Cps': 'dCcD_SrcCps',
    'dCcD_Cyl': 'dCcD_SrcCyl',
    'dCcD_Tri': 'dCcD_SrcTri',
}

def generate_src_object(type, src_obj_data):
    primary: dCcD_SrcGObjInf = dCcD_SrcGObjInf._from_bytes(src_obj_data[:0x30])

    if type == 'dCcD_Sph':
        secondary_struct = generate_sphere_struct(src_obj_data[0x30:])
    elif type == 'dCcD_Cps':
        secondary_struct = generate_capsule_struct(src_obj_data[0x30:])
    elif type == 'dCcD_Cyl' or type == "dCcD_SrcCyl":
        secondary_struct = generate_cylinder_struct(src_obj_data[0x30:])
    elif type == 'dCcD_Tri':
        secondary_struct = generate_tri_struct(src_obj_data[0x30:])
    else:
        raise NotImplementedError(f"Unsupported collider type: {type}")

    # These always seem to be 0. Let's assert it and hardcode the value.
    assert primary.Flags == 0
    assert primary.SrcGObjAt_Mtrl == 0
    assert primary.SrcGObjTg_Mtrl == 0
    assert primary.SrcGObjCo_SPrm == 0

    assert primary.SrcGObjAt_Se in hitSe_enum
    primary.SrcGObjAt_Se = hitSe_enum[primary.SrcGObjAt_Se]

    assert primary.SrcGObjAt_HitMark in At_HitMark_enum
    primary.SrcGObjAt_HitMark = At_HitMark_enum[primary.SrcGObjAt_HitMark]

    assert primary.SrcGObjAt_Spl in At_Spl_enum
    primary.SrcGObjAt_Spl = At_Spl_enum[primary.SrcGObjAt_Spl]

    assert primary.SrcGObjTg_Se in hitSe_enum
    primary.SrcGObjTg_Se = hitSe_enum[primary.SrcGObjTg_Se]

    assert primary.SrcGObjTg_HitMark in Tg_HitMark_enum
    primary.SrcGObjTg_HitMark = Tg_HitMark_enum[primary.SrcGObjTg_HitMark]

    assert primary.SrcGObjTg_Spl in Tg_Spl_enum
    primary.SrcGObjTg_Spl = Tg_Spl_enum[primary.SrcGObjTg_Spl]


    return f"""\
static {TYPE_STRUCT_MAP[type] if type in TYPE_STRUCT_MAP else type} M_cyl_src = {{
    // dCcD_SrcGObjInf
    {{
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ {attack_type_mask(primary.SrcObjAt_Type)},
        /* SrcObjAt  Atp     */ {primary.SrcObjAt_Atp},
        /* SrcObjAt  SPrm    */ {AtSprm_enum.to_bitmask(primary.SrcObjAt_SPrm, allow_zero=True)},
        /* SrcObjTg  Type    */ {attack_type_mask(primary.SrcObjTg_Type)},
        /* SrcObjTg  SPrm    */ {TgSprm_enum.to_bitmask(primary.SrcObjTg_SPrm, allow_zero=True)},
        /* SrcObjCo  SPrm    */ {CoSprm_enum.to_bitmask(primary.SrcObjCo_SPrm, allow_zero=True)},
        /* SrcGObjAt Se      */ {primary.SrcGObjAt_Se},
        /* SrcGObjAt HitMark */ {primary.SrcGObjAt_HitMark},
        /* SrcGObjAt Spl     */ {primary.SrcGObjAt_Spl},
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ {G_AtSPrm_enum.to_bitmask(primary.SrcGObjAt_SPrm, allow_zero=True)},
        /* SrcGObjTg Se      */ {primary.SrcGObjTg_Se},
        /* SrcGObjTg HitMark */ {primary.SrcGObjTg_HitMark},
        /* SrcGObjTg Spl     */ {primary.SrcGObjTg_Spl},
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ {G_TgSprm_enum.to_bitmask(primary.SrcGObjTg_SPrm, allow_zero=True)},
        /* SrcGObjCo SPrm    */ 0,
    }},
{secondary_struct}
}};
"""

@dataclass
class dCcD_Sphere:
    x: float
    y: float
    z: float
    radius: float

    def _from_bytes(b: bytes):
        return dCcD_Sphere(*struct.unpack('>fff f', b))

def generate_sphere_struct(sphere_data):
    sphere = dCcD_Sphere._from_bytes(sphere_data)

    return f"""\
    // cM3dGSphS
    {{
        /* Center */ {sphere.x}f, {sphere.y}f, {sphere.z}f,
        /* Radius */ {sphere.radius}f,
    }},"""

@dataclass
class dCcD_Capsule:
    p0_x: float
    p0_y: float
    p0_z: float
    p1_x: float
    p1_y: float
    p1_z: float
    height: float

    def _from_bytes(b: bytes):
        return dCcD_Capsule(*struct.unpack('>fff fff f', b))

def generate_capsule_struct(capsule_data):
    cap = dCcD_Capsule._from_bytes(capsule_data)
    return f"""\
    // cM3dGCpsS
    {{
        /* P0 */ {cap.p0_x}f, {cap.p0_y}f, {cap.p0_z}f,
        /* P1 */ {cap.p1_x}f, {cap.p1_y}f, {cap.p1_z}f,
        /* Height */ {cap.height}f,
    }},"""

@dataclass
class dCcD_Cylinder:
    center_x: float
    center_y: float
    center_z: float
    radius: float
    height: float

    def _from_bytes(b: bytes):
        return dCcD_Cylinder(*struct.unpack('>fff f f', b))

def generate_cylinder_struct(cylinder_data):
    cylinder = dCcD_Cylinder._from_bytes(cylinder_data)
    return f"""\
    // cM3dGCylS
    {{
        /* Center */ {cylinder.center_x}f, {cylinder.center_y}f, {cylinder.center_z}f,
        /* Radius */ {cylinder.radius}f,
        /* Height */ {cylinder.height}f,
    }},"""

@dataclass
class dCcD_Triangle:
    a_x: float
    a_y: float
    a_z: float
    b_x: float
    b_y: float
    b_z: float
    c_x: float
    c_y: float
    c_z: float

    def _from_bytes(b: bytes):
        return dCcD_Triangle(*struct.unpack('>fff fff fff', b))

def generate_tri_struct(tri_data):
    tri: dCcD_Triangle = dCcD_Triangle._from_bytes(tri_data)
    return f"""\
// cM3dGTriS
{{
    /* a */ {tri.a_x}f, {tri.a_y}f, {tri.a_z}f,
    /* b */ {tri.b_x}f, {tri.b_y}f, {tri.b_z}f,
    /* c */ {tri.c_x}f, {tri.c_y}f, {tri.c_z}f,
}},"""


GHIDRA_DATA = """
...
"""


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2], int(sys.argv[3], 16))
