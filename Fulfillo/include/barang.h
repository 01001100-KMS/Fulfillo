#ifndef BARANG_H
#define BARANG_H

#include <string>
using namespace std;


//  Fulfillo — Struct Barang
//  main struct
//  Jangan ubah field tbtb anj

struct Barang {
    int    id;          // UID barang (auto generate)
    string nama;        // Nama barang
    string kategori;    // Kategori (misal: "Packaging", "Equipment")
    int    stok;        // Current stock value
    double harga;       // Harga satuan
    int    minStok;     // Batas minimum stok (untuk low stock warning)

    // Constructor default
    Barang() : id(0), stok(0), harga(0.0), minStok(0) {}

    // Constructor lengkap
    Barang(int id, string nama, string kategori, int stok, double harga, int minStok)
        : id(id), nama(nama), kategori(kategori),
          stok(stok), harga(harga), minStok(minStok) {}

    // Cek apalah stock menipis
    bool isLowStock() const {
        return stok <= minStok;
    }
};

#endif