# kernel_msm-5.15

Sumber kernel dan builder untuk Redmi Note 12 4G NFC (topaz/tapas)

## Gambaran Umum

Repository ini berisi kode sumber kernel dan skrip build untuk model Redmi Note 12 4G NFC, dengan nama kode `topaz` dan `tapas`. Berbasis pada kernel Linux versi 5.15 (cabang msm-5.15) dan disesuaikan untuk platform Qualcomm MSM.

Proyek ini ditujukan untuk developer, maintainer, dan power user yang ingin build, kustomisasi, atau modifikasi kernel untuk model perangkat spesifik ini.

## Fitur

- **Linux Kernel 5.15:** Basis kernel terkini untuk keamanan, performa, dan kompatibilitas perangkat yang ditingkatkan.
- **Dukungan Perangkat Spesifik:** Kustomisasi, device tree, dan driver untuk varian `topaz` dan `tapas`.
- **Skrip Build:** Tools dan skrip untuk proses build yang efisien.
- **Patch dan Perbaikan:** Integrasi patch penting untuk stabilitas dan performa perangkat.

## Membangun Kernel menggunakan GitHub Actions

Repository ini mendukung pembangunan kernel menggunakan GitHub Actions, yang mengotomatisasi proses build di cloud.

### Langkah-langkah

1. **Fork Repository**  
   Klik tombol "Fork" di bagian kanan atas halaman ini untuk membuat salinan repository Anda sendiri.

2. **Konfigurasi Parameter Build**  
   - Jika diperlukan, edit file workflow (biasanya terletak di `.github/workflows/`) untuk menyesuaikan parameter build, seperti varian perangkat atau opsi compiler.
   - Anda juga dapat menggunakan repository secrets untuk mengatur variabel lingkungan sensitif dengan aman.

3. **Memicu Build**  
   - Pergi ke tab **Actions** di repository fork Anda.
   - Pilih workflow (misalnya, "Kernel Build") dan klik **Run workflow**.
   - Opsional, tentukan parameter build jika workflow mendukung input.

4. **Tunggu Penyelesaian**  
   - Proses build akan dimulai secara otomatis. Anda dapat memantau log dan progres di tab Actions.
   - Setelah selesai, kernel yang dibangun dan artifact apa pun (seperti `Image.gz-dtb` atau zip yang dapat di-flash) akan tersedia di ringkasan workflow run di bawah **Artifacts**.

5. **Unduh Artifacts**  
   - Unduh kernel yang dibangun atau zip yang dikemas dari bagian artifacts workflow.

### Catatan

- Anda mungkin perlu mengaktifkan GitHub Actions di fork Anda sebelum menjalankan workflow untuk pertama kalinya.
- Jika Anda mengalami error atau build gagal, tinjau log untuk troubleshooting.
- Untuk kustomisasi lanjutan, Anda dapat mengedit file yaml workflow di bawah `.github/workflows/`.

## [Opsional] Pengiriman File Otomatis via Bot Telegram

Anda dapat mengotomatisasi pengiriman file kernel yang dibangun langsung ke Telegram menggunakan bot setelah proses build.

### Cara Mengaktifkan

1. **Buat Bot Telegram**  
   - Berbicara dengan [@BotFather](https://t.me/BotFather) untuk membuat bot baru dan mendapatkan `TELEGRAM_BOT_TOKEN` Anda.

2. **Konfigurasi GitHub Secrets**  
   - Pergi ke **Settings** repository Anda > **Secrets and variables** > **Actions**.
   - Tambahkan repository secret baru:
     - Nama: `TELEGRAM_BOT_TOKEN`
     - Nilai: (Isi dengan token API bot Telegram Anda)

3. **Atur Penerima**  
   - Tambahkan secret lain bernama `TELEGRAM_CHAT_ID` dengan ID chat pengguna atau grup Telegram Anda.

4. **Integrasi Workflow**  
   - Pastikan workflow GitHub Actions Anda mencakup langkah/skrip untuk mengirim artifacts menggunakan bot Anda.  
   - Contoh cuplikan skrip (menggunakan curl):

     ```sh
     curl -F document=@path_to_artifact.zip "https://api.telegram.org/bot${{ secrets.TELEGRAM_BOT_TOKEN }}/sendDocument?chat_id=${{ secrets.TELEGRAM_CHAT_ID }}&caption=Build kernel selesai!"
     ```

   - Isi `TELEGRAM_BOT_TOKEN` dengan API bot Telegram Anda.

5. **Selesai!**  
   - Setelah build berhasil, file kernel Anda akan dikirim secara otomatis ke chat Telegram Anda.

## Lisensi

Repository ini berisi kode sumber kernel dan skrip/tools builder.  
**Lisensi adalah sebagai berikut:**

- **Kode sumber kernel:**  
  Dilisensikan di bawah GNU General Public License v2.0 (GPLv2). Lihat file [LICENSE](LICENSE) untuk detail.

- **Skrip builder dan otomasi (termasuk GitHub Actions):**  
  Dilisensikan di bawah GNU General Public License v3.0 (GPLv3). Lihat file [builder/LICENSE](builder/LICENSE) untuk detail.

## Kontribusi

Kontribusi diterima! Silakan buka issues atau kirim pull requests untuk perbaikan bug, peningkatan, atau perbaikan spesifik perangkat.

## Penafian

Proyek ini ditujukan untuk pengguna lanjutan dan developer. Melakukan flash kernel kustom dapat membatalkan garansi perangkat Anda atau menyebabkan perilaku yang tidak diinginkan. Lanjutkan dengan hati-hati dan selalu backup data Anda.

---

Untuk pertanyaan, issues, atau dukungan, silakan buka issue di repository ini.