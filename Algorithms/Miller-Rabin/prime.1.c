#include<stdio.h> /* printf */
#include<stdlib.h> /* atoi, srand, rand */
#include<time.h> /* time */
#include<math.h> /* pow */
#include<gmp.h>

#include "prime.h"

void randrange(mpz_t* n, mpz_t* m, mpz_t* r){
    /* Inclusif */
    mpz_t d;
    mpz_set_si(r, rand());
    mpz_init(d);

    /* (m - n + 1) */
    mpz_sub(d, *m, *n);
    mpz_add_ui(d, *r, 1);
    
    /* r % d + n */
    mpz_mod(*r, *r, d);
    mpz_add(*r, *r, *n);

    /* Free */
    mpz_clear(d);
    
    // return rand() % (m - n + 1) + n;
}

static int factor_of_two(int n){
    int c = 0;

    while(n % 2 == 0){
        n /= 2;
        c += 1;
    }
    return c;
}

static void calculate_s_and_d(int p, int* s, int* d){
    *s = factor_of_two(p - 1);
    *d = (p - 1)/(int)pow(2, *s);
}

static int temoin_de_miller(int a, int n){
    int s;
    int d;
    calculate_s_and_d(n, &s, &d);

    mpz_t x;
    mpz_init(x);

    mpz_ui_pow_ui(x, (unsigned int)a, (unsigned int)d);
    mpz_mod_ui(x, x, (unsigned int)n);

    /* x == 1 || x == n - 1 */
    if( mpz_cmp_si(x, 1) == 0 || mpz_cmp_si(x, n - 1) == 0){
        return 0;
    }
    
    while(s > 1){
        mpz_pow_ui(x, x, 2);
        mpz_mod_ui(x, x, (unsigned int)n);
        if( mpz_cmp_si(x, n - 1) == 0 ){
            mpz_clear(x);
            return 0;
        }
        s -= 1;
    }
    mpz_clear(x);
    return 1;
}

static int miller_rabin(int n, int k){
    int a;

    for(int i = 0; i<k; i++){
        a = randrange(2, n - 2);

        if(temoin_de_miller(a, n)){
            return 0;
        }
    }
    return 1;
}

static void init(){
    static int instance = 0;

    if(!instance){
        srand(time(NULL));
        instance = 1;
    }
}

int isPrime(int n){
    init();

    int k = 100;
    return miller_rabin(n, k);
}
