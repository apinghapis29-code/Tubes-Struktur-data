#ifndef QUEUE_H
#define QUEUE_H
#include "mll.h"

// node antrean
struct NodeQueue {
    string kodeLapangan;
    Booking info;
    NodeQueue* next;
};

// struct queue (FIFO)
struct Queue {
    NodeQueue* head;
    NodeQueue* tail;
};

void createQueue(Queue &Q);
bool isEmpty(Queue Q);

void enqueue(Queue &Q, string kodeLapangan, Booking data);

// kodeLapangan pakai & biar bisa dikembalikan
void dequeue(Queue &Q, string &kodeLapangan, Booking &data);

bool batalWaitingList(Queue &Q, string kodeLapangan, string namaPelanggan);

void tampilkanAntrean(Queue Q);

#endif