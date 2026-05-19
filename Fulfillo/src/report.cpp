#include "../include/report.h"
#include "../include/auth.h"
#include "../include/bst.h"
#include "../include/queue.h"
#include "../include/stack.h"
#include "../include/sort.h"
#include "../include/ui.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ======================== REPORT IMPLEMENTATION ========================

// Tampilkan semua barang dengan stok di bawah minimum
void reportLowStock(BST &bst)
{
    header(" LAPORAN LOW STOCK ");

    if (bst.size == 0)
    {
        cout << "Belum ada data barang.\n";
        jeda();
        return;
    }

    Barang arr[200];
    int    idx = 0;
    bst.inorder(bst.root, arr, idx);

    int count = 0;

    cout << left
         << setw(5)  << "ID"
         << setw(22) << "Nama Barang"
         << setw(15) << "Kategori"
         << setw(8)  << "Stok"
         << setw(8)  << "Min"
         << "Status\n";
    for (int i = 0; i < 65; i++) cout << "-";
    cout << "\n";

    for (int i = 0; i < idx; i++)
    {
        if (arr[i].stok <= arr[i].minStok)
        {
            cout << left
                 << setw(5)  << arr[i].id
                 << setw(22) << arr[i].nama
                 << setw(15) << arr[i].kategori
                 << setw(8)  << arr[i].stok
                 << setw(8)  << arr[i].minStok
                 << "(!) MENIPIS\n";
            count++;
        }
    }

    for (int i = 0; i < 65; i++) cout << "-";
    cout << "\n";

    if (count == 0)
        cout << "Semua stok aman. Tidak ada barang yang menipis.\n";
    else
        cout << "Total barang menipis: " << count << " jenis\n";

    jeda();
}

// Tampilkan laporan lengkap semua stok barang
void reportSemuaStok(BST &bst)
{
    header(" LAPORAN STOK LENGKAP ");

    if (bst.size == 0)
    {
        cout << "Belum ada data barang.\n";
        jeda();
        return;
    }

    Barang arr[200];
    int    idx = 0;
    bst.inorder(bst.root, arr, idx);

    int totalNilai = 0;
    int lowCount   = 0;

    cout << left
         << setw(5)  << "ID"
         << setw(22) << "Nama Barang"
         << setw(15) << "Kategori"
         << setw(8)  << "Stok"
         << setw(12) << "Harga"
         << setw(8)  << "Min"
         << "Status\n";
    for (int i = 0; i < 75; i++) cout << "-";
    cout << "\n";

    for (int i = 0; i < idx; i++)
    {
        string status = (arr[i].stok <= arr[i].minStok) ? "(!)" : "OK";
        if (arr[i].stok <= arr[i].minStok) lowCount++;

        totalNilai += arr[i].stok * arr[i].harga;

        cout << left
             << setw(5)  << arr[i].id
             << setw(22) << arr[i].nama
             << setw(15) << arr[i].kategori
             << setw(8)  << arr[i].stok
             << setw(12) << arr[i].harga
             << setw(8)  << arr[i].minStok
             << status   << "\n";
    }

    for (int i = 0; i < 75; i++) cout << "-";
    cout << "\n";
    cout << "Total jenis barang : " << idx        << "\n";
    cout << "Barang menipis     : " << lowCount   << "\n";
    cout << "Total nilai stok   : Rp" << totalNilai << "\n";

    jeda();
}

// Tampilkan history transaksi dari queue
void reportHistoryTransaksi(Queue &q)
{
    header(" RIWAYAT TRANSAKSI ");
    q.displayHistory();
    jeda();
}

// Tampilkan history undo dari stack
void reportUndoHistory(Stack &s)
{
    header(" HISTORY UNDO ");
    s.displayHistory();
    jeda();
}

// ======================== SORT REPORTS ========================

// Insertion Sort → urut by stok: low → high
void reportSortByStok(BST &bst)
{
    cls();
    header(" LAPORAN STOK (Insertion Sort: Stok Terendah - Tertinggi) ");

    if (bst.size == 0)
    {
        cout << "Belum ada data barang.\n";
        jeda();
        return;
    }

    vector<Barang> data = bst.inorder();
    insertionSortByStok(data);

    cout << left
         << setw(5)  << "No"
         << setw(5)  << "ID"
         << setw(22) << "Nama Barang"
         << setw(15) << "Kategori"
         << setw(8)  << "Stok"
         << setw(8)  << "Min"
         << "Status\n";
    for (int i = 0; i < 70; i++) cout << "-";
    cout << "\n";

    int no = 1;
    for (auto &b : data)
    {
        string status = b.isLowStock() ? "(!) MENIPIS" : "OK";
        cout << left
             << setw(5)  << no++
             << setw(5)  << b.id
             << setw(22) << b.nama
             << setw(15) << b.kategori
             << setw(8)  << b.stok
             << setw(8)  << b.minStok
             << status   << "\n";
    }

    for (int i = 0; i < 70; i++) cout << "-";
    cout << "\n[Insertion Sort] Diurutkan berdasarkan stok: rendah - tinggi\n";
    cout << "Total: " << data.size() << " barang\n";

    jeda();
}

// Bubble Sort → urut by harga: high → low
void reportSortByHarga(BST &bst)
{
    cls();
    header(" LAPORAN NILAI STOK (Bubble Sort: Harga Tertinggi - Terendah) ");

    if (bst.size == 0)
    {
        cout << "Belum ada data barang.\n";
        jeda();
        return;
    }

    vector<Barang> data = bst.inorder();
    bubbleSortByHarga(data);

    double totalNilai = 0;

    cout << left
         << setw(5)  << "No"
         << setw(5)  << "ID"
         << setw(22) << "Nama Barang"
         << setw(8)  << "Stok"
         << setw(14) << "Harga/unit"
         << "Nilai Total\n";
    for (int i = 0; i < 70; i++) cout << "-";
    cout << "\n";

    int no = 1;
    for (auto &b : data)
    {
        double nilai = b.stok * b.harga;
        totalNilai  += nilai;

        cout << left
             << setw(5)  << no++
             << setw(5)  << b.id
             << setw(22) << b.nama
             << setw(8)  << b.stok
             << setw(14) << b.harga
             << "Rp" << nilai << "\n";
    }

    for (int i = 0; i < 70; i++) cout << "-";
    cout << "\n[Bubble Sort] Diurutkan berdasarkan harga: tertinggi - terendah\n";
    cout << "Total nilai seluruh stok: Rp" << totalNilai << "\n";

    jeda();
}

// Selection Sort → urut by kategori: A → Z
void reportSortByKategori(BST &bst)
{
    cls();
    header(" LAPORAN GROUPING KATEGORI (Selection Sort: A - Z) ");

    if (bst.size == 0)
    {
        cout << "Belum ada data barang.\n";
        jeda();
        return;
    }

    vector<Barang> data = bst.inorder();
    selectionSortByKategori(data);

    string kategoriSaat = "";
    int    no           = 1;

    for (auto &b : data)
    {
        // Cetak header kategori saat berganti
        if (b.kategori != kategoriSaat)
        {
            if (!kategoriSaat.empty()) cout << "\n";
            cout << "  [ " << b.kategori << " ]\n";
            cout << "  " << left
                 << setw(4)  << "No"
                 << setw(5)  << "ID"
                 << setw(22) << "Nama Barang"
                 << setw(8)  << "Stok"
                 << setw(12) << "Harga"
                 << "Status\n";
            cout << "  ";
            for (int i = 0; i < 58; i++) cout << "-";
            cout << "\n";
            kategoriSaat = b.kategori;
            no = 1;
        }

        string status = b.isLowStock() ? "(!)" : "OK";
        cout << "  " << left
             << setw(4)  << no++
             << setw(5)  << b.id
             << setw(22) << b.nama
             << setw(8)  << b.stok
             << setw(12) << b.harga
             << status   << "\n";
    }

    cout << "\n";
    for (int i = 0; i < 62; i++) cout << "-";
    cout << "\n[Selection Sort] Diurutkan berdasarkan kategori: A - Z\n";
    cout << "Total: " << data.size() << " barang\n";

    jeda();
}