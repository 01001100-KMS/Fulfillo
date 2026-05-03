#include "include/barang.h"
#include "include/bst.h"
#include "include/user.h"
#include "include/dummy_data.h"
#include "include/auth.h"
#include "include/ui.h"
#include "src/auth.cpp"
#include <iostream>
using namespace std;

// ======================== GLOBAL DATA ========================

Transaksi transaksis[MAX_TRANSAKSI];
int jmlTransaksi = 0;

UserManager um;
BST bst;
User *aktif = nullptr;

// ======================== MAIN ========================

int main()
{
    // ================== 1. INISIALISASI ==================
    loadDummyBarang(bst);
    loadDummyUser(um);

    int pilihan;

    // ================== 2. MENU LOGIN ==================
    do
    {
        header(" SISTEM MANAJEMEN GUDANG ");
        cout << "1. Login\n";
        cout << "0. Keluar\n";

        inputInt("Pilihan: ", pilihan);

        switch (pilihan)
        {
        case 1:
            login(); // proses login (set user aktif)
            break;

        case 0:
            cout << "Keluar dari aplikasi...\n";
            break;

        default:
            cout << "[!] Pilihan tidak valid.\n";
            jeda();
        }

    } while (pilihan != 0);

    // ================== 3. MENU UTAMA (SETELAH LOGIN) ==================
    // (Simulasi menu sistem Fulfillo)

    int menu;
    do
    {
        system("cls");

        int totalBarang = 100;
        int lowStock = 5;

        tampilkanDashboard(totalBarang, lowStock);
        tampilkanMenu();

        cin >> menu;
        cout << endl;

        switch (menu)
        {
        case 1:
            cout << ">> Login\n";
            break;

        case 2:
            tampilkanListBarang();
            break;

        case 3:
            tampilkanLowStock();
            break;

        case 4:
            tampilkanLaporanStok();
            break;

        case 5:
            tampilkanHistory();
            break;

        case 6:
            cout << ">> Keluar...\n";
            break;

        default:
            cout << ">> Pilihan tidak valid!\n";
        }

        cout << endl;

    } while (menu != 6);

    // ================== 4. PENUTUP ==================
    cout << "Program selesai.\n";
    return 0;
}