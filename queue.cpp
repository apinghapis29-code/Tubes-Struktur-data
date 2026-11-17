#include "queue.h"

// Membuat queue kosong
void createQueue(Queue &Q) {
    Q.head = NULL;
    Q.tail = NULL;
}

// Mengecek apakah antrean kosong
bool isEmpty(Queue Q) {
    return (Q.head == NULL);
}

// Membuat gerbang antrean baru
NodeQueue* createNodeQueue(string KodeLapangan, Booking data) {
    NodeQueue* baru = new NodeQueue;
    baru->KodeLapangan = KodeLapangan;
    baru->info = data;
    baru->next = NULL;
    return baru;
}

// Masukkan pelanggan ke dalam antrean
void enqueue(Queue &Q, string KodeLapangan, Booking data) {
    NodeQueue* baru = createNodeQueue(KodeLapangan, data);

    if (isEmpty(Q)) {
        //jika kosong menuju ke antrean baru
        Q.head = baru;
        Q.tail = baru;
    } else {
        //jika sudah ada sambungkan ke belakang tail lalu geser tail
        Q.tail->next = baru;
        Q.tail = baru;
    }

    cout << "Berhasil ditambahkan ke dalam waiting list" << endl;
}

// Mengeluarkan pelanggan paling depan dari antrean
void dequeue(Queue &Q, string &KodeLapangan, Booking &data) {
    if (isEmpty(Q)) {
        cout << "Waiting List kosong" << endl;
        return;
    }

    NodeQueue* hapus = Q.head;
    KodeLapangan = hapus->KodeLapangan;
    data = hapus->info;

    if (Q.head == Q.tail) {
        // Jika hanya ada 1 orang di antrean, setelah keluar antrean jadi kosong
        Q.head = NULL;
        Q.tail = NULL;
    } else {
        // Geser head ke orang berikutnya
        Q.head = Q.head->next;
    }

    delete hapus; // Menghapus memori gerbong lama agar tidak bocor
}

// Menampilkan semua data waiting list
void tampilkanQueue(Queue Q) {
    if (isEmpty(Q)) {
        cout << "Antrean kosong" << endl;
        return;
    }

    NodeQueue* bantu = Q.head;
    int nomor = 1;

    cout << "\n===== DAFTAR WAITING LIST =====" << endl;
    while (bantu != NULL) {
        int jam = bantu->info.jamMulai / 60;
        int menit = bantu->info.jamMulai % 60;

        cout << "Antrean ke-" << nomor << endl;
        cout << "Kode Lapangan  : " << bantu->KodeLapangan << endl;
        cout << "ID Booking     : " << bantu->info.idBooking << endl;
        cout << "Nama Pelanggan : " << bantu->info.namaPelanggan << endl;
        cout << "Tanggal        : " << bantu->info.tanggal << endl;
        cout << "Jam Mulai      : ";
        if (jam < 10) cout << "0";
        cout << jam << ":";
        if (menit < 10) cout << "0";
        cout << menit << endl;
        cout << "Durasi         : " << bantu->info.durasi << " jam" << endl;
        cout << "-------------------------------" << endl;

        bantu = bantu->next;
        nomor++;
    }
    
}