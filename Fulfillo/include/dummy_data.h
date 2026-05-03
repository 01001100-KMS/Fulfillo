#ifndef DUMMY_DATA_H
#define DUMMY_DATA_H

#include "bst.h"
#include "user.h"

// ======================== DUMMY DATA ========================

// Isi BST dengan data barang contoh untuk pengujian awal
inline void loadDummyBarang(BST &bst)
{
    //         id   nama                  kategori      stok   harga     minStok
    bst.insert({1,  "Aki Forklift",        "Elektrikal",   3,  450000,  2});
    bst.insert({2,  "Bubble Wrap Roll",    "Packaging",  480,   18000, 50});
    bst.insert({3,  "Cat Lantai Abu",      "Perawatan",   12,   95000,  5});
    bst.insert({4,  "Drum Plastik 200L",   "Wadah",       20,  185000,  5});
    bst.insert({5,  "Forklift Pallet",     "Alat Berat",   2, 8500000,  1});
    bst.insert({6,  "Gloves Karet",        "APD",        150,   12000, 30});
    bst.insert({7,  "Hand Truck Besi",     "Alat Angkut",  8,  320000,  3});
    bst.insert({8,  "Isolasi Coklat",      "Packaging",    4,    7500, 20});
    bst.insert({9,  "Jaring Pengaman",     "Keselamatan", 15,   75000,  5});
    bst.insert({10, "Kardus Box L",        "Packaging",  200,    5500, 30});
    bst.insert({11, "Label Barcode",       "Administrasi",500,    150,100});
    bst.insert({12, "Masker N95",          "APD",         80,   15000, 50});
    bst.insert({13, "Nylon Tali 10mm",     "Pengikat",    60,   22000, 10});
    bst.insert({14, "Oli Mesin Forklift",  "Perawatan",    6,  120000,  3});
    bst.insert({15, "Pallet Kayu",         "Wadah",       35,   85000, 10});
    bst.insert({16, "Rak Besi 5 Tingkat",  "Furnitur",     7,  950000,  2});
    bst.insert({17, "Selotip Bening",      "Packaging",    2,    8000, 15});
    bst.insert({18, "Timbangan Digital",   "Alat Ukur",    4,  275000,  2});
    bst.insert({19, "Uniform Gudang",      "APD",         25,  135000, 10});
    bst.insert({20, "Velcro Pengikat",     "Pengikat",    90,    9500, 20});
}

// Isi user manager dengan akun default untuk login awal
inline void loadDummyUser(UserManager &um)
{
    um.tambahUser("Heiza", "019", ADMIN);
    um.tambahUser("Arya",  "022", STAFF);
}

#endif