# ArenaGo
**Tugas Besar Struktur Data — Sistem Booking Lapangan**

> **Catatan (Rancangan Awal):** Seluruh struktur file, rancangan fungsi, pembagian fitur, dan log dalam dokumen ini masih bersifat **rancangan awal (*initial draft*)** dan **dapat berubah sewaktu-waktu** menyesuaikan perkembangan pengerjaan kode, kendala teknis di lapangan, maupun arahan dosen/asisten praktikum.

**ArenaGo** adalah aplikasi berbasis konsol yang dibangun menggunakan bahasa pemrograman **C++** untuk mengelola pemesanan (*booking*) lapangan olahraga. Sistem ini mengimplementasikan struktur data utama **Multi Linked List (MLL)** untuk menghubungkan data lapangan dengan daftar jadwal pemesanannya, serta **Queue** untuk mengelola antrean *waiting list* pemesanan.

**Anggota Kelompok / NIM / Kelas:**

1. Hafis Saputra / 109082500087 / S1IF-13-01
2. Rafli Nurhidayat / 109082500152 / S1IF-13-04
3. Danar Prastika Okka Raharja / 109082600169 / S1IF-13-03
4. Denis Ramadhani / 109082500060 / S1IF-13-02

**Rencana Struktur File *(dapat berubah)*:**

```text
ArenaGo/
├── assets/
│   └── alur_sistem.png
├── mll.h
├── mll.cpp
├── queue.h
├── queue.cpp
├── fitur.h
├── fitur.cpp
├── menu.h
├── menu.cpp
├── main.cpp
└── README.md
```

---

## Diagram Alur Sistem (Flowchart)

Berikut adalah rancangan alur kerja sistem (*flowchart*) untuk proses pemesanan lapangan, penanganan jadwal bentrok melalui *Waiting List* (*Queue*), hingga konfirmasi booking:

<p align="center">
  <img src="pic/ALUR-SISTEM.png" alt="Alur Sistem ArenaGo" width="850">
</p>

> **Penjelasan Alur Revisi:**
> * Jika **Lapangan Tersedia (YA)**: Pelanggan langsung mengisi data, sistem menyimpan booking ke dalam *Child* MLL, dan booking terkonfirmasi.
> * Jika **Lapangan Tidak Tersedia (TIDAK)**: Sistem menawarkan opsi masuk ke **Waiting List**. Jika memilih **YA**, data pelanggan dimasukkan ke dalam antrean (*Queue*). Jika memilih **TIDAK**, barulah sistem memunculkan status **Booking Ditolak**.

---

## 1. Log Progress & Pembagian Fitur *(Tentatif)*

Daftar ini digunakan untuk memantau status pengerjaan setiap modul dan alur sistem:

- [v] Perancangan awal struktur data (`mll.h` & `queue.h`)
- [v] Implementasi operasi dasar MLL (`mll.cpp`: *create*, *insert*, *search*, *delete*)
- [ ] Implementasi operasi dasar Queue untuk Waiting List (`queue.cpp`: *enqueue*, *dequeue*)
- [ ] Fitur Pilih Lapangan & Input Tanggal/Jam
- [ ] Fitur Validasi Ketersediaan Lapangan (Cek jadwal bentrok & opsi masuk *waiting list*)
- [ ] Fitur Simpan Data Pelanggan & Konfirmasi Booking / Antrean Waiting List
- [ ] Fitur Pembatalan Booking (*Cancel*) & Promosi Otomatis dari Waiting List
- [ ] Antarmuka Menu Utama (`menu.h` & `menu.cpp`)
- [ ] Integrasi & Pengujian Akhir (`main.cpp`)

---

## 2. Log Perubahan dan Penambahan

Catatan setiap kali ada penyesuaian konsep, penambahan fungsi baru, perubahan struktur kode, atau pembaruan file.

| Tanggal | PIC | File Terkait | Deskripsi Perubahan / Penambahan |
| :--- | :--- | :--- | :--- |
| 16/11/2026 | Hafis Saputra | `mll.h` | Membuat rancangan awal `struct Lapangan` (Parent) dan `struct Booking` (Child). |
| 16/11/2026 | Hafis Saputra | `mll.cpp` | Menambahkan fungsi `cekKetersediaan()` dan `simpanBooking()`. |
| 16/11/2026 | Tim | `queue.h`, `queue.cpp`, `fitur.cpp` | **Revisi Alur:** Jika jadwal sudah terisi, booking tidak langsung ditolak melainkan ditawarkan masuk ke **Waiting List** menggunakan struktur data *Queue* (FIFO). |
| 16/11/2026 | Tim | `fitur.cpp`, `mll.cpp` | Menambahkan fungsi `cancelBooking()` yang otomatis memindahkan antrean terdepan (*dequeue*) dari *Waiting List* menjadi booking terkonfirmasi saat slot dibatalkan. |
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
| 2 | Booking jadwal bentrok (Pilih masuk Waiting List = Ya) | Lapangan A, 20/11/2026, 19:00, Pilihan: `Y` | Pelanggan mengisi data & masuk ke antrean *Waiting List* (Konfirmasi Antrean). | *Menunggu implementasi* | *Pending* |
| 3 | Booking jadwal bentrok (Pilih masuk Waiting List = Tidak) | Lapangan A, 20/11/2026, 19:00, Pilihan: `N` | Muncul pesan **Booking Ditolak** dan alur selesai. | *Menunggu implementasi* | *Pending* |
| 4 | Pembatalan (*Cancel*) jadwal yang memiliki Waiting List | Cancel booking Lapangan A, 20/11/2026, 19:00 | Data pemesan pertama dihapus, pemesan urutan ke-1 di *Waiting List* otomatis naik menjadi booking utama. | *Menunggu implementasi* | *Pending* |
| 5 | *Skenario berikutnya...* | *Input...* | *Output harapan...* | *Output program...* | *Pass / Fail* |
