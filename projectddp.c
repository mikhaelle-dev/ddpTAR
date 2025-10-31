#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // for Sleep and system color on Windows

// =====================
// Sistem Kasir - Toko Meong
// - Login: admin / 123
// - 30 produk bawaan
// - Tampilan: loading, color, menu, struk
// =====================

#define MAX_PRODUK 30
#define MAX_CART 100

typedef struct {
    char nama[50];
    float harga;
} Produk;

typedef struct {
    Produk item;
    int qty;
} CartItem;

// Data produk (30 item)
Produk daftarProduk[MAX_PRODUK] = {
    {"Indomie Goreng", 3500}, {"Aqua 600ml", 4000}, {"Teh Botol Sosro", 5000},
    {"Kopi Kapal Api 1 sachet", 3000}, {"Roti Tawar", 15000}, {"Susu UHT 1L", 21000},
    {"Gula 1kg", 16000}, {"Beras 5kg", 65000}, {"Minyak Goreng 1L", 20000},
    {"Telur 1kg", 28000}, {"Tepung Terigu 1kg", 14000}, {"Sabun Mandi", 8000},
    {"Sampo 200ml", 12000}, {"Pasta Gigi", 10000}, {"Deterjen 1kg", 18000},
    {"Kecap Manis", 13000}, {"Saus Tomat", 12000}, {"Mentega 200gr", 18000},
    {"Tisu", 9000}, {"Air Mineral 1.5L", 8000}, {"Keju Slice", 23000},
    {"Sosis Kanzler", 12000}, {"Mie Instan (5x)", 18000}, {"Kerupuk", 7000},
    {"Bumbu Masak", 11000}, {"Masker 5pcs", 10000}, {"Baterai AA 2pcs", 15000},
    {"Sabun Cuci Piring", 12000}, {"Pewangi Pakaian", 17000}, {"Tisu Basah", 12000}
};

// Keranjang belanja
CartItem keranjang[MAX_CART];
int jumlahCart = 0;
float totalBelanja = 0.0f;
char kasir[50] = "";
char tokoNama[] = "Toko Meong";

// Deklarasi fungsi
void loadingAwal();
void tampilkanMainMenu();
int loginUser();
void menuKasir();
void tampilkanProduk();
void tambahKeKeranjang();
void lihatKeranjang();
void hitungTotal();
void pilihMetodePembayaran();
void prosesPembayaran(char metode[]);
void cetakStruk(char metode[]);
void resetTransaksi();

// Util
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Implementasi
void loadingAwal() {
    system("cls");
    system("color 0a");
    printf("\n\n\n\t\t   SELAMAT DATANG DI %s\n", tokoNama);
    printf("\t\t        Loading: \n\n");
    for (int i = 0; i <= 50; i++) {
        int pct = (i * 2);
        printf("\r\t\t%3d%% [", pct);
        for (int j = 0; j < i; j++) printf("=");
        for (int k = i; k < 50; k++) printf(" ");
        printf("]");
        fflush(stdout);
        Sleep(40); // 40 ms per step => ~2 seconds
    }
    printf("\n\n\t\t   Loading selesai! Tekan Enter untuk lanjut...");
    getchar();
}

void tampilkanMainMenu() {
    system("cls");
    system("color 0b");
    printf("========================================\n");
    printf("        %s - Sistem Kasir\n", tokoNama);
    printf("========================================\n");
    printf("1. Login\n");
    printf("2. Keluar\n");
    printf("========================================\n");
    printf("Pisssssslih: ");
}

int loginUser() {
    char user[50];
    char pass[50];

    system("cls");
    system("color 0e");
    printf("==== LOGIN ===\n");
    printf("Username: ");
    if (!fgets(user, sizeof(user), stdin)) return 0;
    user[strcspn(user, "\n")] = 0;
    printf("Password: ");
    if (!fgets(pass, sizeof(pass), stdin)) return 0;
    pass[strcspn(pass, "\n")] = 0;

    Sleep(400);
    if (strcmp(user, "admin") == 0 && strcmp(pass, "123") == 0) {
        strcpy(kasir, user);
        printf("\nLogin berhasil! Selamat datang, %s.\n", kasir);
        printf("Tekan Enter untuk melanjutkan...");
        getchar();
        return 1;
    } else {
        printf("\nLogin gagal! Username/Password salah. Tekan Enter untuk coba lagi...");
        getchar();
        return 0;
    }
}

void menuKasir() {
    int pilihan;
    while (1) {
        system("cls");
        system("color 0b");
        printf("========================================\n");
        printf("        %s - Sistem Kasir (Kasir: %s)\n", tokoNama, kasir);
        printf("========================================\n");
        printf("1. Tampilkan Produk\n");
        printf("2. Tambah Produk ke Keranjang\n");
        printf("3. Lihat Keranjang\n");
        printf("4. Hitung Total & Pembayaran\n");
        printf("5. Reset Transaksi\n");
        printf("6. Logout\n");
        printf("7. Keluar Program\n");
        printf("========================================\n");
        printf("Pilih menu: ");

        if (scanf("%d", &pilihan) != 1) {
            clearInputBuffer();
            printf("Input tidak valid. Tekan Enter untuk kembali...");
            getchar();
            continue;
        }
        clearInputBuffer();

        switch (pilihan) {
            case 1:
                tampilkanProduk();
                break;
            case 2:
                tambahKeKeranjang();
                break;
            case 3:
                lihatKeranjang();
                break;
            case 4:
                hitungTotal();
                break;
            case 5:
                resetTransaksi();
                break;
            case 6:
                printf("Logout berhasil. Tekan Enter untuk kembali ke menu utama...");
                getchar();
                return; // kembali ke main
            case 7:
                printf("Terima kasih! Program keluar.\n");
                exit(0);
            default:
                printf("Pilihan tidak valid. Tekan Enter untuk kembali...");
                getchar();
                break;
        }
    }
}

void tampilkanProduk() {
    system("cls");
    system("color 0a");
    printf("==== DAFTAR PRODUK (%s) ===\n", tokoNama);
    for (int i = 0; i < MAX_PRODUK; i++) {
        printf("%2d. %-25s Rp %8.2f\n", i + 1, daftarProduk[i].nama, daftarProduk[i].harga);
    }
    printf("\nTekan Enter untuk kembali...");
    getchar();
}

void tambahKeKeranjang() {
    int kode;
    int qty;
    char lagi;
    do {
        tampilkanProduk();
        printf("Masukkan nomor produk yang ingin dibeli (1-%d): ", MAX_PRODUK);
        if (scanf("%d", &kode) != 1) {
            clearInputBuffer();
            printf("Input tidak valid. Tekan Enter untuk kembali ke menu...\n");
            getchar();
            return;
        }
        if (kode < 1 || kode > MAX_PRODUK) {
            clearInputBuffer();
            printf("Kode produk tidak valid. Tekan Enter untuk coba lagi...\n");
            getchar();
            return;
        }
        printf("Masukkan jumlah: ");
        if (scanf("%d", &qty) != 1 || qty <= 0) {
            clearInputBuffer();
            printf("Jumlah tidak valid. Tekan Enter untuk kembali...\n");
            getchar();
            return;
        }
        clearInputBuffer();

        // tambahkan ke keranjang
        if (jumlahCart < MAX_CART) {
            keranjang[jumlahCart].item = daftarProduk[kode - 1];
            keranjang[jumlahCart].qty = qty;
            jumlahCart++;
            totalBelanja += daftarProduk[kode - 1].harga * qty;
            printf("%s x%d ditambahkan. Total sementara: Rp %.2f\n", daftarProduk[kode - 1].nama, qty, totalBelanja);
        } else {
            printf("Keranjang penuh!\n");
        }

        printf("Tambah produk lain? (y/n): ");
        if (scanf(" %c", &lagi) != 1) {
            clearInputBuffer();
            lagi = 'n';
        }
        clearInputBuffer();
    } while (lagi == 'y' || lagi == 'Y');
}

void lihatKeranjang() {
    system("cls");
    system("color 0b");
    if (jumlahCart == 0) {
        printf("Keranjang kosong. Tekan Enter untuk kembali...\n");
        getchar();
        return;
    }
    printf("==== KERANJANG BELANJA ===\n");
    for (int i = 0; i < jumlahCart; i++) {
        printf("%2d. %-25s x%3d = Rp %8.2f\n", i + 1, keranjang[i].item.nama, keranjang[i].qty, keranjang[i].item.harga * keranjang[i].qty);
    }
    printf("----------------------------------\n");
    printf("TOTAL: Rp %.2f\n", totalBelanja);
    printf("Tekan Enter untuk kembali...\n");
    getchar();
}

void hitungTotal() {
    if (jumlahCart == 0) {
        printf("Belum ada produk di keranjang. Tekan Enter untuk kembali...\n");
        getchar();
        return;
    }
    system("cls");
    system("color 0e");
    printf("==== RINCIAN PEMBELIAN ===\n");
    for (int i = 0; i < jumlahCart; i++) {
        printf("%2d. %-25s x%3d = Rp %8.2f\n", i + 1, keranjang[i].item.nama, keranjang[i].qty, keranjang[i].item.harga * keranjang[i].qty);
    }
    printf("----------------------------------\n");
    printf("TOTAL BELANJA: Rp %.2f\n", totalBelanja);
    printf("\nTekan Enter untuk memilih metode pembayaran...");
    getchar();
    pilihMetodePembayaran();
}

void pilihMetodePembayaran() {
    int pilihan;
    char metode[20] = "";
    while (1) {
        system("cls");
        printf("Pilih Metode Pembayaran:\n");
        printf("1. Tunai\n");
        printf("2. QRIS (Non-Tunai)\n");
        printf("3. Batal\n");
        printf("Pilih: ");
        if (scanf("%d", &pilihan) != 1) {
            clearInputBuffer();
            printf("Input tidak valid. Tekan Enter untuk kembali...\n");
            getchar();
            return;
        }
        clearInputBuffer();
        if (pilihan == 1) {
            strcpy(metode, "Tunai");
            prosesPembayaran(metode);
            return;
        } else if (pilihan == 2) {
            strcpy(metode, "QRIS");
            prosesPembayaran(metode);
            return;
        } else if (pilihan == 3) {
            return;
        } else {
            printf("Pilihan tidak valid. Tekan Enter untuk ulang...\n");
            getchar();
        }
    }
}

void prosesPembayaran(char metode[]) {
    float bayar = 0.0f;
    while (1) {
        system("cls");
        printf("Metode: %s\n", metode);
        printf("Total yang harus dibayar: Rp %.2f\n", totalBelanja);
        printf("Masukkan jumlah uang yang dibayar: Rp ");
        if (scanf("%f", &bayar) != 1) {
            clearInputBuffer();
            printf("Input tidak valid. Tekan Enter untuk ulang...\n");
            getchar();
            continue;
        }
        clearInputBuffer();
        if (bayar < totalBelanja) {
            printf("Uang kurang Rp %.2f. Tekan Enter untuk ulang...\n", totalBelanja - bayar);
            getchar();
            continue;
        }
        break;
    }
    // pembayaran sukses
    printf("Pembayaran berhasil! Kembalian: Rp %.2f\n", bayar - totalBelanja);
    Sleep(800);
    cetakStruk(metode);
    // selesai transaksi -> reset
    resetTransaksi();
    printf("Tekan Enter untuk kembali ke menu...\n");
    getchar();
}

void cetakStruk(char metode[]) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    system("cls");
    system("color 0a");
    printf("========================================\n");
    printf("                %s\n", tokoNama);
    printf("           STRUK PEMBELIAN\n");
    printf("========================================\n");
    printf("Kasir    : %s\n", kasir);
    printf("Tanggal  : %02d-%02d-%04d %02d:%02d:%02d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("----------------------------------------\n");
    for (int i = 0; i < jumlahCart; i++) {
        printf("%2d. %-20s x%3d  Rp %8.2f\n", i + 1, keranjang[i].item.nama, keranjang[i].qty, keranjang[i].item.harga * keranjang[i].qty);
    }
    printf("----------------------------------------\n");
    printf("TOTAL    : Rp %.2f\n", totalBelanja);
    printf("Metode   : %s\n", metode);
    printf("========================================\n");
}

void resetTransaksi() {
    jumlahCart = 0;
    totalBelanja = 0.0f;
}

int main() {
    int pilih;
    loadingAwal();
    while (1) {
        tampilkanMainMenu();
        if (scanf("%d", &pilih) != 1) {
            clearInputBuffer();
            printf("Input tidak valid. Tekan Enter untuk ulang...\n");
            getchar();
            continue;
        }
        clearInputBuffer();
        if (pilih == 1) {
            if (loginUser()) {
                menuKasir();
            }
        } else if (pilih == 2) {
            printf("Terima kasih telah menggunakan %s.\n", tokoNama);
            break;
        } else {
            printf("Pilihan tidak valid. Tekan Enter untuk ulang...\n");
            getchar();
        }
    }
    return 0;
}
