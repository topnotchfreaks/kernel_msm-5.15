🚀 GitHub Actions Build Guide

This repository provides a pre-configured GitHub Actions workflow to build the kernel easily through the GitHub UI.
You can trigger builds directly from GitHub using the provided input options.

🛠 How to Start a Build
Go to the Actions tab → Select builder workflow → Click Run workflow and fill in the following:
| Field | Description | Example |
|:------|:------------|:--------|
| **Custom kernel source URL** | The Git URL of the kernel source to build. | `https://github.com/topnotchfreaks/kernel_msm-5.15` |
| **Is private source?** | Check if your repository is private. | (Leave unchecked if public) |
| **Kernel branch (default if empty)** | Branch name to build. | `codelinaro` |
| **Device (used for defconfig)** | The device name or defconfig to use. | `gki` |
| **Kernel source name** | Name of the kernel folder. | `kernel_msm-5.15` |
| **Custom localversion name** | (Optional) Local version suffix. | `-testbuild` |
| **Choose KernelSU version** | Select KernelSU version to patch (optional). | `None` |
| **Enable SUSFS** | Enable SUSFS patches. | (Check to enable) |
| **SUSFS branch to use** | SUSFS branch to pull patches from. | `gki-android13-5.15` |
| **Clang compiler to use** | Choose which Clang toolchain to use. | `Greenforce Clang` |

📋 Example Setup

- **Custom kernel source URL**: `https://github.com/topnotchfreaks/kernel_msm-5.15`
- **Kernel branch**: `codelinaro`
- **Device**: `gki`
- **Kernel source name**: `kernel_msm-5.15`
- **Custom localversion name**: *(optional)*
- **Choose KernelSU version**: `None`
- **Enable SUSFS**: *(Leave unchecked)*
- **Clang compiler to use**: `Greenforce Clang`

> ✅ Click **Run workflow** to start the build!


![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/topnotchfreaks/kernel_msm-5.15/main.yml?branch=builder)
![GitHub branch checks state](https://img.shields.io/github/checks-status/topnotchfreaks/kernel_msm-5.15/builder?branch=builder)
![License](https://img.shields.io/github/license/topnotchfreaks/kernel_msm-5.15)

**🤝 Big thanks to**:
- ![@PhamtomK12](https://github.com/PhamtomK12) Original Kernel builder Owner
- ![@ssocozy](https://github.com/ssocozy)
- ![@NVG-064](https://github.com/NVG-064)
- ![@rifsxd](https://github.com/rifsxd)
- ![@thewildjames](https://github.com/thewildjames)
