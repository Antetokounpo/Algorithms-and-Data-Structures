#include<stdio.h>
#include<gmp.h>
#include "prime.h"

int main(){
    int n = 15485864;

    mpz_t x;
    mpz_init_set_si(x, n);

    printf("%d\n", mpz_probab_prime_p(x, 15));   

    return 0;
}