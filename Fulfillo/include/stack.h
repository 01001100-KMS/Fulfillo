#ifndef STACK_H
#define STACK_H

#include "barang.h"
#include <string>
using namespace std;

// ============================================================
//  Fulfillo — Stack (Undo System)
//  Tanggung jawab: Orang A
//
//  Stack ini menyimpan riwayat aksi yang dilakukan ADMIN.
//  Setiap aksi (tambah, edit, hapus) di-push ke stack.
//  Undo akan pop aksi terakhir dan membalikkan perubahan.
//
//  Hanya Admin yang bisa akses undo — cek role di UI.
// ============================================================

// ======================== ENUM AKSI ========================

enum AksiType
{
    TAMBAH_BARANG,
    HAPUS_BARANG,
    UPDATE_BARANG,
    TAMBAH_STOK,
    KURANG_STOK
};

inline string aksiTypeToString(AksiType tipe)
{
    switch (tipe)
    {
    case TAMBAH_BARANG: return "Tambah Barang";
    case HAPUS_BARANG:  return "Hapus Barang";
    case UPDATE_BARANG: return "Update Barang";
    case TAMBAH_STOK:   return "Tambah Stok";
    case KURANG_STOK:   return "Kurang Stok";
    default:            return "Unknown";
    }
}

// ======================== STRUCT AKSI ========================

struct Aksi
{
    AksiType tipe;
    Barang   barangSebelum; // State barang SEBELUM aksi (untuk undo)
    Barang   barangSesudah; // State barang SESUDAH aksi
    string   keterangan;    // Deskripsi aksi, misal: "Hapus Kardus Box L"
};

// ======================== STACK NODE ========================

struct StackNode
{
    Aksi       data;
    StackNode *next;
    StackNode(Aksi a) : data(a), next(nullptr) {}
};

// ======================== STACK ========================

struct Stack
{
    StackNode *top;
    int        size;
    int        maxSize;

    Stack(int maxSize = 20) : top(nullptr), size(0), maxSize(maxSize) {}
    ~Stack() { clear(); }

    bool isEmpty() { return top == nullptr; }
    bool isFull()  { return size >= maxSize; }
    int  getSize() { return size; }

    void push(Aksi aksi);
    Aksi pop();
    Aksi peek();
    void displayHistory();
    void clear();
};

// ======================== HELPER ========================

inline Aksi buatAksi(AksiType tipe, Barang sebelum, Barang sesudah, string ket)
{
    Aksi a;
    a.tipe          = tipe;
    a.barangSebelum = sebelum;
    a.barangSesudah = sesudah;
    a.keterangan    = ket;
    return a;
}

#endif