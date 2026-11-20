#include "fitur.h"
#include <fstream>
#include <sstream>

// ============ ADMIN ============

// tambah lapangan baru
void lapanganBaru(MLL &L) {
    Lapangan data;

    cout << "\n===== TAMBAH LAPANGAN BARU =====" << endl;
    cout << "Kode Lapangan  : ";
    cin >> data.kodeLapangan;
    cin.ignore();   // WAJIB sebelum getline
    cout << "Nama Lapangan  : ";
    getline(cin, data.namaLapangan);
    cout << "Jenis Olahraga : ";
    getline(cin, data.jenisOlahraga);
    cout << "Harga Per Jam  : ";
    cin >> data.hargaPerJam;

    // validasi harga
    if (data.hargaPerJam <= 0) {
        cout << "HARGA TIDAK VALID!!" << endl;
        return;
    }

    if (tambahLapangan(L, data)); {
        cout << "LAPANGAN BERHASIL DITAMBAHKAN!!" << endl;
    }
}

// hapus lapangan
void hapusLapanganMenu(MLL &L) {
    if (L.firstLapangan == NULL) {
        cout << "BELUM ADA LAPANGAN!!" << endl;
        return;
    }

    tampilkanLapangan(L);

    string kode;
    cout << "\nKode Lapangan yang mau dihapus : ";
    cin >> kode;

    // konfirmasi
    char yakin;
    cout << "Yakin hapus " << kode << "? (y/n): ";
    cin >> yakin;

    if (yakin == 'y' || yakin == 'Y') {
        hapusLapangan(L, kode);
    } else {
        cout << "Batal hapus lapangan." << endl;
    }
}

// proses waiting list (admin)
void prosesWaitingList(MLL &L, Queue &Q) {
    if (isEmpty(Q)) {
        cout << "WAITING LIST KOSONG!!" << endl;
        return;
    }

    // lihat dulu, jangan dequeue sebelum yakin
    string kode = Q.head->kodeLapangan;
    Booking data = Q.head->info;

    cout << "\nMemproses antrean: " << data.namaPelanggan << endl;

    bool sukses = tambahBooking(L, kode, data);

    if (sukses) {
        // berhasil, baru dequeue
        string k;
        Booking d;
        dequeue(Q, k, d);
        cout << "Antrean selesai diproses." << endl;
    } else {
        cout << "Masih bentrok, tetap di antrean." << endl;
    }
}

// ============ USER ============

// booking lapangan
void pesanLapangan(MLL &L, Queue &Q) {
    if (L.firstLapangan == NULL) {
        cout << "BELUM ADA LAPANGAN!!" << endl;
        return;
    }

    tampilkanLapangan(L);

    string kode;
    cout << "\nKode Lapangan  : ";
    cin >> kode;

    // cek lapangan ada atau tidak
    NodeLapangan* lapangan = cariLapangan(L, kode);
    if (lapangan == NULL) {
        cout << "LAPANGAN TIDAK ADA!!" << endl;
        return;
    }

    Booking data;
    int jam;

    cin.ignore();
    cout << "Tanggal (2024-12-01) : ";
    getline(cin, data.tanggal);
    cout << "Jam Mulai (0-23)     : ";
    cin >> jam;
    cout << "Durasi (jam)         : ";
    cin >> data.durasi;

    // validasi input
    if (jam < 0 || jam > 23 || data.durasi <= 0) {
        cout << "INPUT TIDAK VALID!!" << endl;
        return;
    }

    // cek lewat tengah malam
    if (jam * 60 + data.durasi * 60 > 1440) {
        cout << "BOOKING MELEWATI TENGAH MALAM!!" << endl;
        return;
    }
    data.jamMulai = jam * 60;

    cin.ignore();
    cout << "Nama Pelanggan : ";
    getline(cin, data.namaPelanggan);

    // coba booking
    bool sukses = tambahBooking(L, kode, data);

    if (sukses) {
        cout << "BOOKING BERHASIL!!" << endl;
    } else {
        // bentrok, tawarin waiting list
        char jawab;
        cout << "Mau masuk waiting list? (y/n): ";
        cin >> jawab;

        if (jawab == 'y' || jawab == 'Y') {
            enqueue(Q, kode, data);
        } else {
            cout << "Booking dibatalkan." << endl;
        }
    }
}

// cek booking
void cekBookingMenu(MLL L) {
    if (L.firstLapangan == NULL) {
        cout << "BELUM ADA LAPANGAN!!" << endl;
        return;
    }

    tampilkanLapangan(L);

    string kode, nama, tanggal;
    int jam;

    cout << "\n--- CEK BOOKING ---" << endl;
    cout << "Kode Lapangan  : ";
    cin >> kode;
    cin.ignore();
    cout << "Nama Pelanggan : ";
    getline(cin, nama);
    cout << "Tanggal        : ";
    getline(cin, tanggal);
    cout << "Jam Mulai (0-23): ";
    cin >> jam;

    cekBooking(L, nama, kode, tanggal, jam * 60);
}

// batal booking
void batalBooking(MLL &L) {
    if (L.firstLapangan == NULL) {
        cout << "BELUM ADA LAPANGAN!!" << endl;
        return;
    }

    string kode;
    cout << "Kode Lapangan  : ";
    cin >> kode;

    NodeLapangan* lapangan = cariLapangan(L, kode);
    if (lapangan == NULL) {
        cout << "LAPANGAN TIDAK ADA!!" << endl;
        return;
    }

    // tampilkan dulu semua booking di lapangan itu
    tampilkanBooking(L, kode);

    string nama, tanggal;
    int jam;

    cin.ignore();
    cout << "\nNama Pelanggan : ";
    getline(cin, nama);
    cout << "Tanggal        : ";
    getline(cin, tanggal);
    cout << "Jam Mulai (0-23): ";
    cin >> jam;

    // cek dulu, tampilkan detail
    bool ada = cekBooking(L, nama, kode, tanggal, jam * 60);
    if (!ada) {
        cout << "Tidak ada yang dibatalkan." << endl;
        return;
    }

    char yakin;
    cout << "Yakin batal booking ini? (y/n): ";
    cin >> yakin;

    if (yakin == 'y' || yakin == 'Y') {
        hapusBooking(L, nama, kode, tanggal, jam * 60);
    } else {
        cout << "Batal dibatalkan." << endl;
    }
}

// batal waiting list
void batalWaitingListMenu(Queue &Q) {
    if (isEmpty(Q)) {
        cout << "WAITING LIST KOSONG!!" << endl;
        return;
    }

    tampilkanAntrean(Q);

    string nama, kode;

    cin.ignore();
    cout << "\nNama Pelanggan : ";
    getline(cin, nama);
    cout << "Kode Lapangan  : ";
    cin >> kode;

    char yakin;
    cout << "Yakin batal dari waiting list? (y/n): ";
    cin >> yakin;

    if (yakin == 'y' || yakin == 'Y') {
        batalWaitingList(Q, kode, nama);
    } else {
        cout << "Batal dibatalkan." << endl;
    }
}

// simpan data
void simpanData(MLL L, Queue Q) {
    ofstream file("data.txt");

    if (!file.is_open()) {
        cout << "GAGAL SIMPAN DATA!!" << endl;
        return;
    }

    // ============ SIMPAN LAPANGAN + BOOKING ============
    NodeLapangan* lap = L.firstLapangan;
    while (lap != NULL) {
        file << "LAPANGAN|"
             << lap->info.kodeLapangan << "|"
             << lap->info.namaLapangan << "|"
             << lap->info.jenisOlahraga << "|"
             << lap->info.hargaPerJam << endl;

        NodeBooking* book = lap->firstBooking;
        while (book != NULL) {
            file << "BOOKING|"
                 << lap->info.kodeLapangan << "|"
                 << book->info.namaPelanggan << "|"
                 << book->info.tanggal << "|"
                 << book->info.jamMulai << "|"
                 << book->info.durasi << "|"
                 << book->info.totalHarga << endl;
            book = book->next;
        }

        lap = lap->next;
    }

    // ============ SIMPAN WAITING LIST ============  ← BARU
    NodeQueue* antre = Q.head;
    while (antre != NULL) {
        file << "ANTREAN|"
             << antre->kodeLapangan << "|"
             << antre->info.namaPelanggan << "|"
             << antre->info.tanggal << "|"
             << antre->info.jamMulai << "|"
             << antre->info.durasi << "|"
             << antre->info.totalHarga << endl;
        antre = antre->next;
    }

    file.close();
}

// muat data
void muatData(MLL &L, Queue &Q) {
    ifstream file("data.txt");

    if (!file.is_open()) {
        return;
    }

    string baris;
    while (getline(file, baris)) {
        stringstream ss(baris);
        string tipe, kode, nama, jenis, tanggal;
        string sJam, sDurasi, sHarga, sTotal;

        getline(ss, tipe, '|');

        if (tipe == "LAPANGAN") {
            getline(ss, kode,   '|');
            getline(ss, nama,   '|');
            getline(ss, jenis,  '|');
            getline(ss, sHarga, '|');

            Lapangan d;
            d.kodeLapangan  = kode;
            d.namaLapangan  = nama;
            d.jenisOlahraga = jenis;
            d.hargaPerJam   = stod(sHarga);

            tambahLapangan(L, d);
        }
        else if (tipe == "BOOKING") {
            getline(ss, kode,    '|');
            getline(ss, nama,    '|');
            getline(ss, tanggal, '|');
            getline(ss, sJam,    '|');
            getline(ss, sDurasi, '|');
            getline(ss, sHarga,  '|');

            Booking b;
            b.namaPelanggan = nama;
            b.tanggal       = tanggal;
            b.jamMulai      = stoi(sJam);
            b.durasi        = stoi(sDurasi);
            b.totalHarga    = stod(sHarga);

            tambahBooking(L, kode, b);
        }
        else if (tipe == "ANTREAN") {       // ← BARU
            getline(ss, kode,    '|');
            getline(ss, nama,    '|');
            getline(ss, tanggal, '|');
            getline(ss, sJam,    '|');
            getline(ss, sDurasi, '|');
            getline(ss, sHarga,  '|');

            Booking b;
            b.namaPelanggan = nama;
            b.tanggal       = tanggal;
            b.jamMulai      = stoi(sJam);
            b.durasi        = stoi(sDurasi);
            b.totalHarga    = stod(sHarga);

            enqueue(Q, kode, b);
        }
    }

    file.close();
}