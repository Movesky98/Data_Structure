/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);    // 정렬에 표현될 배열을 만들어주기 위한 함수
int freeArray(int *a);      // 프로그램이 종료될 때, 할당받은 동적 메모리를 해제해주기 위한 함수
void printArray(int *a);    // array의 원소를 출력하는 함수

int selectionSort(int *a);  // 선택 정렬을 표현하기 위한 함수
int insertionSort(int *a);  // 삽입정렬을 표현하기 위한 함수
int bubbleSort(int *a);     // 버블 정렬을 표현하기 위한 함수
int shellSort(int *a);      // shell정렬을 표현하기 위한 함수
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에 대한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;               // 명령어를 받기위한 변수 command
	int *array = NULL;          // 정렬에서 표현될 포인터 array
	int *hashtable = NULL;      // 해시 테이블을  표현할 포인터 변수 hashtable
	int key = -1;               // key값을 입력받기 위한 변수 key
	int index = -1;             // hashtable에서 key를 찾아 index로 반환받기 위한 변수 index

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);         // 명령어 입력

		switch(command) {
		case 'z': case 'Z':             // z or Z를 입력받으면
			initialize(&array);         // initialize()함수 실행
			break;
		case 'q': case 'Q':             // q or Q를 입력받으면
			freeArray(array);           // freeArray()함수 실행
			break;
		case 's': case 'S':             // s or S를 입력받으면
			selectionSort(array);       // selectionSort()함수 실행
			break;
		case 'i': case 'I':             // i or I를 입력받으면
			insertionSort(array);       // insertionSort()함수 실행
			break;
		case 'b': case 'B':             // b or B를 입력받으면
			bubbleSort(array);          // bubbleSort()함수 실행
			break;
		case 'l': case 'L':             // l or L를 입력 받으면
			shellSort(array);           // shellSort() 함수 실행
			break;
		case 'k': case 'K':             // k or K를 입력받으면
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);          // 퀵 정렬을 하기 전, 배열에 입력된 원소들을 출력
			quickSort(array, MAX_ARRAY_SIZE);       // quickSort()함수 실행
			printf("----------------------------------------------------------------\n");
			printArray(array);          // 이후 변화된 모습을 다시 출력

			break;

		case 'h': case 'H':             // h or H를 입력받으면
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);          // array를 출력한 후
			hashing(array, &hashtable); // 데이터를 해시테이블에 저장하는 함수 호출
			printArray(hashtable);      // 이후 해시테이블의 들어간 데이터들의 원소값 출력
			break;

		case 'e': case 'E':             // e or E를 입력받으면
			printf("Your Key = ");
			scanf("%d", &key);          // key값을 입력 받고
			printArray(hashtable);      // 해시테이블에 저장되어있는 원소들을 출력
			index = search(hashtable, key); // 해시테이블의 key를 찾아 index에 저장
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':             // p or P를 입력받으면
			printArray(array);          // array에 들어있는 원소들을 출력
			break;
		default:                        // 다른 명령어를 입력할 경우
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");  // 오류 메세지 출력
			break;
		}

	}while(command != 'q' && command != 'Q'); // q or Q를 입력 받으면 함수를 빠져나온다.

	return 1;                           // 힘수 종료
}

int initialize(int** a)             // array가 인자로 들어온다.
{
	int *temp = NULL;               // 배열에 들어갈 원소(정수형)을 받을 포인터 변수 temp

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할 수 있도록 함 */
	} else
		temp = *a;

	/* 랜덤값을 배열값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;                   // 힘수 종료
}

int freeArray(int *a)           // 프로그램을 종료하기 전 할당받은 메모리를 해제해주기 위한 함수
{
	if(a != NULL)               // a가 비어있지 않으면
		free(a);                // 할당받았던 메모리를 해제
	return 0;                   // 힘수 종료
}

void printArray(int *a)         // array에 입력되어있는 원소들을 출력하기 위한 함수
{
	if (a == NULL) {            // array가 비어있으면
		printf("nothing to print.\n");      // 출력할 것들이 없다는 오류메세지 출력
		return;
	}

    /* 원소의 위치(인덱스)에 맞추어, 각 원소들의 값들을 출력 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);              
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)       // 선택 정렬 함수
{
	int min;                    // 최소값을 가리키는 변수 min
	int minindex;               // 최소값이 있는 위치(인덱스)를 가리키는 변수 minindex
	int i, j;                   // 반복문을 돌리기 위한 변수 i, j

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);              // 정렬을 하기 전, 순서에 따라 array의 원소들을 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;           // i번째 인덱스를 minindex에 저장
		min = a[i];             // i번째 인덱스에 있는 원소를 min에 저장
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)       // i+1부터 반복문을 실행
		{                                           // 최소값을 찾는다.
			if (min > a[j])         // 만약에 최소값을 찾으면 (min보다 작은 수를 찾으면)
			{
				min = a[j];         // 그 수를 min으로 지정
				minindex = j;       // 최소값이 위치해 있는  인덱스 값을 minindex로 지정
			}
		}

        /* 최소값을 찾았으므로 위치를 바꾸어준다. */
		a[minindex] = a[i];
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);      // 이후 정렬된 array의 원소들을 출력
	return 0;           // 힘수 종료
}

int insertionSort(int *a)           // 삽입 정렬 함수
{
	int i, j, t;                    // 반복분을 돌리기 위한 변수 i, j와 정렬을 하기 위한 변수 t

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);                  // 정렬을 하기 전, 순서에 따라 array의 원소들을 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];                   // i번째 인덱스의 원소를 t로 지정
		j = i;                      // i부터 반복문을 돌리기 위해 j = i 로 지정
		while (a[j-1] > t && j > 0) // j - 1번째 원소가 t보다 클 경우, j가 양수이면 while문을 실행한다.
		{
			a[j] = a[j-1];          // j번째 인덱스의 원소를 j-1번째 인덱스의 원소로 지정 (j-1번째 인덱스의 원소가 더 크기떄문)
			j--;                    // j--;
		}
		a[j] = t;                   // 이후 j = i-1이 되었으므로 
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);                  // 이후 정렬된 array의 원소들을 출력

	return 0;                       // 힘수 종료
}

int bubbleSort(int *a)              // 버블 정렬 함수
{
	int i, j, t;                    // 반복문을 돌리기 위한 변수 i, j와 더 작은 값을 나타내기 위한 변수 t

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);                  // array에 들어있는 원소들을 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++)         // 반복문 시작
	{                                           
		for (j = 1; j < MAX_ARRAY_SIZE; j++)    // i+1부터 반복문을 시작
		{
			if (a[j-1] > a[j])      // [j-1번째 인덱스의 원소]가 [j번째 인덱스의 원소] 보다 클 경우
			{
                /* [j-1번째 인덱스 원소]와 [j번째 인덱스의 원소]를 교체 */
				t = a[j-1];         
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);                  // array의 정렬된 원소들을 출력

	return 0;                       // 함수 종료
}

int shellSort(int *a)               // 셸 정렬 함수
{
	int i, j, k, h, v;              // 반복문을 나타내기 위한 변수 i, j와
                                    // 비교할 횟수를 나타낼 h,
                                    // j번째 인덱스의 원소를 가지고 비교할 v
                                    // 원소들의 크키를 비교할 k

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);                  // array의 원소들을 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) {      // h는 MAX_ARRAY_SIZE의/2 부터 반복문을 시작,
                                                        // h가 양수일떄까지, h에 나누기 2를 해주면서 반복문을 실행
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)      // j는 h의 간격만큼 비교하면서, 반복문을 실행
			{
				v = a[j];                           // j번째 인덱스의 원소를 v로 지정
				k = j;                              // k를 j로 지정하고
				while (k > h-1 && a[k-h] > v)       // k가 h-1보다 크고 array의 k-h번째 인덱스의 원소가 v보다 크면
                                                    // while문을 계속 실행
				{
                    /* [array의 k번째 인덱스의 원소]와 [array의 k-h번째 인덱스의 원소]를 교체한다. */
					a[k] = a[k-h];                  
					k -= h;
				}
				a[k] = v;           // 이때 k는 k-h이므로 a[k-h]에 v의 원소를 저장한다.
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);          // array의 정렬된 원소들을 출력

	return 0;               // 힘수 종료
}

int quickSort(int *a, int n)        // 퀵 정렬 함수, 처음엔 MAX_ARRAY_SIZE가 들어옴
{
	int v, t;                       // 반복문을 실행하며 나오는 원소들과 값을 비교할 v와 서로의 값을 변경할 때 임시로 값을 저장해놓을 t
	int i, j;                       // 반복문을 실행하면서 각 원소들의 인덱스의 위치를 표현할 i, j

	if (n > 1)                      // n이 1보다 크면
	{
		v = a[n-1];                 // v = a[n-1], v를 마지막 원소로 지정
		i = -1;                     // i는 -1로 지정
		j = n - 1;                  // j는 마지막 인덱스로 지정

		while(1)
		{
            /* v와 비교해 가면서 i, j의 값을 설정 */
			while(a[++i] < v);      // a[0]부터 반복문을 실행하되 a[i]가 v보다 크면 반복문을 빠져나옴
			while(a[--j] > v);      // a[MAX_ARRAY_SIZE - 1]부터 반복문을 실행하되 a[j]가 v보다 작으면 반복문을 빠져나옴

			if (i >= j) break;      // i와 j가 만나게 되면 while문을 탈출

            /* i와 j의 값을 교체 */
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}

        /* 이후 i와 n-1의 값을 교체한다. */
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);            // recursive한 방법으로 quickSort()함수 실행 이떄 n의 값으로 i를 저장
		quickSort(a+i+1, n-i-1);    // recursive한 방법으로 quickSort()함수 실행 이때, n의 값으로 i-1-1을 저장, 배열도 a+i+1 부터 시작하게 된다.
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;              // 해시테이블을 만들기 위한 포인터 변수 hashtavle

	/* hash table이 NULL인 경우 메모리를 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사  --> main에서 배열을 control 할 수 있도록 함 */
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌 경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

    /* 각 변수들 선언 및 초기화 */
	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];                 // key값에 a[i]의 값을 저장하고
		hashcode = hashCode(key);   // key값에 맞는 해시코드를 반환하여 hashcode에 저장
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)  // hashcode의 해시가 -1이면
		{
			hashtable[hashcode] = key;  // hashtable[hashcode]의 값을 a[i]로 지정
		} else 	{                       // hashcode의 해시가 -1이 아니면

			index = hashcode;           // index에 hashcode를 저장

			while(hashtable[index] != -1)   // 해시테이블의[index]가 -1이 될때까지
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; // index++을 해주면서 MAX_HASH_TABLE_SIZE를 넘어가지 않도록 조정
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;      // index의 해시를 key로 지정
		}
	}

	return 0;       // 함수 종료
}

int search(int *ht, int key) {     
	int index = hashCode(key);           // 입력된 key값에 맞는 해시 코드를 반환하여 저장 hashcode에 저장

    /* 이후 해시 테이블에서 key값을 찾으면 index를 리턴해준다.*/
	if(ht[index] == key)		// 해시테이블의 index 번째 원소가 key값과 같으면
		return index;			// index 리턴

	while(ht[++index] != key)	// index + 1 이 key와 같지 않으면
	{
		index = index % MAX_HASH_TABLE_SIZE;	// 증가한 인덱스가 MAX_HASH_TABLE_SIZE를 넘기지 않도록 하면서 증가
	}
	return index;				// 이후 찾으면 index를 리턴
}
