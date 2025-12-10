#ifndef EATBOX_LOGIN_H
#define EATBOX_LOGIN_H
#include <math.h>

#include "function.h"
void login(char nama[50], char pass[50])
{
    appname(43, 2);
    garisx(10);
    garisy(5);
    garisy(consoleW()-5);
    gotoxy(65, 15);
    printf("");
    logname(55, 13);

    for (int x = 41 ; x < 95; x++)
    {
        gotoxy(x, 20);
        printf("-");
        gotoxy(x, 30);
        printf("-");
    }
    gotoxy(40,20); printf("┌");
    gotoxy(95,20); printf("┐");

    for (int y = 21; y < 30; y++)
    {
        gotoxy(40, y);printf("|");
        gotoxy(95, y);printf("|");
    }
    gotoxy(40, 30); printf("└");
    gotoxy(95, 30); printf("┘");

    while (1){
        gotoxy(42, 19);
        printf("[ESC] Keluar");
        gotoxy(56, 19);
        printf("[TAB] Lihat/Sembunyikan");
        gotoxy(81, 19);
        printf("[ENTER] Masuk");

        clearinput(41, 21, 50);
        clearinput(41, 22, 50);
        clearinput(41, 23, 50);

        gotoxy(42, 21); printf("Nama Pengguna\t: ");
        gotoxy(42, 22); printf("Kata Sandi\t: ");

        gotoxy(58, 21); fflush(stdin); inputtext(nama);
        gotoxy(58, 22); fflush(stdin); inputpass(pass);

        if (strcmp(nama, "superadmin") == 0 && strcmp(pass, "superadmin") == 0)
        {break;}

        gotoxy(62, 27);
        printf("Login gagal!\n");
    }
}

#endif //EATBOX_LOGIN_H