# 🚀 GitHub Actionsカーネルビルドガイド

🌐 他の言語: [English 🇬🇧](README.md) | [Indonesian 🇮🇩](README_id.md)

ようこそ！  
このリポジトリでは、**事前に設定されたGitHub Actionsのワークフロー**で、簡単にカーネルビルドができます。

---

## 🛠 ビルドを始める方法

1. **Actions**タブへ移動します。
2. **builder**ワークフローを選択します。
3. **Run workflow**をクリックし、以下を記入します：

| 項目 | 説明 | 例 |
|:-----|:-----|:---|
| **Custom kernel source URL** | ビルド対象のカーネルソースURL。 | `https://github.com/topnotchfreaks/kernel_msm-5.15` |
| **Is private source?** | プライベートリポジトリの場合チェック。 | (公開なら空白) |
| **Kernel branch** | ビルドするブランチ名。 | `codelinaro` |
| **Device (defconfig)** | デバイス名またはdefconfig。 | `gki` |
| **Kernel source name** | カーネルソースフォルダ名。 | `kernel_msm-5.15` |
| **Custom localversion name** | *(オプション)* ローカルバージョンサフィックス。 | `-testbuild` |
| **Choose KernelSU version** | *(オプション)* KernelSUバージョン。 | `None` |
| **Enable SUSFS** | SUSFSパッチを有効にする。 | (チェックを入れる) |
| **SUSFS branch to use** | SUSFSパッチ用のブランチ。 | `gki-android13-5.15` |

---

## 📋 設定例

- **Custom kernel source URL**: `https://github.com/topnotchfreaks/kernel_msm-5.15`
- **Kernel branch**: `codelinaro`
- **Device**: `gki`
- **Kernel source name**: `kernel_msm-5.15`
- **Custom localversion name**: *(オプション)*
- **Choose KernelSU version**: `None`
- **Enable SUSFS**: *(未チェックのまま)*

✅ **Run workflow**をクリックしてビルドを開始しましょう！

---
