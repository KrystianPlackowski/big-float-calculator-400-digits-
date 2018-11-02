#ifndef bigfloat_h
#define bigfloat_h

using namespace std;

#define G getc( stdin)              // funkcje do dzialania na znakach strumienia
#define P(x) putc( x, stdout)
#define U(x) ungetc( x, stdin)
#define min(x,y)((x)<(y)?(x):(y))
#define max(x,y)((x)>(y)?(x):(y))
#define ll long long
#define L 1000000000                // 10^9
#define LL 1000000000000000000LL    // 10^18
#define C 10001                     // maksymalna mozliwa ilosc znakow wczytywanych liczb (cyfry przed przecinkiem + cyfry po)
#define ce continue

#define GG getc(f)                  // funkcje do dzialania na znakach z pliku
#define PP(x) putc(x,f)
#define UU(x) ungetc(x,f)


const int DP = 550;                 // dokladnosc kalkulatora (ilosc miejsc po przecinku)
const int print_DP = 400;           // ilosc cyfr wypisywanych na pulpit
#define g 320                       // ilosc wspolczynnikow we wzorze Spouge'a (define, gdyz liczba ta definiuje rozmiar tablicy globalnej)




// -- funkcje wczytujace i wypisujace --

void scan( char *t1, int &u1, char &s1);

void print( char *t, int u, char s1);

void sscan( FILE *f, char *t1, int &u1, char &s1);

void pprint( FILE *f, char *t, int u, char s1);




// -- funkcje konwertujace miedzy formatami 1- i 9- cyfrowymi --

void read( int *T, char *t, int &u);


void sprint( char *t1, int *T, int &u1);




// -- funkcje konwertujace "zwykle" liczby int/double na liczby "dlugie" --

double ff( char *t, int u, char s);


void ss( double a, char *t, int &u, char &s);


void ss( ll a, char *t, int &u, char &s);





// -- funkcje +/- przesuwajace przecinek w liczbie --

void shift( ll *a, ll b, int &u1);


void shift( int *a, int b, int &u1);


void lswitch( char *t, int &u, int m);


void rswitch( char *t, int &u, int m);





// -- funkcje porownujace liczby --

char comp18( ll *a, ll *b, int u1, int u2);

char comp( char *t1, char *t2, int u1, int u2);

char comp( char *t1, char *t2, int u1, int u2, char s1, char s2);

char comp9( int *a, int *b, int u1, int u2);






// -- funkcje kopiujace liczby --

void copy( char *t1, char *t2, int &u1, int u2);


void copy( char *t1, char *t2, int &u1, int u2, char &s1, char s2);





// -- dodawanie i odejmowanie --

void dec( char *t1, char *t2, int u1, int k, int u2);


void dec( char *t1, char *t2, int &u1, int u2);


void dec( int *t1, int *t2, int &u1, int u2);


void add( char *t1, char *t2, int &u1, int u2);










// -- mnozenie, dzielenie i pierwiastek kwadratowy --


void mod( int &q, int &r, ll a, ll m);       // funkcja pomocnicza do mul(...)


void mul( char *t1, char *t2, int &u1, int u2);


void div( char *t1, char *t2, int &u1, int u2);


void sqrt( char *t, int &u);






// -- funkcje podsumowujace, do podstawowych dzialan na dlugich floatach o roznych znakach --


void add( char *t1, char *t2, int &u1, int u2, char &s1, char s2);

void mul( char *t1, char *t2, int &u1, int u2, char &s1, char s2);

void div( char *t1, char *t2, int &u1, int u2, char &s1, char s2);




// -- funkcje operujace na liczbach: 1. dlugiej i 2. krotkiej -- BARDZO NIEEFEKTYWNE - DO POPRAWIENIA!!!

void mul( char *t1, ll a, int &u1, char &s1);

void div( char *t1, ll a, int &u1, char &s1);




// -- funkcje zwracajace stala liczbowe

void const_init( );

void pi( char *t, int &u, char &s);

void ln10( char *t, int &u, char &s);


#endif
