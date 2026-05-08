#ifndef QUEUE_H
#define QUEUE_H

#include "barang.h"
#include <string>
using namespace std;

// ======================== QUEUE NODE ========================

struct QueueNode
{
    Transaksi  data;
    QueueNode *next;
    QueueNode(Transaksi t) : data(t), next(nullptr) {}
};

// ======================== QUEUE ========================

struct Queue
{
    QueueNode *front;
    QueueNode *rear;
    int        size;
    int        maxSize;

    Queue(int maxSize = 100) : front(nullptr), rear(nullptr), size(0), maxSize(maxSize) {}

    bool isEmpty() { return front == nullptr; }
    bool isFull()  { return size >= maxSize; }

    void      enqueue(Transaksi t);
    Transaksi dequeue();
    Transaksi peek();
    void      displayHistory();
    void      clear();
};

#endif