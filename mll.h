
#ifndef MLL_H
#define MLL_H

#include <iostream>
#include <string>
using namespace std;

// Data lapangan sebagai Parent
struct Lapangan {
    string kodeLapangan;
    string namaLapangan;
    string jenisOlahraga;
    double hargaPerJam;
};

// Data booking sebagai Child
struct Booking {
    string idBooking;
    string namaPelanggan;
    string tanggal;

    // Jam menggunakan menit agar mudah menghitung jadwal
    int jamMulai;
    int durasi;

    double totalHarga;
};

// Node untuk menyimpan data Booking
struct NodeBooking {
    Booking info;
    NodeBooking* next;
};

// Node untuk menyimpan data Lapangan
struct NodeLapangan {
    Lapangan info;
    NodeLapangan* next;
    NodeBooking* firstBooking;
};

// Struktur utama Multi Linked List
struct MLL {
    NodeLapangan* firstLapangan;
};

// Fungsi dasar MLL
void createMLL(MLL &L);

NodeLapangan* createNodeLapangan(Lapangan data);
NodeBooking* createNodeBooking(Booking data);

// Fungsi untuk mengelola lapangan
void tambahLapangan(MLL &L, Lapangan data);
NodeLapangan* cariLapangan(MLL L, string kodeLapangan);
void tampilkanLapangan(MLL L);

// Fungsi untuk mengelola booking
void tambahBooking(MLL &L, string kodeLapangan, Booking data);
void tampilkanBooking(MLL L, string kodeLapangan);

#endif
