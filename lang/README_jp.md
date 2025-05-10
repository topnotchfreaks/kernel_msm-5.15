# 🚀 GitHub Actions カーネルビルドガイド

🌐 利用可能な言語: [インドネシア語 🇮🇩](README_id.md) | [英語 🇺🇸](README.md)

ようこそ！  
このリポジトリでは、**GitHub UI 経由で簡単にカーネルをビルドできる、事前構成済みの GitHub Actions ワークフロー** を提供します。

---

## 📝 クイックスタート：フォーク & セットアップ

1. **このリポジトリをフォーク**  
   右上の **Fork** ボタンをクリックして、自分のコピーを作成します。

2. **Personal Access Token (GH_TOKEN) を Secrets に追加**  
   - フォークしたリポジトリの **Settings** → **Secrets and variables** → **Actions** に移動。
   - **New repository secret** をクリック。
   - 名前を `GH_TOKEN` に設定。
   - `repo` および `workflow` 権限を持つ [GitHub Personal Access Token](https://github.com/settings/tokens) を貼り付けます。
   - **Add secret** をクリック。

---

## 🛠 ビルドの開始方法

1. **Actions** タブに移動。
2. **builder** ワークフローを選択。
3. **Run workflow** をクリックし、以下のフィールドに入力：

| フィールド | 説明 | 例 |
|:-----------|:-----|:---|
| **Custom kernel source URL** | ビルドするカーネルソースの Git URL。 | `https://github.com/topnotchfreaks/kernel_msm-5.15` |
| **Is private source?** | リポジトリがプライベートならチェック。 | （公開の場合は無視） |
| **Kernel branch** | ビルドするブランチ名（空ならデフォルト）。 | `google` |
| **Device (defconfig)** | 使用するデバイス名または defconfig。 | `gki` |
| **Kernel source name** | カーネルフォルダの名前。 | `kernel_msm-5.15` |
| **Custom localversion name** | *(オプション)* カーネルバージョンの接尾辞。 | `-testbuild` |
| **Choose KernelSU version** | *(オプション)* 使用する KernelSU のバージョン。 | `None` |

---

> ✅ **Run workflow** をクリックしてビルドを開始！

---
