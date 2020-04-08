# Tutorial-Chunbuk
for the Tutorial
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int list[5];							// int형 배열 list 선언
	int *plist[5] = {NULL,};				// int형 포인터 배열 plist 선언 및 초기화

	plist[0] = (int *)malloc(sizeof(int));	// 포인터 배열 plist[0]에 int의 크기만큼 메모리 동적 할당

	list[0] = 1;							// list[0]에 1 할당
	list[1] = 100;							// list[1]에 100 할당

	*plist[0] = 200;						// 메모리 공간을 할당 받았던 plist[0]에 역 참조를 시켜 200 할당

	printf("[----- [ 권 동 천 ]  [ 2017038072 ] -----]\n\n");

	printf("value of list[0] = %d\n", list[0]);					// list[0]의 값 출력
	printf("address of list[0]			= %p\n", &list[0]);		// list[0]의 주소값 출력
	printf("value of list				= %p\n", list);			// list의 시작 주소 출력
	printf("addresss of list (&list)	= %p\n", &list);		// list의 주소값 (시작주소) 출력

	printf("--------------------------------------------\n\n");
	printf("value of list[1]	= %d\n", list[1]);				// list[1]의 값 출력
	printf("address of list[1] 	= %p\n", &list[1]);				// list[1]의 주소값 출력
	printf("value of *(list + 1)= %d\n", *(list+1));			// (list + 1)에 역 참조를 시킨 값 출력 (== list[1])
	printf("address of list + 1 = %p\n", list+1);				// list + 1, 배열 list의 인덱스 1에서의 주소값 출력

	printf("--------------------------------------------\n\n");

	printf("value of *plist[0]	= %d\n", *plist[0]);			// plist[0]를 역참조를 하여 plist[0]의 메모리 안에 들어있던 값 출력
	printf("&plist[0]			= %p\n", &plist[0]);			// plist[0]의 주소값 출력
	printf("&plist				= %p\n", &plist);				// plist의 주소 출력 (== &plist[0])
	printf("plist				= %p\n", plist);				// 포인터 배열 변수 plist의 시작 주소 출력 (== &plist, &plist[0])
	printf("plist[0]			= %p\n", plist[0]);				// plist[0]이 가리키는 주소값 출력			plist[0]은 앞에서 먼저 동적 할당을 해주었으므로 동적할당을 받은 메모리의 주소가 들어있다.
	printf("plist[1]			= %p\n", plist[1]);				// plist[1]이 가리키는 주소값 출력
	printf("plist[2]			= %p\n", plist[2]);				// plist[2]이 가리키는 주소값 출력			여기서 plist[1] ~ plist[4] 까지는 NULL로 초기화를 했으므로  000000000이 출력된다.
	printf("plist[3]			= %p\n", plist[3]);				// plist[3]이 가리키는 주소값 출력
	printf("plist[4]			= %p\n", plist[4]);				// plist[4]이 가리키는 주소값 출력

	free(plist[0]);				// plist[0]이 동적 할당으로 확보했던 메모리 해체

	return 0;					// 프로그램 종료
}
