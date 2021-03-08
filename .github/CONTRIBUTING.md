# Contributing to gamesneeze

## Gotchas

* Read, and fill the Pull Request template
  * If this is a fix for a typo in code or documentation in the README please file an issue
  * If the PR is addressing an existing issue include, closes #\<issue number>, in the body of the PR commit message
* If you want to discuss changes, you can also bring it up in #general in our [Discord server](https://discord.gg/SCHsWHFJMb)

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
