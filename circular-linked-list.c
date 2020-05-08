/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {                       // 노드를 나타내기 위한 구조체
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);               // headnode를 초기화 시키기 위한 함수
int freeList(listNode* h);                  // 프로그램을 종료하기 전, 동적할당을 받은 메모리들을 해제시켜주기 위한 함수
int insertLast(listNode* h, int key);       // 연결리스트 마지막에 노드를 삽입하기 위한 함수
int deleteLast(listNode* h);                // 마지막 노드를 삭제하기 위한 함수
int insertFirst(listNode* h, int key);      // 연결리스트의 첫번째에 노드를 삽입하기 위한 함수
int deleteFirst(listNode* h);               // 첫번째 노드를 삭제하기 위한 함수
int invertList(listNode* h);                // 연결리스트의 노드들을 역순으로 재배치 하기 위한 함수

int insertNode(listNode* h, int key);       // key값보다 큰 값을 가지고 있는 노드 앞에 새로운 노드를 삽입하기 위한 함수
int deleteNode(listNode* h, int key);       // key값에 해당하는 값을 가지고 있는 노드를 삭제하기 위한 함수

void printList(listNode* h);                // 연결리스트에 들어있는 노드들을 출력하기 위한 함수



int main()
{
	char command;                           // 명령어를 입력 받기 위한 변수 command
	int key;                                // key값을 입력 받기 위한 변수
	listNode* headnode=NULL;                // 연결리스트의 헤드노드가 될 포인터 변수 headnode

    printf("[----- [Kwon_DongCheon] [2017038072] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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
		case 'z': case 'Z':                 // z or Z를 입력 받으면
			initialize(&headnode);          // intialize()함수 실행
			break;
		case 'p': case 'P':                 // p or P를 입력 받으면
			printList(headnode);            // 연결리스트에 들어있는 노드들 출력
			break;
		case 'i': case 'I':                 // i or I를 입력 받으면
			printf("Your Key = ");          // key 값 입력
			scanf("%d", &key);
			insertNode(headnode, key);      // key값보다 더 큰 값을 가지고 있는 노드 앞에 삽입
			break;
		case 'd': case 'D':                 // d or D를 입력 받으면
			printf("Your Key = ");          // key 값 입력
			scanf("%d", &key);
			deleteNode(headnode, key);      // 해당하는 key값을 가지고 있는 노드 삭제
			break;
		case 'n': case 'N':                 // n or N를 입력 받으면
			printf("Your Key = ");          // key 값 입력
			scanf("%d", &key);              
			insertLast(headnode, key);      // 연결리스트의 마지막에 key값을 가진 노드 삽입
			break;
		case 'e': case 'E':                 // e or E를 입력 받으면
			deleteLast(headnode);           // 마지막 노드를 삭제
			break;
		case 'f': case 'F':                 // f or F를 입력 받으면
			printf("Your Key = ");          // key 값 입력
			scanf("%d", &key);
			insertFirst(headnode, key);     // 해당하는 key 값을 가지고 있는 노드를 첫번째로 삽입
			break;
		case 't': case 'T':                 // t or T를 입력 받으면
			deleteFirst(headnode);          // 연결리스트의 첫번째 노드 삭제
			break;
		case 'r': case 'R':                 // r or R를 입력 받으면
			invertList(headnode);           // 연결리스트에 들어있는 노드들의 순서를 역순으로 재배치
			break;
		case 'q': case 'Q':                 // q or Q를 입력 받으면
			freeList(headnode);             // 종료하기 전 할당받은 메모리들을 모두 해제
			break;
		default:                            // 그 외 다른 명령어를 입력 받으면
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");      // 오류 메세지 출력
			break;
		}

	}while(command != 'q' && command != 'Q');   // q or Q를 입력 받으면 반복문을 빠져나온다.

	return 1;           // 프로그램 종료.
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
    listNode* p = h->rlink;                     // 임시 노드 p에 h->first[첫번째 노드] 를 가르키도록 설정

	listNode* prev = NULL;                      // 삭제하고자 하는 노드
	while(p != h) {                          // 만약 p가 가르키는 것이 NULL이 아니면 (연결리스트의 끝이 아니면)
		prev = p;                               // [삭제할려고 하는 노드]는 p를 가리키고
		p = p->rlink;                           // p는 [p의 다음 노드]를 가리킨다
		free(prev);                             // 이후 prev가 가리키는 노드를 삭제(메모리 해제)
	}                                           // p가 NULL을 가리켜 (마지막 노드에 도착해 삭제했을 경우)
	free(h);                                    // 헤드노드 h를 삭제(메모리 해제)

	return 0;                                   // 함수를 빠져나온다
}



void printList(listNode* h) {                   // 연결리스트에 들어있는 노드들을 출력하기 위한 함수
	int i = 0;                                  // 들어있는 노드들의 갯수를 표현하기 위한 i
	listNode* p;                                // 노드들을 나타내기 위한 포인터 변수 p

	printf("\n---PRINT\n");

	if(h == NULL) {                             // 만약 연결 리스트가 비어있으면
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;                               // p가 [첫번째 노드]를 가리키도록 지정

	while(p != NULL && p != h) {                // p가 비어있거나 p가 h가 되기 전까지 반복문 실행
		printf("[ [%d]=%d ] ", i, p->key);      // 노드들의 순서와 들어있는 key값을 출력
		p = p->rlink;                           // 다음노드로 이동
		i++;                                    // 연결리스트에 들어있는 노드들의 개수 증가
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);
    // 헤드노드를 표현

    // 각 노드들의 주소와 좌-우 링크들이 무엇을 가리키고 있는지 출력하기 위한 코드
	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
     listNode* node = (listNode*)malloc(sizeof(listNode));	// 삽입할 노드
    listNode* link = NULL;									// 연결리스트 마지막 노드를 찾기위한 포인터 변수 link

    if(h->rlink != h){									    // 만약 연결리스트가 비어있지 않으면
        link = h->rlink;									// link가 [첫번째 노드]를 가리키도록 지정

        while (link->rlink != h){					        // [삽입할 노드]의 오른쪽 링크가 h가 될때까지(마지막 노드가 될때까지)
            if(link->rlink != h){						    // [link가 가리키는 노드]가 마지막 노드가 아니면
                link = link->rlink;							// link는 다음 노드를 가리킨다.
            }
        }
        link->rlink = node;							        // [마지막 노드]뒤에 [삽입할 노드]를 삽입
        node->rlink = h;							        // [삽입한 노드]를 마지막 노드로 지정
        node->llink = link;                                 // [삽입한 노드]의 왼쪽 링크필드가 [이전 마지막 노드]를 가리키도록 설정.
        node->key = key;							        // [삽입한 노드]에 key값 할당
        h->llink = node;
    } else {												// 연결리스트가 비어있으면
        h->rlink = node;									// 첫번째 노드를 [삽입할 노드]로 지정
		node->rlink = h;									// 첫번째 노드가 곧 마지막 노드이므로 링크에 h값 지정
        node->key = key;									// [삽입한 노드]에 key값 할당
        node->llink = h;                                    // [삽입한 노드]가 [첫번째 노드]이므로 왼쪽 링크 필드에 h
        h->llink = node;                                    // h의 왼쪽 링크 필드에 [삽입한 노드] 지정
    }
	return 1;												// 함수를 빠져나온다.
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
    listNode* temp = NULL;									// 삭제할 노드를 찾기 위한 포인터 변수 temp
	listNode* Del_Node = NULL;								// 노드를 삭제하기 위한 포인터 변수 Del_Node

	if(h->rlink != h){									    // 연결리스트가 비어있지않으면
		temp = h->rlink;									// temp가 [첫번째 노드]를 가리키도록 지정
		Del_Node = h->rlink;								// Del_Node도 [첫번째 노드]를 가리키도록 지정

		if(temp->rlink != h){							    // [temp가 가리키는 노드]가 [마지막 노드]가 아니면

			do{												// 반복문 실행
				if(temp->rlink->rlink == h){				// [temp가 가리키는 노드]의 [다음노드]가 마지막 노드이면[삭제 될 노드]
					Del_Node = temp->rlink;					// Del_Node가 [삭제 될 노드]를 가리키도록 지정
					temp->rlink = h;						// [temp가 가리키는 노드]를 [마지막 노드]로 설정하고
                    h->llink = temp;                        // h의 왼쪽 링크 필드에 temp 지정

					free(Del_Node);							// [삭제 될 노드]를 삭제
					return 0;								// 함수를 빠져나온다

				}else temp = temp->rlink;					// 만약 [temp가 가리키는 노드]의 [다음노드]가 [마지막 노드]가 아니면 
                                                            // [마지막 노드]를 찾을때까지 다음 노드로 이동

			}while(temp);									// [마지막 노드를 찾을때까지]

		}else{
			free(Del_Node);									// [temp가 가리키는 노드가 마지막이면] -> 첫번째 노드
			h->rlink = h;								    // [첫번째 노드]를 삭제하고 연결리스트를 비운다.
            h->llink = h;
		}
	}else printf("The linked list is already Empty!!\n");	// 연결리스트가 비어있으면 오류메세지 출력

	return 1;												// 함수를 빠져나온다.
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));   // 한개의 노드를 동적할당을 받아

    if(h->rlink == h){                                      // 추가하는 노드가 [처음으로 들어오는 노드] 일 경우
        h->rlink = node;                                    // node를 [첫번째 노드]로 지정
        node->key = key;                                    // node에 key값 할당
        node->llink = h;                                    // node가 [첫번째 노드] 이므로 왼쪽 링크 필드에 h 지정
        node->rlink = h;                                    // 마찬가지로 node의 오른쪽 링크 필드에 h 지정
        h->llink = node;                                    // h의 왼쪽 링크 필드에 [첫번째 노드]이자 [마지막 노드]인 node로 지정

        return 1;
    }


	node->key = key;                                        // 노드의 key에 값을 할당해주고
    h->rlink->llink = node;                                 // [첫번째 노드]의 왼쪽 링크 필드는 node로 지정
	node->rlink = h->rlink;                                 // 노드의 link가 첫번째 노드를 가리키도록 한다
    node->llink = h;                                        // [첫번째 노드]의 왼쪽 링크 필드는 NULL이므로
	h->rlink = node;                                        // 헤더노드의 첫번재 노드로 설정

	return 1;                                               // 함수를 빠져나온다
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
    listNode* temp = NULL;									// 첫번째 노드를 가리키고 삭제하기 위한 포인터 temp

    if(h->rlink != h){									    // 연결리스트가 비어있지 않으면

        if(h->rlink->rlink != h){                           // [첫번째 노드]가 [마지막 노드]가 아니면
        temp = h->rlink;									// temp가 [첫번째 노드]를 가리키도록 지정
        h->rlink = h->rlink->rlink;							// 연결리스트의 첫번째 노드가 [첫번째 노드의 다음 노드]가 되도록 설정
        h->rlink->llink = h;                                // 연결리스트의 [첫번째 노드]가 된 노드의 왼쪽 링크 필드를 h로 지정

        free(temp);											// [본래 첫번째 노드]를 삭제
        }

        else{                                               // 만약 [첫번째 노드]가 [마지막 노드]이면
            temp = h->rlink;                                // [삭제하기 위한 노드]를 [첫번째 노드]로 설정
            h->rlink = h;                                   // 연결리스트에는 노드가 없어지게 되므로 h->rlink = h 
            h->llink = h;                                   // 마찬가지로 왼쪽 링크 필드도 h->llink = h
            free(temp);                                     // [첫번째 노드] 삭제
        }

    } else {												// 연결리스트가 비어있으면

        printf("The linked list is already Empty!!\n");		// 이미 비어있다는 오류 메세지 출력
    }

	return 1;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
    listNode* temp = h;						    // 현재 가리키는 노드를 표현하기위한 포인터 변수 temp
	listNode* middle = h;					    // temp 이전 노드를 표현하기 위한 포인터 변수 middle
	listNode* trail;							// middle 이전 노드를 표현하기 위한 포인터 변수 trail

	if(h->rlink != h){						    // 연결리스트가 비어있지 않으면
		temp = h->rlink;						// temp가 [첫번째 노드]를 가리키도록 지정
        h->llink = temp;

		while(temp->rlink != h){			    // temp가 [마지막 노드]에 도착할때까지
			trail = middle;						// trail이 middle을 가리키도록 하고
			middle = temp;						// middle이 temp를 가리키도록 한다
			temp = temp->rlink;					// 이렇게 진행하게 되면 temp는 점차 [마지막 노드]의 NULL값에 가까워 지게 되고
			middle->rlink = trail;				// middle의 노드가 이전 노드를 가리키면서
            middle->llink = temp;               // middle의 왼쪽 링크 필드를 다음 노드로 설정해 놓는다.
		}										// temp->rlink가 h가 되면 반복문을 빠져나온다  따라서 temp->rlink = h
        temp->llink = h;
        temp->rlink = middle;
		h->rlink = temp;                        // [마지막 노드]에서 [첫번째 노드]가 된 temp에 h의 오른쪽 링크 필드를 지정
												// 325번째 줄에서 trail은 처음, h을 가리키기 때문에f
												// 역순으로 재배치를 하면 [첫번째 노드]가 [마지막 노드]가 될 수 있다.

	}else printf("The linked list is already Empty!!\n");	// 연결리스트가 비어있으면 오류메세지 출력

	return 1;												// 함수를 빠져나온다.
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));   // 삽입할 노드
    listNode* link = NULL;                                  // node보다 앞에 있는 노드를 가리키는 포인터 link

    link = h->rlink;										// 포인터 변수 link가 첫번째 노드를 가리키도록 지정

    if(h->rlink != h){									    // 첫번째 노드가 있으면 (연결리스트가 비어있지 않을 경우)

        if(h->rlink->key > key){							// [첫번째 노드]가 key값보다 큰지 비교
                                                            // [첫번째 노드의 key]값이 더 크면

            node->rlink = h->rlink;							// [삽입할 노드]의 rlink를 첫번째 노드를 가리키도록 하고
            h->rlink->llink = node;
            h->rlink = node;								// [삽입할 노드]가 [첫번째 노드]가 된다.
            node->llink = h;                                // [삽입한 노드]는 [첫번째 노드]이므로 왼쪽 링크 필드에 NULL 지정
            node->key = key;								// [삽입한 노드]에 key값을 할당해준다.

            return 1;										// 함수를 빠져나온다.
        }

        if(h->rlink->rlink != h){						    // 만약 [첫번째 노드]가 마지막 노드가 아닐 경우

            while(key >= link->rlink->key){					// [link가 가리키는 노드]->[link 다음 노드]의 키값이 key보다 크지않으면

                if(link->rlink->rlink != h) 			    // [link 다음 노드]가 [마지막 노드]가 나올때까지
                    link = link->rlink;						// [link가 가리키는 노드]에서 [다음 노드]로 넘어간다
                else {										// 마지막 노드에 도착했을 경우
                    link->rlink->rlink = node;				// [마지막 노드]의 링크필드에 [삽입할 노드]를 가리키고
                    node->rlink = h;						// [삽입할 노드]를 마지막 노드로 지정
                    node->llink = link->rlink;              // [삽입한 노드]가 [마지막 노드]가 되었으므로 왼쪽 링크 필드에 [이전 마지막 노드]를 가리킨다.
                    node->key = key;						// 이후 [삽입한 노드]에 key값 할당
                    h->llink = node;                        // h의 왼쪽 링크 필드에 [마지막 노드] 지정

                    return 1;								// 함수를 빠져나온다
                }
            }
        } else {											// [첫번째 노드]가 [마지막 노드]이고, [첫번째 노드]보다 key이 클 경우
            h->rlink->rlink = node;							// [첫번째 노드] 뒤에 [삽입할 노드]가 오도록 링크를 지정
            node->rlink = h;								// [삽입할 노드]가 마지막 노드가 되도록 하고
            node->llink = h->rlink;                         // [삽입한 노드]가 [두번째 노드] 이므로 왼쪽 링크 필드에 [첫번째 노드]를 가리킨다.
            node->key = key;								// [삽입한 노드]에 key값 할당
            h->llink = node;                                // h의 왼쪽 링크 필드에 [마지막 노드] 지정
            
        }

        if(key < link->rlink->key){							// 연결리스트가 비어있지 않지만, [두번재 노드]의 키값보다 key값이 작을 경우
                                                            // 혹은 [link의 다음 노드의 key]값보다 key값이 작을 경우

            node->rlink = link->rlink;						// [삽입할 노드]의 다음 노드를 [두번째 노드]로 가리키고
            link->rlink->llink = node;                      // [두번째 노드]의 왼쪽 링크 필드에 node로 지정
            link->rlink = node;								// [두번째 노드] 이전에 [삽입할 노드]를 삽입
            node->llink = link;                             // [삽입한 노드]에서 [첫번째 노드]를 가리키는 왼쪽 링크 필드 지정
            node->key = key;								// [삽입한 노드]에 key값 할당

        }
    } else{													// 만약 연결리스트가 비어있으면
        h->rlink = node;									// [삽입할 노드]를 첫번째 노드로 지정
		node->rlink = h;									// [삽입한 노드]가 마지막 노드이므로 오른쪽 링크에 h 지정
        node->llink = h;                                    // [삽입한 노드]가 첫번째 노드 이므로 왼쪽 링크 필드에 h 지정
        node->key = key;									// [삽입한 노드]에 key값 할당
        h->llink = node;                                    // h의 왼쪽 링크 필드에 [삽입한 노드(마지막 노드)] 지정
    }
	return 1;												// 함수를 빠져나온다
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
    listNode* temp = NULL;									// key값을 찾기위한 포인터 변수 temp 선언
    listNode* Del_Node = NULL;								// key값을 찾고나면 삭제하기 위한 포인터 변수 Del_Node 선언

    if(h->rlink != h){									    // 연결리스트가 비어있지않으면
        temp = h->rlink;									// temp가 [첫번째 노드]를 가리키도록 지정
		Del_Node = h->rlink;								// Del_Node도 [첫번째 노드]를 가리키도록 지정

		if(temp->key == key){								// [첫번째 노드]의 키값이 key값과 같으면
            if(temp->rlink == h){                           // [첫번째 노드]가 [마지막 노드]이면
                free(temp);                                 // [첫번째 노드] 삭제
                h->rlink = h;                               // [첫번째 노드]를 삭제하면 연결리스트가 비어있으므로 h->rlink = h
                h->llink = h;                               // 마찬가지로 h->llink = h

                return 0;                                   // 함수를  빠져나온다.
            }
            else{                                           // [첫번째 노드] 뒤에 이어지는 노드들이 존재하면
			    h->rlink = temp->rlink;						// [두번째 노드]가 [첫번째 노드]가 되어지도록 설정
                temp->rlink->llink = h;                     // [첫번째 노드가 된 두번째 노드]의 왼쪽 링크 필드를 h로 지정

			    free(temp);								    // [본래 첫번째 노드]를 삭제
			    return 0;									// 함수를 빠져나온다.
            }

		}else{												// [첫번째 노드]에 key값이 있지 않으면

			if(temp->rlink == h){						    // [첫번째 노드]가 [마지막 노드]일 경우
				printf("Key does not exist.\n");			// 찾는 key값이 없다는 메세지 출력
				return 0;									// 함수를 빠져나온다.
			}
                                                            // [첫번째 노드]가 [마지막 노드]가 아니면

        	do{												// 반복문 실행

            	if(key == temp->rlink->key){				// [temp가 가리키는 노드]의 [다음 노드]의 키값이 key값과 같으면

					Del_Node = temp->rlink;					// Del_Node가 [다음 노드]를 가리키도록 설정 [삭제 될 노드]
					temp->rlink = Del_Node->rlink;			// [temp가 가리키는 노드]는 [삭제 될 노드]의 [다음 노드]를 가리키도록 지정
                    Del_Node->rlink->llink = temp;          // [삭제 될 노드]의 [다음 노드]가 [삭제될 노드]의 [이전 노드]를 가리키도록 지정

                	free(Del_Node);							// [삭제 될 노드]를 삭제
                	return 0;								// 함수를 빠져나온다.

            	} else temp = temp->rlink;					// key값이 같지 않으면 다음노드로 이동

        	}while(temp->rlink != h);				        // [temp가 가리키는 노드]가 [마지막 노드]가 될때까지
		}
		printf("Key does not exist.\n");					// [마지막 노드]에 도착하고 key값이 없으면 오류메세지 출력

    }else printf("The linked list is already Empty!!\n");	// 연결리스트가 비어있으면 오류메세지 출력

	return 1;												// 함수를 빠져나온다.
}

