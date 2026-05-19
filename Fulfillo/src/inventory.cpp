#include "../include/inventory.h"
#include "../include/auth.h"
#include "../include/bst.h"
#include "../include/user.h"
#include "../include/ui.h"
#include "../include/queue.h"
#include "../include/stack.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// ======================== GLOBAL ========================

// FIX: pakai Queue untuk transaksi dan Stack untuk undo
// (array Transaksi[] + jmlTransaksi sudah dihapus dari main.cpp)
extern Queue  transaksiQueue;
extern Stack  undoStack;
extern BST    bst;
extern User  *aktif;

// ======================== HELPER ========================

int getLastId()
{
    vector<Barang> data = bst.inorder();
    int maxId = 0;
    for (auto &b : data)
        if (b.id > maxId)
            maxId = b.id;
    return maxId;
}

// Tampilkan tabel stok tanpa cls/header/jeda (reusable)
void tampilTabelStok()
{
    vector<Barang> data = bst.inorder();
    if (data.empty()) return;

    cout << left
         << setw(5)  << "ID"
         << setw(22) << "Nama Barang"
         << setw(15) << "Kategori"
         << setw(7)  << "Stok"
         << setw(12) << "Harga"
         << "Min\n";

    for (int i = 0; i < 68; i++) cout << "-";
    cout << "\n";

    for (auto &b : data)
    {
        string stokInfo = to_string(b.stok);
        if (b.isLowStock()) stokInfo += " (!)";

        cout << left
             << setw(5)  << b.id
             << setw(22) << b.nama
             << setw(15) << b.kategori
             << setw(7)  << stokInfo
             << setw(12) << b.harga
             << b.minStok << "\n";
    }

    for (int i = 0; i < 68; i++) cout << "-";
    cout << "\n";
}

// ======================== LIHAT STOK ========================

void lihatStok()
{
    cls();
    header(" STOK BARANG ");

    if (bst.size == 0)
    {
        cout << "Belum ada data barang.\n";
        jeda();
        return;
    }

    tampilTabelStok();
    cout << "Total: " << bst.size << " jenis barang\n";

    jeda();
}

// ======================== BARANG MASUK ========================

void barangMasuk()
{
    cls();
    header(" BARANG MASUK ");
    tampilTabelStok();
    cout << "\n";

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

        // FIX: enqueue ke Queue (bukan push ke array)
        transaksiQueue.enqueue({b.id, b.nama, "masuk", b.stok, aktif->username});

        // FIX: push ke Stack untuk undo
        undoStack.push(buatAksi(TAMBAH_BARANG, Barang(), b, "Tambah " + b.nama));

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

        Barang sebelum = *node; // simpan state sebelum diubah
        node->stok += jumlah;

        transaksiQueue.enqueue({id, node->nama, "masuk", jumlah, aktif->username});
        undoStack.push(buatAksi(TAMBAH_STOK, sebelum, *node, "Tambah stok " + node->nama));

        cout << "\nBarang masuk berhasil. Stok sekarang: " << node->stok << "\n";
    }

    jeda();
}

// ======================== BARANG KELUAR ========================

void barangKeluar()
{
    cls();
    header(" BARANG KELUAR ");

    // FIX: cek empty pakai bst.size SEBELUM tampilTabelStok
    // (sebelumnya inorder() dipanggil dua kali)
    if (bst.size == 0)
    {
        cout << "[!] Belum ada data barang.\n";
        jeda();
        return;
    }

    tampilTabelStok();
    cout << "\n";

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

    Barang sebelum = *node; // simpan state sebelum diubah
    node->stok -= jumlah;

    transaksiQueue.enqueue({id, node->nama, "keluar", jumlah, aktif->username});
    undoStack.push(buatAksi(KURANG_STOK, sebelum, *node, "Kurang stok " + node->nama));

    cout << "\nBarang keluar berhasil. Stok sekarang: " << node->stok << "\n";

    if (node->stok <= node->minStok)
        cout << "[!] Peringatan: stok rendah (" << node->minStok << ")!\n";

    jeda();
}

// ======================== RIWAYAT ========================

// FIX: pakai Queue::displayHistory() — tidak perlu loop manual lagi
void riwayatTransaksi()
{
    cls();
    header(" RIWAYAT TRANSAKSI ");
    transaksiQueue.displayHistory();
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
        case 1: barangMasuk();       break;
        case 2: barangKeluar();      break;
        case 3: lihatStok();         break;
        case 4: riwayatTransaksi();  break;
        case 0: break;
        default:
            cout << "[!] Pilihan tidak valid.\n";
            jeda();
        }

    } while (pil != 0);
}