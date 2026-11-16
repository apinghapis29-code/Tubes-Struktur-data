# Tugas Besar Struktur Data — Sistem Booking Lapangan — ArenaGo

> **Catatan (Rancangan Awal):** Seluruh struktur file, rancangan fungsi, pembagian fitur, dan log dalam dokumen ini masih bersifat **rancangan awal (*initial draft*)** dan **dapat berubah sewaktu-waktu** menyesuaikan perkembangan pengerjaan kode, kendala teknis di lapangan, maupun arahan dosen/asisten praktikum.

Deskripsi singkat proyek, bahasa pemrograman yang digunakan (**C++**), serta rencana struktur data utama (**Multi Linked List / MLL** dan **Queue**).

**Anggota Kelompok / NIM / Kelas:**

1. Hafis Saputra / 109082500087 / S1IF-13-01
2. Rafli Nurhidayat / 109082500152 / S1IF-13-04
3. Danar Prastika Okka Raharja / 109082600169 / S1IF-13-03
4. Denis Ramadhani / 109082500060 / S1IF-13-02

**Rencana Struktur File *(dapat berubah)*:** `mll.h`, `mll.cpp`, `fitur.h`, `fitur.cpp`, `menu.h`, `menu.cpp`, `main.cpp`

---

## 1. Log Progress & Pembagian Fitur *(Tentatif)*

Daftar ini digunakan untuk memantau status pengerjaan setiap modul dan alur sistem:

- [ ] Perancangan awal struktur data (`mll.h`)
- [ ] Implementasi operasi dasar MLL (`mll.cpp`: *create*, *insert*, *search*, *delete*)
- [ ] Fitur Pilih Lapangan & Input Tanggal/Jam
- [ ] Fitur Validasi Ketersediaan Lapangan (Cek jadwal bentrok)
- [ ] Fitur Simpan Data Pelanggan & Konfirmasi Booking
- [ ] Antarmuka Menu Utama (`menu.h` & `menu.cpp`)
- [ ] Integrasi & Pengujian Akhir (`main.cpp`)

---

## 2. Log Perubahan dan Penambahan

Catatan setiap kali ada penyesuaian konsep, penambahan fungsi baru, perubahan struktur kode, atau pembaruan file.

| Tanggal | PIC | File Terkait | Deskripsi Perubahan / Penambahan |
| :--- | :--- | :--- | :--- |
| 16/11/2026 | Nama 1 | `mll.h` | Membuat rancangan awal `struct Lapangan` (Parent) dan `struct Booking` (Child). |
| 16/11/2026 | Nama 2 | `mll.cpp` | Menambahkan fungsi `cekKetersediaan()` dan `simpanBooking()`. |
| *dd/mm/yyyy* | *Nama* | *Nama file* | *Tuliskan perubahan atau revisi rancangan di sini...* |

---

## 3. Log Permasalahan saat Compile atau Coding

Catatan *bug*, *error compiler*, atau kendala logika pointer beserta cara mengatasinya agar tidak terulang.

| Tanggal | Masalah / Pesan Error | Penyebab | Solusi | Status |
| :--- | :--- | :--- | :--- | :--- |
| 16/11/2026 | `undefined reference to 'simpanBooking'` | File `mll.cpp` belum ikut ter-compile bersama `main.cpp`. | Menambahkan `mll.cpp` ke dalam konfigurasi *build/project* IDE. | Selesai |
| 16/11/2026 | `redefinition of 'struct Lapangan'` | File `mll.h` dipanggil di beberapa file tanpa *include guard*. | Menambahkan `#ifndef MLL_H_INCLUDED` di baris paling atas `mll.h`. | Selesai |
| *dd/mm/yyyy* | *Pesan error / bug* | *Penyebab masalah* | *Cara memperbaiki* | *Proses / Selesai* |

---

## 4. Log Pengujian Alur Sistem (Testing)

Catatan hasil uji coba skenario input untuk memastikan logika percabangan berjalan sesuai diagram alur.

| No | Skenario Uji Coba | Input Uji | Hasil yang Diharapkan | Hasil Aktual | Status |
| :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | Booking jadwal kosong | Lapangan A, 20/11/2026, 19:00 | Masuk ke isi data pelanggan & konfirmasi berhasil. | Sesuai | Pass |
| 2 | Booking jadwal bentrok | Lapangan A, 20/11/2026, 19:00 | Muncul pesan **Booking Ditolak**. | Sesuai | Pass |
| 3 | *Skenario berikutnya...* | *Input...* | *Output harapan...* | *Output program...* | *Pass / Fail* |
