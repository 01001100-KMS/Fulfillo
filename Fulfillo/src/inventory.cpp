#include "../include/inventory.h"
#include "../include/auth.h"
#include "../include/bst.h"
#include "../include/user.h"
#include "../include/ui.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// ======================== GLOBAL ========================

extern Transaksi transaksis[];
extern int jmlTransaksi;
extern BST bst;
extern User *aktif;

// ======================== HELPER ========================

// Ambil ID terbesar (biar auto increment)
int getLastId()
{
    vector<Barang> data = bst.inorder();
    int maxId = 0;

    for (auto &b : data)
        if (b.id > maxId)
            maxId = b.id;

    return maxId;
}

// ======================== FITUR STOK ========================

void lihatStok()
{
    cls();
    header(" STOK BARANG ");

    vector<Barang> data = bst.inorder();

    if (data.empty())
    {
        cout << "Belum ada data barang.\n";
        jeda();
        return;
    }

    cout << left
         << setw(5) << "ID"
         << setw(22) << "Nama Barang"
         << setw(15) << "Kategori"
         << setw(7) << "Stok"
         << setw(12) << "Harga"
         << "Min\n";

    for (int i = 0; i < 68; i++)
        cout << "-";
    cout << "\n";

    for (auto &b : data)
    {
        string stokInfo = to_string(b.stok);
        if (b.isLowStock())
            stokInfo += " (!)";

        cout << left
             << setw(5) << b.id
             << setw(22) << b.nama
             << setw(15) << b.kategori
             << setw(7) << stokInfo
             << setw(12) << b.harga
             << b.minStok << "\n";
    }

    for (int i = 0; i < 68; i++)
        cout << "-";
    cout << "\nTotal: " << data.size() << " jenis barang\n";

    jeda();
}

// ======================== BARANG MASUK ========================

void barangMasuk()
{
    cls();
    header(" BARANG MASUK ");

    int id;
    inputInt("ID Barang (0 = tambah baru): ", id);

    if (id == 0)
    {
        Barang b;
        b.id = getLastId() + 1;

        cout << "ID otomatis : " << b.id << "\n";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nama Barang : ";
        getline(cin, b.nama);

        cout << "Kategori    : ";
        getline(cin, b.kategori);

        if (b.nama.empty() || b.kategori.empty())
        {
            cout << "[!] Nama dan kategori tidak boleh kosong.\n";
            jeda();
            return;
        }

        inputDouble("Harga       : ", b.harga);
        inputInt("Min Stok    : ", b.minStok);
        inputInt("Jumlah Masuk: ", b.stok);

        if (b.stok <= 0 || b.harga <= 0 || b.minStok <= 0)
        {
            cout << "[!] Nilai harus lebih dari 0.\n";
            jeda();
            return;
        }

        bst.insert(b);

        if (jmlTransaksi < MAX_TRANSAKSI)
            transaksis[jmlTransaksi++] = {
                b.id, b.nama, "masuk", b.stok, aktif->username};

        cout << "\nBarang baru '" << b.nama << "' berhasil ditambahkan.\n";
    }
    else
    {
        Barang *node = bst.searchById(id);

        if (!node)
        {
            cout << "[!] Barang dengan ID " << id << " tidak ditemukan.\n";
            jeda();
            return;
        }

        cout << "Nama Barang  : " << node->nama << "\n";
        cout << "Stok Saat Ini: " << node->stok << "\n";

        int jumlah;
        inputInt("Jumlah Masuk : ", jumlah);

        if (jumlah <= 0)
        {
            cout << "[!] Jumlah harus lebih dari 0.\n";
            jeda();
            return;
        }

        node->stok += jumlah;

        if (jmlTransaksi < MAX_TRANSAKSI)
            transaksis[jmlTransaksi++] = {
                id, node->nama, "masuk", jumlah, aktif->username};

        cout << "\nBarang masuk berhasil. Stok sekarang: " << node->stok << "\n";
    }

    jeda();
}

// ======================== BARANG KELUAR ========================

void barangKeluar()
{
    cls();
    header(" BARANG KELUAR ");

    vector<Barang> data = bst.inorder();

    if (data.empty())
    {
        cout << "[!] Belum ada data barang.\n";
        jeda();
        return;
    }

    int id, jumlah;
    inputInt("ID Barang    : ", id);

    Barang *node = bst.searchById(id);

    if (!node)
    {
        cout << "[!] Barang dengan ID " << id << " tidak ditemukan.\n";
        jeda();
        return;
    }

    cout << "Nama Barang   : " << node->nama << "\n";
    cout << "Stok Saat Ini : " << node->stok << "\n";

    inputInt("Jumlah Keluar : ", jumlah);

    if (jumlah <= 0)
    {
        cout << "[!] Jumlah harus lebih dari 0.\n";
        jeda();
        return;
    }

    if (jumlah > node->stok)
    {
        cout << "[!] Stok tidak mencukupi. Stok tersedia: " << node->stok << "\n";
        jeda();
        return;
    }

    node->stok -= jumlah;

    if (jmlTransaksi < MAX_TRANSAKSI)
        transaksis[jmlTransaksi++] = {
            id, node->nama, "keluar", jumlah, aktif->username};

    cout << "\nBarang keluar berhasil. Stok sekarang: " << node->stok << "\n";

    if (node->stok <= node->minStok)
        cout << "[!] Peringatan: stok rendah (" << node->minStok << ")!\n";

    jeda();
}

// ======================== RIWAYAT ========================

void riwayatTransaksi()
{
    cls();
    header(" RIWAYAT TRANSAKSI ");

    if (jmlTransaksi == 0)
    {
        cout << "Belum ada transaksi.\n";
        jeda();
        return;
    }

    cout << left
         << setw(5) << "No"
         << setw(6) << "ID"
         << setw(22) << "Nama Barang"
         << setw(9) << "Jenis"
         << setw(9) << "Jumlah"
         << "Oleh\n";

    for (int i = 0; i < 62; i++)
        cout << "-";
    cout << "\n";

    for (int i = 0; i < jmlTransaksi; i++)
    {
        cout << left
             << setw(5) << (i + 1)
             << setw(6) << transaksis[i].idBarang
             << setw(22) << transaksis[i].namaBarang
             << setw(9) << transaksis[i].jenis
             << setw(9) << transaksis[i].jumlah
             << transaksis[i].oleh << "\n";
    }

    for (int i = 0; i < 62; i++)
        cout << "-";
    cout << "\nTotal transaksi: " << jmlTransaksi << "\n";

    jeda();
}

// ======================== MENU ========================

void menuKelola()
{
    int pil;

    do
    {
        cls();
        header(" KELOLA STOK ");
        cout << "1. Barang Masuk\n";
        cout << "2. Barang Keluar\n";
        cout << "3. Lihat Stok Barang\n";
        cout << "4. Riwayat Transaksi\n";
        cout << "0. Kembali\n";

        inputInt("Pilihan: ", pil);

        switch (pil)
        {
        case 1:
            barangMasuk();
            break;
        case 2:
            barangKeluar();
            break;
        case 3:
            lihatStok();
            break;
        case 4:
            riwayatTransaksi();
            break;
        case 0:
            break;
        default:
            cout << "[!] Pilihan tidak valid.\n";
            jeda();
        }

    } while (pil != 0);
}