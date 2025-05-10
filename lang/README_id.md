# 🚀 Panduan Build Kernel via GitHub Actions

🌐 Bahasa Tersedia: [Jepang 🇯🇵](README_jp.md) | [Inggris 🇺🇸](README.md)

Selamat datang!  
Repositori ini menyediakan **workflow GitHub Actions yang sudah dikonfigurasi** untuk memudahkan build kernel langsung dari antarmuka GitHub.

---

## 📝 Cara Cepat: Fork & Atur

1. **Fork repositori ini**  
   Klik tombol **Fork** di pojok kanan atas untuk membuat salinan repositori ini ke akunmu.

2. **Tambahkan Personal Access Token (GH_TOKEN) ke Secrets**  
   - Buka menu **Settings** → **Secrets and variables** → **Actions** di repositori hasil fork.
   - Klik **New repository secret**.
   - Beri nama `GH_TOKEN`.
   - Tempel [GitHub Personal Access Token](https://github.com/settings/tokens) milikmu dengan izin `repo` dan `workflow`.
   - Klik **Add secret**.

---

## 🛠 Cara Memulai Build

1. Buka tab **Actions**.
2. Pilih workflow bernama **builder**.
3. Klik **Run workflow** dan isi form berikut:

| Field | Deskripsi | Contoh |
|:------|:----------|:-------|
| **Custom kernel source URL** | URL Git sumber kernel yang ingin dibuild. | `https://github.com/topnotchfreaks/kernel_msm-5.15` |
| **Is private source?** | Centang jika repositorinya privat. | (Biarkan kosong jika publik) |
| **Kernel branch** | Nama branch kernel (default jika dikosongkan). | `google` |
| **Device (defconfig)** | Nama device atau defconfig yang digunakan. | `gki` |
| **Kernel source name** | Nama folder kernel. | `kernel_msm-5.15` |
| **Custom localversion name** | *(Opsional)* Tambahan versi kernel. | `-testbuild` |
| **Choose KernelSU version** | *(Opsional)* Versi KernelSU yang ingin dipasang. | `None` |

---

> ✅ Klik **Run workflow** untuk memulai proses build!

---
