#ifndef FITUR_H
#define FITUR_H

#include "mll.h"
#include "queue.h"

// Fungsi pembantu untuk mengecek apakah jadwal lapangan bentrok
bool cekJadwalBentrok(NodeLapangan* lapangan, string tanggal, int jamMulai, int durasi);

// Fitur utama pemesanan lapangan (mengikuti diagram alur MLL + Waiting List)
bool prosesBooking(MLL &L, Queue &Q);

// Fitur memproses antrean paling depan dari Waiting List masuk ke Booking
void prosesAntreanBerikutnya(MLL &L, Queue *Q);

#endif