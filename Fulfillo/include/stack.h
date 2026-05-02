#ifndef STACK_H
#define STACK_H

#include "Barang.h"
#include <string>
using namespace std;

// ============================================================
//  Fulfillo — Stack (Undo System)
//  Tanggung jawab: Orang A
//  
//  Command was made by AI (Yes again)
//  Stack ini menyimpan riwayat aksi yang dilakukan ADMIN.
//  Setiap aksi (tambah, edit, hapus) di-push ke stack.
//  Undo akan pop aksi terakhir dan membalikkan perubahan.
//
//  Hanya Admin yang bisa akses undo — cek role di UI.
// ============================================================

// Tipe aksi yang bisa di-undo
enum AksiType {
    TAMBAH_BARANG,
    HAPUS_BARANG,
    UPDATE_BARANG,
    TAMBAH_STOK,
    KURANG_STOK
};

// Satu aksi yang disimpan di stack
struct Aksi {
    AksiType tipe;
    Barang   barangSebelum;  // State barang SEBELUM aksi (untuk undo)
    Barang   barangSesudah;  // State barang SESUDAH aksi (untuk redo — minggu 2)
    string   keterangan;     // Deskripsi aksi, misal: "Hapus Kardus Box L"
};

// Node untuk linked list stack
struct StackNode {
    Aksi      data;
    StackNode* next;

    StackNode(Aksi a) : data(a), next(nullptr) {}
};

class Stack {
private:
    StackNode* top;
    int        size;
    int        maxSize;  // Batas maksimal history (default: 20)

public:
    Stack(int maxSize = 20);
    ~Stack();

    // Operasi utama
    void push(Aksi aksi);       // Tambah aksi ke stack
    Aksi pop();                  // Ambil & hapus aksi teratas
    Aksi peek();                 // Lihat aksi teratas tanpa hapus

    // Utility
    bool isEmpty();
    bool isFull();
    int  getSize();
    void clear();
    void displayHistory();       // Tampilkan semua history aksi
};

// ── Helper: buat Aksi dengan mudah ──────────────────────────

inline Aksi buatAksi(AksiType tipe, Barang sebelum, Barang sesudah, string ket) {
    Aksi a;
    a.tipe           = tipe;
    a.barangSebelum  = sebelum;
    a.barangSesudah  = sesudah;
    a.keterangan     = ket;
    return a;
}

// Konversi AksiType ke string untuk ditampilkan
inline string aksiTypeToString(AksiType tipe) {
    switch (tipe) {
        case TAMBAH_BARANG: return "Tambah Barang";
        case HAPUS_BARANG:  return "Hapus Barang";
        case UPDATE_BARANG: return "Update Barang";
        case TAMBAH_STOK:   return "Tambah Stok";
        case KURANG_STOK:   return "Kurang Stok";
        default:            return "Unknown";
    }
}

#endif