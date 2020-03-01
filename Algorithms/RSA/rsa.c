#include<stdio.h>
#include<stdlib.h>
#include<gmp.h>
#include<sys/random.h>

struct private_key {
    mpz_t n;
    mpz_t d;
};

struct public_key {
    mpz_t n;
    mpz_t e;
};

unsigned long int* get_seed(){
    unsigned long int* buf = NULL;
    size_t bufsz = sizeof(unsigned long int);

    buf = malloc(bufsz);

    getrandom(buf, bufsz, GRND_RANDOM);

    return buf;
}

static void get_p_q(mpz_t p, mpz_t q){
    /* Var init */
    gmp_randstate_t state;
    gmp_randinit_mt(state);

    /* Seeding */
    unsigned long int* seed = get_seed();
    gmp_randseed_ui(state, *seed);

    /* Generation */
    mpz_urandomb(p, state, 1024);
    if(!(mpz_probab_prime_p(p, 25))){
        mpz_nextprime(p, p);
    }
    
    mpz_urandomb(q, state, 1024);
    if(!(mpz_probab_prime_p(q, 25))){
        mpz_nextprime(q, q);
    }

    /* Free */
    gmp_randclear(state);
    free(seed);
}

static void module_de_chiffre(mpz_t p, mpz_t q, mpz_t n){
    mpz_mul(n, p, q);
}

static void indicatrice_euler(mpz_t p, mpz_t q, mpz_t phi){
    /* Var init */
    mpz_t _p;
    mpz_t _q;
    mpz_inits(_p, _q, NULL);

    /* (p - 1) && (q - 1) */
    mpz_sub_ui(_p, p, 1);
    mpz_sub_ui(_q, q, 1);

    /* phi(n) = (p - 1)(q - 1) */
    mpz_mul(phi, _p, _q);

    /* Free */
    mpz_clears(_p, _q, NULL);
}

static void get_e(mpz_t phi, mpz_t e){
    /* Var init */
    mpz_t gcd;
    mpz_init(gcd);

    /* Seeding state */
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    unsigned long int* seed = get_seed();
    gmp_randseed_ui(state, *seed);

    /* Find e */
    do{
        mpz_urandomm(e, state, phi);
        mpz_gcd(gcd, e, phi);

    }while(mpz_cmp_ui(gcd, 1) != 0);

    /* Free */
    mpz_clear(gcd);
    gmp_randclear(state);
    free(seed);
}

static void get_d(mpz_t a, mpz_t b, mpz_t d){
    mpz_invert(d, a, b);
}

void encrypt(mpz_t m, struct public_key k, mpz_t c){
    mpz_powm(c, m, k.e, k.n);
}

void decrypt(mpz_t c, struct private_key k, mpz_t m){
    mpz_powm(m, c, k.d, k.n);
}

void generate_keys(struct public_key* pb, struct private_key* pv){
    /* Var init */
    mpz_t p, q, n, phi, e, d;
    mpz_inits(p, q, n, phi, e, d, NULL);

    /* p et q sont premiers */
    get_p_q(p, q);
    //mpz_set_ui(p, 3);
    //mpz_set_ui(q, 11);
    /* n = pq */
    module_de_chiffre(p, q, n);
    /* phi(n) = (p - 1)(q - 1) */
    indicatrice_euler(p, q, phi);
    get_e(phi, e);
    //mpz_set_ui(e, 3);
    /* d = inverse de e % phi(n) */
    get_d(e, phi, d);

    /* Setting the keys */
    mpz_init_set(pb->n, n);
    mpz_init_set(pb->e, e);

    mpz_init_set(pv->n, n);
    mpz_init_set(pv->d, d);

    /* Free */
    mpz_clears(p, q, n, phi, e, d, NULL);
}
