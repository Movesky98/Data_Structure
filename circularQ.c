/*
 * circularQ.c
 *
 */

// 여기서 내가 채워야 하는 것은?
// int isEmpty(QueueType *cQ)
// int isFull(QueueType *cQ)
// void enQueue(QueueType *cQ, element item)
// void deQueue(QueueType *cQ, element *item)

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4					    // Queue의 최대 크기 4

typedef char element;						      // char형 구조체 element 선언, 정의
typedef struct {							        // 구조체 QueueType 선언, 정의
	element queue[MAX_QUEUE_SIZE];			// queue의 저장되는 값은 문자형
	int front, rear;
}QueueType;


QueueType *createQueue();					  // Queue를 만들기 위한 함수
int isEmpty(QueueType *cQ);					// Queue가 비어있을 때 경고를 출력하기 위한 함수
int isFull(QueueType *cQ);					// Queue가 가득 차있을 때 경고를 출력하기 위한 함수
void enQueue(QueueType *cQ, element item);	// Queue에 값을 Push하기 위한 함수
void deQueue(QueueType *cQ, element* item);	// Queue에 저장된 값을 Pop하기 위한 함수
void printQ(QueueType *cQ);					// Queue에 저장되어있는 값들을 출력하기 위한 함수
void debugQ(QueueType *cQ);					// Queue에 관련된 변수 (queue에 저장되어있는 값, front, rear의 위치)의 값을 알려주는 함수

element getElement();						// Queue에 값을 넣기 전 어떤 값을 넣을지 입력받는 함수


int main(void)								// 메인함수 시작
{
	QueueType *cQ = createQueue();			// QueueType 구조체 포인터 cQ 선언 및 Queue 생성
	element data;							// 값을 입력받기 위한 변수 선언

	char command;							// 명령어를 입력받기 위한 변수 선언

	printf("[----- [Kwon Dong Cheon] [2017038072] -----]\n");

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);				// 명령어 입력

		switch(command) {
		case 'i': case 'I':					// command == i || command == I
			data = getElement();			// data에 값을 저장
			enQueue(cQ, data);				// data에 저장된 값을 queue에 Push
			break;							// switch 탈출
		case 'd': case 'D':					// command == d || command == D
			deQueue(cQ, &data);				// queue에 저장되어 있는 값을 하나 Pop
			break;							// switch 탈출
		case 'p': case 'P':					// command == p || command == P
			printQ(cQ);						// cQ에 저장되어 있는 값들을 출력
			break;							// switch 탈출
		case 'b': case 'B':					// command == b || command == B
			debugQ(cQ);						// debugQ() 실행
			break;							// switch 탈출
		case 'q': case 'Q':					// command == q || command == Q
			break;							// switch 탈출
		default:							// 잘못된 명령어를 입력할 경우
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");		// 경고메세지 출력
			break;							//switch 탈출
		}

	}while(command != 'q' && command != 'Q');	// command == q || command == Q이면 반복문을 빠져나온다


	return 1; // 프로그램 종료
}


QueueType *createQueue()						// Queue를 생성하기 위한 함수 정의
{
	QueueType *cQ;									// Queue를 생성하기 위해 구조체 포인터 cQ 선언
	cQ = (QueueType *)malloc(sizeof(QueueType));	// cQ에 QueueType 만큼의 공간을 동적 할당 받는다.
	cQ->front = 0;									// front 초기화
	cQ->rear = 0;									// rear 초기화
	return cQ;										// Queue를 생성하였으므로 cQ 반환
}

element getElement()								// 외부로부터 값을 입력받기 위한 함수 정의
{
	element item;									// 문자를 입력받을 구조체 변수 item 선언
	printf("Input element = ");						
	scanf(" %c", &item);							// 변수 item에 문자를 입력
	return item;									// item 반환
}


/* complete the function */
int isEmpty(QueueType *cQ)							// Queue가 비어있을 때 경고를 보내는 함수
{
    if(cQ->front == cQ->rear)						// Queue의 front 와 rear이 같으면
		return 1;									// 경고가 출력되기 위한 1 반환
    else return 0;									// 같지않으면 0을 반환
}

/* complete the function */
int isFull(QueueType *cQ)							// Queue가 꽉 채워져 있을 때 경고를 보내는 함수
{
	if(cQ->rear == cQ->front){						// Queue의 rear과 front가 같으면
		if(cQ->rear == 0 || cQ->front == 0){ 		// rear이 0이거나 front가 0이면
			cQ->rear = MAX_QUEUE_SIZE -1;			// rear에 MAX_QUEUE_SIZE -1을 저장한다.
		}
		else 										// 둘중 하나라도 0이 아니면
		cQ->rear = (cQ->rear - 1) % MAX_QUEUE_SIZE;	// rear에 (rear -1) % MAX_QUEUE_SIZE를 저장한다
		return 1;									// 이후 경고 출력을 위해 1 반환
	}
	else return 0;									// 아닐경우 0 반환
}


/* complete the function */
void enQueue(QueueType *cQ, element item)			// Queue에 원소를 Push 위한 함수 정의
{
	cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;		// 원소를 넣으면 rear의 값이 증가해야 하므로
    if(isFull(cQ)){									// isFull() 함수 호출 반환되는 값이 참값이면
        printf("Circular Queue Is Full!");			// 꽉 채워져 있을 경우 경고 출력
    }
	else{
    	cQ->queue[cQ->rear] = item;					// 꽉 채워져있지 않을경우 Queue에 원소를 Push
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)			// Queue에 저장된 원소를 Pop하기 위한 함수 정의
{
	
    if(isEmpty(cQ)){								// isEmpty()함수 호출, 반환되는 값이 참이면
        printf("Circular Queue Is Empty!");;		// 비워져있을 경우 경고 출력
    }
	else {												// 원소가 들어있을 경우
    	cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;	// front값을 증가시키고 (Pop을 하기위해)
		cQ->queue[cQ->front] = '\0';					// Pop하여 원소를 빼냄
	}
}


void printQ(QueueType *cQ)						// Queue에 들어있는 원소를 출력하기 위한 함수
{
	int i, first, last;							// front의 위치를 나타내기 위한 변수, rear의 위치를 나타내기 위한 변수 선언

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;		// first에 front의 위치를 저장
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;		// last에 rear의 위치를 저장

	printf("Circular Queue : [");				// 아래로는 Queue에 저장된 원소들을 차례로 출력

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)									// Queue에 저장된 원소, front, rear의 위치를 나타내기 위한 함수 정의
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);					// i가 front의 위치와 같을 경우 front출력
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);			// queue에 저장된 원소들을 출력

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);	// front와 rear의 위치 출력
}

