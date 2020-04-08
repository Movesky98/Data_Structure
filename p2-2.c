#include <stdio.h>

void print1(int *ptr, int rows);		// 배열의 각 인덱스에 해당하는 주소를 출력하기 위한 print1 함수 선언

int main()				// 함수시작
{
	int one[] = {0, 1, 2, 3, 4};		// int형 배열 one[]의 선언과 각 인덱스에 데이터를 할당

	printf("[----- [ 권 동 천 ]  [ 2017038072 ] -----]\n\n");

	printf("one		= %p\n", one);		// int형 배열 one[]의 시작주소 출력
	printf("&one	= %p\n", &one);		// int형 배열 one[]의 주소 출력
	printf("&one[0]	= %p\n", &one[0]);	// int형 배열 one[0]의 주소 출력

	print1(&one[0], 5);			// 각 인덱스에 해당하는 배열의 주소를 출력하기 위해 print1 실행
	return 0;
}

void print1(int *ptr, int rows)			// 배열의 인덱스에 따른 주소를 출력하기 위한 print1 함수 정의
{
	/* print out a one-dimensional array using a pointer*/

	int i;								// int형 변수 i 선언
	printf("Address \t Contents\n");

	for(i=0;i<rows;i++)					// i=0 ~ i<rows까지 반복문 계산
		printf("%p \t %5d\n", ptr + i, *(ptr + i));		// 배열을 매개변수로 받은 포인터 변수 ptr이 가리키는 주소와
														// 그 주소에 담겨있는 데이터 값을 출력
	printf("\n");
}
