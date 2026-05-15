#include "include/barang.h"
#include "include/bst.h"
#include "include/user.h"
#include "include/dummy_data.h"
#include "include/auth.h"
#include "include/ui.h"
#include "include/inventory.h"
#include "include/report.h"
#include "include/queue.h"
#include "include/stack.h"
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
        cls();
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
            return 0; // Keluar dari program langsung
            break;

        default:
            cout << "[!] Pilihan tidak valid.\n";
            jeda();
        }

    } while (pilihan != 0);

    // ================== 4. PENUTUP ==================
    cout << "Program selesai.\n";
    return 0;
}