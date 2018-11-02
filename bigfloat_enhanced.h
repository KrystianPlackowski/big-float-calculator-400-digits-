#ifndef bigfloat_enhanced_h
#define bigfloat_enhanced_h


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <queue>
#include <stack>
#include <string.h>
#include "bigfloat.h"

using namespace std;

#define G getc( stdin)              // funkcje do dzialania na znakach strumienia
#define P(x) putc( x, stdout)
#define U(x) ungetc( x, stdin)
#define min(x,y)((x)<(y)?(x):(y))
#define max(x,y)((x)>(y)?(x):(y))

#define C 10001                     // maksymalna mozliwa ilosc znakow wczytywanych liczb (cyfry przed przecinkiem + cyfry po)
#define ce continue

#define GG getc(f)                  // funkcje do dzialania na znakach z pliku
#define PP(x) putc(x,f)
#define UU(x) ungetc(x,f)




struct num {

    char bb[C];     // tablica przechowujaca cyfry
    int u;          // "dlugosc" liczby, tj. ilosc cyfr po przecinku + ilosc cyfr przed przecinkiem
    char s;         // znak liczby (ujemna czy dodatnia)
};






num scan( );                                     // wczytaj num

num sscan( FILE *f);                             // wczytaj num

void print( num A);                              // wypisz num

void pprint( FILE *f, num A);                              // wypisz num

char operator > ( num A, num B);

char operator < ( num A, num B);

num  abs( num A);                                // wartosc bezwzgledna liczby

num operator + ( num A, num B);

num operator - ( num A, num B);

num operator * ( num A, num B);

num operator / ( num A, num B);

num operator * ( num A, ll b);                  // pomnoz num razy liczbe calkowita

num operator / ( num A, ll b);                  // podziel num przez liczbe calkowita

num sqrt( num A);                               // pierwiastek z num

num floati( double a);                          // zamien double na num

num pi();                                       // zwroc liczbe pi

num ln10();                                     // zwroc wartosc ln(10)






num agm( num a, num b);

num ln( num A);

num exp( num A);



num operator ^ ( num A, num B);

void calc_ck();

void Spouge_init();

num gamma( num z);



#endif
