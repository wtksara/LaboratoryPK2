#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define plik "przyklad.html"

// Wyszukane zosta³y :
// MMXVIII
// CCCVIII
// DXLVIII
// XXXVIII

int sprawdz(char ch)
{
    if ((ch == 'I') || (ch == 'V') || (ch == 'X') || (ch == 'L') || (ch == 'C') || (ch == 'D') || (ch == 'M')) {
        return 1;
    }
    else {
        return 0;
    }
}

int lancuch(FILE* f)
{
    // Schemat XXX V XXX 
    // X - dowolny rzymski zak
    int c;
    for (int i = 0; i < 3; i++)
    {
        c = getc(f);
        if ((c == EOF) || (!sprawdz(c))) {
            return 0;
        }
    }

    c = getc(f);
    if ((c == EOF) || (tolower(c) != 'v')) {
        return 0;
    }

    for (int i = 0; i < 3; i++)
    {
        c = getc(f);
        if ((c == EOF) || (!sprawdz(c))) {
            return 0;
        }
    }

    return 1;
}

void wyswietl(FILE* f)
{
    for (int i = 0; i < 7; i++) {
        putchar(getc(f));
    }
    printf("\n");
}

int main()
{
    FILE* plikhtml = fopen(plik, "r");
    if (!plikhtml)
    {
        printf("Nie mozna otworzyc pliku. ");
        return 0;
    }

    int i = 1;
    fpos_t pozycja;
    int ilosc = 1;
    int c;

    while (i)
    {
        fgetpos(plikhtml, &pozycja);
        if (lancuch(plikhtml))
        {
            fsetpos(plikhtml, &pozycja);
            wyswietl(plikhtml);
        }
        else {
            fsetpos(plikhtml, &pozycja);
        }
        c = getc(plikhtml);
        if (c == EOF)
            i = 0;
        else if (c == '\n')
            ilosc++;
    }

    fclose(plikhtml);
    return 0;
}
