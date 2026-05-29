# AGENTS.md

## 全局注意事项

- **提交规范**：所有提交必须遵循 Conventional Commits（type(scope): 中文描述，scope 使用英文模块名），提交标题需概括所有变更中的重点变更，正文需列出所有变动文件（同类文件可合并列举）并说明大致修改内容。
  - **SSH 签名**：提交必须使用 SSH 密钥签名（`--gpg-sign=~/.ssh/id_ed25519.pub`）。
  - **保留时间戳**：rebase/squash 时使用 `--committer-date-is-author-date` 参数，确保 Committer Date 与 Author Date 一致。
  - **签名验证**：`git verify-commit` 因环境缺少 `gpg.ssh.allowedSignersFile` 会报错属正常现象，只要 commit object 中包含 `gpgsig` 字段即视为已签名。

## 构建

- `pwsh build.ps1` — 需要 **MinGW-w64**（`g++`、`windres`），不能使用 MSVC。
- 源代码为 UTF-8 编码；编译时转为 GBK（`-fexec-charset=GBK`）以支持中文控制台输出。
- 产物：`XiaoaiAgentInjector.exe` + `XiaomiAICreatorInjector.exe`（静态链接，无运行时依赖）。
- 构建产物（`*.exe`、`*.o`）已加入 `.gitignore`。

## 架构

- 每个注入器是 `src/` 下的一个精简 `main()`，调用 `include/InjectorCore.h` 中的 `RunInjector()`，传参因目标而异。
- `InjectorCore.h` 是**纯头文件**——所有逻辑（注册表查找、CreateRemoteThread 注入）均为内联实现。
- 目标程序路径通过注册表键 `HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\<程序名>.exe` 自动发现。
- 无需管理员权限；默认不显示控制台窗口（`-mwindows`）。

## DLL 要求

- **`msimg32.dll` 不在本仓库中。** 需自行获取并放置于注入器 `.exe` 同级目录。
- DLL 作者为 ChsBuffer（错误提示中已引用）。

## 资源文件

- `.rc` 文件使用 `#pragma code_page(65001)`（UTF-8）嵌入自定义图标和 VERSIONINFO。
- `windres -c 65001` 标志与源代码编码保持一致。

## 缺失项

- 无测试、无 CI、无 lint/typecheck 配置。这是一个小型的 Windows 仅限实用工具项目。
