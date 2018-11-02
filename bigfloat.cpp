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
#define ll long long
#define L 1000000000                // 10^9
#define LL 1000000000000000000LL    // 10^18
#define C 10001                     // maksymalna mozliwa ilosc znakow wczytywanych liczb (cyfry przed przecinkiem + cyfry po)
#define ce continue

#define GG getc(f)                  // funkcje do dzialania na znakach z pliku
#define PP(x) putc(x,f)
#define UU(x) ungetc(x,f)








// -- funkcje wczytujace i wypisujace --

void scan( char *t1, int &u1, char &s1) {   // wczytaj liczbe ze strumienia

// t1 - tablica przechowujaca cyfry
// u1 - "dlugosc" liczby, tj. ilosc cyfr po przecinku + ilosc cyfr przed przecinkiem
// s1 - znak liczby (ujemna czy dodatnia)

// liczba przechowywana jest jako ciag cyfr,
// tzn. np. liczba 9803284209384.2563262 widziana jest jako *t1 = [9,8,0,3,2,8,4,2,0,9,3,8,4,2,5,6,3,2,6,2,0,0,0,...]


    int i, u, e;
    char *t = new char[C];
    memset(t, 0, C * sizeof(char));



    while( (e=G) < 45);             // zignoruj ewentualne spacje i znaki nowej linii, oddzielajace liczby ze strumienia
    U(e);


    ( s1=( ( e=G) == 45))? 0 : U(e);
    // ^Jesli przed liczba znajduje sie znak "-", to liczba jest ujemna. Jesli pierwszy pobrany znak jest inny niz '-' to zwroc go do strumienia


    for( u=e=0 ; ((t[u]=G) > 47 && t[u] < 58) || t[u]==46 ;)  // kontynuuj wczytywanie znakow ze strumienia, dopoki sa one cyframi lub "."
        if( !e || u-e < DP)
            t[u] == 46 ? e=u : t[u++]-=48;                   // jezeli w strumieniu znaleziono ".", to zapamietaj ile jest cyfr przed przecinkiem (e)

    U(t[u]);                                                 // ostatni wczytany znak, ktory nie jest ani "." ani cyfra, zwroc do struminia
    e = !e ? 0 : u-e;                                        // jezeli w strumieniu nie bylo "." (wczytana liczba calkowita) to wstaw przecinek na koniec


    for( i=0; i < max( u1, DP-e); i++)                       // jesli ilosc cyfr po przecinku wczytanej liczby < DP, to uzupelnij cyfry zerami
        t1[i] = 0;

    for( i=0; i < u; i++)
        t1[DP-e+i] = t[u-1-i];

    u1 = DP + u - e;

    delete [] t;
}


void print( char *t, int u, char s1) {      // wypisz liczbe zapisana w pamieci

    int i, m = print_DP;                               // wypisz o 20 cyfr mniej, gdyz ostatnie sa obarczone bledem

    s1 ? P(45) : 0;                                    // jesli liczba jest ujemna, to wypisz znak "-" na poczatku

    for( i=u-1; i>=(u-1-m); i==DP ? P(46) : 0,i--)     // wypisz cala liczbe, z dokladnoscia do DP cyfr po ".", wstawiajac w odpowiednim miejscu "."
        P(t[i]+48);

    P(10);  // znak nowej linii
}


void sscan( FILE *f, char *t1, int &u1, char &s1) {  // wczytywanie liczb do DP cyfr po przecinku z pliku *f

    int i,u,e;
    char *t = new char[C];
    memset(t, 0, C * sizeof(char));



    while( (e=GG) < 45);             // zignoruj ewentualne spacje i znaki nowej linii, oddzielajace liczby ze strumienia
    UU(e);


    ( s1 = ((e=GG)==45)) ? 0 : UU(e);



    for( u=e=0; ( (t[u]=GG) > 47 && t[u] < 58 ) || t[u] == 46; )
        if( !e || u-e < DP)
            t[u] == 46 ? e=u : t[u++] -= 48;


    e = !e ? 0 : u-e;
    for( i=0; i < max( u1, DP-e); i++)
        t1[i]=0;

    for( i=0; i < u; i++)
        t1[DP-e+i] = t[u-1-i];

    u1 = DP+u-e;

    delete [] t;
}


void pprint( FILE *f, char *t, int u, char s1) {     // wypisywanie liczby z DP cyframi po przecinku do pliku *f

    int i, m = DP;

    s1 ? PP(45) : 0;

    for( i=u-1; i >= u-1-m; i == DP ? PP(46) : 0,i--)
        PP(t[i]+48);

    PP(10); PP(10);
}





// -- funkcje konwertujace miedzy formatami 1- i 9- cyfrowymi --

void read( int *T, char *t, int &u) { // zamien liczbe przechowywana w formacie: *t = [2,3,2,6,3,0,3,6,3,2,6,0,0,0,...] na format 9-cyfrowy: *T = [23, 263036326, 0, 0, ...]

    int i,j;

    for( i=0; i <= u/9; i++)
        for( j=(i==u/9?(u%9+8)%9:8) ; j>=0; j--)
            T[i] = 10*T[i] + t[i*9+j];

    u=u/9+!!(u%9);
}


void sprint( char *t1, int *T, int &u1)  // zamien liczbe z formatu 9-cyfrowego na format "pojedynczocyfrowy"
{
    int i, j, m;
    m = DP;

    for( i=m/9; i < u1; i++)
        for( j=0; j<9; j++) {

            9*i+j-m >= 0 ? t1[9*i+j-m] = T[i]%10 : 0;
            T[i]/=10;
        }

    for( u1=9*u1-m; !t1[u1-1] && u1>(DP<<1)-m+1; )
        u1--;
}






// -- funkcje konwertujace "zwykle" liczby int/double na liczby "dlugie" --

double ff( char *t, int u, char s) {    // zamien liczbe *t z DP miejscami po przecinku na liczbe double (przyblizona) z 15 miejscami po przecinku

    double a;
    int i;

    for( a=0, i=u-1 ; i >= DP-15; i--)
        a = 10*a+t[i];

    a = s ? -a : a;

    return a*1e-15;
}


void ss( double a, char *t, int &u, char &s) { // zamien liczbe double na postac liczby *t z DP miejscami po przecinku (uzupelnionymi zerami)

    int i, u1;

    //char t1[C]={0};
    char *t1 = new char[C];
    memset(t1, 0, C * sizeof(char));

    for( i=0; i < min( C, u); i++)
        t[i]=0;

    a = (s=a<0) ? -a : a;

    sprintf( t1, "%.lf", round(a*1e+15));

    for( u1=0; t1[u1]; u1++);

    for( u=0; u < u1; u++)
        t[DP-15+u] = t1[u1-1-u]-48;

    u = max( DP+u1-15, DP+1);

    delete [] t1;
}


void ss( ll a, char *t, int &u, char &s) {  // zamien liczbe calkowita a typu long long na postac liczby *t z DP miejscami po przecinku (DP zer)

    int i;
    for( i=0; i < min( C, u); i++)  // zeruj tablice *t
        t[i]=0;

    a=(s=a<0) ? -a : a;             // a = |a|

    for( u=DP+!a ; a ; ) {
        t[u++] = a%10;
        a /= 10;
    }
}






// -- funkcje +/- przesuwajace przecinek w liczbie --

void shift( ll *a, ll b, int &u1){       // (format 18-cyfr) Podziel dluga liczba *a przez krotka liczbe b

    // Uwaga: liczba *a przechowywana jest jako ciag 18-cyfrowych liczb long long, tzn.
    // np. liczba 9803284209384.2563262 widziana jest w pamieci jako a = [ 98, 032842093842563262, 0, 0, ...]

    int u2 = u1 - 1;

    ll x=0, y, l=LL/b;

    for( u1=0; u2>=0 || x; a++, u1++, u2--) {
        y = *a / l;
        *a -= y * l;
        *a = *a * b + x;
        x = y;
    }
}


void shift( int *a, int b, int &u1) {    // (format 9-cyfr) podziel dluga liczba *a przez krotka liczbe b

    // Uwaga: liczba *a przechowywana jest jako ciag 9-cyfrowych liczb long long, tzn.
    // np. liczba 9803284209384.2563262 widziana jest w pamieci jako a = [ 98, 032842093, 842563262, 0, 0, ...]


    int u2 = u1-1;
    int x=0, y, L2=L/b;

    for( u1=0; u2 >= 0 || x; a++, u1++, u2--) {

        y = (*a)/L2;
        *a -= y * L2;
        *a = (*a)*b + x;
        x=y;
    }
}


void lswitch( char *t, int &u, int m) {  // (format "pojedynczocyfrowy") podziel liczbe przez 10^m

    int i;

    for( i=u-1; i >= 0; i--)
        t[i+m] = t[i];

    for( i=0; i < m; i++)
        t[i]=0;

    u += m;
}


void rswitch( char *t, int &u, int m) {  // (format "pojedynczocyfrowy") pomnoz liczbe razy 10^m

    int i;
    for( i=0; i < u; i++)
        t[i] = t[i+m];

    for( i=u ;i < u+m; i++)
        t[i]=0;

    u = max( u-m, DP+1);
}






// -- funkcje porownujace liczby --

char comp18( ll *a, ll *b, int u1, int u2){          // (format 18-cyfr) okresl, czy liczba *a jest wieksza/rowna od liczby *b (ilosc miejsc po przecinku to zawsze DP, wiec nie ma ona znaczenia!)

    if(u1!=u2)
        return u1 > u2;

    int i;
    for( i=u1-1; i && a[i]==b[i]; i--);

    return a[i] >= b[i];
}

char comp( char *t1, char *t2, int u1, int u2) {    // (format "pojedynczocyfrowy") okresl, CZY liczba *a JEST WIEKSZA/ROWNA od liczby *b

    int i;

    if( u1 != u2)
        return u1>u2;


    for( i=0; i < u2-1 && t1[u1-1-i]==t2[u2-1-i]; i++);


    return t1[u1-1-i] >= t2[u2-1-i];
}

char comp( char *t1, char *t2, int u1, int u2, char s1, char s2) { // CZY *a jest wieksza (ALE NIE ROWNA!!!) od liczby *b

    // (format "pojedynczocyfrowy") okresl, CZY liczba *a JEST WIEKSZA od liczby *b dla liczb o roznych znakach

    int i;
    char odp;

    if( u1 != u2)
        odp = u1 > u2;
    else {

        for( i=0; i < u2-1 && t1[u1-1-i] == t2[u2-1-i]; i++);

        odp = t1[u1-1-i] > t2[u2-1-i];
    }




    if( !s1 && !s2)     // jezeli obie liczby dodatnie
        return odp;

    if( s1 && s2)       // jezeli obie ujemne
        return !odp;

    if( !s1 && s2)      // jesli pierwsza dodatnia, druga ujemna
        return 1;

    if( s1 && !s2)      // jesli pierwsza ujemna, druga dodatnia
        return 0;


    return 0;   // unikniecie bledu kompilatora
}

char comp9( int *a, int *b, int u1, int u2) {       // (format 9-cyfr) okresl, CZY liczba *a JEST WIEKSZA/ROWNA od liczby *b

    if( u1 != u2)
        return u1 > u2;

    int i;

    for( i=u1-1; i && a[i]==b[i]; i--);

    return a[i] >= b[i];
}






// -- funkcje kopiujace liczby --

void copy( char *t1, char *t2, int &u1, int u2) { // (format "pojedynczocyfrowy") *t1 := *t2

    int i;
    for( i=0; i < min( C, u1); i++)
        t1[i]=0;

    for( i=0; i < u2; i++)
        t1[i]=t2[i];

    u1=u2;
}

void copy( char *t1, char *t2, int &u1, int u2, char &s1, char s2) {copy(t1,t2,u1,u2); s1=s2;}  // *t1 := *t2 dla liczb zarowno dodatnich, jak i ujemnych






// -- dodawanie i odejmowanie --

void dec( char *t1, char *t2, int u1, int k, int u2) {  // (format "pojedynczocyfrowy") oblicz *t1 := *t1 - 10^k * (*t2)

    // czyli odejmij *t2 od *t1 z przesunieciem dziesietnym o k


    int i;
    for( u1 = max( u1, u2), i=0; i<u1; i++) {

        t1[k+i] -= t2[i];

        if(t1[k+i] < 0) {

            t1[k+i] += 10;
            t1[k+i+1]--;
        }
    }
}


void dec( char *t1, char *t2, int &u1, int u2) {        // (format "pojedynczocyfrowy") oblicz *t1 := *t1 - (*t2)

    dec(t1,t2,u1,0,u2);

    while( u1>DP+1 && !t1[u1-1])
        u1--;
}


void dec( int *t1, int *t2, int &u1, int u2) {          // (forma 9-cyfr) oblicz *t1 := *t1 - *t2 ; zawsze *t1 > *t2

    int i;

    for( i=0; i < u1; i++) {

        t1[i] -= t2[i];
        t1[i] < 0 ? (t1[i] += L, t1[i+1]--) : 0;
    }

    for( ; u1-1 > 0 && !t1[u1-1]; )
        u1--;
}


void add( char *t1, char *t2, int &u1, int u2) {        // (format "pojedynczocyfrowy") *t1 := *t1 + *t2 ; *t1, *t2 > 0

    int i;
    for( u1 = max( u1, u2), i=0; i < u1 ;i++) {

        t1[i]+=t2[i];

        if(t1[i]>9) {

            t1[i]-=10;
            t1[i+1]++;
        }
    }

    t1[u1] ? u1++ : 0;
}









// -- mnozenie, dzielenie i pierwiastek kwadratowy --


void mod( int &q, int &r, ll a, ll m) {ll q2 = a/m; r = a - q2*m; q += q2;} // q := q + a/m ; r := a % m; funkcja pomocnicza do mul(...)

int T1[C/9], T2[C/9], T[(C<<1)/9];  // tablice pomocnicze do funkcji mul(...) i div(...) oznaczonych "!!!!!"
//
void mul( char *t1, char *t2, int &u1, int u2)
{
    int i,j;

    memset(T1, 0,      C/9 * sizeof(int));  // wyzeruj tablice liczb
    memset(T2, 0,      C/9 * sizeof(int));
    memset(T , 0, (C<<1)/9 * sizeof(int));




    read( T1, t1, u1);     // zamien liczbe *t1 na format 9-cyfrowy *T1
    read( T2, t2, u2);     // zamien liczbe *t2 na format 9-cyfrowy *T2


    for( i=0; i < u1; i++)          // pomnoz liczby *T1 i *T2 algorytmem o zlozonosci O(n^2) a wynik zapisz w *T
        for( j=0; j < u2; j++)
            mod( T[i+j+1], T[i+j], (ll)T[i+j]+(ll)T1[i]*T2[j], L);

    u1+=u2;

    sprint( t1, T, u1);      // zamien liczbe *T z formatu 9-cyfrowego na liczbe *t1 w formacie "pojedynczocyfrowym"
}



void div( char *t1, char *t2, int &u1, int u2)
{
    char *tt = new char[C];
    memset(tt, 0, C * sizeof(char));
    int uu = 0;
    copy( tt, t2, uu, u2);  // *tt := *t2


    while( !t1[u1-1])   // pomin zera wiodace: np. 0002424.43563 ---> 2424.43563
        u1--;
    while( !t2[u2-1])
        u2--;


    int i, l, u11=u1, u22=u2;

    memset(T1, 0,      C/9 * sizeof(int));  // wyzeruj tablice liczb
    memset(T2, 0,      C/9 * sizeof(int));





    if( u1 > u2)
        lswitch( t2, u2, u1-u2);
    else
        lswitch( t1, u1, u2-u1);


    read(T1,t1,u1); // zamien z "pojedyczocyfrowych" na 9-cyfrowe
    read(T2,t2,u2);

    char t[C]={0};

    for( i=u22; i <= u11+DP; i++)
    {
        for( l=0; comp9( T1, T2, u1, u2); l++)  // odejmuj *T2 od *T1 tyle, ile razy sie da
            dec(T1,T2,u1,u2);

        t[( u11+DP)-i]=l;                       // tworz licze *t, bedaca wynikiem dzielenia
        shift(T1,10,u1);                        // podziel *T1 przez 10 (zeby odejmowac od niego 10 razy wiecej *T2)
    }

    u1 = max( DP+1, u11-u22+DP+1);
    if( u1 > DP+1 && !t[u1-1])
        u1--;

    copy( t2, tt, u2, uu);                      // przwroc stara wartosc *t2 := *tt

    for( i=u2; i <= C; i++)
        t2[i]=0;

    copy(t1,t,u1,u1);                           // przypisz *t1 := t

    for( i = u1; i <= C; i++)                   // wyzeruj tablice *t
        t1[i]=0;

    delete [] tt;
}


ll a[C/9], b[C/9];                  // liczby pomocnicze, do funkcji liczacej pierwiastek
//
void sqrt( char *t, int &u)         // oblicz pierwiastek kwadratowy z liczby przechowywanej w tablicy *t, o dlugosci (ilosc cyfr) = u
{
    // zrealizuj algorytm: https://pl.wikipedia.org/wiki/Metody_obliczania_pierwiastka_kwadratowego#Wyznaczanie_cyfra_po_cyfrze


    lswitch( t, u, DP);


    int i, k, l, u1,u2;
    //char t1[C]={0};
    char *t1 = new char [C];
    memset(t1, 0, C * sizeof(char));


    u&1 ? ( a[0] = t[u-1], k=u-2) : ( a[0] = 10*t[u-1]+t[u-2], k=u-3);  // inaczej postepuj, jesli dlugosc liczby jest parzysta, a inaczej jesli nieparzysta

    for( t[-1]=0, u1=u2=1; k>=-1; a[0] += 10*t[k]+t[k-1], k-=2)
    {
        for( l=0, b[0]++; comp18(a,b,u1,u2); l++, b[0]+=2)
        {
            for( i=0; i<u2; a[i] -= b[i], i++)
                if( a[i] < b[i]) {
                    a[i] += LL;
                    a[i+1]--;
                }

            while( u1 > 1 && !a[u1-1])
                u1--;
        }
        t1[(k+1)>>1]=l, b[0]--;


        shift( b, 10 , u2);
        shift( a, 100, u1);

    }
    for( i=0; i<u; i++)                 // przypisz wynik *t := sqrt( *t)
        t[i]=t1[i];

    u=(u+1)>>1;
    for( i=0; i < max( u1, u2); i++)    // wyzeruj tablice pomocnicze *a i *b
        a[i] = b[i] = 0;

    delete [] t1;
}








// -- funkcje podsumowujace, do podstawowych dzialan na dlugich floatach o roznych znakach --


void add( char *t1, char *t2, int &u1, int u2, char &s1, char s2) {   // dodaj 2 liczby o roznych mozliwosciach znakow: np. -2+4, -5+12, -4+(-12)

    if( s1==s2) { add( t1, t2, u1, u2); return;}              // obie ujemne lub obie dodatnie

    if( comp( t1, t2, u1, u2)) {dec( t1, t2, u1, u2); return;}  // jesli rozne znaki, to odejmij mniejsza od wiekszej

    int u3;
    char t3[C]={0}, s3;
    copy( t3, t2, u3, u2, s3, s2);

    dec( t3, t1, u3, u1);
    copy( t1, t3, u1, u3, s1, s3);
}


void mul( char *t1, char *t2, int &u1, int u2, char &s1, char s2) { mul( t1, t2, u1, u2); s1^=s2;}   // pomnoz 2 liczby o roznych mozliwosciach znakow


void div( char *t1, char *t2, int &u1, int u2, char &s1, char s2) { div( t1, t2, u1, u2); s1^=s2;}       // podziel 2 liczby o roznych mozliwosciach znakow






// -- funkcje operujace na liczbach: 1. dlugiej i 2. krotkiej -- BARDZO NIEEFEKTYWNE - DO POPRAWIENIA!!!

void mul( char *t1, ll a, int &u1, char &s1) {  // pomnoz "dluga" liczbe *t przez mala, calkowita liczbe a typu long long

    int u2;

    char *t2 = new char[C], s2;
    memset(t2, 0, C * sizeof(char));

    a < 0 ? (s1^=1,a=-a) : 0;

    ss( a, t2, u2, s2);

    mul( t1, t2, u1, u2);

    delete [] t2;
}


void div( char *t1, ll a, int &u1, char &s1) {  // podziel "dluga" liczbe *t przez mala, calkowita liczbe a typu long long

    int u2;

    char *t2 = new char[C], s2;
    memset(t2, 0, C * sizeof(char));

    a < 0 ? (s1^=1,a=-a) : 0;

    ss( a, t2, u2, s2);

    div( t1, t2, u1, u2);

    delete [] t2;
}






// -- funkcje zwracajace stala liczbowe

char LN10[C], PI[C];
int uLN10, uPI;


void const_init( ) {


    FILE *f=fopen("pi.txt","r");      // odczytaj liczby pi = 3.1415... i ln(10) = 2,302... z pliku tekstowego,
                                      // gdzie sa podane do DP miejsc po przecinku
    char s;

    sscan( f, LN10, uLN10, s);    // wczytanie liczby ln(10)
    sscan( f, PI, uPI, s);        // wczytanie liczby pi



    fclose(f);
}

void pi( char *t, int &u, char &s) {

    copy( t, PI, u, uPI); s = 0;
}

void ln10( char *t, int &u, char &s) {

    copy( t, LN10, u, uLN10); s = 0;
}



