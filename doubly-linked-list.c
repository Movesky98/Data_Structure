/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {       // 노드를 표현하기 위한 구조체
	int key;                // 노드의 데이터 필드에 해당하는 변수 key
	struct Node* llink;     // 노드의 왼쪽 링크필드에 해당하는 포인터 변수 llink
	struct Node* rlink;     // 노드의 오른쪽 링크필드에 해당하는 포인터 변수 rlink;
} listNode;



typedef struct Head {       // 헤드노드를 표현하기 위한 구조체
	struct Node* first;     // 첫번째 노드를 가리키기 위한 포인터 변수 first
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할 것 */
int initialize(headNode** h);

/* note: freeList는 싱글 포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할 것
        - 이중 포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);       // 노드의 key값보다 큰 노드가 있을 경우, 그 앞에 삽입하는 함수
int insertLast(headNode* h, int key);       // 마지막 노드보다 뒤에 삽입하는 함수
int insertFirst(headNode* h, int key);      // 연결리스트의 첫번째에 노드를 삽입하는 함수

int deleteNode(headNode* h, int key);       // key값을 받아 해당하는 key값을 가진 노드를 삭제하는 함수
int deleteLast(headNode* h);                // 마지막 노드를 삭제하는 함수
int deleteFirst(headNode* h);               // 첫번째 노드를 삭제하는 함수

int invertList(headNode* h);                // 연결리스트의 순서를 역순으로 재배치하는 함수
void printList(headNode* h);                // 연결리스트에 들어있는 노드들을 순서대로 출력하는 함수


int main()
{
	char command;                           // 명령어를 입력받기 위한 변수 command
	int key;                                // key값을 받을 변수 key
	headNode* headnode = NULL;              // 연결리스트의 헤드노드가 될 포인터 변수 headnode

    printf("[----- [Kwon_DongCheon] [2017038072] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);             // 명령어 입력

		switch(command) {
		case 'z': case 'Z':                 // z or Z를 입력받으면
			initialize(&headnode);          // 연결리스트 초기화
			break;                          // switch문을 빠져나온다
		case 'p': case 'P':                 // p or P를 입력받으면
			printList(headnode);            // 연결리스트에 들어있는 노드들을 출력 
			break;                          // switch문을 빠져나온다
		case 'i': case 'I':                 // i or I를 입력받으면
			printf("Your Key = ");          
			scanf("%d", &key);              // key값 입력
			insertNode(headnode, key);      // 해당하는 key값보다 큰 값을 가진 노드 앞에 삽입
			break;                          // switch문을 빠져나온다
		case 'd': case 'D':                 // d or D를 입력받으면
			printf("Your Key = ");      
			scanf("%d", &key);              // key값 입력
			deleteNode(headnode, key);      // 해당하는 key값을 가진 노드 삭제
			break;                          // switch문을 빠져나온다
		case 'n': case 'N':                 // n or N을 입력받으면
			printf("Your Key = ");  
			scanf("%d", &key);              // key값 입력
			insertLast(headnode, key);      // 해당하는 key값을 가진 노드를 연결리스트 맨 뒤에 삽입
			break;                          // switch문을 빠져나온다
		case 'e': case 'E':                 // e or E를 입력받으면
			deleteLast(headnode);           // 연결리스트의 마지막에 있는 노드 삭제
			break;                          // switch문을 빠져나온다
		case 'f': case 'F':                 // f or F를 입력받으면
			printf("Your Key = ");          
			scanf("%d", &key);              // key값 입력
			insertFirst(headnode, key);     // 해당하는 key값을 가진 노드를 연결리스트 맨 앞에 삽입
			break;                          // switch문을 빠져나온다.
		case 't': case 'T':                 // t or T를 입력받으면
			deleteFirst(headnode);          // 연결리스트의 첫번째 노드를 삭제
			break;                          // switch문을 빠져나온다
		case 'r': case 'R':                 // r or R을 입력받으면
			invertList(headnode);           // 연결리스트에 있는 노드들의 순서를 역순으로 재배치
			break;                          // switch문을 빠져나온다
		case 'q': case 'Q':                 // q or Q를 입력받으면
			freeList(headnode);             // 프로그램을 끝내기 전 연결리스트에 할당된 메모리를 해제해준다
			break;                          // switch문을 빠져나온다
		default:                            // 그 밖에 다른 값들이 입력 될 경우
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");      // 오류메세지 출력
			break;                          // switch문을 빠져나온다.
		}

	}while(command != 'q' && command != 'Q');   // q or Q를 입력받으면

	return 1;   // 프로그램 종료
}


int initialize(headNode** h) {                      // 연결리스트를 형성하기 위해 초기화 하는 함수

	if(*h != NULL)                                  // h가 마지막이 아니면
		freeList(*h);                               // 할당된 메모리 모두 해제

	*h = (headNode *)malloc(sizeof(headNode ));     // 헤더노드 h에 메모리 영역을 할당
	(*h)->first = NULL;                             // 아직 들어온 노드가 없으므로 h->first = NULL
	return 1;   // 함수를 빠져나온다
}

int freeList(headNode* h){
    
	listNode* p = h->first;                     // 임시 노드 p에 h->first[첫번째 노드] 를 가르키도록 설정

	listNode* prev = NULL;                      // 삭제하고자 하는 노드
	while(p != NULL) {                          // 만약 p가 가르키는 것이 NULL이 아니면 (연결리스트의 끝이 아니면)
		prev = p;                               // [삭제할려고 하는 노드]는 p를 가리키고
		p = p->rlink;                           // p는 [p의 다음 노드]를 가리킨다
		free(prev);                             // 이후 prev가 가리키는 노드를 삭제(메모리 해제)
	}                                           // p가 NULL을 가리켜 (마지막 노드에 도착해 삭제했을 경우)
	free(h);                                    // 헤드노드 h를 삭제(메모리 해제)

	return 0;                                   // 함수를 빠져나온다
}


void printList(headNode* h) {                   // 연결리스트를 출력하기 위한 함수
	int i = 0;                                  // 들어있는 노드의 개수를 나타내기 위한 변수 i
	listNode* p;                                // 노드들을 표현하기 위한 포인터 변수 p

	printf("\n---PRINT\n");

	if(h == NULL) {                             // 연결리스트 자체가 없으면
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;                               // p를 [첫번째 노드]로 지정

	while(p != NULL) {                          // p가 마지막 노드를 출력할 때 까지
		printf("[ [%d]=%d ] ", i, p->key);      // 노드의 위치와 노드안에있는 데이터 값을 출력
		p = p->rlink;                           // 다음 노드를 가리키도록 지정
		i++;                                    // 노드의 개수 ++
	}

	printf("  items = %d\n", i);                // 노드의 개수 출력
}




/**
 * list에 key에 대한 노드 하나를 추가
 */
int insertLast(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));	// 삽입할 노드
    listNode* link = NULL;									// 연결리스트 마지막 노드를 찾기위한 포인터 변수 link

    if(h->first != NULL){									// 만약 연결리스트가 비어있지 않으면
        link = h->first;									// link가 [첫번째 노드]를 가리키도록 지정

        while (link->rlink != NULL){					    // [삽입할 노드]의 링크가 NULL이 될때까지(마지막 노드가 될때까지)
            if(link->rlink != NULL){						// [link가 가리키는 노드]가 마지막 노드가 아니면
                link = link->rlink;							// link는 다음 노드를 가리킨다.
            }
        }
        link->rlink = node;							        // [마지막 노드]뒤에 [삽입할 노드]를 삽입
        node->rlink = NULL;							        // [삽입한 노드]를 마지막 노드로 지정
        node->llink = link;                                 // [삽입한 노드]의 왼쪽 링크필드가 [이전 마지막 노드]를 가리키도록 설정.
        node->key = key;							        // [삽입한 노드]에 key값 할당
    } else {												// 연결리스트가 비어있으면
        h->first = node;									// 첫번째 노드를 [삽입할 노드]로 지정
		node->rlink = NULL;									// 첫번째 노드가 곧 마지막 노드이므로 링크에 NULL값 지정
        node->key = key;									// [삽입한 노드]에 key값 할당
        node->llink = NULL;                                 // [삽입한 노드]가 [첫번째 노드]이므로 왼쪽 링크 필드에 NULL
    }
	return 0;												// 함수를 빠져나온다.
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
    listNode* temp = NULL;									// 삭제할 노드를 찾기 위한 포인터 변수 temp
	listNode* Del_Node = NULL;								// 노드를 삭제하기 위한 포인터 변수 Del_Node

	if(h->first != NULL){									// 연결리스트가 비어있지않으면
		temp = h->first;									// temp가 [첫번째 노드]를 가리키도록 지정
		Del_Node = h->first;								// Del_Node도 [첫번째 노드]를 가리키도록 지정

		if(temp->rlink != NULL){							// [temp가 가리키는 노드]가 [마지막 노드]가 아니면

			do{												// 반복문 실행
				if(temp->rlink->rlink == NULL){				// [temp가 가리키는 노드]의 [다음노드]가 마지막 노드이면[삭제 될 노드]
					Del_Node = temp->rlink;					// Del_Node가 [삭제 될 노드]를 가리키도록 지정
					temp->rlink = NULL;						// [temp가 가리키는 노드]를 [마지막 노드]로 설정하고

					free(Del_Node);							// [삭제 될 노드]를 삭제
					return 0;								// 함수를 빠져나온다

				}else temp = temp->rlink;					// 만약 [temp가 가리키는 노드]의 [다음노드]가 [마지막 노드]가 아니면 
                                                            // [마지막 노드]를 찾을때까지 다음 노드로 이동

			}while(temp);									// [마지막 노드를 찾을때까지]

		}else{
			free(Del_Node);									// [temp가 가리키는 노드가 마지막이면] -> 첫번째 노드
			h->first = NULL;								// [첫번째 노드]를 삭제하고 연결리스트를 비운다.
		}
	}else printf("The linked list is already Empty!!\n");	// 연결리스트가 비어있으면 오류메세지 출력
	return 0;												// 함수를 빠져나온다.
}



/**
 * list 처음에 key에 대한 노드 하나를 추가
 */
int insertFirst(headNode* h, int key) {                        
    
	listNode* node = (listNode*)malloc(sizeof(listNode));   // 한개의 노드를 동적할당을 받아
	node->key = key;                                        // 노드의 key에 값을 할당해주고
	node->rlink = h->first;                                 // 노드의 link가 첫번째 노드를 가리키도록 한다
    node->llink = NULL;                                     // [첫번째 노드]의 왼쪽 링크 필드는 NULL이므로
	h->first = node;                                        // 헤더노드의 첫번재 노드로 설정

	return 0;                                               // 함수를 빠져나온다
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
    listNode* temp = NULL;									// 첫번째 노드를 가리키고 삭제하기 위한 포인터 temp

    if(h->first != NULL){									// 연결리스트가 비어있지 않으면

        if(h->first->rlink != NULL){                        // [첫번째 노드]가 [마지막 노드]가 아니면
        temp = h->first;									// temp가 [첫번째 노드]를 가리키도록 지정
        h->first = h->first->rlink;							// 연결리스트의 첫번째 노드가 [첫번째 노드의 다음 노드]가 되도록 설정
        h->first->llink = NULL;                             // 연결리스트의 [첫번째 노드]가 된 노드의 왼쪽 링크 필드를 NULL로 지정

        free(temp);											// [본래 첫번째 노드]를 삭제
        }

        else{                                               // 만약 [첫번째 노드]가 [마지막 노드]이면
            temp = h->first;                                // [삭제하기 위한 노드]를 [첫번째 노드]로 설정
            h->first = NULL;                                // 연결리스트에는 노드가 없어지게 되므로 h->first = NULL 
            free(temp);                                     // [첫번째 노드] 삭제
        }
    } else {												// 연결리스트가 비어있으면
        printf("The linked list is already Empty!!\n");		// 이미 비어있다는 오류 메세지 출력
    }

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
    listNode* temp = NULL;						// 현재 가리키는 노드를 표현하기위한 포인터 변수 temp
	listNode* middle = NULL;					// temp 이전 노드를 표현하기 위한 포인터 변수 middle
	listNode* trail;							// middle 이전 노드를 표현하기 위한 포인터 변수 trail

	if(h->first != NULL){						// 연결리스트가 비어있지 않으면
		temp = h->first;						// temp가 [첫번째 노드]를 가리키도록 지정

		while(temp){							// temp가 [마지막 노드]에 도착할때까지
			trail = middle;						// trail이 middle을 가리키도록 하고
			middle = temp;						// middle이 temp를 가리키도록 한다
			temp = temp->rlink;					// 이렇게 진행하게 되면 temp는 점차 [마지막 노드]의 NULL값에 가까워 지게 되고
			middle->rlink = trail;				// middle의 노드가 이전 노드를 가리키면서
            middle->llink = temp;
		}										// temp가 NULL이 되면 반복문을 빠져나온다  따라서 temp == NULL
		h->first = middle;						// middle은 마지막 노드가 되었으므로 역순으로 재배치하면 middle은 시작 노드가 된다.
												// 325번째 줄에서 trail은 처음, NULL을 가리키기 때문에
												// 역순으로 재배치를 하면 [첫번째 노드]가 [마지막 노드]가 될 수 있다.
	}else printf("The linked list is already Empty!!\n");	// 연결리스트가 비어있으면 오류메세지 출력

	return 0;												// 함수를 빠져나온다.
}



/* 리스트를 검색하여, 입력받은 key보다 큰 값이 나오는 노드 바로 앞에 삽입  */
int insertNode(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));   // 삽입할 노드
    listNode* link = NULL;                                  // node보다 앞에 있는 노드를 가리키는 포인터 link

    link = h->first;										// 포인터 변수 link가 첫번째 노드를 가리키도록 지정

    if(h->first != NULL){									// 첫번째 노드가 있으면 (연결리스트가 비어있지 않을 경우)

        if(h->first->key > key){							// [첫번째 노드]가 key값보다 큰지 비교
                                                            // [첫번째 노드의 key]값이 더 크면
            node->rlink = h->first;							// [삽입할 노드]의 rlink를 첫번째 노드를 가리키도록 하고
            h->first = node;								// [삽입할 노드]가 [첫번째 노드]가 된다.
            node->llink = NULL;                             // [삽입한 노드]는 [첫번째 노드]이므로 왼쪽 링크 필드에 NULL 지정
            node->key = key;								// [삽입한 노드]에 key값을 할당해준다.
            return 0;										// 함수를 빠져나온다.
        }

        if(h->first->rlink != NULL){						// 만약 [첫번째 노드]가 마지막 노드가 아닐 경우

            while(key >= link->rlink->key){					// [link가 가리키는 노드]->[link 다음 노드]의 키값이 key보다 크지않으면

                if(link->rlink->rlink != NULL)				// [link 다음 노드]가 [마지막 노드]가 나올때까지
                    link = link->rlink;						// [link가 가리키는 노드]에서 [다음 노드]로 넘어간다

                else {										// 마지막 노드에 도착했을 경우
                    link->rlink->rlink = node;				// [마지막 노드]의 링크필드에 [삽입할 노드]를 가리키고
                    node->rlink = NULL;						// [삽입할 노드]를 마지막 노드로 지정
                    node->llink = link->rlink;              // [삽입한 노드]가 [마지막 노드]가 되었으므로 왼쪽 링크 필드에 [이전 마지막 노드]를 가리킨다.
                    node->key = key;						// 이후 [삽입한 노드]에 key값 할당

                    return 0;								// 함수를 빠져나온다
                }
            }
        } else {											// [첫번째 노드]가 [마지막 노드]이고, [첫번째 노드]보다 key이 클경우
            h->first->rlink = node;							// [첫번째 노드] 뒤에 [삽입할 노드]가 오도록 링크를 지정
            node->rlink = NULL;								// [삽입할 노드]가 마지막 노드가 되도록 하고
            node->llink = h->first;                         // [삽입한 노드]가 [두번째 노드] 이므로 왼쪽 링크 필드에 [첫번째 노드]를 가리킨다.
            node->key = key;								// [삽입한 노드]에 key값 할당
        }

        if(key < link->rlink->key){							// 연결리스트가 비어있지 않지만, [두번재 노드]의 키값보다 key값이 작을 경우

            node->rlink = link->rlink;						// [삽입할 노드]의 다음 노드를 [두번째 노드]로 가리키고
            link->rlink = node;								// [두번째 노드] 이전에 [삽입할 노드]를 삽입
            node->llink = link;                             // [삽입한 노드]에서 [첫번째 노드]를 가리키는 왼쪽 링크 필드 지정
            node->key = key;								// [삽입한 노드]에 key값 할당
        }
    } else{													// 만약 연결리스트가 비어있으면
        h->first = node;									// [삽입할 노드]를 첫번째 노드로 지정
		node->rlink = NULL;									// [삽입한 노드]가 마지막 노드이므로 링크에 NULL 지정
        node->llink = NULL;                                 // [삽입한 노드]가 첫번째 노드 이므로 왼쪽 링크 필드에 NULL 지정
        node->key = key;									// [삽입한 노드]에 key값 할당
    }
	return 0;												// 함수를 빠져나온다
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
    listNode* temp = NULL;									// key값을 찾기위한 포인터 변수 temp 선언
    listNode* Del_Node = NULL;								// key값을 찾고나면 삭제하기 위한 포인터 변수 Del_Node 선언

    if(h->first != NULL){									// 연결리스트가 비어있지않으면
        temp = h->first;									// temp가 [첫번째 노드]를 가리키도록 지정
		Del_Node = h->first;								// Del_Node도 [첫번째 노드]를 가리키도록 지정

		if(temp->key == key){								// [첫번째 노드]의 키값이 key값과 같으면
            if(temp->rlink == NULL){                        // [첫번째 노드]가 [마지막 노드]이면
                free(temp);                                 // [첫번째 노드] 삭제
                h->first = NULL;                            // [첫번째 노드]를 삭제하면 연결리스트가 비어있으므로 h->first = NULL
                return 0;                                   // 함수를  빠져나온다.
            }
            else{                                           // [첫번째 노드] 뒤에 이어지는 노드들이 존재하면
			    h->first = temp->rlink;						// [두번째 노드]가 [첫번째 노드]가 되어지도록 설정
                temp->rlink->llink = NULL;                  // [첫번째 노드가 된 두번째 노드]의 왼쪽 링크 필드를 NULL로 지정

			    free(temp);								    // [본래 첫번째 노드]를 삭제
			    return 0;									// 함수를 빠져나온다.
            }

		}else{												// [첫번째 노드]에 key값이 있지 않으면

			if(temp->rlink == NULL){						// [첫번째 노드]가 [마지막 노드]일 경우
				printf("Key does not exist.\n");			// 찾는 key값이 없다는 메세지 출력
				return 0;									// 함수를 빠져나온다.
			}
                                                            // [첫번째 노드]가 [마지막 노드]가 아니면

        	do{												// 반복문 실행

            	if(key == temp->rlink->key){				// [temp가 가리키는 노드]의 [다음 노드]의 키값이 key값과 같으면

					Del_Node = temp->rlink;					// Del_Node가 [다음 노드]를 가리키도록 설정 [삭제 될 노드]
					temp->rlink = Del_Node->rlink;			// [temp가 가리키는 노드]는 [삭제 될 노드]의 [다음 노드]를 가리키도록 지정
                    temp->llink = Del_Node->llink;

                	free(Del_Node);							// [삭제 될 노드]를 삭제
                	return 0;								// 함수를 빠져나온다.

            	} else temp = temp->rlink;					// key값이 같지 않으면 다음노드로 이동

        	}while(temp->rlink != NULL);				    // [temp가 가리키는 노드]가 [마지막 노드]가 될때까지
		}
		printf("Key does not exist.\n");					// [마지막 노드]에 도착하고 key값이 없으면 오류메세지 출력

    }else printf("The linked list is already Empty!!\n");	// 연결리스트가 비어있으면 오류메세지 출력

	return 0;												// 함수를 빠져나온다.
}
