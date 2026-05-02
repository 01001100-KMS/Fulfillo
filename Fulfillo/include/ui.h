#ifndef UI_H
#define UI_H

// menampilkan menu utama
void tampilkanMenu();

// menampilkan dashboard (total & stok menipis)
void tampilkanDashboard(int totalBarang, int lowStock);

// menampilkan daftar semua barang dalm bentuk tabel barang.txt
void tampilkanListBarang();

// menampilkan barang dengan stok rendah saja
void tampilkanLowStock();

// menampilkan laporan stok lengkap
void tampilkanLaporanStok();

// menampilkan riwayat transaksi
void tampilkanHistory();

#endif