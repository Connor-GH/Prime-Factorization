import std.stdio : writeln;
static size_t size = 1;

static ulong[] prime_nums;

static void do_prime() {
	size_t j = 0;
	for (ulong i = 11; j < size; i+=2) {
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

static bool num_divisible(ulong num) {
	//same as result = (num % 4 == 0) && (num % 5 == 0) &&
	//(num % 6 == 0);  ... just returns a number 1/10th the size
	bool result = (num % 20 == 0) | (num % 6 == 0);

	for (size_t i = 0; (i < size); i++) {
		result = result && (num % prime_nums[i] == 0);
		if (result == 0)
			break;
	}
	return result;

}
int main(string[] args) {
	if (args.length > 1) {
		import std.conv : to;
		size = to!size_t(args[1]);
		prime_nums.reserve(size);
	}
	do_prime();
	ulong i = 2;
	for (i = i; (i < 18_000_000_000_000_000); i+=2) {
		if (num_divisible(i))
			break;
	}
	writeln(i*10);
	return 0;

}

