#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <errno.h>

#define NDEBUG // Nie pojawi siê zaden komunikat o b³edach, dzieki NDEBUG
#include <assert.h>

#define BINARY "properties.dat"
#define JSON "properties.json"
#define CVS "data.csv"

typedef enum { TRUE = 1, FALSE = 0 } bool;

char month[2];   // globalne zmienne sa zerowane
void PESELdata();
void wordsort();

char PESEL[12] = { 0 };
char DATA[11] = { 0 };

int valid = 0;

int getBirthYear() {
    int year;
    int month;
    year = 10 * (PESEL[0] - '0');
    year += (PESEL[1] - '0');
    month = 10 * (PESEL[2] - '0');
    month += (PESEL[3] - '0');
    if (month > 80 && month < 93) {
        year += 1800;
    }
    else if (month > 0 && month < 13) {
        year += 1900;
    }
    else if (month > 20 && month < 33) {
        year += 2000;
    }
    else if (month > 40 && month < 53) {
        year += 2100;
    }
    else if (month > 60 && month < 73) {
        year += 2200;
    }
    return year;
}

int getBirthMonth() {
    int month;
    month = 10 * (PESEL[2] - '0');
    month += (PESEL[3] - '0');
    if (month > 80 && month < 93) {
        month -= 80;
    }
    else if (month > 20 && month < 33) {
        month -= 20;
    }
    else if (month > 40 && month < 53) {
        month -= 40;
    }
    else if (month > 60 && month < 73) {
        month -= 60;
    }
    return month;
}

int getBirthDay() {
    int day;
    day = 10 * (PESEL[4] - '0');
    day += (PESEL[5] - '0');
    return day;
}

struct info
{
    char* nazwa;
    int rodzaj;
    float min;
    float max;
};

struct info* ilekolumn(int ile, char* data[])
{
    struct info* kolumny = malloc(sizeof(struct info) * ile);
    int l = 0;

    for (int i = 0; i < ile && (!l); i++)
    {
            kolumny[i].nazwa = data[i * 4];
            kolumny[i].rodzaj = strcmp(data[i * 4 + 1], "int");

            int wartosc = 0;
            wartosc += sscanf_s(data[i * 4 + 2], "%f", &kolumny[i].min);
            wartosc += sscanf_s(data[i * 4 + 3], "%f", &kolumny[i].max);
            if (wartosc != 2) {
                l++;
            }
    }

    if (l)
    {
        printf("Nie da sie dopasowac parametrów\n");
        free(kolumny);
        kolumny = NULL;
    }

    return kolumny;
}

int zapiszBINARY(int w, int k, struct info* columns, char* file)
{
    FILE* binfile;
    errno_t err;
    err = fopen_s(&binfile, file, "w");
    if (binfile)
    {
        fwrite(&w, sizeof(int), 1, binfile);
        fwrite(&k, sizeof(int), 1, binfile);
        fwrite(columns, sizeof(struct info), k, binfile);
        for (int i = 0; i < k; i++)
        {
            int dlugosc = strlen(columns[i].nazwa);
            fwrite(&dlugosc, sizeof(int), 1, binfile);
            fwrite(columns[i].nazwa, sizeof(char), dlugosc, binfile);
        }
        fclose(binfile);
    }
    else {
        return 1;
    }
    return 0;
}

int zapiszJSON(int w, int k, struct info* columns, char* file)
{
    FILE* JSONfile;
    errno_t err;
    err = fopen_s(&JSONfile, file, "w");
    if (JSONfile)
    {
        bool option;
        fprintf(JSONfile, "{\n\t\"ILOSC KOLUMN\": %d,\n", k);
        fprintf(JSONfile, "\t\"ILOSC WIERSZY\": %d,\n", w);
        fprintf(JSONfile, "\t\"ZAWARTOSC KOLUMN\": [\n");

        for (int i = 0; i < k; i++)
        {
            fprintf(JSONfile, "\t\t{\n");
            fprintf(JSONfile, "\t\t\t\"NAZWA\": \"%s\",\n", columns[i].nazwa);
            fprintf(JSONfile, "\t\t\t\"FLOAT\": %s,\n", (columns[i].rodzaj == 0 ? "false" : "true"));
            fprintf(JSONfile, "\t\t\t\"MINIMUM\": %f,\n", columns[i].min);
            fprintf(JSONfile, "\t\t\t\"MAKSIUMUM\": %f\n", columns[i].max);
            fprintf(JSONfile, "\t\t}");

            if (i < k - 1)
                fprintf(JSONfile, ",");

            fprintf(JSONfile, "\n");
        }

        fprintf(JSONfile, "\t]\n}");
        fclose(JSONfile);
    }
    else {
        return 1;
    }
    return 0;
}

int zapiszCVS(int w, int k, struct info* columns, char* file)
{
    FILE* csv;
    errno_t err;
    err = fopen_s(&csv, file, "w");
    if (!csv) {
        return 1;
    }

    fprintf(csv, "%s", columns[0].nazwa);
    for (int i = 1; i < k; i++) {
        fprintf(csv, ",%s", columns[i].nazwa);
    }
    fprintf(csv, "\n");

    srand(time(NULL));

    for (int wiersz = 0; wiersz < w; wiersz++)
    {
        for (int kolumna = 0; kolumna < k; kolumna++)
        {
            float roznica = columns[kolumna].max - columns[kolumna].min;
            double wartosc = columns[kolumna].min + (double)(rand() % (int)roznica);
            if (columns[kolumna].rodzaj)
            {
                fprintf(csv, "%lf", wartosc);
            }
            else
            {
                int ile = (int)(wartosc);
                fprintf(csv, "%d", ile);
            }
            if (kolumna != k - 1)
                fprintf(csv, ",");
        }
        fprintf(csv, "\n");
    }

    fclose(csv);
    return 0;
}

int main(int argc, char* argv[])
{
    //ZADANIE 1
    //PESELdata(); // Sprawdzenie daty urodzenia z peselu
    //wordsort();

    //ZADANIE 2

    if (argc == 1)
    {
        printf(" Otrzymalam %d argumentow\n", argc - 1);
        printf(" Masz zadeklarowac 4 argumenty:\n");
        printf(" 1. Nazwa \n 2. Typ int lub float \n 3. Minimalna wartosc \n 4. Maksymalna wartosc\n");
        printf(" Oraz okreslic rozmiar pliku cvs \n\n");
        return 0;
    }

    int w = 0;
    sscanf_s(argc[argv - 1], "%d", &w);
    if (w <= 0)
    {
        printf("Ilosc wierszy nie moze byc mniejsza lub rowna zeru \n");
        return 0;
    }

    int k = (argc - 2) / 4;
    struct info* kolumny = ilekolumn(k, argv + 1);

    if (kolumny == NULL) {
        return 0;
    }

    if (!zapiszBINARY(w, k, kolumny, BINARY)) {
        printf("Zapisano poprawnie plik binarny \n");
    }
    else {
        printf("Nie udalo sie zapisac poprawnie pliku binarnego \n");
    }

    if (!zapiszJSON(w, k, kolumny, JSON)) {
        printf("Zapisano poprawnie plik json \n");
    }
    else {
        printf("Nie udalo sie zapisac poprawnie pliku json \n");
    }

    if (!zapiszCVS(w, k, kolumny, CVS)) {
        printf("Zapisano poprawnie plik cvs \n");
    }
    else {
        printf("Nie udalo sie zapisac poprawnie pliku cvs \n");
    }

    free(kolumny);
    return 0;
}

void PESELdata()
{
    int checking = 0;
    while (checking != 1) {
        // Funkcja, która sprawdza czy ciag to liczba
        char PESELP[12] = { 0 };
        fputs("Podaj PESEL: ", stdout);
        gets(PESELP);
        int check = 0;

        check = check + (PESELP[0] - '0') * 9;
        check = check + (PESELP[1] - '0') * 7;
        check = check + (PESELP[2] - '0') * 3;
        check = check + (PESELP[3] - '0') * 1;
        check = check + (PESELP[4] - '0') * 9;
        check = check + (PESELP[5] - '0') * 7;
        check = check + (PESELP[6] - '0') * 3;
        check = check + (PESELP[7] - '0') * 1;
        check = check + (PESELP[8] - '0') * 9;
        check = check + (PESELP[9] - '0') * 7;
        check = check % 10;
        int k = 1;
        int number = (PESELP[10] - '0');
        /* assert (check != number); {
            printf("Nie poprawny numer pesel \n");
            k = 0;
        }*/
        int p = 0;
        for (int i = 0; i < sizeof(PESELP); i++) {
            if (!isdigit(PESELP[i]))
            {
                printf("Pesel sklada sie tylko z cyfr \n");
            }
            else {
                p++;
            }
        }

        if ((p == 11) && (k == 1)) {
            checking = 1;
            strncpy_s(PESEL, sizeof(PESELP), PESELP, sizeof(PESELP));
        }
    }
    printf("\n PODANY PRZEZ CIEBIE PESEL TO : ");

    puts(PESEL);
    printf("\n");
    int year = getBirthYear();
    int month = getBirthMonth();
    int day = getBirthDay();

    int l1 = snprintf(NULL, 0, "%d", year);
    int l2 = snprintf(NULL, 0, "%d", month);
    int l3 = snprintf(NULL, 0, "%d", day);
    char* cyear = malloc(l1 + 1);
    char* cmonth = malloc(l2 + 1);
    char* cday = malloc(l3 + 1);

    snprintf(cyear, l1 + 1, "%d", year);
    snprintf(cmonth, l2 + 1, "%d", month);
    snprintf(cday, l3 + 1, "%d", day);

    if (day < 10) {
        memmove(DATA + 1, DATA + 0, 1);
        memset(DATA + 0, '0', 1);
    }
    strcat_s(DATA, sizeof(DATA) + 1, cday);
    if (month < 10) {
        memmove(DATA + 3, DATA + 2, 1);
        memset(DATA + 2, '0', 1);
    }
    strcat_s(DATA, sizeof(DATA) + 1, cmonth);
    strcat_s(DATA, sizeof(DATA) + 1, cyear);

    free(cyear);
    cyear = NULL;
    free(cmonth);
    cmonth = NULL;
    free(cday);
    cday = NULL;

    FILE* pFile;
    errno_t err = fopen_s(&pFile, "plik.txt", "a");
    fputs(DATA, pFile);
    fclose(pFile);

    puts(DATA);

}

void wordsort()
{
    //Uporz¹dkowaæ  s³owa  po liczbie  wyst¹pieñ  danej litery
    fputs("\n\n Podaj 3 slowa: \n", stdout);
    char str[30];
    char str1[30];
    char str2[30];

    gets(str);
    gets(str1);
    gets(str2);
    char* cstr = _strdup(str);
    char* cstr1 = _strdup(str1);
    char* cstr2 = _strdup(str2);
    fputs("Chcesz wyszukac \n 1.Znak 'c' \n 2.Napis 'ch' \n", stdout);
    int choice = 1;
    scanf_s("%d", &choice);
    int ilosc = 0;
    int ilosc1 = 0;
    int ilosc2 = 0;

    if (choice == 1) {
        const char ch = 'c';
        char* ret;
        while (ret = strchr(str, ch)) {
            ilosc++;
            memcpy(ret + 0, ret + 1, sizeof(ret) + 1);
        }
        while (ret = strchr(str1, ch)) {
            ilosc1++;
            memcpy(ret + 0, ret + 1, sizeof(ret) + 1);
        }
        while (ret = strchr(str2, ch)) {
            ilosc2++;
            memcpy(ret + 0, ret + 1, sizeof(ret) + 1);
        }
    }
    if (choice == 2) {
        char ch[] = "ch";
        char* ret;
        while (ret = strstr(str, ch)) {
            ilosc++;
            memcpy(ret + 0, ret + 1, sizeof(ret) + 1);
        }
        while (ret = strstr(str1, ch)) {
            ilosc1++;
            memcpy(ret + 0, ret + 1, sizeof(ret) + 1);
        }
        while (ret = strstr(str2, ch)) {
            ilosc2++;
            memcpy(ret + 0, ret + 1, sizeof(ret) + 1);
        }
    }


    printf("Slowa w najwiekszej liczbe wystapien litery ");
    if (choice == 1) printf("'c' \n");
    else printf("'ch' \n");
    if (ilosc > ilosc1 || ilosc > ilosc2)
    {
        if (ilosc1 > ilosc2)
        {
            printf(" %d \n", cstr);
            printf(" %d \n", cstr1);
            printf(" %s \n", cstr2);
        }
        else {
            printf(" %s \n", cstr);
            printf(" %s \n", cstr2);
            printf(" %s \n", cstr1);
        }
    }
    else if (ilosc1 > ilosc || ilosc1 > ilosc2)
    {
        if (ilosc > ilosc2)
        {
            printf(" %s \n", cstr1);
            printf(" %s \n", cstr);
            printf(" %s \n", cstr2);
        }
        else {
            printf(" %s \n", cstr1);
            printf(" %s \n", cstr2);
            printf(" %s \n", cstr);
        }
    }
    else
    {
        if (ilosc1 > ilosc)
        {
            printf(" %s \n", cstr2);
            printf(" %s \n", cstr1);
            printf(" %s \n", cstr);

        }
        else {
            printf(" %s \n", cstr2);
            printf(" %s \n", cstr);
            printf(" %s \n", cstr1);
        }
    }
    char buffer[80];
    int amount = sprintf_s(buffer, 80, "%d", ilosc + ilosc1 + ilosc2);
    printf(" Wystapila %d razy w wszystkich slowach  \n", amount);
    free(cstr);
    cstr = NULL;
    free(cstr1);
    cstr1 = NULL;
    free(cstr2);
    cstr2 = NULL;
}

