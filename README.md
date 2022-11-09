<p align="center">
  <img src="/res/logo.png" alt="gamesneeze-linux">
  <a href="/LICENSE"><img src="https://img.shields.io/badge/License-MIT-green.svg" alt="MIT License"></a>
  <a><img src="https://img.shields.io/badge/Platform-Linux-green.svg" alt="Linux"></a>
  <a><img src="https://img.shields.io/badge/Game-CS:GO-green.svg" alt="CS:GO"></a>
  <a><img src="https://img.shields.io/badge/State-Maintained-green.svg" alt="Maintained"></a>
  <a><img src="https://img.shields.io/badge/Detection-Undetected-green.svg" alt="Detection: Undetected"></a>
  <a href="https://gitter.im/gamesneeze/community?utm_source=share-link&utm_medium=link&utm_campaign=share-link"><img src="https://img.shields.io/badge/Chat-Gitter-green.svg" alt="Gitter"></a>
  <a href="https://discord.gg/SCHsWHFJMb"><img src="https://img.shields.io/badge/Chat-Discord-blue.svg" alt="Discord"></a>
</p>

An open source training utility for Counter-Strike: Global Offensive on Linux.

## If you have an issue injecting gamesneeze, ask on the [Common Issues](#Common-Issues) section, if your issue is still not fixed, ask on the `#support` channel on the Discord.

## Donations

Donations are accepted in BTC and Monero

##### If sending more than 5 usd contact me on discord letting me know and I will add you to the credits as a donor along with the amount donated.

```
BTC:
bc1qwrqhhlam4rl7yh2a09ntgdduw3vg9er3ce8rjq

Monero:
86xJi2jQEocYZ7o6BTrbmTPJKLxbfHAdKdPcTgro3PAw6z3MCcYLq28Ehg4tzRUCPFKDQM1SKbp4RRygnk9FCBux3uxXCDN

Buy me a Coffee:
www.buymeacoffee.com/sekc
```

### Donators
 - [moke#9091](https://github.com/mokeWe) - 0.19XMR (~$30)
 - hx#5185 - 0.2XMR (~$30)

## Current Features

### Features

 - Basic GDB injector
 - ImGui menu
 - Chams
 - ESP
 - Weapon ESP
 - Chicken/Fish ESP
 - World colour modulation
 - Force square radar
 - Recoil crosshair
 - Rank revealer
 - Radio fake ban/fake chat
 - Clantag (and pBeeMovie clantag)
 - Backtracking
 - Backtrack Chams
 - Flappy Bird clone
 - Legitbot
 - Hitmarkers
 - Nightmode
 - Skybox changer
 - Skinchanger
 - Ragebot (currently in development and doesn't have awall/bulletsim so no mindmg/hitchance/autoshoot)
 - AntiAim (currently sways, need to fix LBY breaker)
 - JumpBug
 - EdgeBug
 - Edge Jump


## How to use

### Debian / Ubuntu / Pop OS / Linux Mint required packages:

```sudo apt install -y libsdl2-dev cmake git gcc-10 g++-10 gdb clang```

### Arch / Manjaro required packages:

```sudo pacman -S --needed base-devel git cmake gdb sdl2 clang```

### Fedora required packages:

```sudo dnf install gcc-g++ gdb SDL2-devel cmake git clang```

### OpenSUSE required packages:

```sudo zypper install gcc gdb SDL2-devel cmake git llvm-clang llvm-gold```

```sh
git clone https://github.com/seksea/gamesneeze
cd gamesneeze
chmod +x toolbox.sh
./toolbox.sh -p -u -b -l # pull, unload trainer if currently injected, build and then load, use -h for help
```


## Basic toolbox.sh usage

| Argument           | Description                               |
| ------------------ | ----------------------------------------- |
| -u (--unload)      | Unload the trainer from CS:GO if loaded   |
| -l (--load)        | Load/inject the trainer via gdb           |
| -ld (--load_debug) | Load/inject the trainer and debug via gdb |
| -b (--build)       | Build to the build/ dir                   |
| -bd (--build_debug)| Build to the build/ dir as debug          |
| -p (--pull)        | Update the trainer                        |
| -h (--help)        | Show help                                 |

All args are executed in the order they are written in, for example, "-u -b -l" would unload the cheat, build it, and then load it back into csgo.


## Common Issues

### This trainer will not work with Windows systems, it only supports Linux.

#

### Gamesneeze not injecting but successfully building?

Solution 1 - Steam is installed via snap or flatpak, uninstall steam through 
```
snap uninstall steam
```
or
```
flatpak uninstall steam
```

and then reinstall it through your *actual* package manager (pacman/apt/etc)


## Found a bug or want to contribute to the project?

 - [Create a pull request](https://github.com/seksea/gamesneeze/compare) ([tutorial](https://github.com/yangsu/pull-request-tutorial))
 - [Report a bug](https://github.com/seksea/gamesneeze/issues/new)

## [To-do](https://github.com/seksea/gamesneeze/projects/1)

## Screenshots

![Console Output](res/console.png)
![Choms Output](res/chams.png)
