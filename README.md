# 🚀 Android Kernel Builder
## ⚠️ Important Notice

This workflow is configured for specific devices. **You must modify the settings for your device** or it may not work properly.

## 🔧 Quick Start

1. **Fork this repository**
2. Go to **Actions** tab → **"Build kernels"** workflow
3. Click **"Run workflow"** and configure:

### Workflow Settings

| Setting | Description | Default |
|---------|-------------|---------|
| **Kernel source URL** | Your kernel repository URL | `https://github.com/topnotchfreaks/kernel_msm-5.15` |
| **Kernel branch** | Branch to build from | `codelinaro` |
| **Device** | Device name for defconfig | `gki` |
| **Custom localversion** | Add custom version suffix | (empty) |
| **Build KSU variant** | Include KernelSU version | `true` |
| **LTO mode** | Optimization level | `thin` |

4. **Wait for build** (20-40 minutes)
5. **Download** the flashable ZIP from artifacts

## 📱 Telegram Notifications (Optional)

Get build results sent to Telegram:

1. Create a bot with [@BotFather](https://t.me/BotFather)
2. Get your chat ID from [@GetIDsBot](https://t.me/GetIDsBot)
3. Add these secrets in repository **Settings** → **Secrets**:
   - `TELEGRAM_BOT_TOKEN`
   - `TELEGRAM_USER_ID`

## 🤝 Credits

- **@PhamtomK12** – Original builder
- **@ssocozy** – Contributor  
- **@NVG-064** – Contributor
- **@ShirkNeko** – SUSFS integration
- **@thewildjames** – Wild-KSU

---

**Ready to build? Hit that "Run workflow" button! 🎉**
