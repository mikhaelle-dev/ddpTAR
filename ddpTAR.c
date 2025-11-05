// kasir_windows_full.c
// Versi: Windows-ready (MinGW / Code::Blocks / VSCode)
// Perubahan: semua system("clear") -> system("cls"), usleep(...) -> Sleep(ms), unistd.h dihapus

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#define MAX_PRODUK 100
#define MAX_KERANJANG 50

// =================== VARIABEL GLOBAL ===================
char lastMetode[20];
char tokoNama[] = "TOKO MEONG";
char kasir [50] = "Admin";
char metode [20];
float lastBayar = 0.0f, lastKembalian = 0.0f;
int adaTransaksi = 0;
int notaID = 1;

typedef struct {
    char nama[50];
    float harga;
    int stok;
} Produk;

/* Inisialisasi produk awal (beberapa contoh) */
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

int jumlahProduk = 10; // jumlah produk yang valid saat ini

typedef struct {
    Produk item;
    int qty;
} KeranjangItem;

KeranjangItem keranjang[MAX_KERANJANG];
int jumlahKeranjang = 0;
float totalBelanja = 0.0f;

// Untuk struk terakhir
char lastStrukText[8192] = "";
float lastSubtotal = 0.0f;
int lastDiscPercent = 0;
float lastDiskon = 0.0f;
float lastPpn = 0.0f;
float lastGrandTotal = 0.0f;

// =================== PROTOTYPE / UTIL ===================
void clear_input_buffer(void);
const char *random_address(void);
void save_struk_to_file(const char *filename, const char *struktext);
void tampilkan_struk_dari_text(const char *text);
void loadingawal_centered(const char *text);
void loadingawal_before_login(void);
void menu1(void);
int loginmasuk(void);
void author(void);

void tampilkanProduk(void);
void tampilkanProduk2(void);
void editProduk(void);
void tambahkeranjang(void);
void lihatKeranjangbayar(void);
void hapusDariKeranjang_menu(void);

void pembayaran(void);
void cetakStrukAndSave(const char *buffer);

// menu kasir
void menuKasir(void);
void lihatRiwayatFile(void);

// util implementations
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

const char *random_address() {
    static const char *addresses[] = {
        "Toko Meong - Diponegoro No.6, Medan",
        "Toko Meong - Jalan Kenangan No.11, Bandung",
        "Toko Meong - Jl. Pelangi No.9, Jakarta",
        "Toko Meong - Jl. Surya No.21, Surabaya",
        "Toko Meong - Jl. Aurora No.3, Antartika Basecamp"
    };
    int n = sizeof(addresses) / sizeof(addresses[0]);
    return addresses[rand() % n];
}

void save_struk_to_file(const char *filename, const char *struktext) {
    FILE *f = fopen(filename, "a");
    if (!f) return;
    fputs(struktext, f);
    fclose(f);
}

void tampilkan_struk_dari_text(const char *text) {
    system("cls");
    printf("%s", text);
    printf("\nTekan Enter untuk kembali ke menu...");
    getchar();
}

// =================== LOADING ===================
void loadingawal_centered(const char *text) {
    system("cls");
    for (int i = 0; i < 6; ++i) printf("\n");
    printf("\t\t==========================================\n");
    char buf[40];
    snprintf(buf, sizeof(buf), "%s", text);
    printf("\t\t||  %-34s  ||\n", buf);
    printf("\t\t==========================================\n");
    for (int i = 0; i <= 50; i++) {
        printf("\r\t\t      LOADING : %3d%%", i * 2);
        fflush(stdout);
        Sleep(10); // ~10000us -> 10ms
    }
    printf("\n\t\t      SELESAI! Tekan Enter...");
    getchar();
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

void author() {
        system("cls");
        printf("\n\n    ==========================================\n");
        printf("    ||         PROJECT TUGAS RANCANG        ||\n    ");
        printf("||             KELOMPOK 6               ||\n");
        printf("    ==========================================\n");
        printf("    || 1. MIKHAELL     - 672025048          ||\n");
        printf("    || 2. FADILLA      - 672025034          ||\n");
        printf("    || 3. ARGA WIRA    - 672025041          ||\n");
        printf("    || 4. NAUFALDEN    - 672025045          ||\n");
        printf("    || 5. HARRDO       - 672025060          ||\n");
        printf("    ==========================================\n");
        printf("    Tekan Enter untuk kembali...");
}

// login
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
    for (int i = 0; i < jumlahProduk; i++) {
        if (strlen(daftarProduk[i].nama) == 0) continue; // skip yang sudah dihapus
        printf("%2d. %-20s Rp %8.0f | Stok: %3d\n",
               i + 1, daftarProduk[i].nama, daftarProduk[i].harga, daftarProduk[i].stok);
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
    for (int i = 0; i < jumlahProduk; i++) {
        if (strlen(daftarProduk[i].nama) == 0) continue;
        printf("%2d. %-20s Rp %8.0f | Stok: %3d\n",
               i + 1, daftarProduk[i].nama, daftarProduk[i].harga, daftarProduk[i].stok);
    }
    printf("=====================================\n");
}

void editProduk() {
    int pilih, kode;
    char newNama[50];
    float newHarga;
    int newStok;

    while (1) {
        system("cls");
        printf("=====================================\n");
        printf("         MENU EDIT PRODUK            \n");
        printf("=====================================\n");
        printf("1. Lihat Produk\n");
        printf("2. Ubah Produk\n");
        printf("3. Tambah Produk Baru\n");
        printf("4. Hapus Produk\n");
        printf("5. Kembali\n");
        printf("=====================================\n");
        printf("Pilih menu: ");
        if (scanf("%d", &pilih) != 1) {
            clear_input_buffer();
            printf("Input invalid. Kembali ke menu edit...\n");
            Sleep(150); // usleep(150000)
            continue;
        }
        clear_input_buffer();

        if (pilih == 1) {
            // Lihat Produk -> tampilkan daftar seperti gambar 2 (tanpa pause paksa)
            system("cls");
            printf("=====================================\n");
            printf("        DAFTAR PRODUK TOKO MEONG     \n");
            printf("=====================================\n");
            for (int i = 0; i < jumlahProduk; i++) {
                if (strlen(daftarProduk[i].nama) == 0) continue;
                printf("%2d. %-20s Rp %8.0f | Stok: %3d\n",
                       i + 1, daftarProduk[i].nama, daftarProduk[i].harga, daftarProduk[i].stok);
            }
            printf("=====================================\n");
            // beri kesempatan lihat lalu langsung kembali ke menu (tidak memaksa Enter kecuali user mau)
            printf("Tekan Enter untuk kembali ke MENU EDIT PRODUK...");
            getchar();
            continue;
        }
        else if (pilih == 2) {
            // Ubah Produk -> tampilkan daftar lalu minta nomor
            system("cls");
            printf("=====================================\n");
            printf("        DAFTAR PRODUK TOKO MEONG     \n");
            printf("=====================================\n");
            for (int i = 0; i < jumlahProduk; i++) {
                if (strlen(daftarProduk[i].nama) == 0) continue;
                printf("%2d. %-20s Rp %8.0f | Stok: %3d\n",
                       i + 1, daftarProduk[i].nama, daftarProduk[i].harga, daftarProduk[i].stok);
            }
            printf("=====================================\n");
            printf("Masukkan nomor produk yang ingin diedit (99 = kembali): ");
            if (scanf("%d", &kode) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(100); continue; }
            clear_input_buffer();

            if (kode == 99) continue;
            if (kode < 1 || kode > jumlahProduk || strlen(daftarProduk[kode - 1].nama) == 0) {
                printf("Nomor produk tidak valid!\n");
                Sleep(100);
                continue;
            }

            // tampilkan sub-menu edit untuk produk terpilih
            while (1) {
                system("cls");
                printf("=====================================\n");
                printf("     EDIT PRODUK: %s\n", daftarProduk[kode - 1].nama);
                printf("=====================================\n");
                printf("1. Ubah Nama\n");
                printf("2. Ubah Harga\n");
                printf("3. Ubah Stok\n");
                printf("4. Kembali ke MENU EDIT PRODUK\n");
                printf("Pilih menu: ");
                if (scanf("%d", &pilih) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(100); continue; }
                clear_input_buffer();

                if (pilih == 1) {
                    printf("Masukkan nama baru: ");
                    if (!fgets(newNama, sizeof(newNama), stdin)) break;
                    newNama[strcspn(newNama, "\n")] = 0;
                    strcpy(daftarProduk[kode - 1].nama, newNama);
                    printf("Nama berhasil diubah!\n");
                    Sleep(100);
                } else if (pilih == 2) {
                    printf("Masukkan harga baru: Rp ");
                    if (scanf("%f", &newHarga) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(100); continue; }
                    daftarProduk[kode - 1].harga = newHarga;
                    clear_input_buffer();
                    printf("Harga berhasil diubah!\n");
                    Sleep(100);
                } else if (pilih == 3) {
                    printf("Masukkan stok baru: ");
                    if (scanf("%d", &newStok) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(100); continue; }
                    daftarProduk[kode - 1].stok = newStok;
                    clear_input_buffer();
                    printf("Stok berhasil diubah!\n");
                    Sleep(100);
                } else if (pilih == 4) {
                    break; // kembali ke MENU EDIT PRODUK
                } else {
                    printf("Pilihan tidak valid.\n");
                    Sleep(100);
                }
            }
        }
        else if (pilih == 3) {
            // Tambah Produk Baru
            if (jumlahProduk >= MAX_PRODUK) {
                printf("Kapasitas penuh!\n");
                Sleep(700);
                continue;
            }
            printf("Masukkan nama produk baru: ");
            if (!fgets(daftarProduk[jumlahProduk].nama, sizeof(daftarProduk[jumlahProduk].nama), stdin)) {
                clear_input_buffer(); continue;
            }
            daftarProduk[jumlahProduk].nama[strcspn(daftarProduk[jumlahProduk].nama, "\n")] = 0;
            printf("Masukkan harga: ");
            if (scanf("%f", &daftarProduk[jumlahProduk].harga) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(100); continue; }
            printf("Masukkan stok: ");
            if (scanf("%d", &daftarProduk[jumlahProduk].stok) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(100); continue; }
            clear_input_buffer();
            jumlahProduk++;
            printf("Produk baru berhasil ditambahkan!\n");
            Sleep(700);
        }
        else if (pilih == 4) {
            // Hapus Produk
            system("cls");
            printf("=====================================\n");
            printf("        DAFTAR PRODUK TOKO MEONG     \n");
            printf("=====================================\n");
            for (int i = 0; i < jumlahProduk; i++) {
                if (strlen(daftarProduk[i].nama) == 0) continue;
                printf("%2d. %-20s Rp %8.0f | Stok: %3d\n",
                       i + 1, daftarProduk[i].nama, daftarProduk[i].harga, daftarProduk[i].stok);
            }
            printf("=====================================\n");
            printf("\nMasukkan nomor produk yang ingin dihapus: ");
            if (scanf("%d", &kode) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(100); continue; }
            clear_input_buffer();
            if (kode < 1 || kode > jumlahProduk) {
                printf("Nomor tidak valid!\n");
                Sleep(700);
                continue;
            }
            // geser array untuk hapus
            for (int i = kode - 1; i < jumlahProduk - 1; i++) {
                daftarProduk[i] = daftarProduk[i + 1];
            }
            // kosongkan last slot just in case
            strcpy(daftarProduk[jumlahProduk - 1].nama, "");
            daftarProduk[jumlahProduk - 1].harga = 0;
            daftarProduk[jumlahProduk - 1].stok = 0;
            jumlahProduk--;
            printf("Produk berhasil dihapus!\n");
            Sleep(700);
        }
        else if (pilih == 5) {
            // Kembali ke menu utama
            return;
        }
        else {
            printf("Pilihan tidak valid. Silakan pilih kembali.\n");
            Sleep(100);
        }
    }
}

// =================== TAMBAH KERANJANG ===================
void tambahkeranjang() {
    int kode, qty;
    char lagi = 'n';

    do {
        tampilkanProduk2();
        printf("Masukkan nomor produk yang ingin dibeli (99 = kembali): ");
        if (scanf("%d", &kode) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(100); return; }
        clear_input_buffer();

        if (kode == 99) return;
        if (kode < 1 || kode > jumlahProduk || strlen(daftarProduk[kode - 1].nama) == 0) {
            printf("Nomor produk tidak valid!\n");
            Sleep(100);
            continue;
        }

        printf("Masukkan jumlah: ");
        if (scanf("%d", &qty) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(100); return; }
        clear_input_buffer();

        if (qty < 1) {
            printf("Jumlah harus >= 1\n"); Sleep(100); continue;
        }

        if (qty > daftarProduk[kode - 1].stok) {
            printf("Stok tidak cukup!\n");
            Sleep(100);
            continue;
        }

        daftarProduk[kode - 1].stok -= qty;
        keranjang[jumlahKeranjang].item = daftarProduk[kode - 1];
        keranjang[jumlahKeranjang].qty = qty;
        jumlahKeranjang++;
        totalBelanja += daftarProduk[kode - 1].harga * qty;

        printf("\n%s x%d ditambahkan.\n", daftarProduk[kode - 1].nama, qty);
        printf("Total sementara: Rp %.0f\n", totalBelanja);

        printf("\nTambah barang lagi? (y/n): ");
        if (scanf(" %c", &lagi) != 1) { clear_input_buffer(); lagi = 'n'; }
        clear_input_buffer();

    } while (lagi == 'y' || lagi == 'Y');
}

// =================== LIHAT KERANJANG & OPERASI (hapus item dll) ===================
void hapusDariKeranjang_menu() {
    if (jumlahKeranjang == 0) {
        printf("Keranjang kosong!\n");
        return;
    }

    int hapus;
    printf("Nomor produk yang ingin dihapus/ubah jumlah (0 = batal): ");
    if (scanf("%d", &hapus) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(100); return; }
    clear_input_buffer();

    if (hapus == 0) return;
    if (hapus < 1 || hapus > jumlahKeranjang) {
        printf("Nomor tidak valid!\n");
        return;
    }

    // tampilkan qty dan opsi
    int currentQty = keranjang[hapus - 1].qty;
    printf("Produk: %s | Jumlah: %d\n", keranjang[hapus - 1].item.nama, currentQty);
    printf("1. Hapus seluruh item\n2. Kurangi sejumlah item\nPilih: ");
    int opsi;
    if (scanf("%d", &opsi) != 1) { clear_input_buffer(); printf("Input invalid\n"); return; }
    clear_input_buffer();

    if (opsi == 1) {
        // kembalikan stok ke daftarProduk
        for (int p = 0; p < jumlahProduk; ++p) {
            if (strlen(daftarProduk[p].nama) == 0) continue;
            if (strcmp(daftarProduk[p].nama, keranjang[hapus - 1].item.nama) == 0) {
                daftarProduk[p].stok += keranjang[hapus - 1].qty;
                break;
            }
        }
        totalBelanja -= keranjang[hapus - 1].item.harga * keranjang[hapus - 1].qty;
        for (int j = hapus - 1; j < jumlahKeranjang - 1; j++)
            keranjang[j] = keranjang[j + 1];
        jumlahKeranjang--;
        printf("Produk dihapus dari keranjang.\n");
    } else if (opsi == 2) {
        printf("Masukkan jumlah yang ingin dikurangi (1 - %d): ", currentQty - 1);
        int kurang;
        if (scanf("%d", &kurang) != 1) { clear_input_buffer(); printf("Input invalid\n"); return; }
        clear_input_buffer();
        if (kurang <= 0 || kurang >= currentQty) {
            printf("Jumlah tidak valid. Gunakan opsi Hapus seluruh jika mau menghapus semua.\n");
            return;
        }
        // kurangi qty
        keranjang[hapus - 1].qty -= kurang;
        totalBelanja -= keranjang[hapus - 1].item.harga * kurang;
        // kembalikan stok setara reduction
        for (int p = 0; p < jumlahProduk; ++p) {
            if (strlen(daftarProduk[p].nama) == 0) continue;
            if (strcmp(daftarProduk[p].nama, keranjang[hapus - 1].item.nama) == 0) {
                daftarProduk[p].stok += kurang;
                break;
            }
        }
        printf("Jumlah di keranjang dikurangi %d unit. Sisa %d unit.\n", kurang, keranjang[hapus - 1].qty);
    } else {
        printf("Opsi tidak valid.\n");
    }
}

// lihat keranjang & pilihan bayar/hapus/kembali
void lihatKeranjangbayar() {
    int pilih;
    if (jumlahKeranjang == 0) {
        printf("Keranjang kosong!\n");
        printf("\nTekan Enter untuk kembali...");
        getchar();
        return;
    }

    while (1) {
        system("cls");
        printf("=====================================\n");
        printf("             ISI KERANJANG ANDA      \n");
        printf("=====================================\n");

        for (int i = 0; i < jumlahKeranjang; i++) {
            printf("%d. %-20s x%d  Rp %.0f\n",
                i + 1,
                keranjang[i].item.nama,
                keranjang[i].qty,
                keranjang[i].item.harga * keranjang[i].qty);
        }
        printf("-------------------------------------\n");
        printf("TOTAL BELANJA: Rp %.0f\n", totalBelanja);
        printf("\n1. Bayar Sekarang\n2. Hapus / Kurangi Produk dari Keranjang\n3. Kembali\n");
        printf("Pilih: ");
        if (scanf("%d", &pilih) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(100); continue; }
        clear_input_buffer();

        if (pilih == 1) {
            pembayaran();
            return;
        } else if (pilih == 2) {
            hapusDariKeranjang_menu();
            printf("\nTekan Enter untuk melanjutkan...");
            getchar();
        } else {
            return;
        }
    }
}

// =================== CETAK STRUK (pakai buffer dari pembayaran) ===================
void cetakStrukAndSave(const char *buffer) {
    // tampilkan buffer di layar
    system("cls");
    printf("%s", buffer);

    // simpan ke file riwayat_struk.txt (append) di working dir Windows
    save_struk_to_file("riwayat_struk.txt", buffer);

    // simpan ke lastStrukText (untuk menu "Struk Terakhir")
    strncpy(lastStrukText, buffer, sizeof(lastStrukText) - 1);
    lastStrukText[sizeof(lastStrukText) - 1] = '\0';

    adaTransaksi = 1;

    printf("\nStruk sukses disimpan ke 'riwayat_struk.txt'\n");
    printf("Tekan Enter untuk kembali...");
    getchar();
}

// =================== PEMBAYARAN (dengan simpan struk & lastStruk) ===================
void pembayaran() {
    if (jumlahKeranjang == 0) {
        printf("Keranjang kosong! Tekan Enter untuk kembali...");
        getchar();
        return;
    }

    // hitung subtotal
    float subtotal = 0.0f;
    for (int i = 0; i < jumlahKeranjang; ++i)
        subtotal += keranjang[i].item.harga * keranjang[i].qty;

    // discount random 3-10%
    int discPercent = (rand() % 8) + 3; // 3..10
    float diskon = subtotal * discPercent / 100.0f;
    float taxable = subtotal - diskon;
    float ppn = taxable * 0.10f;
    float grandTotal = taxable + ppn;

    // simpan ke global supaya struk konsisten
    lastSubtotal = subtotal;
    lastDiscPercent = discPercent;
    lastDiskon = diskon;
    lastPpn = ppn;
    lastGrandTotal = grandTotal;

    int pilihMetode = 0;
    float bayar = 0.0f;
    char namametode[20];

    while (1) {
        system("cls");
        printf("=====================================\n");
        printf("              PEMBAYARAN             \n");
        printf("=====================================\n");
        printf("Subtotal   : Rp %.0f\n", subtotal);
        printf("Diskon %d%% : Rp %.0f\n", discPercent, diskon);
        printf("PPN 10%%    : Rp %.0f\n", ppn);
        printf("=====================================\n");
        printf("GRAND TOTAL: Rp %.0f\n", grandTotal);
        printf("=====================================\n");
        printf("1. QRIS\n2. CASH\n3. TRANSFER\n4. BATAL BAYAR\n");
        printf("Pilih metode: ");
        if (scanf("%d", &pilihMetode) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(100); continue; }
        clear_input_buffer();

        if (pilihMetode == 4) {
            printf("Transaksi dibatalkan. Tekan Enter...");
            getchar();
            return;
        }

        if (pilihMetode != 1 && pilihMetode != 2 && pilihMetode != 3) {
            printf("Metode tidak valid. Coba lagi.\n");
            Sleep(100);
            continue;
        }

        if (pilihMetode == 1) { strcpy(namametode, "QRIS"); }
        else if (pilihMetode == 2) { strcpy(namametode, "CASH"); }
        else if (pilihMetode == 3) { strcpy(namametode, "TRANSFER"); }

        if (pilihMetode == 2) {
            // CASH: minta input nominal
            printf("Masukkan nominal pembayaran: Rp ");
            if (scanf("%f", &bayar) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(100); continue; }
            clear_input_buffer();

            if (bayar < grandTotal) {
                printf("Uang kurang! Tekan Enter untuk memilih metode lagi...");
                getchar();
                continue; // kembali ke pilih metode
            }
        } else {
            // QRIS & TRANSFER otomatis dianggap 'lunas'
            bayar = grandTotal;
        }

        float kembalian = bayar - grandTotal;

        // simpan last transaksi
        strncpy(lastMetode, namametode, sizeof(lastMetode)-1);
        lastMetode[sizeof(lastMetode)-1]=0;
        lastBayar = bayar;
        lastKembalian = kembalian;
        adaTransaksi = 1;

        // juga isi global 'metode' supaya konsisten bila diperlukan
        strncpy(metode, namametode, sizeof(metode)-1);
        metode[sizeof(metode)-1] = '\0';

        // build struk ke buffer (sehingga bisa disimpan dan ditampilkan lagi)
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        char waktu_str[64];
        snprintf(waktu_str, sizeof(waktu_str), "%04d-%02d-%02d %02d:%02d:%02d",
                tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        const char *alamat = random_address();

FILE *f = fopen("riwayat_struk.txt", "a");
if (!f) return;

fprintf(f, "=====================================\n");
fprintf(f, "              STRUK                 \n");
fprintf(f, "=====================================\n");
fprintf(f, "Nota ID : %d\n", notaID);
fprintf(f, "Tanggal : %s\n", waktu_str);
fprintf(f, "Alamat  : %s\n", alamat);
fprintf(f, "-------------------------------------\n");

for (int i = 0; i < jumlahKeranjang; ++i) {
    fprintf(f, "%-20s x%2d Rp %.0f\n",
            keranjang[i].item.nama,
            keranjang[i].qty,
            keranjang[i].item.harga * keranjang[i].qty);
}

fprintf(f, "-------------------------------------\n");
fprintf(f, "SUBTOTAL   : Rp %.0f\n", subtotal);
fprintf(f, "DISKON %d%% : Rp %.0f\n", discPercent, diskon);
fprintf(f, "PPN 10%%    : Rp %.0f\n", ppn);
fprintf(f, "GRAND TOTAL: Rp %.0f\n", grandTotal);
fprintf(f, "DIBAYAR    : Rp %.0f\n", bayar);
fprintf(f, "KEMBALIAN  : Rp %.0f\n", kembalian);
fprintf(f, "METODE     : %s\n", namametode);
fprintf(f, "=====================================\n\n");

fclose(f);

// tampilkan di layar juga
system("cls");
printf("=====================================\n");
printf("              STRUK                 \n");
printf("=====================================\n");
printf("Nota ID : %d\n", notaID);
printf("Tanggal : %s\n", waktu_str);
printf("Alamat  : %s\n", alamat);
printf("-------------------------------------\n");

for (int i = 0; i < jumlahKeranjang; ++i) {
    printf("%-20s x%2d Rp %.0f\n",
        keranjang[i].item.nama,
        keranjang[i].qty,
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
printf("=====================================\n\n");
printf("Struk juga telah disimpan ke 'riwayat_struk.txt'\n");
printf("Tekan Enter untuk kembali...");
getchar();

// increment notaID for next transaction
notaID++;

// reset keranjang & total (lakukan setelah cetak & simpan)
jumlahKeranjang = 0;
totalBelanja = 0.0f;

return;


        // increment notaID for next transaction
        notaID++;

        // reset keranjang & total (lakukan setelah cetak & simpan)
        jumlahKeranjang = 0;
        totalBelanja = 0.0f;

        return;
    }
}

// =================== RIWAYAT FILE ===================
void lihatRiwayatFile(void) {
    system("cls");
    FILE *file = fopen("riwayat_struk.txt", "r");
    if (!file) {
        printf("Belum ada riwayat pembelian.\n");
        printf("Tekan Enter untuk kembali...");
        getchar();
        return;
    }
    printf("===== RIWAYAT PEMBELIAN =====\n\n");
    char baris[1024];
    while (fgets(baris, sizeof(baris), file)) {
        printf("%s", baris);
    }
    fclose(file);
    printf("\nTekan Enter untuk kembali...");
    getchar();
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
        printf("6. Lihat Riwayat File\n");
        printf("7. Logout\n");
        printf("=====================================\n");
        printf("Pilih menu: ");
        if (scanf("%d", &pilih) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(100); continue; }
        clear_input_buffer();

        switch (pilih) {
            case 1:
                tampilkanProduk();
                break;
            case 2:
                editProduk();
                break;
            case 3:
                tambahkeranjang();
                break;
            case 4:
                lihatKeranjangbayar();
                break;
            case 5:
                if (adaTransaksi && strlen(lastStrukText) > 0) {
                    tampilkan_struk_dari_text(lastStrukText);
                } else {
                    printf("Belum ada transaksi!\nTekan Enter...");
                    getchar();
                }
                break;
            case 6:
                lihatRiwayatFile();
                break;
            case 7:
                printf("Logout berhasil. Tekan Enter...");
                getchar();
                return;
            default:
                printf("Pilihan tidak valid.\n");
                Sleep(100);
        }
    }
}

// =================== MAIN ===================
int main() {
    srand((unsigned int)time(NULL)); // random untuk alamat  diskon

    loadingawal_before_login();

    int pilih;
    while (1) {
        menu1();
        if (scanf("%d", &pilih) != 1) { clear_input_buffer(); printf("Input invalid\n"); Sleep(100); continue; }
        clear_input_buffer();

        if (pilih == 1) {
            if (loginmasuk()) menuKasir();
        } else if (pilih == 2) {
            printf("Keluar program...\n");
            break;
        } else if (pilih == 3) {
            author();
            getchar();
        } else {
            printf("Salah pilih!\n");
            Sleep(100);
        }
    }

    return 0;
}


// git add .
// git commit -m "Update"
// git branch
//git push origin main
