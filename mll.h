#ifndef MLL_H
#define MLL_H

#include <iostream>
#include <string>
using namespace std;

// data lapangan
struct Lapangan {
    string kodeLapangan;
    string namaLapangan;
    string jenisOlahraga;
    double hargaPerJam;
};

// data booking
struct Booking {
    string namaPelanggan;
    string tanggal;
    int jamMulai;
    int durasi;
    double totalHarga;
};

struct NodeBooking {
    Booking info;
    NodeBooking* next;
};

struct NodeLapangan {
    Lapangan info;
    NodeLapangan* next;
    NodeBooking* firstBooking;
};

struct MLL {
    NodeLapangan* firstLapangan;
};

// dasar
void createMLL(MLL &L);

// admin
bool tambahLapangan(MLL &L, Lapangan data);
bool hapusLapangan(MLL &L, string kodeLapangan);
NodeLapangan* cariLapangan(MLL L, string kodeLapangan);
void tampilkanLapangan(MLL L);

// user
bool tambahBooking(MLL &L, string kodeLapangan, Booking data);
bool hapusBooking(MLL &L, string namaPelanggan, string kodeLapangan, string tanggal, int jamMulai);
NodeBooking* cariBooking(MLL L, string kodeLapangan, string namaPelanggan, string tanggal, int jamMulai);
bool cekBooking(MLL L, string namaPelanggan, string kodeLapangan, string tanggal, int jamMulai);
void tampilkanBooking(MLL L, string kodeLapangan);
string statusBooking(Booking data);

#endif