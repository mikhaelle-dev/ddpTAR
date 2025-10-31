#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#define MAX_PRODUK 5 
#define MAX_KERANJANG 50

// Variabel global
char lastMetode[20];
float lastBayar, lastKembalian;
int adaTransaksi = 0;

typedef struct {
    char nama[50];
    float harga;
} Produk;

Produk daftarProduk[MAX_PRODUK] = {
    {"Indomie Goreng", 3500},
    {"Aqua 600ml", 4000},
    {"Teh Botol Sosro", 5000},
    {"Roti Tawar", 15000},
    {"Minyak Goreng 1L", 20000}
};

typedef struct {
    Produk item;
    int qty;
} keranjangItem;

keranjangItem keranjang[MAX_KERANJANG];
int jumlahkeranjang = 0;
float totalBelanja = 0.0f;

// =================== FUNGSI UTAMA ===================

void loadingawal() {
    system("cls");
    system("color 0b");
    printf("\n\n\n\t\t\t\t\t\t\t\t ==========================================\n");
    printf("\t\t\t\t\t\t\t\t ||        LOADING TOKO MEONG...         ||\n");
    printf("\t\t\t\t\t\t\t\t ||                                      ||\n");
    for (int i = 0; i <= 50; i++) {
        printf("\r\t\t\t\t\t\t\t\t ||          LOADING : %d%%              ||", i * 2);
        fflush(stdout);
        Sleep(15);
    }
    printf("\n\t\t\t\t\t\t\t\t ||                                      ||");
    printf("\n\t\t\t\t\t\t\t\t ||              SELESAI                 ||");
    printf("\n\t\t\t\t\t\t\t\t ||  silahkan tekan enter untuk lanjut   ||");
    printf("\n\t\t\t\t\t\t\t\t ==========================================\n");
    while (getchar() != '\n');
}

void menu1() {
    system("cls");
    printf("\n\n\n ==========================================\n");
    printf(" ||                  MENU LOGIN          ||\n");
    printf(" ||                                      ||\n");
    printf(" || 1. LOGIN                             ||\n");
    printf(" || 2. KELUAR                            ||\n");
    printf(" ||                                      ||\n");
    printf(" ==========================================\n");
    printf(" PILIH :  ");
}

int loginmasuk() {
    char user[50], pass[50];

    system("cls");
    printf("\n\n ==========================================\n");
    printf(" ||              LOGIN AKUN             ||\n");
    printf(" ==========================================\n");

    printf(" USERNAME : ");
    fgets(user, sizeof(user), stdin);
    user[strcspn(user, "\n")] = 0; 

    printf(" PASSWORD : ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = 0; 

    if (strcmp(user, "admin") == 0 && strcmp(pass, "123") == 0) {
        printf("\n LOGIN BERHASIL! Tekan Enter untuk lanjut...");
        getchar();
        return 1; 
    } else {
        printf("\n LOGIN GAGAL!  SILAHKAN LOGIN KEMBALI...");
        getchar();
        return 0; 
    }
}

// =================== FITUR KASIR ===================

void tampilkanProduk() {
    system("cls");
    printf("=====================================\n");
    printf("        DAFTAR PRODUK TOKO MEONG     \n");
    printf("=====================================\n");
    for (int i = 0; i < MAX_PRODUK; i++) {
        printf("%d. %-20s Rp %.0f\n", i + 1, daftarProduk[i].nama, daftarProduk[i].harga);
    }
    printf("=====================================\n");
    printf("Tekan Enter untuk kembali...");
    getchar();
}

void tampilkanProduk2() {
    system("cls");
    printf("=====================================\n");
    printf("        DAFTAR PRODUK TOKO MEONG     \n");
    printf("=====================================\n");
    for (int i = 0; i < MAX_PRODUK; i++) {
        printf("%d. %-20s Rp %.0f\n", i + 1, daftarProduk[i].nama, daftarProduk[i].harga);
    }
    printf("=====================================\n");
}

void strukbayar(char metode[], float bayar, float kembalian);

void pembayaran() {
    int metode;
    float bayar, kembalian;
    char namametode[20];

    system("cls");
    printf("=====================================\n");
    printf("              PEMBAYARAN             \n");
    printf("=====================================\n");
    printf("Total belanja: Rp %.0f\n", totalBelanja);
    printf("-------------------------------------\n");
    printf(" list metode pembayaran \n");
    printf("1. QRIS\n");
    printf("2. CASH\n");
    printf("3. TRANSFER\n");
    printf("-------------------------------------\n");
    printf(" pilih metode pembayaran : ");
    scanf("%d", &metode);
    getchar();

    switch (metode) {
        case 1:
            strcpy(namametode, "QRIS");
            break;
        case 2:
            strcpy(namametode, "CASH");
            break;
        case 3:
            strcpy(namametode, "TRANSFER");
            break;
        default:
            printf("Metode pembayaran tidak valid!\n");
            Sleep(1000);
            return;
    }

    printf("Masukkan nominal pembayaran: Rp ");
    scanf("%f", &bayar);
    getchar();

    if (bayar < totalBelanja) {
        printf("Uang anda kurang!\n");
        Sleep(1000);
        return;
    }

    kembalian = bayar - totalBelanja;

    // Simpan data transaksi terakhir
    strcpy(lastMetode, namametode);
    lastBayar = bayar;
    lastKembalian = kembalian;
    adaTransaksi = 1;

    strukbayar(namametode, bayar, kembalian);
}

void tambahkeranjang() {
    int kode, qty;
    char lagi;

    do {
        system("cls");
        tampilkanProduk2();

        printf("Masukkan nomor produk yang ingin dibeli: ");
        scanf("%d", &kode);
        getchar();

        if (kode < 1 || kode > MAX_PRODUK) {
            printf("Nomor produk tidak valid!\n");
            Sleep(1000);
            continue;
        }

        printf("Masukkan jumlah: ");
        scanf("%d", &qty);
        getchar();

        keranjang[jumlahkeranjang].item = daftarProduk[kode - 1];
        keranjang[jumlahkeranjang].qty = qty;
        jumlahkeranjang++;
        totalBelanja += daftarProduk[kode - 1].harga * qty;

        printf("\n%s x%d ditambahkan ke keranjang.\n", daftarProduk[kode - 1].nama, qty);
        printf("Total sementara: Rp %.0f\n", totalBelanja);

        printf("\nApakah ingin menambah barang lagi? (y/n): ");
        scanf(" %c", &lagi);
        getchar();

    } while (lagi == 'y' || lagi == 'Y');
}

void lihatKeranjangbayar() {
    char lagi;
    system("cls");
    printf("=====================================\n");
    printf("             ISI KERANJANG ANDA      \n");
    printf("=====================================\n");

    if (jumlahkeranjang == 0) {
        printf("Keranjang masih kosong!\n");
    } else {
        for (int i = 0; i < jumlahkeranjang; i++) {
            printf("%d. %-20s x%d  Rp %.0f\n",
                   i + 1,
                   keranjang[i].item.nama,
                   keranjang[i].qty,
                   keranjang[i].item.harga * keranjang[i].qty);
        }
        printf("-------------------------------------\n");
        printf("TOTAL BELANJA: Rp %.0f\n", totalBelanja);
    }

    printf("=====================================\n");
    printf("\nApakah ingin membayar sekarang? (y/n): ");
    scanf(" %c", &lagi);
    getchar();

    if (lagi == 'y' || lagi == 'Y') {
        pembayaran();
    } else {
        return;
    }
}

void strukbayar(char metode[], float bayar, float kembalian) {
    system("cls");
    printf("=====================================\n");
    printf("                  STRUK              \n");
    printf("=====================================\n");
    for (int i = 0; i < jumlahkeranjang; i++) {
        printf("%-20s x%d Rp %.0f\n",
               keranjang[i].item.nama,
               keranjang[i].qty,
               keranjang[i].item.harga * keranjang[i].qty);
    }
    printf("-------------------------------------\n");
    printf("TOTAL BELANJA : Rp %.0f\n", totalBelanja);
    printf("DIBAYAR       : Rp %.0f\n", bayar);
    printf("KEMBALIAN     : Rp %.0f\n", kembalian);
    printf("PEMBAYARAN    : %s\n", metode);
    printf("=====================================\n");
    printf("     Terima kasih telah belanja!     \n");
    printf("=====================================\n");

    jumlahkeranjang = 0;
    totalBelanja = 0;

    printf("\nTekan Enter untuk kembali ke menu kasir...");
    getchar();
}

// =================== MENU UTAMA KASIR ===================

void menuKasir() {
    int pilih;

    while (1) {
        system("cls");
        printf("=====================================\n");
        printf("         MENU KASIR - TOKO MEONG     \n");
        printf("=====================================\n");
        printf("1. Lihat Produk\n");
        printf("2. Tambah Produk ke Keranjang\n");
        printf("3. Lihat Keranjang\n");
        printf("4. Pembayaran\n");
        printf("5. Struk\n");
        printf("6. Logout\n");
        printf("=====================================\n");
        printf("Pilih menu: ");
        scanf("%d", &pilih);
        getchar();

        switch (pilih) {
            case 1:
                tampilkanProduk();
                break;
            case 2:
                tambahkeranjang();
            case 3:
                lihatKeranjangbayar();
            case 4:
                pembayaran();
                break;
            case 5:
                if (adaTransaksi)
                    strukbayar(lastMetode, lastBayar, lastKembalian);
                else {
                    printf("Belum ada transaksi!\n");
                    Sleep(1000);
                }
                break;
            case 6:
                printf("Logout berhasil. Tekan Enter untuk kembali ke menu utama...");
                getchar();
                return;
            default:
                printf("Pilihan tidak valid.\n");
                Sleep(1000);
                break;
        }
    }
}

// =================== MAIN ===================

int main() {
    int pilih;
    loadingawal();

    while (1) {
        menu1();
        scanf("%d", &pilih);
        getchar();

        if (pilih == 1) {
            if (loginmasuk()) {
                menuKasir();
            }
        } else if (pilih == 2) {
            printf("Keluar program...\n");
            break;
        } else {
            printf("Salah pilih!\n");
            getchar();
        }
    }

    return 0;
}
