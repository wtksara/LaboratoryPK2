#pragma once
#define BUFFER_ROZMIAR 5000
#define PLIK_WYJSCIOWY "wyniki.csv"

#define CZAS 40
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <stdio.h>
#include <time.h>
#include "bufor.h"
#include <conio.h>



void pokaz_stan(FILE* outStream, struct MaszynaStanow stan)
{
    char* stateString = NULL;

    switch (stan.aktualnystan) 
    {
    case otwarta: {
        stateString = _strdup("otwarta");
        break;
    }
    case zamknieta: {
        stateString = _strdup("zamknieta");
        break;
    }
    }

    fprintf(outStream, "\n STAN: %10s\t ", stateString);

    if (stan.znak != '\0')
        fprintf(outStream, "\tZNAK ZMIANY: %c \n", stan.znak);

    free(stateString);
}

bool zapiszdopliku(char* fileName, struct BuforCykliczny* buffer)
{
    FILE* csv = fopen(fileName, "w");

    if (!csv) {
        return false;
    }
    fprintf(csv, "STAN,ZNAK ZMIANY\n");
    buffer->dlugoscc = buffer->dlugoscw;
    for (int i = 0; i < buffer->dlugoscw; i++)
    {
       
        struct MaszynaStanow stan = czytaj(buffer);
        char znaczek = (stan.znak == '\0' ? ' ' : stan.znak);
        char* stateString = NULL;

        switch (stan.aktualnystan)
        {
        case otwarta: {
            stateString = _strdup("otwarta");
            break;
        }
        case zamknieta: {
            stateString = _strdup("zamknieta");
            break;
        }
        }
        fprintf(csv, "%s,%c\n", stateString, znaczek);

        free(stateString);
    }

    fclose(csv);
    return true;
}

int main()
{
    struct BuforCykliczny buforek = nowy(BUFFER_ROZMIAR);
    struct MaszynaStanow maszyna = { zamknieta, 0 };

    int running = 1;
    printf("\n PRZYCISKI DO OBSLUGI:\n");
    printf("\n S - STOP:\n");
    printf("\n O - OTWORZ:\n");
    printf("\n C - ZAMKNIJ:\n");

    char przycisk = '\0';
    while (1)
    {
        if (_kbhit)
            przycisk = getchar();

        switch (przycisk) {

        case 's':
        {
            maszyna.znak = przycisk;

            pisz(&buforek, maszyna);

            pokaz_stan(stdout, maszyna);

            switch (maszyna.aktualnystan)
            {
            case otwarta: maszyna.aktualnystan = zamknieta; break;
            case zamknieta: maszyna.aktualnystan = zamknieta; break;
            }
 
            break;
        }

        case 'o':
        {
            maszyna.znak = przycisk;

            pisz(&buforek, maszyna);

            pokaz_stan(stdout, maszyna);

            switch (maszyna.aktualnystan)
            {
            case otwarta: maszyna.aktualnystan = otwarta; break;
            case zamknieta: maszyna.aktualnystan = otwarta; break;
            }
           

            break;
        }
        case 'c':
        {
            maszyna.znak = przycisk;

            pisz(&buforek, maszyna);

            pokaz_stan(stdout, maszyna);

            switch (maszyna.aktualnystan)
            {
            case otwarta: maszyna.aktualnystan = zamknieta; break;
            case zamknieta: maszyna.aktualnystan = zamknieta; break;
            }

            break;
        }
        default :
        {
            printf("\n ZLY PRZYCISK:\n");
            break;
        }
        }


        
        if (przycisk == 's') {
            maszyna.znak = 'e';

            pisz(&buforek, maszyna);

            pokaz_stan(stdout, maszyna);
            break;
        }
        while ((przycisk = getchar()) != '\n' && przycisk != EOF) // Zczytywanie do koñca lini lub konca pliku
        {
        }
        
    }

        zapiszdopliku(PLIK_WYJSCIOWY, &buforek);

        zwolnij(&buforek);

        printf("\nKONIEC\n");
        return 0;
    
}

