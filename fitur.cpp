#include "fitur.h"

// Mengecek apakah jadwal pada tanggal & jam tertentu sudah terisi
bool cekJadwalBentrok(NodeLapangan* lapangan, string tanggal, int jamMulai, int durasi) {
    NodeBooking* cek = lapangan->firstBooking;
    int jamSelesai = jamMulai + (durasi * 60);

    while (cek != NULL) {
        if (cek->info.tanggal == tanggal) {
            int mulaiLama = cek->info.jamMulai;
            int selesaiLama = mulaiLama + (cek->info.durasi * 60);

            if (jamMulai < selesaiLama && jamSelesai > mulaiLama) {
                return true; // Bentrok ditemukan
            }
        }
        cek = cek->next;
    }
    return false; // Jadwal aman
}

// Alur lengkap pemesanan lapangan sesuai diagram sistem
void prosesBookin(MLL &L, Queue &Q) {
    if (L.firstLapangan == NULL) {
        cout << "Belum ada data lapangan terdaftar" << endl;
        return;
    }

    tampilkanLapangan(L);

    string KodeLapangan;
    cout << ""
}