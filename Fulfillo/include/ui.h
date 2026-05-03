#ifndef UI_H
#define UI_H

#include <string>
using namespace std;

// ======================== HELPER ========================

void header(string judul);
void jeda();
void inputInt(string pesan, int &var);

// ======================== MENU UTAMA ========================

void tampilkanMenu();
void tampilkanDashboard(int totalBarang, int lowStock);

// ======================== INVENTORY VIEW ========================

void tampilkanListBarang();
void tampilkanLowStock();
void tampilkanLaporanStok();
void tampilkanHistory();

// ======================== USER ========================

void daftarUser();
void registrasi();
void hapusUser();

// ======================== MENU ROLE ========================

void menuAdmin();
void menuStaff();

// ======================= Something  ========================
void inputDouble(string pesan, double &var);
#endif