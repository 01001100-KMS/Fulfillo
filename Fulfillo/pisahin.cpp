#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
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

struct Barang
{
    int id;
    string nama, kategori;
    int stok;
    int harga;
    int minStok;
};

struct Transaksi
{
    int idBarang;
    string namaBarang, jenis; // "masuk" atau "keluar"
    int jumlah;
    string oleh;
};

// ======================== BST NODE ========================

struct BSTNode
{
    Barang data;
    BSTNode *left, *right;
    BSTNode(Barang b) : data(b), left(nullptr), right(nullptr) {}
};

// ======================== BST ========================

struct BST
{
    BSTNode *root;
    int size;
    BST() : root(nullptr), size(0) {}

    // Tambahkan barang baru ke BST berdasarkan ID sebagai kunci
    void insert(Barang b)
    {
        BSTNode *node = new BSTNode(b);
        if (!root)
        {
            root = node;
            size++;
            return;
        }
        BSTNode *cur = root, *par = nullptr;
        while (cur)
        {
            par = cur;
            if (b.id < cur->data.id)
                cur = cur->left;
            else
                cur = cur->right;
        }
        if (b.id < par->data.id)
            par->left = node;
        else
            par->right = node;
        size++;
    }

    // Cari node BST berdasarkan ID
    BSTNode *cari(int id)
    {
        BSTNode *cur = root;
        while (cur)
        {
            if (id == cur->data.id)
                return cur;
            else if (id < cur->data.id)
                cur = cur->left;
            else
                cur = cur->right;
        }
        return nullptr;
    }

    // Hapus node dengan ID tertentu dari BST dan jaga struktur tetap valid
    BSTNode *hapusNode(BSTNode *node, int id)
    {
        if (!node)
            return nullptr;
        if (id < node->data.id)
            node->left = hapusNode(node->left, id);
        else if (id > node->data.id)
            node->right = hapusNode(node->right, id);
        else
        {
            if (!node->left)
            {
                BSTNode *t = node->right;
                delete node;
                size--;
                return t;
            }
            if (!node->right)
            {
                BSTNode *t = node->left;
                delete node;
                size--;
                return t;
            }
            // Cari successor (paling kiri di subtree kanan)
            BSTNode *suc = node->right;
            while (suc->left)
                suc = suc->left;
            node->data = suc->data;
            node->right = hapusNode(node->right, suc->data.id);
        }
        return node;
    }

    // Hapus barang dengan ID tertentu dari BST
    void hapus(int id) { root = hapusNode(root, id); }

    // Isi array dengan data barang dalam urutan naik berdasarkan ID
    void inorder(BSTNode *node, Barang arr[], int &idx)
    {
        if (!node)
            return;
        inorder(node->left, arr, idx);
        arr[idx++] = node->data;
        inorder(node->right, arr, idx);
    }

    // Kembalikan ID terbesar yang ada di BST
    int idTerakhir()
    {
        if (!root)
            return 0;
        BSTNode *cur = root;
        while (cur->right)
            cur = cur->right;
        return cur->data.id;
    }
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

// ======================== GLOBAL DATA ========================

const int MAX_TRANSAKSI = 200;
Transaksi transaksis[MAX_TRANSAKSI];
int jmlTransaksi = 0;

UserManager um;
BST bst;
User *aktif = nullptr;

// ======================== DUMMY DATA ========================

// Isi BST dengan data barang contoh untuk pengujian awal
void loadDummyBarang(BST &bst)
{
    //         id   nama                  kategori      stok   harga     minStok
    bst.insert({1, "Aki Forklift", "Elektrikal", 3, 450000, 2});
    bst.insert({2, "Bubble Wrap Roll", "Packaging", 480, 18000, 50});
    bst.insert({3, "Cat Lantai Abu", "Perawatan", 12, 95000, 5});
    bst.insert({4, "Drum Plastik 200L", "Wadah", 20, 185000, 5});
    bst.insert({5, "Forklift Pallet", "Alat Berat", 2, 8500000, 1});
    bst.insert({6, "Gloves Karet", "APD", 150, 12000, 30});
    bst.insert({7, "Hand Truck Besi", "Alat Angkut", 8, 320000, 3});
    bst.insert({8, "Isolasi Coklat", "Packaging", 4, 7500, 20});
    bst.insert({9, "Jaring Pengaman", "Keselamatan", 15, 75000, 5});
    bst.insert({10, "Kardus Box L", "Packaging", 200, 5500, 30});
    bst.insert({11, "Label Barcode", "Administrasi", 500, 150, 100});
    bst.insert({12, "Masker N95", "APD", 80, 15000, 50});
    bst.insert({13, "Nylon Tali 10mm", "Pengikat", 60, 22000, 10});
    bst.insert({14, "Oli Mesin Forklift", "Perawatan", 6, 120000, 3});
    bst.insert({15, "Pallet Kayu", "Wadah", 35, 85000, 10});
    bst.insert({16, "Rak Besi 5 Tingkat", "Furnitur", 7, 950000, 2});
    bst.insert({17, "Selotip Bening", "Packaging", 2, 8000, 15});
    bst.insert({18, "Timbangan Digital", "Alat Ukur", 4, 275000, 2});
    bst.insert({19, "Uniform Gudang", "APD", 25, 135000, 10});
    bst.insert({20, "Velcro Pengikat", "Pengikat", 90, 9500, 20});
}

// Isi user manager dengan akun default untuk login awal
void loadDummyUser(UserManager &um)
{
    um.tambahUser("Heiza", "019", ADMIN);
    um.tambahUser("Arya", "022", STAFF);
}

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

// ======================== FITUR USER (ADMIN) ========================

// Tampilkan daftar semua user yang tersimpan
void daftarUser()
{
    header(" DAFTAR USER ");
    cout << left << setw(5) << "No"
         << setw(20) << "Username"
         << "Role\n";
    for (int i = 0; i < 35; i++)
        cout << "-";
    cout << "\n";
    for (int i = 0; i < um.jml; i++)
    {
        cout << left << setw(5) << (i + 1)
             << setw(20) << um.data[i].username
             << roleStr(um.data[i].role) << "\n";
    }
    for (int i = 0; i < 35; i++)
        cout << "-";
    cout << "\nTotal: " << um.jml << " user\n";
    jeda();
}

// Registrasi user baru dengan validasi input
void registrasi()
{
    header(" REGISTRASI USER BARU ");

    if (um.jml >= UserManager::MAX)
    {
        cout << "[!] User sudah mencapai batas maksimum.\n";
        jeda();
        return;
    }

    string username, password, roleInput;

    cout << "Username : ";
    cin >> username;
    cout << "Password : ";
    cin >> password;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (username.empty())
    {
        cout << "[!] Username tidak boleh kosong.\n";
        jeda();
        return;
    }
    if (!semuaAlphanumeric(username))
    {
        cout << "[!] Username hanya boleh berisi huruf dan angka.\n";
        jeda();
        return;
    }
    if (password.empty())
    {
        cout << "[!] Password tidak boleh kosong.\n";
        jeda();
        return;
    }
    if (!semuaAngka(password))
    {
        cout << "[!] Password hanya boleh berisi angka.\n";
        jeda();
        return;
    }

    int pilRole;
    cout << "Role (1=Admin, 2=Staff): ";
    inputInt("", pilRole);
    if (pilRole != 1 && pilRole != 2)
    {
        cout << "[!] Role tidak valid.\n";
        jeda();
        return;
    }

    Role r = (pilRole == 1) ? ADMIN : STAFF;
    if (!um.tambahUser(username, password, r))
    {
        cout << "[!] Username '" << username << "' sudah digunakan.\n";
        jeda();
        return;
    }

    cout << "\nRegistrasi berhasil. User '" << username
         << "' [" << roleStr(r) << "] ditambahkan.\n";
    jeda();
}

// Hapus user lain berdasarkan username, kecuali user yang sedang login
void hapusUser()
{
    header(" HAPUS USER ");

    if (um.jml <= 1)
    {
        cout << "[!] Tidak ada user yang bisa dihapus.\n";
        jeda();
        return;
    }

    cout << left << setw(5) << "No"
         << setw(20) << "Username"
         << "Role\n";
    for (int i = 0; i < 35; i++)
        cout << "-";
    cout << "\n";

    int tampil = 0;
    for (int i = 0; i < um.jml; i++)
    {
        if (um.data[i].username != aktif->username)
        {
            tampil++;
            cout << left << setw(5) << tampil
                 << setw(20) << um.data[i].username
                 << roleStr(um.data[i].role) << "\n";
        }
    }

    if (tampil == 0)
    {
        cout << "[!] Tidak ada user lain yang bisa dihapus.\n";
        jeda();
        return;
    }

    for (int i = 0; i < 35; i++)
        cout << "-";
    cout << "\n";

    string target;
    cout << "Masukkan username yang ingin dihapus: ";
    cin >> target;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool ditemukan = false;
    for (int i = 0; i < um.jml; i++)
        if (um.data[i].username == target)
        {
            ditemukan = true;
            break;
        }

    if (!ditemukan)
    {
        cout << "[!] Username '" << target << "' tidak ditemukan.\n";
        jeda();
        return;
    }

    if (!um.hapusUser(target, aktif->username))
    {
        cout << "[!] Tidak dapat menghapus akun yang sedang digunakan.\n";
        jeda();
        return;
    }

    cout << "\nUser '" << target << "' berhasil dihapus.\n";
    jeda();
}

// ======================== FITUR STOK ========================

// Tampilkan semua data barang dalam stok beserta status minimum
void lihatStok()
{
    header(" STOK BARANG ");
    if (bst.size == 0)
    {
        cout << "Belum ada data barang.\n";
        jeda();
        return;
    }

    Barang arr[200];
    int idx = 0;
    bst.inorder(bst.root, arr, idx);

    cout << left
         << setw(5) << "ID"
         << setw(22) << "Nama Barang"
         << setw(15) << "Kategori"
         << setw(7) << "Stok"
         << setw(12) << "Harga"
         << "Min\n";
    for (int i = 0; i < 68; i++)
        cout << "-";
    cout << "\n";

    for (int i = 0; i < idx; i++)
    {
        string stokInfo = to_string(arr[i].stok);
        if (arr[i].stok <= arr[i].minStok)
            stokInfo += " (!)";
        cout << left
             << setw(5) << arr[i].id
             << setw(22) << arr[i].nama
             << setw(15) << arr[i].kategori
             << setw(7) << stokInfo
             << setw(12) << arr[i].harga
             << arr[i].minStok << "\n";
    }
    for (int i = 0; i < 68; i++)
        cout << "-";
    cout << "\nTotal: " << idx << " jenis barang"
         << "  |  (!): stok mendekati/di bawah minimum\n";
    jeda();
}

// Tambah stok barang baru atau update stok barang yang sudah ada
void barangMasuk()
{
    header(" BARANG MASUK ");

    int id;
    inputInt("ID Barang (0 = tambah baru): ", id);

    if (id == 0)
    {
        // Tambah barang baru
        if (bst.size >= 200)
        {
            cout << "[!] Data barang sudah mencapai batas maksimum.\n";
            jeda();
            return;
        }

        Barang b;
        b.id = bst.idTerakhir() + 1;
        cout << "ID otomatis : " << b.id << "\n";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nama Barang : ";
        getline(cin, b.nama);
        cout << "Kategori    : ";
        getline(cin, b.kategori);

        if (b.nama.empty() || b.kategori.empty())
        {
            cout << "[!] Nama dan kategori tidak boleh kosong.\n";
            jeda();
            return;
        }

        inputInt("Harga       : ", b.harga);
        inputInt("Min Stok    : ", b.minStok);
        inputInt("Jumlah Masuk: ", b.stok);

        if (b.stok <= 0 || b.harga <= 0 || b.minStok <= 0)
        {
            cout << "[!] Nilai harus lebih dari 0.\n";
            jeda();
            return;
        }

        bst.insert(b);
        if (jmlTransaksi < MAX_TRANSAKSI)
            transaksis[jmlTransaksi++] = {b.id, b.nama, "masuk", b.stok, aktif->username};

        cout << "\nBarang baru '" << b.nama << "' berhasil ditambahkan.\n";
    }
    else
    {
        BSTNode *node = bst.cari(id);
        if (!node)
        {
            cout << "[!] Barang dengan ID " << id << " tidak ditemukan.\n";
            jeda();
            return;
        }

        cout << "Nama Barang  : " << node->data.nama << "\n";
        cout << "Stok Saat Ini: " << node->data.stok << "\n";

        int jumlah;
        inputInt("Jumlah Masuk : ", jumlah);
        if (jumlah <= 0)
        {
            cout << "[!] Jumlah harus lebih dari 0.\n";
            jeda();
            return;
        }

        node->data.stok += jumlah;
        if (jmlTransaksi < MAX_TRANSAKSI)
            transaksis[jmlTransaksi++] = {id, node->data.nama, "masuk", jumlah, aktif->username};

        cout << "\nBarang masuk berhasil. Stok sekarang: " << node->data.stok << "\n";
    }
    jeda();
}

// Kurangi stok barang saat barang keluar
void barangKeluar()
{
    header(" BARANG KELUAR ");

    if (bst.size == 0)
    {
        cout << "[!] Belum ada data barang.\n";
        jeda();
        return;
    }

    int id, jumlah;
    inputInt("ID Barang    : ", id);

    BSTNode *node = bst.cari(id);
    if (!node)
    {
        cout << "[!] Barang dengan ID " << id << " tidak ditemukan.\n";
        jeda();
        return;
    }

    cout << "Nama Barang   : " << node->data.nama << "\n";
    cout << "Stok Saat Ini : " << node->data.stok << "\n";
    inputInt("Jumlah Keluar : ", jumlah);

    if (jumlah <= 0)
    {
        cout << "[!] Jumlah harus lebih dari 0.\n";
        jeda();
        return;
    }
    if (jumlah > node->data.stok)
    {
        cout << "[!] Stok tidak mencukupi. Stok tersedia: " << node->data.stok << "\n";
        jeda();
        return;
    }

    node->data.stok -= jumlah;
    if (jmlTransaksi < MAX_TRANSAKSI)
        transaksis[jmlTransaksi++] = {id, node->data.nama, "keluar", jumlah, aktif->username};

    cout << "\nBarang keluar berhasil. Stok sekarang: " << node->data.stok << "\n";
    if (node->data.stok <= node->data.minStok)
        cout << "[!] Peringatan: stok mendekati/di bawah minimum (" << node->data.minStok << ")!\n";
    jeda();
}

// Tampilkan riwayat semua transaksi masuk dan keluar
void riwayatTransaksi()
{
    header(" RIWAYAT TRANSAKSI ");
    if (jmlTransaksi == 0)
    {
        cout << "Belum ada transaksi.\n";
        jeda();
        return;
    }
    cout << left
         << setw(5) << "No"
         << setw(6) << "ID"
         << setw(22) << "Nama Barang"
         << setw(9) << "Jenis"
         << setw(9) << "Jumlah"
         << "Oleh\n";
    for (int i = 0; i < 62; i++)
        cout << "-";
    cout << "\n";
    for (int i = 0; i < jmlTransaksi; i++)
    {
        cout << left
             << setw(5) << (i + 1)
             << setw(6) << transaksis[i].idBarang
             << setw(22) << transaksis[i].namaBarang
             << setw(9) << transaksis[i].jenis
             << setw(9) << transaksis[i].jumlah
             << transaksis[i].oleh << "\n";
    }
    for (int i = 0; i < 62; i++)
        cout << "-";
    cout << "\nTotal transaksi: " << jmlTransaksi << "\n";
    jeda();
}

// Menu pilihan untuk kelola stok dan transaksi
void menuKelola()
{
    int pil;
    do
    {
        header(" KELOLA STOK ");
        cout << "1. Barang Masuk\n";
        cout << "2. Barang Keluar\n";
        cout << "3. Lihat Stok Barang\n";
        cout << "4. Riwayat Transaksi\n";
        cout << "0. Kembali\n";
        inputInt("Pilihan: ", pil);

        switch (pil)
        {
        case 1:
            barangMasuk();
            break;
        case 2:
            barangKeluar();
            break;
        case 3:
            lihatStok();
            break;
        case 4:
            riwayatTransaksi();
            break;
        case 0:
            break;
        default:
            cout << "[!] Pilihan tidak valid.\n";
            jeda();
        }
    } while (pil != 0);
}

// ======================== MENU ========================

// Tampilkan menu khusus admin untuk mengelola user dan stok
void menuAdmin()
{
    int pil;
    do
    {
        header(" MENU ADMIN ");
        cout << "Login sebagai: " << aktif->username << " [admin]\n\n";
        cout << "1. Registrasi User Baru\n";
        cout << "2. Lihat Daftar User\n";
        cout << "3. Hapus User\n";
        cout << "4. Kelola Stok\n";
        cout << "0. Logout\n";
        inputInt("Pilihan: ", pil);

        switch (pil)
        {
        case 1:
            registrasi();
            break;
        case 2:
            daftarUser();
            break;
        case 3:
            hapusUser();
            break;
        case 4:
            menuKelola();
            break;
        case 0:
            break;
        default:
            cout << "[!] Pilihan tidak valid.\n";
            jeda();
        }
    } while (pil != 0);

    cout << "\nBerhasil logout.\n\n";
}

// Tampilkan menu staff yang hanya bisa mengelola stok
void menuStaff()
{
    int pil;
    do
    {
        header(" MENU STAFF ");
        cout << "Login sebagai: " << aktif->username << " [staff]\n\n";
        cout << "1. Kelola Stok\n";
        cout << "0. Logout\n";
        inputInt("Pilihan: ", pil);

        switch (pil)
        {
        case 1:
            menuKelola();
            break;
        case 0:
            break;
        default:
            cout << "[!] Pilihan tidak valid.\n";
            jeda();
        }
    } while (pil != 0);

    cout << "\nBerhasil logout.\n\n";
}

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

// Titik masuk program utama: muat data, tampilkan menu login, dan tutup aplikasi
int main()
{
    loadDummyBarang(bst);
    loadDummyUser(um);

    int pil;
    do
    {
        header(" SISTEM MANAJEMEN GUDANG ");
        cout << "1. Login\n";
        cout << "0. Keluar\n";
        inputInt("Pilihan: ", pil);

        switch (pil)
        {
        case 1:
            login();
            break;
        case 0:
            break;
        default:
            cout << "[!] Pilihan tidak valid.\n";
            jeda();
        }
    } while (pil != 0);

    cout << "Program selesai.\n";
    return 0;
}