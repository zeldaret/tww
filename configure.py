#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import json
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 1
VERSIONS = [
    "GZLJ01",  # 0
    "GZLE01",  # 1
    "GZLP01",  # 2
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--no-asm",
    action="store_true",
    help="don't incorporate .s files from asm directory",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--warn",
    dest="warn",
    type=str,
    choices=["all", "off", "error"],
    help="how to handle warnings",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
if args.no_asm:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-1"
config.compilers_tag = "20240706"
config.dtk_tag = "v1.4.1"
config.objdiff_tag = "v3.0.0-beta.6"
config.sjiswrap_tag = "v1.2.0"
config.wibo_tag = "0.6.11"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym version={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.debug:
    config.ldflags.append("-g")  # Or -gdwarf-2 for Wii linkers
if args.map:
    config.ldflags.append("-mapunused")
    # config.ldflags.append("-listclosure") # For Wii linkers

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = 72 # The Wind Waker (DOL)

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    # "-W all",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-fp_contract on",
    "-str reuse",
    "-multibyte",  # For Wii compilers, replace with `-enc SJIS`
    "-i include",
    f"-i build/{config.version}/include",
    "-i src",
    "-i src/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Include",
    "-i src/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Include",
    "-i src/PowerPC_EABI_Support/MSL/MSL_C/PPC_EABI/Include",
    "-i src/PowerPC_EABI_Support/MSL/MSL_C++/MSL_Common/Include",
    "-i src/PowerPC_EABI_Support/Runtime/Inc",
    f"-DVERSION={version_num}",
]

# Debug flags
if args.debug:
    # Or -sym dwarf-2 for Wii compilers
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
    cflags_base.extend(['-pragma "dont_inline on"'])
    cflags_base.extend(['-pragma "optimization_level 0"'])
else:
    cflags_base.append("-DNDEBUG=1")
if args.warn == "all":
    cflags_base.append("-W all")
elif args.warn == "off":
    cflags_base.append("-W off")
elif args.warn == "error":
    cflags_base.append("-W error")

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-gccinc",
    "-common off",
    "-inline deferred,auto",
    "-char signed",
]

# Dolphin library flags
cflags_dolphin = [
    *cflags_base,
    "-fp_contract off",
]

# Framework flags
cflags_framework = [
    *cflags_base,
    "-use_lmw_stmw off",
    "-str reuse,pool,readonly",
    "-inline noauto",
    "-O3,s",
    "-schedule off",
    "-sym on",
    "-fp_contract off",
]

# REL flags
cflags_rel = [
    *cflags_framework,
    "-sdata 0",
    "-sdata2 0",
]

config.linker_version = "GC/1.3.2"


# Helper function for Dolphin libraries
def DolphinLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5n",
        "cflags": cflags_dolphin,
        "progress_category": "sdk",
        "host": False,
        "objects": objects,
    }


# Helper function for REL script objects
def Rel(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.3.2",
        "cflags": cflags_rel,
        "progress_category": "game",
        "host": True,
        "objects": objects,
    }


# Helper function for actor RELs
def ActorRel(status, rel_name, extra_cflags=[]):
    return Rel(rel_name, [Object(
        status, f"d/actor/{rel_name}.cpp",
        extra_cflags=extra_cflags,
        scratch_preset_id=73, # The Wind Waker (REL)
    )])


# Helper function for JSystem libraries
def JSystemLib(lib_name, objects, progress_category="third_party"):
    return {
        "lib": lib_name,
        "mw_version": "GC/1.3.2",
        "cflags": cflags_framework,
        "progress_category": progress_category,
        "host": True,
        "objects": objects,
    }

Matching = True                   # Object matches and should be linked
NonMatching = False               # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    {
        "lib": "machine",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_framework,
        "progress_category": "core",
        "host": True,
        "objects": [
            Object(Matching,    "m_Do/m_Do_main.cpp"),
            Object(Matching,    "m_Do/m_Do_printf.cpp"),
            Object(Matching,    "m_Do/m_Do_audio.cpp"),
            Object(Matching,    "m_Do/m_Do_controller_pad.cpp"),
            Object(NonMatching, "m_Do/m_Do_graphic.cpp"),
            Object(Matching,    "m_Do/m_Do_machine.cpp"),
            Object(Matching,    "m_Do/m_Do_mtx.cpp", extra_cflags=['-pragma "nosyminline on"']),
            Object(NonMatching, "m_Do/m_Do_ext.cpp", extra_cflags=["-sym off"]),
            Object(NonMatching, "m_Do/m_Do_lib.cpp"),
            Object(Matching,    "m_Do/m_Do_hostIO.cpp"),
            Object(Matching,    "m_Do/m_Do_Reset.cpp"),
            Object(Matching,    "m_Do/m_Do_dvd_thread.cpp"),
            Object(Matching,    "m_Do/m_Do_DVDError.cpp"),
            Object(Matching,    "m_Do/m_Do_MemCard.cpp"),
            Object(Matching,    "m_Do/m_Do_MemCardRWmng.cpp"),
            Object(Matching,    "m_Do/m_Do_gba_com.cpp"),
            Object(Matching,    "m_Do/m_Do_machine_exception.cpp"),
        ],
    },
    {
        "lib": "c",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_framework,
        "progress_category": "game",
        "host": True,
        "objects": [
            Object(NonMatching, "c/c_damagereaction.cpp"),
            Object(Matching,    "c/c_dylink.cpp"),
        ],
    },
    {
        "lib": "framework",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_framework,
        "progress_category": "core",
        "host": True,
        "objects": [
            # f_ap
            Object(Matching,    "f_ap/f_ap_game.cpp"),

            # f_op
            Object(Matching,    "f_op/f_op_actor.cpp", extra_cflags=["-sym off"]),
            Object(Matching,    "f_op/f_op_actor_iter.cpp"),
            Object(Matching,    "f_op/f_op_actor_tag.cpp"),
            Object(Equivalent,  "f_op/f_op_actor_mng.cpp", extra_cflags=['-pragma "nosyminline on"']), # weak func order
            Object(Matching,    "f_op/f_op_camera.cpp"),
            Object(Matching,    "f_op/f_op_camera_mng.cpp"),
            Object(Matching,    "f_op/f_op_overlap.cpp"),
            Object(Matching,    "f_op/f_op_overlap_mng.cpp"),
            Object(Matching,    "f_op/f_op_overlap_req.cpp"),
            Object(Matching,    "f_op/f_op_scene.cpp"),
            Object(Matching,    "f_op/f_op_scene_iter.cpp"),
            Object(Matching,    "f_op/f_op_scene_mng.cpp"),
            Object(Matching,    "f_op/f_op_scene_req.cpp"),
            Object(Matching,    "f_op/f_op_scene_tag.cpp"),
            Object(Matching,    "f_op/f_op_view.cpp"),
            Object(Matching,    "f_op/f_op_kankyo.cpp"),
            Object(Matching,    "f_op/f_op_msg.cpp"),
            Object(Matching,    "f_op/f_op_kankyo_mng.cpp"),
            Object(NonMatching, "f_op/f_op_msg_mng.cpp", extra_cflags=['-pragma "nosyminline on"']),
            Object(Matching,    "f_op/f_op_draw_iter.cpp"),
            Object(Matching,    "f_op/f_op_draw_tag.cpp"),
            Object(Matching,    "f_op/f_op_scene_pause.cpp"),

            # f_pc
            Object(Matching,    "f_pc/f_pc_base.cpp"),
            Object(Matching,    "f_pc/f_pc_create_iter.cpp"),
            Object(Matching,    "f_pc/f_pc_create_req.cpp"),
            Object(Matching,    "f_pc/f_pc_create_tag.cpp"),
            Object(Matching,    "f_pc/f_pc_creator.cpp"),
            Object(Matching,    "f_pc/f_pc_delete_tag.cpp"),
            Object(Matching,    "f_pc/f_pc_deletor.cpp"),
            Object(Matching,    "f_pc/f_pc_draw_priority.cpp"),
            Object(Matching,    "f_pc/f_pc_executor.cpp"),
            Object(Matching,    "f_pc/f_pc_layer.cpp"),
            Object(Matching,    "f_pc/f_pc_leaf.cpp"),
            Object(Matching,    "f_pc/f_pc_layer_iter.cpp"),
            Object(Matching,    "f_pc/f_pc_layer_tag.cpp"),
            Object(Matching,    "f_pc/f_pc_line.cpp"),
            Object(Matching,    "f_pc/f_pc_load.cpp"),
            Object(Matching,    "f_pc/f_pc_manager.cpp"),
            Object(Matching,    "f_pc/f_pc_method.cpp"),
            Object(Matching,    "f_pc/f_pc_node.cpp"),
            Object(Matching,    "f_pc/f_pc_node_req.cpp"),
            Object(Matching,    "f_pc/f_pc_priority.cpp"),
            Object(Matching,    "f_pc/f_pc_profile.cpp"),
            Object(Matching,    "f_pc/f_pc_searcher.cpp"),
            Object(Matching,    "f_pc/f_pc_line_tag.cpp"),
            Object(Matching,    "f_pc/f_pc_line_iter.cpp"),
            Object(Matching,    "f_pc/f_pc_method_iter.cpp"),
            Object(Matching,    "f_pc/f_pc_method_tag.cpp"),
            Object(Matching,    "f_pc/f_pc_pause.cpp"),
            Object(Matching,    "f_pc/f_pc_draw.cpp"),
            Object(Matching,    "f_pc/f_pc_fstcreate_req.cpp"),
            Object(Matching,    "f_pc/f_pc_stdcreate_req.cpp"),
        ],
    },
    {
        "lib": "dolzel",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_framework,
        "progress_category": "game",
        "host": True,
        "objects": [
            Object(Equivalent,  "d/d_stage.cpp"), # weak func order
            Object(NonMatching, "d/d_map.cpp"),
            Object(Matching,    "d/d_com_inf_game.cpp", extra_cflags=['-sym off']),
            Object(Matching,    "d/d_com_lib_game.cpp"),
            Object(Matching,    "d/d_com_static.cpp", extra_cflags=['-sym off']),
            Object(Matching,    "d/d_lib.cpp"),
            Object(Matching,    "d/d_save.cpp", extra_cflags=['-pragma "nosyminline on"']),
            Object(Matching,    "d/d_save_init.cpp"),
            Object(Matching,    "d/d_shop.cpp", extra_cflags=['-pragma "nosyminline on"']),
            Object(Matching,    "d/d_jnt_hit.cpp"),
            Object(Matching,    "d/d_chain.cpp"),
            Object(NonMatching, "d/d_cloth_packet.cpp"),
            Object(NonMatching, "d/d_a_obj.cpp"),
            Object(Matching,    "d/d_a_obj_tribox_static.cpp"),
            Object(Matching,    "d/d_a_ship_static.cpp"),
            Object(Matching,    "d/d_a_boko_static.cpp"),
            Object(Matching,    "d/d_a_bomb_static.cpp"),
            Object(Matching,    "d/d_a_branch_static.cpp"),
            Object(Matching,    "d/d_a_mgameboard_static.cpp"),
            Object(Matching,    "d/d_a_itembase_static.cpp"),
            Object(Matching,    "d/d_a_item_static.cpp"),
            Object(Matching,    "d/d_a_shop_item_static.cpp"),
            Object(Matching,    "d/d_a_race_item_static.cpp"),
            Object(Matching,    "d/d_a_leaflift_static.cpp"),
            Object(NonMatching, "d/d_demo.cpp"),
            Object(Equivalent,  "d/d_door.cpp", extra_cflags=['-pragma "nosyminline on"']), # weak func order
            Object(Matching,    "d/d_resorce.cpp", extra_cflags=['-pragma "nosyminline on"']),
            Object(Matching,    "d/d_material.cpp"),
            Object(Matching,    "d/d_event.cpp"),
            Object(Matching,    "d/d_event_data.cpp"),
            Object(Matching,    "d/d_event_manager.cpp"),
            Object(NonMatching, "d/d_magma.cpp", extra_cflags=['-sym off']),
            Object(NonMatching, "d/d_boss_magma.cpp"),
            Object(Matching,    "d/d_grass.cpp", extra_cflags=['-pragma "nosyminline on"']),
            Object(NonMatching, "d/d_tree.cpp"),
            Object(NonMatching, "d/d_particle.cpp"),
            Object(Matching,    "d/d_particle_name.cpp"),
            Object(Matching,    "d/d_path.cpp"),
            Object(Matching,    "d/d_drawlist.cpp", extra_cflags=['-sym off']),
            Object(Matching,    "d/d_kankyo_data.cpp"),
            Object(Matching,    "d/d_kankyo_wether.cpp"),
            Object(NonMatching, "d/d_kankyo_rain.cpp"),
            Object(Matching,    "d/d_kankyo_demo.cpp"),
            Object(NonMatching, "d/d_detect.cpp"),
            Object(Matching,    "d/d_vibration.cpp"),
            Object(Matching,    "d/d_vib_pattern.cpp"),
            Object(Matching,    "d/d_attention.cpp"),
            Object(Matching,    "d/d_att_dist.cpp"),
            Object(Matching,    "d/d_bg_s.cpp"),
            Object(Matching,    "d/d_bg_s_acch.cpp"),
            Object(Matching,    "d/d_bg_s_func.cpp"),
            Object(Matching,    "d/d_bg_s_lin_chk.cpp"),
            Object(Matching,    "d/d_bg_s_movebg_actor.cpp"),
            Object(Matching,    "d/d_bg_s_spl_grp_chk.cpp"),
            Object(Matching,    "d/d_bg_s_wtr_chk.cpp"),
            Object(Matching,    "d/d_bg_w.cpp"),
            Object(Matching,    "d/d_bg_w_deform.cpp"),
            Object(Matching,    "d/d_bg_w_hf.cpp"),
            Object(Matching,    "d/d_bg_w_sv.cpp"),
            Object(Matching,    "d/d_cc_d.cpp"),
            Object(Matching,    "d/d_cc_mass_s.cpp"),
            Object(Matching,    "d/d_cc_s.cpp"),
            Object(Matching,    "d/d_cc_uty.cpp"),
            Object(NonMatching, "d/d_cam_param.cpp"),
            Object(Matching,    "d/d_cam_type.cpp"),
            Object(Matching,    "d/d_cam_style.cpp"),
            Object(Matching,    "d/d_cam_type2.cpp"),
            Object(NonMatching, "d/d_ev_camera.cpp"),
            Object(Matching,    "d/d_wood.cpp", extra_cflags=["-sym off"]),
            Object(NonMatching, "d/d_flower.cpp"),
            Object(Matching,    "d/d_item_data.cpp"),
            Object(Matching,    "d/d_seafightgame.cpp"),
            Object(Matching,    "d/d_spline_path.cpp"),
            Object(Matching,    "d/d_s_actor_data_mng.cpp"),
            Object(Matching,    "d/d_item.cpp"),
            Object(NonMatching, "d/d_2dnumber.cpp"),
            Object(Matching,    "d/d_a_npc_cb1_static.cpp"),
            Object(NonMatching, "d/d_a_npc_mk_static.cpp"),
            Object(Matching,    "d/d_salvage.cpp"),
            Object(Matching,    "d/d_snap.cpp"),
            Object(Matching,    "d/d_point_wind.cpp"),
            Object(Equivalent,  "d/actor/d_a_agb.cpp", extra_cflags=['-pragma "nosyminline on"']), # weak func order
            Object(Matching,    "d/actor/d_a_arrow.cpp", extra_cflags=["-sym off"]),
            Object(Matching,    "d/actor/d_a_bg.cpp"),
            Object(Equivalent,  "d/actor/d_a_bomb.cpp", extra_cflags=['-pragma "nosyminline on"']), # weak func order
            Object(Matching,    "d/actor/d_a_bomb2.cpp"),
            Object(NonMatching, "d/actor/d_a_boomerang.cpp"),
            Object(Matching,    "d/actor/d_a_dai_item.cpp", extra_cflags=["-sym off"]),
            Object(NonMatching, "d/actor/d_a_demo00.cpp"),
            Object(Matching,    "d/actor/d_a_disappear.cpp"),
            Object(Matching,    "d/actor/d_a_esa.cpp"),
            Object(NonMatching, "d/actor/d_a_grid.cpp"),
            Object(NonMatching, "d/actor/d_a_himo2.cpp"),
            Object(Equivalent,  "d/actor/d_a_hookshot.cpp"), # weak func order
            Object(Matching,    "d/actor/d_a_ib.cpp", extra_cflags=['-pragma "nosyminline on"']),
            Object(NonMatching, "d/actor/d_a_item.cpp"),
            Object(Matching,    "d/actor/d_a_itembase.cpp"),
            Object(Matching,    "d/actor/d_a_nh.cpp"),
            Object(NonMatching, "d/actor/d_a_npc_fa1.cpp"),
            Object(NonMatching, "d/actor/d_a_obj_search.cpp"),
            Object(Matching,    "d/actor/d_a_player.cpp"),
            Object(NonMatching, "d/actor/d_a_player_main.cpp"),
            Object(Matching,    "d/actor/d_a_player_npc.cpp"),
            Object(Matching,    "d/actor/d_a_sea.cpp"),
            Object(Matching,    "d/actor/d_a_spc_item01.cpp"),
            Object(Matching,    "d/actor/d_a_vrbox.cpp", extra_cflags=['-pragma "nosyminline on"']),
            Object(Matching,    "d/actor/d_a_vrbox2.cpp"),
            Object(NonMatching, "d/d_auction_screen.cpp"),
            Object(Matching,    "d/d_place_name.cpp"),
            Object(NonMatching, "d/d_camera.cpp"),
            Object(Matching,    "d/d_envse.cpp"),
            Object(NonMatching, "d/d_file_error.cpp"),
            Object(NonMatching, "d/d_file_select.cpp"),
            Object(Matching,    "d/d_gameover.cpp"),
            Object(NonMatching, "d/d_kankyo.cpp"),
            Object(Matching,    "d/d_kyeff.cpp"),
            Object(Matching,    "d/d_kyeff2.cpp"),
            Object(Matching,    "d/d_ky_thunder.cpp"),
            Object(Matching,    "d/d_letter.cpp"),
            Object(Matching,    "d/d_level_se.cpp"),
            Object(NonMatching, "d/d_menu_cloth.cpp"),
            Object(NonMatching, "d/d_menu_collect.cpp"),
            Object(NonMatching, "d/d_menu_dmap.cpp"),
            Object(NonMatching, "d/d_menu_fmap.cpp"),
            Object(NonMatching, "d/d_menu_fmap2.cpp"),
            Object(NonMatching, "d/d_menu_item.cpp"),
            Object(NonMatching, "d/d_menu_option.cpp"),
            Object(NonMatching, "d/d_menu_save.cpp"),
            Object(NonMatching, "d/d_menu_window.cpp"),
            Object(NonMatching, "d/d_mesg.cpp", extra_cflags=["-sym off"]),
            Object(NonMatching, "d/d_message.cpp"),
            Object(NonMatching, "d/d_message_paper.cpp"),
            Object(NonMatching, "d/d_meter.cpp"),
            Object(NonMatching, "d/d_minigame_starter.cpp"),
            Object(NonMatching, "d/d_minigame_terminater.cpp"),
            Object(NonMatching, "d/d_msg.cpp"),
            Object(NonMatching, "d/d_name.cpp"),
            Object(Matching,    "d/d_npc.cpp"),
            Object(NonMatching, "d/d_operate_wind.cpp"),
            Object(Matching,    "d/d_metronome.cpp"),
            Object(Matching,    "d/d_ovlp_fade.cpp"),
            Object(Matching,    "d/d_ovlp_fade2.cpp"),
            Object(MatchingFor("GZLE01", "GZLP01"), "d/d_ovlp_fade3.cpp"),
            Object(NonMatching, "d/d_ovlp_fade4.cpp"),
            Object(NonMatching, "d/d_picture_box.cpp"),
            Object(Matching,    "d/d_s_logo.cpp"),
            Object(Matching,    "d/d_s_menu.cpp"),
            Object(NonMatching, "d/d_s_name.cpp"),
            Object(Matching,    "d/d_s_open.cpp"),
            Object(NonMatching, "d/d_s_open_sub.cpp"),
            Object(Matching,    "d/d_s_play.cpp", extra_cflags=['-pragma "nosyminline on"']),
            Object(Matching,    "d/d_s_room.cpp", extra_cflags=['-pragma "nosyminline on"']),
            Object(Matching,    "d/d_s_title.cpp"),
            Object(NonMatching, "d/d_scope.cpp"),
            Object(Matching,    "d/d_throwstone.cpp"),
            Object(Matching,    "d/d_timer.cpp"),
            Object(NonMatching, "d/d_water_mark.cpp"),
            Object(Matching,    "d/d_wind_arrow.cpp"),
            Object(NonMatching, "d/d_wpillar.cpp"),
            Object(Matching,    "d/d_wpot_water.cpp"),
        ],
    },
    {
        "lib": "DynamicLink",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_framework,
        "progress_category": "core",
        "host": True,
        "objects": [
            Object(Matching,    "DynamicLink.cpp"),
        ],
    },
    {
        "lib": "SSystem",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_framework,
        "progress_category": "third_party",
        "host": True,
        "objects": [
            Object(Matching,    "SSystem/SComponent/c_malloc.cpp"),
            Object(Matching,    "SSystem/SComponent/c_API.cpp"),
            Object(Matching,    "SSystem/SComponent/c_API_graphic.cpp"),
            Object(Matching,    "SSystem/SComponent/c_cc_d.cpp"),
            Object(Matching,    "SSystem/SComponent/c_cc_s.cpp"),
            Object(Matching,    "SSystem/SComponent/c_counter.cpp"),
            Object(Matching,    "SSystem/SComponent/c_list.cpp"),
            Object(Matching,    "SSystem/SComponent/c_list_iter.cpp"),
            Object(Matching,    "SSystem/SComponent/c_node.cpp"),
            Object(Matching,    "SSystem/SComponent/c_node_iter.cpp"),
            Object(Matching,    "SSystem/SComponent/c_tree.cpp"),
            Object(Matching,    "SSystem/SComponent/c_tree_iter.cpp"),
            Object(Matching,    "SSystem/SComponent/c_phase.cpp"),
            Object(Matching,    "SSystem/SComponent/c_request.cpp"),
            Object(Matching,    "SSystem/SComponent/c_tag.cpp"),
            Object(Matching,    "SSystem/SComponent/c_tag_iter.cpp"),
            Object(Matching,    "SSystem/SComponent/c_xyz.cpp"),
            Object(Matching,    "SSystem/SComponent/c_sxyz.cpp"),
            Object(Matching,    "SSystem/SComponent/c_math.cpp"),
            Object(Matching,    "SSystem/SComponent/c_bg_s.cpp"),
            Object(Matching,    "SSystem/SComponent/c_bg_s_chk.cpp"),
            Object(Matching,    "SSystem/SComponent/c_bg_s_gnd_chk.cpp"),
            Object(Matching,    "SSystem/SComponent/c_bg_s_lin_chk.cpp"),
            Object(Matching,    "SSystem/SComponent/c_bg_w.cpp"),
            Object(Matching,    "SSystem/SComponent/c_m2d.cpp"),
            Object(Matching,    "SSystem/SComponent/c_m2d_g_box.cpp"),
            Object(Matching,    "SSystem/SComponent/c_m3d.cpp"),
            Object(Matching,    "SSystem/SComponent/c_m3d_g_aab.cpp"),
            Object(Matching,    "SSystem/SComponent/c_m3d_g_cyl.cpp"),
            Object(Matching,    "SSystem/SComponent/c_m3d_g_pla.cpp"),
            Object(Matching,    "SSystem/SComponent/c_m3d_g_sph.cpp"),
            Object(Matching,    "SSystem/SComponent/c_m3d_g_tri.cpp"),
            Object(Matching,    "SSystem/SComponent/c_lib.cpp"),
            Object(Matching,    "SSystem/SComponent/c_angle.cpp"),
            Object(Matching,    "SSystem/SComponent/c_data_tbl.cpp"),
            Object(Matching,    "SSystem/SStandard/s_basic.cpp"),
        ],
    },
    JSystemLib(
        "JFramework",
        [
            Object(Matching,    "JSystem/JFramework/JFWDisplay.cpp"),
            Object(NonMatching, "JSystem/JFramework/JFWSystem.cpp"),
        ],
    ),
    JSystemLib(
        "J3DU",
        [
            Object(Matching,    "JSystem/J3DU/J3DUClipper.cpp"),
            Object(NonMatching, "JSystem/J3DU/J3DUMotion.cpp"),
            Object(Matching,    "JSystem/J3DU/J3DUDL.cpp"),
        ],
    ),
    JSystemLib(
        "JParticle",
        [
            Object(Matching,    "JSystem/JParticle/JPABaseShape.cpp"),
            Object(Matching,    "JSystem/JParticle/JPAExtraShape.cpp"),
            Object(Matching,    "JSystem/JParticle/JPASweepShape.cpp"),
            Object(Matching,    "JSystem/JParticle/JPAExTexShape.cpp"),
            Object(Matching,    "JSystem/JParticle/JPADynamicsBlock.cpp"),
            Object(Matching,    "JSystem/JParticle/JPAFieldBlock.cpp"),
            Object(Matching,    "JSystem/JParticle/JPAKeyBlock.cpp"),
            Object(Matching,    "JSystem/JParticle/JPATexture.cpp"),
            Object(Matching,    "JSystem/JParticle/JPAResourceManager.cpp"),
            Object(Matching,    "JSystem/JParticle/JPAEmitterLoader.cpp"),
            Object(Matching,    "JSystem/JParticle/JPAMath.cpp"),
            Object(NonMatching, "JSystem/JParticle/JPAField.cpp"),
            Object(Matching,    "JSystem/JParticle/JPAEmitter.cpp"),
            Object(Matching,    "JSystem/JParticle/JPAParticle.cpp"),
            Object(Matching,    "JSystem/JParticle/JPAEmitterManager.cpp"),
            Object(NonMatching, "JSystem/JParticle/JPADrawVisitor.cpp"),
            Object(NonMatching, "JSystem/JParticle/JPADraw.cpp"),
            Object(Matching,    "JSystem/JParticle/JPADrawSetupTev.cpp"),
        ],
    ),
    JSystemLib(
        "JStage",
        [
            Object(Matching,    "JSystem/JStage/JSGActor.cpp"),
            Object(Matching,    "JSystem/JStage/JSGAmbientLight.cpp"),
            Object(Matching,    "JSystem/JStage/JSGCamera.cpp"),
            Object(Matching,    "JSystem/JStage/JSGFog.cpp"),
            Object(Matching,    "JSystem/JStage/JSGLight.cpp"),
            Object(Matching,    "JSystem/JStage/JSGObject.cpp"),
            Object(Matching,    "JSystem/JStage/JSGSystem.cpp"),
        ],
    ),
    JSystemLib(
        "JStudio",
        [
            Object(Matching,    "JSystem/JStudio/JStudio/jstudio-control.cpp"),
            Object(Matching,    "JSystem/JStudio/JStudio/jstudio-data.cpp"),
            Object(Matching,    "JSystem/JStudio/JStudio/jstudio-math.cpp"),
            Object(NonMatching, "JSystem/JStudio/JStudio/jstudio-object.cpp"),
            Object(Equivalent,  "JSystem/JStudio/JStudio/functionvalue.cpp"), # weak func order
            Object(NonMatching, "JSystem/JStudio/JStudio/fvb.cpp"),
            Object(Matching,    "JSystem/JStudio/JStudio/fvb-data.cpp"),
            Object(Matching,    "JSystem/JStudio/JStudio/fvb-data-parse.cpp"),
            Object(Matching,    "JSystem/JStudio/JStudio/object-id.cpp"),
            Object(NonMatching, "JSystem/JStudio/JStudio/stb.cpp"),
            Object(Matching,    "JSystem/JStudio/JStudio/stb-data.cpp"),
            Object(Matching,    "JSystem/JStudio/JStudio/stb-data-parse.cpp"),
        ],
    ),
    JSystemLib(
        "JStudio_JStage",
        [
            Object(Matching,    "JSystem/JStudio/JStudio_JStage/control.cpp"),
            Object(Matching,    "JSystem/JStudio/JStudio_JStage/object.cpp"),
            Object(Matching,    "JSystem/JStudio/JStudio_JStage/object-actor.cpp"),
            Object(Matching,    "JSystem/JStudio/JStudio_JStage/object-ambientlight.cpp"),
            Object(Matching,    "JSystem/JStudio/JStudio_JStage/object-camera.cpp"),
            Object(Matching,    "JSystem/JStudio/JStudio_JStage/object-fog.cpp"),
            Object(Matching,    "JSystem/JStudio/JStudio_JStage/object-light.cpp"),
        ],
    ),
    JSystemLib(
        "JStudio_JAudio",
        [
            Object(Matching,    "JSystem/JStudio/JStudio_JAudio/control.cpp"),
            Object(Matching,    "JSystem/JStudio/JStudio_JAudio/object-sound.cpp"),
        ],
    ),
    JSystemLib(
        "JStudio_JParticle",
        [
            Object(Matching,    "JSystem/JStudio/JStudio_JParticle/control.cpp"),
            Object(Matching,    "JSystem/JStudio/JStudio_JParticle/object-particle.cpp", extra_cflags=['-pragma "nosyminline on"']),
        ],
    ),
    JSystemLib(
        "JStudio_JMessage",
        [
            Object(Matching,    "JSystem/JStudio/JStudio_JMessage/control.cpp"),
            Object(Matching,    "JSystem/JStudio/JStudio_JMessage/object-message.cpp"),
        ],
    ),
    JSystemLib(
        "JStudioToolLibrary",
        [
            Object(Matching,    "JSystem/JStudio/JStudioToolLibrary/console.cpp"),
        ],
    ),
    JSystemLib(
        "JAudio",
        [
            Object(Matching,    "JSystem/JAudio/JASCalc.cpp"),
            Object(Matching,    "JSystem/JAudio/JASAiCtrl.cpp"),
            Object(Matching,    "JSystem/JAudio/JASDvdThread.cpp"),
            Object(Matching,    "JSystem/JAudio/JASCallback.cpp"),
            Object(Matching,    "JSystem/JAudio/JASRate.cpp"),
            Object(Matching,    "JSystem/JAudio/JASHardStream.cpp"),
            Object(Matching,    "JSystem/JAudio/JASHeapCtrl.cpp"),
            Object(Matching,    "JSystem/JAudio/JASResArcLoader.cpp"),
            Object(Matching,    "JSystem/JAudio/JASProbe.cpp"),
            Object(Matching,    "JSystem/JAudio/JASKernelDebug.cpp"),
            Object(Matching,    "JSystem/JAudio/JASCmdStack.cpp"),
            Object(Matching,    "JSystem/JAudio/JASSystemHeap.cpp"),
            Object(Matching,    "JSystem/JAudio/JASNoteMgr.cpp"),
            Object(Matching,    "JSystem/JAudio/JASOuterParam.cpp"),
            Object(Matching,    "JSystem/JAudio/JASPlayer_impl.cpp"),
            Object(Matching,    "JSystem/JAudio/JASRegisterParam.cpp"),
            Object(Matching,    "JSystem/JAudio/JASSeqCtrl.cpp"),
            Object(Matching,    "JSystem/JAudio/JASSeqParser.cpp"),
            Object(NonMatching, "JSystem/JAudio/JASTrack.cpp"),
            Object(Matching,    "JSystem/JAudio/JASTrackInterrupt.cpp"),
            Object(Matching,    "JSystem/JAudio/JASTrackPort.cpp"),
            Object(Matching,    "JSystem/JAudio/JASBank.cpp"),
            Object(Matching,    "JSystem/JAudio/JASWaveBank.cpp"),
            Object(Matching,    "JSystem/JAudio/JASBasicBank.cpp"),
            Object(Matching,    "JSystem/JAudio/JASBasicInst.cpp"),
            Object(Matching,    "JSystem/JAudio/JASDrumSet.cpp"),
            Object(NonMatching, "JSystem/JAudio/JASBasicWaveBank.cpp"),
            Object(Matching,    "JSystem/JAudio/JASSimpleWaveBank.cpp"),
            Object(Matching,    "JSystem/JAudio/JASInstEffect.cpp"),
            Object(Matching,    "JSystem/JAudio/JASInstSense.cpp"),
            Object(Matching,    "JSystem/JAudio/JASInstRand.cpp"),
            Object(Matching,    "JSystem/JAudio/JASWSParser.cpp"),
            Object(NonMatching, "JSystem/JAudio/JASBNKParser.cpp"),
            Object(Matching,    "JSystem/JAudio/JASWaveArcLoader.cpp"),
            Object(Matching,    "JSystem/JAudio/JASWaveBankMgr.cpp"),
            Object(NonMatching, "JSystem/JAudio/JASBankMgr.cpp"),
            Object(Matching,    "JSystem/JAudio/JASAudioThread.cpp"),
            Object(Matching,    "JSystem/JAudio/JASDSPBuf.cpp"),
            Object(NonMatching, "JSystem/JAudio/JASDSPChannel.cpp"),
            Object(Matching,    "JSystem/JAudio/JASDSPInterface.cpp"),
            Object(Matching,    "JSystem/JAudio/JASDriverIF.cpp"),
            Object(Matching,    "JSystem/JAudio/JASChGlobal.cpp"),
            Object(Matching,    "JSystem/JAudio/JASChAllocQueue.cpp"),
            Object(Matching,    "JSystem/JAudio/JASChannel.cpp"),
            Object(NonMatching, "JSystem/JAudio/JASChannelMgr.cpp"),
            Object(Matching,    "JSystem/JAudio/JASOscillator.cpp"),
            Object(Matching,    "JSystem/JAudio/JASDriverTables.cpp"),
            Object(Matching,    "JSystem/JAudio/dspproc.c", extra_cflags=["-lang c++", "-O4", "-func_align 32"]),
            Object(Matching,    "JSystem/JAudio/dsptask.c", extra_cflags=["-lang c++", "-O4", "-func_align 32"]),
            Object(Matching,    "JSystem/JAudio/osdsp.c", extra_cflags=["-lang c++", "-O4", "-func_align 32", "-str nopool"]),
            Object(Matching,    "JSystem/JAudio/osdsp_task.c", extra_cflags=["-lang c++", "-O4", "-func_align 32"]),
            Object(Matching,    "JSystem/JAudio/JAIAnimation.cpp"),
            Object(NonMatching, "JSystem/JAudio/JAIBasic.cpp"),
            Object(Matching,    "JSystem/JAudio/JAIBankWave.cpp"),
            Object(Matching,    "JSystem/JAudio/JAIConst.cpp"),
            Object(Matching,    "JSystem/JAudio/JAIDummyObject.cpp"),
            Object(Matching,    "JSystem/JAudio/JAIFx.cpp"),
            Object(Matching,    "JSystem/JAudio/JAIGlobalParameter.cpp"),
            Object(Matching,    "JSystem/JAudio/JAIInitData.cpp"),
            Object(NonMatching, "JSystem/JAudio/JAISeMgr.cpp"),
            Object(Matching,    "JSystem/JAudio/JAISequenceHeap.cpp"),
            Object(NonMatching, "JSystem/JAudio/JAISequenceMgr.cpp"),
            Object(NonMatching, "JSystem/JAudio/JAISound.cpp"),
            Object(NonMatching, "JSystem/JAudio/JAISoundTable.cpp"),
            Object(NonMatching, "JSystem/JAudio/JAIStreamMgr.cpp"),
            Object(Matching,    "JSystem/JAudio/JAISystemInterface.cpp"),
        ],
    ),
    JSystemLib(
        "JMessage",
        [
            Object(Matching,    "JSystem/JMessage/data.cpp"),
            Object(Matching,    "JSystem/JMessage/control.cpp"),
            Object(NonMatching, "JSystem/JMessage/processor.cpp"),
            Object(NonMatching, "JSystem/JMessage/resource.cpp"),
        ],
    ),
    DolphinLib(
        "gba",
        [
            Object(Matching,    "dolphin/gba/GBA.c"),
            Object(Matching,    "dolphin/gba/GBAGetProcessStatus.c"),
            Object(Matching,    "dolphin/gba/GBAJoyBoot.c"),
            Object(Matching,    "dolphin/gba/GBARead.c"),
            Object(Matching,    "dolphin/gba/GBAWrite.c"),
            Object(Matching,    "dolphin/gba/GBAXfer.c"),
        ],
    ),
    JSystemLib(
        "JAZelAudio",
        [
            Object(NonMatching, "JAZelAudio/JAIZelBasic.cpp"),
            Object(NonMatching, "JAZelAudio/JAIZelAnime.cpp"),
            Object(NonMatching, "JAZelAudio/JAIZelAtmos.cpp"),
            Object(NonMatching, "JAZelAudio/JAIZelInst.cpp"),
            Object(Matching,    "JAZelAudio/JAIZelParam.cpp"),
            Object(NonMatching, "JAZelAudio/JAIZelCharVoiceTable.cpp"),
            Object(Matching,    "JAZelAudio/JAIZelScene.cpp"),
            Object(Matching,    "JAZelAudio/JAIZelSound.cpp"),
        ],
        progress_category="game",
    ),
    DolphinLib(
        "gf",
        [
            Object(NonMatching, "dolphin/gf/GFGeometry.cpp"),
            Object(NonMatching, "dolphin/gf/GFLight.cpp"),
            Object(NonMatching, "dolphin/gf/GFPixel.cpp"),
            Object(NonMatching, "dolphin/gf/GFTev.cpp"),
            Object(NonMatching, "dolphin/gf/GFTransform.cpp"),
        ],
    ),
    JSystemLib(
        "JKernel",
        [
            Object(Matching,    "JSystem/JKernel/JKRHeap.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRStdHeap.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRExpHeap.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRSolidHeap.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRDisposer.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRThread.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRAram.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRAramHeap.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRAramBlock.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRAramPiece.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRAramStream.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRFileLoader.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRFileFinder.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRFileCache.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRArchivePub.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRArchivePri.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRMemArchive.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRAramArchive.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRDvdArchive.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRCompArchive.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRFile.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRDvdFile.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRDvdRipper.cpp"),
            Object(Matching,    "JSystem/JKernel/JKRDvdAramRipper.cpp", extra_cflags=["-sym off"]),
            Object(Matching,    "JSystem/JKernel/JKRDecomp.cpp"),
        ],
    ),
    JSystemLib(
        "JSupport",
        [
            Object(Matching,    "JSystem/JSupport/JSUList.cpp"),
            Object(Matching,    "JSystem/JSupport/JSUInputStream.cpp"),
            Object(Matching,    "JSystem/JSupport/JSUMemoryStream.cpp"),
            Object(Matching,    "JSystem/JSupport/JSUFileStream.cpp"),
        ],
    ),
    JSystemLib(
        "JGadget",
        [
            Object(Matching,    "JSystem/JGadget/binary.cpp"),
            Object(Matching,    "JSystem/JGadget/linklist.cpp"),
            Object(Matching,    "JSystem/JGadget/std-vector.cpp"),
        ],
    ),
    JSystemLib(
        "JUtility",
        [
            Object(Matching,    "JSystem/JUtility/JUTCacheFont.cpp"),
            Object(Matching,    "JSystem/JUtility/JUTResource.cpp"),
            Object(Matching,    "JSystem/JUtility/JUTTexture.cpp"),
            Object(Matching,    "JSystem/JUtility/JUTPalette.cpp"),
            Object(Matching,    "JSystem/JUtility/JUTNameTab.cpp"),
            Object(Matching,    "JSystem/JUtility/JUTGraphFifo.cpp"),
            Object(Matching,    "JSystem/JUtility/JUTFont.cpp"),
            Object(Matching,    "JSystem/JUtility/JUTResFont.cpp"),
            Object(Matching,    "JSystem/JUtility/JUTDbPrint.cpp"),
            Object(Matching,    "JSystem/JUtility/JUTGamePad.cpp"),
            Object(Matching,    "JSystem/JUtility/JUTException.cpp"),
            Object(Matching,    "JSystem/JUtility/JUTDirectPrint.cpp"),
            Object(Matching,    "JSystem/JUtility/JUTAssert.cpp"),
            Object(Matching,    "JSystem/JUtility/JUTVideo.cpp"),
            Object(Matching,    "JSystem/JUtility/JUTXfb.cpp"),
            Object(Matching,    "JSystem/JUtility/JUTFader.cpp"),
            Object(Matching,    "JSystem/JUtility/JUTProcBar.cpp"),
            Object(Matching,    "JSystem/JUtility/JUTConsole.cpp"),
            Object(Matching,    "JSystem/JUtility/JUTDirectFile.cpp"),
            Object(Matching,    "JSystem/JUtility/JUTGba.cpp"),
            Object(Matching,    "JSystem/JUtility/JUTFontData_Ascfont_fix12.cpp"), # Originally a .s file
        ],
    ),
    JSystemLib(
        "J2DGraph",
        [
            Object(Matching,    "JSystem/J2DGraph/J2DGrafContext.cpp"),
            Object(Matching,    "JSystem/J2DGraph/J2DOrthoGraph.cpp"),
            Object(Matching,    "JSystem/J2DGraph/J2DPrint.cpp"),
            Object(Matching,    "JSystem/J2DGraph/J2DPane.cpp"),
            Object(Matching,    "JSystem/J2DGraph/J2DScreen.cpp"),
            Object(Matching,    "JSystem/J2DGraph/J2DWindow.cpp"),
            Object(Matching,    "JSystem/J2DGraph/J2DPicture.cpp"),
            Object(Matching,    "JSystem/J2DGraph/J2DTextBox.cpp"),
        ],
    ),
    JSystemLib(
        "JRenderer",
        [
            Object(Matching,    "JSystem/JRenderer/JRenderer.cpp"),
        ],
    ),
    JSystemLib(
        "J3DGraphBase",
        [
            Object(Matching,    "JSystem/J3DGraphBase/J3DGD.cpp"),
            Object(Matching,    "JSystem/J3DGraphBase/J3DSys.cpp"),
            Object(Matching,    "JSystem/J3DGraphBase/J3DVertex.cpp"),
            Object(NonMatching, "JSystem/J3DGraphBase/J3DTransform.cpp"),
            Object(Matching,    "JSystem/J3DGraphBase/J3DPacket.cpp"),
            Object(Matching,    "JSystem/J3DGraphBase/J3DShapeMtx.cpp"),
            Object(Matching,    "JSystem/J3DGraphBase/J3DShape.cpp"),
            Object(Matching,    "JSystem/J3DGraphBase/J3DMaterial.cpp"),
            Object(NonMatching, "JSystem/J3DGraphBase/J3DMatBlock.cpp"),
            Object(Matching,    "JSystem/J3DGraphBase/J3DTevs.cpp"),
            Object(Matching,    "JSystem/J3DGraphBase/J3DDrawBuffer.cpp"),
        ],
    ),
    JSystemLib(
        "J3DGraphAnimator",
        [
            Object(Matching,    "JSystem/J3DGraphAnimator/J3DModelData.cpp"),
            Object(NonMatching, "JSystem/J3DGraphAnimator/J3DModel.cpp"),
            Object(Matching,    "JSystem/J3DGraphAnimator/J3DAnimation.cpp"),
            Object(Matching,    "JSystem/J3DGraphAnimator/J3DMaterialAnm.cpp"),
            Object(Matching,    "JSystem/J3DGraphAnimator/J3DVisibility.cpp"),
            Object(NonMatching, "JSystem/J3DGraphAnimator/J3DCluster.cpp"),
            Object(NonMatching, "JSystem/J3DGraphAnimator/J3DJoint.cpp"),
            Object(Matching,    "JSystem/J3DGraphAnimator/J3DNode.cpp"),
            Object(NonMatching, "JSystem/J3DGraphAnimator/J3DMaterialAttach.cpp"),
        ],
    ),
    JSystemLib(
        "J3DGraphLoader",
        [
            Object(Matching,     "JSystem/J3DGraphLoader/J3DMaterialFactory.cpp"),
            Object(Matching,     "JSystem/J3DGraphLoader/J3DMaterialFactory_v21.cpp"),
            Object(Matching,    "JSystem/J3DGraphLoader/J3DClusterLoader.cpp"),
            Object(Matching,    "JSystem/J3DGraphLoader/J3DModelLoader.cpp"),
            Object(Matching,    "JSystem/J3DGraphLoader/J3DModelLoaderCalcSize.cpp"),
            Object(Matching,    "JSystem/J3DGraphLoader/J3DJointFactory.cpp"),
            Object(Matching,    "JSystem/J3DGraphLoader/J3DShapeFactory.cpp"),
            Object(Matching,    "JSystem/J3DGraphLoader/J3DAnmLoader.cpp"),
        ],
    ),
    JSystemLib(
        "JMath",
        [
            Object(Matching,    "JSystem/JMath/JMath.cpp"),
            Object(Matching,    "JSystem/JMath/random.cpp"),
        ],
    ),
    DolphinLib(
        "base",
        [
            Object(NonMatching, "dolphin/base/PPCArch.c"),
        ],
    ),
    DolphinLib(
        "os",
        [
            Object(Matching, "dolphin/os/__start.c"),
            Object(Matching, "dolphin/os/OS.c"),
            Object(Matching, "dolphin/os/OSAlarm.c"),
            Object(Matching, "dolphin/os/OSAlloc.c"),
            Object(Matching, "dolphin/os/OSArena.c"),
            Object(Matching, "dolphin/os/OSAudioSystem.c"),
            Object(Matching, "dolphin/os/OSCache.c"),
            Object(Matching, "dolphin/os/OSContext.c"),
            Object(Matching, "dolphin/os/OSError.c"),
            Object(Matching, "dolphin/os/OSFont.c"),
            Object(Matching, "dolphin/os/OSInterrupt.c"),
            Object(Matching, "dolphin/os/OSLink.c"),
            Object(Matching, "dolphin/os/OSMessage.c"),
            Object(Matching, "dolphin/os/OSMemory.c"),
            Object(Matching, "dolphin/os/OSMutex.c"),
            Object(Matching, "dolphin/os/OSReboot.c"),
            Object(Matching, "dolphin/os/OSReset.c"),
            Object(Matching, "dolphin/os/OSResetSW.c"),
            Object(Matching, "dolphin/os/OSRtc.c"),
            Object(Matching, "dolphin/os/OSSync.c"),
            Object(Matching, "dolphin/os/OSThread.c"),
            Object(Matching, "dolphin/os/OSTime.c"),
            Object(Matching, "dolphin/os/__ppc_eabi_init.cpp"),
        ],
    ),
    DolphinLib(
        "exi",
        [
            Object(NonMatching, "dolphin/exi/EXIBios.c"),
            Object(NonMatching, "dolphin/exi/EXIUart.c"),
        ],
    ),
    DolphinLib(
        "si",
        [
            Object(NonMatching, "dolphin/si/SIBios.c"),
            Object(NonMatching, "dolphin/si/SISamplingRate.c"),
        ],
    ),
    DolphinLib(
        "db",
        [
            Object(NonMatching, "dolphin/db/db.c"),
        ],
    ),
    DolphinLib(
        "mtx",
        [
            Object(Matching,    "dolphin/mtx/mtx.c"),
            Object(Matching,    "dolphin/mtx/mtxvec.c"),
            Object(Matching,    "dolphin/mtx/mtx44.c"),
            Object(Matching,    "dolphin/mtx/vec.c"),
            Object(Matching,    "dolphin/mtx/quat.c"),
        ],
    ),
    DolphinLib(
        "dvd",
        [
            Object(Matching, "dolphin/dvd/dvdlow.c"),
            Object(Matching, "dolphin/dvd/dvdfs.c"),
            Object(Matching, "dolphin/dvd/dvd.c"),
            Object(Matching, "dolphin/dvd/dvdqueue.c"),
            Object(Matching, "dolphin/dvd/dvderror.c"),
            Object(Matching, "dolphin/dvd/dvdidutils.c"),
            Object(Matching, "dolphin/dvd/dvdFatal.c"),
            Object(Matching, "dolphin/dvd/fstload.c"),
        ],
    ),
    DolphinLib(
        "vi",
        [
            Object(NonMatching, "dolphin/vi/vi.c"),
        ],
    ),
    DolphinLib(
        "pad",
        [
            Object(NonMatching, "dolphin/pad/Padclamp.c"),
            Object(NonMatching, "dolphin/pad/Pad.c"),
        ],
    ),
    DolphinLib(
        "ai",
        [
            Object(NonMatching, "dolphin/ai/ai.c"),
            Object(NonMatching, "dolphin/ar/ar.c"),
        ],
    ),
    DolphinLib(
        "ar",
        [
            Object(NonMatching, "dolphin/ar/arq.c"),
        ],
    ),
    DolphinLib(
        "dsp",
        [
            Object(NonMatching, "dolphin/dsp/dsp.c"),
            Object(NonMatching, "dolphin/dsp/dsp_debug.c"),
            Object(NonMatching, "dolphin/dsp/dsp_task.c"),
        ],
    ),
    DolphinLib(
        "card",
        [
            Object(NonMatching, "dolphin/card/CARDBios.c"),
            Object(NonMatching, "dolphin/card/CARDUnlock.c"),
            Object(NonMatching, "dolphin/card/CARDRdwr.c"),
            Object(NonMatching, "dolphin/card/CARDBlock.c"),
            Object(NonMatching, "dolphin/card/CARDDir.c"),
            Object(NonMatching, "dolphin/card/CARDCheck.c"),
            Object(NonMatching, "dolphin/card/CARDMount.c"),
            Object(NonMatching, "dolphin/card/CARDFormat.c"),
            Object(NonMatching, "dolphin/card/CARDOpen.c"),
            Object(NonMatching, "dolphin/card/CARDCreate.c"),
            Object(NonMatching, "dolphin/card/CARDRead.c"),
            Object(NonMatching, "dolphin/card/CARDWrite.c"),
            Object(NonMatching, "dolphin/card/CARDStat.c"),
            Object(NonMatching, "dolphin/card/CARDNet.c"),
        ],
    ),
    DolphinLib(
        "gx",
        [
            Object(NonMatching, "dolphin/gx/GXInit.c", extra_cflags=["-opt nopeephole"]),
            Object(NonMatching, "dolphin/gx/GXFifo.c"),
            Object(NonMatching, "dolphin/gx/GXAttr.c"),
            Object(NonMatching, "dolphin/gx/GXMisc.c"),
            Object(NonMatching, "dolphin/gx/GXGeometry.c"),
            Object(NonMatching, "dolphin/gx/GXFrameBuf.c"),
            Object(NonMatching, "dolphin/gx/GXLight.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "dolphin/gx/GXTexture.c"),
            Object(NonMatching, "dolphin/gx/GXBump.c"),
            Object(NonMatching, "dolphin/gx/GXTev.c"),
            Object(NonMatching, "dolphin/gx/GXPixel.c"),
            Object(NonMatching, "dolphin/gx/GXStubs.c"),
            Object(NonMatching, "dolphin/gx/GXDisplayList.c"),
            Object(NonMatching, "dolphin/gx/GXTransform.c", extra_cflags=["-fp_contract off"]),
            Object(Matching,    "dolphin/gx/GXPerf.c"),
        ],
    ),
    DolphinLib(
        "gd",
        [
            Object(NonMatching, "dolphin/gd/GDBase.c"),
            Object(NonMatching, "dolphin/gd/GDGeometry.c"),
        ],
    ),
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": "GC/1.3",
        "cflags": cflags_runtime,
        "progress_category": "sdk",
        "host": False,
        "objects": [
            Object(Matching,    "PowerPC_EABI_Support/Runtime/Src/__mem.c"),
            Object(Matching,    "PowerPC_EABI_Support/Runtime/Src/__va_arg.c"),
            Object(Matching,    "PowerPC_EABI_Support/Runtime/Src/global_destructor_chain.c"),
            Object(Matching,    "PowerPC_EABI_Support/Runtime/Src/CPlusLibPPC.cp"),
            Object(NonMatching, "PowerPC_EABI_Support/Runtime/Src/NMWException.cp"),
            Object(Matching,    "PowerPC_EABI_Support/Runtime/Src/ptmf.c"),
            Object(Matching,    "PowerPC_EABI_Support/Runtime/Src/runtime.c"),
            Object(Matching,    "PowerPC_EABI_Support/Runtime/Src/__init_cpp_exceptions.cpp"),
            Object(Matching,    "PowerPC_EABI_Support/Runtime/Src/Gecko_ExceptionPPC.cp"),
            Object(Matching,    "PowerPC_EABI_Support/Runtime/Src/GCN_mem_alloc.c", extra_cflags=["-str reuse,nopool,readonly"]),
        ],
    },
    {
        "lib": "MSL_C",
        "mw_version": "GC/1.3",
        "cflags": cflags_runtime,
        "progress_category": "sdk",
        "host": False,
        "objects": [
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/abort_exit.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/alloc.c", extra_cflags=["-inline noauto"]),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/errno.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/ansi_files.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Src/ansi_fp.c", extra_cflags=["-inline noauto"]),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/arith.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/buffer_io.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/ctype.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/direct_io.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/file_io.c", extra_cflags=["-inline noauto"]),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/FILE_POS.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/mbstring.c", extra_cflags=["-inline noauto"]),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/mem.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/mem_funcs.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/misc_io.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/printf.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/float.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/scanf.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/string.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/strtoul.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Src/uart_console_io.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Src/wchar_io.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_acos.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_asin.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_atan2.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_fmod.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_rem_pio2.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/k_cos.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/k_rem_pio2.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/k_sin.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/k_tan.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_atan.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_copysign.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_cos.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_floor.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_frexp.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_ldexp.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_modf.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_sin.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_tan.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_acos.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_asin.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_atan2.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_fmod.c"),
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/PPC_EABI/Src/math_ppc.c"),
        ],
    },
    {
        "lib": "TRK_MINNOW_DOLPHIN",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_runtime,
        "progress_category": "sdk",
        "host": False,
        "objects": [
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/Portable/mainloop.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/Portable/nubevent.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/Portable/nubinit.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/Portable/msg.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/Portable/msgbuf.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/Portable/serpoll.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/Portable/usr_put.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/Portable/dispatch.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/Portable/msghndlr.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/Portable/support.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/Portable/mutex_TRK.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/Portable/notify.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/ppc/Generic/flush_cache.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/Portable/mem_TRK.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/ppc/Generic/targimpl.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/ppc/Export/targsupp.s"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/ppc/Generic/__exception.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/Os/dolphin/dolphin_trk.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/ppc/Generic/mpc_7xx_603e.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/Portable/main_TRK.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/Os/dolphin/dolphin_trk_glue.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/Os/dolphin/targcont.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/Os/dolphin/target_options.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/MetroTRK/Export/mslsupp.c"),
        ],
    },
    {
        "lib": "amcstubs",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_runtime,
        "progress_category": "sdk",
        "host": False,
        "objects": [
            Object(NonMatching, "amcstubs/AmcExi2Stubs.c"),
        ],
    },
    {
        "lib": "OdemuExi2",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_runtime,
        "progress_category": "sdk",
        "host": False,
        "objects": [
            Object(NonMatching, "OdemuExi2/DebuggerDriver.c"),
        ],
    },
    {
        "lib": "odenotstub",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_runtime,
        "progress_category": "sdk",
        "host": False,
        "objects": [
            Object(NonMatching, "odenotstub/odenotstub.c"),
        ],
    },

    # Begin RELs
    {
        "lib": "REL",
        "mw_version": "GC/1.3.2",
        "cflags": cflags_rel,
        "progress_category": "sdk",
        "host": False,
        "objects": [
            Object(Matching, "REL/executor.c"),
            Object(
                Matching,
                "REL/global_destructor_chain.c",
                source="PowerPC_EABI_Support/Runtime/Src/global_destructor_chain.c",
            ),
        ],
    },
    Rel("f_pc_profile_lst", [Object(Matching, "f_pc/f_pc_profile_lst.cpp")]),
    ActorRel(Matching,    "d_a_agbsw0", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_andsw0"),
    ActorRel(Matching,    "d_a_andsw2"),
    ActorRel(Matching,    "d_a_att", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_bflower", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_bita", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_branch"),
    ActorRel(NonMatching, "d_a_bridge"),
    ActorRel(NonMatching, "d_a_coming2"),
    ActorRel(NonMatching, "d_a_coming3"),
    ActorRel(NonMatching, "d_a_demo_dk"),
    ActorRel(NonMatching, "d_a_demo_kmm"),
    ActorRel(NonMatching, "d_a_door10"),
    ActorRel(Matching,    "d_a_dr"),
    ActorRel(NonMatching, "d_a_dr2"),
    ActorRel(NonMatching, "d_a_ep"),
    ActorRel(Matching,    "d_a_floor"),
    ActorRel(Matching,    "d_a_grass"),
    ActorRel(Matching,    "d_a_hitobj", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_hot_floor", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_ikari"),
    ActorRel(NonMatching, "d_a_jbo"),
    ActorRel(Matching,    "d_a_kaji"),
    ActorRel(NonMatching, "d_a_kanban"),
    ActorRel(NonMatching, "d_a_ki"),
    ActorRel(NonMatching, "d_a_knob00"),
    ActorRel(NonMatching, "d_a_kui"),
    ActorRel(Matching,    "d_a_kytag00"),
    ActorRel(Matching,    "d_a_kytag01"),
    ActorRel(NonMatching, "d_a_kytag02"),
    ActorRel(NonMatching, "d_a_kytag03"),
    ActorRel(Matching,    "d_a_kytag04"),
    ActorRel(Matching,    "d_a_kytag05"),
    ActorRel(Matching,    "d_a_kytag06"),
    ActorRel(Matching,    "d_a_kytag07"),
    ActorRel(Matching,    "d_a_lamp" , extra_cflags=['-sym off']),
    ActorRel(NonMatching, "d_a_lod_bg"),
    ActorRel(Matching,    "d_a_lwood"),
    ActorRel(Matching,    "d_a_magma"),
    ActorRel(NonMatching, "d_a_majuu_flag"),
    ActorRel(NonMatching, "d_a_mdoor"),
    ActorRel(NonMatching, "d_a_msw"),
    ActorRel(Matching,    "d_a_mtoge"),
    ActorRel(Matching,    "d_a_obj_AjavW", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_obj_Ygush00", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_obj_akabe"),
    ActorRel(Matching,    "d_a_obj_barrel", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_obj_barrel2"),
    ActorRel(Matching,    "d_a_obj_bscurtain", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_obj_cafelmp"),
    ActorRel(NonMatching, "d_a_obj_coming"),
    ActorRel(NonMatching, "d_a_obj_demo_barrel"),
    ActorRel(Matching,    "d_a_obj_doguu", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_obj_doguu_demo"),
    ActorRel(Matching,    "d_a_obj_gryw00", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_obj_hfuck1", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_obj_hole", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_obj_ice"),
    ActorRel(NonMatching, "d_a_obj_ikada"),
    ActorRel(Matching,    "d_a_obj_kanat"),
    ActorRel(NonMatching, "d_a_obj_leaves"),
    ActorRel(NonMatching, "d_a_obj_lpalm"),
    ActorRel(Matching,    "d_a_obj_monument"),
    ActorRel(Equivalent,  "d_a_obj_movebox", extra_cflags=['-pragma "nosyminline on"']), # weak func order
    ActorRel(NonMatching, "d_a_obj_mshokki"),
    ActorRel(NonMatching, "d_a_obj_ohatch"),
    ActorRel(NonMatching, "d_a_obj_otble"),
    ActorRel(Matching,    "d_a_obj_pbco"),
    ActorRel(NonMatching, "d_a_obj_pirateship"),
    ActorRel(Matching,    "d_a_obj_quake"),
    ActorRel(NonMatching, "d_a_obj_rcloud"),
    ActorRel(Matching,    "d_a_obj_roten", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_obj_shelf"),
    ActorRel(Matching,    "d_a_obj_shmrgrd", extra_cflags=["-sym off"]),
    ActorRel(Matching,    "d_a_obj_swpush", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_obj_table"),
    ActorRel(NonMatching, "d_a_obj_tenmado"),
    ActorRel(NonMatching, "d_a_obj_tide"),
    ActorRel(Matching,    "d_a_obj_timer"),
    ActorRel(Equivalent,  "d_a_obj_toripost", extra_cflags=['-pragma "nosyminline on"']), # weak func order
    ActorRel(NonMatching, "d_a_obj_tousekiki"),
    ActorRel(NonMatching, "d_a_obj_warpt"),
    ActorRel(Matching,    "d_a_obj_wood", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Equivalent,  "d_a_pirate_flag"), # weak func order
    ActorRel(Equivalent,  "d_a_race_item", extra_cflags=['-pragma "nosyminline on"']), # weak func order
    ActorRel(Equivalent,  "d_a_rd", extra_cflags=['-pragma "nosyminline on"']), # weak func order
    ActorRel(Matching,    "d_a_rectangle"),
    ActorRel(NonMatching, "d_a_salvage"),
    ActorRel(NonMatching, "d_a_sbox"),
    ActorRel(NonMatching, "d_a_sk"),
    ActorRel(NonMatching, "d_a_sk2"),
    ActorRel(Matching,    "d_a_spotbox"),
    ActorRel(NonMatching, "d_a_ssk"),
    ActorRel(NonMatching, "d_a_stone"),
    ActorRel(NonMatching, "d_a_stone2"),
    ActorRel(Matching,    "d_a_swc00"),
    ActorRel(Equivalent,  "d_a_swhit0", extra_cflags=['-pragma "nosyminline on"']), # weak func order
    ActorRel(Matching,    "d_a_swtdoor"),
    ActorRel(NonMatching, "d_a_tag_attention"),
    ActorRel(NonMatching, "d_a_tag_ba1"),
    ActorRel(Matching,    "d_a_tag_event"),
    ActorRel(Matching,    "d_a_tag_evsw", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_tag_ghostship"),
    ActorRel(NonMatching, "d_a_tag_hint"),
    ActorRel(Matching,    "d_a_tag_kb_item"),
    ActorRel(NonMatching, "d_a_tag_kk1"),
    ActorRel(NonMatching, "d_a_tag_light"),
    ActorRel(Matching,    "d_a_tag_msg"),
    ActorRel(NonMatching, "d_a_tag_photo"),
    ActorRel(Matching,    "d_a_tag_waterlevel"),
    ActorRel(Matching,    "d_a_tama", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_tbox", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_tpota", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_tsubo"),
    ActorRel(NonMatching, "d_a_warpdm20"),
    ActorRel(NonMatching, "d_a_warphr"),
    ActorRel(Matching,    "d_a_wbird"),
    ActorRel(NonMatching, "d_a_ykgr"),
    ActorRel(Matching,    "d_a_alldie"),
    ActorRel(Matching,    "d_a_am", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_am2", extra_cflags=["-sym off"]),
    ActorRel(NonMatching, "d_a_amiprop"),
    ActorRel(Matching,    "d_a_arrow_iceeff", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_arrow_lighteff", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_beam"),
    ActorRel(NonMatching, "d_a_boko"),
    ActorRel(NonMatching, "d_a_canon"),
    ActorRel(NonMatching, "d_a_cc"),
    ActorRel(NonMatching, "d_a_dai"),
    ActorRel(Matching,    "d_a_demo_item", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_door12"),
    ActorRel(NonMatching, "d_a_fallrock"),
    ActorRel(NonMatching, "d_a_ff"),
    ActorRel(NonMatching, "d_a_gy_ctrl"),
    ActorRel(NonMatching, "d_a_himo3"),
    ActorRel(NonMatching, "d_a_hmlif"),
    ActorRel(NonMatching, "d_a_hys"),
    ActorRel(NonMatching, "d_a_kamome"),
    ActorRel(NonMatching, "d_a_kantera"),
    ActorRel(NonMatching, "d_a_kn"),
    ActorRel(NonMatching, "d_a_kokiie"),
    ActorRel(NonMatching, "d_a_ks"), # code 100%, possible issue unique to this TU
    ActorRel(NonMatching, "d_a_kt"), # regalloc, weak func order
    ActorRel(NonMatching, "d_a_mflft"),
    ActorRel(NonMatching, "d_a_npc_cb1"),
    ActorRel(NonMatching, "d_a_npc_md"),
    ActorRel(NonMatching, "d_a_npc_so"),
    ActorRel(NonMatching, "d_a_nzg"),
    ActorRel(NonMatching, "d_a_obj_aygr"),
    ActorRel(NonMatching, "d_a_obj_balancelift"),
    ActorRel(Equivalent,  "d_a_obj_barrier", extra_cflags=['-pragma "nosyminline on"']), # weak func order
    ActorRel(NonMatching, "d_a_obj_bemos"),
    ActorRel(NonMatching, "d_a_obj_canon"),
    ActorRel(NonMatching, "d_a_obj_eff"),
    ActorRel(NonMatching, "d_a_obj_magmarock"),
    ActorRel(NonMatching, "d_a_obj_majyuu_door"),
    ActorRel(NonMatching, "d_a_obj_stair"),
    ActorRel(NonMatching, "d_a_obj_swflat"),
    ActorRel(Equivalent,  "d_a_obj_swhammer"), # weak func order
    ActorRel(Matching,    "d_a_obj_swheavy"),
    ActorRel(NonMatching, "d_a_obj_swlight"),
    ActorRel(NonMatching, "d_a_oq"),
    ActorRel(Equivalent,  "d_a_pedestal", extra_cflags=['-pragma "nosyminline on"']), # weak func order
    ActorRel(NonMatching, "d_a_saku"),
    ActorRel(Matching,    "d_a_seatag"),
    ActorRel(Matching,    "d_a_shand", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_ship", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Equivalent,  "d_a_shop_item"), # weak func order
    ActorRel(NonMatching, "d_a_sie_flag"),
    ActorRel(NonMatching, "d_a_sitem"),
    ActorRel(NonMatching, "d_a_ss"),
    ActorRel(NonMatching, "d_a_sss"),
    ActorRel(Matching,    "d_a_syan", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_tag_md_cb"),
    ActorRel(NonMatching, "d_a_tag_mk"),
    ActorRel(Matching,    "d_a_tag_so"),
    ActorRel(Matching,    "d_a_tornado", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_warpf"),
    ActorRel(NonMatching, "d_a_wind_tag"),
    ActorRel(NonMatching, "d_a_acorn_leaf"),
    ActorRel(NonMatching, "d_a_atdoor"),
    ActorRel(Matching,    "d_a_auction", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_bb"),
    ActorRel(NonMatching, "d_a_bdk"),
    ActorRel(NonMatching, "d_a_bdkobj"),
    ActorRel(NonMatching, "d_a_bgn"),
    ActorRel(NonMatching, "d_a_bgn2"),
    ActorRel(NonMatching, "d_a_bgn3"),
    ActorRel(NonMatching, "d_a_bigelf"),
    ActorRel(Matching,    "d_a_bk", extra_cflags=["-sym off"]),
    ActorRel(NonMatching, "d_a_bl"),
    ActorRel(NonMatching, "d_a_bmd"),
    ActorRel(NonMatching, "d_a_bmdfoot"),
    ActorRel(NonMatching, "d_a_bmdhand"),
    ActorRel(NonMatching, "d_a_bo"),
    ActorRel(Matching,    "d_a_boss_item"),
    ActorRel(NonMatching, "d_a_bpw"),
    ActorRel(NonMatching, "d_a_bst"),
    ActorRel(NonMatching, "d_a_btd"),
    ActorRel(NonMatching, "d_a_bwd"),
    ActorRel(Equivalent,  "d_a_bwdg", extra_cflags=['-pragma "nosyminline on"']), # weak func order
    ActorRel(NonMatching, "d_a_bwds"),
    ActorRel(NonMatching, "d_a_daiocta"),
    ActorRel(NonMatching, "d_a_daiocta_eye"),
    ActorRel(Matching,    "d_a_deku_item", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_dk"),
    ActorRel(Matching,    "d_a_dummy"),
    ActorRel(NonMatching, "d_a_fallrock_tag"),
    ActorRel(Matching,    "d_a_fan", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_fganon", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_fgmahou"),
    ActorRel(NonMatching, "d_a_fire"),
    ActorRel(NonMatching, "d_a_fm"),
    ActorRel(NonMatching, "d_a_gm"),
    ActorRel(NonMatching, "d_a_gnd"),
    ActorRel(NonMatching, "d_a_goal_flag"),
    ActorRel(NonMatching, "d_a_gy"),
    ActorRel(NonMatching, "d_a_icelift"),
    ActorRel(NonMatching, "d_a_kb"),
    ActorRel(NonMatching, "d_a_kddoor"),
    ActorRel(NonMatching, "d_a_kita"),
    ActorRel(NonMatching, "d_a_klft"),
    ActorRel(NonMatching, "d_a_kmon"),
    ActorRel(Matching,    "d_a_komore", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_lbridge", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_leaflift", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_lstair"),
    ActorRel(NonMatching, "d_a_machine"),
    ActorRel(NonMatching, "d_a_mant"),
    ActorRel(Matching,    "d_a_mbdoor"),
    ActorRel(NonMatching, "d_a_mgameboard"),
    ActorRel(Matching,    "d_a_mmusic"),
    ActorRel(NonMatching, "d_a_mo2"),
    ActorRel(NonMatching, "d_a_mozo"),
    ActorRel(NonMatching, "d_a_mt"),
    ActorRel(NonMatching, "d_a_npc_ac1"),
    ActorRel(NonMatching, "d_a_npc_ah"),
    ActorRel(NonMatching, "d_a_npc_aj1"),
    ActorRel(NonMatching, "d_a_npc_auction"),
    ActorRel(NonMatching, "d_a_npc_ba1"),
    ActorRel(NonMatching, "d_a_npc_bj1"),
    ActorRel(NonMatching, "d_a_npc_bm1"),
    ActorRel(NonMatching, "d_a_npc_bmcon1"),
    ActorRel(NonMatching, "d_a_npc_bms1"),
    ActorRel(NonMatching, "d_a_npc_bmsw"),
    ActorRel(NonMatching, "d_a_npc_bs1"), # regalloc, weak func order
    ActorRel(NonMatching, "d_a_npc_btsw"),
    ActorRel(Equivalent,  "d_a_npc_btsw2", extra_cflags=['-pragma "nosyminline on"']), # weak func order
    ActorRel(NonMatching, "d_a_npc_co1"),
    ActorRel(NonMatching, "d_a_npc_de1"),
    ActorRel(NonMatching, "d_a_npc_ds1"),
    ActorRel(NonMatching, "d_a_npc_gk1"),
    ActorRel(NonMatching, "d_a_npc_gp1"),
    ActorRel(NonMatching, "d_a_npc_hi1"),
    ActorRel(NonMatching, "d_a_npc_ho"),
    ActorRel(NonMatching, "d_a_npc_hr"),
    ActorRel(NonMatching, "d_a_npc_jb1"),
    ActorRel(NonMatching, "d_a_npc_ji1", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Equivalent,  "d_a_npc_kamome", extra_cflags=['-pragma "nosyminline on"']), # weak func order
    ActorRel(NonMatching, "d_a_npc_kf1"),
    ActorRel(NonMatching, "d_a_npc_kg1"),
    ActorRel(NonMatching, "d_a_npc_kg2"),
    ActorRel(NonMatching, "d_a_npc_kk1"),
    ActorRel(NonMatching, "d_a_npc_km1"),
    ActorRel(NonMatching, "d_a_npc_ko1"),
    ActorRel(NonMatching, "d_a_npc_kp1"),
    ActorRel(NonMatching, "d_a_npc_ls1"),
    ActorRel(NonMatching, "d_a_npc_mk"),
    ActorRel(NonMatching, "d_a_npc_mn"),
    ActorRel(NonMatching, "d_a_npc_mt"),
    ActorRel(Equivalent,  "d_a_npc_nz", extra_cflags=['-pragma "nosyminline on"']), # weak func order
    ActorRel(NonMatching, "d_a_npc_ob1"),
    ActorRel(Equivalent,  "d_a_npc_os", extra_cflags=['-pragma "nosyminline on"']), # weak func order
    ActorRel(NonMatching, "d_a_npc_p1"),
    ActorRel(NonMatching, "d_a_npc_p2"),
    ActorRel(NonMatching, "d_a_npc_people", extra_cflags=['-pragma "nosyminline on"']), # regalloc, weak func order
    ActorRel(NonMatching, "d_a_npc_pf1"),
    ActorRel(NonMatching, "d_a_npc_photo"),
    ActorRel(NonMatching, "d_a_npc_pm1"),
    ActorRel(Equivalent,  "d_a_npc_roten", extra_cflags=['-pragma "nosyminline on"']), # weak func order
    ActorRel(NonMatching, "d_a_npc_rsh1"),
    ActorRel(NonMatching, "d_a_npc_sarace"),
    ActorRel(NonMatching, "d_a_npc_sv"),
    ActorRel(NonMatching, "d_a_npc_tc"),
    ActorRel(NonMatching, "d_a_npc_tt"),
    ActorRel(NonMatching, "d_a_npc_uk"),
    ActorRel(NonMatching, "d_a_npc_ym1"),
    ActorRel(NonMatching, "d_a_npc_yw1"),
    ActorRel(NonMatching, "d_a_npc_zk1"),
    ActorRel(NonMatching, "d_a_npc_zl1"),
    ActorRel(NonMatching, "d_a_nz"),
    ActorRel(NonMatching, "d_a_obj_Itnak"),
    ActorRel(NonMatching, "d_a_obj_Vds"),
    ActorRel(Matching,    "d_a_obj_Vteng", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_obj_YLzou"),
    ActorRel(Matching,    "d_a_obj_Yboil", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_obj_adnno"),
    ActorRel(NonMatching, "d_a_obj_ajav"),
    ActorRel(NonMatching, "d_a_obj_apzl"),
    ActorRel(NonMatching, "d_a_obj_ashut"),
    ActorRel(NonMatching, "d_a_obj_auzu"),
    ActorRel(NonMatching, "d_a_obj_buoyflag"),
    ActorRel(NonMatching, "d_a_obj_buoyrace"),
    ActorRel(NonMatching, "d_a_obj_correct"),
    ActorRel(Matching,    "d_a_obj_dmgroom", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_obj_dragonhead", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_obj_drift"),
    ActorRel(Matching,    "d_a_obj_eayogn"),
    ActorRel(Matching,    "d_a_obj_ebomzo", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_obj_ekskz"),
    ActorRel(Equivalent,  "d_a_obj_eskban", extra_cflags=['-pragma "nosyminline on"']), # weak func order
    ActorRel(Matching,    "d_a_obj_ferris", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_obj_figure", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_obj_firewall"),
    ActorRel(NonMatching, "d_a_obj_flame"),
    ActorRel(NonMatching, "d_a_obj_ftree"),
    ActorRel(Matching,    "d_a_obj_ganonbed", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_obj_gaship", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_obj_gaship2"),
    ActorRel(NonMatching, "d_a_obj_gnnbtltaki"),
    ActorRel(NonMatching, "d_a_obj_gnndemotakie"),
    ActorRel(NonMatching, "d_a_obj_gnndemotakis"),
    ActorRel(Matching,    "d_a_obj_gong"),
    ActorRel(NonMatching, "d_a_obj_gtaki"),
    ActorRel(NonMatching, "d_a_obj_hami2"),
    ActorRel(NonMatching, "d_a_obj_hami3"),
    ActorRel(NonMatching, "d_a_obj_hami4"),
    ActorRel(Equivalent,  "d_a_obj_hat"), # weak func order
    ActorRel(Matching,    "d_a_obj_hbrf1"),
    ActorRel(NonMatching, "d_a_obj_hcbh"),
    ActorRel(Equivalent,  "d_a_obj_hha"), # weak func order
    ActorRel(NonMatching, "d_a_obj_hlift"),
    ActorRel(Matching,    "d_a_obj_homen", extra_cflags=["-sym off"]),
    ActorRel(Matching,    "d_a_obj_homensmoke", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_obj_hsehi1"),
    ActorRel(NonMatching, "d_a_obj_htetu1"),
    ActorRel(Matching,    "d_a_obj_iceisland", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_obj_jump"),
    ActorRel(NonMatching, "d_a_obj_kanoke"),
    ActorRel(Equivalent,  "d_a_obj_ladder", extra_cflags=['-pragma "nosyminline on"']), # weak func order
    ActorRel(NonMatching, "d_a_obj_light"),
    ActorRel(NonMatching, "d_a_obj_mkie"),
    ActorRel(NonMatching, "d_a_obj_mkiek"),
    ActorRel(Matching,    "d_a_obj_mknjd", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_obj_mmrr"),
    ActorRel(NonMatching, "d_a_obj_msdan"),
    ActorRel(NonMatching, "d_a_obj_msdan2"),
    ActorRel(NonMatching, "d_a_obj_msdan_sub"),
    ActorRel(NonMatching, "d_a_obj_msdan_sub2"),
    ActorRel(Equivalent,  "d_a_obj_mtest", extra_cflags=['-pragma "nosyminline on"']), # weak func order
    ActorRel(NonMatching, "d_a_obj_nest"),
    ActorRel(Matching,    "d_a_obj_ojtree"),
    ActorRel(NonMatching, "d_a_obj_ospbox"),
    ActorRel(Matching,    "d_a_obj_paper", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_obj_pbka"),
    ActorRel(NonMatching, "d_a_obj_pfall"),
    ActorRel(NonMatching, "d_a_obj_plant"),
    ActorRel(NonMatching, "d_a_obj_rflw"),
    ActorRel(Matching,    "d_a_obj_rforce"),
    ActorRel(Matching,    "d_a_obj_smplbg", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_obj_tapestry"),
    ActorRel(NonMatching, "d_a_obj_tntrap"),
    ActorRel(Matching,    "d_a_obj_tower"),
    ActorRel(NonMatching, "d_a_obj_trap"),
    ActorRel(NonMatching, "d_a_obj_tribox"),
    ActorRel(NonMatching, "d_a_obj_try"),
    ActorRel(Matching,    "d_a_obj_usovmc"),
    ActorRel(Matching,    "d_a_obj_vfan", extra_cflags=[ '-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_obj_vgnfd", extra_cflags=[ '-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_obj_vmc", extra_cflags=["-sym off"]),
    ActorRel(Matching,    "d_a_obj_vmsdz"),
    ActorRel(Matching,    "d_a_obj_vmsms"),
    ActorRel(NonMatching, "d_a_obj_volcano"),
    ActorRel(NonMatching, "d_a_obj_vtil"),
    ActorRel(NonMatching, "d_a_obj_vyasi"),
    ActorRel(Matching,    "d_a_obj_xfuta"),
    ActorRel(Matching,    "d_a_obj_zouK", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_oship"),
    ActorRel(NonMatching, "d_a_ph"),
    ActorRel(NonMatching, "d_a_pt"),
    ActorRel(NonMatching, "d_a_pw"),
    ActorRel(NonMatching, "d_a_pz"),
    ActorRel(Equivalent,  "d_a_sail", extra_cflags=['-pragma "nosyminline on"']), # weak func order
    ActorRel(NonMatching, "d_a_salvage_tbox"),
    ActorRel(Matching,    "d_a_scene_change"),
    ActorRel(Matching,    "d_a_shutter", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_shutter2"),
    ActorRel(NonMatching, "d_a_st"),
    ActorRel(Matching,    "d_a_steam_tag", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_swattack", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_switem", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_swpropeller"),
    ActorRel(Matching,    "d_a_swtact"),
    ActorRel(Matching,    "d_a_tag_etc"),
    ActorRel(Matching,    "d_a_tag_island"),
    ActorRel(NonMatching, "d_a_tag_kf1"),
    ActorRel(Matching,    "d_a_tag_ret", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_tag_volcano"),
    ActorRel(Matching,    "d_a_title", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_tn"),
    ActorRel(Matching,    "d_a_toge", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_tori_flag", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_wall", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(Matching,    "d_a_warpfout"),
    ActorRel(NonMatching, "d_a_warpgn"),
    ActorRel(NonMatching, "d_a_warpls"),
    ActorRel(NonMatching, "d_a_warpmj"),
    ActorRel(NonMatching, "d_a_waterfall"),
    ActorRel(NonMatching, "d_a_windmill"),
    ActorRel(NonMatching, "d_a_wz"),
    ActorRel(Matching,    "d_a_ygcwp", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_yougan"),
    ActorRel(Matching,    "d_a_ghostship", extra_cflags=['-pragma "nosyminline on"']),
    ActorRel(NonMatching, "d_a_movie_player", extra_cflags=["-O3,p"]),
]


# Define our custom asset processing scripts
config.custom_build_rules = [
    {
        "name": "convert_matDL",
        "command": "$python tools/converters/matDL_dis.py $in $out --symbol $symbol --scope $scope",
        "description": "CONVERT $symbol",
    },
]
config.custom_build_steps = {}

# Grab the specific GameID so we can format our strings properly
version = VERSIONS[version_num]
out_dir = config.build_dir / version


# This generates the build steps needed for preprocessing
def emit_build_rule(asset):
    steps = config.custom_build_steps.setdefault("pre-compile", [])
    custom_data = asset.get("custom_data") or {}

    match asset.get("custom_type"):
        case None:
            return

        case "matDL":
            steps.append(
                {
                    "rule": "convert_matDL",
                    "inputs": out_dir / "bin" / asset["binary"],
                    "outputs": out_dir / "include" / asset["header"],
                    "variables": {
                        "symbol": asset.get("rename") or asset["symbol"],
                        "scope": custom_data.get("scope", "local")
                    },
                    "implicit": Path("tools/converters/matDL_dis.py"),
                }
            )

        case _:
            print("Unknown asset type: " + asset["custom_type"])


# Parse the config and create the build rules for all our assets
config_path = out_dir / "config.json"
if config_path.exists():
    config_data = json.load(open(config_path))
    for asset in config_data.get("extract", []):
        emit_build_rule(asset)
    for module in config_data.get("modules", []):
        for asset in module.get("extract", []):
            emit_build_rule(asset)


# Optional callback to adjust link order. This can be used to add, remove, or reorder objects.
# This is called once per module, with the module ID and the current link order.
#
# For example, this adds "dummy.c" to the end of the DOL link order if configured with --non-matching.
# "dummy.c" *must* be configured as a Matching (or Equivalent) object in order to be linked.
def link_order_callback(module_id: int, objects: List[str]) -> List[str]:
    # Don't modify the link order for matching builds
    if not config.non_matching:
        return objects
    if module_id == 0:  # DOL
        return objects + ["dummy.c"]
    return objects

# Uncomment to enable the link order callback.
# config.link_order_callback = link_order_callback


# Optional extra categories for progress tracking
config.progress_categories = [
    ProgressCategory("game", "TWW Game Code"),
    ProgressCategory("core", "Core Engine"),
    ProgressCategory("sdk", "SDK"),
    ProgressCategory("third_party", "Third Party"),
]
config.progress_each_module = args.verbose

# Disable missing return type warnings for incomplete objects
for lib in config.libs:
    for obj in lib["objects"]:
        if not obj.completed:
            obj.options["extra_clang_flags"].append("-Wno-return-type")

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress and write progress.json
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
