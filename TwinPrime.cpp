#include <stdio.h>
#include <iostream>
#include <omp.h>
using namespace std;

//Checks if the number is prime or not
bool isPrime(int n)
{
    // Corner cases
    if (n <= 1)  return false;
    if (n <= 3)  return true;

    // This is checked so that we can skip
    // middle five numbers in below loop
    if (n%2 == 0 || n%3 == 0) return false;
    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
            return false;

    return true;
}

// checks if the number supplied is prime by invoking isPrime() function
// returns 1 if number is prime, otherwise 0.
int countPrimes(int p) {
    int c = 0;

    if(isPrime(p)) {
        c++;
    }
    return c;
}


// Finds all twin prime numbers in a range from 1 to n
// This also invokes countPrimes() function and adds the output to count.
// pragma omp critical allows only one thread at a time to access that section
// of the code. This makes it so that no more than one thread has access to
// cout and countPrimes() function.
static void twinPrime(int range, int threads) {
    int count = 0;
    int countTwin = 0;

    #pragma omp parallel for num_threads(threads) reduction(+: count, countTwin)
    for (int i = 1; i < range; i++) {
        if(isPrime(i) && isPrime(i + 2)) {
            countTwin++;
            printf("%d %d \n", i, i+2);
        }
        count += countPrimes(i);
    }
    printf("Number of twin primes between 1 and %d is %d \n", range, countTwin);
    printf("Number of Primes: %d", count);
}

int main(int argc, char *argv[]) {
    // num is first argument.
    int num = atoi(argv[1]);
    // threads is second argument.
    int threads = atoi(argv[2]);
    twinPrime(num, threads);
    return 0;
}
