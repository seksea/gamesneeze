<p align="center">
  <img src="/res/logo.png" alt="gamesneeze-linux">
  <a href="/LICENSE"><img src="https://img.shields.io/badge/License-MIT-green.svg" alt="MIT License"></a>
  <a><img src="https://img.shields.io/badge/OS-Linux-green.svg" alt="Linux"></a>
  <a><img src="https://img.shields.io/badge/Cheat-CS:GO-green.svg" alt="CS:GO cheat"></a>
  <a><img src="https://img.shields.io/badge/State-Unfinished-red.svg" alt="Unfinished"></a>
  <a><img src="https://img.shields.io/badge/Detection-Unknown-yellow.svg" alt="Detection: Unknown"></a>
  <a href="https://gitter.im/gamesneeze/community?utm_source=share-link&utm_medium=link&utm_campaign=share-link"><img src="https://img.shields.io/badge/Chat-Gitter-green.svg" alt="Gitter"></a>
</p>

An open source cheat for Counter-Strike: Global Offensive on linux.

## Current Features
- Basic GDB injector
- Example CreateMove Hook
- SwapWindow & PollEvent Hooked
- ImGui

## How to use
```
git clone https://github.com/seksea/gamesneeze
cd gamesneeze
chmod +x toolbox.sh
sudo ./toolbox.sh -u -b -l # unload cheat if currently injected, build and then load, use -h for help
```

## Basic toolbox.sh usage
| Argument          | Description                           |
| ----------------- | ------------------------------------- |
| -u (--unload)     | Unload the cheat from CS:GO if loaded |
| -l (--load)       | Load/inject the cheat via gdb         |
| -b (--build)      | Build to the build/ dir               |
| -h (--help)       | Show help                             |

All args are executed in the order they are written in, for example, "-u -b -l" would unload the cheat, build it, and then load it back into csgo.


## Found a bug/want to add something?
- [Create a pull request](https://github.com/seksea/gamesneeze/compare) ([tutorial](https://github.com/yangsu/pull-request-tutorial))
- [Report a bug](https://github.com/seksea/gamesneeze/issues/new)

## Todo
- [x] Start Game Interfaces
- [ ] Add bunch of interfaces
- [x] Game Hooks
- [ ] Visual/Misc Features
- [ ] Prediction
- [ ] Legitbot
- [ ] Ragebot

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
- lowerCamelCase for everything except stuff ripped from source sdk:
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
![Current Menu](https://imgur.com/E65seLC.png)
![Console Output](res/console.png)
