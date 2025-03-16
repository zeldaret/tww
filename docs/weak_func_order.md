# Fixing weak function ordering

If everything symbol in a TU is 100% matched, but the order of weak functions (ones with `[gw]` in objdiff) is different on the left and the right, then the TU is functionally equivalent, but it won't actually match when linked.

## Table of Contents

1. [Compiler flags](#compiler-flags)
2. [Factors affecting weak function order within a .text section](#factors-affecting-weak-function-order-within-a-text-section)
3. [Factors affecting the number of .text sections](#factors-affecting-the-number-of-text-sections)

## Compiler flags

The most common cause of weak functions being ordered incorrectly is simply the compiler flags. The following compiler flags are currently known to affect it:

* `-sym on` (the default)
* `-sym off`
* `-pragma "nosyminline on"`

If the weak function ordering is incorrect with the default (`-sym on`), you should try modifying [configure.py](../configure.py) to add different flags for the TU you're working on, like so:

```py
ActorRel(Matching, "d_a_am", extra_cflags=['-pragma "nosyminline on"']),
```

First try adding `-pragma "nosyminline on"`, as that fixes the weak function ordering for many actors. Try running `ninja` again to check if it matches this time. If it still doesn't match and the order is still wrong in objdiff, try using `-sym off` instead and checking again.

If neither of those fix it, I recommend marking the TU as `Equivalent` in [configure.py](../configure.py) and adding a comment about the weak function order, e.g.:

```py
ActorRel(Equivalent, "d_a_pirate_flag"), # weak func order
```

Then you can just submit a pull request as-is instead of worrying about it any more. The build system won't be able to automatically verify that the TU is accurately decompiled, but it will still contribute to the project's overall percent completion and be useful for anyone interested in understanding the code of the actor you just decompiled or modding the actor, as weak function order has no effect on the functionality of the code.

**You can stop reading here if you're new to decompilation and working on learning the basics.** The rest of this document will go into more advanced details about weak function ordering, but all of the exact specifics are not fully understood by anyone yet.

### Explanation of compiler flags

`-sym on` is a flag that enables debugging information, such as line numbers (you can see these line numbers in objdiff, to the left of the assembly instructions).  
Due to a strange quirk of the compiler, this flag has the side effect of causing functions to be split up into multiple .text sections, one for each unique filename that a function is defined in. So functions defined in the .cpp file would go in the first .text section, functions defined in one header file would get their own separate .text section, functions defined in a different header file would go in a third .text section, etc.

`-sym off` disables that debugging information, removing line numbers.  
This also disables the multiple .text sections side effect - all functions will go in a single section instead.

When `-sym on` is enabled, using the `-pragma "nosyminline on"` flag too will cause inline functions to have their debugging information disabled, while normal functions will still have debugging information.  
This has an unpredictable effect on the number of .text sections in the file. Some of the weak functions defined in headers will be merged into the main .text section for the .cpp file, while others will be merged into a different .text section that's for a different header, others will not be merged at all, etc. It's not currently understood how this is determined.

## Factors affecting weak function order within a .text section

If one of those three compiler flags result in the .text sections being split up correctly, but there are still weak functions out of order compared to other functions in the same section, there are a number of known factors that can affect this.

### Defining template virtual weak functions inside vs outside a class body

For template classes, sometimes defining virtual weak functions within the class body like this:

```cpp
template<typename T>
class JPACallBackBase {
public:
    JPACallBackBase() {}
    virtual ~JPACallBackBase() {}

    virtual void init(T) {}
    virtual void execute(T) {}
    virtual void executeAfter(T) {}
    virtual void draw(T) {}
};  // Size: 0x04
```

Will result in those functions being put out of order. These can be fixed by moving the definitions to after the class body (but still in the header), and marking the declarations as `inline` within the class body:

```cpp
template<typename T>
class JPACallBackBase {
public:
    JPACallBackBase() {}
    virtual ~JPACallBackBase() {}

    inline virtual void init(T);
    inline virtual void execute(T);
    inline virtual void executeAfter(T);
    inline virtual void draw(T);
};  // Size: 0x04

template<>
void JPACallBackBase<JPABaseEmitter*>::init(JPABaseEmitter*) {}
template<>
void JPACallBackBase<JPABaseEmitter*>::execute(JPABaseEmitter*) {}
template<>
void JPACallBackBase<JPABaseEmitter*>::executeAfter(JPABaseEmitter*) {}
template<>
void JPACallBackBase<JPABaseEmitter*>::draw(JPABaseEmitter*) {}
```

### TODO HeartPiece's list

* [ ] pure virtual base class
* [ ] pure virtual declarations in classes inheriting from a pure virtual base class (i.e. re-declaring something pure virtual)
* [ ] implicit vs explicit definitions of special virtual functions (such as dtors)
* [ ] ordering of virtual weak function declaration in inheriting classes after their order is defined in a base class
* [ ] ordering of virtual function declaration in "higher" (more base) classes when the virtuals are weak in an inheriting class
* [x] definition within or external to a class within a given header for template virtuals (and template weak functions in general, do not have to be virtual)
* [ ] order of declaration of weak AND virtual weak functions in template class definitions (interweaving non-virtual weak function definitions between virtual function definitions affects ordering)
* [ ] calling of inlines within weak virtual template function definitions (calling inlines, even if they don't get generated as actual functions, affects where stuff spits out, such as "invisible" getters and setters)
* [ ] stripped functions calling virtual functions within files
* [ ] ordering of NON-weak functions within virtual tables (previously ordered by declaration in base classes) causing vtable spawn ordering adjustments (i.e. hitting the "key" method for a vtable before or after a "key" method for another table)
* [ ] calling a virtual function from an inheriting class vs a base class on the same object

## Factors affecting the number of .text sections

If none of the three sym compiler flags mentioned above result in the .text sections being split up correctly, then there are a few known factors that can influence this splitting, but for the most part this is still an unsolved problem.

We have a list of decompiled actors that cannot be linked due to this issue [here on GitHub](https://github.com/zeldaret/tww/issues?q=is%3Aissue%20state%3Aopen%20label%3Aweakfunc-order).

### TODO

* constructor defined in header vs cpp
* explicit vs implicit definition of virtual weak destructor in child class (e.g. `virtual ~dCcD_Cyl() {}`) (only has an effect WITHOUT nosyminline) (also applies to non-virtual destructors if the class has other virtual functions?)
