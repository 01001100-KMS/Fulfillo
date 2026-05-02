#ifndef BST_H
#define BST_H

#include "Barang.h"
#include <string>
#include <vector>
using namespace std;

//  Fulfillo — Binary Search Tree (BST)
//  Under Responsibility of Heiza
//  BST ini dipake untuk pencarian barang dengan cepat.
//  Tree diurutkan berdasarkan NAMA barang (alphabetical) bukan numerik ya anak anak.
//  Untuk search by ID, pakai fungsi searchById().

struct BSTNode {
    Barang  data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Barang b) : data(b), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    // Helper functions (private, dipanggil internal)
    BSTNode* insertHelper(BSTNode* node, Barang barang);
    BSTNode* deleteHelper(BSTNode* node, string nama);
    BSTNode* findMin(BSTNode* node);
    void     inorderHelper(BSTNode* node, vector<Barang>& result);
    void     clearHelper(BSTNode* node);
    BSTNode* searchByNameHelper(BSTNode* node, string nama);
    void     searchByKeywordHelper(BSTNode* node, string keyword, vector<Barang>& result);

public:
    BST();
    ~BST();

    // CRUD pada tree
    void    insert(Barang barang);
    void    remove(string nama);
    void    update(string nama, Barang barangBaru);

    // Pencarian
    Barang* searchByName(string nama);        // Exact match
    Barang* searchById(int id);               // Search by ID (traversal)
    vector<Barang> searchByKeyword(string keyword); // Partial match

    // Traversal — kembaliin semua barang urut alfabetical
    vector<Barang> inorder();

    // Utility
    bool isEmpty();
    void clear();
};

#endif