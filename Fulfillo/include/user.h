#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

// ======================== ENUM ========================

enum Role
{
    ADMIN,
    STAFF
};

// ======================== STRUCT ========================

struct User
{
    string username, password;
    Role role;
};

// ======================== USER MANAGER ========================

struct UserManager
{
    static const int MAX = 50;
    User data[MAX];
    int jml;

    // Inisialisasi manager user dengan jumlah awal 0
    UserManager() : jml(0) {}

    // Tambah user baru jika username belum digunakan
    bool tambahUser(const string &username, const string &password, Role role)
    {
        if (jml >= MAX)
            return false;
        for (int i = 0; i < jml; i++)
            if (data[i].username == username)
                return false;
        data[jml++] = {username, password, role};
        return true;
    }

    // Hapus user kecuali user yang sedang login
    bool hapusUser(const string &username, const string &loginUser)
    {
        if (username == loginUser)
            return false;
        for (int i = 0; i < jml; i++)
        {
            if (data[i].username == username)
            {
                for (int j = i; j < jml - 1; j++)
                    data[j] = data[j + 1];
                jml--;
                return true;
            }
        }
        return false;
    }

    // Cari user berdasarkan username dan password
    User *cari(const string &username, const string &password)
    {
        for (int i = 0; i < jml; i++)
            if (data[i].username == username && data[i].password == password)
                return &data[i];
        return nullptr;
    }
};

#endif