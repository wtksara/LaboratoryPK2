#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <conio.h>
#include <windows.h>


#define		SIZE_OF_BUFFER		    8	// Maksymalny rozmiar buffora
#define		SUCCESS			        0
#define		FAILURE			        -1

int ile = 1;
int random(int min, int max);
int	numerRGB(int* pNumber);
///////////////////////////////////////////////////////////////////////////////////////////////
typedef struct ListElement {
	int data;
	struct ListElement* poprzedni;
	struct ListElement* nastepny;
} ListElement_type;

void push_back(ListElement_type** glowa, int number);
int ilejest (ListElement_type** glowa, int pwartosc);

int main() {

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//ZAD 1
	int	CirBuf[SIZE_OF_BUFFER] = { 0 };	// Pusty bufor
	int	czytIndex = 0;	// Indeks do czytania
	int	piszIndex = 0;	// Indeks do pisania
	int	dlugosc = 0;	// Ilosc zmiennych w buforze

	srand(time(0));
	int wartosc = 0;
	int index = 0;
	printf("Ile chcesz wygenerowac wartosci RGB ? \n");
	scanf_s("%d", &wartosc);

	int * tab = malloc(sizeof(int) * wartosc);

	printf("\nWartosci wpisane do bufora cyklicznego \n");
	while (wartosc > 0) {
	
		// Sprawdzam czy buffer jest pe³ny
		if (dlugosc == SIZE_OF_BUFFER) {

			tab[index] = CirBuf[czytIndex];
			index++;
			dlugosc--;	 //	Dekrementacja
			czytIndex++;	 //	Inkrementacja do czytania

			// Ostatni index, ustawiam indeks do czytania na 0
			if (czytIndex == SIZE_OF_BUFFER) {
				czytIndex = 0;
			}

		}
		numerRGB(&CirBuf[piszIndex]);	 // Wpisanie liczby RGB
		dlugosc++;	 //	Inkrementacja indeksu
		piszIndex++;	 //	Inkrementacja indeksu do zapisu

		// Ostatni buffer , ustawiam indeks do pisania na 0
		if (piszIndex == SIZE_OF_BUFFER) {
			piszIndex = 0;
		}
		wartosc--;	
    }

	printf("\n Wartosci wpisane do tablicy z bufora");
	for (int i = 0; i < index; i++) {
	   printf("\n %d . Wartosc to %d ", i, tab[i]);
	}
	printf("\n ");

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//ZAD 2
	ListElement_type* glowa;
	glowa = (ListElement_type*)malloc(sizeof(ListElement_type));
	glowa = NULL;
	int zmienna = 0;
	int wieksza = 0; 

	printf("\n Wartosci wpisane do pierwszej listy z tablicy");
	while (zmienna != index) {

		push_back(&glowa, tab[zmienna]);
		printf("\n %d Dodano do listy liczbe: %d ",zmienna,tab[zmienna]);
		zmienna++;
	}
	printf("\n ");

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//ZAD 3

	ListElement_type* glowa1;
	glowa1 = (ListElement_type*)malloc(sizeof(ListElement_type));
	glowa1 = NULL;

	printf("\n Wartosci wpisane do drugiej listy z tablicy za pomoca arytmetyki wskaznikowej");
	int * ptr;
	ptr = tab;
	zmienna = 0;
	while (*ptr != tab[index]) {

		push_back(&glowa1, *ptr);
		printf("\n %d Dodano do listy liczbe: %d ", zmienna, *ptr);
		zmienna++;
		ptr++;
	}


	printf("\n \n Zliczanie wartosci RGB wiekszy od zadanej wartosci RGB ");
	printf("\n Podaj wartosc RGB: ");
	scanf_s("%d", &wartosc);
	int iloscliczb = ilejest(&glowa, wartosc);

	printf("\n Ilosc liczb wiekszych od zadanej w liscie pierwszej to %d ", iloscliczb);

	int iloscliczb1 = ilejest(&glowa1, wartosc);

	printf("\n Ilosc liczb wiekszych od zadanej w liscie drugiej to %d ", iloscliczb1);

	system("pause");
};

int random(int min, int max)
{
	int tmp;
	if (max >= min)
		max -= min;
	else
	{
		tmp = min - max;
		min = max;
		max = tmp;
	}
	return max ? (rand() % max + min) : min;
}

int numerRGB(int* pNumber) {

	int R = (random(0, 256));
	int G = (random(0, 256));
	int B = (random(0, 256));

	int RGBnumber = ((R * 65536) + (G * 256) + B);
	printf("%d .",ile);
	ile++;
	printf("Liczba RGB po obliczeniu :%d \n", RGBnumber);

	char * number[9]; 
	const int ilosc = 9;
	sprintf_s(number,ilosc, "%d", RGBnumber);

	if (sscanf_s(number, "%d", pNumber) != 1) {
		return FAILURE;
	}
	return SUCCESS;
}

void push_back(ListElement_type** head, int number)
{
	if (*head == NULL)
	{
		*head = (ListElement_type*)malloc(sizeof(ListElement_type));
		(*head)->data = number;
		(*head)->poprzedni = NULL;
		(*head)->nastepny = NULL;
	}
	else
	{
		ListElement_type* aktualny = *head;
		ListElement_type* new_element;

		while (aktualny->nastepny != NULL) {
			aktualny = aktualny->nastepny;
		}

		aktualny->nastepny = (ListElement_type*)malloc(sizeof(ListElement_type));
		aktualny->nastepny->data = number;
		aktualny->nastepny->poprzedni = aktualny;
		aktualny->nastepny->nastepny = NULL;
	}

}

int ilejest(ListElement_type** head, int pwartosc)
{
	if (*head == NULL)
	{
		return 0;
	}
	else
	{
		int zmienna = 0;
		ListElement_type* aktualny = *head;
		while (aktualny != NULL) {
			if (aktualny->data > pwartosc) {
				zmienna++;
			}
			aktualny = aktualny->nastepny;
		}
		return zmienna;
	}
}


