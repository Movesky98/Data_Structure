#include <stdio.h>

struct student1 {			// struct 구조체 student1 선언
	char lastName;
	int studentId;
	char grade;
};

typedef struct {			// typedef를 이용해 struct 구조체 student2 선언
	char lastName;
	int studentId;
	char grade;
} student2;

int main()
{
	printf("[----- [ 권 동 천 ]  [ 2017038072 ] -----]\n\n");

	struct student1 st1 = {'A', 100, 'A'};				// 구조체 student1으로 변수 st1 선언 및 초기화

	printf("st1.lastName = %c\n", st1.lastName);		// st1.lastName 출력 (== A)
	printf("st1.studentId = %d\n", st1.studentId);		// st1.studentId 출력 (100)
	printf("st1.grade = %c\n", st1.grade);				// st1.grade 출력 (A)


	student2 st2 = {'B', 200, 'B'};						// 구조체 student2로 변수 st2 선언 및 초기화
														// student2는 typedef를 이용해 선언했으므로 굳이 struct를 붙여주지 않아도 된다.
	printf("\nst2.lastName = %c\n", st2.lastName);		// st2.lastName 출력 (== B)
	printf("st2.studentId = %d\n", st2.studentId);		// st2.studentId 출력 (== 200)
	printf("st2.grade = %c\n", st2.grade);				// st2.grade 출력 (== B)

	student2 st3;										// 구조체 student2로 변수 st3 선언

	st3 = st2;											// 변수 st3에 변수 st2의 데이터를 할당

	printf("\nst3.lastName = %c\n", st3.lastName);		// st3.lastName 출력 (== st2.lastName)
	printf("st3.studentId = %d\n", st3.studentId);		// st3.studentId 출력(== st2.studentId)
	printf("st3.grade = %c\n", st3.grade);				// st3.grade 출력 (== st2.grade)


	/*equality test*/
	/*
	if(st3 == st2)					//st3와 st2가 같으면
		printf("equal\n");			// 같다고 출력
	else							// 아니면
		printf("not equal\n");		// 다르다고 출력
	 */

	return 0;						// 프로그램 종료.
}
