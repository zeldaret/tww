# Cheatsheet

## Common Inlines
When accessing a field in `g_dComIfG_gameInfo`, there is likely an inline using the format `dComIfG_XXX`,
check `d_com_inf_game.h`

Common interactions with the `fopAc_ac_c` struct involve the `fopAcM_` inlines. Check `f_op_actor_mng.h`
Other Actor inlines can be found in `f_pc_manager.h`

Accessing `g_env_light` should use the inline `dKy_getEnvlight()`

The stage based inlines can be found in `d_stage.h`

Audio Inlines are in `m_Do_audio.h`, check when dealing with `mDoAud_zelAudio_c`

The `Mtx` struct has a lot of inlines in the `m_Do_mtx.h` file

*TODO - insert JKR inlines, might be more useful to pair with Ghidra output examples?*

### Finding Inlines
Make sure to reference the debug map when dealing with functions, especially on the first pass.

This can hint at a local `inline` when you see something like `function__##currentNamespace_varation##currentNamespace`, for example
`getItemNo__15daSpcItem01_prmFP13daSpcItem01_c`. That same format can hint at another file's inline being referenced.

## Macros

The two main Macros you'll likely see are the `fopAcm_SetupActor` Macro, and the `JUTAssertion` Macros.

### fopAcm_SetupActor
For `fopAcm_SetupActor` the first hint is being in some sort of `create` function, in Ghidra the macro is already expanded
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
The original developers of The Wind Waker used switch statements extensively. Ghidra fails to recognize small switches,
so here is a quick example to refer to.

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
You can also get single case switch statements instead of `if/else`. For example,
```c++
if (m_itemNo == BOKO_BELT) {
    offsetY = -24.0f;
}
// Should be
switch (m_itemNo) {
case BOKO_BELT:
    offsetY = -24.0f;
    break;
}
```
The above is especially useful to try out in case you're dealing with register mismatch.
The assembly will hint at as the switch statement if you get this pattern,
```asm
cmpwi
beq
bge
;
cmpwi
beq
b
;; Aka cmpwi + a lot of branching is likely a small switch statement.
```

## Register Problems
When dealing with register mismatching, we've found the following situations to help.
When dealing with enums, you might have to do a double return. For example
```c++
return createInit() ? 4 : 5 
// Matches, but we know Enums were used in this function.
if (createInit()) {
   return cPhs_COMPLEATE_e;
} else {
   return cPhs_ERROR_e;
}
```
This pattern also holds for general `if` statements.
```c++
s32 modelFileName = (mArrowType == TYPE_LIGHT ? 0x38 : 0x37) & 0xFFFF;
// Matches, but Enums are preferred.
u16 modelFileIndex;
if (mArrowType == TYPE_LIGHT) {
    modelFileIndex = LINK_BOL_ARROWGLITTER;
} else {
    modelFileIndex = LINK_BOL_ARROW;
}
```

## Struct Size
Not all the Structs in Ghidra have been defined. You'll see array access syntax for undersized structs. Cross-reference 
with [this resource](https://github.com/LagoLunatic/WW-Hacking-Docs/blob/master/Extracted%20Data/Actor%20Instance%20Sizes.txt)
and adjust accordingly.

As there are still plenty of fields we don't have names for, defining our struct is very useful, you'll see the following
patterns in the codebase.

```c++
public:
  /* 0xOFFSET */ type mName; 
// Offset value for the field, Ghidra is useful for this.
  /* 0xOFFSET */ type* mpName;
// AKA standard C naming conventions.

// The following are more "personal preference" approaches to handling unknown values.
  /* 0xOFFSET */ u8 mOffset[0xHigh_Unknown - 0xOffset];
// All the values between 0xHigh_Unknown - 0xOffset are still unknown.
  /* 0xOFFSET  */ u8 field_0xOFFSET;
  /* 0xOFFSET1 */ u8 field_0xOFFSET1;
// Similar to the array approach, but defines all the unkown `u8` as their own field instead.
  /* 0xOFFSET */  type field_0xOFFSET;
// This field is typed correctly, but has an unknown purpose. `type mOffset` could also convey this. 
} // Size 0xVALUE
// ^ Total size of the Struct, could also do the folling
STATIC_ASSERT(sizeof(MyStruct) == 0xVALUE);
```