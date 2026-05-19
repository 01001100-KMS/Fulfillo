// ======================== ui.h ========================
#ifndef UI_H
#define UI_H
#include <string>

// ======================== HELPER ========================
void inputInt(std::string pesan, int &var);
void inputDouble(std::string pesan, double &var);
void header(std::string judul);
void jeda();
void cls();

// ======================== MENU UTAMA ========================
void tampilkanDashboard(int totalBarang, int lowStock);

// ======================== INVENTORY ========================
void tampilkanListBarang();
void tampilkanLowStock();
void tampilkanLaporanStok();
void tampilkanHistory();

// ======================== USER ========================
void daftarUser();
void registrasi();
void hapusUser();

// ======================== UNDO ========================
void undoAksi(); // FIX: integrasi Stack undo untuk Admin

// ======================== ROLE ========================
void menuAdmin();
void menuStaff();

#endif