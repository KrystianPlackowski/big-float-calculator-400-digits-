#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <queue>
#include <stack>
#include <string.h>
#include <windows.h>                // biblioteka wykorzystywana wylacznie to obliczania czasu liczenia dzialania (funkcja GetTickCount() )
#include "bigfloat.h"               // dodawanie, odejmowanie, dzielenie i mnozenie liczb zmiennoprzecinkowych do DP cyfr
#include "bigfloat_enhanced.h"      // srednia arytmetyczno-geometryczna, logarytm naturalny, exp, definicje operatorow

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





struct compx {

    num re;
    num im;
};



char z[128];                    // ponizej struktury do funkcji ONP (odwrotna notacja polska)
stack <int> S;
queue <int> Q;


num NUMS[100];                  // maksymalna ilosc liczb w dzialaniu = 100







char onp()  // odwrotna notacja polska (obliczanie wyrazen nawiasowych)
{
    int p; char c, d=1, result = 1;         // result = 1 oznacza dobre wyrazenie, result = 0 bledne nawiasowanie

    while( (c=G) <= 10);
    U(c);

    for( p=15; (c=G) > 10; )                // wczytuj pokolei znaki ze strumienia
    {
        if( c=='-' && d) {                  // znaleziono znak minus na poczatku strumienia!
            NUMS[p] = floati(0);            // wstaw liczbe "0" na kolejke, dzieki czemu dzialanie "-(2+3)" zostanie zrozumiane jako "0-(2+3)"
            Q.push(p++);
        }
        d=0;



        // ponizej: wczytano LICZBE, wloz ja na kolejke V

        if( 47 < c && c < 58){ U(c); NUMS[p] = scan(); Q.push(p++); ce;}    // wczytaj liczbe ze strumienia i wrzuc ja na kolejke


        if( c=='P') { G; NUMS[p] = pi(); Q.push(p++); ce; }                  // wpisano stala pi przez "PI" w strumieniu
        // ^oblicz 2 * PI/2 = PI i wrzuc na kolejke


        if( c=='E') { NUMS[p] = exp( floati(1)); Q.push(p++); ce;}           // wpisano stala e (podstawe logarytmu naturalnego)
        // ^oblicz exp(1) i wrzuc na kolejke




        // ponizej: wczytano FUNKCJE, wloz ja na stos V

        if( c=='l') {G; S.push(7); ce;}   // wczytaj funkcje ln(...)        (logarytm naturalny)

        if( c=='e') {G,G; S.push(8); ce;} // wczytaj funkcje exp(...)       (exponenta)

        if( c=='W') {S.push(9); ce;}     // wczutaj funkcje W(... , ...)   (funkcja W lamberta, dwuarguentowa: W(-1, -0.2) = -2,5426... ; W(0, -0.2) = -0,25917... )

        if( c=='s') { G,G,G; S.push(12); ce;}  // ^wczytaj funkcje sqrt(...) (zwykly pierwiastek kwadratowy)

        if( c=='a') { G,G; S.push(11); ce;}  // wczytaj funkcje agm(... , ...) (srednia artytmetyczno-geometryczna: agm(1,2) = 1.45679103... )




        // ponizej: wczytano OPERATOR ze zbioru {+,-,*,/,^,!) V

        if( z[(int)c] <= 6)
        {
            while( !S.empty() && S.top() <= 6 && ( S.top()/2 >= z[(int)c]/2+(c=='^'))) {

                Q.push(S.top());
                S.pop();
            }
            S.push(z[(int)c]); ce;
        }


        if( (d = (c ==','))) {                              // wczytano przecinek oddzielajacy argumenty funkcji


            while( !S.empty() && S.top() != 14) { Q.push(S.top()); S.pop();}

            if( S.empty() && S.top() != 14) result = -1;     // bledne nawiasowanie
            ce;
        }



        if( c == '(') { S.push(14); d=1; ce;}                // wczytano nawias zwykly (14 na stosie oznacza nawias zwykly)



        if( c == ')') {

            while( !S.empty() && S.top() != 14) { Q.push(S.top()); S.pop();}


            if( S.empty()) result = -1; else S.pop();        // jesli teraz stos jest pusty, oznacza to bledne nawiasowanie!

             // jesli na stosie jest funkcja, to doluz ja do kolejki V

            if( !S.empty() && 14 > S.top() && S.top() > 6) { Q.push(S.top()); S.pop();}

            //if( S.empty()) result = -1;                     // jesli teraz stos jest pusty, oznacza to bledne nawiasowanie!

        }
        else
            result = -2;                                    // niezindentyfikowany znak na wejsciu!
    }


    while( !S.empty()) {

        if( S.top() == 14)                                 // jesli natrafiono na lewy nawias, oznacza to bledne nawiasowanie!
            result = -1;

        Q.push(S.top());
        S.pop();
    }


    return result;
}







int main()
{

    const_init();                           // zainicjalizuj (wczytaj) stale pi() i ln10()

    //calc_ck();                            // oblicz wspolczynniki Spouge'a do funkcji gamma (silni)

    Spouge_init();                          // wczytaj wspolczynniki Spouge'a do funkcji gamma (silni)





    num a, b;

    char result;
    int i, aa, bb;

    for( i=33; i <= 127; i++)
        z[i]=127;

    z['+']=0;                           // kazdemu znakowi ascii przypisz jakas wartosc (mapa)
    z['-']=1;
    z['*']=2;
    z['/']=3;
    z['^']=4;
    z['!']=6;



    for( ; ; P(10))
    {

        result = onp();                // przerob input na wyrazenie w ONP. Rozpoznaj, jesli pojawil sie blad na wejsciu




        double tt = GetTickCount();   // zapamietaj czas na poczatku dzialania

        for( ; result == 1 && !Q.empty(); Q.pop())
        {
            i = Q.front();

            if( i > 14) {S.push(i); ce;}                   // jezeli na kolejce jest liczba, to wrzuc ja na stos



            // wez ze stosu 1 liczbe

            if( S.empty()){ result = -2; break;}            // nie znaleziono liczby

            a = NUMS[ aa=S.top()];
            S.pop();


            // jezeli na kolejce jest operator lub funkcja 2-argumentowa, to wez ze stosu 2. liczbe

            if( i <= 5 || i == 11) {

                if( S.empty()){ result = -2; break;}        // nie znaleziono liczby

                b = NUMS[ bb=S.top()];
                S.pop();
            }




            if(i==0) { NUMS[bb] = b + a; S.push(bb);}       // dodawanie
            if(i==1) { NUMS[bb] = b - a; S.push(bb);}       // odejmowanie (dodawanie, gdzie druga liczba jest z przeciwnym znakiem)
            if(i==2) { NUMS[bb] = b * a; S.push(bb);}       // mnozenie
            if(i==3) { NUMS[bb] = b / a; S.push(bb);}       // dzielenie
            if(i==4) { NUMS[bb] = b ^ a; S.push(bb);}       // potegowanie (zmiennoprzecinkowe)
            if(i==6) { NUMS[aa] = gamma(a); S.push(aa);}    // silnia/funkcja gamma (zmiennoprzecinkowa)
            if(i==7) { NUMS[aa] = ln(a);  S.push(aa);}      // logarytm naturalny
            if(i==8) { NUMS[aa] = exp(a); S.push(aa);}      // e^x
            //if(i==9)                                      // funkcja W Lamberta ( x * e^x = a, x = ?)
            //if(i==10)                                     // super pierwiastek kwadratowy ( x^x = a, x = ?)
            if(i==11){ NUMS[bb] = agm(b,a); S.push(bb);}    // srednia arytmetyczno-geometryczna liczb a i b
            if(i==12){ NUMS[aa] = sqrt(a);  S.push(aa);}    // pierwiastek kwadratowy
        }




         if( result == 1 && !S.empty()) {                   // jezeli nie bylo ZADNEGO bledu, to wypisz wynik


            aa = S.top();
            print( NUMS[aa]);                               // wypisz na ekran wynik dzialania z dokladnoscia do DP cyfr po "."
            S.pop();

            printf( "%.3lfs\n", (GetTickCount()-tt)/1000);  // wypisz czas obliczen
        }



        if( result == -1) printf( "mismatched parentheses\n");
        if( result == -2) printf( "unidentified character\n");


        while( !Q.empty()) Q.pop();
        while( !S.empty()) S.pop();
    }

    return 0;
}

