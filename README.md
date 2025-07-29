# 🔧 Kernel Build Workflow for Android Devices

**A customizable GitHub Actions workflow for building Linux Kernel 5.15 GKI with KernelSU (KSU) and SUSFS support**

---

## ⚠️ **IMPORTANT: Device Compatibility Warning**

> **🚨 This workflow is designed for building kernels for specific Android devices!**

To use this workflow for a different device, you must update the following:

| Component | What to Change |
|-----------|---------------|
| **🔗 Kernel Source** | Update `kernelSourceURL` and `kernelBranch` to match your device's kernel source |
| **🔧 Defconfig** | Set `kernelDevice` to your device's defconfig (e.g., `sm8450_defconfig`) |
| **📝 Patches** | Modify or add device-specific patches for compatibility |
| **🔐 KSU/SUSFS** | Ensure KernelSU and SUSFS patches align with your kernel and Android version |
| **📦 AnyKernel3** | Use a device-specific AnyKernel3 template for flashing |
| **⚙️ Build Configs** | Adjust compiler flags, LTO mode, and optimizations for your hardware |

### ⚡ **Risks of Improper Usage:**
- ❌ Build failures
- ❌ Incompatible kernel images
- ❌ Device bootloops
- ❌ Potential hardware damage

**💡 Always test thoroughly on your device before widespread use!**

---

## 📋 **What is this?**

A GitHub Actions workflow to build a **Linux Kernel 5.15** for Android devices, with optional support for **KernelSU (KSU)** and **SUSFS** for advanced root functionality. It produces flashable ZIP files using **AnyKernel3**.

## ✨ **Key Features**

| Feature | Description |
|---------|-------------|
| 🐧 **Linux Kernel 5.15** | Stable kernel optimized for Android 13 |
| 🤖 **Automated Builds** | GitHub Actions automates kernel compilation |
| 🔐 **KSU + SUSFS** | Optional KernelSU with SUSFS for root and advanced filesystem features |
| ⚙️ **LTO Support** | Choose between Thin or Full LTO for performance optimization |
| 📦 **Flashable ZIP** | Ready-to-flash AnyKernel3 ZIPs for recovery installation |
| 📱 **Telegram Notifications** | Optional Telegram integration for build status updates |

---

## 🚀 **How to Use (GitHub Actions)**

### Step 1: Fork or Clone the Repository
1. Fork this repository by clicking the **"Fork"** button, or clone it to your own repository.
2. Ensure you have a GitHub account with Actions enabled.

### Step 2: Configure Workflow Inputs
1. Go to the **Actions** tab in your repository.
2. Select the **"Test Build"** workflow.
3. Click **"Run workflow"** and provide the following inputs:

| Input | Description | Default Value |
|-------|-------------|---------------|
| `kernelSourceURL` | URL of the kernel source repository | `https://github.com/topnotchfreaks/kernel_msm-5.15` |
| `kernelBranch` | Kernel source branch | `codelinaro` |
| `kernelDevice` | Device defconfig (e.g., `gki_defconfig`) | `gki` |
| `localVersion` | Custom kernel version suffix (e.g., `-mybuild`) | `""` (empty) |
| `buildKSU` | Build KSU variant? | `true` (builds both KSU and non-KSU variants) |
| `ltoMode` | LTO optimization mode | `Thin` (options: `Thin`, `Full`) |

### Step 3: Run the Workflow
- Click **"Run workflow"** to start the build process.
- The workflow builds:
  - A **non-KSU** kernel variant.
  - A **KSU** variant (if `buildKSU` is `true`).
- Build time is typically 20-40 minutes, depending on the LTO mode and hardware.

### Step 4: Download Artifacts
- After the build completes, go to the workflow run summary in the **Actions** tab.
- Download the following artifacts:
  - Individual kernel images (`kernel-noksu` and `kernel-ksu`).
  - A flashable ZIP file (`Kernel-5.15_YYYY-MM-DD.zip`).
- Flash the ZIP file via a custom recovery (e.g., TWRP or OrangeFox).

---

## 📱 **Telegram Integration (Optional)**

Receive build status notifications and artifacts directly on Telegram.

### Setup Instructions:
1. **Create a Telegram Bot**:
   - Message [@BotFather](https://t.me/BotFather) on Telegram.
   - Follow the instructions to create a bot and obtain a `TELEGRAM_BOT_TOKEN`.
2. **Get Your Chat ID**:
   - Message your bot or a service like [@GetIDsBot](https://t.me/GetIDsBot) to get your `TELEGRAM_USER_ID`.
3. **Add Secrets to GitHub**:
   - Go to your repository → **Settings** → **Secrets and variables** → **Actions**.
   - Add two secrets:
     - `TELEGRAM_BOT_TOKEN`: Your bot token from BotFather.
     - `TELEGRAM_USER_ID`: Your Telegram chat ID.
4. **Enable Notifications**:
   - The workflow will automatically send build results (success or failure) to your Telegram chat.

---

## 🛠 **Workflow Details**

### Build Process
1. **Setup Workspace**: Installs dependencies (Clang, LLVM, etc.) and sets up the build environment.
2. **Clone Kernel Source**: Clones the specified kernel source and branch.
3. **Download Clang**: Fetches the latest Clang toolchain from `topnotchfreaks/clang`.
4. **Configure Environment**: Sets up swap space based on LTO mode (`8G` for Thin, `20G` for Full).
5. **Apply Patches**:
   - LineageOS disguise patch.
   - Clang 21+ compatibility patch (if needed).
   - KernelSU and SUSFS patches (for KSU variant).
6. **Build Kernel**:
   - Configures the kernel with the specified defconfig.
   - Applies LTO mode (`Thin` or `Full`) and custom `localVersion`.
   - Compiles the kernel using Clang and LLVM.
7. **Package Output**:
   - Creates a flashable ZIP using AnyKernel3.
   - Uploads kernel images and the ZIP as artifacts.
8. **Telegram Notification**: Sends build results to Telegram (if configured).

### Supported Configurations
- **Kernel Version**: 5.15
- **Android Version**: 13
- **Compiler**: Clang (fetched from `topnotchfreaks/clang`)
- **LTO Modes**: Thin (faster builds) or Full (better optimization)
- **Variants**: Non-KSU and KSU (with SUSFS support)

---

## 🤝 **Credits**

Special thanks to these amazing developers:

- **@PhamtomK12** – Original Kernel Builder Owner
- **@ssocozy** - Project Contributor
- **@NVG-064** - Project Contributor
- **@ShirkNeko** – SUSFS Integration & susfs4ksu patches

---

## 🔧 **Contributing**

We welcome contributions to improve this workflow! Here's how you can help:

1. **Report Issues**: Open an issue for bugs or build failures.
2. **Suggest Features**: Propose new features or optimizations.
3. **Submit Pull Requests**: Contribute code improvements or new patches.
4. **Add Device Support**: Help adapt the workflow for other devices.

---

## ⚠️ **Important Disclaimer**

> **🚨 For Advanced Users Only**
> 
> - Flashing custom kernels may **void your device warranty**.
> - Always **backup your data** before flashing.
> - **Test thoroughly** on your device to avoid bootloops or hardware issues.
> - The contributors are **not responsible** for any device damage.

---

## 📞 **Need Help?**

- **Issues**: Open an issue on this repository.
- **Community**: Join relevant Telegram groups or X communities for kernel development support.

**Happy building! 🎉**