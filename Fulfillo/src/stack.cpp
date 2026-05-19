#include "../include/stack.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ======================== PUSH ========================

// FIX: hapus cout debug "[STACK] Aksi disimpan" — noise di UI
void Stack::push(Aksi aksi)
{
    if (isFull())
    {
        // Hapus aksi paling lama (paling bawah stack)
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
}

// ======================== POP ========================

// FIX: hapus cout debug — caller yang handle pesan error
Aksi Stack::pop()
{
    if (isEmpty())
    {
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

// ======================== PEEK ========================

// FIX: hapus cout debug
Aksi Stack::peek()
{
    if (isEmpty())
    {
        Barang kosong;
        return buatAksi(TAMBAH_BARANG, kosong, kosong, "");
    }
    return top->data;
}

// ======================== DISPLAY HISTORY ========================

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

// ======================== CLEAR ========================

void Stack::clear()
{
    while (!isEmpty())
        pop();
}