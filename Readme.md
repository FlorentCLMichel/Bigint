### Sumary

A simple library for doing arithmetic operations on non-negative integers with arbitrary size. Integers are implemented as vectors of digits. 
This implementation is not designed with efficiency in mind and is rather slow compared with dedicated libraries. 
Instead, it is aimed at showing how arbitrary-size arithmetic can be performed using a simple approach. 
The library is designed to work with bases between 2 and 62, using digits between 0 and 9 then capital Latin letters and then lowercase letters. 
Larger bases may work, but could give unexpected results. 
All operations involving two Bigints assume they are written in the same base.

It currently implements comparison of two Bigints, addition, subtraction, multiplication, Euclidean division, modulo, exponentiation by an integer, summation of the digits, primality test, and a simple algorithm to find the first prime numbers.

### Use

The library implements the class `Bigint` with some basic arithmetic operations. 

It comes with a few tests in the file `test_BigInt.cpp`. 
To compile the test program on Linux, run `make` from within the repository directory. 
The resulting executable can be run in a console with one argument between 2 and 62 included, determining the base. 
If no argument is given, the base 10 is used.
