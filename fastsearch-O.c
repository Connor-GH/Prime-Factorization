#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <gmp.h>

#include "fastsearch-O.h"

static size_t size;
static size_t *prime_nums;

static inline void do_prime(void) {
	size_t j = 0;
	for (size_t i = 11; j < size; i+=2) {
		if ((i % 3 == 0) ||
		(i % 5 == 0) ||
		(i % 7 == 0)) {
		} else {
			bool encountered = false;
			for (size_t k = 0; k < j; k++) {
				if (i % prime_nums[k] == 0) {
					encountered = true;
					break;
				}
			}
			if (!encountered) {
				prime_nums[j] = i;
				j++;
			}
		}
	}
}


void throw(void) {
	fprintf(stderr, "Requires argument in the form of a 'long long'.\n"
			"This argument is the number of prime factors you want in "
			"your number, starting from the first factor being \"2\".\n");
	exit(1);
}


static __attribute__((noreturn)) void printf_noreturn(size_t num) {
	printf("%lu\n", num);
	exit(1);
}

// Incidentally, this is a prime factorization finder in the
// pattern of 2 * 3 * 5 * 7 * 11 * ...
//
// Its main purpose is to find numbers that are divisible by
// every one of the first few primes.
//
// Each number doubles its amount of divisors, with
// the amount of divisors being 2 to the power of the distinct prime factors,
// not counting 1.
//
// These numbers are very predictable. Multiply primes together to
// get the numbers naturally. This is just a quadratic, provable way
// of doing this.
int main(int argc, char **argv) {
	size_t num = 0;
	if (argc > 1) {
		num = strtol(argv[1], NULL, 10);
		if (num == 1) printf_noreturn(2);
		if (num == 2) printf_noreturn(2*3);
		if (num == 3) printf_noreturn(2*3*5);
		if (num == 4) printf_noreturn(2*3*5*7);
		if ((num != LONG_MAX) && (num > 0)) {
			size = num-4;
		} else {
			throw();
		}
	} else {
		throw();
	}
	prime_nums = malloc(sizeof(size_t) * size);
	do_prime();


	size_t j = 0;
	mpz_t i, j_mpz, num_gmp, num_two, ten, mod;
	mpz_init_set_ui(i, 2*3*5*7);
	mpz_init(j_mpz);
	mpz_init_set_ui(num_gmp, num);
	mpz_init_set_ui(num_two, 2U);
	mpz_init_set_ui(ten, 10U);
	mpz_init_set_str(mod, BASICALLY_INFINITY
		, 10);
	for (i; j < size; j++) {
		//i *= prime_nums[j];
		mpz_set_ui(j_mpz, prime_nums[j]);
		mpz_mul(i, i, j_mpz);
	}

	mpz_powm(num_two, num_two, num_gmp, mod);
	gmp_printf("Number: %Zd\n"
			"Number of factors: %lu\n"
			"Number of divisors: %Zd\n",
			i, num, num_two);
	mpz_clears(i,
	j_mpz,
	num_gmp,
	num_two,
	ten,
	mod, NULL);
	free(prime_nums);
	exit(0);
}

