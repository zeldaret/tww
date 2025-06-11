The Legend of Zelda: The Wind Waker  
[![Build Status]][actions] [![Progress]][progress site] [![DOL Progress]][progress site] [![RELs Progress]][progress site] [![Discord Badge]][discord]
=============

[Build Status]: https://github.com/zeldaret/tww/actions/workflows/build.yml/badge.svg
[actions]: https://github.com/zeldaret/tww/actions/workflows/build.yml
[Progress]: https://decomp.dev/zeldaret/tww.svg?mode=shield&measure=code&label=Code&category=all
[DOL Progress]: https://decomp.dev/zeldaret/tww.svg?mode=shield&measure=code&label=DOL&category=dol
[RELs Progress]: https://decomp.dev/zeldaret/tww.svg?mode=shield&measure=code&label=RELs&category=modules
[progress site]: https://zeldaret.github.io/tww/
[Discord Badge]: https://img.shields.io/discord/688807550715560050?color=%237289DA&logo=discord&logoColor=%23FFFFFF
[discord]: https://discord.com/invite/DqwyCBYKqf/

A work-in-progress decompilation of The Legend of Zelda: The Wind Waker for GameCube.

This repository does **not** contain any game assets or assembly whatsoever. An existing copy of the game is required.

All GameCube versions are supported:

- `GZLE01`: Rev 0 (USA), Rev 48 (KOR)
- `GZLP01`: Rev 0 (PAL)
- `GZLJ01`: Rev 0 (JPN)
- `D44J01`: Kiosk demo (JPN)

Dependencies
============

Windows:
--------

On Windows, it's **highly recommended** to use native tooling. WSL or msys2 are **not** required.  
When running under WSL, [objdiff](#diffing) is unable to get filesystem notifications for automatic rebuilds.

- Install [Python](https://www.python.org/downloads/) and add it to `%PATH%`.
  - Also available from the [Windows Store](https://apps.microsoft.com/store/detail/python-311/9NRWMJP3717K).
- Download [ninja](https://github.com/ninja-build/ninja/releases) and add it to `%PATH%`.
  - Quick install via pip: `pip install ninja`

macOS:
------
- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages):
  ```
  brew install ninja
  ```
- Install [wine-crossover](https://github.com/Gcenx/homebrew-wine):
  ```
  brew install --cask --no-quarantine gcenx/wine/wine-crossover
  ```

After OS upgrades, if macOS complains about `Wine Crossover.app` being unverified, you can unquarantine it using:
```sh
sudo xattr -rd com.apple.quarantine '/Applications/Wine Crossover.app'
```

Linux:
------
- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).
- For non-x86(_64) platforms: Install wine from your package manager.
  - For x86(_64), [WiBo](https://github.com/decompals/WiBo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

Building
========

- Clone the repository:
  ```
  git clone https://github.com/zeldaret/tww.git
  ```

- Copy your game's disc image to `orig/GZLE01`.
  - Supported formats: ISO (GCM), RVZ, WIA, WBFS, CISO, NFS, GCZ, TGC
  - After the initial build, the disc image can be deleted to save space.

- Configure:
  ```
  python configure.py
  ```
  To use a version other than `GZLE01` (USA), specify `--version GZLJ01` (JPN) or `--version GZLP01` (PAL).

- Build:
  ```
  ninja
  ```

Diffing
=======

Once the initial build succeeds, an `objdiff.json` should exist in the project root. 

Download the latest release from [encounter/objdiff](https://github.com/encounter/objdiff). Under project settings, set `Project directory`. The configuration should be loaded automatically. 

Select an object from the left sidebar to begin diffing. Changes to the project will rebuild automatically: changes to source files, headers, `configure.py`, `splits.txt` or `symbols.txt`.

![](assets/objdiff.png)

Setting up Ghidra
=================

Ghidra is a tool that automatically decompiles code. Although Ghidra's output is not accurate enough to be directly copy-pasted into this decompilation project, it can still be helpful for understanding functions and decompiling them faster.

We have a shared Ghidra project for TWW already set up. To get access to this server:

* Go to https://ghidra.decomp.dev and link your Discord account.
* Create a Ghidra account by entering a new username and password into the form on the right.
* Request "Read" access to the WindWaker server.

Then wait for an admin to approve your request. Once you have access, you can set up the Ghidra project like so:

* To use Ghidra, you first need to install JDK. You can download OpenJDK 17 from [here](https://adoptium.net/temurin/releases/).
* Download the RootCubed Ghidra build ghidra_11.1_DEV_20240115 from [here](https://rootcubed.dev/ghidra_builds/).
* Launch Ghidra with `ghidraRun`.
* In Ghidra, go to `File -> New Project...`. Select `Shared Project` and input the following information:
    * Server Name: ghidra.decomp.dev
    * Port Number: 13100
    * User ID: (the username that you chose earlier)
    * Password: (the password that you chose earlier)
* You should now be able to view the files in the Ghidra project. You should checkout the `main` file.

Now you have Ghidra set up and ready to use.

For an introduction on how to use Ghidra, you can read [this section of the Twilight Princess decompilation's guide](https://zsrtp.link/contribute/decompiler-setup#using-ghidra).

Optionally, you may also want to also request "Read" access to the TwilightPrincess server on https://ghidra.decomp.dev and set that Ghidra project up too, even if you are not interested in working on that game. The reason for this is that a significant amount of engine code is shared between The Wind Waker and Twilight Princess, and the debug version of Twilight Princess (called `shield_chn_debug` in the Ghidra project) is easier to work with because inline functions are not inlined in that version. It can be worth checking if the function you're working on is present in that game as well.

Contributing
=======

If you've got all the requirements set up and want to learn how to contribute to the decompilation effort, see [this guide](/docs/decompiling.md) for details.
