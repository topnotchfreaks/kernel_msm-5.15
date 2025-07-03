# 🌐 Languages
[Bahasa 🇮🇩](lang/README_id.md) | [日本語 🇯🇵](lang/README_jp.md) | [Portugués 🇧🇷](lang/README_pt.md) | [Espanhol 🇪🇸](lang/README_es.md)

# 🔧 kernel_msm-5.15

**Kernel source and builder for Redmi Note 12 4G NFC (topaz/tapas)**

---

## ⚠️ **IMPORTANT: Device Compatibility Warning**

> **🚨 This builder is ONLY for Redmi Note 12 4G NFC (topaz/tapas) devices!**

### Want to use this for other devices? You MUST change these 6 things:

| Component | What to Change |
|-----------|---------------|
| **🔗 Kernel Source** | Update source URL, branch, and device support |
| **🔧 Kernel Tweaks** | Modify patches and device-specific tweaks |
| **📝 Makefile** | Update compiler flags for your hardware |
| **🔐 KSU/SUSFS** | Adapt root patches for your kernel version |
| **📦 AnyKernel3** | Use your device's flashing template |
| **⚙️ Device Config** | Update device name and defconfig settings |

### ⚡ **Risks of improper usage:**
- ❌ Build failures
- ❌ Broken kernel images  
- ❌ Device bootloops
- ❌ Potential hardware damage

**💡 Always test thoroughly before widespread use!**

---

## 📋 **What is this?**

A complete kernel building solution for **Redmi Note 12 4G NFC** devices (codenames: `topaz` and `tapas`).

Built on **Linux Kernel 5.15** (msm-5.15 branch) for Qualcomm MSM platforms.

## ✨ **Key Features**

| Feature | Description |
|---------|-------------|
| 🐧 **Linux Kernel 5.15** | Latest stable kernel with security & performance improvements |
| 📱 **Device Support** | Custom drivers, device trees for topaz/tapas variants |
| 🤖 **Automated Building** | GitHub Actions for cloud-based kernel compilation |
| 🔐 **KSU + SUSFS** | Integrated KernelSU with SUSFS for advanced root features |
| 📦 **Ready-to-Flash** | AnyKernel3 ZIP files for easy installation |

---

## 🚀 **How to Build (GitHub Actions)**

### Step 1: Fork the Repository
Click the **"Fork"** button at the top-right of this page.

### Step 2: Trigger the Build
1. Go to the **Actions** tab in your forked repository
2. Select **"Build kernels"** workflow
3. Click **"Run workflow"**
4. Configure build options (optional):
   - Kernel source URL
   - Branch name
   - Device type
   - Compiler choice

### Step 3: Wait for Build
- Monitor progress in the Actions tab
- Build usually takes 20-30 minutes
- Both **NoKSU** and **KSU** kernels are built

### Step 4: Download Results
- Find artifacts in the workflow run summary
- Download the **AnyKernel3 ZIP** file
- Flash via recovery (TWRP/OrangeFox)

### 💡 **Build Options Available:**
- **Clang Compiler**: ZyC, Greenforce, or TopNotchFreaks
- **Custom Version**: Add your own version suffix
- **Private Repos**: Support for private kernel sources

---

## 📱 **Telegram Integration (Optional)**

Get build results sent directly to your Telegram!

### Quick Setup:
1. **Create Bot**: Message [@BotFather](https://t.me/BotFather) → get `TELEGRAM_BOT_TOKEN`
2. **Add Secrets**: Go to your repo → Settings → Secrets and variables → Actions
   - Add `TELEGRAM_BOT_TOKEN` (your bot token)
   - Add `TELEGRAM_USER_ID` (your Telegram user ID)
3. **Done!** 🎉 Builds will auto-send to your chat

### Example Integration:
```bash
curl -F document=@kernel.zip \
     -F caption="✅ Build complete!" \
     -F chat_id=YOUR_CHAT_ID \
     "https://api.telegram.org/botYOUR_BOT_TOKEN/sendDocument"
```

---

## 📄 **License Information**

| Component | License |
|-----------|---------|
| **Kernel Source Code** | GNU General Public License v2.0 ([LICENSE](LICENSE)) |
| **Builder Scripts & Actions** | GNU General Public License v3.0 ([builder/LICENSE](builder/LICENSE)) |

---

## 🤝 **Contributors & Credits**

Special thanks to these amazing developers:

- **@PhamtomK12** – Original Kernel Builder Owner
- **@ssocozy** - Project Contributor
- **@NVG-064** - Project Contributor
- **@ShirkNeko** – SUSFS Integration
- **@thewildjames** – Kernel patches

---

## 🔧 **Contributing**

We welcome contributions! Here's how you can help:

1. **🐛 Report Issues**: Found a bug? Open an issue!
2. **💡 Suggest Features**: Have an idea? Let us know!
3. **🔧 Submit PRs**: Code improvements welcome!
4. **📱 Device Support**: Help add support for more devices!

---

## ⚠️ **Important Disclaimer**

> **🚨 For Advanced Users Only**
> 
> - Flashing custom kernels may **void your warranty**
> - Always **backup your data** before flashing
> - **Test thoroughly** before daily use
> - We are **not responsible** for any device damage

---

## 📞 **Need Help?**

- **🐛 Issues**: Open an issue on this repository
- **💬 Discussions**: Use GitHub Discussions
- **📚 Documentation**: Check the wiki (coming soon)

**Happy building! 🎉**
