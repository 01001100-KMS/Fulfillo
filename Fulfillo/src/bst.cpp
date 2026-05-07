#include "../include/BST.h"

#include <algorithm>
#include <iostream>
#include <cctype>

using namespace std;

// ======================== NODE ========================

BSTNode::BSTNode(const Barang& b)
    : data(b), left(nullptr), right(nullptr) {}


// ======================== CONSTRUCTOR ========================

BST::BST() : root(nullptr) {}

BST::~BST() {
    clear();
}


// ======================== INSERT ========================

BSTNode* BST::insertHelper(BSTNode* node,
                           const Barang& barang)
{
    if (node == nullptr) {
        return new BSTNode(barang);
    }

    string namaBaru = barang.nama;
    string namaNode = node->data.nama;

    transform(namaBaru.begin(), namaBaru.end(),
              namaBaru.begin(), ::tolower);

    transform(namaNode.begin(), namaNode.end(),
              namaNode.begin(), ::tolower);

    if (namaBaru < namaNode) {
        node->left =
            insertHelper(node->left, barang);
    }
    else if (namaBaru > namaNode) {
        node->right =
            insertHelper(node->right, barang);
    }
    else {

        // Update stok kalau nama sama
        node->data.stok += barang.stok;

        cout << "[BST] Barang sudah ada.\n";
    }

    return node;
}

void BST::insert(const Barang& barang)
{
    root = insertHelper(root, barang);
}


// ======================== FIND MIN ========================

BSTNode* BST::findMin(BSTNode* node)
{
    while (node && node->left != nullptr) {
        node = node->left;
    }

    return node;
}


// ======================== DELETE ========================

BSTNode* BST::deleteHelper(BSTNode* node,
                           const string& nama)
{
    if (node == nullptr)
        return nullptr;

    string target = nama;
    string current = node->data.nama;

    transform(target.begin(), target.end(),
              target.begin(), ::tolower);

    transform(current.begin(), current.end(),
              current.begin(), ::tolower);

    if (target < current) {

        node->left =
            deleteHelper(node->left, nama);
    }
    else if (target > current) {

        node->right =
            deleteHelper(node->right, nama);
    }
    else {

        // Tidak punya anak
        if (node->left == nullptr &&
            node->right == nullptr)
        {
            delete node;
            return nullptr;
        }

        // Satu anak kanan
        else if (node->left == nullptr)
        {
            BSTNode* temp = node->right;

            delete node;

            return temp;
        }

        // Satu anak kiri
        else if (node->right == nullptr)
        {
            BSTNode* temp = node->left;

            delete node;

            return temp;
        }

        // Dua anak
        BSTNode* successor =
            findMin(node->right);

        node->data = successor->data;

        node->right =
            deleteHelper(node->right,
                         successor->data.nama);
    }

    return node;
}

void BST::remove(const string& nama)
{
    if (searchByName(nama) == nullptr)
    {
        cout << "[BST] Barang tidak ditemukan.\n";
        return;
    }

    root = deleteHelper(root, nama);

    cout << "[BST] Barang berhasil dihapus.\n";
}


// ======================== SEARCH ========================

BSTNode* BST::searchByNameHelper(
    BSTNode* node,
    const string& nama)
{
    if (node == nullptr)
        return nullptr;

    string target = nama;
    string current = node->data.nama;

    transform(target.begin(), target.end(),
              target.begin(), ::tolower);

    transform(current.begin(), current.end(),
              current.begin(), ::tolower);

    if (target == current)
        return node;

    if (target < current)
        return searchByNameHelper(
            node->left, nama);

    return searchByNameHelper(
        node->right, nama);
}

Barang* BST::searchByName(
    const string& nama)
{
    BSTNode* result =
        searchByNameHelper(root, nama);

    if (result == nullptr)
        return nullptr;

    return &(result->data);
}