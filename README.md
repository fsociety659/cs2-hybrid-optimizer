<div align="center">

# 🎯 CS2 Hybrid Optimizer (Python + C)

**Smart hybrid optimizer for Counter-Strike 2**  

<br/>

[![Python](https://img.shields.io/badge/PYTHON-8A2BE2?style=for-the-badge&logo=python&logoColor=white)](https://python.org)
&nbsp;&nbsp;
[![C](https://img.shields.io/badge/C-2E8B57?style=for-the-badge&logo=c&logoColor=white)](https://cppreference.com)

<br/>

> 🧠 Eliminates stutters, stabilizes 0.1% Low FPS and prepares Windows for perfect gameplay  

<br/>

**[🇷🇺 Русская версия](./README_RU.md)**  

</div>

---

## ⚙️ How it works (Architecture)

| Component | Role | Tech Stack |
|-----------|------|-------------|
| 🐍 **Python (brain)** | Smart interface: detects CPU threads, game path, controls logic | `psutil`, `pywin32`, `PyInstaller` |
| ⚡ **C engine (cleaner.dll)** | Silent cleaning motor: works directly with WinAPI, Windows kernel, no slow system() calls | `WinAPI`, `DirectX`, `kernel32` |

> ✅ **Python** — ease of use & control.  
> 🔥 **C** — speed & silence (no console popups, pure kernel work).

---

## 🚀 Key Features

| Feature | What it does | Effect |
|---------|--------------|--------|
| 🧠 **Smart CPU pinning** | Automatically splits logical threads by 2 (Hyper-Threading / SMT). CS2 runs on physical cores only. | Eliminates **shader stuttering** |
| 🗑️ **GPU cache reset** | Cleans `DXCache`, `GLCache` folders (NVIDIA / AMD / DirectX) | Restores smoothness after updates |
| 🧹 **Steam shader cleanup** | Deletes shader cache junk for CS2 (AppID: 730) | Faster map loading |
| 💾 **RAM standby list cleaning** | Frees up cached RAM (like RAMMap tool) | More free memory for gaming |
| 🛡️ **Windows Defender bypass** | Adds CS2 folder to antivirus exclusions | Defender won't eat CPU while playing |
| 🔒 **Lock protection** | Force closes stuck `cs2.exe` processes | No "game already running" errors |
| ⚡ **Perfect auto-launch** | Generates launch options (`-high -nojoy -threads X +fps_max 0`) and starts the game via Steam | Max FPS with zero lag |

---

## 📖 How to Use

1. 📥 **Download** `CS2_Hybrid_Optimizer.exe` from [Releases](../../releases)
2. 🖱️ **Run as Administrator**
3. 🌐 **Choose language:** `1` — English, `2` — Русский
4. 🎮 **Wait 5 seconds** — the tool does everything automatically
5. ✅ **Enjoy smooth gaming** — no stutters, no freezes

> 💡 **Note:** No need to install Python or C compilers. Everything is packed inside a single `.exe` file.

---

## ⚖️ Disclaimer (MIT License)

**© 2025 CS2 Hybrid Optimizer**

This software is provided "AS IS", without any warranties.

The author is not responsible for:
- ❌ game crash during an important round (yes, it hurts, but happens);
- ❌ flickering lights in your apartment (power outage — not related to software);
- ❌ VAC ban (code is clean, doesn't touch game memory, only OS).

You use this program **at your own risk**.  
But the code is fully open — feel free to check it yourself.

---

<div align="center">

**💻 Made for gamers, by a gamer. No bloat, just smooth FPS.**

</div>
