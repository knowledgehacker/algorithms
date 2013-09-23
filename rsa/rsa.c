#include <math.h>
#include <stdio.h>

/*
 * 1. Pick up two large prime numbers, p and q.
 * 2. Use n = p * q as the public key modulus.
 * 3. Calculate phi(n) = number of "{k | 1 <= k < n, gcd(k,n) = 1}".
 * 4. Find an integer e, such that 1 <= e <= phi(n), and gcd(e, phi(n)) = 1, use it as the public key exponent.
 * 5. Find d, such that d*e = 1 mod phi(n), use it as the private key.
 *
 * Encrypt value m as c = m^e mod n.
 * Decrypt value m as c^d mod n.
 */

#define PHI(p, q) ((p-1) * (q-1))

int modulus = 0;
int public_expo = 0;
int private_expo = 0;

void gen_key_pair(int p, int q) {
	p = find_least_big_prim_number(p);
	q = find_least_big_prim_number(q);
	printf("p: %d, q: %d\n", p, q);

	modulus = p * q;
	printf("modulus: %d\n", modulus);

	int phi = PHI(p, q);
	printf("phi: %d\n", phi);
	public_expo = gen_public_expo(phi);
	printf("public_expo: %d\n", public_expo);
	private_expo = 	gen_private_expo(public_expo, phi);
	printf("private_expo: %d\n", private_expo);
}

int find_least_big_prim_number(int n) {
	int i = n;
	while(1) {
		int is_prime = 1;
		for(int j = 2; j*j <= i; ++j)
			if(i%j == 0) {
				is_prime = 0;

				break;
			}

		if(is_prime)
			break;

		++i;
	}

	return i;
}

/*
 * As to two prime numbers p and q.
 * phi(n = p * q) = phi(p) * phi(q) = (p-1) * (q-1).
 */
int phi(int p, int q) {
	return (p-1) * (q-1);
}

/*
 * find e, such that 1 <= e <= phi, and e and phi is relatively prime. how to do it efficiently?
 */
int gen_public_expo(int phi) {
	if(phi % 2 != 0)
		return 2;

	if(phi % 3 != 0)
		return 3;

	for(int i = 2; i < phi; ++i) {
		int j = 2;
		while(j*j <= i) {
			if((i % j == 0) && (phi % j == 0))
				break;

			++j;
		}

		if(j*j > i)
			return i;
	}
}

int gen_private_expo(int public_expo, int phi) {
	int i = 1;
	while(1) {
		if((i * public_expo) % phi == 1)
			break;

		++i;
	}

	return i;
} 

/*
 * calculate n^e % modulus, how to do it efficiently?
 */
int expo_modulus(int n, int e, int modulus) {
	if(e == 1)
		return n % modulus;

	int min_expo = 1;
	int tmp = 1;
	while((tmp *= n) < modulus)
		++min_expo;
	//printf("n: %d, min_expo: %d, tmp: %d\n", n, min_expo, tmp);

	int new_n = tmp % modulus;
	int new_e = e / min_expo;

	int xx = expo_modulus(new_n, new_e, modulus);
	
	int e_rem = e % min_expo;
	for(int i = 0; i < e_rem; ++i)
		xx *= n;

	return xx % modulus;
}

int encrypt(int msg) {
	return expo_modulus(msg, public_expo, modulus);
}

int decrypt(int encrypted_msg) {
	return  expo_modulus(encrypted_msg, private_expo, modulus);
}

int main(int argc, char** argv) {
	int p = 15, q = 24;
	gen_key_pair(p, q);

	int msg = 321;
	int encrypted_msg = encrypt(msg);
	printf("encrypted_msg: %d\n", encrypted_msg);
	int decrypted_msg = decrypt(encrypted_msg);
	printf("decrypted_msg: %d\n", decrypted_msg);

	return 0;
}
