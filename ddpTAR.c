#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#define MAX_PRODUK 10
#define MAX_KERANJANG 50

// Variabel global
char lastMetode[20];
float lastBayar = 0.0f, lastKembalian = 0.0f;
int adaTransaksi = 0;
int notaID = 1;

typedef struct {
    char nama[50];
    float harga;
    int stok;
} Produk;

Produk daftarProduk[MAX_PRODUK] = {
    {"Indomie Goreng", 3500, 50},
    {"Aqua 600ml", 4000, 40},
    {"Teh Botol Sosro", 5000, 30},
    {"Roti Tawar", 15000, 20},
    {"Minyak Goreng 1L", 20000, 10},
    {"Beng-Beng", 3000, 90},
    {"Chocolatos", 2000, 10},
    {"Paddlepop", 10000, 20},
    {"Telur 1kg", 11000, 16},
    {"Susu Beruang", 11000, 50}
};

typedef struct {
    Produk item;
    int qty;
} keranjangItem;

keranjangItem keranjang[MAX_KERANJANG];
int jumlahkeranjang = 0;
float totalBelanja = 0.0f;

// Prototypes
void loadingawal_centered(const char *text);
void loadingawal_before_login(void);
void menu1(void);
int loginmasuk(void);
void tampilkanProduk(void);
void tampilkanProduk2(void);
void editProduk(void);
void tambahkeranjang(void);
void lihatKeranjangbayar(void);
void pembayaran(void);
void strukbayar(char metode[], float bayar, float kembalian);
void menuKasir(void);
void save_struk_to_file(const char *filename, const char *struktext);
void clear_input_buffer(void);
const char *random_address(void);

// =================== UTIL ===================
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

const char *random_address() {
    static const char *addresses[] = {
        "Toko Meong - Diponegoro No.6, Medan, Sumut",
        "Toko Meong - Jalan Kenangan No.11, Bandung",
        "Toko Meong - Jl. Aurora No.3, Antartika Basecamp",
        "Toko Meong - Jl. Pelangi No.9, Kuala Lumpur",
        "Toko Meong - Jl. Surya No.21, Hiroshima"
    };
    int n = sizeof(addresses) / sizeof(addresses[0]);
    return addresses[rand() % n];
}

// =================== LOADING (DI TENGAH) ===================
void loadingawal_centered(const char *text) {
    system("cls");
    system("color 0b");
    for (int i = 0; i < 6; ++i) printf("\n");
    printf("\t\t\t==========================================\n");
    // ensure text fits visually - truncate or pad if needed
    char buf[40];
    snprintf(buf, sizeof(buf), "%s", text);
    printf("\t\t\t||  %-34s  ||\n", buf);
    printf("\t\t\t==========================================\n");
    for (int i = 0; i <= 50; i++) {
        printf("\r\t\t\t      LOADING : %3d%%", i * 2);
        fflush(stdout);
        Sleep(12);
    }
    printf("\n\t\t\t      SELESAI! Tekan Enter untuk lanjut...");
    clear_input_buffer();
    
}

void loadingawal_before_login(void) {
    loadingawal_centered("LOADING TOKO MEONG...");
}

// =================== MENU LOGIN ===================
void menu1() {
    system("cls");
    printf("\n\n\n ==========================================\n");
    printf(" ||             MENU LOGIN               ||\n");
    printf(" ||        Project by Kelompok 6         ||\n");
    printf(" ==========================================\n");
    printf(" || 1. LOGIN                             ||\n");
    printf(" || 2. KELUAR                            ||\n");
    printf(" || 3. PEMBUAT PROJECT                   ||\n");
    printf(" ==========================================\n");
    printf(" PILIH :  ");
}



void author(){
    system("cls");
    printf("\n\n\n ==========================================\n");
    printf(" ||        PROJECT TUGAS RANCANG         ||\n");
    printf(" ||              KELOMPOK 6              ||\n");
    printf(" ==========================================\n");
    printf(" || 1. MIKHAELL - 672025048              ||\n");
    printf(" || 2. FADILLA                           ||\n");
    printf(" || 3. ARGA WIRA                         ||\n");
    printf(" || 4. NAUFALDEN                         ||\n");
    printf(" || 5. HARRDO                            ||\n");
    printf(" ||                                      ||\n");
    printf(" || # Enter Untuk Kembali                ||\n");
    printf(" ==========================================\n");


}





int loginmasuk() {
    char user[50], pass[50];
    system("cls");
    printf("\n\n ==========================================\n");
    printf(" ||              LOGIN AKUN             ||\n");
    printf(" ==========================================\n");

    printf(" USERNAME : ");
    if (!fgets(user, sizeof(user), stdin)) return 0;
    user[strcspn(user, "\n")] = 0;

    printf(" PASSWORD : ");
    if (!fgets(pass, sizeof(pass), stdin)) return 0;
    pass[strcspn(pass, "\n")] = 0;

    if (strcmp(user, "admin") == 0 && strcmp(pass, "123") == 0) {
        printf("\n LOGIN BERHASIL! Tekan Enter untuk lanjut...");
        getchar();
        return 1;
    } else {
        printf("\n LOGIN GAGAL! Tekan Enter untuk kembali...");
        getchar();
        return 0;
    }
}

// =================== PRODUK ===================
void tampilkanProduk() {
    system("cls");
    printf("=====================================\n");
    printf("        DAFTAR PRODUK TOKO MEONG     \n");
    printf("=====================================\n");
    for (int i = 0; i < MAX_PRODUK; i++) {
        printf("%2d. %-20s Rp %8.0f | Stok: %3d\n", i + 1, daftarProduk[i].nama, daftarProduk[i].harga, daftarProduk[i].stok);
    }
    printf("=====================================\n");
    printf("Tekan Enter untuk kembali...");
    getchar();
}

void tampilkanProduk2() {
    // same as tampilkanProduk but without pause - used inside loops
    system("cls");
    printf("=====================================\n");
    printf("        DAFTAR PRODUK TOKO MEONG     \n");
    printf("=====================================\n");
    for (int i = 0; i < MAX_PRODUK; i++) {
        printf("%2d. %-20s Rp %8.0f | Stok: %3d\n", i + 1, daftarProduk[i].nama, daftarProduk[i].harga, daftarProduk[i].stok);
    }
    printf("=====================================\n");
}

void editProduk() {
    int kode, pilih;
    char newNama[50];
    float newHarga;
    int newStok;

    tampilkanProduk2();
    printf("Masukkan nomor produk yang ingin diedit (99 = kembali): ");
    if (scanf("%d", &kode) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(800); return; }
    clear_input_buffer();

    if (kode == 99) {
        
        return;
    }

    if (kode < 1 || kode > MAX_PRODUK) {
        printf("Nomor produk tidak valid!\n");
        Sleep(1000);
        return;
    }

    system("cls");
    printf("=====================================\n");
    printf("     EDIT PRODUK: %s\n", daftarProduk[kode - 1].nama);
    printf("=====================================\n");
    printf("1. Ubah Nama\n");
    printf("2. Ubah Harga\n");
    printf("3. Ubah Stok\n");
    printf("99. Kembali\n");
    printf("Pilih menu: ");
    if (scanf("%d", &pilih) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(800); return; }
    clear_input_buffer();

    switch (pilih) {
        case 1:
            printf("Masukkan nama baru: ");
            if (!fgets(newNama, sizeof(newNama), stdin)) return;
            newNama[strcspn(newNama, "\n")] = 0;
            strcpy(daftarProduk[kode - 1].nama, newNama);
            printf("Nama berhasil diubah!\n");
            break;
        case 2:
            printf("Masukkan harga baru: Rp ");
            if (scanf("%f", &newHarga) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(800); return; }
            daftarProduk[kode - 1].harga = newHarga;
            clear_input_buffer();
            printf("Harga berhasil diubah!\n");
            break;
        case 3:
            printf("Masukkan stok baru: ");
            if (scanf("%d", &newStok) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(800); return; }
            daftarProduk[kode - 1].stok = newStok;
            clear_input_buffer();
            printf("Stok berhasil diubah!\n");
            break;
        case 99:
            return;
        default:
            printf("Pilihan tidak valid.\n");
            break;
    }

    Sleep(1000);
}

// =================== STRUK & FILE ===================
void save_struk_to_file(const char *filename, const char *struktext) {
    FILE *f = fopen(filename, "a");
    if (!f) return;
    fputs(struktext, f);
    fclose(f);
}

void strukbayar(char metode[], float bayar, float kembalian) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char waktu_str[64];
    snprintf(waktu_str, sizeof(waktu_str), "%04d-%02d-%02d %02d:%02d:%02d",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    const char *alamat = random_address();

    // hitung subtotal dari isi keranjang
    float subtotal = 0.0f;
    for (int i = 0; i < jumlahkeranjang; ++i)
        subtotal += keranjang[i].item.harga * keranjang[i].qty;

    // discount random 3-10%
    int discPercent = (rand() % 8) + 3; // 3..10
    float diskon = subtotal * discPercent / 100.0f;
    float taxable = subtotal - diskon;
    float ppn = taxable * 0.10f;
    float grandTotal = taxable + ppn;

    system("cls");
    printf("=====================================\n");
    printf("                STRUK                 \n");
    printf("=====================================\n");
    printf("Nota ID : %d\n", notaID);
    printf("Tanggal : %s\n", waktu_str);
    printf("Alamat  : %s\n", alamat);
    printf("-------------------------------------\n");
    if (jumlahkeranjang == 0) {
        printf("<Keranjang kosong>\n");
    } else {
        for (int i = 0; i < jumlahkeranjang; ++i) {
            printf("%-20s x%2d Rp %.0f\n", keranjang[i].item.nama, keranjang[i].qty,
                   keranjang[i].item.harga * keranjang[i].qty);
        }
    }
    printf("-------------------------------------\n");
    printf("SUBTOTAL   : Rp %.0f\n", subtotal);
    printf("DISKON %d%% : Rp %.0f\n", discPercent, diskon);
    printf("PPN 10%%    : Rp %.0f\n", ppn);
    printf("GRAND TOTAL: Rp %.0f\n", grandTotal);
    printf("DIBAYAR    : Rp %.0f\n", bayar);
    printf("KEMBALIAN  : Rp %.0f\n", kembalian);
    printf("METODE     : %s\n", metode);
    printf("=====================================\n");
    printf("   Terima kasih telah belanja di Toko Meong!\n");
    printf("=====================================\n");

    // simpan ke file
    char buffer[4096];
    int pos = 0;
    pos += snprintf(buffer + pos, sizeof(buffer) - pos, "Nota ID : %d\n", notaID);
    pos += snprintf(buffer + pos, sizeof(buffer) - pos, "Tanggal  : %s\n", waktu_str);
    pos += snprintf(buffer + pos, sizeof(buffer) - pos, "Alamat   : %s\n", alamat);
    pos += snprintf(buffer + pos, sizeof(buffer) - pos, "-------------------------------------\n");
    if (jumlahkeranjang == 0) {
        pos += snprintf(buffer + pos, sizeof(buffer) - pos, "<Keranjang kosong>\n");
    } else {
        for (int i = 0; i < jumlahkeranjang; ++i) {
            pos += snprintf(buffer + pos, sizeof(buffer) - pos, "%-20s x%2d Rp %.0f\n",
                            keranjang[i].item.nama, keranjang[i].qty,
                            keranjang[i].item.harga * keranjang[i].qty);
        }
    }
    pos += snprintf(buffer + pos, sizeof(buffer) - pos,
                    "-------------------------------------\nSUBTOTAL   : Rp %.0f\nDISKON %d%% : Rp %.0f\nPPN 10%%    : Rp %.0f\nGRAND TOTAL: Rp %.0f\nDIBAYAR    : Rp %.0f\nKEMBALIAN  : Rp %.0f\nMETODE     : %s\n=====================================\n\n",
                    subtotal, discPercent, diskon, ppn, grandTotal, bayar, kembalian, metode);

    save_struk_to_file("data.txt", buffer);

    // tunggu enter
    printf("\nTekan Enter untuk kembali ke menu...");
    getchar();
}

// =================== PEMBAYARAN (LOOP VALID) ===================
void pembayaran() {
    if (jumlahkeranjang == 0) {
        printf("Keranjang kosong! Tekan Enter untuk kembali...");
        getchar();
        return;
    }

    // hitung subtotal + discount random and grandTotal (but we recompute discount inside struk to persist same percent? 
    // We'll pick discount here and pass values; to keep struk and payment consistent, compute discount here and pass values to struk.)
    float subtotal = 0.0f;
    for (int i = 0; i < jumlahkeranjang; ++i)
        subtotal += keranjang[i].item.harga * keranjang[i].qty;

    
    int discPercent = (rand() % 8) + 3;
    float diskon = subtotal * discPercent / 100.0f;
    float taxable = subtotal - diskon;
    float ppn = taxable * 0.10f;
    float grandTotal = taxable + ppn;

 
    static int lastDiscPercent = 0;
    lastDiscPercent = discPercent;

    int metode = 0;
    float bayar = 0.0f;
    char namametode[20];

    while (1) {
        system("cls");
        printf("=====================================\n");
        printf("              PEMBAYARAN             \n");
        printf("=====================================\n");
        printf("Subtotal       : Rp %.0f\n", subtotal);
        printf("Diskon %d%%       : Rp %.0f\n", discPercent, diskon);
        printf("PPN 10%%         : Rp %.0f\n", ppn);
        printf("-------------------------------------\n");
        printf("GRAND TOTAL    : Rp %.0f\n", grandTotal);
        printf("-------------------------------------\n");
        printf("1. QRIS\n2. CASH\n3. TRANSFER\n4. BATAL BAYAR\n");
        printf("Pilih metode: ");
        if (scanf("%d", &metode) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(800); continue; }
        clear_input_buffer();

        if (metode == 4) {
            printf("Transaksi dibatalkan. Tekan Enter...");
            getchar();
            return;
        }

        switch (metode) {
            case 1: strcpy(namametode, "QRIS"); break;
            case 2: strcpy(namametode, "CASH"); break;
            case 3: strcpy(namametode, "TRANSFER"); break;
            default:
                printf("Metode tidak valid. Coba lagi.\n");
                Sleep(800);
                continue;
        }

        printf("Masukkan nominal pembayaran: Rp ");
        if (scanf("%f", &bayar) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(800); continue; }
        clear_input_buffer();

        if (bayar < grandTotal) {
            printf("Uang kurang! Tekan Enter untuk memilih metode lagi...");
            getchar();
            continue; // kembali ke pilih metode
        }

        float kembalian = bayar - grandTotal;

        // simpan last transaksi
        strcpy(lastMetode, namametode);
        lastBayar = bayar;
        lastKembalian = kembalian;
        adaTransaksi = 1;

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        char waktu_str[64];
        snprintf(waktu_str, sizeof(waktu_str), "%04d-%02d-%02d %02d:%02d:%02d",
                tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

        const char *alamat = random_address();

        system("cls");
        printf("=====================================\n");
        printf("                STRUK                 \n");
        printf("=====================================\n");
        printf("Nota ID : %d\n", notaID);
        printf("Tanggal : %s\n", waktu_str);
        printf("Alamat  : %s\n", alamat);
        printf("-------------------------------------\n");
        for (int i = 0; i < jumlahkeranjang; ++i) {
            printf("%-20s x%2d Rp %.0f\n", keranjang[i].item.nama, keranjang[i].qty,
                   keranjang[i].item.harga * keranjang[i].qty);
        }
        printf("-------------------------------------\n");
        printf("SUBTOTAL   : Rp %.0f\n", subtotal);
        printf("DISKON %d%% : Rp %.0f\n", discPercent, diskon);
        printf("PPN 10%%    : Rp %.0f\n", ppn);
        printf("GRAND TOTAL: Rp %.0f\n", grandTotal);
        printf("DIBAYAR    : Rp %.0f\n", bayar);
        printf("KEMBALIAN  : Rp %.0f\n", kembalian);
        printf("METODE     : %s\n", namametode);
        printf("=====================================\n");
        printf("   Terima kasih telah belanja di Toko Meong!\n");
        printf("=====================================\n");

        // Save to file with same content
        char buffer[4096];
        int pos = 0;
        pos += snprintf(buffer + pos, sizeof(buffer) - pos, "Nota ID : %d\n", notaID);
        pos += snprintf(buffer + pos, sizeof(buffer) - pos, "Tanggal  : %s\n", waktu_str);
        pos += snprintf(buffer + pos, sizeof(buffer) - pos, "Alamat   : %s\n", alamat);
        pos += snprintf(buffer + pos, sizeof(buffer) - pos, "-------------------------------------\n");
        for (int i = 0; i < jumlahkeranjang; ++i) {
            pos += snprintf(buffer + pos, sizeof(buffer) - pos, "%-20s x%2d Rp %.0f\n",
                            keranjang[i].item.nama, keranjang[i].qty,
                            keranjang[i].item.harga * keranjang[i].qty);
        }
        pos += snprintf(buffer + pos, sizeof(buffer) - pos,
                        "-------------------------------------\nSUBTOTAL   : Rp %.0f\nDISKON %d%% : Rp %.0f\nPPN 10%%    : Rp %.0f\nGRAND TOTAL: Rp %.0f\nDIBAYAR    : Rp %.0f\nKEMBALIAN  : Rp %.0f\nMETODE     : %s\n=====================================\n\n",
                        subtotal, discPercent, diskon, ppn, grandTotal, bayar, kembalian, namametode);

        save_struk_to_file("data.txt", buffer);

        // increment notaID for next transaction
        notaID++;

        // reset keranjang & total
        jumlahkeranjang = 0;
        totalBelanja = 0.0f;

        // wait enter and return to menu
        printf("\nTekan Enter untuk kembali ke menu...");
        getchar();
        return;
    }
}

// 
void tambahkeranjang() {
    int kode, qty;
    char lagi;

    do {
        tampilkanProduk2();

        printf("Masukkan nomor produk yang ingin dibeli (99 = kembali): ");
        if (scanf("%d", &kode) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(800); return; }
        clear_input_buffer();

        if (kode == 99) return;
        if (kode < 1 || kode > MAX_PRODUK) {
            printf("Nomor produk tidak valid!\n");
            Sleep(1000);
            continue;
        }

        printf("Masukkan jumlah: ");
        if (scanf("%d", &qty) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(800); return; }
        clear_input_buffer();

        if (qty < 1) {
            printf("Jumlah harus >= 1\n"); Sleep(800); continue;
        }

        if (qty > daftarProduk[kode - 1].stok) {
            printf("Stok tidak cukup!\n");
            Sleep(1000);
            continue;
        }

        daftarProduk[kode - 1].stok -= qty;
        keranjang[jumlahkeranjang].item = daftarProduk[kode - 1];
        keranjang[jumlahkeranjang].qty = qty;
        jumlahkeranjang++;
        totalBelanja += daftarProduk[kode - 1].harga * qty;

        printf("\n%s x%d ditambahkan.\n", daftarProduk[kode - 1].nama, qty);
        printf("Total sementara: Rp %.0f\n", totalBelanja);

        printf("\nTambah barang lagi? (y/n): ");
        if (scanf(" %c", &lagi) != 1) { clear_input_buffer(); lagi = 'n'; }
        clear_input_buffer();

    } while (lagi == 'y' || lagi == 'Y');
}

void lihatKeranjangbayar() {
    char lagi;
    system("cls");
    printf("=====================================\n");
    printf("             ISI KERANJANG ANDA      \n");
    printf("=====================================\n");

    if (jumlahkeranjang == 0) {
        printf("Keranjang kosong!\n");
        printf("\nTekan Enter untuk kembali...");
        getchar();
        return;
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

    printf("\nBayar sekarang? (y/n): ");
    if (scanf(" %c", &lagi) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(800); return; }
    clear_input_buffer();

    if (lagi == 'y' || lagi == 'Y') {
        // only proceed if cart not empty (already ensured)
        pembayaran();
    } else {
        return; // balik ke menu
    }
}

// =================== MENU KASIR ===================
void menuKasir() {
    int pilih;
    while (1) {
        system("cls");
        printf("=====================================\n");
        printf("         MENU KASIR - TOKO MEONG     \n");
        printf("=====================================\n");
        printf("1. Lihat Produk\n");
        printf("2. Edit Produk\n");
        printf("3. Tambah Produk ke Keranjang\n");
        printf("4. Lihat Keranjang & Bayar\n");
        printf("5. Struk Terakhir\n");
        printf("6. Logout\n");
        printf("=====================================\n");
        printf("Pilih menu: ");
        if (scanf("%d", &pilih) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(800); continue; }
        clear_input_buffer();

        switch (pilih) {
            case 1: tampilkanProduk(); break;
            case 2: editProduk(); break;
            case 3: tambahkeranjang();
            case 4: lihatKeranjangbayar(); break;
            case 5:
                if (adaTransaksi) {
                
                    printf("Menampilkan ringkasan pesanan terakhir:\n");
                    strukbayar(lastMetode, lastBayar, lastKembalian);
                } else {
                    printf("Belum ada transaksi!\nTekan Enter...");
                    getchar();
                }
                break;
            case 6:
                printf("Logout berhasil. Tekan Enter...");
                getchar();
                return;
            default:
                printf("Pilihan tidak valid.\n");
                Sleep(1000);
        }
    }
}

// =================== MAIN ===================
int main() {
    srand((unsigned int)time(NULL)); // random untuk alamat & diskon
    loadingawal_before_login();

    int pilih;
    while (1) {
        menu1();
        if (scanf("%d", &pilih) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(800); continue; }
        clear_input_buffer();

        if (pilih == 1) {
            if (loginmasuk()) menuKasir();
        } else if (pilih == 2) {
            printf("Keluar program...\n");
            break;
        } else if (pilih == 3){ author();
            getchar();
        }else {
            printf("Salah pilih!\n");
            Sleep(1000);
        }
    }
    return 0;
}
