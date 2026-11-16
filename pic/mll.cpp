
#include "mll.h"

// Membuat MLL kosong
void createMLL(MLL &L) {
    L.firstLapangan = NULL;
}

// Membuat node lapangan
NodeLapangan* createNodeLapangan(Lapangan data) {
    NodeLapangan* baru = new NodeLapangan;

    baru->info = data;
    baru->next = NULL;
    baru->firstBooking = NULL;

    return baru;
}

// Membuat node booking
NodeBooking* createNodeBooking(Booking data) {
    NodeBooking* baru = new NodeBooking;

    baru->info = data;
    baru->next = NULL;

    return baru;
}

// Menambahkan lapangan ke dalam MLL
void tambahLapangan(MLL &L, Lapangan data) {
    if (cariLapangan(L, data.kodeLapangan) != NULL) {
        cout << "Kode lapangan sudah digunakan!" << endl;
        return;
    }

    NodeLapangan* baru = createNodeLapangan(data);

    if (L.firstLapangan == NULL) {
        L.firstLapangan = baru;
    } else {
        NodeLapangan* bantu = L.firstLapangan;

        while (bantu->next != NULL) {
            bantu = bantu->next;
        }

        bantu->next = baru;
    }

    cout << "Lapangan berhasil ditambahkan!" << endl;
}

// Mencari lapangan berdasarkan kode
NodeLapangan* cariLapangan(MLL L, string kodeLapangan) {
    NodeLapangan* bantu = L.firstLapangan;

    while (bantu != NULL) {
        if (bantu->info.kodeLapangan == kodeLapangan) {
            return bantu;
        }

        bantu = bantu->next;
    }

    return NULL;
}

// Menampilkan semua lapangan
void tampilkanLapangan(MLL L) {
    NodeLapangan* bantu = L.firstLapangan;

    if (bantu == NULL) {
        cout << "Belum ada data lapangan." << endl;
        return;
    }

    cout << "\n===== DAFTAR LAPANGAN =====" << endl;

    while (bantu != NULL) {
        cout << "Kode Lapangan : "
             << bantu->info.kodeLapangan << endl;

        cout << "Nama Lapangan : "
             << bantu->info.namaLapangan << endl;

        cout << "Jenis Olahraga: "
             << bantu->info.jenisOlahraga << endl;

        cout << "Harga Per Jam : Rp"
             << bantu->info.hargaPerJam << endl;

        cout << "--------------------------" << endl;

        bantu = bantu->next;
    }
}

// Menambahkan booking ke lapangan tertentu
void tambahBooking(MLL &L, string kodeLapangan, Booking data) {
    NodeLapangan* lapangan = cariLapangan(L, kodeLapangan);

    if (lapangan == NULL) {
        cout << "Lapangan tidak ditemukan!" << endl;
        return;
    }

    if (data.durasi <= 0 || data.jamMulai < 0 ||
        data.jamMulai >= 1440) {
        cout << "Jam mulai atau durasi tidak valid!" << endl;
        return;
    }

    if (lapangan->info.hargaPerJam < 0) {
        cout << "Harga lapangan tidak valid!" << endl;
        return;
    }

    // Memeriksa apakah jadwal booking bertabrakan
    NodeBooking* cek = lapangan->firstBooking;

    int jamSelesai = data.jamMulai + (data.durasi * 60);

    while (cek != NULL) {
        if (cek->info.tanggal == data.tanggal) {
            int mulaiLama = cek->info.jamMulai;
            int selesaiLama =
                mulaiLama + (cek->info.durasi * 60);

            if (data.jamMulai < selesaiLama &&
                jamSelesai > mulaiLama) {

                cout << "Jadwal lapangan sudah terisi!"
                     << endl;
                return;
            }
        }

        cek = cek->next;
    }

    // Menghitung total harga booking
    data.totalHarga =
        lapangan->info.hargaPerJam * data.durasi;

    NodeBooking* baru = createNodeBooking(data);

    // Memasukkan booking ke daftar child
    if (lapangan->firstBooking == NULL) {
        lapangan->firstBooking = baru;
    } else {
        NodeBooking* bantu = lapangan->firstBooking;

        while (bantu->next != NULL) {
            bantu = bantu->next;
        }

        bantu->next = baru;
    }

    cout << "Booking berhasil ditambahkan!" << endl;
}

// Menampilkan booking dari lapangan tertentu
void tampilkanBooking(MLL L, string kodeLapangan) {
    NodeLapangan* lapangan = cariLapangan(L, kodeLapangan);

    if (lapangan == NULL) {
        cout << "Lapangan tidak ditemukan!" << endl;
        return;
    }

    NodeBooking* bantu = lapangan->firstBooking;

    if (bantu == NULL) {
        cout << "Belum ada booking untuk lapangan ini."
             << endl;
        return;
    }

    cout << "\n===== DAFTAR BOOKING =====" << endl;
    cout << "Nama Lapangan: "
         << lapangan->info.namaLapangan << endl;

    while (bantu != NULL) {
        int jam = bantu->info.jamMulai / 60;
        int menit = bantu->info.jamMulai % 60;

        cout << "\nID Booking     : "
             << bantu->info.idBooking << endl;

        cout << "Nama Pelanggan : "
             << bantu->info.namaPelanggan << endl;

        cout << "Tanggal        : "
             << bantu->info.tanggal << endl;

        cout << "Jam Mulai      : ";

        if (jam < 10) cout << "0";
        cout << jam << ":";

        if (menit < 10) cout << "0";
        cout << menit << endl;

        cout << "Durasi         : "
             << bantu->info.durasi << " jam" << endl;

        cout << "Total Harga    : Rp"
             << bantu->info.totalHarga << endl;

        cout << "--------------------------" << endl;

        bantu = bantu->next;
    }
}
