#ifndef BST_H
#define BST_H

#include "barang.h"
#include <string>
#include <vector>

struct BSTNode {
    Barang data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const Barang& b);
};

class BST {
private:
    BSTNode* root;

    BSTNode* insertHelper(BSTNode* node, const Barang& barang);
    BSTNode* deleteHelper(BSTNode* node, const std::string& nama);
    BSTNode* findMin(BSTNode* node);

    void inorderHelper(BSTNode* node,
                        std::vector<Barang>& result);

    void clearHelper(BSTNode* node);

    BSTNode* searchByNameHelper(BSTNode* node,
                                const std::string& nama);

    void searchByKeywordHelper(BSTNode* node,
                               const std::string& keyword,
                               std::vector<Barang>& result);

public:
    BST();
    ~BST();

    void insert(const Barang& barang);
    void remove(const std::string& nama);

    void update(const std::string& nama,
                const Barang& barangBaru);

    Barang* searchByName(const std::string& nama);
    Barang* searchById(int id);

    std::vector<Barang>
    searchByKeyword(const std::string& keyword);

    std::vector<Barang> inorder();

    bool isEmpty();

    void clear();
};

#endif