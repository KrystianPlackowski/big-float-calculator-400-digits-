#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <queue>
#include <stack>
#include <string.h>
#include "bigfloat.h"
//#include "bigfloat_enhanced.h"

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





num A;

num scan( ) { scan( A.bb, A.u, A.s); return A;}                                         // wczytaj num

num sscan( FILE *f) { sscan( f, A.bb, A.u, A.s); return A;}                             // wczytaj num

void print( num A) {  print( A.bb, A.u, A.s); }                                         // wypisz num

void pprint( FILE *f, num A) {  pprint( f, A.bb, A.u, A.s); }

char operator > ( num A, num B) { return comp( A.bb, B.bb, A.u, B.u, A.s, B.s);}

char operator < ( num A, num B) { return !comp( A.bb, B.bb, A.u, B.u, A.s, B.s);}

num  abs( num A) { A.s = 0; return A;}                                                  // wartosc bezwzgledna liczby

num operator + ( num A, num B) { add( A.bb, B.bb, A.u, B.u, A.s, B.s); return A;}

num operator - ( num A, num B) { add( A.bb, B.bb, A.u, B.u, A.s, !B.s); return A;}

num operator * ( num A, num B) { mul( A.bb, B.bb, A.u, B.u, A.s, B.s); return A;}

num operator / ( num A, num B) { div( A.bb, B.bb, A.u, B.u, A.s, B.s); return A;}

num operator * ( num A, ll b) { mul( A.bb, b, A.u, A.s); return A;}                     // pomnoz num razy liczbe calkowita

num operator / ( num A, ll b) { div( A.bb, b, A.u, A.s); return A;}                     // podziel num przez liczbe calkowita

num sqrt( num A) { sqrt( A.bb, A.u); return A;}                                         // pierwiastek z num

num floati( double a) { ss( a, A.bb, A.u, A.s); return A;}                       // zamien double na num

num pi() { pi( A.bb, A.u, A.s); return A;}                                       // zwroc liczbe pi

num ln10() { ln10( A.bb, A.u, A.s); return A;}                                   // zwroc wartosc ln(10)



num c;

num agm( num a, num b) {    // srednia arytmetyczno-geometryczna liczb a i b

    do {

        c = (a+b) / 2;
        a = sqrt(a*b);
        b = c;
    }
    while( abs(a-b) > floati(0));

    return a;
}


num ln( num A)   // oblicz logarytm naturalny z liczby A z dokladnoscia do DP cyfr po przecinku
{
    // wykorzystuje nastepujacy algorytm: https://en.wikipedia.org/wiki/Natural_logarithm#High_precision

    // nalezy skorzystajac z wlasnosci: agm(k*a, k*b) = k * agm(a, b)

    // wowczas:     ln(x) = (PI/2) * (x*10^m) / agm( 4, x*10^m) - m * ln(10) ; z dokladnoscia do m miejsc po przecinku!



    int m = (DP<<1) - A.u;             // m - wymagana ilosc miejsc po przecinku dokladnosci



    lswitch( A.bb, A.u, m);            // A := A * 10^m       // funkcja przesuwajaca odpowiednio przecinek



    A = pi() / 2 * A / agm( floati(4), A) - ln10() * m;


    return A;
}



num wyn, sum_el;

num exp( num A)  // oblicz e^(A) z dokladnoscia do DP cyfr po przecinku
{
    // oblicz e^input
    // zauwazmy ze: e^x == e^(x/2^20) ^ (2^20)


    int i;

    wyn = floati(1);
    sum_el = floati(1);



    for( i=0; i < 20; i++)                              // A := A / 2^20
        A = A / 2;


    for( i=1; i < 3 || abs(sum_el) > floati(0); i++) {  // dopoki element sum_el jest wiekszy od zera z dokladnoscia do DP

        sum_el = sum_el * A / i;

        wyn = wyn + sum_el;
    }


    for( i=0; i < 20; i++)                              // wyn := wyn^(2^20)
        wyn = wyn * wyn;


    return wyn;
}


num operator ^ ( num A, num B){ A = exp( B * ln(A)); return A;}







num c_k[g];                                     // tablica wspolczynnikow Spouge'a

void calc_ck() {                                // oblicz wspolczynniki we wzorze Spouge'a na funkcje gamma

    int k;
    num fact;


    c_k[0] = sqrt( pi() * 2);

    c_k[1] = sqrt( floati(g-1)) * exp( floati(-1+g));


    fact = floati(-1);

    for( k = 2; k < g; k++) {

        c_k[k] = ( floati(-k+g)^floati(k-0.5)) * exp( floati(-k+g)) / fact;
        fact = fact * floati(-k);

        printf( "%d coefficients calculated. %d more left\n", k, (int)g-k);
    }




    FILE *f = fopen( "Spouge.txt", "w");    // wypisz obliczone wspolczynniki do pliku tekstowego

    for( k = 0 ; k <= g-1 ; k++)
        pprint( f, c_k[k]);

    fclose(f);
}


void Spouge_init() {

    int i;
    FILE *f = fopen( "Spouge.txt", "r");    // wypisz obliczone wspolczynniki do pliku tekstowego

    for( i = 0 ; i <= g-1 ; i++)
        c_k[i] = sscan(f);

    fclose(f);
}


num gamma( num z) {                         // oblicz wartosc funkcji gamma z liczby z

    int k;
    num part;

    part = c_k[0];

    for( k=1; k < g; k++)
        part = part + c_k[k] / ( z+floati(k));

    z = ( ( z+floati(g))^( floati(0.5)+z )) * exp( floati(-g)-z) * part;

    return z;
}
