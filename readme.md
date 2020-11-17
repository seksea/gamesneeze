<p align="center">
  <img src="/res/logo.png" alt="gamesneeze-linux">
  <a href="/LICENSE"><img src="https://img.shields.io/badge/License-MIT-green.svg" alt="MIT License"></a>
  <a><img src="https://img.shields.io/badge/OS-Linux-green.svg" alt="Linux"></a>
  <a><img src="https://img.shields.io/badge/Cheat-CS:GO-green.svg" alt="CS:GO cheat"></a>
  <a><img src="https://img.shields.io/badge/State-Unfinished-red.svg" alt="Unfinished"></a>
  <a><img src="https://img.shields.io/badge/Detection-Unknown-yellow.svg" alt="Detection: Unknown"></a>
</p>

An open source cheat for Counter-Strike: Global Offensive on linux.

## Current Features
- Basic GDB injector
- SwapWindow & PollEvent Hooked
- ImGui

## How to use
```
git clone https://github.com/seksea/gamesneeze
cd gamesneeze
chmod +x build.sh
sudo ./build.sh
# (build.sh will uninject before it's built and ask if you want to inject after it's built, use ./inject.sh for just injecting on its own)
```

## Todo
- [ ] Game Interfaces
- [ ] Game Classes
- [ ] Game Hooks

![Current Menu](/res/currentMenu.png)
![Console Output](/res/consoleOutput.png)