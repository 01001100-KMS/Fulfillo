#ifndef SORT_H
#define SORT_H

#include "barang.h"
#include <vector>
using namespace std;

// ======================== INSERTION SORT ========================
// Urut by stok: low → high (relevan untuk deteksi barang menipis)

inline void insertionSortByStok(vector<Barang> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++)
    {
        Barang key = arr[i];
        int    j   = i - 1;
        while (j >= 0 && arr[j].stok > key.stok)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// ======================== BUBBLE SORT ========================
// Urut by harga: high → low (untuk laporan nilai stok tertinggi)

inline void bubbleSortByHarga(vector<Barang> &arr)
{
    int  n       = arr.size();
    bool swapped = false;

    for (int i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].harga < arr[j + 1].harga)
            {
                Barang temp  = arr[j];
                arr[j]       = arr[j + 1];
                arr[j + 1]   = temp;
                swapped      = true;
            }
        }
        // Early exit jika sudah terurut
        if (!swapped) break;
    }
}

// ======================== SELECTION SORT ========================
// Urut by kategori: A → Z (untuk grouping barang per kategori)

inline void selectionSortByKategori(vector<Barang> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j].kategori < arr[minIdx].kategori)
                minIdx = j;
        }
        if (minIdx != i)
        {
            Barang temp  = arr[i];
            arr[i]       = arr[minIdx];
            arr[minIdx]  = temp;
        }
    }
}

#endif