#include "../include/BST.h"
#include <algorithm>
#include <iostream>
using namespace std;

//  Fulfillo — BST Implementation
//  Tanggung jawab: Orang A
//  (command was made by ai cuz my lazyness)

// ── Constructor & Destructor ─────────────────────────────────

BST::BST() : root(nullptr) {}

BST::~BST() {
    clear();
}

// ── Private Helpers ──────────────────────────────────────────

BSTNode* BST::insertHelper(BSTNode* node, Barang barang) {
    if (node == nullptr) {
        return new BSTNode(barang);
    }

    // Bandingkan nama (case-insensitive)
    string namaBaru  = barang.nama;
    string namaNode  = node->data.nama;
    transform(namaBaru.begin(), namaBaru.end(), namaBaru.begin(), ::tolower);
    transform(namaNode.begin(), namaNode.end(), namaNode.begin(), ::tolower);

    if (namaBaru < namaNode) {
        node->left  = insertHelper(node->left, barang);
    } else if (namaBaru > namaNode) {
        node->right = insertHelper(node->right, barang);
    } else {
        // Nama sudah ada — update stok saja
        node->data.stok += barang.stok;
        cout << "[BST] Barang '" << barang.nama << "' sudah ada. Stok diupdate.\n";
    }

    return node;
}

BSTNode* BST::findMin(BSTNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

BSTNode* BST::deleteHelper(BSTNode* node, string nama) {
    if (node == nullptr) return nullptr;

    string namaTarget = nama;
    string namaNode   = node->data.nama;
    transform(namaTarget.begin(), namaTarget.end(), namaTarget.begin(), ::tolower);
    transform(namaNode.begin(),   namaNode.end(),   namaNode.begin(),   ::tolower);

    if (namaTarget < namaNode) {
        node->left  = deleteHelper(node->left, nama);
    } else if (namaTarget > namaNode) {
        node->right = deleteHelper(node->right, nama);
    } else {
        // Node ditemukan — 3 kasus
        if (node->left == nullptr && node->right == nullptr) {
            // Kasus 1: Leaf node
            delete node;
            return nullptr;
        } else if (node->left == nullptr) {
            // Kasus 2: Punya 1 anak (kanan)
            BSTNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            // Kasus 2: Punya 1 anak (kiri)
            BSTNode* temp = node->left;
            delete node;
            return temp;
        } else {
            // Kasus 3: Punya 2 anak
            // Cari inorder successor (nilai terkecil di subtree kanan)
            BSTNode* successor = findMin(node->right);
            node->data = successor->data;
            node->right = deleteHelper(node->right, successor->data.nama);
        }
    }

    return node;
}

BSTNode* BST::searchByNameHelper(BSTNode* node, string nama) {
    if (node == nullptr) return nullptr;

    string namaTarget = nama;
    string namaNode   = node->data.nama;
    transform(namaTarget.begin(), namaTarget.end(), namaTarget.begin(), ::tolower);
    transform(namaNode.begin(),   namaNode.end(),   namaNode.begin(),   ::tolower);

    if (namaTarget == namaNode) return node;
    if (namaTarget < namaNode)  return searchByNameHelper(node->left, nama);
    return searchByNameHelper(node->right, nama);
}

void BST::searchByKeywordHelper(BSTNode* node, string keyword, vector<Barang>& result) {
    if (node == nullptr) return;

    // Traversal semua node, cek apakah nama mengandung keyword
    string namaNode = node->data.nama;
    string kw       = keyword;
    transform(namaNode.begin(), namaNode.end(), namaNode.begin(), ::tolower);
    transform(kw.begin(), kw.end(), kw.begin(), ::tolower);

    if (namaNode.find(kw) != string::npos) {
        result.push_back(node->data);
    }

    searchByKeywordHelper(node->left,  keyword, result);
    searchByKeywordHelper(node->right, keyword, result);
}

void BST::inorderHelper(BSTNode* node, vector<Barang>& result) {
    if (node == nullptr) return;
    inorderHelper(node->left, result);
    result.push_back(node->data);
    inorderHelper(node->right, result);
}

void BST::clearHelper(BSTNode* node) {
    if (node == nullptr) return;
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
}

// ── Public Methods ───────────────────────────────────────────

void BST::insert(Barang barang) {
    root = insertHelper(root, barang);
}

void BST::remove(string nama) {
    if (searchByName(nama) == nullptr) {
        cout << "[BST] Barang '" << nama << "' tidak ditemukan.\n";
        return;
    }
    root = deleteHelper(root, nama);
    cout << "[BST] Barang '" << nama << "' berhasil dihapus.\n";
}

void BST::update(string nama, Barang barangBaru) {
    // Update = hapus lama, insert baru
    BSTNode* found = searchByNameHelper(root, nama);
    if (found == nullptr) {
        cout << "[BST] Barang '" << nama << "' tidak ditemukan.\n";
        return;
    }
    root = deleteHelper(root, nama);
    root = insertHelper(root, barangBaru);
}

Barang* BST::searchByName(string nama) {
    BSTNode* result = searchByNameHelper(root, nama);
    if (result == nullptr) return nullptr;
    return &(result->data);
}

// Helper untuk searchById
static BSTNode* searchByIdHelper(BSTNode* node, int id) {
    if (node == nullptr) return nullptr;
    if (node->data.id == id) return node;
    BSTNode* left = searchByIdHelper(node->left, id);
    if (left != nullptr) return left;
    return searchByIdHelper(node->right, id);
}

Barang* BST::searchById(int id) {
    BSTNode* result = searchByIdHelper(root, id);
    if (result == nullptr) return nullptr;
    return &(result->data);
}

vector<Barang> BST::searchByKeyword(string keyword) {
    vector<Barang> result;
    searchByKeywordHelper(root, keyword, result);
    return result;
}

vector<Barang> BST::inorder() {
    vector<Barang> result;
    inorderHelper(root, result);
    return result;
}

bool BST::isEmpty() {
    return root == nullptr;
}

void BST::clear() {
    clearHelper(root);
    root = nullptr;
}