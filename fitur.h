#ifndef FITUR_H
#define FITUR_H

#include "mll.h"
#include "queue.h"

// Fitur untuk input data lapangan baru
void inputLapanganBaru(MLL &L);

// Fitur utama untuk memesan lapangan (MLL + Waiting List)
void pesanLapangan(MLL &L, Queue &Q);

// Fitut utama memproses antrean waiting list paling depan
void prosesWaitingLint(MLL &L, Queue &Q);

#endif