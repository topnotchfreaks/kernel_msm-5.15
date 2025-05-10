# 🚀 GitHub Actions Kernel Build Guide

🌐 Available Languages: [Indonesian 🇮🇩](lang/README_id.md) | [Japanese 🇯🇵](lang/README_jp.md) | [Portugués 🇧🇷](lang/README_pt.md) | [Espanhol 🇪🇸](lang/README_es.md)

Welcome!  
This repository provides a **pre-configured GitHub Actions workflow** to easily build kernels through the GitHub UI.

---

## 📝 Quick Start: Fork & Set Up

1. **Fork this repository**  
   Click the **Fork** button at the top right of this page to create your own copy.

2. **Add a Personal Access Token (GH_TOKEN) to Secrets**  
   - Go to your forked repository’s **Settings** → **Secrets and variables** → **Actions**.
   - Click **New repository secret**.
   - Name it `GH_TOKEN`.
   - Paste your [GitHub Personal Access Token](https://github.com/settings/tokens) with `repo` and `workflow` permissions.
   - Click **Add secret**.

---

## 🛠 How to Start a Build

1. Go to the **Actions** tab.
2. Select the **builder** workflow.
3. Click **Run workflow** and fill in the following:

| Field | Description | Example |
|:------|:------------|:--------|
| **Custom kernel source URL** | Git URL of the kernel source you want to build. | `https://github.com/topnotchfreaks/kernel_msm-5.15` |
| **Is private source?** | Check if your repository is private. | (Leave unchecked if public) |
| **Kernel branch** | Branch name to build (default if empty). | `google` |
| **Device (defconfig)** | Device name or defconfig to use. | `gki` |
| **Kernel source name** | Name for the kernel folder. | `kernel_msm-5.15` |
| **Custom localversion name** | *(Optional)* Suffix for the kernel version. | `-testbuild` |
| **Choose KernelSU version** | *(Optional)* KernelSU version to patch. | `None` |

---

> ✅ Click **Run workflow** to start the build!

---

## 📈 Status

![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/topnotchfreaks/kernel_msm-5.15/main.yml?branch=builder)
![License](https://img.shields.io/github/license/topnotchfreaks/kernel_msm-5.15)

---

## 🤝 Special Thanks

- [@PhamtomK12](https://github.com/PhamtomK12) - Original Kernel Builder Owner
- [@ssocozy](https://github.com/ssocozy)
- [@NVG-064](https://github.com/NVG-064)
- [@rifsxd](https://github.com/rifsxd)
- [@thewildjames](https://github.com/thewildjames)

---
