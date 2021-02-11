#include <stdio.h>
#include <stdlib.h>

int tab [20] [31] = { 0 };
int rozmiar[20] = { 0 };
int k = 0;
int ptab[31] = { 0 };


void dec_to_bin(int liczba)
{
	int i = 0;

	while (liczba) //dopóki liczba bêdzie ró¿na od zera
	{
		tab[k][i++] = liczba % 2;
		liczba /= 2;
	}

	rozmiar[k] = i;
	for (int j = i - 1; j >= 0; j--)
	{
		printf("%d ", tab[k][j]);
	}
	k++;

}

// Ustawianie bitu  
void set_bit(int liczba, int bit)
{
	int dlugosc = rozmiar[liczba - 1];

	for (int i = 0; i < dlugosc; i++) {
		if (i == dlugosc - bit) {
			tab[liczba - 1][i] = 1;
		}
	}

	for (int j = dlugosc - 1; j >= 0; j--)
	{
		printf("%d ", tab[liczba-1][j]);

	}
}

// Ustawianie bitu poprzez maske 
void set_bit_mask (int liczba, int bit)
{
	printf("USTAWIANIE POPRZEZ MASKE \n");
	int dlugosc = rozmiar[liczba - 1];

	for (int i = 0; i < 31; i++) {
		if (i == (dlugosc-bit)) {
			ptab[i] = 1;
		}
	}
	
	printf("Liczba %d po: ", liczba);
	for (int j = dlugosc - 1; j >= 0; j--)
	{
	    ptab[j] = ((tab[liczba - 1][j]) || (ptab[j]));
		printf("%d ", ptab[j]);
	}
}



int main() {
	int i = 0;
	int tablica[20] = { 0 };

	while (i < 20)
	{
		printf("Podaj liczbe: ");
		scanf_s("%d", &tablica[i]);
		i = i + 1;
	}

	i = 0;

	while (i < 20)
	{
		printf("%d. ", i+1);
		printf("%d ", tablica[i]);
		printf(" w postaci binarnej: ");
		dec_to_bin(tablica[i]);
		printf("\n");
		i = i + 1;
	}

	// Ustawianie bitu  
	int liczba = 0;
	int bit = 0;
	printf("Ustawianie bitu \n ");
	printf("Wybierz numer liczby do edycji: ");
	scanf_s("%d", &liczba);
	printf("Wybierz numer bitu do edycji : ");
	scanf_s("%d", &bit);
	set_bit(liczba, bit);

	// Ustawianie bitu poprzez maske 
	
	printf("\n ");
	printf("Ustawianie bitu poprzez maske \n ");
	printf("Pamietaj ze ustawiles juz liczbe %d \n", liczba );
	liczba = 0;
	bit = 0;
	printf("Wybierz numer liczby do edycji: ");
	scanf_s("%d", &liczba);
	printf("Wybierz numer bitu do edycji : ");
	scanf_s("%d", &bit);
	set_bit_mask(liczba, bit);
	
	system("PAUSE");
};
