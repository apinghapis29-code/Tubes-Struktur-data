#include "mll.h"
#include <iomanip>
#include <ctime>

// status booking dibanding waktu sekarang (tanggal format YYYY-MM-DD)
string statusBooking(Booking data) {
    time_t sekarang = time(NULL);
    tm* waktu = localtime(&sekarang);

    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", waktu);
    string hariIni = buf;
    int menitSekarang = waktu->tm_hour * 60 + waktu->tm_min;
    int jamSelesai = data.jamMulai + (data.durasi * 60);

    // format YYYY-MM-DD bisa dibandingkan langsung sebagai string
    if (data.tanggal < hariIni) return "Selesai";
    if (data.tanggal > hariIni) return "Akan Datang";

    // tanggalnya hari ini, cek jamnya
    if (menitSekarang < data.jamMulai) return "Akan Datang";
    if (menitSekarang < jamSelesai) return "Sedang Berlangsung";
    return "Selesai";
}

// bikin MLL kosong
void createMLL(MLL &L) {
    L.firstLapangan = NULL;
}

// cari lapangan berdasarkan kode
NodeLapangan* cariLapangan(MLL L, string kodeLapangan) {
    NodeLapangan* cek = L.firstLapangan;
    while (cek != NULL) {
        if (cek->info.kodeLapangan == kodeLapangan) {
            return cek;
        }
        cek = cek->next;
    }
    return NULL;
}

// tambah lapangan (admin)
bool tambahLapangan(MLL &L, Lapangan data) {
    // cek dulu, kode jangan sampai dobel
    if (cariLapangan(L, data.kodeLapangan) != NULL) {
        cout << "KODE SUDAH TERPAKAI!!" << endl;
        return false;
    }

    // bikin node baru
    NodeLapangan* baru = new NodeLapangan;
    baru->info = data;
    baru->next = NULL;
    baru->firstBooking = NULL;

    // kalau list kosong, jadi node pertama
    if (L.firstLapangan == NULL) {
        L.firstLapangan = baru;
    } else {
        // kalau sudah ada, taruh di paling belakang
        NodeLapangan* cek = L.firstLapangan;
        while (cek->next != NULL) {
            cek = cek->next;
        }
        cek->next = baru;
    }
    return true;
}

// hapus lapangan (admin)
bool hapusLapangan(MLL &L, string kodeLapangan) {
    if (L.firstLapangan == NULL) {
        cout << "BELUM ADA LAPANGAN!!" << endl;
        return false;
    }

    // cari dulu lapangannya
    NodeLapangan* hapus = cariLapangan(L, kodeLapangan);
    if (hapus == NULL) {
        cout << "LAPANGAN TIDAK DITEMUKAN!!" << endl;
        return false;
    }

    // hapus semua booking di dalamnya dulu
    NodeBooking* boking = hapus->firstBooking;
    while (boking != NULL) {
        NodeBooking* nextBooking = boking->next;
        delete boking;
        boking = nextBooking;
    }

    // lepas lapangan dari rantai
    if (hapus == L.firstLapangan) {
        // kalau lapangan pertama
        L.firstLapangan = hapus->next;
    } else {
        // cari lapangan sebelumnya
        NodeLapangan* sebelum = L.firstLapangan;
        while (sebelum->next != hapus) {
            sebelum = sebelum->next;
        }
        sebelum->next = hapus->next;
    }

    delete hapus;
    cout << "LAPANGAN BERHASIL DIHAPUS!!" << endl;
    return true;
}

// tampilkan semua lapangan
void tampilkanLapangan(MLL L) {
    if (L.firstLapangan == NULL) {
        cout << "BELUM ADA LAPANGAN!!" << endl;
        return;
    }

    cout << "\n========== DAFTAR LAPANGAN ==========" << endl;
    cout << "+----------+----------------------+--------------+-----------------+" << endl;
    cout << "| " << left << setw(8)  << "Kode"
         << " | " << setw(20) << "Nama"
         << " | " << setw(12) << "Jenis"
         << " | " << setw(15) << "Harga/Jam"
         << " |" << endl;
    cout << "+----------+----------------------+--------------+-----------------+" << endl;

    NodeLapangan* cek = L.firstLapangan;
    while (cek != NULL) {
        cout << "| " << left << setw(8)  << cek->info.kodeLapangan
             << " | " << setw(20) << cek->info.namaLapangan
             << " | " << setw(12) << cek->info.jenisOlahraga
             << " | " << setw(15) << ("Rp" + to_string((int)cek->info.hargaPerJam))
             << " |" << endl;
        cek = cek->next;
    }
    cout << "+----------+----------------------+--------------+-----------------+" << endl;
}

// tambah booking (user)
bool tambahBooking(MLL &L, string kodeLapangan, Booking data) {
    // cek lapangan ada atau tidak
    NodeLapangan* lapangan = cariLapangan(L, kodeLapangan);
    if (lapangan == NULL) {
        cout << "LAPANGAN TIDAK ADA!!" << endl;
        return false;
    }

    // cek bentrok jadwal
    int jamSelesai = data.jamMulai + (data.durasi * 60);
    NodeBooking* cek = lapangan->firstBooking;
    while (cek != NULL) {
        if (cek->info.tanggal == data.tanggal) {
            int mulaiLama = cek->info.jamMulai;
            int selesaiLama = mulaiLama + (cek->info.durasi * 60);
            if (data.jamMulai < selesaiLama && jamSelesai > mulaiLama) {
                cout << "JADWAL BENTROK!!" << endl;
                return false;
            }
        }
        cek = cek->next;
    }

    // hitung total harga
    data.totalHarga = lapangan->info.hargaPerJam * data.durasi;

    // bikin node booking baru
    NodeBooking* baru = new NodeBooking;
    baru->info = data;
    baru->next = NULL;

    // taruh di akhir daftar booking
    if (lapangan->firstBooking == NULL) {
        lapangan->firstBooking = baru;
    } else {
        NodeBooking* bantu = lapangan->firstBooking;
        while (bantu->next != NULL) {
            bantu = bantu->next;
        }
        bantu->next = baru;
    }
    return true;
}

// hapus booking (batal)
bool hapusBooking(MLL &L, string namaPelanggan, string kodeLapangan, string tanggal, int jamMulai) {
    NodeLapangan* cek = cariLapangan(L, kodeLapangan);
    if (cek == NULL) {
        cout << "LAPANGAN TIDAK ADA!!" << endl;
        return false;
    }

    // cari bookingnya
    NodeBooking* hapus = cek->firstBooking;
    NodeBooking* sebelum = NULL;
    bool ketemu = false;

    while (hapus != NULL) {
        if (hapus->info.namaPelanggan == namaPelanggan &&
            hapus->info.tanggal == tanggal &&
            hapus->info.jamMulai == jamMulai) {
            ketemu = true;
            break;
        }
        sebelum = hapus;
        hapus = hapus->next;
    }

    if (!ketemu) {
        cout << "BOOKING TIDAK DITEMUKAN!!" << endl;
        return false;
    }

    // lepas dari rantai
    if (sebelum == NULL) {
        cek->firstBooking = hapus->next;
    } else {
        sebelum->next = hapus->next;
    }

    delete hapus;
    cout << "BOOKING BERHASIL DIBATALKAN!!" << endl;
    return true;
}

// cari booking
NodeBooking* cariBooking(MLL L, string kodeLapangan, string namaPelanggan, string tanggal, int jamMulai) {
    NodeLapangan* lapangan = cariLapangan(L, kodeLapangan);
    if (lapangan == NULL) {
        return NULL;
    }

    NodeBooking* cek = lapangan->firstBooking;
    while (cek != NULL) {
        if (cek->info.namaPelanggan == namaPelanggan &&
            cek->info.tanggal == tanggal &&
            cek->info.jamMulai == jamMulai) {
            return cek;
        }
        cek = cek->next;
    }
    return NULL;
}

// cek booking (tampil detail kalau ada)
bool cekBooking(MLL L, string namaPelanggan, string kodeLapangan, string tanggal, int jamMulai) {
    NodeBooking* hasil = cariBooking(L, kodeLapangan, namaPelanggan, tanggal, jamMulai);

    if (hasil == NULL) {
        cout << "BOOKING TIDAK DITEMUKAN!!" << endl;
        return false;
    }

    int jam = hasil->info.jamMulai / 60;
    int menit = hasil->info.jamMulai % 60;

    cout << "\n=== BOOKING DITEMUKAN ===" << endl;
    cout << "Kode Lapangan  : " << kodeLapangan << endl;
    cout << "Nama Pelanggan : " << hasil->info.namaPelanggan << endl;
    cout << "Tanggal        : " << hasil->info.tanggal << endl;
    cout << "Jam Mulai      : ";
    if (jam < 10) cout << "0";
    cout << jam << ":";
    if (menit < 10) cout << "0";
    cout << menit << endl;
    cout << "Durasi         : " << hasil->info.durasi << " jam" << endl;
    cout << "Total Harga    : Rp" << (int)hasil->info.totalHarga << endl;
    cout << "Status         : " << statusBooking(hasil->info) << endl;

    return true;
}

// tampilkan semua booking di satu lapangan
void tampilkanBooking(MLL L, string kodeLapangan) {
    NodeLapangan* lapangan = cariLapangan(L, kodeLapangan);
    if (lapangan == NULL) {
        cout << "LAPANGAN TIDAK ADA!!" << endl;
        return;
    }

    if (lapangan->firstBooking == NULL) {
        cout << "BELUM ADA BOOKING!!" << endl;
        return;
    }

    cout << "\n========== BOOKING " << lapangan->info.namaLapangan << " ==========" << endl;
    cout << "+--------------------+--------------+----------+----------+-----------------+--------------------+" << endl;
    cout << "| " << left << setw(18) << "Nama"
         << " | " << setw(12) << "Tanggal"
         << " | " << setw(8)  << "Jam"
         << " | " << setw(8)  << "Durasi"
         << " | " << setw(15) << "Total"
         << " | " << setw(18) << "Status"
         << " |" << endl;
    cout << "+--------------------+--------------+----------+----------+-----------------+--------------------+" << endl;

    NodeBooking* cek = lapangan->firstBooking;
    while (cek != NULL) {
        int jam = cek->info.jamMulai / 60;
        int menit = cek->info.jamMulai % 60;

        // susun dulu jadi string biar setw-nya tepat
        string jamStr = (jam < 10 ? "0" : "") + to_string(jam) + ":" +
                        (menit < 10 ? "0" : "") + to_string(menit);
        string durasiStr = to_string(cek->info.durasi) + " jam";
        string totalStr = "Rp" + to_string((int)cek->info.totalHarga);

        cout << "| " << left << setw(18) << cek->info.namaPelanggan
             << " | " << setw(12) << cek->info.tanggal
             << " | " << setw(8)  << jamStr
             << " | " << setw(8)  << durasiStr
             << " | " << setw(15) << totalStr
             << " | " << setw(18) << statusBooking(cek->info)
             << " |" << endl;

        cek = cek->next;
    }
    cout << "+--------------------+--------------+----------+----------+-----------------+--------------------+" << endl;
}