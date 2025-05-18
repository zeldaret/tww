# Register swaps / register allocation

Sometimes, all of the instructions in a function will match, but which variable got put in which processor register by the compiler (register allocation) is all swapped around. This is known as a register swap or regswap.

Some regswaps you encounter will have unique solutions, but most are caused by just a handful of recurring patterns. The purpose of this document is to act as a cheatsheet showing examples of those common patterns and how they can be fixed.

## Double check that the function is equivalent

Before trying different things that affect how the compiler performs register allocation, you should first double check that the way you've decompiled the function so far is even functionally equivalent.

Rarely, you will make a mistake and swap two different variables of the same type, e.g. by passing the `this` pointer to a function when you should have passed a local variable that points to a different actor entirely.

One thing you can do to help spot these mistakes is click on one of the swapped registers on the left hand side in objdiff, then click on the swapped register that's in the same location but on the right hand side. Even though the register numbers are different, you should see that the highlighted locations where they are used is the same on both sides if the function is equivalent. If the highlighted locations are different on each side, this might mean you used the wrong variable in that spot. (However, for very large functions, this trick might not always work. The highlighted locations might differ due to complex regalloc even if you didn't make any mistakes.)

If you did make a mistake that causes the function to be non-equivalent, then none of the patterns the rest of this guide goes over will help you, and you'll just be wasting your time trying them.

## Shuffling local variable declaration order

The order that local variables is declared is not always the same as the order they are first assigned to, and this can impact regalloc.

You can try moving all of the local variable declarations to the top of the function like so:

```cpp
/* 8024F410-8024FA90       .text cM3d_Cross_CylLin__FPC8cM3dGCylPC8cM3dGLinP3VecP3Vec */
int cM3d_Cross_CylLin(const cM3dGCyl* cyl, const cM3dGLin* line, Vec* param_2, Vec* param_3) {
    f32 ratio;
    f32 f2;
    f32 fVar5;
    f32 fVar2;
    f32 fVar1;
    f32 fVar6;
    f32 fVar4;
    BOOL bVar4;
    BOOL bVar3;
    BOOL bVar6;
    BOOL bVar5;
    u32 uVar11;
    f32 sp28;
    f32 r_sq;
    int count;

    ratio = 0.0f;
    ...
```

And then try moving them around relative to each other to see if you can change regalloc that way.

## C-style actor base pointer as a separate variable

When working on C-style actors (actor classes named like `xyz_class` that don't have member functions), you will often encounter a regswap where one of the incorrect registers will contain the `xyz_class* i_this` parameter. For example:

```cpp
/* 00000FF4-00001344       .text Line_check__FP9am2_class4cXyz */
static BOOL Line_check(am2_class* i_this, cXyz destPos) {
    dBgS_LinChk linChk;
    cXyz centerPos = i_this->current.pos;
    centerPos.y += 100.0f + REG12_F(19);
    i_this->mLinChkCenter = centerPos;
    i_this->mLinChkDest = destPos;
    linChk.Set(&centerPos, &destPos, i_this);
    if (!dComIfG_Bgsp()->LineCross(&linChk)) {
        return TRUE;
    }
    return FALSE;
}
```

In these cases, try making a local variable called `actor` to hold a pointer to the actor's base class at the start of the function, and then use that variable instead of `i_this` whenever the base class is needed:

```diff
/* 00000FF4-00001344       .text Line_check__FP9am2_class4cXyz */
static BOOL Line_check(am2_class* i_this, cXyz destPos) {
+   fopAc_ac_c* actor = i_this;
    dBgS_LinChk linChk;
-   cXyz centerPos = i_this->current.pos;
+   cXyz centerPos = actor->current.pos;
    centerPos.y += 100.0f + REG12_F(19);
    i_this->mLinChkCenter = centerPos;
    i_this->mLinChkDest = destPos;
-   linChk.Set(&centerPos, &destPos, i_this);
+   linChk.Set(&centerPos, &destPos, actor);
    if (!dComIfG_Bgsp()->LineCross(&linChk)) {
        return TRUE;
    }
    return FALSE;
}
```

## Casting

Explicitly casting from one type to another can affect regalloc. This applies to both primitive types and pointer types. Sometimes, you may have to add a cast that serves no practical purpose just to fix regalloc.

Even the type of casting operator you use affects it in some cases. For example, this C-style cast:

```cpp
J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, VBAKH_BDL_VBAKH);
```

Is functionally equivalent to this C++ static_cast:

```cpp
J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arcname, VBAKH_BDL_VBAKH));
```

But the two of them produce different regalloc.

## Temp variables

Sometimes, instead of writing a single line that does multiple things at once, you may need to split the intermediate values it calculates out into temp variables across multiple lines.

## Inlines

Inlines can affect regalloc, so be sure that you're using the exact inlines mentioned in the debug maps. Also try using inlines used in other functions from the same object, or inlines used in similar functions from a different object.

If you're sure that you're using the right inline, but there are still regswaps happening in the area of the function where the inline is used, the cause can sometimes be that the inline itself is implemented wrong. You may have to try modifying the inline and write the code inside it differently in order to fix the regalloc in the functions that use it.

But when modifying an existing inline, be careful that you don't break any already-matched functions that use the same inline. If you want to quickly check if you caused any regressions, first run `ninja baseline` on the main branch, then run `ninja changes` on your own branch, and any functions that decreased in match percent on your branch will be printed out.

## Const

Whether a variable is `const` or not can affect regalloc (as well as instruction ordering). This is especially true for inline functions parameters.

Even though we know the function signatures of all functions and inlines from the symbol maps, const is not included in mangled symbol names for primitive parameters - only for pointer parameters.

For example, the mangled name `__ct<f>__Q29JGeometry8TVec3<f>Ffff` from the symbol maps would demangle to this signature:

```cpp
TVec3(f32 x, f32 y, f32 z)
```

However, `f32` is a primitive type. So the following is another possibility for this inline's signature:

```cpp
TVec3(const f32 x, const f32 y, const f32 z)
```

You may need to try adding or removing const from inlines like this, but be careful that you don't break any already-matched functions that use the same inline you're modifying. Again, you can use `ninja changes` to check if you caused any regressions.
