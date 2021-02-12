<p align="center">
  <img src="/res/logo.png" alt="gamesneeze-linux">
  <a href="/LICENSE"><img src="https://img.shields.io/badge/License-MIT-green.svg" alt="MIT License"></a>
  <a><img src="https://img.shields.io/badge/OS-Linux-green.svg" alt="Linux"></a>
  <a><img src="https://img.shields.io/badge/Cheat-CS:GO-green.svg" alt="CS:GO cheat"></a>
  <a><img src="https://img.shields.io/badge/State-Unfinished-red.svg" alt="Unfinished"></a>
  <a><img src="https://img.shields.io/badge/Detection-Undetected-green.svg" alt="Detection: Unknown"></a>
  <a href="https://gitter.im/gamesneeze/community?utm_source=share-link&utm_medium=link&utm_campaign=share-link"><img src="https://img.shields.io/badge/Chat-Gitter-green.svg" alt="Gitter"></a>
  <a href="https://discord.gg/SCHsWHFJMb"><img src="https://img.shields.io/badge/Chat-Discord-blue.svg" alt="Discord"></a>
</p>

An open source cheat for Counter-Strike: Global Offensive on Linux.

**:warning: :warning: THIS IS A CHEAT FOR LINUX, IT WILL NOT INJECT IF YOU ARE ON WINDOWS, AND I'M NOT PLANNING ON PORTING ANYTIME SOON, DO NOT JOIN THE DISCORD ASKING FOR DLL :warning: :warning:**

## Current Features

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/d3769a82a63d419fad166c49d98bd810)](https://app.codacy.com/gh/seksea/gamesneeze?utm_source=github.com&utm_medium=referral&utm_content=seksea/gamesneeze&utm_campaign=Badge_Grade)

### Interfaces

- Interfaces::client
- Interfaces::engine
- Interfaces::panel
- Interfaces::clientMode
- Interfaces::globals
- Interfaces::entityList
- Interfaces::engineVgui
- Interfaces::modelRender
- Interfaces::modelInfo
- Interfaces::materialSystem

### Hooks

- CreateMove
- PaintTraverse
- SwapWindow
- PollEvent
- DrawModelExecute
- FrameStageNotify
- Paint

### Features

- Chams
- ESP
- Weapon ESP
- Chicken/Fish ESP
- World Colour Modulation
- Force square radar
- Recoil Crosshair
- Rank Revealer
- Radio fake ban/fake chat
- Clantag (and pBeeMovie clantag)
- Simple triggerbot

### Others

- Basic GDB injector
- ImGui menu

## How to use

```sh
git clone https://github.com/seksea/gamesneeze
cd gamesneeze
chmod +x toolbox.sh
./toolbox.sh -u -b -l # unload cheat if currently injected, build and then load, use -h for help
```

## Basic toolbox.sh usage

| Argument          | Description                           |
| ----------------- | ------------------------------------- |
| -u (--unload)     | Unload the cheat from CS:GO if loaded |
| -l (--load)       | Load/inject the cheat via gdb         |
| -b (--build)      | Build to the build/ dir               |
| -h (--help)       | Show help                             |

All args are executed in the order they are written in, for example, "-u -b -l" would unload the cheat, build it, and then load it back into csgo.

## Found a bug / want to add something?

- [Create a pull request](https://github.com/seksea/gamesneeze/compare) (Add yourself to the [credits](src/core/menu/tabs/misc.cpp#L10))
- [Report a bug](https://github.com/seksea/gamesneeze/issues/new)

## [Todo List](https://github.com/seksea/gamesneeze/projects/1)

## Code style

- Interfaces layed out like this (func names, arg names and comments typed as in the [2015 leak](https://github.com/perilouswithadollarsign/cstrike15_src) or the [source sdk](https://github.com/ValveSoftware/source-sdk-2013)):

```cpp
// https://github.com/ValveSoftware/source-sdk-2013/blob/0d8dceea4310fde5706b3ce1c70609d72a38efdf/sp/src/public/cdll_int.h#L194
class IVEngineClient {
public:
  // Gets the dimensions of the game window
  void GetScreenSize(int& width, int& height) {
    typedef void (*Fn)(void*, int&, int&);
    return getVirtualFunc<Fn>(this, 5)(this, width, height);
  }
  // etc...
}
```

- Namespaces start with capital letter:

```cpp
namespace Log {};
namespace Hooks {};
//etc...
```

- classes begin with capital letters:

 ```cpp
class Player {
public:
    // etc...
}
```

- lowerCamelCase for everything else except stuff ripped from source sdk:

```cpp
class InterfaceReg {
public:
    InstantiateInterfaceFn m_CreateFn;
    const char* m_pName;
    InterfaceReg* m_pNext;
};
```

- filenames all lowercase:

```
createmove.cpp
ibaseclientdll.hpp
hooks.hpp
```

## Screenshots

![Console Output](res/console.png)

![Choms Output](res/chams.png)
