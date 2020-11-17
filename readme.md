<p align="center">
  <div id="title">
    <h1 style="color: #eeeeee">game<span style="color:#6CC312">sneeze</span>-linux</h1>
  </div>

  <img src="https://img.shields.io/badge/License-MIT-green.svg" alt="MIT License">
  <img src="https://img.shields.io/badge/OS-Linux-green.svg" alt="Linux">
  <img src="https://img.shields.io/badge/Cheat-CS:GO-green.svg" alt="CS:GO cheat">
  <img src="https://img.shields.io/badge/State-Unfinished-red.svg" alt="Unfinished">
  <img src="https://img.shields.io/badge/Detection-Unknown-yellow.svg" alt="Detection: Unknown">
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
# (build.sh will ask if you want to inject after it's built, use ./inject.sh for just injecting on its own)
```