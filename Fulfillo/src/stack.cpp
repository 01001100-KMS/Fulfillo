#include "../include/Stack.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ============================================================
//  Fulfillo — Stack Implementation
//  Tanggung jawab: Orang A
//  What do u expect?
// ============================================================

// ── Constructor & Destructor ─────────────────────────────────

Stack::Stack(int maxSize) : top(nullptr), size(0), maxSize(maxSize) {}

Stack::~Stack() {
    clear();
}

// ── Operasi Utama ────────────────────────────────────────────

void Stack::push(Aksi aksi) {
    if (isFull()) {
        // Stack penuh — hapus aksi paling lama (bottom)
        // Implementasi sederhana: hapus semua kalau penuh (bisa diimprove)
        cout << "[STACK] History penuh. Aksi paling lama dihapus.\n";

        // Rebuild stack tanpa elemen terbawah
        // Simpan semua ke array sementara
        Aksi temp[maxSize];
        int  count = 0;
        StackNode* curr = top;
        while (curr != nullptr) {
            temp[count++] = curr->data;
            curr = curr->next;
        }
        clear();
        // Re-push semua kecuali yang paling bawah (index terakhir)
        for (int i = count - 2; i >= 0; i--) {
            StackNode* newNode = new StackNode(temp[i]);
            newNode->next = top;
            top = newNode;
            size++;
        }
    }

    StackNode* newNode = new StackNode(aksi);
    newNode->next = top;
    top  = newNode;
    size++;

    cout << "[STACK] Aksi disimpan: " << aksi.keterangan << "\n";
}

Aksi Stack::pop() {
    if (isEmpty()) {
        cout << "[STACK] Tidak ada aksi yang bisa di-undo.\n";
        // Return aksi kosong
        Barang kosong;
        return buatAksi(TAMBAH_BARANG, kosong, kosong, "");
    }

    StackNode* temp = top;
    Aksi       aksi = temp->data;
    top  = top->next;
    size--;
    delete temp;

    return aksi;
}

Aksi Stack::peek() {
    if (isEmpty()) {
        cout << "[STACK] Stack kosong.\n";
        Barang kosong;
        return buatAksi(TAMBAH_BARANG, kosong, kosong, "");
    }
    return top->data;
}

// ── Utility ──────────────────────────────────────────────────

bool Stack::isEmpty() {
    return top == nullptr;
}

bool Stack::isFull() {
    return size >= maxSize;
}

int Stack::getSize() {
    return size;
}

void Stack::clear() {
    while (!isEmpty()) {
        pop();
    }
}

void Stack::displayHistory() {
    if (isEmpty()) {
        cout << "\n  [Tidak ada history aksi]\n";
        return;
    }

    cout << "\n";
    cout << "  ╔══════════════════════════════════════════════╗\n";
    cout << "  ║           HISTORY AKSI (UNDO LIST)           ║\n";
    cout << "  ╠══════════════════════════════════════════════╣\n";

    StackNode* curr  = top;
    int        index = 1;
    while (curr != nullptr) {
        cout << "  ║  " << setw(2) << index << ". "
             << left << setw(15) << aksiTypeToString(curr->data.tipe)
             << " | " << setw(20) << curr->data.keterangan
             << " ║\n";
        curr = curr->next;
        index++;
    }

    cout << "  ╚══════════════════════════════════════════════╝\n";
    cout << "  Total: " << size << " aksi tersimpan\n\n";
}