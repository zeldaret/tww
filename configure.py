#!/usr/bin/env python3
import os
import io
import platform
import sys
import argparse
import json

from pathlib import Path
from tools import ninja_syntax

if sys.platform == "cygwin":
    sys.exit(
        f"Cygwin/MSYS2 is not supported."
        f"\nPlease use native Windows Python instead."
        f"\n(Current path: {sys.executable})"
    )

VERSIONS = [
    "GZLJ01",  # 0
    "GZLE01",  # 1
    "GZLP01",  # 2
]

if len(VERSIONS) > 1:
    versions_str = ", ".join(VERSIONS[:-1]) + f" or {VERSIONS[-1]}"
else:
    versions_str = VERSIONS[0]

parser = argparse.ArgumentParser()
parser.add_argument(
    "--version",
    dest="version",
    default="GZLE01",
    help=f"version to build ({versions_str})",
)
parser.add_argument(
    "--build-dir",
    dest="build_dir",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--build-dtk",
    dest="build_dtk",
    type=Path,
    help="path to decomp-toolkit source",
)
parser.add_argument(
    "--compilers",
    dest="compilers",
    type=Path,
    help="path to compilers (default: tools/mwcc_compiler)",
)
parser.add_argument(
    "--map",
    dest="map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    dest="debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if os.name != "nt" and not "_NT-" in os.uname().sysname:
    parser.add_argument(
        "--wrapper",
        dest="wrapper",
        type=Path,
        help="path to wine (or wibo)",
    )
parser.add_argument(
    "--sjiswrap",
    dest="sjiswrap",
    type=Path,
    help="path to sjiswrap",
)
args = parser.parse_args()

version = args.version.upper()
if version not in VERSIONS:
    sys.exit(f"Invalid version '{version}', expected {versions_str}")
version_num = VERSIONS.index(version)

CFLAGS_BASE = [
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
    "-multibyte",
    "-i include",
    f"-DVERSION={version_num}",
]
if args.debug:
    CFLAGS_BASE.extend(["-sym on", "-DDEBUG=1"])
else:
    CFLAGS_BASE.append("-DNDEBUG=1")

CFLAGS_RUNTIME = [
    *CFLAGS_BASE,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-inline deferred,auto",
]

CFLAGS_FRAMEWORK = [
    *CFLAGS_BASE,
    "-use_lmw_stmw off",
    "-str reuse,pool,readonly",
    "-inline noauto",
    "-O3,s",
    "-schedule off",
    "-sym on",
]

CFLAGS_REL = [
    *CFLAGS_FRAMEWORK,
    "-sdata 0",
    "-sdata2 0",
]

LINKER_VERSION = "GC/1.3.2"


class Object:
    def __init__(self, obj_path, completed, options):
        self.obj_path = obj_path
        self.completed = completed
        self.options = options


def Matching(obj_path, **kwargs):
    return Object(obj_path, True, kwargs)


def NonMatching(obj_path, **kwargs):
    return Object(obj_path, False, kwargs)


LIBS = [
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": "GC/1.3.2",
        "cflags": CFLAGS_RUNTIME,
        "host": False,
        "objects": [
            Matching("Runtime/__init_cpp_exceptions.cpp"),
            Matching("Runtime/Gecko_ExceptionPPC.cp"),
            Matching("Runtime/global_destructor_chain.c"),
        ],
    },
    {
        "lib": "REL",
        "mw_version": "GC/1.3.2",
        "cflags": CFLAGS_REL,
        "host": False,
        "objects": [
            Matching("REL/executor.c"),
            Matching(
                "REL/global_destructor_chain.c",
                source="Runtime/global_destructor_chain.c",
            ),
        ],
    },
    {
        "lib": "JSystem",
        "mw_version": "GC/1.3.2",
        "cflags": CFLAGS_FRAMEWORK,
        "host": True,
        "objects": [
            Matching   ("JSystem/JKernel/JKRFile.cpp"),
            Matching   ("JSystem/JSupport/JSUList.cpp"),
            NonMatching("JSystem/JSupport/JSUInputStream.cpp"),
            Matching   ("JSystem/JSupport/JSUMemoryStream.cpp"),
            Matching   ("JSystem/JSupport/JSUFileStream.cpp"),
            Matching   ("JSystem/JUtility/JUTNameTab.cpp"),
            Matching   ("JSystem/JUtility/JUTPalette.cpp"),
            NonMatching("JSystem/JParticle/JPATexture.cpp"),
        ],
    },
    {
        "lib": "SSystem",
        "mw_version": "GC/1.3.2",
        "cflags": CFLAGS_FRAMEWORK,
        "host": True,
        "objects": [
            Matching   ("SSystem/SStandard/s_basic.cpp"),
            Matching   ("SSystem/SComponent/c_malloc.cpp"),
            Matching   ("SSystem/SComponent/c_API.cpp"),
            Matching   ("SSystem/SComponent/c_API_graphic.cpp"),
            Matching   ("SSystem/SComponent/c_counter.cpp"),
            Matching   ("SSystem/SComponent/c_list.cpp"),
            Matching   ("SSystem/SComponent/c_list_iter.cpp"),
            Matching   ("SSystem/SComponent/c_node.cpp"),
            Matching   ("SSystem/SComponent/c_node_iter.cpp"),
            Matching   ("SSystem/SComponent/c_tree.cpp"),
            Matching   ("SSystem/SComponent/c_tree_iter.cpp"),
            NonMatching("SSystem/SComponent/c_phase.cpp"),
            Matching   ("SSystem/SComponent/c_request.cpp"),
            Matching   ("SSystem/SComponent/c_tag.cpp"),
            Matching   ("SSystem/SComponent/c_tag_iter.cpp"),
            NonMatching("SSystem/SComponent/c_xyz.cpp"),
            Matching   ("SSystem/SComponent/c_sxyz.cpp"),
            NonMatching("SSystem/SComponent/c_math.cpp"),
            NonMatching("SSystem/SComponent/c_bg_s.cpp"),
            Matching   ("SSystem/SComponent/c_bg_s_chk.cpp"),
            NonMatching("SSystem/SComponent/c_bg_s_gnd_chk.cpp"),
            NonMatching("SSystem/SComponent/c_bg_s_lin_chk.cpp"),
            NonMatching("SSystem/SComponent/c_bg_w.cpp"),
            NonMatching("SSystem/SComponent/c_m2d.cpp"),
            NonMatching("SSystem/SComponent/c_m2d_g_box.cpp"),
            Matching   ("SSystem/SComponent/c_m3d_g_aab.cpp"),
            NonMatching("SSystem/SComponent/c_m3d_g_cyl.cpp"),
            Matching   ("SSystem/SComponent/c_m3d_g_pla.cpp"),
            NonMatching("SSystem/SComponent/c_m3d_g_sph.cpp"),
            Matching   ("SSystem/SComponent/c_m3d_g_tri.cpp"),
            NonMatching("SSystem/SComponent/c_lib.cpp"),
            NonMatching("SSystem/SComponent/c_angle.cpp"),
            NonMatching("SSystem/SComponent/c_data_tbl.cpp"),
        ],
    },
    {
        "lib": "framework",
        "mw_version": "GC/1.3.2",
        "cflags": CFLAGS_FRAMEWORK,
        "host": True,
        "objects": [
            NonMatching("f_ap/f_ap_game.cpp"),
            NonMatching("f_op/f_op_actor.cpp"),
            Matching   ("f_op/f_op_actor_iter.cpp"),
            Matching   ("f_op/f_op_actor_tag.cpp"),
            NonMatching("f_op/f_op_actor_mng.cpp"),
            NonMatching("f_op/f_op_camera.cpp"),
            Matching   ("f_op/f_op_camera_mng.cpp"),
            Matching   ("f_op/f_op_overlap.cpp"),
            Matching   ("f_op/f_op_overlap_mng.cpp"),
            Matching   ("f_op/f_op_overlap_req.cpp"),
            Matching   ("f_op/f_op_scene.cpp"),
            Matching   ("f_op/f_op_scene_iter.cpp"),
            Matching   ("f_op/f_op_scene_mng.cpp"),
            Matching   ("f_op/f_op_scene_req.cpp"),
            Matching   ("f_op/f_op_scene_tag.cpp"),
            Matching   ("f_op/f_op_view.cpp"),
            Matching   ("f_op/f_op_kankyo.cpp"),
            Matching   ("f_op/f_op_msg.cpp"),
            NonMatching("f_op/f_op_kankyo_mng.cpp"),
            NonMatching("f_op/f_op_msg_mng.cpp"),
            Matching   ("f_op/f_op_draw_iter.cpp"),
            Matching   ("f_op/f_op_draw_tag.cpp"),
            Matching   ("f_op/f_op_scene_pause.cpp"),
            Matching   ("f_pc/f_pc_base.cpp"),
            Matching   ("f_pc/f_pc_create_iter.cpp"),
            Matching   ("f_pc/f_pc_create_req.cpp"),
            Matching   ("f_pc/f_pc_create_tag.cpp"),
            Matching   ("f_pc/f_pc_creator.cpp"),
            Matching   ("f_pc/f_pc_delete_tag.cpp"),
            Matching   ("f_pc/f_pc_deletor.cpp"),
            Matching   ("f_pc/f_pc_draw_priority.cpp"),
            Matching   ("f_pc/f_pc_executor.cpp"),
            Matching   ("f_pc/f_pc_layer.cpp"),
            Matching   ("f_pc/f_pc_leaf.cpp"),
            Matching   ("f_pc/f_pc_layer_iter.cpp"),
            Matching   ("f_pc/f_pc_layer_tag.cpp"),
            Matching   ("f_pc/f_pc_line.cpp"),
            Matching   ("f_pc/f_pc_load.cpp"),
            NonMatching("f_pc/f_pc_manager.cpp"),
            Matching   ("f_pc/f_pc_method.cpp"),
            Matching   ("f_pc/f_pc_node.cpp"),
            Matching   ("f_pc/f_pc_node_req.cpp"),
            Matching   ("f_pc/f_pc_priority.cpp"),
            Matching   ("f_pc/f_pc_profile.cpp"),
            Matching   ("f_pc/f_pc_searcher.cpp"),
            Matching   ("f_pc/f_pc_line_tag.cpp"),
            Matching   ("f_pc/f_pc_line_iter.cpp"),
            Matching   ("f_pc/f_pc_method_iter.cpp"),
            Matching   ("f_pc/f_pc_method_tag.cpp"),
            Matching   ("f_pc/f_pc_pause.cpp"),
            Matching   ("f_pc/f_pc_draw.cpp"),
            Matching   ("f_pc/f_pc_fstcreate_req.cpp"),
            Matching   ("f_pc/f_pc_stdcreate_req.cpp"),

            # machine
            NonMatching("m_Do/m_Do_controller_pad.cpp"),

            # dolzel
            Matching   ("d/d_com_lib_game.cpp"),
            Matching   ("d/d_particle_name.cpp"),
            NonMatching("d/d_s_title.cpp"),
            NonMatching("d/d_com_inf_game.cpp"),
            NonMatching("d/d_save.cpp"),
            NonMatching("d/d_save_init.cpp"),

            # ?
            NonMatching("DynamicLink.cpp"),
        ],
    },
    {
        "lib": "f_pc_profile_lst",
        "mw_version": "GC/1.3.2",
        "cflags": CFLAGS_REL,
        "host": True,
        "objects": [
            Matching("f_pc/f_pc_profile_lst.cpp"),
        ],
    },
]

# Tool versions
COMPILERS_TAG = "1"
DTK_TAG = "v0.4.1"
SJISWRAP_TAG = "v1.1.0"
WIBO_TAG = "0.5.0"

# On Windows, we need this to use && in commands
chain = "cmd /c " if os.name == "nt" else ""

# Begin generating build.ninja
out = io.StringIO()
n = ninja_syntax.Writer(out)

n.variable("ninja_required_version", "1.3")
n.newline()

n.comment("The arguments passed to configure.py, for rerunning it.")
n.variable("configure_args", sys.argv[1:])
n.variable("python", f'"{sys.executable}"')
n.newline()

###
# Variables
###
n.comment("Variables")
version = args.version
version_num = VERSIONS.index(args.version)
build_path = args.build_dir / version
config_path = Path("config") / version / "config.yml"
tools_path = Path("tools")

ldflags = f"-fp hardware -nodefaults"
if args.map:
    ldflags += f" -mapunused"
if args.debug:
    ldflags += " -g"
n.variable("ldflags", ldflags)
n.variable("mw_version", LINKER_VERSION)
if sys.platform == "win32":
    exe = ".exe"
    wrapper = None
else:
    exe = ""
    wrapper = args.wrapper or "wine"
n.newline()


# Replace forward slashes with backslashes on Windows
def os_str(value):
    return str(value).replace("/", os.sep)


# Stringify paths for ninja_syntax
def path(value):
    if value is None:
        return None
    elif isinstance(value, list):
        return list(map(os_str, filter(lambda x: x is not None, value)))
    else:
        return [os_str(value)]


###
# Tooling
###
n.comment("Tooling")

build_tools_path = args.build_dir / "tools"
download_tool = tools_path / "download_tool.py"
n.rule(
    name="download_tool",
    command=f"$python {download_tool} $tool $out --tag $tag",
    description="TOOL $out",
)

if args.build_dtk:
    dtk = build_tools_path / "release" / f"dtk{exe}"
    n.rule(
        name="cargo",
        command="cargo build --release --manifest-path $in --bin $bin --target-dir $target",
        description="CARGO $bin",
        depfile=path(Path("$target") / "release" / "$bin.d"),
        deps="gcc",
    )
    n.build(
        outputs=path(dtk),
        rule="cargo",
        inputs=path(args.build_dtk / "Cargo.toml"),
        variables={
            "bin": "dtk",
            "target": build_tools_path,
        },
    )
else:
    dtk = build_tools_path / f"dtk{exe}"
    n.build(
        outputs=path(dtk),
        rule="download_tool",
        implicit=path(download_tool),
        variables={
            "tool": "dtk",
            "tag": DTK_TAG,
        },
    )

if args.sjiswrap:
    sjiswrap = args.sjiswrap
else:
    sjiswrap = build_tools_path / "sjiswrap.exe"
    n.build(
        outputs=path(sjiswrap),
        rule="download_tool",
        implicit=path(download_tool),
        variables={
            "tool": "sjiswrap",
            "tag": SJISWRAP_TAG,
        },
    )

# Only add an implicit dependency on wibo if we download it
wrapper_implicit = None
if (
    sys.platform == "linux"
    and platform.machine() in ("i386", "x86_64")
    and args.wrapper is None
):
    wrapper = build_tools_path / "wibo"
    wrapper_implicit = wrapper
    n.build(
        outputs=path(wrapper),
        rule="download_tool",
        implicit=path(download_tool),
        variables={
            "tool": "wibo",
            "tag": WIBO_TAG,
        },
    )

compilers_implicit = None
if args.compilers:
    compilers = args.compilers
else:
    compilers = tools_path / "mwcc_compiler"
    compilers_implicit = compilers
    n.build(
        outputs=path(compilers),
        rule="download_tool",
        implicit=path(download_tool),
        variables={
            "tool": "compilers",
            "tag": COMPILERS_TAG,
        },
    )

n.newline()

###
# Rules
###
compiler_path = compilers / "$mw_version"
mwcc = compiler_path / "mwcceppc.exe"
mwcc_implicit = [compilers_implicit or mwcc, wrapper_implicit, sjiswrap]
mwld = compiler_path / "mwldeppc.exe"
mwld_implicit = [compilers_implicit or mwld, wrapper_implicit]

wrapper_cmd = f"{wrapper} " if wrapper else ""
mwcc_cmd = f"{wrapper_cmd}{sjiswrap} {mwcc} $cflags -MMD -c $in -o $basedir"
mwld_cmd = f"{wrapper_cmd}{mwld} $ldflags -o $out @$out.rsp"

if os.name != "nt":
    transform_dep = tools_path / "transform_dep.py"
    mwcc_cmd += f" && $python {transform_dep} $basefile.d $basefile.d"
    mwcc_implicit.append(transform_dep)

n.comment("Link ELF file")
n.rule(
    name="link",
    command=mwld_cmd,
    description="LINK $out",
    rspfile="$out.rsp",
    rspfile_content="$in_newline",
)
n.newline()

n.comment("Generate DOL")
n.rule(
    name="elf2dol",
    command=f"{dtk} elf2dol $in $out",
    description="DOL $out",
)
n.newline()

n.comment("Generate RELs")
makerel_rsp = build_path / "makerel.rsp"
n.rule(
    name="makerel",
    command=f"{dtk} rel make -w -c $config @{makerel_rsp}",
    description="REL",
    rspfile=path(makerel_rsp),
    rspfile_content="$in_newline",
)
n.newline()

n.comment("MWCC build")
n.rule(
    name="mwcc",
    command=mwcc_cmd,
    description="MWCC $out",
    depfile="$basefile.d",
    deps="gcc",
)
n.newline()

n.comment("Host build")
n.variable("host_cflags", "-I include -Wno-trigraphs")
n.variable(
    "host_cppflags",
    "-std=c++98 -I include -fno-exceptions -fno-rtti -D_CRT_SECURE_NO_WARNINGS -Wno-trigraphs -Wno-c++11-extensions",
)
n.rule(
    name="host_cc",
    command="clang $host_cflags -c -o $out $in",
    description="CC $out",
)
n.rule(
    name="host_cpp",
    command="clang++ $host_cppflags -c -o $out $in",
    description="CXX $out",
)
n.newline()

###
# Rules for source files
###
n.comment("Source files")
build_src_path = build_path / "src"
build_host_path = build_path / "host"
build_config_path = build_path / "config.json"

objdiff_config = {
    "min_version": "0.4.3",
    "custom_make": "ninja",
    "build_target": False,
    "watch_patterns": [
        "*.c",
        "*.cp",
        "*.cpp",
        "*.h",
        "*.hpp",
        "*.py",
        "*.yml",
        "*.txt",
        "*.json",
    ],
    "units": [],
}


def locate_unit(unit):
    for lib in LIBS:
        for obj in lib["objects"]:
            if obj.obj_path == unit:
                return [lib, obj]
    return None


def map_path(path):
    return path.parent / (path.name + ".MAP")


class LinkStep:
    def __init__(self, config):
        self.name = config["name"]
        self.module_id = config["module_id"]
        self.ldscript = config["ldscript"]
        self.inputs = []

    def add(self, obj):
        self.inputs.append(obj)

    def output(self):
        if self.module_id == 0:
            return build_path / f"{self.name}.dol"
        else:
            return build_path / self.name / f"{self.name}.rel"

    def partial_output(self):
        if self.module_id == 0:
            return build_path / f"{self.name}.elf"
        else:
            return build_path / self.name / f"{self.name}.plf"

    def write(self, n):
        n.comment(f"Link {self.name}")
        if self.module_id == 0:
            elf_path = build_path / f"{self.name}.elf"
            dol_path = build_path / f"{self.name}.dol"
            elf_ldflags = f"$ldflags -lcf {self.ldscript}"
            if args.map:
                elf_map = map_path(elf_path)
                elf_ldflags += f" -map {elf_map}"
            else:
                elf_map = None
            n.build(
                outputs=path(elf_path),
                rule="link",
                inputs=path(self.inputs),
                implicit=path([self.ldscript, *mwld_implicit]),
                implicit_outputs=path(elf_map),
                variables={"ldflags": elf_ldflags},
            )
            n.build(
                outputs=path(dol_path),
                rule="elf2dol",
                inputs=path(elf_path),
                implicit=path(dtk),
            )
        else:
            preplf_path = build_path / self.name / f"{self.name}.preplf"
            plf_path = build_path / self.name / f"{self.name}.plf"
            preplf_ldflags = f"$ldflags -sdata 0 -sdata2 0 -m _prolog -r"
            plf_ldflags = f"$ldflags -sdata 0 -sdata2 0 -m _prolog -r1 -strip_partial -lcf {self.ldscript}"
            if args.map:
                preplf_map = map_path(preplf_path)
                preplf_ldflags += f" -map {preplf_map}"
                plf_map = map_path(plf_path)
                plf_ldflags += f" -map {plf_map}"
            else:
                preplf_map = None
                plf_map = None
            n.build(
                outputs=path(preplf_path),
                rule="link",
                inputs=path(self.inputs),
                implicit=path(mwld_implicit),
                implicit_outputs=path(preplf_map),
                variables={"ldflags": preplf_ldflags},
            )
            n.build(
                outputs=path(plf_path),
                rule="link",
                inputs=path(self.inputs),
                implicit=path([self.ldscript, preplf_path, *mwld_implicit]),
                implicit_outputs=path(plf_map),
                variables={"ldflags": plf_ldflags},
            )

        n.newline()


has_units = False
if build_config_path.is_file():
    has_units = True

    src_path = Path("src")
    link_steps = []
    used_compiler_versions = set()
    source_inputs = []
    host_source_inputs = []
    source_added = set()

    def add_unit(obj, step):
        obj_path, unit = obj["object"], obj["name"]
        result = locate_unit(unit)
        if not result:
            step.add(obj_path)
            base_object = Path(unit).with_suffix("")
            objdiff_config["units"].append(
                {
                    "name": str(f"{step.name}/{base_object}").replace(os.sep, "/"),
                    "target_path": str(obj_path).replace(os.sep, "/"),
                    "reverse_fn_order": False,
                }
            )
            return

        lib, data = result
        lib_name = lib["lib"]

        options = {
            "add_to_all": True,
            "mw_version": None,
            "cflags": None,
            "source": unit,
        }

        completed = data.completed
        if data.options is not None:
            options.update(data.options)

        unit_src_path = src_path / options["source"]
        if not unit_src_path.exists():
            step.add(obj_path)
            return

        mw_version = options["mw_version"] or lib["mw_version"]
        cflags = options["cflags"] or lib["cflags"]
        if type(cflags) is list:
            cflags_str = " ".join(cflags)
        else:
            cflags_str = str(cflags)
        used_compiler_versions.add(mw_version)

        base_object = Path(data.obj_path).with_suffix("")
        src_obj_path = build_src_path / f"{base_object}.o"
        src_base_path = build_src_path / base_object

        if src_obj_path not in source_added:
            source_added.add(src_obj_path)

            n.comment(f"{unit}: {lib_name} (linked {completed})")
            n.build(
                outputs=path(src_obj_path),
                rule="mwcc",
                inputs=path(unit_src_path),
                variables={
                    "mw_version": path(Path(mw_version)),
                    "cflags": cflags_str,
                    "basedir": os.path.dirname(src_base_path),
                    "basefile": path(src_base_path),
                },
                implicit=path(mwcc_implicit),
            )

            if lib["host"]:
                host_obj_path = build_host_path / f"{base_object}.o"
                host_base_path = build_host_path / base_object
                n.build(
                    outputs=path(host_obj_path),
                    rule="host_cc" if unit_src_path.suffix == ".c" else "host_cpp",
                    inputs=path(unit_src_path),
                    variables={
                        "basedir": os.path.dirname(host_base_path),
                        "basefile": path(host_base_path),
                    },
                )
                if options["add_to_all"]:
                    host_source_inputs.append(host_obj_path)

            if options["add_to_all"]:
                source_inputs.append(src_obj_path)

        reverse_fn_order = False
        if type(cflags) is list:
            for flag in cflags:
                if not flag.startswith("-inline "):
                    continue
                for value in flag.split(" ")[1].split(","):
                    if value == "deferred":
                        reverse_fn_order = True
                    elif value == "nodeferred":
                        reverse_fn_order = False
        objdiff_config["units"].append(
            {
                "name": str(f"{step.name}/{base_object}").replace(os.sep, "/"),
                "target_path": str(obj_path).replace(os.sep, "/"),
                "base_path": str(src_obj_path).replace(os.sep, "/"),
                "reverse_fn_order": reverse_fn_order,
                "complete": completed,
            }
        )

        if completed:
            obj_path = src_obj_path
        step.add(obj_path)

    with open(build_config_path) as r:
        config = json.load(r)
        link_step = LinkStep(config)
        for unit in config["units"]:
            add_unit(unit, link_step)
        link_steps.append(link_step)

        for module in config["modules"]:
            module_link_step = LinkStep(module)
            for unit in module["units"]:
                add_unit(unit, module_link_step)
            link_steps.append(module_link_step)
    n.newline()

    # Check if all compiler versions exist
    for mw_version in used_compiler_versions:
        mw_path = compilers / mw_version / "mwcceppc.exe"
        if args.compilers and not os.path.exists(mw_path):
            sys.exit(f"Compiler {mw_path} does not exist")

    # Check if linker exists
    mw_path = compilers / LINKER_VERSION / "mwldeppc.exe"
    if args.compilers and not os.path.exists(mw_path):
        sys.exit(f"Linker {mw_path} does not exist")

    ###
    # Link
    ###
    for step in link_steps:
        step.write(n)
    n.newline()

    ###
    # Generate RELs
    ###
    n.comment("Generate RELs")
    n.build(
        outputs=path(
            list(
                map(
                    lambda step: step.output(),
                    filter(lambda step: step.module_id != 0, link_steps),
                )
            )
        ),
        rule="makerel",
        inputs=path(list(map(lambda step: step.partial_output(), link_steps))),
        implicit=path([dtk, config_path]),
        variables={"config": path(config_path)},
    )
    n.newline()

    ###
    # Helper rule for building all source files
    ###
    n.comment("Build all source files")
    n.build(
        outputs="all_source",
        rule="phony",
        inputs=path(source_inputs),
    )
    n.newline()

    ###
    # Helper rule for building all source files, with a host compiler
    ###
    n.comment("Build all source files with a host compiler")
    n.build(
        outputs="all_source_host",
        rule="phony",
        inputs=path(host_source_inputs),
    )
    n.newline()

    ###
    # Check hash
    ###
    n.comment("Check hash")
    ok_path = build_path / "ok"
    n.rule(
        name="check",
        command=f"{dtk} shasum -q -c $in -o $out",
        description="CHECK $in",
    )
    n.build(
        outputs=path(ok_path),
        rule="check",
        inputs=path(Path("orig") / f"{version}.sha1"),
        implicit=path([dtk, *map(lambda step: step.output(), link_steps)]),
    )
    n.newline()

    ###
    # Helper tools
    ###
    # TODO: make these rules work for RELs too
    dol_link_step = link_steps[0]
    dol_elf_path = dol_link_step.partial_output()
    dol_map_path = map_path(dol_elf_path)
    n.comment("Check for mismatching symbols")
    n.rule(
        name="dol_diff",
        command=f"{dtk} -L error dol diff $in",
        description=f"DIFF {dol_elf_path}",
    )
    n.build(
        inputs=path([config_path, dol_elf_path, dol_map_path]),
        outputs="dol_diff",
        rule="dol_diff",
    )
    n.build(
        outputs="diff",
        rule="phony",
        inputs="dol_diff",
    )
    n.newline()

    n.comment("Apply symbols from linked ELF")
    n.rule(
        name="dol_apply",
        command=f"{dtk} dol apply $in",
        description=f"APPLY {dol_elf_path}",
    )
    n.build(
        inputs=path([config_path, dol_elf_path, dol_map_path]),
        outputs="dol_apply",
        rule="dol_apply",
        implicit=path([ok_path]),
    )
    n.build(
        outputs="apply",
        rule="phony",
        inputs="dol_apply",
    )

###
# DOL split
###
n.comment("Generate objects from original DOL")
n.rule(
    name="split",
    command=f"{dtk} dol split $in $out_dir",
    description="SPLIT",
    depfile="$out_dir/dep",
    deps="gcc",
)
n.build(
    inputs=path(config_path),
    outputs=path(build_config_path),
    rule="split",
    implicit=path(dtk),
    variables={"out_dir": path(build_path)},
)
n.newline()

###
# Regenerate on change
###
n.comment("Reconfigure on change")
script = os.path.relpath(__file__)
n.rule(
    name="configure",
    command=f"$python {script} $configure_args",
    generator=True,
    description=f"RUN {script}",
)
n.build(
    outputs="build.ninja",
    rule="configure",
    implicit=path([script, tools_path / "ninja_syntax.py", build_config_path]),
)
n.newline()

###
# Default rule
###
n.comment("Default rule")
if has_units:
    n.default(path(ok_path))
else:
    n.default(path(build_config_path))

###
# Write build.ninja
###
with open("build.ninja", "w") as f:
    f.write(out.getvalue())
n.close()

###
# Write objdiff config
###
with open("objdiff.json", "w") as w:
    json.dump(objdiff_config, w, indent=4)
