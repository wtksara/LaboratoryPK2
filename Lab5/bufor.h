#pragma once
#ifndef BUFOR
#define BUFOR

#include <stdlib.h>
#include <stdio.h>

struct MaszynaStanow {
    enum Stan aktualnystan;
    char znak;
};

enum Stan
{
    otwarta,
    zamknieta,
};

struct BuforCykliczny
{
    unsigned int rozmiar;       // Rozmiar
    int dlugoscw;                // Dlugosc pisanie
    int dlugoscc;                // Dlugosc czytanie
    int pozycja_czytaj;                // pozycja do czytania
    int pozycja_pisz;               // pozycja do pisania
    struct MaszynaStanow* data; // Data
};

// Utworz bufor cykliczny
struct BuforCykliczny nowy (unsigned int rozmiar);

// Wpisywanie wartosci do buffora
void pisz(struct BuforCykliczny* bufor, struct MaszynaStanow stan);

// Czytanie wartosci z bufora
struct MaszynaStanow czytaj(struct BuforCykliczny* bufor);

// Zwolnij pamiec
void zwolnij(struct BuforCykliczny* bufor);


#endif