<div align="center">

# CS2 Hybrid Optimizer

### Hybrid Counter-Strike 2 Performance Optimizer (Python + C)

![GitHub release](https://img.shields.io/github/v/release/yourname/CS2-Hybrid-Optimizer?style=for-the-badge)
![Platform](https://img.shields.io/badge/Platform-Windows%2010%20%7C%2011-blue?style=for-the-badge)
![Language](https://img.shields.io/badge/Python%20%2B%20C-Hybrid-green?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)
![CS2](https://img.shields.io/badge/Counter--Strike%202-Optimized-orange?style=for-the-badge)

### Eliminate Stutters - Stabilize FPS - Clean Your System Before Launch

| Select Language |
|:---:|
| **English** (current) &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; [**Russian**](./README_RU.md) |

</div>

---

## Overview

**CS2 Hybrid Optimizer** is an open-source utility designed to improve the overall smoothness of **Counter-Strike 2**.

The project combines the flexibility of **Python** with the speed of native **C/WinAPI** code to perform system cleanup, cache maintenance, OS-level scheduler tuning, and automated game launching.

The primary goal is to improve:

- Frame pacing and frame-time consistency
- 0.1% Low FPS
- Shader compilation behavior
- System cleanliness before launch
- Overall gameplay smoothness

---

## Architecture

| Component | Role | Technologies |
| --- | --- | --- |
| Python (Brain) | Application logic, CPU thread detection, Windows Registry scanning, path discovery, launch configuration, logging, and the console UI | `ctypes`, `winreg`, `multiprocessing`, `subprocess` |
| C Engine (`cleaner.dll`) | Performs cache cleanup, RAM standby list purging, and timer resolution requests directly through the Windows/NT API | `WinAPI`, `ntdll`, `kernel32`, `shell32` |

---

## Features

### Cache & Memory

| Feature | What It Does | Effect |
| --- | --- | --- |
| GPU Cache Reset | Cleans D3DSCache, NVIDIA DXCache/GLCache, and AMD DxCache/OglCache/VkCache folders | Restores smoothness after driver or game updates |
| Steam Shader Cleanup | Removes obsolete shader data from Steam AppID 730's cache | Faster map loading |
| RAM Standby List Purge | Calls the undocumented `NtSetSystemInformation` routine to release cached RAM pages held in the standby list | Frees memory without forcing other running apps to page back in from disk |
| High-Precision System Timer | Requests the highest available timer resolution via `NtSetTimerResolution` (typically ~0.5ms instead of Windows' default ~15.6ms) | Reduces frame-pacing jitter; released automatically when the optimizer exits |

### System-Level Tuning

| Feature | What It Does | Effect |
| --- | --- | --- |
| Smart CPU Core Allocation | Detects CPU threads and divides by two to target physical cores (SMT / Hyper-Threading aware) | Reduces shader-compilation related stutters |
| High Performance Power Plan | Activates Windows' High Performance power scheme | Prevents CPU throttling during gameplay |
| Xbox GameBar / GameDVR Disable | Disables `AppCaptureEnabled` and `GameDVR_Enabled` registry keys | Removes background recording/capture overhead |
| Win32PrioritySeparation Tuning | Sets the Windows scheduler to short, fixed quantums favoring the foreground app | Improves responsiveness of the active window |
| MMCSS Responsiveness Tweak | Sets `SystemResponsiveness` to 0 so background tasks no longer reserve CPU time during gameplay | More CPU headroom for `cs2.exe` |
| Fullscreen Optimizations Disable | Disables DX exclusive-fullscreen optimization specifically for `cs2.exe` | Can reduce input latency in fullscreen mode |
| DNS Cache Flush | Runs `ipconfig /flushdns` | Clears stale DNS entries before connecting to matchmaking |

### Launch & Convenience

| Feature | What It Does | Effect |
| --- | --- | --- |
| Defender Exclusion Automation | Adds the CS2 install directory to Windows Defender exclusions (shown in console and logged) | Prevents background scanning during gameplay |
| Anti-Hang Protection | Forcefully terminates stuck `cs2.exe` processes before launch | Prevents launch conflicts |
| autoexec.cfg Generator | Writes a tuned `autoexec.cfg` (network rates, interpolation, fps_max) into the CS2 cfg folder | Consistent in-game settings on every launch |
| Perfect Launch Generator | Generates optimized launch options and starts CS2 through Steam | Consistent startup configuration |
| Post-Launch Priority Boost | A few seconds after launch, sets `cs2.exe`'s process priority to High via PowerShell | Smoother CPU scheduling for the game process |

---

## Generated Launch Parameters

The optimizer automatically creates launch options similar to:

```bash
-high
-nojoy
-fullscreen
-threads X
+fps_max 0
+exec autoexec
```

Where **X** is automatically calculated according to the number of detected physical CPU cores.

---

## How It Works

1. Calculates optimal launch options based on detected CPU threads/cores.
2. Detects the installed Counter-Strike 2 location via the Windows Registry and adds the install folder to Windows Defender exclusions.
3. Terminates any stuck `cs2.exe` process before starting.
4. Estimates current cache size for the summary report.
5. Calls the native C engine to clean GPU shader caches, clean the Steam shader cache, purge the RAM standby list, and request a high-precision system timer.
6. Flushes the DNS cache and switches Windows to the High Performance power plan.
7. Disables Xbox GameBar / GameDVR, and tunes `Win32PrioritySeparation` and `SystemResponsiveness` for foreground-app priority.
8. Generates `autoexec.cfg` and disables Fullscreen Optimizations for CS2, if the install was found.
9. Displays a summary and, on confirmation, launches Counter-Strike 2 through Steam - boosting its process priority shortly after launch.

---

## How To Use

### 1. Download

Download the latest:

```text
CS2_Hybrid_Optimizer.exe
```

from the Releases section.

### 2. Run as Administrator

Right-click:

```text
Run as Administrator
```

Administrator privileges are required for cache cleanup, registry tuning, and Defender configuration.

### 3. Select Language

```text
1 - English
2 - Russian
```

### 4. Wait for Optimization

The native C engine and Python layer will:

- Clean caches
- Purge the RAM standby list
- Tune system-level scheduler and timer settings
- Prepare the operating system
- Remove obsolete shader data

### 5. Launch Counter-Strike 2

At the end you will see:

```text
Launch Counter-Strike 2 now? (Y/N)
```

| Input | Result |
| --- | --- |
| Y | Launch CS2 with optimized settings |
| Enter | Launch CS2 with optimized settings |
| N | Exit application |

---

## Requirements

| Requirement | Version |
| --- | --- |
| Operating System | Windows 10 / 11 |
| Architecture | x64 |
| Steam | Installed |
| Counter-Strike 2 | Installed |
| Permissions | Administrator |

---

## Safety

This project:

- Does NOT inject into CS2
- Does NOT modify game memory
- Does NOT hook VAC-protected modules
- Does NOT alter game files
- Works exclusively with Windows/Steam cache data and OS-level system settings (registry, power plan, scheduler)

---

## Tech Stack

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
ntdll
kernel32
shell32
```

---

## License

MIT License

### Funny Legal Disclaimer

The author is **not responsible** for:

- Lost competitive matches
- Missed AWP shots
- Random power outages
- Your teammate rushing Mid every round
- Internet provider disasters
- Cosmic radiation flipping a bit in RAM

The software does **not** modify Counter-Strike 2 memory, game files, VAC modules, or gameplay behavior.

If you get banned, lag, lose ELO, miss a clutch, or your room light starts blinking dramatically during overtime, that's between you, Valve, physics, and destiny.

---

<div align="center">

### Star the repository if it improved your CS2 experience

Made with coffee, Python, and WinAPI.

</div>