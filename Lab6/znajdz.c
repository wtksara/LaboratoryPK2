#include "znajdz.h"

int znajdzpozycje(char c)
{
    return (int)(unsigned char)(c);
}

char dostanznak(unsigned char c)
{
    return (char)(c);
}

struct elementlisty** nowa()
{
    struct elementlisty** nowa = calloc(UCHAR_MAX + 1, sizeof(struct elementlisty*));
    return nowa;
}

void wystapienie(struct elementlisty** lista, char c, int index)
{
    struct elementlisty* nowyele = (struct elementlisty*)malloc(sizeof(struct elementlisty));
    nowyele->pozycja = index;
    nowyele->nastepny = lista[znajdzpozycje(c)];
    lista[znajdzpozycje(c)] = nowyele;
}

void zapisz(struct elementlisty** lista, char* str)
{
    for (int i = 0; i < strlen(str); i++)
        wystapienie(lista, str[i], i);
}

int ilepowtorzen(struct elementlisty** lista, char c)
{
    struct elementlisty* glowa = lista[znajdzpozycje(c)];

    int ilosc = 0;
    while (glowa)
    {
        ilosc++;
        glowa = glowa->nastepny;
    }
    return ilosc;
}

int mindystans(struct elementlisty** lista, char c)
{
    struct elementlisty* glowa = lista[znajdzpozycje(c)];

    if ((!glowa) || (!(glowa->nastepny)))
        return -1;

    int pierwszy = glowa->pozycja;
    glowa = glowa->nastepny;
    int second = glowa->pozycja;

    int min = abs(pierwszy - second);

    glowa = glowa->nastepny;
    while (glowa)
    {
        pierwszy = second;
        second = glowa->pozycja;
        min = MIN(min, abs(pierwszy - second));
        glowa = glowa->nastepny;
    }
    return min;
}

int maxdystans(struct elementlisty** element, char c)
{
    struct elementlisty* glowa = element[znajdzpozycje(c)];

    if ((!glowa) || (!(glowa->nastepny)))
        return -1;

    int first = glowa->pozycja;
    while (glowa->nastepny)
        glowa = glowa->nastepny;

    return abs(first - glowa->pozycja);
}

void wyczysc(struct elementlisty** lista)
{
    struct elementlisty* pwsk, * kwsk;

    for (int i = 0; i < UCHAR_MAX; i++)
    {
        pwsk = lista[i];

        while (pwsk)
        {
            kwsk = pwsk->nastepny;
            free(pwsk);
            pwsk = kwsk;
        }
    }
    free(lista);
}