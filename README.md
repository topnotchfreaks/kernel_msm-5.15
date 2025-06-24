# Languages
[Bahasa 🇮🇩](lang/README_id.md) | [日本語 🇯🇵](lang/README_jp.md) | [Portugués 🇧🇷](lang/README_pt.md) | [Espanhol 🇪🇸](lang/README_es.md)

# kernel_msm-5.15

Kernel source and builder for Redmi Note 12 4G NFC (topaz/tapas)

## Overview

This repository contains the kernel source code and build scripts for the Redmi Note 12 4G NFC models, code-named `topaz` and `tapas`. It is based on the Linux kernel version 5.15 (msm-5.15 branch) and tailored for Qualcomm MSM platforms.

This project is intended for developers, maintainers, and power users who wish to build, customize, or modify the kernel for these specific device models.

## Features

- **Linux Kernel 5.15:** Up-to-date kernel base for enhanced security, performance, and device compatibility.
- **Device Specific Support:** Customizations, device trees, and drivers for `topaz` and `tapas` variants.
- **Build Scripts:** Tools and scripts for a streamlined build process.
- **Patches and Fixes:** Integration of important patches for device stability and performance.

## Building the Kernel using GitHub Actions

This repository supports building the kernel using GitHub Actions, which automates the build process in the cloud.

### Steps

1. **Fork the Repository**  
   Click the "Fork" button on the top right of this page to create your own copy of the repository.

2. **Configure Build Parameters**  
   - If needed, edit the workflow file (usually located at `.github/workflows/`) to customize build parameters, such as device variant or compiler options.
   - You can also use repository secrets to securely set sensitive environment variables.

3. **Trigger the Build**  
   - Go to the **Actions** tab in your forked repository.
   - Select the workflow (e.g., "Kernel Build") and click **Run workflow**.
   - Optionally, specify build parameters if the workflow supports inputs.

4. **Wait for Completion**  
   - The build process will start automatically. You can monitor logs and progress in the Actions tab.
   - Once finished, the built kernel and any artifacts (such as `Image.gz-dtb` or flashable zips) will be available in the workflow run summary under **Artifacts**.

5. **Download Artifacts**  
   - Download the built kernel or packaged zip from the workflow artifacts section.

### Notes

- You may need to enable GitHub Actions on your fork before running the workflow for the first time.
- If you encounter errors or failed builds, review the logs for troubleshooting.
- For advanced customization, you can edit the workflow yaml files under `.github/workflows/`.

## [Optional] Automated File Sending via Telegram Bot

You can automate sending the built kernel files directly to Telegram using a bot after the build process.

### How to Enable

1. **Create a Telegram Bot**  
   - Talk to [@BotFather](https://t.me/BotFather) to create a new bot and obtain your `TELEGRAM_BOT_TOKEN`.

2. **Configure GitHub Secrets**  
   - Go to your repository's **Settings** > **Secrets and variables** > **Actions**.
   - Add a new repository secret:
     - Name: `TELEGRAM_BOT_TOKEN`
     - Value: (Fill with your Telegram bot API token)

3. **Set the Recipient**  
   - Add another secret called `TELEGRAM_CHAT_ID` with your Telegram user or group chat ID.

4. **Workflow Integration**  
   - Ensure your GitHub Actions workflow includes steps/scripts to send artifacts using your bot.  
   - Example script snippet (using curl):

     ```sh
     curl -F document=@path_to_artifact.zip "https://api.telegram.org/bot${{ secrets.TELEGRAM_BOT_TOKEN }}/sendDocument?chat_id=${{ secrets.TELEGRAM_CHAT_ID }}&caption=Kernel build complete!"
     ```

   - Fill the `TELEGRAM_BOT_TOKEN` with your Telegram bot API.

5. **Done!**  
   - After a successful build, your kernel file will be sent automatically to your Telegram chat.

## Licensing

This repository contains both kernel source code and builder scripts/tools.  
**Licenses are as follows:**

- **Kernel source code:**  
  Licensed under the GNU General Public License v2.0 (GPLv2). See the [LICENSE](LICENSE) file for details.

- **Builder scripts and automation (including GitHub Actions):**  
  Licensed under the GNU General Public License v3.0 (GPLv3). See the [builder/LICENSE](builder/LICENSE) file for details.

## Contributing

Contributions are welcome! Please open issues or submit pull requests for bug fixes, enhancements, or device-specific improvements.

### Special thanks to the developers

- @PhamtomK12 – Original Kernel Builder Owner
- @ssocozy
- @NVG-064
- @ShirkNeko
- @thewildjames

## Disclaimer

This project is intended for advanced users and developers. Flashing custom kernels may void your device warranty or cause unintended behavior. Proceed with caution and always back up your data.

---

For questions, issues, or support, please open an issue on this repository.