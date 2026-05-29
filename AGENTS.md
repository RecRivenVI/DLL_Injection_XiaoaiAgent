## 全局注意事项（Commit 规范）
所有由 Agent 产生或代执行的 Git 提交必须严格遵守以下规范，不得例外：
### 1. Commit Message 格式
必须使用 Conventional Commits 规范：
```
type(scope): 中文描述
```
要求如下：
* `type` 必须使用标准类型（如 feat / fix / refactor / docs / style / perf / test / build / ci / chore / revert 等）
* `scope` 必须存在，且必须为英文模块名
* 严禁省略 scope（禁止出现无 scope 的提交）
* 标题必须使用中文描述
* 标题必须概括本次提交的核心变更
* 不允许冗长流水账式描述
* 不允许混合多主题描述（除非确实属于同一逻辑变更）
---
### 2. Commit Body 规范
每个提交必须包含 body（提交正文），要求如下：
* 必须列出本次提交涉及的主要文件
* 同类文件允许合并描述
* 必须说明每类文件的大致修改内容
* 描述需简洁清晰（中文）
* 不要求逐行解释，但必须覆盖关键变更范围
* 不得遗漏核心变更文件
---
### 3. 提交签名要求
所有提交必须使用 SSH 签名：
* 必须使用 `--gpg-sign=~/.ssh/id_ed25519.pub`
* 提交必须包含 `gpgsig` 字段（用于证明签名已写入 commit object）
---
### 4. 时间戳要求
所有提交必须保持作者时间一致性：
* 如涉及 rebase 或 amend 操作，必须使用 `--committer-date-is-author-date`
* 确保 Committer Date 与 Author Date 完全一致
* 不得引入人为时间漂移
---
### 5. 约束原则（非常重要）
* 禁止通过提交行为改变代码逻辑以“顺带修复格式”
* 提交只能表达实际变更内容，不得混入无关修改
* 一个 Commit 应对应一个清晰的逻辑变更单元
* 不得为了格式化 commit message 而拆分或合并提交历史
* 不得修改 Git 历史结构（仅限新增提交）