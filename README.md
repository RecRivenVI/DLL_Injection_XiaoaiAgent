# DLL Injector for XiaoaiAgent & XiaomiAICreator

A lightweight Windows DLL injection utility that injects `msimg32.dll` into the **XiaoaiAgent (PC 版小爱同学)** and **XiaomiAICreator (小米AI创作)** processes. The injector uses classic `CreateProcess` + `CreateRemoteThread` + `LoadLibrary` injection technique.

> This project is for educational and research purposes only.

## Features

- **Two injectors in one project** — targets both XiaoaiAgent and XiaomiAICreator
- **Registry-based target discovery** — automatically locates the target application from Windows registry (`App Paths`)
- **Minimal and clean codebase** — core injection logic in a single header file
- **Static linking** — standalone executables with no runtime dependencies
- **Embedded metadata** — version info and custom icons via Windows resource files
- **No admin required** — runs at user privilege level for per-user installations

## How It Works

1. The injector reads the target application's install path from the registry at `HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\<AppName>.exe`
2. It launches the target process in a **suspended state** (`CREATE_SUSPENDED`)
3. It allocates memory in the target process via `VirtualAllocEx`
4. It writes the full path of `msimg32.dll` into that memory
5. It creates a remote thread that calls `LoadLibraryA` with the DLL path as argument, forcing the target to load the DLL
6. After a short wait (3s), it resumes the target process's main thread

The `msimg32.dll` must be placed in the **same directory** as the injector executable. The DLL itself is not included in this repository.

## Project Structure

```
.
├── src/
│   ├── XiaoaiAgentInjector.cpp      # Entry point for XiaoaiAgent injector
│   └── XiaomiAICreatorInjector.cpp  # Entry point for XiaomiAICreator injector
├── include/
│   └── InjectorCore.h               # Core injection logic (header-only)
├── resources/
│   ├── XiaoaiAgent.ico              # Icon for XiaoaiAgent injector
│   ├── XiaoaiAgent.rc               # Resource script with VERSIONINFO
│   ├── XiaomiAICreator.ico          # Icon for XiaomiAICreator injector
│   └── XiaomiAICreator.rc           # Resource script with VERSIONINFO
├── build.ps1                        # PowerShell build script (MinGW)
├── LICENSE                          # MIT License
└── README.md                        # This file
```

## Prerequisites

- **MinGW-w64** (with `g++` and `windres`) — install via [MSYS2](https://www.msys2.org/) or a MinGW-w64 toolchain of your choice
- **Windows SDK** — headers are included with MinGW-w64
- **msimg32.dll** — obtain from the DLL author (ChsBuffer). Place it next to the injector executable.

## Building

Open a PowerShell terminal and run:

```powershell
.\build.ps1
```

This will produce two executables:
- `XiaoaiAgentInjector.exe`
- `XiaomiAICreatorInjector.exe`

### Build Flags

The build script uses the following flags:
- `-static -static-libgcc -static-libstdc++` — statically link runtime libraries for standalone executables
- `-mwindows` — Windows subsystem (no console window by default)
- `-luser32` — link against `user32` for message boxes
- `-finput-charset=UTF-8 -fexec-charset=GBK` — UTF-8 source, GBK executable encoding for Chinese text

## Usage

1. Place `msimg32.dll` in the same directory as the injector executable
2. Run the injector. The target application will launch automatically with the DLL injected
3. If `msimg32.dll` is missing, the injector will show an error message

> **Note:** The target application must be installed for the registry path to exist. Per-user installations of XiaoaiAgent may require running the injector as the same user.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Author

**RavenYin** — Copyright (c) 2026
