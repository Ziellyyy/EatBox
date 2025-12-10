#ifndef EATBOX_FUNCTION_H
#define EATBOX_FUNCTION_H

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "data.h"

// FUNGSI UTILITY DASAR
void gotoxy(int x, int y)
{
    HANDLE move = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD kor = {x, y};
    SetConsoleCursorPosition(move, kor);
}
int consoleW() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
int consoleH() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
void appname(int x, int y)
{
    gotoxy(x, y  ); printf("███████╗ █████╗ ████████╗██████╗  ██████╗ ██╗  ██╗");
    gotoxy(x, y+1); printf("██╔════╝██╔══██╗╚══██╔══╝██╔══██╗██╔═══██╗╚██╗██╔╝");
    gotoxy(x, y+2); printf("█████╗  ███████║   ██║   ██████╔╝██║   ██║ ╚███╔╝ ");
    gotoxy(x, y+3); printf("██╔══╝  ██╔══██║   ██║   ██╔══██╗██║   ██║ ██╔██╗ ");
    gotoxy(x, y+4); printf("███████╗██║  ██║   ██║   ██████╔╝╚██████╔╝██╔╝ ██╗");
    gotoxy(x, y+5); printf("╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═════╝  ╚═════╝ ╚═╝  ╚═╝");
}
void logname(int x, int y)
{
    gotoxy(x, y  ); printf(" ____ ____ ____ ____ ____ ");
    gotoxy(x, y+1); printf("││M │││A │││S │││U │││K ││");
    gotoxy(x, y+2); printf("││__│││__│││__│││__│││__││");
    gotoxy(x, y+3); printf("│╱__╲│╱__╲│╱__╲│╱__╲│╱__╲│");
}

// ILANGIN SCROLL
void Borderless() {
    HWND console = GetConsoleWindow();

    LONG style = GetWindowLong(console, GWL_STYLE);
    style &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
    SetWindowLong(console, GWL_STYLE, style);

    HMONITOR monitor = MonitorFromWindow(console, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi = { sizeof(mi) };
    GetMonitorInfo(monitor, &mi);

    SetWindowPos(console, HWND_TOP,
        mi.rcMonitor.left,
        mi.rcMonitor.top,
        mi.rcMonitor.right - mi.rcMonitor.left,
        mi.rcMonitor.bottom - mi.rcMonitor.top,
        SWP_FRAMECHANGED | SWP_SHOWWINDOW);
}

// FUNGSI WARNA RGB (ANSI)
void enableANSI() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // Virtual Terminal Processing untuk kode warna ANSI/RGB
    DWORD mode = 0;
    GetConsoleMode(h, &mode);
    mode |= 0x0004; // 0x0004 = ENABLE_VIRTUAL_TERMINAL_PROCESSING
    SetConsoleMode(h, mode);
}
void setRGBColor(int r, int g, int b, int isBackground) {
    if (isBackground) {
        printf("\x1b[48;2;%d;%d;%dm", r, g, b); // warna background
    } else {
        printf("\x1b[38;2;%d;%d;%dm", r, g, b); // warna text:
    }
}
void fillScreenBG() {
    int w = consoleW();
    int h = consoleH();

    setRGBColor(202, 40, 44, 1);

    gotoxy(0, 0);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            printf(" ");
        }
    }
}
void applyColors()
{
    RGBColor red = {202, 40, 44};
    RGBColor cream = {251, 255, 199};

    setRGBColor(red.R, red.G, red.B, 1);
    setRGBColor(cream.R, cream.G, cream.B, 0);

    fillScreenBG();
    gotoxy(0,0);
}
void goFullscreen() // Alt + Enter buat Fullscreen
{
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1C, 0, 0);
    keybd_event(VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
    Sleep(150);
}
void maximizeConsole()
{
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_MAXIMIZE);
    Sleep(150);
}
void fixConsoleBuffer() {
    HWND console = GetConsoleWindow();
    HMONITOR monitor = MonitorFromWindow(console, MONITOR_DEFAULTTONEAREST);

    MONITORINFO mi = { sizeof(mi) };
    GetMonitorInfo(monitor, &mi);

    int width  = mi.rcMonitor.right  - mi.rcMonitor.left;
    int height = mi.rcMonitor.bottom - mi.rcMonitor.top;

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(hOut, (COORD){ width, height });
}

void startupSequence() {
    enableANSI();
    maximizeConsole();
    goFullscreen();
    Borderless();
    Sleep(200);
    fixConsoleBuffer();
    applyColors();
    Sleep(50);
}

//PERULANGAN GARIS DARI UJUNG KE UJUNG
void garisx(int y)
{
    HANDLE move = GetStdHandle(STD_OUTPUT_HANDLE); //akses cursor (posisi text nya)
    int width = consoleW();

    for (int x = 0; x < width; x++)
    {
        COORD kor = {x, y}; //kordinat cursornya
        SetConsoleCursorPosition(move, kor); //buat mulai posisi nya sesuai kordinat
        printf("█");
    }

    COORD reset = {0, 7};
    SetConsoleCursorPosition(move, reset);
}
void garisy(int x)
{
    HANDLE move = GetStdHandle(STD_OUTPUT_HANDLE); //akses cursor (posisi text nya)
    int height = consoleH();

    for (int y = 0; y < height; y++)
    {
        COORD kor = {x, y}; //kordinat cursornya
        SetConsoleCursorPosition(move, kor); //buat mulai posisi nya sesuai kordinat
        printf("██");
    }
}

//INPUT SAAT LOGIN
void clearinput(int x, int y, int l) // membersihkan input yang salah
{
    gotoxy(x, y);
    for (int i = 0; i < l; i++)
        printf(" ");
}
void inputpass(char pass[]) //fungsi untuk password
{
    char ch;
    int i = 0, visible = 0;

    while (1)
    {
        ch = _getch(); // buat baca input langsung dari keyboard

        if (ch == 27)exit(0);

        if (ch == 13) // baca input ketika ENTER
        {
            pass[i] = '\0'; //biar ENTER g masuk ke array
            break;
        }
        else if (ch == 9) // baca input ketika TAB (show/hide)
        {
            visible = !visible;

            gotoxy(42, 22);
            printf("Kata Sandi\t: ");
            for (int j = 0; j < i; j++)
                printf(visible ? "%c" : "*", pass[j]);
        }
        else if (ch == 8) // baca input ketika BACKSPACE
        {
            if (i > 0)
            {
                i--;
                printf("\b \b"); //fungsi untuk backspace
            }
        }
        else
        {
            pass[i++] = ch;
            printf(visible ? "%c" : "*", ch);
        }
    }
}
void inputtext(char input[])
{
    char ch;
    int i = 0;

    while (1)
    {
        ch = _getch(); // buat baca input langsung dari keyboard

        if (ch == 27)exit(0);

        if (ch == 13) // baca input ketika ENTER
        {
            input[i] = '\0'; //biar ENTER g masuk ke array
            break;
        }
        if (ch == 8 && i > 0) // baca input ketika BACKSPACE
        {
            i--;
            printf("\b \b"); //fungsi untuk backspace
        }
        else if (ch >= 32 && ch <= 126) {
            input[i++] = ch;
            printf("%c", ch);
        }
    }
}

void supadm(char nama[50])
{
    HANDLE move = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");

    SetConsoleCursorPosition(move, (COORD){7,2});
    printf("EATBOX");

    garisx(5);
    garisy(25);

    SetConsoleCursorPosition(move, (COORD){30,2});
    printf("Halo, %s", nama);

    int left = 30;
    int right = 105;
    int top = 7;
    int bot = 28;

    for (int x = left; x < right; x++)
    {
        SetConsoleCursorPosition(move, (COORD){x, top});
        printf("─");
        SetConsoleCursorPosition(move, (COORD){x, bot});
        printf("─");
    }

    for (int y = top; y < bot; y++)
    {
        SetConsoleCursorPosition(move, (COORD){left, y});
        printf("│");
        SetConsoleCursorPosition(move, (COORD){right, y});
        printf("│");
    }

    for (int y = top; y < bot-1; y++)
    {
        SetConsoleCursorPosition(move, (COORD){left+23, y+1});
        printf("│");
        SetConsoleCursorPosition(move, (COORD){left+43, y+1});
        printf("│");
        SetConsoleCursorPosition(move, (COORD){left+63, y+1});
        printf("│");
    }

    SetConsoleCursorPosition(move, (COORD){left, top}); printf("┌");
    SetConsoleCursorPosition(move, (COORD){right, top}); printf("┐");
    SetConsoleCursorPosition(move, (COORD){left, bot}); printf("└");
    SetConsoleCursorPosition(move, (COORD){right, bot}); printf("┘");

    int yhead = top + 1;

    SetConsoleCursorPosition(move, (COORD){left + 3, yhead});
    printf("Nama Admin");

    SetConsoleCursorPosition(move, (COORD){left + 25, yhead});
    printf("No. telp");

    SetConsoleCursorPosition(move, (COORD){left + 45, yhead});
    printf("Email");

    SetConsoleCursorPosition(move, (COORD){left + 65, yhead});
    printf("Status");

    for (int x = left+1; x < right; x++)
    {
        SetConsoleCursorPosition(move, (COORD){x, yhead + 1});
        printf("─");
    }

    SetConsoleCursorPosition(move, (COORD){1,10}); printf("1. Tambah Admin");
    SetConsoleCursorPosition(move, (COORD){1,11}); printf("2. Ubah Admin");
    SetConsoleCursorPosition(move, (COORD){1,12}); printf("3. Hapus Admin");
    SetConsoleCursorPosition(move, (COORD){1,13}); printf("0. Keluar");
    SetConsoleCursorPosition(move, (COORD){1,15}); printf("Masukan Pilihan Anda :");
    int n; while (n < 0 || n > 3){scanf("%d", &n);}
}

#endif //EATBOX_FUNCTION_H