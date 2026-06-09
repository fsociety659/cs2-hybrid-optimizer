<div align="center">

# 🎯 CS2 Hybrid Optimizer

### Hybrid Counter-Strike 2 Performance Optimizer (Python + C)

![GitHub release](https://img.shields.io/github/v/release/yourname/CS2-Hybrid-Optimizer?style=for-the-badge)
![Platform](https://img.shields.io/badge/Platform-Windows%2010%20%7C%2011-blue?style=for-the-badge)
![Language](https://img.shields.io/badge/Python%20%2B%20C-Hybrid-green?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)
![CS2](https://img.shields.io/badge/Counter--Strike%202-Optimized-orange?style=for-the-badge)

### 🚀 Eliminate Stutters • Stabilize FPS • Clean Your System Before Launch

 Выберите язык / Select Language |
|:---:|
| en **English** (Current) &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; [ru **Russia**](./README_RU.md) |

</div>

---

## 📖 Overview

**CS2 Hybrid Optimizer** is an open-source utility designed to improve the overall smoothness of **Counter-Strike 2**.

The project combines the flexibility of **Python** with the speed of native **C/WinAPI** code to perform system cleanup, cache maintenance, CPU affinity optimization, memory cleanup, and automated game launching.

The primary goal is to improve:

* 🎯 Frame pacing
* 📈 0.1% Low FPS
* ⚡ Shader compilation behavior
* 🧹 System cleanliness before launch
* 🎮 Overall gameplay smoothness

---

## 🏗 Architecture

| Component                   | Role                                                                                                                                 | Technologies                          |
| --------------------------- | ------------------------------------------------------------------------------------------------------------------------------------ | ------------------------------------- |
| 🐍 Python (Brain)           | Handles application logic, CPU thread detection, Windows Registry scanning, path discovery, launch configuration, and user interface | `ctypes`, `winreg`, `multiprocessing` |
| ⚙️ C Engine (`cleaner.dll`) | Performs high-speed cache cleanup directly through Windows API without relying on slow shell calls                                   | `WinAPI`, `kernel32`                  |

---

## ✨ Features

| Feature                          | What It Does                                                                                            | Effect                                           |
| -------------------------------- | ------------------------------------------------------------------------------------------------------- | ------------------------------------------------ |
| 🧠 Smart CPU Core Allocation     | Detects CPU threads and divides them by two to target physical cores only (SMT / Hyper-Threading aware) | Reduces shader-compilation related stutters      |
| 🎮 GPU Cache Reset               | Cleans DXCache and GLCache folders used by NVIDIA, AMD and DirectX                                      | Restores smoothness after driver or game updates |
| 🔥 Steam Shader Cleanup          | Removes obsolete shader data from Steam AppID 730 cache                                                 | Faster map loading                               |
| 🧹 Memory Optimization           | Calls `SetProcessWorkingSetSize()` to trim process working sets                                         | Frees unnecessary memory usage                   |
| 🛡 Defender Exclusion Automation | Automatically adds CS2 directory to Windows Defender exclusions                                         | Prevents background scanning during gameplay     |
| 🚨 Anti-Hang Protection          | Forcefully terminates stuck `cs2.exe` processes before launch                                           | Prevents launch conflicts                        |
| 🚀 Perfect Launch Generator      | Generates optimized launch options and starts CS2 through Steam                                         | Consistent startup configuration                 |

---

## ⚡ Generated Launch Parameters

The optimizer automatically creates launch options similar to:

```bash
-high
-nojoy
-threads X
+fps_max 0
```

Where **X** is automatically calculated according to the number of detected physical CPU cores.

---

## 🔬 How It Works

1. Detects installed Counter-Strike 2 location via Windows Registry.
2. Terminates stuck game instances.
3. Cleans GPU caches.
4. Cleans Steam shader cache.
5. Optimizes memory usage.
6. Configures Windows Defender exclusions.
7. Calculates optimal thread count.
8. Generates launch parameters.
9. Optionally launches Counter-Strike 2 through Steam.

---

## 🚀 How To Use

### 1️⃣ Download

Download the latest:

```text
CS2_Hybrid_Optimizer.exe
```

from the Releases section.

---

### 2️⃣ Run as Administrator

Right-click:

```text
Run as Administrator
```

Administrator privileges are required for cache cleanup and Defender configuration.

---

### 3️⃣ Select Language

```text
1 - English
2 - Russian
```

---

### 4️⃣ Wait for Optimization

The native C engine will:

* Clean caches
* Prepare the operating system
* Remove obsolete shader data
* Optimize memory usage

---

### 5️⃣ Launch Counter-Strike 2

At the end you will see:

```text
Launch Counter-Strike 2 now? (Y/N)
```

| Input | Result                             |
| ----- | ---------------------------------- |
| Y     | Launch CS2 with optimized settings |
| Enter | Launch CS2 with optimized settings |
| N     | Exit application                   |

---

## 📋 Requirements

| Requirement      | Version         |
| ---------------- | --------------- |
| Operating System | Windows 10 / 11 |
| Architecture     | x64             |
| Steam            | Installed       |
| Counter-Strike 2 | Installed       |
| Permissions      | Administrator   |

---

## 🔒 Safety

This project:

✅ Does NOT inject into CS2

✅ Does NOT modify game memory

✅ Does NOT hook VAC-protected modules

✅ Does NOT alter game files

✅ Works exclusively with Windows and Steam cache data

---

## 📊 Tech Stack

### Python Layer

```text
ctypes
winreg
multiprocessing
subprocess
```

### Native Layer

```text
C
WinAPI
kernel32
shell32
```

---

## 📜 License

MIT License

### Funny Legal Disclaimer™

The author is **not responsible** for:

* 💀 Lost competitive matches
* 💀 Missed AWP shots
* 💀 Random power outages
* 💀 Your teammate rushing Mid every round
* 💀 Internet provider disasters
* 💀 Cosmic radiation flipping a bit in RAM

The software does **not** modify Counter-Strike 2 memory, game files, VAC modules, or gameplay behavior.

If you get banned, lag, lose ELO, miss a clutch, or your room light starts blinking dramatically during overtime...

that's between you, Valve, physics, and destiny.

---

<div align="center">

### ⭐ Star the repository if it improved your CS2 experience

Made with ☕, Python and WinAPI.

</div>
