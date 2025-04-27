![English](https://github.com/topnotchfreaks/kernel_msm-5.15/README.md)
![Indonesia](https://github.com/topnotchfreaks/kernel_msm-5.15/README_id.md)

# 🚀 GitHub Actionsビルドガイド

このリポジトリは、GitHubのUIから簡単にカーネルをビルドできるように、事前設定されたGitHub Actionsのワークフローを提供しています。  
用意された入力オプションを使って、直接GitHub上でビルドを開始できます。

## 🛠 ビルドを開始する方法
**Actions**タブに移動 → **builder workflow**を選択 → **Run workflow**をクリックし、以下を入力してください：

| 項目 | 説明 | 例 |
|:-----|:-----|:---|
| **Custom kernel source URL** | ビルドしたいカーネルソースのGit URL。 | `https://github.com/topnotchfreaks/kernel_msm-5.15` |
| **Is private source?** | リポジトリがプライベートの場合はチェック。 | (公開ならチェック不要) |
| **Kernel branch (空欄時はデフォルト)** | ビルドするブランチ名。 | `codelinaro` |
| **Device (defconfigに使用)** | 使用するデバイス名またはdefconfig。 | `gki` |
| **Kernel source name** | カーネルソースフォルダ名。 | `kernel_msm-5.15` |
| **Custom localversion name** | (オプション) ローカルバージョンのサフィックス。 | `-testbuild` |
| **Choose KernelSU version** | 適用するKernelSUバージョン（オプション）。 | `None` |
| **Enable SUSFS** | SUSFSパッチを有効化。 | (チェックを入れると有効) |
| **SUSFS branch to use** | SUSFSパッチを取得するブランチ。 | `gki-android13-5.15` |
| **Clang compiler to use** | 使用するClangツールチェインを選択。 | `Greenforce Clang` |

## 📋 設定例

- **Custom kernel source URL**: `https://github.com/topnotchfreaks/kernel_msm-5.15`
- **Kernel branch**: `codelinaro`
- **Device**: `gki`
- **Kernel source name**: `kernel_msm-5.15`
- **Custom localversion name**: *(オプション)*
- **Choose KernelSU version**: `None`
- **Enable SUSFS**: *(未チェックのまま)*
- **Clang compiler to use**: `Greenforce Clang`

> ✅ **Run workflow**をクリックしてビルドを開始しましょう！

![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/topnotchfreaks/kernel_msm-5.15/main.yml?branch=builder)
![GitHub branch checks state](https://img.shields.io/github/checks-status/topnotchfreaks/kernel_msm-5.15/builder?branch=builder)
![License](https://img.shields.io/github/license/topnotchfreaks/kernel_msm-5.15)

## **🤝 特別な感謝**:
- ![@PhamtomK12](https://github.com/PhamtomK12) 元のカーネルビルダーのオーナー
- ![@ssocozy](https://github.com/ssocozy)
- ![@NVG-064](https://github.com/NVG-064)
- ![@rifsxd](https://github.com/rifsxd)
- ![@thewildjames](https://github.com/thewildjames)
- 