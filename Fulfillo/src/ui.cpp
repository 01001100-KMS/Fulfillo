// ======================== ui.cpp ========================

#include "../include/ui.h"
#include "../include/auth.h"
#include "../include/inventory.h"
#include "../include/user.h"
#include "../include/bst.h"
#include "../include/stack.h"
#include "../include/report.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

// ======================== GLOBAL ========================

extern UserManager um;
extern User       *aktif;
extern BST         bst;
extern Stack       undoStack;

// ======================== INPUT HELPER ========================

void inputInt(string pesan, int &var)
{
    while (true)
    {
        cout << pesan;
        cin >> var;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[!] Input harus angka.\n";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
}

void inputDouble(string pesan, double &var)
{
    while (true)
    {
        cout << pesan;
        cin >> var;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[!] Input harus angka.\n";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
}

void header(string judul)
{
    cout << "\n====================================\n";
    cout << judul << endl;
    cout << "====================================\n";
}

void jeda()
{
    cout << "\nTekan ENTER untuk lanjut...";
    cin.get();
}

void cls()
{
    system("cls");
}

// ======================== DASHBOARD ========================

void tampilkanDashboard(int totalBarang, int lowStock)
{
    header(" DASHBOARD ");
    cout << "Total Barang : " << totalBarang << endl;
    cout << "Low Stock    : " << lowStock    << endl;
    cout << "====================================\n";

    if (lowStock > 0)
        cout << "[WARNING] Ada stok menipis!\n";
    else
        cout << "Semua stok aman.\n";
}

// ======================== INVENTORY ========================

void tampilkanListBarang()
{
    lihatStok();
}

void tampilkanLowStock()
{
    header(" LOW STOCK ");
    cout << "[Belum diimplementasi]\n";
    jeda();
}

void tampilkanLaporanStok()
{
    header(" LAPORAN STOK ");
    cout << "[Belum diimplementasi]\n";
    jeda();
}

void tampilkanHistory()
{
    riwayatTransaksi();
}

// ======================== USER ========================

void daftarUser()
{
    cls();
    header(" DAFTAR USER ");

    cout << left
         << setw(5)  << "No"
         << setw(20) << "Username"
         << "Role\n";
    cout << "------------------------------------\n";

    for (int i = 0; i < um.jml; i++)
    {
        cout << left
             << setw(5)  << (i + 1)
             << setw(20) << um.data[i].username
             << roleStr(um.data[i].role) << endl;
    }

    cout << "------------------------------------\n";
    cout << "Total User: " << um.jml << endl;

    jeda();
}

void registrasi()
{
    cls();
    header(" REGISTRASI USER ");

    if (um.jml >= UserManager::MAX)
    {
        cout << "[!] User penuh.\n";
        jeda();
        return;
    }

    string username, password;

    cout << "Username : ";
    getline(cin, username);

    cout << "Password : ";
    getline(cin, password);

    if (username.empty())
    {
        cout << "[!] Username kosong.\n";
        jeda();
        return;
    }

    if (password.empty())
    {
        cout << "[!] Password kosong.\n";
        jeda();
        return;
    }

    if (!semuaAlphanumeric(username))
    {
        cout << "[!] Username harus alphanumeric.\n";
        jeda();
        return;
    }

    if (!semuaAngka(password))
    {
        cout << "[!] Password harus angka.\n";
        jeda();
        return;
    }

    int pilRole;
    cout << "\n1. Admin\n";
    cout << "2. Staff\n";
    inputInt("Pilih role: ", pilRole);

    if (pilRole != 1 && pilRole != 2)
    {
        cout << "[!] Role tidak valid.\n";
        jeda();
        return;
    }

    Role roleBaru = (pilRole == 1) ? ADMIN : STAFF;
    bool berhasil = um.tambahUser(username, password, roleBaru);

    if (!berhasil)
    {
        cout << "[!] Username sudah dipakai.\n";
        jeda();
        return;
    }

    cout << "Registrasi berhasil.\n";
    jeda();
}

void hapusUser()
{
    cls();
    header(" HAPUS USER ");

    if (aktif == nullptr)
    {
        cout << "[!] Tidak ada user aktif.\n";
        jeda();
        return;
    }

    string username;
    cout << "Masukkan username: ";
    getline(cin, username);

    bool berhasil = um.hapusUser(username, aktif->username);

    if (!berhasil)
        cout << "[!] Gagal hapus user.\n";
    else
        cout << "User berhasil dihapus.\n";

    jeda();
}

// ======================== UNDO ========================

void undoAksi()
{
    cls();
    header(" UNDO AKSI TERAKHIR ");

    if (undoStack.isEmpty())
    {
        cout << "[!] Tidak ada aksi yang bisa di-undo.\n";
        jeda();
        return;
    }

    Aksi aksi = undoStack.peek();

    cout << "Aksi terakhir : " << aksi.keterangan << "\n";
    cout << "Tipe          : " << aksiTypeToString(aksi.tipe) << "\n\n";

    int konfirmasi;
    inputInt("Undo aksi ini? (1=Ya, 0=Tidak): ", konfirmasi);

    if (konfirmasi != 1)
    {
        cout << "Undo dibatalkan.\n";
        jeda();
        return;
    }

    undoStack.pop();

    switch (aksi.tipe)
    {
    case TAMBAH_BARANG:
        bst.remove(aksi.barangSesudah.nama);
        cout << "\nUndo berhasil: Barang '" << aksi.barangSesudah.nama << "' dihapus.\n";
        break;

    case TAMBAH_STOK:
    case KURANG_STOK:
    case UPDATE_BARANG:
    {
        Barang *b = bst.searchByName(aksi.barangSebelum.nama);
        if (b)
        {
            *b = aksi.barangSebelum;
            cout << "\nUndo berhasil: Stok '" << b->nama
                 << "' dikembalikan ke " << b->stok << ".\n";
        }
        else
        {
            cout << "\n[!] Barang tidak ditemukan, undo gagal.\n";
        }
        break;
    }

    default:
        cout << "\n[!] Tipe aksi tidak dikenali.\n";
    }

    jeda();
}

// ======================== MENU LAPORAN (SORTING) ========================

void menuLaporan()
{
    int pil;

    do
    {
        cls();
        header(" LAPORAN & PENGURUTAN ");

        cout << "Sorting Method:\n\n";
        cout << "1. Insertion Sort Stok Terendah ke Tertinggi\n";
        cout << "   (Prioritas restock)\n\n";
        cout << "2. Bubble Sort Harga Tertinggi ke Terendah\n";
        cout << "   (Laporan nilai stok)\n\n";
        cout << "3. Selection Sort Kategori A - Z\n";
        cout << "   (Grouping per kategori)\n\n";
        cout << "0. Kembali\n";

        inputInt("\nPilihan: ", pil);

        switch (pil)
        {
        case 1: reportSortByStok(bst);     break;
        case 2: reportSortByHarga(bst);    break;
        case 3: reportSortByKategori(bst); break;
        case 0: break;
        default:
            cout << "[!] Pilihan tidak valid.\n";
            jeda();
        }

    } while (pil != 0);
}

// ======================== MENU ADMIN ========================

void menuAdmin()
{
    if (aktif == nullptr)
    {
        cout << "[!] User tidak ditemukan.\n";
        return;
    }

    int pil;

    do
    {
        cls();
        header(" MENU ADMIN ");

        cout << "Login sebagai: " << aktif->username << " [ADMIN]\n\n";

        cout << "1. Registrasi User\n";
        cout << "2. Daftar User\n";
        cout << "3. Hapus User\n";
        cout << "4. Kelola Stok\n";
        cout << "5. Undo Aksi Terakhir\n";
        cout << "6. Laporan & Pengurutan\n";   // NEW
        cout << "0. Logout\n";

        inputInt("\nPilihan: ", pil);

        switch (pil)
        {
        case 1: registrasi();   break;
        case 2: daftarUser();   break;
        case 3: hapusUser();    break;
        case 4: menuKelola();   break;
        case 5: undoAksi();     break;
        case 6: menuLaporan();  break;         // NEW
        case 0:
            cout << "\nLogout berhasil.\n";
            break;
        default:
            cout << "[!] Pilihan tidak valid.\n";
            jeda();
        }

    } while (pil != 0);
}

// ======================== MENU STAFF ========================

void menuStaff()
{
    if (aktif == nullptr)
    {
        cout << "[!] User tidak ditemukan.\n";
        return;
    }

    int pil;

    do
    {
        cls();
        header(" MENU STAFF ");

        cout << "Login sebagai: " << aktif->username << " [STAFF]\n\n";

        cout << "1. Kelola Stok\n";
        cout << "2. Laporan & Pengurutan\n";   // NEW — staff bisa lihat laporan
        cout << "0. Logout\n";

        inputInt("\nPilihan: ", pil);

        switch (pil)
        {
        case 1: menuKelola();  break;
        case 2: menuLaporan(); break;          // NEW
        case 0:
            cout << "\nLogout berhasil.\n";
            break;
        default:
            cout << "[!] Pilihan tidak valid.\n";
            jeda();
        }

    } while (pil != 0);
}