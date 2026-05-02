#include <iostream>
#include "../include/ui.h"
#include <fstream>
#include <iomanip>
using namespace std;

// menampilkan menu utama sistem inventory yang berisi pilihan fitur yang dapat dipilih oleh pengguna.
void tampilkanMenu() {
    cout << "==================================" << endl;
    cout << "      SISTEM INVENTORY BARANG      " << endl;
    cout << "==================================" << endl;
    cout << "1. Login" << endl;
    cout << "2. Lihat Barang" << endl;
    cout << "3. Low Stock" << endl;
    cout << "4. Laporan Stok" << endl;
    cout << "5. History" << endl;
    cout << "6. Keluar" << endl;
    cout << "==================================" << endl;
    cout << "Pilih menu: ";
}

// menampilkan ringkasan data berupa total barang dan jumlah stok menipis, serta memberikan peringatan jika terdapat barang dengan stok rendah.

void tampilkanDashboard(int totalBarang, int lowStock) {
    cout << "==============================" << endl;
    cout << "         DASHBOARD            " << endl;
    cout << "==============================" << endl;

    cout << "Total Barang     : " << totalBarang << endl;
    cout << "Stok Menipis     : " << lowStock << endl;

    cout << "==============================" << endl;

    if (lowStock > 0) {
        cout << "⚠ WARNING: Ada barang dengan stok rendah!" << endl;
    } else {
        cout << "✔ Semua stok aman" << endl;
    }

    cout << "==============================" << endl;
}

// untuk membaca data barang dari file barang.txt dan menampilkannya dalam bentuk tabel yang rapi berisi ID, nama, dan stok barang.
void tampilkanListBarang() {
    ifstream file("../data/barang.txt");

    if (!file.is_open()) {
        cout << "Gagal membuka file barang!" << endl;
        return;
    }

    string id, nama;
    int stok;

    cout << "==========================================" << endl;
    cout << "              LIST BARANG                 " << endl;
    cout << "==========================================" << endl;

    cout << left << setw(10) << "ID"
         << setw(20) << "Nama"
         << setw(10) << "Stok" << endl;

    cout << "------------------------------------------" << endl;

    while (file >> id >> nama >> stok) {
        cout << left << setw(10) << id
             << setw(20) << nama
             << setw(10) << stok << endl;
    }

    cout << "==========================================" << endl;

    file.close();
}

// untuk membaca data dari file dan menampilkan daftar barang yang memiliki stok rendah (≤ 10), serta memberikan informasi jika semua stok dalam kondisi aman.
void tampilkanLowStock() {
    ifstream file("../data/barang.txt");

    if (!file.is_open()) {
        cout << "Gagal membuka file barang!" << endl;
        return;
    }

    string id, nama;
    int stok;

    cout << "========== LOW STOCK WARNING ==========" << endl;

    bool ada = false;

    while (file >> id >> nama >> stok) {
        if (stok <= 10) {
            cout << "⚠ " << nama << " (Stok: " << stok << ")" << endl;
            ada = true;
        }
    }

    if (!ada) {
        cout << "Semua stok aman ✔" << endl;
    }

    cout << "=======================================" << endl;

    file.close();
}

// untuk membaca data barang dari file dan menampilkan laporan stok lengkap yang berisi ID, nama, dan jumlah stok setiap barang.
void tampilkanLaporanStok() {
    ifstream file("../data/barang.txt");

    if (!file.is_open()) {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    string id, nama;
    int stok;

    cout << "=========== LAPORAN STOK ===========" << endl;

    while (file >> id >> nama >> stok) {
        cout << "ID: " << id 
             << " | Nama: " << nama 
             << " | Stok: " << stok << endl;
    }

    cout << "====================================" << endl;

    file.close();
}

// untuk menampilkan riwayat transaksi barang (masuk dan keluar) dalam bentuk daftar sederhana.
void tampilkanHistory() {
    cout << "========= HISTORY TRANSAKSI =========" << endl;

    cout << "[Masuk] Pensil +10" << endl;
    cout << "[Keluar] Buku -5" << endl;
    cout << "[Masuk] Penghapus +20" << endl;

    cout << "====================================" << endl;
}

