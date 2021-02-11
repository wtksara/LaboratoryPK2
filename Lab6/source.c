
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#include "znajdz.h"
#define FIZZ 3
#define BUZZ 5

void strcat_c(char* str, char c)
{
    for (; *str; str++); // note the terminating semicolon here. 
    *str++ = c;
    *str++ = 0;
}
// Wersja z podzielnoscia przez 3 lub 5
char* FizzBuzz1(int i)
{
    // Podzielne przez 15
    if (i % (BUZZ * FIZZ) == 0 && i!=0) {
        return _strdup("FizzBuzz");
    }
    // Podzielne przez 3
    else if ((i % FIZZ) == 0 && i != 0) {
        return _strdup("Fizz");
    }
    // Podzielne przez 5
    else if ((i % BUZZ) == 0&& i!=0) {
        return _strdup("Buzz");
    }
    else // Inny numer            
    {
        char* ptext = calloc(150, sizeof(char));
        sprintf(ptext, "%d", i);
        return ptext;
    }
}

// Wersja z zastepowaniem liczby 3 i 5 
char* FizzBuzz2(int i)
{
    char* ptext = calloc(150, sizeof(char));

    int number = i;
  
        char tablica[2];
        if (number > 10) {
            tablica[1] = number % 10 + '0';
            tablica[0] = ((number / 10) % 10) + '0';

            int l = 0;
            if (tablica[0] == '3') {
                strcat(ptext, "Fizz");
                l++;
            }
            else if (tablica[0] == '5') {
                strcat(ptext, "Buzz");
                l++;
            }

            if (tablica[1] == '3') {
                strcat(ptext, "Fizz");
                l++;
            }
            else if (tablica[1] == '5')
            {
                strcat(ptext, "Buzz");
                l++;
            }
            if (l==0) {
                sprintf(ptext, "%d", i);
            }

        }
        else {
            if (number == 3) {
                strcat(ptext, "Fizz");
            }
            else if (number == 5) {
                strcat(ptext, "Buzz");
            }
            else {
                sprintf(ptext, "%d", i);
            }
        }
    
    return ptext;
}

// Wersja z zastepowaniem tylko liczby 3 i 5, a pozostawianiem reszty
char* FizzBuzz3(int i)
{
    char* ptext = calloc(150, sizeof(char));

    int number = i;

    char tablica[2];
    if (number > 10) {
        tablica[1] = number % 10 + '0';
        tablica[0] = ((number / 10) % 10) + '0';

        int l = 0;
        if (tablica[0] == '3') {
            strcat(ptext, "Fizz");
        }
        else if (tablica[0] == '5') {
            strcat(ptext, "Buzz");
        }
        else {
            strcat_c(ptext, tablica[0]);
        }

        if (tablica[1] == '3') {
            strcat(ptext, "Fizz");
        }
        else if (tablica[1] == '5')
        {
            strcat(ptext, "Buzz");
        }
        else {
            strcat_c(ptext, tablica[1]);
        }

    }
    else {
        if (number == 3) {
            strcat(ptext, "Fizz");
        }
        else if (number == 5) {
            strcat(ptext, "Buzz");
        }
        else {
            sprintf(ptext, "%d", i);
        }
    }

    return ptext;
}


int main(int argc, char* argv[])
{
  
    if (argc < 2)
    {
        printf("MUSISZ PODAC TEKST\n\n");
        printf("PRZYKLAD: ./lab6 \"tekst\" plikwyjsciowy.txt\n");
        return 0;
    }
    char* plik_wyjsciowy = _strdup(argv[2]);

    FILE* output = fopen(plik_wyjsciowy, "w");

    if (!output)
    {
        printf("NIE MOZNA BYLO OTWORZYC PLIKU %s\n", plik_wyjsciowy);
        free(plik_wyjsciowy);
        return 0;
    }
  
    struct elementlisty** glowa = nowa();
    zapisz(glowa, argv[1]);
   
    fprintf(output, "ASCII_kod,Znak,Ilosc wystawien,Minimalny dystans,Maksymalny dystans\n");
    
    for (int i = 35; i < 122; i++)
    {
        char znak = dostanznak(i);
        int ilosc = ilepowtorzen(glowa, znak);
        fprintf(output, "%d,'%c',%d,", i, znak, ilosc);

        if (ilosc > 1)
            fprintf(output, "%d,%d\n", mindystans(glowa, znak), maxdystans(glowa, znak));

        else
            fprintf(output, ",\n");
    }
  
    printf("Zwalnianie pamieci\n");
    free(plik_wyjsciowy);
    wyczysc(glowa);
    fprintf(output, "\n\n ZADANIE 2 \n\n\n");

    setbuf(stdout, NULL);

    char* (*funkcje[])(int) = { FizzBuzz1, FizzBuzz2, FizzBuzz3 };

    for (int i = 0; i < 3; i++)
    {
        switch (i) {
        case 0: { fprintf(output, "  I WERSJA. FIZZ BUZZ TYPOWE \n\n"); break; }
        case 1: { fprintf(output, "\n\n  II WERSJA. FIZZ BUZZ ZASTEPOWANIE LICZBY Z 3 i 5 \n\n"); break; }
        case 2: { fprintf(output, "\n\n  III WERSJA. FIZZ BUZZ ZASTEPOWANIE TYLKO LICZBY Z 3 i 5, POZOSTAWIENIEM RESZTY \n\n"); break; }
        }
        for (int j = 0; j < 100; j++) {
            char* tekst = funkcje[i](j);
            fprintf(output,"%s,", tekst);
            free(tekst);
        }
        fprintf(output, "\n\n");
    }

    fclose(output);
    
    return 0;
}
