#include <stdio.h>
#include <stdlib.h>

void main()
{
	int list[5];		// int형 배열 list 선언
	int *plist[5];		// int형 포인터 배열 plist 선언

	list[0] = 10;		// list[0]에 10 할당
	list[1] = 11;		// list[1]에 11 할당

	plist[0] = (int*)malloc(sizeof(int));			// plist[0]에 int의 크기만큼의 메모리를 할당받는다.

	printf("[----- [ 권 동 천 ]  [ 2017308072 ] -----)\n\n");

	printf("list[0] \t= %d\n", list[0]);					// list[0]의 값 출력
	printf("address of list \t= %p\n", list);				// 배열 변수 list의 시작주소 출력
	printf("address of list[0] \t= %p\n", &list[0]);		// list[0]의 주소값 출력
	printf("address of list + 0 \t= %p\n", list + 0);		// list + 0, list[0]의 주소
	printf("address of list + 1 \t= %p\n", list + 1);		// list + 1, list[1]의 주소
	printf("address of list + 2 \t= %p\n", list + 2);		// list + 2, list[2]의 주소
	printf("address of list + 3 \t= %p\n", list + 3);		// list + 3, list[3]의 주소
	printf("address of list + 4 \t= %p\n", list + 4);		// list + 4, list[4]의 주소
	printf("address of list[4] \t= %p\n", &list[4]);		// list[4]의 주소값 출력

	free(plist[0]);		// plist[0]에 동적할당을 통해 확보했던 메모리 해제
}
