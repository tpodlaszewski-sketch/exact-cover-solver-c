// Tomasz Podlaszewski

#include <stdio.h>
#include <stdbool.h>

#define SIZE 320
#define MAX_ROWS 220
#define EMPTY '_'

int wczytajFiltr(int F[]) // wczytuje filtr, zwraca liczbe znakow w wierszu
{
    int c;
    int i = 0;
    c = getchar();
    while (c != '\n' && c != EOF)
    {
        F[i] = c;
        i++;
        c = getchar();
    }
    return i;
}

void wczytajWiersze(int W[], int c) // wczytuje pojedynczy wiersz do tablicy, zaczynajac od znaku c
{
    int i = 0;
    while (c != '\n' && c != EOF)
    {
        W[i] = c;
        c = getchar();
        i++;
    }
}

void wypisz(int A[], int F[], int d) // wypisuje wynik z uzwglednieniem filtra
{
    for (int i = 0; i < d; i++)
    {
        if (F[i] == '+')
            printf("%c", A[i]);
    }
    printf("\n");
}

bool czyZgodny(int A[], int W[], int d) // sprawdza czy dany wiersz moze byc dopisany do tablicy z wynikiem
{
    bool zgodny = true;
    int i = 0;

    while (i < d && zgodny)
    {
        if (W[i] != EMPTY && A[i] != EMPTY)
            zgodny = false;
        i++;
    }

    return zgodny;
}

void wstawWiersz(int A[], int W[], int d) // wpisuje wartości z wiersza w tablice z aktualnym wynikiem
{
    for (int i = 0; i < d; i++)
    {
        if (A[i] == EMPTY && W[i] != EMPTY)
            A[i] = W[i];
    }
}

void usunWiersz(int A[], int W[], int d) // usuwa z aktualnego wyniku znaki z danego wiersza
{
    for (int i = 0; i < d; i++)
    {
        if (W[i] != EMPTY)
            A[i] = EMPTY;
    }
}

void rek(int F[], int W[][SIZE], int A[], int d, int w)
{
    int pierwszy_wolny = -1;
    int i = 0;

    while (i < d && pierwszy_wolny == -1) // szukamy pierwszego niezapelnionego miejsca w aktualnym wyniku
    {
        if (A[i] == EMPTY)
            pierwszy_wolny = i;
        i++;
    }

    if (pierwszy_wolny == -1) // jesli aktualny wynik ma wszystkie miejsca zapelnione
    {
        wypisz(A, F, d);
        return;
    }
    else
    {
        for (int k = 0; k < w; k++)
        {
            if (W[k][pierwszy_wolny] != EMPTY && czyZgodny(A, W[k], d))
            {
                wstawWiersz(A, W[k], d);
                rek(F, W, A, d, w);
                usunWiersz(A, W[k], d);
            }
        }
    }
}

int main()
{
    int F[SIZE];
    int d = wczytajFiltr(F);

    int W[MAX_ROWS][SIZE];
    int c = getchar();
    int w = 0; // liczba wierszy

    while (c != EOF)
    {
        wczytajWiersze(W[w], c);
        w++;
        c = getchar();
    }

    int A[SIZE]; // tablica do przechowywania aktualnego wyniku
    for (int i = 0; i < d; i++)
        A[i] = EMPTY; // EMPTY symbolizuje niezapelnione miejsce w zbiorze

    rek(F, W, A, d, w);

    return 0;
}
