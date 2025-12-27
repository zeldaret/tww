# Coding guidelines

This page contains some tips on how code should be written in this decompilation project. We don't have strict style rules for most things, but you should keep your code readable, and try to stick to the names and style used by the original programmers whenever possible.

Naming variables properly isn't required to help with the decompilation. You can submit a PR with code you decompiled even if many of the variable names are just placeholders (e.g. `field_0x290`, `temp`, `r29`, `sp10`, etc) - these names can always be cleaned up later in a documentation pass of the actor. Placeholder names are preferable to coming up with names that are incorrect if you aren't sure exactly what the variables are.

## Table of Contents

1. [Primitive types](#primitive-types)
2. [Offsets and padding](#offsets-and-padding)
3. [Includes](#includes)
4. [Naming style](#naming-style)
5. [Use the official names where possible](#use-the-official-names-where-possible)
6. [Resource archive enums](#resource-archive-enums)
7. [Look at the actor's model](#look-at-the-actors-model)

## Primitive types

Prefer using the [Dolphin typedefs](../include/dolphin/types.h) for primitive types in game code, for example:

* `signed char` -> `s8`
* `signed short` -> `s16`
* `signed long` -> `s32`
* `signed long long` -> `s64`
* `unsigned char` -> `u8`
* `unsigned short` -> `u16`
* `unsigned long` -> `u32`
* `float` -> `f32`
* `double` -> `f64`

This makes no difference for matching, but the original devs used these in game code so it's best to do the same for consistency. The typedefs are also shorter and require less typing.

But be aware that `int` and `s32` are *not* the same type. Even though they are both signed 32-bit integers, the compiler treats them differently and will produce different code sometimes, so which one you use matters for matching. There is no typedef for `int`, so use that type directly.

## Offsets and padding

Member variables of classes and structs should all have comments to their left with the hexadecimal data offset of that member:

```cpp
struct anm_prm {
    /* 0x00 */ s8 anmTblIdx;
    /* 0x01 */ u8 armAnmTblIdx;
    /* 0x02 */ u8 btpAnmTblIdx;
    /* 0x04 */ int loopMode;
    /* 0x08 */ f32 morf;
    /* 0x0C */ f32 speed;
};
```

Furthermore, padding data should not be written in the class/struct body. In the example above, note that no field is located at offset 0x03, and then `int loopMode;` starts at offset 0x04. This is because `int` needs to be aligned to 4 bytes, so the compiler can't put it at offset 0x03, so it inserts one unused byte of padding before `loopMode`.

If a translation unit isn't fully decompiled yet, then there's no way to know if a particular offset is padding or if it actually has a field in there that is used by code that hasn't been decompiled yet. So you should wait until the TU is 100% decompiled before removing fields that look like padding.

## Includes

Avoid unnecessary includes, especially in header files. clangd will give you a warning saying "Included header is not used directly (fix available)" if you aren't using a header at all.

Forward declaring types where possible will reduce compile times. So instead of putting all the includes in an actor's header file, like so:

```cpp
#include "d/d_path.h"
#include "d/actor/d_a_obj_search.h"
dPath* ppd;
daObj_Search::Act_c* mpSearchLight;
```

You could move those includes into the actor's .cpp file where they are actually needed, and add forward declarations to the actor's header like so:

```cpp
class dPath;
namespace daObj_Search { class Act_c; };
dPath* ppd;
daObj_Search::Act_c* mpSearchLight;
```

## Naming style

We try to stick to the same naming style that the original developers used. They didn't have a completely consistent naming style, but they tended to use certain prefixes and styles depending on the type of variable.

Function parameters should be prefixed with `i_` (or `o_` if it's an output parameter) and use lowerCamelCase:

* `fopAc_ac_c* i_this`
* `int i_itemNo`
* `GXTlutObj* o_tlutObj`

In-function local variables have no prefix and use lower_snake_case:

* `int zoff_blend_cnt = 0;`
* `int phase_state = ...`

Member variables of classes are generally prefixed with `m` (or `mp` for pointers) and use UpperCamelCase:

* `fpc_ProcID mTimerID;`
* `J3DModel* mpModel;`

Member variables of structs (plain old data) have no prefix and use lower_snake_case:

* `csXyz shape_angle;`
* `int id;`

Static variables are prefixed with `l_`, while global variables are prefixed with `g_` (the official names for these are all known from the symbol maps):

* `static cXy l_texCoord[] = ...`
* `dComIfG_inf_c g_dComIfG_gameInfo;`

## Use the official names where possible

If a class has a getter function (whether it's an inline or not) that returns a member variable, you should generally name the member as indicated by its getter.

For example: `getChainCnt()` would return `mChainCnt`.

Another place that official variable names of all kinds can be revealed is in debug assertion strings. In these cases, you should always use the exact name from the assert, even if it doesn't follow a consistent style. For example, the following are both official names for similar in-function local variables:

```cpp
J3DModelData* modelData = ...
JUT_ASSERT(98, modelData != NULL);
```

```cpp
J3DModelData* model_data = ...
JUT_ASSERT(382, model_data != NULL);
```

## Resource archive enums

Most actors will load resource files, such as model data, with code similar to this:

```cpp
modelData = (J3DModelData*)dComIfG_getObjectRes("Bk", 0x5B);
```

The first argument to `dComIfG_getObjectRes` is the name of the resource archive being used, in this case `files/res/Object/Bk.arc` within the game's files.  
The second argument is the file index of the specific file being loaded from this archive, in this case index 0x5B within the archive.

In order to make the code more readable, you should replace all of these file indexes with enums containing the filename instead. But you don't have to create these enums manually, the decomp already has enums for all resource archives.

You can find the header for the archive in question by pressing VSCode's `Ctrl+P` shortcut and typing `res_` followed by the name of the resource archive.  
In this example, the header you want is located at `include/d/res/res_bk.h` because the archive is named "Bk". The resource archive's name is not necessarily the same as the actor's name (though in this example it is).

Once you open the header, search for the file index, e.g. 0x5B:

```cpp
BK_BMD_BK_TATE=0x5B,
```

This means `BK_BMD_BK_TATE` is the enum for this file, so replace the index with the enum like so:

```cpp
modelData = (J3DModelData*)dComIfG_getObjectRes("Bk", BK_BMD_BK_TATE);
```

## Look at the actor's model

If a variable's name doesn't appear in a function name or assertion string, we'll have to come up with a name for it ourselves. To do this, you usually need to know what the decompiled actor you're looking at actually is in-game before you can start coming up with names. But it's often pretty hard to tell what an actor is just by reading its code.

The official TU name of the actor doesn't tell you much, not only because they're frequently in Japanese, but also because they're aggressively abbreviated. e.g. `d_a_nh` is short for "mori **n**o **h**otaru", which is Japanese for "forest firefly", but it would be pretty much impossible to guess that without context, even if you know Japanese.

If the actor has a 3D model, you can determine what the actor is by simply viewing the model in a model viewer. First, find the .arc file for this actor. Look in the `createHeap` or `useHeapInit` function for this actor. You should see something like:

```cpp
(J3DModelData*)dComIfG_getObjectRes("Bk", BK_BDL_BK)
```

This means the actor's .arc in this example is named "Bk". You can find it your copy of TWW's files at `files/res/Object/Bk.arc`.

Next go to https://noclip.website/ and drag-and-drop the .arc file onto the website. It should display all of the 3D models in that archive on top of each other. You can open up the "Layers" menu on the left hand side and toggle off specific models if it's too confusing with them all overlapping.

Alternatively, you can also download [GCFT](https://github.com/LagoLunatic/GCFT) (version 2.0.0 or higher) to view models if you prefer an offline program to a website. GCFT allows you to load not just models but also their animations, which may be helpful in determining the exact difference between states if the actor has multiple animations.  
Drag-and-drop the .arc file onto GCFT to open it, then right click on one of the BDL models and select "Open J3D" to view the model. You can also go back to the RARC tab and right click a BCK animation and select "Load J3D Animation" to view that animation on the model you have loaded.
