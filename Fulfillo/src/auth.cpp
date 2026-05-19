#include "../include/auth.h"
#include "../include/bst.h"
#include "../include/ui.h"
#include "../include/user.h"
#include <iostream>
#include <limits>
using namespace std;

// Global variables — didefinisikan di main.cpp
extern UserManager um;
extern BST         bst;
extern User       *aktif;

// ======================== UTILITAS ========================

string roleStr(Role r)
{
    return r == ADMIN ? "admin" : "staff";
}

// FIX: inputInt DIHAPUS dari sini — sudah didefinisikan di ui.cpp
// FIX: garis() DIHAPUS — tidak dipakai di mana pun

bool semuaAngka(const string &s)
{
    if (s.empty()) return false;
    for (char c : s)
        if (!isdigit(c)) return false;
    return true;
}

bool semuaAlphanumeric(const string &s)
{
    if (s.empty()) return false;
    for (char c : s)
        if (!isalnum(c)) return false;
    return true;
}

// ======================== AUTH ========================

void login()
{
    cls();
    header(" LOGIN ");

    string uname, pass;

    cout << "Username : ";
    cin >> uname;

    cout << "Password : ";
    cin >> pass;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (uname.empty() || pass.empty())
    {
        cout << "\n[!] Username dan password tidak boleh kosong.\n";
        jeda();
        return;
    }

    User *u = um.cari(uname, pass);

    if (!u)
    {
        cout << "\n[!] Username atau password salah.\n";
        jeda();
        return;
    }

    aktif = u;

    cout << "\n>>> Login berhasil! " << aktif->username
         << " [" << roleStr(aktif->role) << "] <<<\n";

    jeda();
    cls();

    if (aktif->role == ADMIN)
        menuAdmin();
    else
        menuStaff();

    aktif = nullptr;
}