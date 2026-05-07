#include "../include/report.h"
#include "../include/auth.h"
#include "../include/bst.h"
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