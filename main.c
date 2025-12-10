#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "function.h"
#include "login.h"

int main(void)
{
    startupSequence();
    char nama[50], pass[50];
    system("chcp 65001 > nul"); //ini buat baca UFT-8

    login(nama, pass);
    if (nama[0] != '\0' && pass[0] != '\0')
    {
        supadm(nama);

    }

    printf("\x1b[0m");
    getchar();
    return 0;
}