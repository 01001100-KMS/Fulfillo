#include "../include/ui.h"
#include "../include/auth.h"
#include "../src/auth.cpp"
#include "../include/inventory.h"
#include "../include/user.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
using namespace std;

// ======================== HELPER ========================

void header(string judul) {
    system("cls"); // Windows
    cout << "====================================\n";
    cout << judul << endl;
    cout << "====================================\n";
}

void jeda() {
    cout << "\nTekan ENTER untuk lanjut...";
    cin.ignore();
    cin.get();
}

void inputInt(string pesan, int &var) {
    while (true) {
        cout << pesan;
        cin >> var;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[!] Input harus angka.\n";
        } else {
            cin.ignore(1000, '\n');
            break;
        }
    }
}

// ======================== GLOBAL ========================

extern UserManager um;
extern User *aktif;

// ======================== DASHBOARD & MENU UTAMA ========================

void tampilkanMenu() {
    cout << "==================================\n";
    cout << "      SISTEM INVENTORY BARANG      \n";
    cout << "==================================\n";
    cout << "1. Login\n";
    cout << "2. Lihat Barang\n";
    cout << "3. Low Stock\n";
    cout << "4. Laporan Stok\n";
    cout << "5. History\n";
    cout << "6. Keluar\n";
    cout << "==================================\n";
    cout << "Pilih menu: ";
}

void tampilkanDashboard(int totalBarang, int lowStock) {
    cout << "==============================\n";
    cout << "         DASHBOARD            \n";
    cout << "==============================\n";

    cout << "Total Barang : " << totalBarang << endl;
    cout << "Stok Menipis : " << lowStock << endl;

    cout << "==============================\n";

    if (lowStock > 0)
        cout << "⚠ WARNING: Ada barang dengan stok rendah!\n";
    else
        cout << "✔ Semua stok aman\n";

    cout << "==============================\n";
}

// ======================== INVENTORY VIEW ========================

void tampilkanListBarang() {
    ifstream file("../data/barang.txt");

    if (!file.is_open()) {
        cout << "Gagal membuka file barang!\n";
        return;
    }

    string id, nama;
    int stok;

    cout << "==========================================\n";
    cout << "              LIST BARANG                 \n";
    cout << "==========================================\n";

    cout << left << setw(10) << "ID"
         << setw(20) << "Nama"
         << setw(10) << "Stok" << endl;

    cout << "------------------------------------------\n";

    while (file >> id >> nama >> stok) {
        cout << left << setw(10) << id
             << setw(20) << nama
             << setw(10) << stok << endl;
    }

    cout << "==========================================\n";
    file.close();
}

void tampilkanLowStock() {
    ifstream file("../data/barang.txt");

    if (!file.is_open()) {
        cout << "Gagal membuka file barang!\n";
        return;
    }

    string id, nama;
    int stok;
    bool ada = false;

    cout << "========== LOW STOCK WARNING ==========\n";

    while (file >> id >> nama >> stok) {
        if (stok <= 10) {
            cout << "⚠ " << nama << " (Stok: " << stok << ")\n";
            ada = true;
        }
    }

    if (!ada)
        cout << "Semua stok aman ✔\n";

    cout << "=======================================\n";
    file.close();
}

void tampilkanLaporanStok() {
    ifstream file("../data/barang.txt");

    if (!file.is_open()) {
        cout << "Gagal membuka file!\n";
        return;
    }

    string id, nama;
    int stok;

    cout << "=========== LAPORAN STOK ===========\n";

    while (file >> id >> nama >> stok) {
        cout << "ID: " << id
             << " | Nama: " << nama
             << " | Stok: " << stok << endl;
    }

    cout << "====================================\n";
    file.close();
}

void tampilkanHistory() {
    cout << "========= HISTORY TRANSAKSI =========\n";
    cout << "[Masuk] Pensil +10\n";
    cout << "[Keluar] Buku -5\n";
    cout << "[Masuk] Penghapus +20\n";
    cout << "====================================\n";
}

// ======================== USER MANAGEMENT (ADMIN) ========================

void daftarUser() {
    header(" DAFTAR USER ");

    cout << left << setw(5) << "No"
         << setw(20) << "Username"
         << "Role\n";

    for (int i = 0; i < 35; i++) cout << "-";
    cout << "\n";

    for (int i = 0; i < um.jml; i++) {
        cout << left << setw(5) << (i + 1)
             << setw(20) << um.data[i].username
             << roleStr(um.data[i].role) << "\n";
    }

    for (int i = 0; i < 35; i++) cout << "-";
    cout << "\nTotal: " << um.jml << " user\n";

    jeda();
}

void registrasi() {
    header(" REGISTRASI USER BARU ");

    if (um.jml >= UserManager::MAX) {
        cout << "[!] User sudah penuh.\n";
        jeda();
        return;
    }

    string username, password;

    cout << "Username : ";
    cin >> username;
    cout << "Password : ";
    cin >> password;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (username.empty() || !semuaAlphanumeric(username)) {
        cout << "[!] Username tidak valid.\n";
        jeda();
        return;
    }

    if (password.empty() || !semuaAngka(password)) {
        cout << "[!] Password harus angka.\n";
        jeda();
        return;
    }

    int pilRole;
    cout << "Role (1=Admin, 2=Staff): ";
    inputInt("", pilRole);

    if (pilRole != 1 && pilRole != 2) {
        cout << "[!] Role tidak valid.\n";
        jeda();
        return;
    }

    Role r = (pilRole == 1) ? ADMIN : STAFF;

    if (!um.tambahUser(username, password, r)) {
        cout << "[!] Username sudah dipakai.\n";
        jeda();
        return;
    }

    cout << "Registrasi berhasil!\n";
    jeda();
}

void hapusUser() {
    header(" HAPUS USER ");

    string target;
    cout << "Masukkan username: ";
    cin >> target;

    if (!um.hapusUser(target, aktif->username)) {
        cout << "[!] Gagal hapus user.\n";
    } else {
        cout << "User berhasil dihapus.\n";
    }

    jeda();
}

// ======================== MENU ROLE ========================

void menuAdmin() {
    int pil;
    do {
        header(" MENU ADMIN ");
        cout << "Login sebagai: " << aktif->username << " [admin]\n\n";
        cout << "1. Registrasi User\n";
        cout << "2. Daftar User\n";
        cout << "3. Hapus User\n";
        cout << "4. Kelola Stok\n";
        cout << "0. Logout\n";

        inputInt("Pilihan: ", pil);

        switch (pil) {
        case 1: registrasi(); break;
        case 2: daftarUser(); break;
        case 3: hapusUser(); break;
        case 4: menuKelola(); break;
        }
    } while (pil != 0);
}

void menuStaff() {
    int pil;
    do {
        header(" MENU STAFF ");
        cout << "Login sebagai: " << aktif->username << " [staff]\n\n";
        cout << "1. Kelola Stok\n";
        cout << "0. Logout\n";

        inputInt("Pilihan: ", pil);

        if (pil == 1)
            menuKelola();

    } while (pil != 0);

void inputDouble(string pesan, double &var) {
    while (true) {
        cout << pesan;
        cin >> var;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[!] Input harus angka (boleh desimal).\n";
        } else {
            cin.ignore(1000, '\n');
            break;
        }
    }
}
}