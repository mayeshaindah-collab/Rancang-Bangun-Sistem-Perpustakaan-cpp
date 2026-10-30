#include <iostream>
#include <string>
using namespace std;

struct Buku {
    int id;
    string judul;
    string penulis;
    int stok;
};

struct Peminjaman {
    int idBuku;
    string namaPeminjam;
    int lamaPinjam;
    bool sedangMeminjam;
};

int main() {
    Buku buku[5] = {
        {101, "Laskar Pelangi", "Andrea Hirata", 3},
        {102, "Bumi", "Tere Liye", 2},
        {103, "Negeri 5 Menara", "Ahmad Fuadi", 4},
        {104, "Dilan 1990", "Pidi Baiq", 2},
        {105, "Bumi Manusia", "Pramoedya Ananta Toer", 3}
    };

    Peminjaman pinjaman[5];

    for (int i = 0; i < 5; i++) {
        pinjaman[i].sedangMeminjam = false;
    }

    int pilihan;
    char ulang = 'Y';

    do {
        // MENU UTAMA
        cout << "\n====================================\n";
        cout << "       SISTEM PERPUSTAKAAN\n";
        cout << "====================================\n";
        cout << "1. Lihat Daftar Buku\n";
        cout << "2. Cari Buku Berdasarkan ID\n";
        cout << "3. Pinjam Buku\n";
        cout << "4. Kembalikan Buku\n";
        cout << "5. Lihat Data Peminjaman\n";
        cout << "6. Keluar\n";
        cout << "====================================\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        // 1. LIHAT DAFTAR BUKU
        if (pilihan == 1) {
            cout << "\n========== DAFTAR BUKU ==========\n";

            for (int i = 0; i < 5; i++) {
                cout << "\nID Buku : " << buku[i].id << endl;
                cout << "Judul   : " << buku[i].judul << endl;
                cout << "Penulis : " << buku[i].penulis << endl;
                cout << "Stok    : " << buku[i].stok << endl;

                if (buku[i].stok > 0) {
                    cout << "Status  : Tersedia\n";
                } else {
                    cout << "Status  : Habis\n";
                }
                cout << "---------------------------------\n";
            }
        }

        // 2. CARI BUKU BERDASARKAN ID
        else if (pilihan == 2) {
            int idCari;
            bool ditemukan = false;

            cout << "\nMasukkan ID buku: ";
            cin >> idCari;

            for (int i = 0; i < 5; i++) {
                if (buku[i].id == idCari) {
                    ditemukan = true;

                    cout << "\nBuku ditemukan!\n";
                    cout << "ID Buku : " << buku[i].id << endl;
                    cout << "Judul   : " << buku[i].judul << endl;
                    cout << "Penulis : " << buku[i].penulis << endl;
                    cout << "Stok    : " << buku[i].stok << endl;

                    if (buku[i].stok > 0) {
                        cout << "Status  : Bisa dipinjam\n";
                    } else {
                        cout << "Status  : Tidak bisa dipinjam\n";
                    }
                    break;
                }
            }

            if (!ditemukan) {
                cout << "ID buku tidak ditemukan!\n";
            }
        }

        // 3. PINJAM BUKU
        else if (pilihan == 3) {
            string nama;
            int idPinjam, lama;

            cout << "\n========== PEMINJAMAN BUKU ==========\n";
            cout << "Masukkan nama peminjam: ";
            cin.ignore();
            getline(cin, nama);

            cout << "Masukkan ID buku yang ingin dipinjam: ";
            cin >> idPinjam;

            int index = -1;

            for (int i = 0; i < 5; i++) {
                if (buku[i].id == idPinjam) {
                    index = i;
                    break;
                }
            }

            if (index == -1) {
                cout << "ID buku tidak ditemukan!\n";
            } else if (buku[index].stok <= 0) {
                cout << "Maaf, buku sedang tidak tersedia.\n";
            } else {
                cout << "Judul buku: " << buku[index].judul << endl;
                cout << "Lama peminjaman (hari): ";
                cin >> lama;

                if (nama != "" && lama >= 1) {
                    if (lama <= 7) {
                        int tempat = -1;

                        for (int i = 0; i < 5; i++) {
                            if (!pinjaman[i].sedangMeminjam) {
                                tempat = i;
                                break;
                            }
                        }

                        if (tempat != -1) {
                            pinjaman[tempat].idBuku = idPinjam;
                            pinjaman[tempat].namaPeminjam = nama;
                            pinjaman[tempat].lamaPinjam = lama;
                            pinjaman[tempat].sedangMeminjam = true;

                            buku[index].stok--;

                            cout << "\nPeminjaman berhasil!\n";
                            cout << "Nama : " << nama << endl;
                            cout << "Buku : " << buku[index].judul << endl;
                            cout << "Lama : " << lama << " hari\n";
                        } else {
                            cout << "Data peminjaman sudah penuh!\n";
                        }
                    } else {
                        cout << "Lama peminjaman maksimal 7 hari!\n";
                    }
                } else {
                    cout << "Nama dan lama peminjaman harus diisi dengan benar!\n";
                }
            }
        }

        // 4. KEMBALIKAN BUKU
        else if (pilihan == 4) {
            string nama;
            int idKembali, hari;

            cout << "\n========== PENGEMBALIAN BUKU ==========\n";
            cout << "Masukkan nama peminjam: ";
            cin.ignore();
            getline(cin, nama);

            cout << "Masukkan ID buku: ";
            cin >> idKembali;

            int data = -1;

            for (int i = 0; i < 5; i++) {
                if (pinjaman[i].sedangMeminjam &&
                    pinjaman[i].idBuku == idKembali &&
                    pinjaman[i].namaPeminjam == nama) {
                    data = i;
                    break;
                }
            }

            if (data != -1 && pinjaman[data].sedangMeminjam) {
                cout << "Masukkan jumlah hari buku dipinjam: ";
                cin >> hari;

                int indexBuku = -1;

                for (int i = 0; i < 5; i++) {
                    if (buku[i].id == idKembali) {
                        indexBuku = i;
                        break;
                    }
                }

                if (hari >= 0 && hari <= 7) {
                    cout << "Buku dikembalikan tepat waktu.\n";
                    cout << "Denda: Rp0\n";
                } else if (hari > 7) {
                    int terlambat = hari - 7;
                    int denda = terlambat * 1000;

                    cout << "Buku terlambat " << terlambat
                         << " hari.\n";
                    cout << "Denda: Rp" << denda << endl;
                } else {
                    cout << "Jumlah hari tidak valid!\n";
                }

                if (hari >= 0 && indexBuku != -1) {
                    buku[indexBuku].stok++;
                    pinjaman[data].sedangMeminjam = false;
                    cout << "Buku berhasil dikembalikan!\n";
                }
            } else {
                cout << "Data peminjaman tidak ditemukan!\n";
            }
        }

        // 5. LIHAT DATA PEMINJAMAN
        else if (pilihan == 5) {
            cout << "\n========== DATA PEMINJAMAN ==========\n";
            bool adaData = false;

            for (int i = 0; i < 5; i++) {
                if (pinjaman[i].sedangMeminjam) {
                    adaData = true;

                    cout << "Nama Peminjam : "
                         << pinjaman[i].namaPeminjam << endl;
                    cout << "ID Buku       : "
                         << pinjaman[i].idBuku << endl;
                    cout << "Lama Pinjam   : "
                         << pinjaman[i].lamaPinjam << " hari\n";
                    cout << "---------------------------------\n";
                }
            }

            if (!adaData) {
                cout << "Belum ada buku yang sedang dipinjam.\n";
            }
        }

        // 6. KELUAR
        else if (pilihan == 6) {
            cout << "\nTerima kasih telah menggunakan\n";
            cout << "Sistem Perpustakaan!\n";
        }

        // PILIHAN SALAH
        else {
            cout << "\nPilihan tidak valid!\n";
            cout << "Silakan pilih menu 1-6.\n";
        }

        // PENGULANGAN Y/y DAN T/t
        if (pilihan != 6) {
            do {
                cout << "\nIngin kembali ke menu utama? (Y/T): ";
                cin >> ulang;

                if (ulang != 'Y' && ulang != 'y' &&
                    ulang != 'T' && ulang != 't') {
                    cout << "Input salah! Masukkan Y/y atau T/t.\n";
                }
            } while (ulang != 'Y' && ulang != 'y' &&
                     ulang != 'T' && ulang != 't');

            if (ulang == 'T' || ulang == 't') {
                cout << "\nTerima kasih telah menggunakan\n";
                cout << "Sistem Perpustakaan!\n";
            }
        }

    } while (pilihan != 6 && (ulang == 'Y' || ulang == 'y'));

    return 0;
}
