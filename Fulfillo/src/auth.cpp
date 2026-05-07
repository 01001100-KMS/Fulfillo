#include "../include/auth.h"
#include "../include/bst.h"
#include "../include/ui.h"
#include "../include/user.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// Global variables — didefinisikan di main.cpp
extern UserManager um;
extern BST bst;
extern User *aktif;

// ======================== UTILITAS ========================

// Ubah nilai role menjadi teks untuk tampilan
string roleStr(Role r) { return r == ADMIN ? "admin" : "staff"; }

// Baca input bilangan bulat dengan validasi
void inputInt(const string &prompt, int &hasil)
{
    while (true)
    {
        cout << prompt;
        if (!(cin >> hasil))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[!] Input harus berupa bilangan bulat. Coba lagi.\n";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
    }
}

// Cetak garis pemisah menu
void garis()
{
    for (int i = 0; i < 60; i++)
        cout << "=";
    cout << "\n";
}

// Cetak judul menu dengan header
void header(const string &judul)
{
    garis();
    cout << setw(30 + judul.size() / 2) << judul << "\n";
    garis();
}

// Berhenti sementara sampai user menekan Enter
void jeda()
{
    cout << "\nEnter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Periksa apakah semua karakter string adalah angka
bool semuaAngka(const string &s)
{
    if (s.empty())
        return false;
    for (char c : s)
        if (!isdigit(c))
            return false;
    return true;
}

// Periksa apakah string hanya berisi huruf dan angka
bool semuaAlphanumeric(const string &s)
{
    if (s.empty())
        return false;
    for (char c : s)
        if (!isalnum(c))
            return false;
    return true;
}

// ======================== AUTH ========================

// Proses login user, verifikasi, dan arahkan ke menu yang sesuai
void login()
{
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

    if (aktif->role == ADMIN)
        menuAdmin();
    else
        menuStaff();

    aktif = nullptr;
}