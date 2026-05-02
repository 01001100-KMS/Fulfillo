#include <iostream>
#include <iomanip>
#include "include/Barang.h"
#include "include/BST.h"
#include "include/Stack.h"
using namespace std;

// ============================================================
//  Fulfillo — Test File untuk Orang A
//  Jalankan file ini untuk verifikasi BST & Stack berjalan.
//
//  Compile:
//    g++ testA.cpp src/BST.cpp src/Stack.cpp -o testA
//  Run:
//    ./testA
// ============================================================

void printSeparator(string judul) {
    cout << "\n══════════════════════════════════════\n";
    cout << "  " << judul << "\n";
    cout << "══════════════════════════════════════\n";
}

void printBarang(Barang b) {
    cout << "  [" << setw(3) << b.id << "] "
         << left  << setw(20) << b.nama
         << " | Stok: " << setw(4) << b.stok
         << " | Harga: Rp" << b.harga
         << (b.isLowStock() ? " ⚠ LOW STOCK" : "")
         << "\n";
}

// ── TEST BST ─────────────────────────────────────────────────
void testBST() {
    printSeparator("TEST BST");

    BST bst;

    // Dummy data barang warehouse
    Barang data[] = {
        Barang(1, "Kardus Box L",   "Packaging",  150, 5000,  20),
        Barang(2, "Pallet Kayu",    "Equipment",   30, 75000,  5),
        Barang(3, "Bubble Wrap",    "Packaging",  500, 15000, 50),
        Barang(4, "Selotip Besar",  "Packaging",   10, 8000,  15),
        Barang(5, "Forklift Mini",  "Equipment",    2, 500000, 1),
        Barang(6, "Kardus Box S",   "Packaging",   80, 3000,  20),
    };

    // Insert semua barang
    cout << "\n>> Insert barang...\n";
    for (auto& b : data) {
        bst.insert(b);
    }

    // Tampilkan inorder (harusnya urut alfabetis)
    cout << "\n>> Inorder traversal (urut alfabetis):\n";
    vector<Barang> semua = bst.inorder();
    for (auto& b : semua) {
        printBarang(b);
    }

    // Test search by name (exact)
    cout << "\n>> Search by name 'Pallet Kayu':\n";
    Barang* found = bst.searchByName("Pallet Kayu");
    if (found) printBarang(*found);
    else       cout << "  Tidak ditemukan.\n";

    // Test search by name (tidak ada)
    cout << "\n>> Search by name 'Meja Kerja' (tidak ada):\n";
    found = bst.searchByName("Meja Kerja");
    if (found) printBarang(*found);
    else       cout << "  Tidak ditemukan.\n";

    // Test search by keyword
    cout << "\n>> Search keyword 'kardus':\n";
    vector<Barang> hasil = bst.searchByKeyword("kardus");
    if (hasil.empty()) cout << "  Tidak ditemukan.\n";
    else for (auto& b : hasil) printBarang(b);

    // Test search by ID
    cout << "\n>> Search by ID = 3:\n";
    Barang* byId = bst.searchById(3);
    if (byId) printBarang(*byId);
    else      cout << "  Tidak ditemukan.\n";

    // Test delete
    cout << "\n>> Hapus 'Bubble Wrap'...\n";
    bst.remove("Bubble Wrap");
    cout << "\n>> Inorder setelah hapus:\n";
    semua = bst.inorder();
    for (auto& b : semua) printBarang(b);

    // Test update
    cout << "\n>> Update 'Selotip Besar' stok jadi 100...\n";
    Barang updated(4, "Selotip Besar", "Packaging", 100, 8000, 15);
    bst.update("Selotip Besar", updated);
    found = bst.searchByName("Selotip Besar");
    if (found) printBarang(*found);

    // Low stock check
    cout << "\n>> Cek barang low stock:\n";
    semua = bst.inorder();
    bool adaLow = false;
    for (auto& b : semua) {
        if (b.isLowStock()) {
            printBarang(b);
            adaLow = true;
        }
    }
    if (!adaLow) cout << "  Tidak ada barang low stock.\n";
}

// ── TEST STACK ───────────────────────────────────────────────
void testStack() {
    printSeparator("TEST STACK (UNDO SYSTEM)");

    Stack stack(5); // Max 5 aksi untuk testing

    Barang b1(1, "Kardus Box L",  "Packaging", 150, 5000,  20);
    Barang b2(2, "Pallet Kayu",   "Equipment",  30, 75000,  5);
    Barang b3(3, "Bubble Wrap",   "Packaging", 500, 15000, 50);
    Barang kosong;

    // Simulasi beberapa aksi
    cout << "\n>> Push 3 aksi ke stack...\n";
    stack.push(buatAksi(TAMBAH_BARANG, kosong, b1, "Tambah Kardus Box L"));
    stack.push(buatAksi(TAMBAH_BARANG, kosong, b2, "Tambah Pallet Kayu"));
    stack.push(buatAksi(HAPUS_BARANG,  b3, kosong, "Hapus Bubble Wrap"));

    // Tampilkan history
    stack.displayHistory();

    // Peek — lihat aksi teratas
    cout << ">> Peek (aksi teratas): " << stack.peek().keterangan << "\n";

    // Undo 1x
    cout << "\n>> Undo 1x...\n";
    Aksi undone = stack.pop();
    cout << "   Undo aksi: " << undone.keterangan << "\n";
    cout << "   Tipe: " << aksiTypeToString(undone.tipe) << "\n";

    // Tampilkan history setelah undo
    stack.displayHistory();

    // Test stack kosong
    cout << ">> Undo terus sampai kosong...\n";
    while (!stack.isEmpty()) {
        Aksi a = stack.pop();
        cout << "   Undo: " << a.keterangan << "\n";
    }
    stack.pop(); // Harusnya muncul pesan error

    cout << "\n>> isEmpty: " << (stack.isEmpty() ? "true" : "false") << "\n";
}

// ── MAIN ─────────────────────────────────────────────────────
int main() {
    cout << "\n";
    cout << "  ███████╗██╗   ██╗██╗     ███████╗██╗██╗     ██╗      ██████╗ \n";
    cout << "  ██╔════╝██║   ██║██║     ██╔════╝██║██║     ██║     ██╔═══██╗\n";
    cout << "  █████╗  ██║   ██║██║     █████╗  ██║██║     ██║     ██║   ██║\n";
    cout << "  ██╔══╝  ██║   ██║██║     ██╔══╝  ██║██║     ██║     ██║   ██║\n";
    cout << "  ██║     ╚██████╔╝███████╗██║     ██║███████╗███████╗╚██████╔╝\n";
    cout << "  ╚═╝      ╚═════╝ ╚══════╝╚═╝     ╚═╝╚══════╝╚══════╝ ╚═════╝ \n";
    cout << "                    Test Suite — Orang A (Minggu 1)\n\n";

    testBST();
    testStack();

    cout << "\n══════════════════════════════════════\n";
    cout << "  Semua test selesai!\n";
    cout << "══════════════════════════════════════\n\n";

    return 0;
}