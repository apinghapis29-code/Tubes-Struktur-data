#ifndef FITUR_H
#define FITUR_H
#include "mll.h"
#include "queue.h"

// admin
void lapanganBaru(MLL &L);
void hapusLapanganMenu(MLL &L);
void prosesWaitingList(MLL &L, Queue &Q);

// user
void pesanLapangan(MLL &L, Queue &Q);
void cekBookingMenu(MLL L);
void batalBooking(MLL &L);
void batalWaitingListMenu(Queue &Q);

// simpan data
void simpanData(MLL L, Queue Q);
void muatData(MLL &L, Queue &Q);

#endif