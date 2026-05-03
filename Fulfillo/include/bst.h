#ifndef BST_H
#define BST_H

#include "barang.h"
#include <string>
#include <vector>
using namespace std;

// ======================== NODE ========================

struct BSTNode {
    Barang data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Barang b) : data(b), left(nullptr), right(nullptr) {}
};

// ======================== CLASS BST ========================

class BST {
private:
    BSTNode* root;

    // Helper (internal)
    BSTNode* insertHelper(BSTNode* node, Barang barang);
    BSTNode* deleteHelper(BSTNode* node, string nama);
    BSTNode* findMin(BSTNode* node);
    void inorderHelper(BSTNode* node, vector<Barang>& result);
    void clearHelper(BSTNode* node);
    BSTNode* searchByNameHelper(BSTNode* node, string nama);
    void searchByKeywordHelper(BSTNode* node, string keyword, vector<Barang>& result);

public:
    BST();
    ~BST();

    // CRUD
    void insert(Barang barang);
    void remove(string nama);
    void update(string nama, Barang barangBaru);

    // Search
    Barang* searchByName(string nama);
    Barang* searchById(int id);
    vector<Barang> searchByKeyword(string keyword);

    // Traversal
    vector<Barang> inorder();

    // Utility
    bool isEmpty();
    void clear();
};

#endif