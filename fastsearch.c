#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

//#define size 3

static size_t size;
static size_t *prime_nums;

static inline void do_prime(void) {
	size_t j = 0;
	for (size_t i = 11; j < size; i+=2) {
		if ((i % 3 == 0) ||
		(i % 5 == 0) ||
		(i % 7 == 0) ) {
		} else {
			prime_nums[j] = i;
			j++;
		}
	}
}


static __attribute__((always_inline)) __attribute__((pure)) bool num_divisible(size_t num) {
//	bool result = (num % 4 == 0) && (num % 5 == 0) &&
//		(num % 6 == 0);

	bool result = (num % 20 == 0) | (num % 6 == 0);

	for (size_t i = 0; i < size; i++) {
		result &= (num % prime_nums[i] == 0);
		if (result == 0)
			break;
	}

	return result;
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
	size_t i = 2;
	prime_nums = malloc(sizeof(size_t) * size);
	do_prime();

	for (i; i < 18000000000000000; i+=2) {
		if (num_divisible(i)) {
			break;
		}
	}
	printf("%lu\n", i*10);
	free(prime_nums);
	exit(0);
}

