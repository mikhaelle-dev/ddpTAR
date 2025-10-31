#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>

// Fungsi loading awal
void loadingawal() {
    system("cls");
    system("color 0a");
    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t ==========================================\n");
    printf("\t\t\t\t\t\t\t\t\t\t ||        LOADING TOKO MEONG...         ||\n");
    printf("\t\t\t\t\t\t\t\t\t\t ||                                      ||\n");

    for (int i = 0; i <= 50; i++) {
        printf("\r\t\t\t\t\t\t\t\t\t\t ||          LOADING : %d%%              ||", i * 2);
        fflush(stdout);
        Sleep(40);
    }

    printf("\n\t\t\t\t\t\t\t\t\t\t ||                                      ||");
    printf("\n\t\t\t\t\t\t\t\t\t\t ||                SELESAI               ||");
    printf("\n\t\t\t\t\t\t\t\t\t\t ||  Silahkan tekan Enter untuk lanjut   ||");
    printf("\n\t\t\t\t\t\t\t\t\t\t ==========================================\n");
    while (getchar() != '\n'); // tunggu Enter
}

// Fungsi tampilan menu utama
void menu1() {
    system("cls");

    for (int i = 0; i <= 50; i++) {
        printf("\r\t\t\t\t\t\t\t\t\t\t                 LOADING : %d%%              ", i * 2);
        fflush(stdout);
        Sleep(10);
    }

    printf("\n\n\n ==========================================\n");
    printf(" ||                  MENU LOGIN          ||\n");
    printf(" ||                                      ||\n");
    printf(" || 1. LOGIN                             ||\n");
    printf(" || 2. KELUAR                            ||\n");
    printf(" ||                                      ||\n");
    printf(" ==========================================\n");
    printf(" PILIH : ");
}

// Fungsi login
int loginmasuk() {
    char user[50], pass[50];

    system("cls");
    printf("\n\n ==========================================\n");
    printf(" ||              LOGIN AKUN             ||\n");
    printf(" ==========================================\n");

    printf(" USERNAME : ");
    fgets(user, sizeof(user), stdin);
    user[strcspn(user, "\n")] = 0; // hapus newline

    printf(" PASSWORD : ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = 0; // hapus newline

    // Perbandingan username dan password
    if (strcmp(user, "admin") == 0 && strcmp(pass, "123") == 0) {
        printf("\n LOGIN BERHASIL! Tekan Enter untuk lanjut...");
        getchar();
        return 1; // berhasil
    } else {
        printf("\n LOGIN GAGAL! Tekan Enter untuk ulang...");
        getchar();
        return 0; // gagal
    }
}

int main() {
    int pilih;
    loadingawal();

    while (1) {
        menu1();
        scanf("%d", &pilih);
        getchar(); // hapus enter sisa dari scanf

        if (pilih == 1) {
            if (loginmasuk()) {
                printf("\nSelamat datang di sistem kasir Toko Meong!\n");
                printf("Tekan Enter untuk kembali ke menu utama...");
                getchar();
            }
        } else if (pilih == 2) {
            printf("\nKeluar dari program...\n");
            Sleep(1000);
            break;
        } else {
            printf("\nPilihan tidak valid! Tekan Enter untuk ulang...");
            getchar();
        }
    }

    return 0;
}
