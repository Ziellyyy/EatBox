#ifndef EATBOX_DATA_H
#define EATBOX_DATA_H
#include <stdint.h>

typedef char text[255];
typedef struct
{
    int tahun, bulan, hari;
    int jam, menit, detik;
}DateTime;
typedef struct {
    uint8_t R;
    uint8_t G;
    uint8_t B;
} RGBColor;

//YANG BARU
//MASTER
typedef struct
{
    char id_akun[10];
    char username[50];
    char password[35];
    char telp[15];
    char email[50];
    char role[20];
    text alamat;
    int status;
    int poin;
}Akun;

typedef struct
{
    char id_menu[10];
    char kategori[20];
    char nama_menu[100];
    double harga;
    text deskripsi;
    char status[20];
}Menu;

typedef struct
{
    char id_bahan[10];
    char nama_bahan[50];
    int stok;
    char satuan[20];
    int minimal_stok;
};

typedef struct
{
    char id_meja[10];
    int nomor_meja;
    int kapasitas;
    char status[20];
};

//TRANSAKSI
typedef struct
{
    char id_pesan[10];
    char id_akun[10];
    char id_menu[10];
    int jumlah;
    double total;
    double subtotal;
    DateTime tanggal;
};

typedef struct
{
    char id_bayar[10];
    char id_pesan[10];
    char id_akun[10];
    DateTime tanggal;
    double jumlah;
    char metode_bayar[20];
    char status[20];
}Pembayaran;
#endif //EATBOX_DATA_H