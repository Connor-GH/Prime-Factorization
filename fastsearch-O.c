#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <gmp.h>

//#define size 3

static size_t size;
static size_t *prime_nums;

static inline void do_prime(void) {
	size_t j = 0;
	for (size_t i = 11; j < size; i+=2) {
		if ((i % 3 == 0) ||
		(i % 5 == 0) ||
		(i % 7 == 0) ||
		(i % 9 == 0)) {
		} else {
			prime_nums[j] = i;
			j++;
		}
	}
}


void throw(void) {
	fprintf(stderr, "Requires argument in the form of a 'long long'.\n");
	exit(1);
}


// Incidentally, this is a prime factorization finder in the
// pattern of (2^2) * 3 * 5 * 11 * ...
//
// Its main purpose is to find numbers that are divisible by
// every one of the first few primes.
//
// Each number doubles its amount of divisors, with
// the 6th iteration having 768, 7th having 1536, 8th having 3072...
//
// These numbers are very predictable. Multiply primes together to
// get the numbers naturally. This is just a quadratic, provable way
// of doing this.
int main(int argc, char **argv) {
	size_t num = 0;
	if (argc > 1) {
		num = strtol(argv[1], NULL, 10);
		if (num != LONG_MAX) {
			size = num;
		} else {
			throw();
		}
	} else {
		throw();
	}
	prime_nums = malloc(sizeof(size_t) * size);
	do_prime();


	size_t j = 0;
	mpz_t i, j_mpz;
	mpz_init_set_ui(i, 2*2*3*5);
	mpz_init(j_mpz);
	for (i; j < size; j++) {
		//i *= prime_nums[j];
		mpz_set_ui(j_mpz, prime_nums[j]);
		mpz_mul(i, i, j_mpz);
	}

	gmp_printf("%Zd\n", i);
	mpz_clear(i);
	free(prime_nums);
	exit(0);
}

