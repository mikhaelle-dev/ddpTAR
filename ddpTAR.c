#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <direct.h> // untuk _mkdir

#define MAX_PRODUK 100
#define MAX_KERANJANG 50
int sw, sh;


char tokoNama[] = "TOKO MEONG";
char kasir[] = "Admin";

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

int jumlahProduk = 10;

typedef struct {
    Produk item;
    int qty;
} KeranjangItem;

KeranjangItem keranjang[MAX_KERANJANG];
int jumlahKeranjang = 0;
float totalBelanja = 0.0f;

int notaID = 1;










// Fungsi untuk mengatur posisi cursor
void gotoxy(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// Fungsi untuk mendapatkan ukuran layar
void updateScreenSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    sw = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    sh = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

// Fungsi beep sederhana
void beep() {
    Beep(750, 300); // frekuensi 750Hz, durasi 300ms
}

// Fungsi typewriter
void typewriter(const char *text, int delay) {
    for (int i = 0; i < strlen(text); i++) {
        printf("%c", text[i]);
        Sleep(delay);
    }
}

// Fungsi tampilAngka buat keluar program
void tampilAngka(const char *angka[], int baris) {
    system("cls");
    updateScreenSize();
    int ypos = (sh / 2) - (baris / 2);
    for (int i = 0; i < baris; i++) {
        int xpos = (sw / 2) - (strlen(angka[i]) / 2);
        gotoxy(xpos, ypos + i);
        printf("%s\n", angka[i]);
    }
    Sleep(1500);
}

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

const char *random_address() {
    static const char *addresses[] = {
        "Toko Meong - Diponegoro No.6, pochinki",
        "Toko Meong - Jalan Kenangan No.11, moniyan",
        "Toko Meong - Jl. Pelangi No.9, halmahera",
        "Toko Meong - Jl. Surya No.21, paris",
        "Toko Meong - Jl. Aurora No.3, Antartika Basecamp"
    };
    int n = sizeof(addresses) / sizeof(addresses[0]);
    return addresses[rand() % n];
}

void ensure_riwayat_folder() {
    const char *folder = "C:\\kasir meong\\riwayat";
    // _mkdir akan mengembalikan 0 jika berhasil, atau -1 jika gagal/already exists
    _mkdir(folder); // kalau sudah ada, tidak masalah
}
void loadingawal_tengah(const char *text) 
{
    int width = 50; 
    system("cls");

    int y_judul = sh / 2 - 6;
    int y_bar   = sh / 2 - 2;
    int y_info  = y_bar + 7;
    int x_judul = (sw - 30) / 2;

    // Judul
    gotoxy(x_judul, y_judul);
    printf("SELAMAT DATANG DI TUGAS RANCANG");

    int x_bar = (sw - (width + 4)) / 2;

    for (int i = 0; i <= 100; i++)
    {
        // Teks persentase loading
        gotoxy((sw - 15) / 2, y_bar - 1);
        printf("Loading : %3d%%", i);

        // Garis atas
        gotoxy(x_bar, y_bar);
        for (int j = 0; j < width + 4; j++)
            printf("=");

        // Isi bar
        gotoxy(x_bar, y_bar + 1);
        printf("||");

        int fill = i * width / 100;
        for (int j = 0; j < width; j++)
            printf(j < fill ? "#" : " ");  // ← FIX: sekarang terisi

        printf("||");

        // Garis bawah
        gotoxy(x_bar, y_bar + 2);
        for (int j = 0; j < width + 4; j++)
            printf("=");

        Sleep(5); // lebih smooth
    }

    // Instruksi lanjut
    gotoxy((sw - 24) / 2, y_info);
    printf("TEKAN ENTER UNTUK LANJUT");

    getchar();
}


void loadingawal_tengah2(const char *text){
    system("cls");
    updateScreenSize();
    int y_loading = sh / 2;
    int x_loading = (sw / 2) - 35;
    for (int i = 0; i <= 50; i++)
    {
        gotoxy(x_loading, y_loading);
        printf("                  LOADING : %3d%%            ", i * 2);
        fflush(stdout);
        Sleep(30);
    }
}

void keluar_program() {
    system("cls");
    updateScreenSize();

    beep();

    // Pesan terima kasih
    const char *msg = "Terima kasih telah menggunakan program ini!";
    int xpos = (sw / 2) - (strlen(msg) / 2);
    int ypos = sh / 2 - 2;
    gotoxy(xpos, ypos);
    printf("%s", msg);
    Sleep(3000);

    // Angka 3 jumbo
    const char *angka3[] = {
        "    ***********   ",
        "   *************  ",
        "  **         ***  ",
        "             ***  ",
        "             ***  ",
        "      *********   ",
        "      *********   ",
        "             ***  ",
        "             ***  ",
        "  **         ***  ",
        "   *************  ",
        "    ***********   ",
        "                 ",
        "                 ",
        "                 "
    };
    tampilAngka(angka3, 15);

    // Angka 2 jumbo
    const char *angka2[] = {
        "    ***********   ",
        "   *************  ",
        "  **         ***  ",
        "             ***  ",
        "             ***  ",
        "           ***    ",
        "         ***      ",
        "       ***        ",
        "     ***          ",
        "   ***            ",
        "  ****************",
        " *****************",
        "                 ",
        "                 ",
        "                 "
    };
    tampilAngka(angka2, 15);

    // Angka 1 tebal
    const char *angka1[] = {
        "    ****  ",
        "   *****  ",
        "  ******  ",
        "    ****  ",
        "    ****  ",
        "    ****  ",
        "    ****  ",
        "    ****  ",
        "    ****  ",
        "  ********"
    };
    tampilAngka(angka1, 10);

    // Kotak pesan terakhir
    system("cls");
    updateScreenSize();

const char *box_top    = "||==========================================================================||";
const char *box_mid1   = "||                                                                          ||";
const char *box_mid2   = "||                           IKAN HIU MAKAN SARI ROTI                       ||";
const char *box_mid3   = "||                     ROTINYA HABIS DIMAKAN BURUNG PERKUTUT                ||";
const char *box_mid4   = "||                             TERIMA KASIH KAK AFI                         ||";
const char *box_mid5   = "||                ATAS ILMU DAN BIMBINGAN SELAMA SATU SEMESTER INI          ||";
const char *box_mid6   = "||                                                                          ||";
const char *box_mid7   = "||                              - KELOMPOK 6 -                              ||";
const char *box_mid8   = "||                                                                          ||";
const char *box_bottom = "||==========================================================================||";


    int bx = (sw / 2) - (strlen(box_top) / 2);
    int by = sh / 2 - 5;

    beep();
    gotoxy(bx, by);     typewriter(box_top, 30);
    gotoxy(bx, by+1);   typewriter(box_mid1, 30);
    gotoxy(bx, by+2);   typewriter(box_mid2, 30);
    gotoxy(bx, by+3);   typewriter(box_mid3, 30);
    gotoxy(bx, by+4);   typewriter(box_mid4, 30);
    gotoxy(bx, by+5);   typewriter(box_mid5, 30);
    gotoxy(bx, by+6);   typewriter(box_mid6, 30);
    gotoxy(bx, by+7);   typewriter(box_mid7, 30);
    gotoxy(bx, by+8);   typewriter(box_mid8, 30);
    gotoxy(bx, by+9);   typewriter(box_bottom, 30);

    beep();
    Sleep(3000);

}

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
    printf("    ||         PROJECT TUGAS RANCANG        ||\n");
    printf("    ||             KELOMPOK 6               ||\n");
    printf("    ==========================================\n");
    printf("    || 1. MIKHAELL     - 672025048          ||\n");
    printf("    || 2. FADILLA      - 672025034          ||\n");
    printf("    || 3. ARGA WIRA    - 672025041          ||\n");
    printf("    || 4. NAUFALDEN    - 672025045          ||\n");
    printf("    || 5. HARRDO       - 672025060          ||\n");
    printf("    ==========================================\n");
    printf("    Tekan Enter untuk kembali...");
}

int loginmasuk() {
    char user[50], pass[50];
    system("cls");
    printf("\n\n ==========================================\n");
    printf(" ||             LOGIN AKUN               ||\n");
    printf(" ==========================================\n");

    printf(" USERNAME : ");
    fgets(user, sizeof(user), stdin);
    user[strcspn(user, "\n")] = 0;

    printf(" PASSWORD : ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = 0;

    if (strcmp(user, "admin") == 0 && strcmp(pass, "123") == 0) {
        printf("\n LOGIN BERHASIL! Tekan Enter untuk lanjut...");
        loadingawal_tengah2("");
        return 1;
    } else {
        printf("\n LOGIN GAGAL! Tekan Enter untuk kembali...");
        getchar();
        return 0;
    }
}

void tampilkanProduk() {
    system("cls");
    printf("=======================================================\n");
    printf("||              DAFTAR PRODUK TOKO MEONG             ||\n");
    printf("=======================================================\n");
    for (int i = 0; i < jumlahProduk; i++) {
        if (strlen(daftarProduk[i].nama) == 0) continue;
        printf("|| %2d. %-20s Rp %8.0f | Stok: %3d  ||\n",
            i + 1, daftarProduk[i].nama, daftarProduk[i].harga, daftarProduk[i].stok);
    }
    printf("=======================================================\n");
    printf("Tekan Enter untuk kembali...");
    getchar();
}

void tampilkanProduk2() {
    system("cls");
    printf("=======================================================\n");
    printf("||              DAFTAR PRODUK TOKO MEONG             ||\n");
    printf("=======================================================\n");
    for (int i = 0; i < jumlahProduk; i++) {
        if (strlen(daftarProduk[i].nama) == 0) continue;
        printf("|| %2d. %-20s Rp %8.0f | Stok: %3d  ||\n",
            i + 1, daftarProduk[i].nama, daftarProduk[i].harga, daftarProduk[i].stok);
    }
    printf("=======================================================\n");
}

void editProduk() {
    int pilih, kode;
    char newNama[50];
    float newHarga;
    int newStok;

    while (1) {
        system("cls");
        printf("=======================================\n");
        printf("||           MENU EDIT PRODUK        ||\n");
        printf("=======================================\n");
        printf("|| 1. Lihat Produk                   ||\n");
        printf("|| 2. Ubah Produk                    ||\n");
        printf("|| 3. Tambah Produk Baru             ||\n");
        printf("|| 4. Hapus Produk                   ||\n");
        printf("|| 5. Kembali                        ||\n");
        printf("=======================================\n");
        printf("Pilih menu: ");
        scanf("%d", &pilih);
        clear_input_buffer();

        if (pilih == 1) {
            tampilkanProduk();
        }

        else if (pilih == 2) {
            tampilkanProduk2();
            printf("Masukkan nomor produk yang ingin diedit (99 = kembali): ");
            scanf("%d", &kode);
            clear_input_buffer();
            if (kode == 99) continue;
            if (kode < 1 || kode > jumlahProduk) continue;

            while (1) {
                system("cls");
                printf("=====================================\n");
                printf("EDIT PRODUK: %s\n", daftarProduk[kode - 1].nama);
                printf("1. Ubah Nama\n");
                printf("2. Ubah Harga\n");
                printf("3. Ubah Stok\n");
                printf("4. Kembali\n");
                printf("Pilih: ");
                scanf("%d", &pilih);
                clear_input_buffer();

                if (pilih == 1) {
                    printf("Nama baru: ");
                    fgets(newNama, sizeof(newNama), stdin);
                    newNama[strcspn(newNama, "\n")] = 0;
                    strcpy(daftarProduk[kode - 1].nama, newNama);
                }
                else if (pilih == 2) {
                    printf("Harga baru: ");
                    scanf("%f", &newHarga);
                    daftarProduk[kode - 1].harga = newHarga;
                }
                else if (pilih == 3) {
                    printf("Stok baru: ");
                    scanf("%d", &newStok);
                    daftarProduk[kode - 1].stok = newStok;
                }
                else break;
            }
        }

        else if (pilih == 3) {
            printf("Nama produk baru: ");
            fgets(daftarProduk[jumlahProduk].nama, 50, stdin);
            daftarProduk[jumlahProduk].nama[strcspn(daftarProduk[jumlahProduk].nama, "\n")] = 0;
            printf("Harga: ");
            scanf("%f", &daftarProduk[jumlahProduk].harga);
            printf("Stok: ");
            scanf("%d", &daftarProduk[jumlahProduk].stok);
            clear_input_buffer();
            jumlahProduk++;
        }

        else if (pilih == 4) {
            tampilkanProduk2();
            printf("Nomor produk yang ingin dihapus: ");
            scanf("%d", &kode);
            clear_input_buffer();
            if (kode < 1 || kode > jumlahProduk) continue;

            for (int i = kode - 1; i < jumlahProduk - 1; i++) {
                daftarProduk[i] = daftarProduk[i + 1];
            }
            jumlahProduk--;
        }

        else if (pilih == 5) return;
    }
}

void tambahkeranjang() {
    int kode, qty;
    char lagi = 'n';

    do {
        tampilkanProduk2();
        printf("Nomor produk (99=Kembali): ");
        scanf("%d", &kode);
        clear_input_buffer();

        if (kode == 99) return;
        if (kode < 1 || kode > jumlahProduk) continue;

        printf("Jumlah: ");
        scanf("%d", &qty);
        clear_input_buffer();

        if (qty <= 0 || qty > daftarProduk[kode - 1].stok) continue;

        daftarProduk[kode - 1].stok -= qty;
        keranjang[jumlahKeranjang].item = daftarProduk[kode - 1];
        keranjang[jumlahKeranjang].qty = qty;
        jumlahKeranjang++;
        totalBelanja += daftarProduk[kode - 1].harga * qty;

        printf("Tambah lagi? (y/n): ");
        scanf(" %c", &lagi);
        clear_input_buffer();

    } while (lagi == 'y' || lagi == 'Y');
}

void hapusDariKeranjang_menu() {
    if (jumlahKeranjang == 0) {
        printf("Keranjang kosong!\n");
        return;
    }

    int hapus;
    printf("Nomor produk (0=Batal): ");
    scanf("%d", &hapus);
    clear_input_buffer();

    if (hapus == 0) return;
    if (hapus < 1 || hapus > jumlahKeranjang) return;

    Produk *item = &keranjang[hapus - 1].item;
    int qty = keranjang[hapus - 1].qty;

    printf("1. Hapus semua\n2. Kurangi jumlah\nPilih: ");
    int opsi;
    scanf("%d", &opsi);
    clear_input_buffer();

    if (opsi == 1) {
        for (int i = 0; i < jumlahProduk; i++) {
            if (strcmp(daftarProduk[i].nama, item->nama) == 0)
                daftarProduk[i].stok += qty;
        }
        totalBelanja -= item->harga * qty;

        for (int i = hapus - 1; i < jumlahKeranjang - 1; i++)
            keranjang[i] = keranjang[i + 1];
        jumlahKeranjang--;
    }

    else if (opsi == 2) {
        printf("Kurangi berapa: ");
        int kurang;
        scanf("%d", &kurang);
        clear_input_buffer();

        if (kurang <= 0 || kurang >= qty) return;

        keranjang[hapus - 1].qty -= kurang;
        totalBelanja -= item->harga * kurang;

        for (int i = 0; i < jumlahProduk; i++) {
            if (strcmp(daftarProduk[i].nama, item->nama) == 0)
                daftarProduk[i].stok += kurang;
        }
    }
}

void pembayaran() {
    if (jumlahKeranjang == 0) {
        printf("Keranjang kosong! Tekan Enter...");
        getchar();
        return;
    }

    float subtotal = 0;
    for (int i = 0; i < jumlahKeranjang; i++)
        subtotal += keranjang[i].item.harga * keranjang[i].qty;

    int disc = (rand() % 8) + 3;
    float pot = subtotal * disc / 100.0;
    float after = subtotal - pot;
    float ppn = after * 0.10;
    float grand = after + ppn;

    int pilihMetode = 0;
    float bayar = 0;

    while (1) {
        system("cls");
        printf("=====================================\n");
        printf("PEMBAYARAN\n");
        printf("Subtotal: %.0f\n", subtotal);
        printf("Diskon %d%%: %.0f\n", disc, pot);
        printf("PPN 10%%: %.0f\n", ppn);
        printf("TOTAL: %.0f\n", grand);
        printf("-------------------------------------\n");
        printf("1. QRIS\n2. CASH\n3. TRANSFER\n4. Batal\n");
        printf("Pilih: ");
        scanf("%d", &pilihMetode);
        clear_input_buffer();

        if (pilihMetode == 4) return;
        if (pilihMetode < 1 || pilihMetode > 3) continue;

        if (pilihMetode == 2) {
            printf("Nominal bayar: ");
            scanf("%f", &bayar);
            clear_input_buffer();
            if (bayar < grand) continue;
        } else {
            bayar = grand;
        }

        float kembali = bayar - grand;

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        char waktu[64];
        snprintf(waktu, sizeof(waktu),
                 "%04d-%02d-%02d %02d:%02d:%02d",
                 tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday,
                 tm.tm_hour, tm.tm_min, tm.tm_sec);

        const char *alamat = random_address();

        char metode[20];
        if (pilihMetode == 1) strcpy(metode, "QRIS");
        else if (pilihMetode == 2) strcpy(metode, "CASH");
        else strcpy(metode, "TRANSFER");

        system("cls");
        printf("=====================================\n");
        printf("STRUK PEMBELIAN\n");
        printf("=====================================\n");
        printf("Nota ID: %d\n", notaID);
        printf("Tanggal: %s\n", waktu);
        printf("Alamat: %s\n", alamat);
        printf("-------------------------------------\n");
        for (int i = 0; i < jumlahKeranjang; i++) {
            printf("%-20s x%2d Rp %.0f\n",
                keranjang[i].item.nama,
                keranjang[i].qty,
                keranjang[i].item.harga * keranjang[i].qty);
        }
        printf("-------------------------------------\n");
        printf("Subtotal   : %.0f\n", subtotal);
        printf("Diskon     : %.0f\n", pot);
        printf("PPN 10%%    : %.0f\n", ppn);
        printf("TOTAL      : %.0f\n", grand);
        printf("Bayar      : %.0f\n", bayar);
        printf("Kembalian  : %.0f\n", kembali);
        printf("Metode     : %s\n", metode);
        printf("=====================================\n\n");


        // BUAT FILE NOTA DI FOLDER RIWAYAT
        ensure_riwayat_folder(); // pastikan folder ada
        char nota_path[260];
        snprintf(nota_path, sizeof(nota_path), "C:\\kasir meong\\riwayat\\nota_%d.txt", notaID);
        FILE *f = fopen(nota_path, "w");
        if (f) {
            fprintf(f, "=====================================\n");
            fprintf(f, "Nota ID: %d\n", notaID);
            fprintf(f, "Tanggal: %s\n", waktu);
            fprintf(f, "Alamat: %s\n", alamat);
            fprintf(f, "-------------------------------------\n");
            for (int i = 0; i < jumlahKeranjang; i++) {
                fprintf(f, "%-20s x%2d Rp %.0f\n",
                        keranjang[i].item.nama,
                        keranjang[i].qty,
                        keranjang[i].item.harga * keranjang[i].qty);
            }
            fprintf(f, "Subtotal: %.0f\n", subtotal);
            fprintf(f, "Diskon: %.0f\n", pot);
            fprintf(f, "PPN: %.0f\n", ppn);
            fprintf(f, "TOTAL: %.0f\n", grand);
            fprintf(f, "Bayar: %.0f\n", bayar);
            fprintf(f, "Kembalian: %.0f\n", kembali);
            fprintf(f, "Metode: %s\n", metode);
            fprintf(f, "=====================================\n\n");
            fclose(f);
        } else {
            printf("Gagal menulis nota ke %s\n", nota_path);
        }

        // JUGA APPEND KE riwayat_struk.txt (opsional, untuk log gabungan)
        FILE *f2 = fopen("riwayat_struk.txt", "a");
        if (f2) {
            fprintf(f2, "=====================================\n");
            fprintf(f2, "Nota ID: %d\n", notaID);
            fprintf(f2, "Tanggal: %s\n", waktu);
            fprintf(f2, "Alamat: %s\n", alamat);
            fprintf(f2, "-------------------------------------\n");
            for (int i = 0; i < jumlahKeranjang; i++) {
                fprintf(f2, "%-20s x%2d Rp %.0f\n",
                        keranjang[i].item.nama,
                        keranjang[i].qty,
                        keranjang[i].item.harga * keranjang[i].qty);
            }
            fprintf(f2, "Subtotal: %.0f\n", subtotal);
            fprintf(f2, "Diskon: %.0f\n", pot);
            fprintf(f2, "PPN: %.0f\n", ppn);
            fprintf(f2, "TOTAL: %.0f\n", grand);
            fprintf(f2, "Bayar: %.0f\n", bayar);
            fprintf(f2, "Kembalian: %.0f\n", kembali);
            fprintf(f2, "Metode: %s\n", metode);
            fprintf(f2, "=====================================\n\n");
            fclose(f2);
        }

        printf("Struk tersimpan!\nTekan Enter...");
        getchar();

        // PANGGIL PYTHON UNTUK GENERATE PDF OTOMATIS
        // Pastikan printpdf.py berada di C:\kasir meong\printpdf.py
            system("python \E:\project 2025\TAR.DDP\DOSEN");

        jumlahKeranjang = 0;
        totalBelanja = 0;
        notaID++;

        return;
    }
}

void lihatKeranjangbayar() {
    int pilih;

    while (1) {
        system("cls");
        if (jumlahKeranjang == 0) {
            printf("Keranjang kosong!\n");
            printf("Tekan Enter...");
            getchar();
            return;
        }

        printf("=====================================\n");
        printf("KERANJANG ANDA\n");
        printf("=====================================\n");
        for (int i = 0; i < jumlahKeranjang; i++) {
            printf("%d. %-20s x%d Rp %.0f\n",
                   i+1,
                   keranjang[i].item.nama,
                   keranjang[i].qty,
                   keranjang[i].item.harga * keranjang[i].qty);
        }
        printf("-------------------------------------\n");
        printf("Total: %.0f\n\n", totalBelanja);

        printf("1. BAYAR\n2. HAPUS / KURANGI PRODUK\n3. KEMBALI\n");
        printf("Pilih: ");
        scanf("%d", &pilih);
        clear_input_buffer();

        if (pilih == 1) pembayaran();
        else if (pilih == 2) {
            hapusDariKeranjang_menu();
        } else return;
    }
}

void lihatRiwayatFile() {
    system("cls");
    FILE *file = fopen("riwayat_struk.txt", "r");
    if (!file) {
        printf("Belum ada riwayat.\nTekan Enter...");
        getchar();
        return;
    }

    char baris[512];
    printf("===== RIWAYAT STRUK =====\n\n");
    while (fgets(baris, sizeof(baris), file))
        printf("%s", baris);

    fclose(file);
    printf("\nTekan Enter...");
    getchar();
}

void menuKasir() {
    int pilih;

    while (1) {
        system("cls");
        printf("=======================================\n");
        printf("||      MENU KASIR - TOKO MEONG      ||\n");
        printf("=======================================\n");
        printf("|| 1. Lihat Produk                   ||\n");
        printf("|| 2. Edit Produk                    ||\n");
        printf("|| 3. Tambah Produk ke Keranjang     ||\n");
        printf("|| 4. Lihat Keranjang & Bayar        ||\n");
        printf("|| 5. Lihat Riwayat File             ||\n");    
        printf("|| 6. Logout                         ||\n");
        printf("=======================================\n");
        printf("Pilih menu: ");

        scanf("%d", &pilih);
        clear_input_buffer();

        if (pilih == 1) tampilkanProduk();
        else if (pilih == 2) editProduk();
        else if (pilih == 3) tambahkeranjang();
        else if (pilih == 4) lihatKeranjangbayar();
        else if (pilih == 5) lihatRiwayatFile();
        else if (pilih == 6) {
            keluar_program("");
            getchar();
            return;
        }
    }
}

int main() {
    srand(time(NULL));
    updateScreenSize();

    loadingawal_tengah("LOADING PROGRAM");

    int pilih;

    while (1) {
        menu1();
        scanf("%d", &pilih);
        clear_input_buffer();

        if (pilih == 1) {
            if (loginmasuk())
                menuKasir();
        }
        else if (pilih == 2) {
            keluar_program("");
            break;
        }
        else if (pilih == 3) {
            author();
            getchar();
        }
        else {
            printf("Pilihan salah!\n");
            Sleep(200);
        }
    }

    return 0;
}
