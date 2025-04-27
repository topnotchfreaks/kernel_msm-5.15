![Inggris](https://github.com/topnotchfreaks/kernel_msm-5.15/README.md)
![Jepang](https://github.com/topnotchfreaks/kernel_msm-5.15/README_jp.md)

# 🚀 Panduan Build GitHub Actions

Repositori ini menyediakan workflow GitHub Actions yang sudah dikonfigurasi untuk membangun kernel dengan mudah melalui UI GitHub.  
Anda bisa memulai build langsung dari GitHub dengan opsi input yang telah disediakan.

## 🛠 Cara Memulai Build
Masuk ke tab **Actions** → Pilih **builder workflow** → Klik **Run workflow** dan isi sebagai berikut:

| Field | Deskripsi | Contoh |
|:------|:----------|:-------|
| **Custom kernel source URL** | URL Git dari source kernel yang ingin dibuild. | `https://github.com/topnotchfreaks/kernel_msm-5.15` |
| **Is private source?** | Centang jika repositori Anda privat. | (Biarkan kosong jika public) |
| **Kernel branch (default jika kosong)** | Nama branch yang ingin dibuild. | `codelinaro` |
| **Device (digunakan untuk defconfig)** | Nama device atau defconfig yang digunakan. | `gki` |
| **Kernel source name** | Nama folder source kernel. | `kernel_msm-5.15` |
| **Custom localversion name** | (Opsional) Tambahan nama versi lokal. | `-testbuild` |
| **Choose KernelSU version** | Pilih versi KernelSU untuk patch (opsional). | `None` |
| **Enable SUSFS** | Aktifkan patch SUSFS. | (Centang untuk mengaktifkan) |
| **SUSFS branch to use** | Branch SUSFS untuk menarik patch. | `gki-android13-5.15` |
| **Clang compiler to use** | Pilih toolchain Clang yang digunakan. | `Greenforce Clang` |

## 📋 Contoh Setup

- **Custom kernel source URL**: `https://github.com/topnotchfreaks/kernel_msm-5.15`
- **Kernel branch**: `codelinaro`
- **Device**: `gki`
- **Kernel source name**: `kernel_msm-5.15`
- **Custom localversion name**: *(opsional)*
- **Choose KernelSU version**: `None`
- **Enable SUSFS**: *(Biarkan kosong)*
- **Clang compiler to use**: `Greenforce Clang`

> ✅ Klik **Run workflow** untuk memulai build!

![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/topnotchfreaks/kernel_msm-5.15/main.yml?branch=builder)
![GitHub branch checks state](https://img.shields.io/github/checks-status/topnotchfreaks/kernel_msm-5.15/builder?branch=builder)
![License](https://img.shields.io/github/license/topnotchfreaks/kernel_msm-5.15)

## **🤝 Terima kasih kepada**:
- ![@PhamtomK12](https://github.com/PhamtomK12) Pemilik asli Kernel builder
- ![@ssocozy](https://github.com/ssocozy)
- ![@NVG-064](https://github.com/NVG-064)
- ![@rifsxd](https://github.com/rifsxd)
- ![@thewildjames](https://github.com/thewildjames)
- 