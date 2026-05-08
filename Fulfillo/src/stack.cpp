#include "../include/stack.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ============================================================
//  Fulfillo — Stack Implementation
//  Tanggung jawab: Orang A
// ============================================================

// Tambah aksi ke stack, hapus aksi terlama jika penuh
void Stack::push(Aksi aksi)
{
    if (isFull())
    {
        cout << "[STACK] History penuh. Aksi paling lama dihapus.\n";

        // Traverse ke node sebelum yang paling bawah, lalu hapus
        if (top->next == nullptr)
        {
            delete top;
            top = nullptr;
            size--;
        }
        else
        {
            StackNode *cur = top;
            while (cur->next->next != nullptr)
                cur = cur->next;
            delete cur->next;
            cur->next = nullptr;
            size--;
        }
    }

    StackNode *newNode = new StackNode(aksi);
    newNode->next = top;
    top  = newNode;
    size++;

    cout << "[STACK] Aksi disimpan: " << aksi.keterangan << "\n";
}

// Ambil dan hapus aksi teratas dari stack
Aksi Stack::pop()
{
    if (isEmpty())
    {
        cout << "[STACK] Tidak ada aksi yang bisa di-undo.\n";
        Barang kosong;
        return buatAksi(TAMBAH_BARANG, kosong, kosong, "");
    }

    StackNode *temp = top;
    Aksi       aksi = temp->data;
    top  = top->next;
    size--;
    delete temp;
    return aksi;
}

// Lihat aksi teratas tanpa menghapus
Aksi Stack::peek()
{
    if (isEmpty())
    {
        cout << "[STACK] Stack kosong.\n";
        Barang kosong;
        return buatAksi(TAMBAH_BARANG, kosong, kosong, "");
    }
    return top->data;
}

// Tampilkan semua history aksi di stack
void Stack::displayHistory()
{
    if (isEmpty())
    {
        cout << "\n  [Tidak ada history aksi]\n";
        return;
    }

    cout << "\n";
    cout << "  +================================================+\n";
    cout << "  |         HISTORY AKSI (UNDO LIST)               |\n";
    cout << "  +================================================+\n";

    StackNode *curr  = top;
    int        index = 1;
    while (curr != nullptr)
    {
        cout << "  | " << setw(2) << index << ". "
             << left << setw(15) << aksiTypeToString(curr->data.tipe)
             << " | " << setw(20) << curr->data.keterangan
             << " |\n";
        curr = curr->next;
        index++;
    }

    cout << "  +================================================+\n";
    cout << "  Total: " << size << " aksi tersimpan\n\n";
}

// Hapus semua node di stack
void Stack::clear()
{
    while (!isEmpty())
        pop();
}