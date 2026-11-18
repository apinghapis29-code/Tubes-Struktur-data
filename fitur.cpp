#include "fitur.h"

// Meminta input user untuk menambah lapangan baru
void inputLapanganBaru(MLL &L) {
    Lapangan data;

    cout << "\n--- TAMBAH LAPANGAN BARU ---" << endl;
    cout << "Kode Lapangan  : ";
    cin >> data.kodeLapangan;
    cin.ignore();

    cout << "Nama Lapangan  : ";
    getline(cin, data.namaLapangan);

    cout << "Jenis Olahraga : ";
    getline(cin, data.jenisOlahraga);

    cout << "Harga Per Jam  : ";
    cin >> data.hargaPerJam;

    tambahLapangan(L, data);
}

// Alur pemesanan Lapangan sesuai diagram
void pesanLapangan(MLL &L, Queue &Q) {
    if (L.firstLapangan == NULL) {
        cout << "Belum ada lapangan yang tersedia!" << endl;
        return;
    }

    tampilkanLapangan(L);

    string kode;
    cout << "\nMasukkan Kode Lapangan" << endl;
    cin >> kode;

    NodeLapangan* lapangan = cariLapangan(L, kode);
    if (lapangan == NULL) {
        cout << "Lapangan tidak ditemukan!" << endl;
        return;
    }

    Booking data;
    int jam, menit;

    cin.ignore();
    cout << "Hari & Tanggal : " << endl;
    getline(cin, data.tanggal);

    cout << "Jam Mulai      : " << endl;
    cin >> jam;
    cout << "Menit Mulai    : " << endl;
    cin >> menit;
    cout << "Durasi (Jam)   : " << endl;
    cin >> data.durasi;

    data.jamMulai = (jam * 60) + menit;

    // Cek apakah jadwal bentrok dengan booking yang sudah ada
    NodeBooking* cek = lapangan->firstBooking;
    int jamSelesai = data.jamMulai + (data.durasi * 60);
    bool bentrok = false;

    while (cek != NULL) {
        if (cek->info.tanggal == data.tanggal) {
            int mulaiLama = cek->info.jamMulai;
            int selesaiLama = mulaiLama + (cek->info.durasi * 60);

            if (data.jamMulai < selesaiLama && jamSelesai > mulaiLama) {
                bentrok = true;
            }
        }
        cek = cek->next;
    }

    // Jika jadwal kosong
    if (bentrok == false) {
        cout << "\nJadwal tersedia! Silahkan isi data pelanggan." << endl;
        cin.ignore();
        cout << "ID Booking     : " << endl;
        getline(cin, data.idBooking);
        cout << "Nama Pelanggan : " << endl;
        getline(cin, data.namaPelanggan);

        tambahBooking(L, kode, data);
    } else {
        // Jika jadwal sudah terisi, tawarkan waiting list
        string mau;
        cout << "\nJadwal pada jam tersebut sudah terisi!" << endl;
        cout << "Mau masuk waiting list? (mau/tidak)" << endl;
        cin >> mau;

        if (mau == "mau") {
            cin.ignore();
            cout << "ID Booking     : ";
            getline(cin, data.idBooking);
            cout << "Nama Pelanggan : ";
            getline(cin, data.namaPelanggan);

            data.totalHarga = lapangan->info.hargaPerJam * data.durasi;
            enqueue(Q, kode, data);
        } else {
            cout << "Booking dibatalkan." << endl;
        }
    }
}

// Memindahkan antrean terdepan masuk ke daftar booking
void prosesWaitingList(MLL &L, Queue &Q) {
    if (isEmpty(Q)) {
        cout << "Waiting list masih kosong." << endl;
        return;
    }

    string kode;
    Booking data;
    dequeue(Q, kode, data);

    cout << "\nMemproses antrean atas nama: " << data.namaPelanggan << endl;
    tambahBooking(L, kode, data);
}