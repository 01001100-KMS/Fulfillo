#include <iostream>
#include "include/Auth.h"
#include "include/UI.h"
#include "include/Inventory.h"
#include "include/Report.h"

using namespace std;

int main() {
    int pilihan;
    // 1. Inisialisasi sistem
    //    - Load data awal (dummy data / dari file)
    //    - Setup struktur data (BST, Queue, Stack)

    // 2. Tampil splash screen / nama app "Fulfillo"

    // 3. Login loop
    //    - Tampilkan form login
    //    - Validasi username & password
    //    - Dapat role → Admin atau Staff

    // 4. Menu loop (berdasarkan role)
    //    - Kalau Admin → tampil menu Admin
    //    - Kalau Staff → tampil menu Staff
    //    - Loop sampai user logout
     do {
        system("cls");

        int totalBarang = 100;
        int lowStock = 5;

        tampilkanDashboard(totalBarang, lowStock);
    
        tampilkanMenu();  
        cin >> pilihan;

        cout << endl;

        switch(pilihan) {
            case 1:
                cout << ">> Login" << endl;
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
                cout << ">> Keluar..." << endl;
                break;

            default:
                cout << ">> Pilihan tidak valid!" << endl;
    }
        cout << endl;

    } while(pilihan != 6);

    





    // 5. Cleanup & exit
    //    - Simpan data (kalau pakai file handling)
    //    - Goodbye message

    return 0;
}