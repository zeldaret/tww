# Cheatsheet

## Common Inlines

| Struct/Object        | Inline Definition  |
|----------------------|--------------------|
| `g_dComIfG_gameInfo` | `d_com_inf_game.h` |
| `fopAc_ac_c`         | `f_op_actor_mng.h` |
| `fopAc_ac_c`         | `f_pc_manager.h`   |
| Mtx                  | `m_Do_mtx.h`       |
| Stage                | `d_stage.h`        |

Accessing `g_env_light` might use `dKy_getEnvlight()`, in a small handful of places.

Audio Inlines are in `m_Do_audio.h`, check when dealing with `mDoAud_zelAudio_c`

### Finding Inlines

Make sure to reference the debug map when dealing with functions, especially on the first pass. 
You can find the map pinned in the Main Decomp channel in the Discord. You can think of this map as one
of the last steps of the compiler, where it writes a record of what symbols it used and where it used them. Particularly
for debugging purposes.

If you go into the `.text section layout` of the Map file, 
you'll be able to spot what inlines are used, and in what function.

This can hint at a locally defined `inline` when you see something like `function__##currentNamespace_varation##currentNamespace`,
for example
`getItemNo__15daSpcItem01_prmFP13daSpcItem01_c`.

## Macros

The two main Macros you'll likely see are the `fopAcm_SetupActor` Macro, and the `JUTAssertion` Macros.

### fopAcM_SetupActor

For `fopAcM_SetupActor` the first hint is being in some sort of `create` function, in Ghidra the macro is already
expanded
so just keep an eye out for something like the following.

```c++
if (((this->parent).mCondition & Constructed) == 0) {
    if(this != (structPointer_c *) 0x0) {
        fopAc_ac_c::fopAc_ac_c((fopAc_ac_c*) this);
        // More stuff
    }
    (this->parent).mCondition = (this->parent).mCondition | Constructed;
}
```

Everything within the first `if` statement is handled by the `fopAcm_SetupActor` Macro.

### JUTAssertion

This is more a "family" of Macros, however most of the time we're dealing with `JUT_ASSERT`. Super easy pattern to spot,
just the following.

```c++
if (condition) {
  tempVar = JUTAssertion::getSDevice();
  JUTAssertion::showAssert(tempVar, "current_file.cpp", lineNumber, "condition");
  m_Do_printf::OSPanic("current_file.cpp", lineNumber, "Halt");
}
```

This is really useful for figuring out the variable names used, so keep an eye out for it. See `JUTAssert.h` for the
full family of Macros.

## Recognize the 'switch'

Ghidra fails occasionally to recognize switch statements, so here is a quick example to refer to.

```c++
if (m_itemNo != SHIELD) {
    if (m_itemNo < SHIELD && m_itemNo == PENDANT) {
        if (mAcch.m_flags & dBgS_Acch::GROUND_LANDING) {
            // stuff
        }
    } else if (mAcch.m_flags & dBgS_Acch::GROUND_LANDING) {
        // stuff 1
    }
}
// Should be
switch (m_itemNo) {
case SHIELD:
    break;
case PENDANT:
    if (mAcch.ChkGroundLanding()) {
        // stuff
    }
    break;
default:
    if (mAcch.ChkGroundLanding()) {
       // stuff 1
    }
    break;
}
```

You can rarely get single case switch statements instead of `if/else`. For example,

```c++
if (m_itemNo == BOKO_BELT) {
    offsetY = -24.0f;
}
// Instead
switch (m_itemNo) {
case BOKO_BELT:
    offsetY = -24.0f;
    break;
}
```

However, a single switch statement will be uncommon. When in doubt you can view the Assembly, and switch statements
will always have the following pattern.

```asm
cmpwi
beq
bge
;
cmpwi
beq
b
;; Aka cmpwi + a lot of branching -> Switch Statement
```

## General Styling / Matching

Compilers are weird, here are some oddities we've found, and solutions to get them to match.

```c++
// Intuition would be the following.
return createInit() ? cPhs_COMPLEATE_e : cPhs_ERROR_e; 
// Which fails to match, try this instead.
if (createInit()) {
   return cPhs_COMPLEATE_e;
} else {
   return cPhs_ERROR_e;
}
```

- Insert more oddities as they crop up.
## Struct Size

Not all the Structs in Ghidra have been defined. You'll see array access syntax for undersized structs. Cross-reference
with [this resource](https://github.com/LagoLunatic/WW-Hacking-Docs/blob/master/Extracted%20Data/Actor%20Instance%20Sizes.txt)
and adjust accordingly.
