#include "../include/queue.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ======================== QUEUE IMPLEMENTATION ========================

// Tambah transaksi ke belakang queue, hapus terlama jika penuh
void Queue::enqueue(Transaksi t)
{
    if (isFull())
    {
        // Hapus yang paling lama (front)
        dequeue();
    }

    QueueNode *node = new QueueNode(t);
    if (isEmpty())
    {
        front = rear = node;
    }
    else
    {
        rear->next = node;
        rear       = node;
    }
    size++;
}

// Ambil dan hapus transaksi terdepan dari queue
Transaksi Queue::dequeue()
{
    if (isEmpty())
    {
        return {0, "", "", 0, ""};
    }

    QueueNode *temp  = front;
    Transaksi  data  = temp->data;
    front            = front->next;
    if (front == nullptr)
        rear = nullptr;
    size--;
    delete temp;
    return data;
}

// Lihat transaksi terdepan tanpa menghapus
Transaksi Queue::peek()
{
    if (isEmpty())
        return {0, "", "", 0, ""};
    return front->data;
}

// Tampilkan semua history transaksi di queue
void Queue::displayHistory()
{
    if (isEmpty())
    {
        cout << "  Belum ada transaksi.\n";
        return;
    }

    cout << "\n";
    for (int i = 0; i < 65; i++) cout << "=";
    cout << "\n";
    cout << left
         << setw(5)  << "No"
         << setw(6)  << "ID"
         << setw(22) << "Nama Barang"
         << setw(9)  << "Jenis"
         << setw(9)  << "Jumlah"
         << "Oleh\n";
    for (int i = 0; i < 65; i++) cout << "-";
    cout << "\n";

    QueueNode *cur   = front;
    int        index = 1;
    while (cur != nullptr)
    {
        cout << left
             << setw(5)  << index
             << setw(6)  << cur->data.idBarang
             << setw(22) << cur->data.namaBarang
             << setw(9)  << cur->data.jenis
             << setw(9)  << cur->data.jumlah
             << cur->data.oleh << "\n";
        cur = cur->next;
        index++;
    }

    for (int i = 0; i < 65; i++) cout << "=";
    cout << "\nTotal transaksi: " << size << "\n";
}

// Hapus semua node di queue
void Queue::clear()
{
    while (!isEmpty())
        dequeue();
}