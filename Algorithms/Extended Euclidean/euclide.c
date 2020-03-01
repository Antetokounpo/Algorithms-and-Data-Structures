#include<gmp.h>


void euclide(mpz_t a, mpz_t b, mpz_t d){
    /* Algorithme d'Euclide étendu */

    mpz_t r, u, v, rp, up, vp, rs, us, vs, q;
    mpz_inits(r, u, v, rp, up, vp, rs, us, vs, q, NULL);

    mpz_set(r, a);
    mpz_set(rp, b);
    mpz_set_ui(u, 1);
    mpz_set_ui(v, 0);
    mpz_set_ui(up, 0);
    mpz_set_ui(vp, 1);

    while(mpz_cmp_ui(rp, 0) != 0){
        mpz_fdiv_q(q, r, rp);

        /* Variables de stockage */
        mpz_set(rs, r);
        mpz_set(us, u);
        mpz_set(vs, v);

        /* r = r' */
        mpz_set(r, rp);
        mpz_set(u, up);
        mpz_set(v, vp);

        /* r' = rs - q*r' */
        mpz_mul(rp, q, rp);
        mpz_sub(rp, rs, rp);


        /* u' = us - q*u' */
        mpz_mul(up, q, up);
        mpz_sub(up, us, up);

        /* v' = vs - q*v' */
        mpz_mul(vp, q, vp);
        mpz_sub(vp, vs, vp);
    }

    mpz_set(d, u);

    mpz_clears(r, u, v, rp, up, vp, rs, us, vs, q, NULL);
}