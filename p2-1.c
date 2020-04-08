#include <stdio.h>

#define MAX_SIZE 100		// MAX_SIZE == 100

float sum(float [], int);		// 배열들의 합을 확인하기 위한 함수 sum 선언

float input[MAX_SIZE], answer;	// float형 전역변수 배열 input과 float형 전역변수 answer 선언
int i;							// int형 전연변수 i 선언

void main(void)
{
	for(i=0; i<MAX_SIZE; i++)						// i=0 ~ i=100 까지  배열 input에
		input[i] = i;								// 1씩 증가하면서 할당 예) input[0] = 0, input[1] = 1...

	printf("[----- [ 권 동 천 ]  [ 2017038072 ] -----]\n\n");

	/*for checking call by reference */
	printf("address of input = %p\n", input);		// 배열 input의 시작 주소 출력

	answer = sum(input, MAX_SIZE);					// 배열의 합을 계산하는 sum을 이용해 나온 값을 변수 answer에 할당
	printf("The Sum is : %f\n", answer);			// 배열의 합 answer 출력
}

float sum(float list[], int n)			// 배열들의 합을 확인하기 위한 함수 sum 정의
{
	printf("value of list = %p\n", list);		// 매개변수로부터 받은 list의 값 출력 이때, 배열의 시작주소를 매개변수로 받는다.
	printf("address of list = %p\n\n", &list);	// float 배열 list의 주소값 출력

	int i;						// int형 지역번수 i 선언
	float tempsum = 0;			// 배열들의 합을 계산하기위한 float형 지역변수 tempsum 선언과 초기화
	for(i=0;i<n;i++)			// i=0~i<n까지 반복문 계산
		tempsum += list[i];		// tempsum에 배열들의 합을 할당

	return tempsum;				//  tempsum 반환
}
