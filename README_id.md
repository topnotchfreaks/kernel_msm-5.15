# 🚀 Panduan Build Kernel GitHub Actions

🌐 Bahasa Lain: [English 🇬🇧](README.md) | [Japanese 🇯🇵](README_jp.md)

Selamat datang!  
Repositori ini menyediakan **workflow GitHub Actions** untuk membangun kernel dengan mudah melalui UI GitHub.

---

## 🛠 Cara Memulai Build

1. Buka tab **Actions**.
2. Pilih workflow **builder**.
3. Klik **Run workflow** dan isi data berikut:

| Field | Deskripsi | Contoh |
|:------|:----------|:-------|
| **Custom kernel source URL** | URL Git source kernel. | `https://github.com/topnotchfreaks/kernel_msm-5.15` |
| **Is private source?** | Centang jika repositori privat. | (Biarkan kosong jika publik) |
| **Kernel branch** | Nama branch untuk build. | `codelinaro` |
| **Device (defconfig)** | Nama device/defconfig. | `gki` |
| **Kernel source name** | Nama folder kernel. | `kernel_msm-5.15` |
| **Custom localversion name** | *(Opsional)* Sufiks lokalversi kernel. | `-testbuild` |
| **Choose KernelSU version** | *(Opsional)* Versi KernelSU. | `None` |

---

## 📋 Contoh Setup

- **Custom kernel source URL**: `https://github.com/topnotchfreaks/kernel_msm-5.15`
- **Kernel branch**: `codelinaro`
- **Device**: `gki`
- **Kernel source name**: `kernel_msm-5.15`
- **Custom localversion name**: *(opsional)*
- **Choose KernelSU version**: `None`

✅ Klik **Run workflow** untuk memulai build!

---
