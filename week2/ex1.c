#include <limits.h>
#include <float.h>
#include <stdio.h>

int main() {
	int a;
	float b;
	double c;
	a = INT_MAX;
	b = FLT_MAX;
	c = DBL_MAX;
	printf("size a - %lu, value = %d\n", sizeof(a), a);
	printf("size b - %lu, value = %f\n", sizeof(b), b);
	printf("size c - %lu, value = %lf\n", sizeof(c), c);
	return 0;
}
