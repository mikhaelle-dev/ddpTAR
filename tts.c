#include <stdio.h>

#include <stdio.h>

void penjumlahan() {
    int batas, i, hasil;

    do {
        hasil = 0;
        printf("Masukkan batas : ");
        scanf("%d", &batas);

        printf("\nPenjumlahan angka dari 1 sampai %d:\n", batas);

        for (i = 1; i <= batas; i++) {
            printf("%d\n", i);
            hasil += i;
        }

        printf("_____________+\n");
        printf("Total = %d\n", hasil);

        if (hasil < 120) {
            printf("Total masih kurang dari 120 mass, ulangi lagi!\n\n");
        } else if (hasil > 120) {
            printf("Waduh kelebihan! Total = %d (lebih dari 120)\n\n", hasil);
        } else {
            printf("ASEKKKK udh pas 120!\n\n");
        }

    } while (hasil <= 120); 
}


void pyramid() {
    int i, j, k, n;
    printf("Masukkan tinggi pyramid: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        for (j = i; j < n; j++) {
            printf(" ");
        }
        for (k = 1; k <= (2 * i - 1); k++) {
            printf("*");
        }
        printf("\n");
    }
    printf("\n");
}

void datadiri() {
    printf("  NAMA : MIKHAEL RAKARENZO\n");
    printf("  NIM  : 672025048\n\n");
}

int main() {
    int pilihan;

    do {
        printf("\n=========================\n");
        printf("|          TTS          |\n");
        printf("=========================\n");
        printf("| 1. Penjumlahan        |\n");
        printf("| 2. Pyramid            |\n");
        printf("| 3. Data Diri          |\n");
        printf("| 4. Keluar             |\n");
        printf("=========================\n");
        printf("Masukkan angka menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                printf("\n======================================\n");
                printf(" === ANDA MEMASUKI MENU PENJUMLAHAN ===");
                printf("\n======================================\n");
                penjumlahan();
                break;
            case 2:
                printf("\n======================================\n");
                printf(" === ANDA MEMASUKI MENU PYRAMID ===");
                printf("\n======================================\n");
                pyramid();
                break;
            case 3:
                printf("\n======================================\n");
                printf(" === ANDA MEMASUKI MENU DATA DIRI ===");
                printf("\n======================================\n");
                datadiri();
                break;
            case 4:
                printf("\n======================================\n");
                printf(" === ANDA KELUAR DARI PROGRAM ===");
                printf("\n======================================\n");
                printf("       Terima kasih wleee!\n");
                break;
            default:
                printf("\nPilihan gak valid mas! Coba lagi.\n");
        }
    } while (pilihan != 4);

    return 0;
}
