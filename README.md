
# Advanced arbitrary precision calculator for evaluating brackets expressions


## List of possible functions in the intepreter with examples


**Name,					     Example of use**


List of operators:

a) Addition: 				    2+5

b) Substracting: 			    2.71-3.14

c) Multiply: 				    1234*5678

d) Division: 				    355/113

e) Exponentiation: 			    2^100

f) Factorial/Gamma function: 	            2.5!

List of functions:

a) Square root: 	                    sqrt(2)

b) Natural logarithm: 	                    ln(17)

c) Exponential function: 	            exp(-0.5) OR E^(-0.5)

d) Arithmetic-geometric mean: 	            agm(1,2)

https://en.wikipedia.org/wiki/Arithmetic%E2%80%93geometric_mean

Two constants:

a) Archimedes' constant PI: 	            E^PI

b) Natural logarithm's base E: 	            sqrt(E)!


=================================================================


The first library "bigfloat.h" contains implementation of only basic operators and square root, and 2 constants, when the second library "bigfloat_enhanced.h" contains more advanced functions, based on those basic ones from the first library.

Two constants: ln(10) and PI are available up to 1000 digits in the text file "pi.txt". They can't be computed directly, but are needed for program's functionality.

The text file "Spouge.txt" contains all previously computed coefficients for Gamma function using Spouge's formula:

https://en.wikipedia.org/wiki/Spouge%27s_approximation

If arithmetics precision 'DP' or number of coefficients 'g' is changed, the function 'calc_ck()' that is greyed out in file "main.cpp" has to be evaluated once, in order to compute required coefficients again. When proper coefficients are stored in "Spouge.txt", evaluating 'calc_ck()' is not needed.


=================================================================


## Some examples of possible expressions


**Expression,					    Result**


1/agm(1,sqrt(2)) &nbsp;&nbsp;&nbsp;&nbsp;			         0.83462684167407318...

sqrt(2)! &nbsp;&nbsp;&nbsp;&nbsp;					 1.25381548064289168...

2^(1/3)	&nbsp;&nbsp;&nbsp;&nbsp;				         1.25992104989487316...

(-1.5)!	&nbsp;&nbsp;&nbsp;&nbsp;				        -3.54490770181103205...

2^100/3^50 &nbsp;&nbsp;&nbsp;&nbsp;					 1765780.963259017009...

ln(E^2+PI) &nbsp;&nbsp;&nbsp;&nbsp;					 2.354289934174038634...

-(2+5^2) &nbsp;&nbsp;&nbsp;&nbsp;					-27.00000000000000000...

2^2^2 &nbsp;&nbsp;&nbsp;&nbsp;						 16.00000000000000000...

sqrt(2)^sqrt(2) &nbsp;&nbsp;&nbsp;&nbsp;				         1.632526919438152844...


=================================================================


## Changing precision
Inside the file "bigfloat.h" you can find following global constants that can be modified:


const int DP = 550;                 /* precision of all arithmetics operations */

const int print_DP = 400;           /* number of digits that are printed into console as a result of expression */

#define g 320                       /* number of coefficients used in Spouge's formula for gamma function */


=================================================================


## Errors
Program outputs `mismatched parentheses` (weak bracketing) and `unidentified character` (any other not-defined expression) errors without terminating.


=================================================================


## Linux
Library <windows.h> used to evaluate duration of computation of expressions doesn't exist in Linux OS. In order to compile, one needs to comment lines number 7, 210, 265 (lines 210 and 265 use `GetTickCount()` function). After that, it's possible to compile the program by typing `g++ main.cpp bigfloat.cpp bigfloat_enhanced.cpp` in terminal, what creates a file `a.out`, which can be run by typing `./a.out`.
