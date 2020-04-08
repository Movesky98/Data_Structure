#include <stdio.h>
#include <stdlib.h>

int main()
{
	int **x;										// int형 이중 포인터 변수 x 선언

	printf("[----- [ 권 동 천 ]  [ 2017038072 ] -----]\n\n");

	printf("sizeof(x) = %u\n", sizeof(x));			// 이중 포인터 변수 x가 가리키는 주소의 크기 출력
	printf("sizeof(*x) = %u\n", sizeof(*x));		// 이중 포인터 변수 x를 역참조 한 값의 크기 출력(== x가 가리키는 포인터 변수에 들어있는 (포인터 변수가 가리키는) 주소 값)
	printf("sizeof(**x) = %u\n", sizeof(**x));		// 이중 포인터 변수 x에 2번 역참조를 하였으므로 주소안에 들어있는 값 (int형 데이터)의 크기 출력

	return 0;
}
