// main.cpp

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#define MAXSIZE 100000

static int origin[MAXSIZE], result[MAXSIZE];
static int N, QueryCount;

extern void array_restore(int N, int result[]);

// ISO9899
static unsigned long int next = 1;
static int rand(void) // RAND_MAX assumed to be 65535
{
	next = next * 1103515245 + 12345;
	return (unsigned int)(next >> 16) & 65535;
}

int orderCheck(int left, int right)
{
	QueryCount++;
	if (left < 0 || left >= N) return 1;
	if (right < 0 || right >= N) return 1;
	if (origin[left] < origin[right]) return 1;
	else return 0;
}

inline void Swap(int&a, int&b) {
	int t = a; a = b; b = t;
}

static void init(int t)
{
	int i, j;
	QueryCount = 0;
	N = (t * 2000 - 1000) + rand() % 1000;
	for (i = 0; i < N; i++) {
		origin[i] = i + 1;
		result[i] = 0;
	}
	for (i = 0; i < N; i++) {
		j = (int)((long long)rand() * rand() % N);
		Swap(origin[i], origin[j]);
	}
}

static int arr_comp()
{
	if (QueryCount >= N * 20) return MAXSIZE * 100;
	for (int i = 0; i < N; i++) {
		if (origin[i] != result[i]) return MAXSIZE * 100;
	}
	return QueryCount;
}

int main(void)
{
	for (int tc = 1; tc <= 50; tc++)
	{
		init(tc);
		array_restore(N, result);
		printf("#%d %d %d\n", tc, N, arr_comp());
	}

	return 0;
}