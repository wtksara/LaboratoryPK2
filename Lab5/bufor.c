#include "bufor.h"

struct BuforCykliczny nowy(unsigned int rozmiar)
{
    struct BuforCykliczny buffer = { rozmiar, 0,0, 0, 0, malloc(sizeof(struct MaszynaStanow) * rozmiar) };
    return buffer;
}

void pisz (struct BuforCykliczny* bufor, struct MaszynaStanow stan)
{
    if (bufor->dlugoscw >= bufor->rozmiar)
    {
        printf("Buffor przepelniony\n");
        return;
    }
    bufor->data[bufor->pozycja_pisz] = stan;
    bufor->pozycja_pisz++;
    bufor->pozycja_pisz = bufor->pozycja_pisz % bufor->rozmiar;
    bufor->dlugoscw++;
}

struct MaszynaStanow czytaj (struct BuforCykliczny* bufor)
{
    if (bufor->dlugoscw==0)
    {
        printf("Buffor jest pusty\n");
        struct MaszynaStanow pusty = { zamknieta, '\0' };
        return pusty;
    }
  
    int pozycja = bufor->pozycja_czytaj;
    bufor->pozycja_czytaj++;
    bufor->pozycja_czytaj = bufor->pozycja_czytaj % bufor->rozmiar;
    bufor->dlugoscc--;
    return bufor->data[pozycja];
}

void zwolnij( struct BuforCykliczny* bufor)
{
    free(bufor->data);
}

