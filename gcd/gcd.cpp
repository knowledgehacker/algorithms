#include<vector>
#include<iostream>

void gcd_aux(const int a, const int b);

void gcd(const int a, const int b) {
	if(a < b)
		gcd_aux(b, a);
	else
		gcd_aux(a, b);
}

/**
 * Calculate the greatest common divisor for two integers, a and b using Euclid algorithm, that is, d = gcd(a, b).
 * And calculate the coefficients x and y, thus a*x + b*y = d.
 *
 * We know Eculid calculates the greatest common divisor for integers a and b using the following algorithm:
 * a = b*x1 + a1;		(1)
 * b = a1*x2 + a2;		(2)
 * ...
 * an-2 = an-1*xn + an;	(n)
 * an-1 = an*xn+1;		(n+1)
 * Then an is the largest common divisor for a and b.
 *
 * We use a vector to store all the quotients x1, x2, ..., xn+1, and another vector to store all the remainders a1, a2, ..., an.
 * From equation (n+1), we know an-1 can be divided by an, and from equation (n), we know an-2 can be divided by an, ...,
 * we know a2, a1 can also be divided by an.
 * And x2*(1) - (2), we get:
 * -x2*a + (1+x1x2)*b = a2 = X*an;
 * We let x = (-x2)/X, y = (1+x1*x2)/X, and d = gcd(a, b) = an, then a*x + b*y = d.
 * Thus x and y are the coefficients we want.
 */
void gcd_aux(const int a, const int b) {
	int tmp_a = a;
	int tmp_b = b;

	if(a < b) {
		int tmp = tmp_a;
		tmp_a = tmp_b;
		tmp_b = tmp;
	}

	std::vector<int> quotients;
	std::vector<int> remainders;

	while(true) {
		int quotient = tmp_a / tmp_b;
		quotients.push_back(quotient);
		int remainder = tmp_a % tmp_b;
		if(remainder == 0)
			break;
		remainders.push_back(remainder);

		tmp_a = tmp_b;
		tmp_b = remainder;
	}

	int x1 = quotients[0];
	int x2 = quotients[1];
	std::cout<<"x1: "<<x1<<std::endl;
	std::cout<<"x2: "<<x2<<std::endl;

	int a2 = remainders[1];
	int an = remainders[remainders.size()-1];
	std::cout<<"a2: "<<a2<<std::endl;
	std::cout<<"an: "<<an<<std::endl;

	int x = -x2 / (a2/an);
	int y = (1+x1*x2) / (a2/an);
	std::cout<<"x: "<<x<<std::endl;
	std::cout<<"y: "<<y<<std::endl;

	std::cout<<a<<"*"<<x<<"+"<<b<<"*"<<y<<": "<<a*x+b*y<<std::endl;
	std::cout<<"d: "<<an<<std::endl;
}

int main() {
	int a = 12;
	int b = 21;

	gcd(a, b);

	return 0;
}

