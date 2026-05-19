#ifndef REPORT_H
#define REPORT_H

#include "bst.h"
#include "queue.h"
#include "stack.h"

// ======================== REPORT ========================

void reportLowStock(BST &bst);
void reportSemuaStok(BST &bst);
void reportHistoryTransaksi(Queue &q);
void reportUndoHistory(Stack &s);

// ======================== SORT REPORT ========================

void reportSortByStok(BST &bst);      // Insertion Sort → stok low → high
void reportSortByHarga(BST &bst);     // Bubble Sort    → harga high → low
void reportSortByKategori(BST &bst);  // Selection Sort → kategori A → Z

#endif