/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>


typedef struct node {				// 노드를 나타내기 위한 구조체
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];		// iterativeInorder 방식으로 트리를 출력하기 위해 사용되는
int top = -1;						// 스택

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];		// 트리의 레벨따라 출력하기 위해 사용하는
int front = -1;						// 원형 큐
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */



int main()
{
	char command;					// 명령어를 입력받기 위한 변수 command
	int key;						// key값을 입력받기 위한 변수 key
	Node* head = NULL;				// 트리의 헤더 노드가 될 구조체 포인터변수 head

	printf("[----- [KwonDongCheon] [2017038072] -----]\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);		// 명령어 입력

		switch(command) {
		case 'z': case 'Z':			// z or Z일 경우
			initializeBST(&head);	// 트리를 형성하거나 초기화 시키기 위한 함수 호출
			break;
		case 'q': case 'Q':			// q or Q일 경우
			freeBST(head);			// 프로그램이 종료되기 전 트리에 할당된 메모리들을 해제하기 위한 함수 호출
			break;
		case 'i': case 'I':			// i or I일 경우
			printf("Your Key = ");
			scanf("%d", &key);		// key값을 입력받고
			insert(head, key);		// 트리에 해당 key값을 가진 노드 삽입
			break;
		case 'd': case 'D':			// d or D일 경우
			printf("Your Key = ");	
			scanf("%d", &key);		// key값을 입력받고
			deleteNode(head, key);	// 트리의 해당 key값을 가진 노드 삭제
			break;

		case 'r': case 'R':			// r or R일 경우
			recursiveInorder(head->left);	// RecursiveInorder 방식으로 트리의 노드들을 출력
			break;
		case 't': case 'T':			// t or T일 경우
			iterativeInorder(head->left);	// iterativeInorder 방식으로 트리의 노드들을 출력
			break;

		case 'l': case 'L':			// l or L일 경우
			levelOrder(head->left);			// levelOrder 방식으로 트리의 노드들을 출력
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');	// q or Q를 입력받으면 반복문을 빠져나온다.

	return 0; 		// 프로그램 종료.
}

int initializeBST(Node** h) {		// 트리를 형성하거나 초기화 하기위한 함수

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)				// RecursiveInorder 방식으로 트리의 노드들을 출력하기 위한 함수
{
	if(ptr) {									// 트리가 형성되어있지 않으면
		recursiveInorder(ptr->left);			// Inorder 방식에 따라
		printf(" [%d] ", ptr->key);				// 노드들을 출력한다.
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)           // Root에서 부터 시작
{
    if(node == NULL){						// 트리가 형성되어있지 않으면
        printf("The tree is empty!!!");		// 오류 메세지 출력
        return;								// 함수 종료
    }

    Node* SearchNode = NULL;				// 출력할 노드들을 탐색하는 구조체 포인터 변수SearchNode
    SearchNode = node;						// SearchNode를 Root로 지정
    
    while(1){								// 노드들을 출력하기위해 반복문 시작
        while(SearchNode != NULL){			// 시작과 동시에 제일 좌측으로 가기 위해 그리고 탐색하기 위한 반복문
            push(SearchNode);				// SearchNode를 Stack에 Push
            SearchNode = SearchNode->left;	// 이후 왼쪽 자식노드로 이동
        }

    	if(top != -1){							// 스택이 비어있지 않으면
			SearchNode = pop();					// Stack top에 있는 노드를 SearchNode에 Pop
            printf(" [%d] ", SearchNode->key);	// 해당 노드의 key 값 출력
            SearchNode = SearchNode->right;		// 계속 탐색하기 위해 오른쪽 자식 노드로 이동
        } 
        else break;								// 스택이 비어있을 경우 반복문 종료
    }
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)					// levelOrder 방식으로 트리의 노드들을 출력하기 위한 함수
{
	front = 0, rear =0;						// front와 rear를 0으로 설정한 후
	Node* SearchNode = NULL;				// 트리를 탐색하며 노드들을 출력할 구조체 포인터 변수 SearchNode 선언

	if(ptr != NULL){						// 트리가 비어있지 않으면
		SearchNode = ptr;					// SearchNode를 Root로 지정
		enQueue(SearchNode);				// 원형 큐에 SearchNode를 Push

		while(front != rear){				// front와 rear이 같지않으면 반복문 실행
			SearchNode = deQueue();			// 원형 큐에 있는 노드를 Pop하여 SearchNode에 저장
			printf(" [%d] ", SearchNode->key);	// 해당 노드의 key 값 출력

			if(SearchNode->left != NULL)	// SearchNode의 왼쪽 자식노드가 존재할 경우
				enQueue(SearchNode->left);	// 왼쪽 자식노드를 원형 큐에 Push
			if(SearchNode->right != NULL)	// SearchNode의 오른족 자식노드가 존재할 경우
				enQueue(SearchNode->right);	// 오른쪽 자식 노드를 원형 큐에 Push
			
			SearchNode = queue[front + 1];	// SearchNode가 원형큐에 들어있는 가장 첫번째 노드를 가리킴
		}
	}
}


int insert(Node* head, int key)				// 노드를 삽입하기 위한 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node));	// 삽입될 노드
	newNode->key = key;						// 노드의 key값에 입력된 key값 지정
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {				// 트리가 비어있을 경우
		head->left = newNode;				// 트리의 Root 노드로 삽입
		return 1;							// 함수 종료
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)			// 해당 key를 가진 노드를 삭제하기 위한 함수
{
	Node* SearchNode = NULL;				// 삭제 하고자 하는 노드를 가리키는 SearchNode
	Node* temp_Search = NULL;				// SearchNode의 이전 노드를 가리키기 위한 temp_Search
	Node* FindMinNode = NULL;				// SearchNode의 왼쪽, 오른쪽 자식 노드가 존재할 경우 사용할 FindMinNode
	Node* temp_Find = NULL;					// FindMinNode의 이전 노드를 가리키기 위한 temp_Find

	SearchNode = head->left;				// SearchNode를 트리의 Root 노드로 지정

	while(SearchNode){							// SearchNode가 NULL이 아니면 반복문 실행
		if(SearchNode->key < key){				// SearchNode의 key값이 입력된 키값보다 작을 경우
			temp_Search = SearchNode;			// temp_Search를 SearchNode로 지정
			SearchNode = SearchNode->right;		// SearchNode는 오른쪽 자식 노드로 이동
		}

		else if(SearchNode->key > key){			// SearchNode의 key값이 입력된 키값보다 클 경우
			temp_Search = SearchNode;			// Temp_Search를 SearchNode로 지정
			SearchNode = SearchNode->left;		// SearchNode는 왼쪽 자식 노드로 이동
		}

		else if(SearchNode->key == key){		// 입력된 키값을 가지고 있는 노드를 찾으면
			
			if((SearchNode->left == NULL) && (SearchNode->right == NULL)){			// leaf 노드 인 경우 1번째 케이스
				if(temp_Search->left == SearchNode){			// SearchNode가 이전 노드의 왼쪽 자식 노드이면
					temp_Search->left = NULL;					// SearchNode 이전 노드의 왼쪽 자식 노드를 NULL로 지정
					free(SearchNode);							// 입력된 키 값을 가지고 있는 노드를 삭제
					return 0;
				}else if(temp_Search->right == SearchNode){		// SearchNode가 이전 노드의 오른쪽 자식 노드이면
					temp_Search->right = NULL;					// SearchNode 이전 노드의 오른쪽 자식 노드를 NULL로 지정
					free(SearchNode);							// 입력된 키 값을 가지고 있는 노드를 삭제
					return 0;
				}


			}else if((SearchNode->left == NULL) && (SearchNode->right != NULL)){	// 자식노드가 한쪽에만 있을 경우 2번째 케이스
				if(temp_Search->left == SearchNode){			// SearchNode가 이전 노드의 왼쪽 자식 노드이면
					temp_Search->left = SearchNode->right;		// SearchNode 이전 노드의 왼쪽 자식 노드를 SearchNode의 오른쪽 자식 노드로 지정
					free(SearchNode);							// 입력된 키 값을 가지고 있는 노드를 삭제
					return 0;
				}else if(temp_Search->right == SearchNode){		// SearchNode가 이전 노드의 오른족 자식 노드이면
					temp_Search->right = SearchNode->right;		// SearchNode 이전 노드의 오른쪽 자식 노드를 SearchNode의 오른쪽 자식 노드로 지정
					free(SearchNode);							// 입력된 키 값을  가지고 있는 노드를 삭제
					return 0;
				}

			}else if((SearchNode->left != NULL) && (SearchNode->right == NULL)){	
				if(temp_Search->left == SearchNode){			// SearchNode가 이전 노드의 왼쪽 자식 노드이면
					temp_Search->left = SearchNode->left;		// SearchNode 이전 노드의 왼쪽 자식 노드를 SearchNode의 왼쪽 자식 노드로 지정
					free(SearchNode);							// 입력된 키 값을 가지고 있는 노드를 삭제
					return 0;
				}else if(temp_Search->right == SearchNode){		// SearchNode가 이전 노드의 오른쪽 자식 노드이면
					temp_Search->right == SearchNode->left;		// SearchNode 이전 노드의 오른쪽 자식 노드를 SearchNode의 왼쪽 자식 노드로 지정
					free(SearchNode);							// 입력된 키 값을 가지고 있는 노드를 삭제
					return 0;
				}

			}else if((SearchNode->left != NULL) && (SearchNode->right  != NULL)){	// 자식노드가 두쪽 다 있을 경우 3번째 케이스
				if(temp_Search->left == SearchNode){			// SearchNode가 이전 노드의 왼쪽 자식 노드이면
					FindMinNode = SearchNode->right;			// 오른쪽 트리에서 가장 작은 노드를 찾기 위해
					while(1){									// 반복문 실행
						if(FindMinNode->left != NULL){			// 찾고자 하는 가장 작은 노드의 왼쪽 자식 노드가 비어있지 않을 경우
							temp_Find = FindMinNode;			// [찾고자 하는 가장 작은 노드]의 이전 노드를 FindMinNode로 지정
							FindMinNode = FindMinNode->left;	// [찾고자 하는 가장 작은 노드]를 왼쪽 자식노드로 이동

						}else if(FindMinNode->right != NULL){	// [찾고자 하는 가장 작은 노드]의 왼쪽은 비어있지만 오른쪽 자식 노드가 비어있지 않을 경우
							temp_Find = FindMinNode;			// [찾고자 하는 가장 작은 노드]의 이전 노드를 FindMinNode로 지정
							FindMinNode = FindMinNode->right;	// [찾고자 하는 가장 작은 노드]를 오른쪽 자식 노드로 이동

						}else{									// [찾고자 하는 가장 작은 노드]를 찾으면
							if(temp_Find->left == FindMinNode){	// [찾고자 하는 가장 작은 노드]가 이전노드의 왼쪽 자식노드 일 경우
								temp_Find->left = NULL;			// 이전노드의 왼쪽 자식노드를 NULL로 지정
								temp_Search->left = FindMinNode;		// [삭제할 노드]의 이전 노드의 왼쪽 자식노드를 [찾고자 하는 노드]로 지정
								FindMinNode->left = SearchNode->left;	// [찾고자 하는 노드]의 왼쪽 자식 노드를 [삭제할 노드]의 왼쪽 자식 노드로 지정
								FindMinNode->right = SearchNode->right;	// [찾고자 하는 노드]의 오른쪽 자식 노드도 지정
								free(SearchNode);						// 입력된 키 값을 가지고 있는 노드 삭제
								return 0;

							}else if(temp_Find->right == FindMinNode){	// [찾고자 하는 가장 작은 노드]가 이전 노드의 오른쪽 자식 노드일 경우
								temp_Find->right = NULL;				// [찾고자 하는 노드]의 이전 노드의 오른족 자식노드를 NULL로 지정
								temp_Search->left = FindMinNode;		// [삭제할 노드]의 이전 노드의 왼쪽 자식노드를 [찾고자 하는 노드]로 지정
								FindMinNode->left = SearchNode->left;	// [찾고자 하는 노드]의 왼족 자식 노드를 [삭제할 노드]의 왼쪽 자식 노드로 지정
								FindMinNode->right = SearchNode->right;	// [찾고자 하는 노드]의 오른쪽 자식 노드도 지정
								free(SearchNode);						// 입력된 키 값을 가지고 있는 노드 삭제
								return 0;
							}
							
						} 
						break;		// 반복문 탈출!
					}


				}else if(temp_Search->right == SearchNode){				// SearchNode가 이전 노드의 오른쪽 자식 노드이면
					FindMinNode = SearchNode->right;					// 오른쪽 트리에서 가장 작은 노드를 찾기 위해
					while(1){											// 반복문 실행
						if(FindMinNode->left != NULL){					// [찾고자 하는 노드]의 왼쪽 자식 노드가 비어있지 않으면
							temp_Find = FindMinNode;					// [찾고자 하는 노드]의 이전노드를 FindMinNode로 지정
							FindMinNode = FindMinNode->left;			// [찾고자 하는 노드]는 왼쪽 자식노드로 이동

						}else if(FindMinNode->right != NULL){			// [찾고자 하는 노드]의 오른쪽 자식 노드가 비어있지 않으면
							temp_Find = FindMinNode;					// [찾고자 하는 노드]의 이전노드를 FindMinNode로 지정
							FindMinNode = FindMinNode->right;			// [찾고자 하는 노드]는 오른쪽 자식노드로 이동

						}else{											// [찾고자 하는 가장 작은 노드]를 찾으면
							if(temp_Find->left == FindMinNode){			// [찾고자 하는 가장 작은 노드]가 이전노드의 왼쪽 자식노드 일 경우
								temp_Find->left = NULL;					// 이전노드의 왼쪽 자식노드를 NULL로 지정
								temp_Search->right = FindMinNode;		// [삭제할 노드]의 이전 노드의 왼쪽 자식노드를 [찾고자 하는 노드]로 지정
								FindMinNode->left = SearchNode->left;	// [찾고자 하는 노드]의 왼쪽 자식 노드를 [삭제할 노드]의 왼쪽 자식 노드로 지정
								FindMinNode->right = SearchNode->right;	// [찾고자 하는 노드]의 오른쪽 자식 노드도 지정
								free(SearchNode);						// 입력된 키 값을 가지고 있는 노드 삭제
								return 0;
							}else if(temp_Find->right == FindMinNode){	// [찾고자 하는 가장 작은 노드]가 이전 노드의 오른쪽 자식 노드일 경우
								temp_Find->right = NULL;				// [찾고자 하는 노드]의 이전 노드의 오른족 자식노드를 NULL로 지정
								temp_Search->right = FindMinNode;		// [삭제할 노드]의 이전 노드의 왼쪽 자식노드를 [찾고자 하는 노드]로 지정
								FindMinNode->left = SearchNode->left;	// [찾고자 하는 노드]의 왼족 자식 노드를 [삭제할 노드]의 왼쪽 자식 노드로 지정
								FindMinNode->right = SearchNode->right;	// [찾고자 하는 노드]의 오른쪽 자식 노드도 지정
								free(SearchNode);						// 입력된 키 값을 가지고 있는 노드 삭제
								return 0;
							}
						} 
					}
					break;		// 반복문 탈출!
				}

			}
		}
	}
	printf("key does not Exist!!");			// 해당 키값을 가진 노드가 없을 경우 오류 메세지 출력
	return 0;					// 함수 종료.
}


void freeNode(Node* ptr)			// 해당 노드에 할당된 메모리를 해제시켜주기 위한 함수
{
	if(ptr) {						// 노드가 비어있지 않으면
		freeNode(ptr->left);		// 노드의 왼쪽 자식노드에 할당된 메모리 해제
		freeNode(ptr->right);		// 오른쪽 자식 노드에 할당된 메모리 해제
		free(ptr);					// 노드에 할당된 메모리 해제
	}
}

int freeBST(Node* head)				// 이진트리에 있는 노드들에게 할당된 메모리를 해제시켜 주기 위한 함수
{

	if(head->left == head)			// 트리가 비어있으면
	{
		free(head);					// 헤더노드에 할당된 메모리해제
		return 1;					// 함수 종료
	}

	Node* p = head->left;			// 트리가 비어있지 않으면

	freeNode(p);					// 트리 안에있는 노드들의 메모리 해제

	free(head);						// 헤더노드에 할당된 메모리 해제
	return 1;						// 함수 종료
}



Node* pop()							// Stack에 들어있는 값을 Pop하기 위한 함수
{
    return stack[top--];
}

void push(Node* aNode)				// Stack에 값을 Push하기 위한 함수
{
    stack[++top] = aNode;
}



Node* deQueue()
{
	if(front == rear){								// 큐가 비워져있으면
        printf("Circular Queue Is Empty!");;		// 비워져있을 경우 경고 출력
    }
	else {											// 원소가 들어있을 경우
    	front = (front + 1) % MAX_QUEUE_SIZE;		// front값을 증가시키고 (POP)
		return queue[front];						// Pop하여 원소를 빼냄
	}
}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;				// 원소를 넣으면 rear의 값이 증가해야 하므로

	if(rear == front){								// Queue의 rear과 front가 같으면
		if(rear == 0 || front == 0){ 				// rear이 0이거나 front가 0이면
			rear = MAX_QUEUE_SIZE -1;				// rear에 MAX_QUEUE_SIZE -1을 저장한다.
		}
		else 										// 둘중 하나가가 0이 아니면
			rear = (rear - 1) % MAX_QUEUE_SIZE;		// rear에 (rear -1) % MAX_QUEUE_SIZE를 저장한다
			printf("Circular Queue Is Full!");		// 꽉 채워져 있으므로 경고 출력
	}else
		queue[rear] = aNode;			// 꽉 채워져있지 않을경우 Queue에 원소를 Push
}
