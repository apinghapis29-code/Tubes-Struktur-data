#include "queue.h"
#include <iomanip>

// bikin queue kosong
void createQueue(Queue &Q) {
    Q.head = NULL;
    Q.tail = NULL;
}

// cek queue kosong
bool isEmpty(Queue Q) {
    return Q.head == NULL;
}

// tambah antrean di belakang
void enqueue(Queue &Q, string kodeLapangan, Booking data) {
    NodeQueue* baru = new NodeQueue;
    baru->kodeLapangan = kodeLapangan;
    baru->info = data;
    baru->next = NULL;

    if (isEmpty(Q)) {
        // antrean kosong
        Q.head = baru;
        Q.tail = baru;
    } else {
        // sambung di belakang
        Q.tail->next = baru;
        Q.tail = baru;
    }

    cout << "BERHASIL MASUK WAITING LIST!!" << endl;
}

// keluarkan antrean paling depan
void dequeue(Queue &Q, string &kodeLapangan, Booking &data) {
    if (isEmpty(Q)) {
        cout << "WAITING LIST KOSONG!!" << endl;
        return;
    }

    NodeQueue* hapus = Q.head;
    kodeLapangan = hapus->kodeLapangan;
    data = hapus->info;

    if (Q.head == Q.tail) {
        // cuma 1 node
        Q.head = NULL;
        Q.tail = NULL;
    } else {
        Q.head = Q.head->next;
    }

    delete hapus;
}

// batal waiting list (user berubah pikiran)
bool batalWaitingList(Queue &Q, string kodeLapangan, string namaPelanggan) {
    if (isEmpty(Q)) {
        cout << "WAITING LIST KOSONG!!" << endl;
        return false;
    }

    // cari dulu node-nya
    NodeQueue* hapus = Q.head;
    NodeQueue* sebelum = NULL;
    bool ketemu = false;

    while (hapus != NULL) {
        if (hapus->info.namaPelanggan == namaPelanggan &&
            hapus->kodeLapangan == kodeLapangan) {
            ketemu = true;
            break;
        }
        sebelum = hapus;
        hapus = hapus->next;
    }

    if (!ketemu) {
        cout << "ANTREAN TIDAK DITEMUKAN!!" << endl;
        return false;
    }

    // lepas dari rantai (queue ada head & tail, jadi ada 4 kasus)
    if (sebelum == NULL) {
        // node pertama
        Q.head = hapus->next;
        if (Q.head == NULL) {
            Q.tail = NULL;
        }
    } else if (hapus == Q.tail) {
        // node terakhir
        sebelum->next = NULL;
        Q.tail = sebelum;
    } else {
        // node tengah
        sebelum->next = hapus->next;
    }

    delete hapus;
    cout << "ANTREAN BERHASIL DIBATALKAN!!" << endl;
    return true;
}

// tampilkan semua antrean
void tampilkanAntrean(Queue Q) {
    if (isEmpty(Q)) {
        cout << "WAITING LIST KOSONG!!" << endl;
        return;
    }

    cout << "\n========== DAFTAR WAITING LIST ==========" << endl;
    cout << "+------+--------------------+----------+--------------+----------+----------+-----------------+" << endl;
    cout << "| " << left << setw(4)  << "No"
         << " | " << setw(18) << "Nama"
         << " | " << setw(8)  << "Kode"
         << " | " << setw(12) << "Tanggal"
         << " | " << setw(8)  << "Jam"
         << " | " << setw(8)  << "Durasi"
         << " | " << setw(15) << "Total"
         << " |" << endl;
    cout << "+------+--------------------+----------+--------------+----------+----------+-----------------+" << endl;

    NodeQueue* cek = Q.head;
    int nomor = 1;

    while (cek != NULL) {
        int jam = cek->info.jamMulai / 60;
        int menit = cek->info.jamMulai % 60;

        string jamStr = (jam < 10 ? "0" : "") + to_string(jam) + ":" +
                        (menit < 10 ? "0" : "") + to_string(menit);
        string durasiStr = to_string(cek->info.durasi) + " jam";
        string totalStr = "Rp" + to_string((int)cek->info.totalHarga);

        cout << "| " << left << setw(4)  << nomor
             << " | " << setw(18) << cek->info.namaPelanggan
             << " | " << setw(8)  << cek->kodeLapangan
             << " | " << setw(12) << cek->info.tanggal
             << " | " << setw(8)  << jamStr
             << " | " << setw(8)  << durasiStr
             << " | " << setw(15) << totalStr
             << " |" << endl;

        cek = cek->next;
        nomor++;
    }
    cout << "+------+--------------------+----------+--------------+----------+----------+-----------------+" << endl;
}