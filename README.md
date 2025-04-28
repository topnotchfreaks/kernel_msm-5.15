# 🚀 GitHub Actions Kernel Build Guide

🌐 Available Languages: [Indonesian 🇮🇩](README_id.md) | [Japanese 🇯🇵](README_jp.md)

Welcome!  
This repository provides a **pre-configured GitHub Actions workflow** to easily build kernels through the GitHub UI.

You can start builds directly from GitHub using a few simple input options!

---

## 🛠 How to Start a Build

1. Go to the **Actions** tab.
2. Select the **builder** workflow.
3. Click **Run workflow** and fill in the following:

| Field | Description | Example |
|:------|:------------|:--------|
| **Custom kernel source URL** | Git URL of the kernel source you want to build. | `https://github.com/topnotchfreaks/kernel_msm-5.15` |
| **Is private source?** | Check if your repository is private. | (Leave unchecked if public) |
| **Kernel branch** | Branch name to build (default if empty). | `codelinaro` |
| **Device (defconfig)** | Device name or defconfig to use. | `gki` |
| **Kernel source name** | Name for the kernel folder. | `kernel_msm-5.15` |
| **Custom localversion name** | *(Optional)* Suffix for the kernel version. | `-testbuild` |
| **Choose KernelSU version** | *(Optional)* KernelSU version to patch. | `None` |

---

## 📋 Example Setup

| Option | Value |
|:------|:------|
| Custom kernel source URL | `https://github.com/topnotchfreaks/kernel_msm-5.15` |
| Kernel branch | `codelinaro` |
| Device | `gki` |
| Kernel source name | `kernel_msm-5.15` |
| Custom localversion name | *(Optional)* |
| Choose KernelSU version | `None` |

> ✅ Click **Run workflow** to start the build!

---

## 📈 Status

![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/topnotchfreaks/kernel_msm-5.15/main.yml?branch=builder)
![GitHub branch checks state](https://img.shields.io/github/checks-status/topnotchfreaks/kernel_msm-5.15/builder?branch=builder)
![License](https://img.shields.io/github/license/topnotchfreaks/kernel_msm-5.15)

---

## 🤝 Special Thanks

- [@PhamtomK12](https://github.com/PhamtomK12) - Original Kernel Builder Owner
- [@ssocozy](https://github.com/ssocozy)
- [@NVG-064](https://github.com/NVG-064)
- [@rifsxd](https://github.com/rifsxd)
- [@thewildjames](https://github.com/thewildjames)

---
