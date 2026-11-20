#include "menu.h"

// login admin
bool loginAdmin() {
    string username, password;
    int maksPercobaan = 3;
    int sisa = maksPercobaan;

    while (sisa > 0) {
        cout << "\n===== LOGIN ADMIN =====" << endl;
        cout << "Username   : ";
        cin >> username;
        cout << "Password   : ";
        cin >> password;

        // cek username & password
        if ((username == "ADMIN" && password == "ADMIN123") || 
            (username == "admin" && password == "admin123")) {
            cout << "Login Berhasil!" << endl;
            return true;
        }

        sisa--;
        cout << "Username atau Password salah!!" << endl;
        if (sisa > 0) {
            cout << "Sisa percobaan: " << sisa << endl;
        }
    }
    cout << "\nAnda gagal login " << maksPercobaan << " kali" << endl;
    cout << "Kembali ke menu utama" << endl;
    return false;
}

// menu utama (pilih role)
void menuUtama(MLL &L, Queue &Q) {
    int pilihan;

    do {
        cout << "\n==============================" << endl;
        cout << "      ARENAGO - PILIH ROLE    " << endl;
        cout << "==============================" << endl;
        cout << "1. Masuk sebagai Admin" << endl;
        cout << "2. Masuk sebagai User" << endl;
        cout << "0. Keluar" << endl;
        cout << "------------------------------" << endl;
        cout << "Pilih: ";
        cin >> pilihan;

        if (pilihan == 1) {
            if (loginAdmin()) {
                menuAdmin(L, Q);
            }
        } else if (pilihan == 2) {
            menuUser(L, Q);
        } else if (pilihan == 0) {
            cout << "Terima kasih!" << endl;
        } else {
            cout << "Pilihan salah." << endl;
        }
    } while (pilihan != 0);
}

// menu admin
void menuAdmin(MLL &L, Queue &Q) {
    int pilihan;

    do {
        cout << "\n=== MENU ADMIN ===" << endl;
        cout << "1. Tambah Lapangan" << endl;
        cout << "2. Hapus Lapangan" << endl;
        cout << "3. Lihat Daftar Lapangan" << endl;
        cout << "4. Lihat Waiting List" << endl;
        cout << "5. Proses Waiting List" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilih: ";
        cin >> pilihan;

        if (pilihan == 1) {
            lapanganBaru(L);
        } else if (pilihan == 2) {
            hapusLapanganMenu(L);
        } else if (pilihan == 3) {
            tampilkanLapangan(L);
        } else if (pilihan == 4) {
            tampilkanAntrean(Q);
        } else if (pilihan == 5) {
            prosesWaitingList(L, Q);
        } else if (pilihan == 0) {
            cout << "Keluar dari menu admin." << endl;
        } else {
            cout << "Pilihan salah." << endl;
        }
    } while (pilihan != 0);
}

// menu user
void menuUser(MLL &L, Queue &Q) {
    int pilihan;
    string kode;

    do {
        cout << "\n=== MENU USER ===" << endl;
        cout << "1. Lihat Daftar Lapangan" << endl;
        cout << "2. Booking Lapangan" << endl;
        cout << "3. Cek Booking Saya" << endl;
        cout << "4. Batal Booking" << endl;
        cout << "5. Batal Waiting List" << endl;
        cout << "6. Lihat Semua Booking di Lapangan" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilih: ";
        cin >> pilihan;

        if (pilihan == 1) {
            tampilkanLapangan(L);
        } else if (pilihan == 2) {
            pesanLapangan(L, Q);
        } else if (pilihan == 3) {
            cekBookingMenu(L);
        } else if (pilihan == 4) {
            batalBooking(L);
        } else if (pilihan == 5) {
            batalWaitingListMenu(Q);
        } else if (pilihan == 6) {
            cout << "Kode Lapangan: ";
            cin >> kode;
            tampilkanBooking(L, kode);
        } else if (pilihan == 0) {
            cout << "Keluar dari menu user." << endl;
        } else {
            cout << "Pilihan salah." << endl;
        }
    } while (pilihan != 0);
}