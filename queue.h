#ifndef QUEUE_H
#define QUEUE_H
#include "mll.h"

// Node untuk menyimpan satu antrean waiting list
struct NodeQueue{
    string KodeLapangan; //menyimpan lapangan mana yang ditunggu
    Booking info; //menyimpan data pelanggan, tanggal, dan jam
    NodeQueue* next;
};

// Struktur utama Queue dengan penunjuk depan (head) dan belakang (tail)
struct Queue{
    NodeQueue* head;
    NodeQueue* tail;
};

// Operasi dasar Queue
void createQueue(Queue *Q);
bool isEmpty(Queue Q);

// Antrean baru
NodeQueue* createNodeQueue(string KodeLapangan, Booking data);

// Menambah antrean di belakang 
void enqueue(Queue &Q, string KodeLapangan, Booking data);

// Mengeluarkan antrean di depan
void dequeue(Queue &Q, string &KodeLapangan, Booking data);

// Menampilkan seluruh data waiting list
void tampilkanQueue(Queue Q);

#endif