#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "data.h"
#include "function.h"

#define MAX_MENU 100
#define FILENAME "../FILE/menu.dat"
#define ITEMS_PER_PAGE 10

Menu daftarMenu[MAX_MENU];
int jumlahMenu = 0;
int currentPage = 1;

// DECLARATION
void loadMenu();
void saveMenu();
void tambahMenu();
void lihatMenu();
void ubahMenu();
void hapusMenu();
void tampilMenuUtama();
void generateID(char *id);
int cariMenuByID(char *id);
void tampilkanTabel(int page);
void cariMenu();

int main() {
    system("cls");
    system("chcp 65001 > nul");

    startupSequence();
    loadMenu();
    int pilih;

    do {
        system("cls");
        tampilMenuUtama();
        printf("\nPilih menu (1-6): ");

        if (scanf("%d", &pilih) != 1) {
            while (getchar() != '\n');
            printf("\nInput tidak valid! Tekan Enter...");
            getch();
            continue;
        }
        while (getchar() != '\n');

        switch (pilih) {
            case 1:
                tambahMenu();
                break;
            case 2:
                lihatMenu();
                break;
            case 3:
                ubahMenu();
                break;
            case 4:
                hapusMenu();
                break;
            case 5:
                cariMenu();
                break;
            case 6:
                printf("\n=== Terima kasih ===\n");
                saveMenu();
                break;
            default:
                printf("\nPilihan tidak sesuai! Tekan Enter untuk kembali...");
                getch();
        }
    } while (pilih != 6);

    return 0;
}

void tampilMenuUtama() {
    applyColors();
    printf("\n");
    printf("|========================================|\n");
    printf("|               EAT BOX                  |\n");
    printf("|========================================|\n");
    printf("|  1. Tambah Menu Baru                   |\n");
    printf("|  2. Lihat Semua Menu                   |\n");
    printf("|  3. Ubah Menu                          |\n");
    printf("|  4. Hapus Menu                         |\n");
    printf("|  5. Cari Menu                          |\n");
    printf("|  6. Keluar                             |\n");
    printf("|========================================|\n");
}

void loadMenu() {
    FILE *file = fopen(FILENAME, "rb");

    if (file == NULL) {
        printf("\nBelum terdia, membuat file baru.\n");
        return;
    }

    jumlahMenu = 0;
    char buffer[512];

    while (fgets(buffer, sizeof(buffer), file)) {
        if (sscanf(buffer, "%9[^|]|%19[^|]|%99[^|]|%lf|%199[^|]|%19[^\n]",
                   daftarMenu[jumlahMenu].id_menu,
                   daftarMenu[jumlahMenu].kategori,
                   daftarMenu[jumlahMenu].nama_menu,
                   &daftarMenu[jumlahMenu].harga,
                   daftarMenu[jumlahMenu].deskripsi,
                   daftarMenu[jumlahMenu].status) == 6)
        {
            jumlahMenu++;
            if (jumlahMenu >= MAX_MENU) break;
        }
    }

    fclose(file);
    printf("\n[OK] Data menu berhasil dimuat (%d item)\n", jumlahMenu);
}

void saveMenu() {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("\n[ERROR] Gagal menyimpan data!\n");
        return;
    }

    for (int i = 0; i < jumlahMenu; i++) {
        fprintf(file, "%s|%s|%s|%.2lf|%s|%s\n",
                daftarMenu[i].id_menu,
                daftarMenu[i].kategori,
                daftarMenu[i].nama_menu,
                daftarMenu[i].harga,
                daftarMenu[i].deskripsi,
                daftarMenu[i].status);
    }

    fclose(file);
}

void generateID(char *id) {
    int maxNum = 0;
    for (int i = 0; i < jumlahMenu; i++) {
        int num;
        if (sscanf(daftarMenu[i].id_menu, "MN%d", &num) == 1) {
            if (num > maxNum) maxNum = num;
        }
    }
    sprintf(id, "MN%03d", maxNum + 1);
}

int cariMenuByID(char *id) {
    for (int i = 0; i < jumlahMenu; i++) {
        if (strcmp(daftarMenu[i].id_menu, id) == 0) {
            return i;
        }
    }
    return -1;
}

void tambahMenu() {
    system("cls");
    applyColors();

    Menu m;
    int pointer = 0;   // indeks input yang aktif
    int maxField = 5;  // kategori, nama, harga, deskripsi, status

    strcpy(m.kategori, "");
    strcpy(m.nama_menu, "");
    m.harga = 0;
    strcpy(m.deskripsi, "");
    strcpy(m.status, "");

    generateID(m.id_menu);

    while (1) {
        system("cls");

        //posisi header
        printf("\033[41m\033[93m");  // background merah, teks kuning
        printf("\n\n                 EATBOX - INPUT MENU BARU\n\n");
        printf("\033[0m");

        //form
        printf("\033[41m"); // background merah
        printf("  ---------------------------------------------------------  \n");
        printf("     ID Menu      : %s\n", m.id_menu);
        printf("     Kategori     : %s\n", m.kategori);
        printf("     Nama Menu    : %s\n", m.nama_menu);
        printf("     Harga        : %.0lf\n", m.harga);
        printf("     Deskripsi    : %s\n", m.deskripsi);
        printf("     Status       : %s\n", m.status);
        printf("  ---------------------------------------------------------  \n\n");
        printf("\033[0m");

        //sidebar
        char *field[] = {
            "Kategori",
            "Nama Menu",
            "Harga",
            "Deskripsi",
            "Status",
            "Simpan",
            "Batal"
        };

        printf("\033[41m\033[93m");
        printf("   [↑↓] Pilih Input   [ENTER] Edit / Lanjut\n\n");
        printf("\033[0m");

        for (int i = 0; i < 7; i++) {
            if (i == pointer) {
                setRGBColor(202, 40, 44, 0);
                setRGBColor(251, 255, 199, 1);
                printf("   \033[93m> %s\033[0m\n", field[i]);
            }
            else {
                setRGBColor(202, 40, 44, 1);
                setRGBColor(251, 255, 199, 0);
                printf("     %s\n", field[i]);
            }
        }

        //untuk memulai
        char tombol = getch();

        if (tombol == 72) {  // UP
            pointer--;
            if (pointer < 0) pointer = 6;
        }
        else if (tombol == 80) { // DOWN
            pointer++;
            if (pointer > 6) pointer = 0;
        }
        else if (tombol == 13) { // ENTER
            system("cls");

            switch (pointer) {

            case 0: // Kategori
                printf("Masukkan Kategori : ");
                fgets(m.kategori, sizeof(m.kategori), stdin);
                m.kategori[strcspn(m.kategori, "\n")] = 0;
                break;

            case 1: // Nama Menu
                printf("Masukkan Nama Menu : ");
                fgets(m.nama_menu, sizeof(m.nama_menu), stdin);
                m.nama_menu[strcspn(m.nama_menu, "\n")] = 0;
                break;

            case 2: // Harga
                printf("Masukkan Harga : ");
                while (scanf("%lf", &m.harga) != 1 || m.harga < 0) {
                    while (getchar() != '\n');
                    printf("Harga tidak valid! Masukkan angka: ");
                }
                while (getchar() != '\n');
                break;

            case 3: // Deskripsi
                printf("Masukkan Deskripsi : ");
                fgets(m.deskripsi, sizeof(m.deskripsi), stdin);
                m.deskripsi[strcspn(m.deskripsi, "\n")] = 0;
                break;

            case 4: // Status
                printf("Masukkan Status (Tersedia/Habis): ");
                fgets(m.status, sizeof(m.status), stdin);
                m.status[strcspn(m.status, "\n")] = 0;
                break;

            case 5: //menyimpan
                daftarMenu[jumlahMenu++] = m;
                saveMenu();
                printf("\nMenu berhasil disimpan!");
                getch();
                return;

            case 6: //batal
                printf("\nInput dibatalkan.");
                getch();
                return;
            }
        }
    }
}


void tampilkanTabel(int page) {
    applyColors();
    int maxPage = (jumlahMenu == 0) ? 1 : ((jumlahMenu - 1) / ITEMS_PER_PAGE) + 1;

    if (page > maxPage) page = maxPage;
    if (page < 1) page = 1;
    currentPage = page;

    int start = (page - 1) * ITEMS_PER_PAGE;
    int end = start + ITEMS_PER_PAGE;
    if (end > jumlahMenu) end = jumlahMenu;

    printf("\n");
    printf("\n|======|==================|========================|==========|=========================|============|\n");
    printf("\n| %-4s | %-16s | %-22s | %-8s | %-23s | %-10s |\n",
           "ID", "Kategori", "Nama Menu", "Harga", "Deskripsi", "Status");
    printf("\n|======|==================|========================|==========|=========================|============|\n");

    for (int i = start; i < end; i++) {
        char desc_short[24];
        if (strlen(daftarMenu[i].deskripsi) > 23) {
            strncpy(desc_short, daftarMenu[i].deskripsi, 20);
            desc_short[20] = '.';
            desc_short[21] = '.';
            desc_short[22] = '.';
            desc_short[23] = '\0';
        } else {
            strcpy(desc_short, daftarMenu[i].deskripsi);
        }

        printf("| %-4s | %-16s | %-22s | %8.0lf | %-23s | %-10s |\n",
               daftarMenu[i].id_menu,
               daftarMenu[i].kategori,
               daftarMenu[i].nama_menu,
               daftarMenu[i].harga,
               desc_short,
               daftarMenu[i].status);
    }

    printf("|======|==================|========================|==========|=========================|============|\n");
    printf("\nHalaman: %d / %d  (Total Menu: %d)\n", currentPage, maxPage, jumlahMenu);
}

void lihatMenu() {
    applyColors();
    if (jumlahMenu == 0) {
        system("cls");
        printf("\n[INFO] Belum ada menu yang tersedia.\n");
        printf("Tekan Enter untuk kembali...");
        getch();
        return;
    }

    int pilihan;
    int maxPage = ((jumlahMenu - 1) / ITEMS_PER_PAGE) + 1;

    do {
        system("cls");
        printf("\n|=======================================|\n");
        printf("\n|          DAFTAR MENU                  |\n");
        printf("\n|=======================================|\n");

        tampilkanTabel(currentPage);

        printf("\n[1] Halaman Sebelumnya  [2] Halaman Selanjutnya  [0] Kembali\n");
        printf("Pilihan: ");

        if (scanf("%d", &pilihan) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (pilihan == 1 && currentPage > 1) {
            currentPage--;
        } else if (pilihan == 2 && currentPage < maxPage) {
            currentPage++;
        }
    } while (pilihan != 0);

    currentPage = 1;
}

void ubahMenu() {
    system("cls");
    applyColors();
    printf("\n|=======================================|\n");
    printf("|             UBAH MENU                   |\n");
    printf("\n|=======================================|\n");

    char id[10];
    printf("\nMasukkan ID menu yang ingin diubah: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    int index = cariMenuByID(id);

    if (index == -1) {
        printf("\n[ERROR] Menu dengan ID '%s' tidak ditemukan!\n", id);
        printf("Tekan Enter untuk kembali...");
        getch();
        return;
    }

    printf("\n--- Data Saat Ini ---\n");
    printf("ID        : %s\n", daftarMenu[index].id_menu);
    printf("Kategori  : %s\n", daftarMenu[index].kategori);
    printf("Nama      : %s\n", daftarMenu[index].nama_menu);
    printf("Harga     : Rp %.2lf\n", daftarMenu[index].harga);
    printf("Deskripsi : %s\n", daftarMenu[index].deskripsi);
    printf("Status    : %s\n", daftarMenu[index].status);

    printf("\n--- Masukkan Data Baru ---\n");

    printf("Kategori Baru  : ");
    fgets(daftarMenu[index].kategori, sizeof(daftarMenu[index].kategori), stdin);
    daftarMenu[index].kategori[strcspn(daftarMenu[index].kategori, "\n")] = 0;

    printf("Nama Baru      : ");
    fgets(daftarMenu[index].nama_menu, sizeof(daftarMenu[index].nama_menu), stdin);
    daftarMenu[index].nama_menu[strcspn(daftarMenu[index].nama_menu, "\n")] = 0;

    printf("Harga Baru     : ");
    while (scanf("%lf", &daftarMenu[index].harga) != 1 || daftarMenu[index].harga < 0) {
        while (getchar() != '\n');
        printf("Input tidak valid! Masukkan harga yang benar: ");
    }
    while (getchar() != '\n');

    printf("Deskripsi Baru : ");
    fgets(daftarMenu[index].deskripsi, sizeof(daftarMenu[index].deskripsi), stdin);
    daftarMenu[index].deskripsi[strcspn(daftarMenu[index].deskripsi, "\n")] = 0;

    printf("Status Baru    : ");
    fgets(daftarMenu[index].status, sizeof(daftarMenu[index].status), stdin);
    daftarMenu[index].status[strcspn(daftarMenu[index].status, "\n")] = 0;

    saveMenu();
    printf("\nMenu berhasil diubah!\n");
    printf("Tekan Enter untuk kembali.");
    getch();
}

void hapusMenu() {
    system("cls");
    applyColors();
    printf("\n|=======================================|\n");
    printf("\n|          HAPUS MENU                   |\n");
    printf("\n|=======================================|\n");

    char id[10];
    printf("\nMasukkan ID menu yang ingin dihapus: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    int index = cariMenuByID(id);

    if (index == -1) {
        printf("\n[ERROR] Menu dengan ID '%s' tidak ditemukan!\n", id);
        printf("Tekan Enter untuk kembali...");
        getch();
        return;
    }

    printf("\n--- Data Menu ---\n");
    printf("ID        : %s\n", daftarMenu[index].id_menu);
    printf("Kategori  : %s\n", daftarMenu[index].kategori);
    printf("Nama      : %s\n", daftarMenu[index].nama_menu);
    printf("Harga     : Rp %.2lf\n", daftarMenu[index].harga);

    printf("\nApakah Anda yakin ingin menghapus menu ini? (y/n): ");
    char konfirmasi;
    scanf(" %c", &konfirmasi);
    while (getchar() != '\n');

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        for (int i = index; i < jumlahMenu - 1; i++) {
            daftarMenu[i] = daftarMenu[i + 1];
        }
        jumlahMenu--;

        saveMenu();
        printf("\n[OK] Menu berhasil dihapus!\n");
    } else {
        printf("\n[INFO] Penghapusan dibatalkan.\n");
    }

    printf("Tekan Enter untuk kembali.");
    getch();
}

void cariMenu() {
    system("cls");
    applyColors();
    printf("\n|=======================================|\n");
    printf("|           CARI MENU                   |\n");
    printf("|=======================================|\n");

    char keyword[100];
    printf("\nMasukkan nama menu : ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    printf("\n");
    printf("|======|====================|========================|==========|=========================|============|\n");
    printf("| %-4s | %-16s | %-22s | %-8s | %-23s | %-10s |\n",
           "ID", "Kategori", "Nama Menu", "Harga", "Deskripsi", "Status");
    printf("|======|====================|==========================|==========|=========================|============|\n");

    int found = 0;
    for (int i = 0; i < jumlahMenu; i++) {
        if (strstr(daftarMenu[i].nama_menu, keyword) != NULL ||
            strstr(daftarMenu[i].kategori, keyword) != NULL) {

            char desc_short[24];
            if (strlen(daftarMenu[i].deskripsi) > 23) {
                strncpy(desc_short, daftarMenu[i].deskripsi, 20);
                desc_short[20] = '.';
                desc_short[21] = '.';
                desc_short[22] = '.';
                desc_short[23] = '\0';
            } else {
                strcpy(desc_short, daftarMenu[i].deskripsi);
            }

            printf("| %-4s | %-16s | %-22s | %8.0lf | %-23s | %-10s |\n",
                   daftarMenu[i].id_menu,
                   daftarMenu[i].kategori,
                   daftarMenu[i].nama_menu,
                   daftarMenu[i].harga,
                   desc_short,
                   daftarMenu[i].status);
            found = 1;
        }
    }

    if (!found) {
        printf("| %-98s |\n", "Tidak ada menu yang ditemukan");
    }

    printf("|======|==================|========================|==========|=========================|============|\n");
    printf("\nTekan Enter untuk kembali...");
    getch();
}