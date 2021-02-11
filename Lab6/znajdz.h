#pragma once

#ifndef LISTA
#define LISTA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
// Makro
#define MIN(a, b) (a < b ? a : b)

struct elementlisty
{
    int pozycja;               // Pozycja 
    struct elementlisty* nastepny; // Nastepny element
};

// Inicjalizacja
struct elementlisty** nowa();

// Otrzymanie numeru pozycji
int znajdzpozycje(char c);

// Otrzymanie znaku
char dostanznak(unsigned char c);

// Numer wystapienia
void wystapienie(struct elementlisty** element, char c, int index);

// Zapisz string do tablicy
void zapisz(struct elementlisty** element, char* str);

// Ilosc powtorzen
int ilepowtorzen(struct elementlisty** element, char c);

// Minimalny dystans miedzy znakami
int mindystans(struct elementlisty** element, char c);

// Maksymalny dystans miedzy znakami
int maxdystans(struct elementlisty** element, char c);

// Czyszczenie pamieci
void wyczysc(struct elementlisty** element);

#endif