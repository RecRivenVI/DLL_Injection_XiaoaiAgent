# DLL Injector —— 小爱同学 & 小米AI创作 注入器

一个轻量级的 Windows DLL 注入工具，用于将 `msimg32.dll` 注入到 **PC 版小爱同学** 和 **小米AI创作 PC 版** 进程中。采用经典的 `CreateProcess` + `CreateRemoteThread` + `LoadLibrary` 注入技术实现。

> 本项目仅供学习和研究参考，请勿用于非法用途。

## 功能特点

- **双注入器合一** — 同时支持小爱同学和小米AI创作两个目标程序
- **注册表路径自动发现** — 从 Windows 注册表 (`App Paths`) 自动定位目标程序安装位置
- **极简代码** — 核心注入逻辑全部封装在单个头文件中，易于理解和修改
- **静态链接** — 生成的独立可执行文件无运行时依赖
- **嵌入元数据** — 通过 Windows 资源文件嵌入版本信息与自定义图标
- **无需管理员权限** — 用户权限即可运行（适用于当前用户安装的程序）

## 工作原理

1. 注入器从注册表 `HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\<程序名>.exe` 读取目标程序安装路径
2. 以**挂起状态** (`CREATE_SUSPENDED`) 启动目标进程
3. 通过 `VirtualAllocEx` 在目标进程中分配内存
4. 将 `msimg32.dll` 的完整路径写入该内存
5. 创建远程线程，以 DLL 路径为参数调用 `LoadLibraryA`，强制目标进程加载 DLL
6. 等待 3 秒后恢复目标进程主线程执行

`msimg32.dll` 必须放置在注入器可执行文件的**同级目录**下。本仓库不包含该 DLL 文件。

## 项目结构

```
.
├── src/
│   ├── XiaoaiAgentInjector.cpp      # 小爱同学注入器入口
│   └── XiaomiAICreatorInjector.cpp  # 小米AI创作注入器入口
├── include/
│   └── InjectorCore.h               # 核心注入逻辑（头文件）
├── resources/
│   ├── XiaoaiAgent.ico              # 小爱同学注入器图标
│   ├── XiaoaiAgent.rc               # 小爱同学资源脚本（含版本信息）
│   ├── XiaomiAICreator.ico          # 小米AI创作注入器图标
│   └── XiaomiAICreator.rc           # 小米AI创作资源脚本（含版本信息）
├── build.ps1                        # PowerShell 编译脚本
├── LICENSE                          # MIT 许可证
└── README.md                        # 说明文档（英文）
```

## 环境要求

- **MinGW-w64**（含 `g++` 和 `windres`）— 通过 [MSYS2](https://www.msys2.org/) 或其他 MinGW-w64 工具链安装
- **Windows SDK** — MinGW-w64 已自带所需头文件
- **msimg32.dll** — 请向 DLL 作者 ChsBuffer 获取，并放置于注入器同级目录

## 编译方法

打开 PowerShell 终端并运行：

```powershell
.\build.ps1
```

编译完成后会生成两个可执行文件：
- `XiaoaiAgentInjector.exe` — 小爱同学注入器
- `XiaomiAICreatorInjector.exe` — 小米AI创作注入器

### 编译选项说明

- `-static -static-libgcc -static-libstdc++` — 静态链接运行时库，生成独立可执行文件
- `-mwindows` — Windows 子系统（默认不显示控制台窗口）
- `-luser32` — 链接 `user32` 库以支持消息弹窗
- `-finput-charset=UTF-8 -fexec-charset=GBK` — 源代码 UTF-8 编码，生成 GBK 编码的可执行文件（确保中文正常显示）

## 使用方法

1. 将 `msimg32.dll` 放入注入器可执行文件的同级目录
2. 直接运行注入器，目标程序将自动启动并完成 DLL 注入
3. 如果缺少 `msimg32.dll`，注入器会弹出错误提示

> **注意：** 目标程序必须已安装，注册表路径才存在。如果小爱同学是当前用户安装的，请以相同用户身份运行注入器。

## 许可证

本项目基于 MIT 许可证发布。详见 [LICENSE](LICENSE) 文件。

## 作者

**RavenYin** — 版权所有 (c) 2026
