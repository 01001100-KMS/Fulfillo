#ifndef BARANG_H
#define BARANG_H

#include <string>
using namespace std;

// ======================== KONSTANTA ========================

const int MAX_TRANSAKSI = 200;

// ======================== STRUCT BARANG ========================
// Fulfillo — Struct Barang (gabungan final, jangan ubah field sembarangan)

struct Barang {
    int    id;          
    string nama;        
    string kategori;    
    int    stok;        
    double harga;
    int    minStok;     

    // Constructor default
    Barang() : id(0), stok(0), harga(0.0), minStok(0) {}

    // Constructor lengkap
    Barang(int id, string nama, string kategori, int stok, double harga, int minStok)
        : id(id), nama(nama), kategori(kategori),
          stok(stok), harga(harga), minStok(minStok) {}

    // Cek apakah stok menipis
    bool isLowStock() const {
        return stok <= minStok;
    }
};

// ======================== STRUCT TRANSAKSI ========================

struct Transaksi {
    int idBarang;
    string namaBarang;
    string jenis;   // "masuk" atau "keluar"
    int jumlah;
    string oleh;
};

#endif