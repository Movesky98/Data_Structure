#include <stdio.h>

struct student {								// struct 구조체 student 선언
	char lastName[13];			/* 13bytes */
	int studentId;				/* 4bytes */
	short grade;				/* 2bytes */
};

int main()
{
	struct student pst;			// 구조체 student로 변수 pst 선언

	printf("[----- [ 권 동 천 ]  [ 2017038072 ] -----]\n\n");

	printf("size of student = %u\n", sizeof(struct student));		// 구조체 student의 크기 출력
																	// 이때, 채워넣기(Padding)으로 인해
																	// lastName[13]에는 전체 16bytes 중 13bytes,
																	// grade에는 4bytes 중 2bytes만큼의 공간이 있어
																	// 나머지 빈 메모리공간에는 Padding을 하는 것을 볼 수 있다.

	printf("size of int = %u\n", sizeof(int));						// 데이터 타입 int의 크기 출력
	printf("size of short = %u\n", sizeof(short));					// 데이터 타입 short의 크기 출력

	return 0;			// 프로그램 종료.
}
