/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {           // 트리에 들어갈 노드들을 표현하기 위한 구조체 node 
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);    // 트리를 형성하기 위해, 또는 초기화를 하기 위한 함수

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */
void Free_Node(Node* ptr); /* free all nodes allocated to the tree */
/* you may add your own defined functions if necessary */


int main()
{
	char command;       // 명령어를 받기위한 변수 command
	int key;            // 키 값을 할당받을 변수 key
	Node* head = NULL;  // 트리의 헤드노드가 될 포인터 변수 head
	Node* ptr = NULL;	/* temp */
    
    printf("[----- [KwonDongCheon] [2017038072] -----]\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);     // 명령어 입력

		switch(command) {
		case 'z': case 'Z':         // z or Z를 입력 받으면
			initializeBST(&head);   // initializeBST()함수 실행
			break;
		case 'q': case 'Q':         // q or Q를 입력 받으면
			freeBST(head);          // 트리에 있는 노드들의 메모리를 해제
			break;
		case 'n': case 'N':         // n or N을 입력 받으면
			printf("Your Key = ");
			scanf("%d", &key);      // key 값을 입력 받고
			insert(head, key);      // key값을 가지고 있는 노드 삽입
			break;
		case 'd': case 'D':         // d or D를 입력 받으면
			printf("Your Key = ");
			scanf("%d", &key);      // key 값을 입력 받고
			deleteLeafNode(head, key);  // 키 값을 가지고 있는 리프 노드가 있으면 삭제
			break;
		case 'f': case 'F':         // f or F를 입력 받으면
			printf("Your Key = ");
			scanf("%d", &key);      // key 값을 입력 받고
			ptr = searchIterative(head, key);   // key값을 가진 노드를 탐색
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':         // s or S를 입력받으면
			printf("Your Key = ");
			scanf("%d", &key);      // key값을 입력받으면
			ptr = searchRecursive(head->left, key);     // key 값을 가진 노드가 있는지 탐색
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':         // i or I를 입력받으면
			inorderTraversal(head->left);   // 중위 순회에 따라 키 값을 출력
			break;
		case 'p': case 'P':         // p or P를 입력받으면
			preorderTraversal(head->left);  // 전위 순회에 따라 키 값을 출력
			break;
		case 't': case 'T':         // t or T를 입력받으면
			postorderTraversal(head->left); // 후위 순회에 따라 키 값을 출력
			break;
		default:                    // 그 외 다른 명령어를 입력받으면
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");  // 오류 메세지 출력
			break;
		}

	}while(command != 'q' && command != 'Q');   // q or Q를 입력받으면 빠져나간다.

	return 1;   // 프로그램 종료.
}

int initializeBST(Node** h) {       // 트리를 형성하기 위한, 또는 초기화를 하기 위한 함수

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)        // 중위 순회에 따라 노드에 들어있는 키 값을 출력하기 위한 함수
{
  if (ptr){                             // ptr이 NULL이 아니면
      inorderTraversal(ptr->left);      // inorderTraversal()에 왼쪽 링크 필드를 인자로 넣고 실행
      printf("[ %d ]  ", ptr->key);     // [해당 노드]의 키 값을 출력
      inorderTraversal(ptr->right);     // inorderTraversal()에 오른쪽 링크 필드를 인자로 넣고 실행
  }
}

void preorderTraversal(Node* ptr)       // 전위 순회에 따라 노드에 들어있는 키 값을 출력하기 위한 함수
{
    if(ptr){                            // ptr이 NULL이 아니면
        printf("[ %d ]  ", ptr->key);   // [해당 노드]의 키 값을 출력
        preorderTraversal(ptr->left);   // preorderTraversal()에 왼쪽 링크 필드를 인자로 넣고 실행
        preorderTraversal(ptr->right);  // preorderTraversal()에 오른쪽 링크 필드를 인자로 넣고 실행
    }
}

void postorderTraversal(Node* ptr)      // 후위 순회에 따라 노드에 들어있는 키 값을 출력하기 위한 함수
{
    if(ptr){                            // ptr이 NULL이 아니면
        postorderTraversal(ptr->left);  // postorderTraversal()에 왼쪽 링크 필드를 인자로 넣고 실행
        postorderTraversal(ptr->right); // postorderTraversal()에 오른쪽 링크 필드를 인자로 넣고 실행
        printf("[ %d ]  ", ptr->key);   // [해당 노드]의 키 값을 출력
    }
}

int insert(Node* head, int key)         // 키 값을 가진 노드를 트리에 삽입하기 위한 함수
{
    Node* node = (Node*)malloc(sizeof(Node));   // [삽입할 노드]
    Node* temp = NULL;                      // 노드를 삽입할 위치를 찾아줄 포인터 변수 temp 
    if (head->left){                        // 헤드 노드가 초기 상태가 아니면 (트리가 형성되어 있으면)
        temp = head->left;                  // [temp]노드를 트리의 루트 노드로 지정
        while(temp){
            if(temp->key < key){            // 키 값이 [temp]의 키 값보다 클 경우
                if(!(temp->right)){         // [temp 노드]의 오른쪽 자식노드가 비어있으면
                    temp->right = node;     // [temp 노드]의 오른쪽 자식 노드를 [삽입할 노드]로 지정
                    node->key = key;        // [삽입한 노드]에 key 값 할당
                    node->left = NULL;      // [삽입한 노드]는 리프노드이므로 왼쪽 링크 필드에 NULL 지정
                    node->right = NULL;     // [삽입한 노드]의 오른쪽 링크 필드에 NULL 지정
                    return 0;
                }                           // [temp 노드]의 오른쪽 자식노드가 비어있지 않으면
                temp = temp->right;         // 노드를 삽입하기 위해 계속해서 key 값 비교

            } else if(key <temp->key){      // 키 값이 [temp]의 키 값보다 작을 경우
                if(!(temp->left)){          // [temp 노드]의 왼쪽 자식 노드가 비어있을 경우
                    temp->left = node;      // [temp 노드]의 왼쪽 자식 노드를 [삽입할 노드]로 지정
                    node->key = key;        // [삽입한 노드]에 key 값 할당
                    node->left = NULL;      // [삽입한 노드]는 리프 노드이므로 왼쪽 링크 필드에 NULL 지정
                    node->right = NULL;     // [삽입한 노드]의 오른쪽 링크 필드도 NULL 지정
                    return 0;
                }                           // [temp 노드]의 왼쪽 자식 노드가 비어있지 않으면
                temp = temp->left;

            } else if(temp->key == key){    // 만약 트리 안에 key값에 해당되는 노드가 있으면
                free(node);                 // [삽입할 노드]를 삭제하고
                return 0;                   // 삽입을 무시하고 함수를 끝냄
            }
        }
    }                                       // 헤드노드가 초기 상태일 경우 (트리가 형성되어 있지 않으면)
    head->left = node;                      // 헤드의 왼쪽 링크필드에 [삽입할 노드]를 지정
    node->key = key;                        // [삽입한 노드]에 key 값 할당
    node->left = NULL;                      // [삽입한 노드]가 루트노드이자, 자식노드가 없으므로
    node->right =NULL;                      // 왼쪽, 오른쪽 노드에 NULL 지정
    return 0;                               // 함수 종료
}

int deleteLeafNode(Node* head, int key)     // 키 값을 가지고 있는 리프 노드를 삭제하기 위한 함수
{
    Node* temp = NULL;                      // 삭제할 노드를 위치 찾기 위한 포인터 변수 temp
    Node* pre_temp = NULL;                  // 포인터 변수 [temp가 가리키는 노드]의 [이전노드]를 가리키기 위한 변수 pre_temp

    if(head->left){                         // 트리가 비어있지 않으면
        pre_temp = head;                    // pre_temp가 헤드 노드를 가리키도록 지정
        temp = head->left;                  // temp는 루트 노드를 가리키도록 지정

        while(temp){                        // temp가 비어있지 않으면(루트 노드가 있으면)
            if(temp->key < key){            // [temp가 가리키는 노드]의 키 값이 할당받은 키 값보다 작을 때,
                if(!temp->right){           // [temp의 오른쪽 자식 노드]가 없으면
                    printf("※Key does not Exist※\n");       // 오류 메세지 출력
                    return 0;               // 프로그램 종료
                }                           // [temp의 오른쪽 자식 노드]가 존재하면
                pre_temp = temp;            // 다음 자식노드로 넘어가기 위해 pre_temp가 temp를 가리키도록 지정
                temp = temp->right;         // temp는 다음 노드로 이동

            }else if(key < temp->key){      // 할당받은 키 값이 [temp가 가리키는 노드]의 키 값보다 작을 경우
                if(!temp->left){            // [temp의 왼쪽 자식 노드]가 존재하지 않으면
                    printf("※Key does not Exist※\n");       // key에 해당하는 노드가 없다는 메세지 출력
                    return 0;               // 프로그램 종료.
                }                           // [temp의 왼쪽 자식 노드]가 존재하면
                pre_temp = temp;            // 다음 자식 노드로 넘어가기 위해 pre_temp가 temp를 가리키도록 지정
                temp = temp->left;          // temp는 다음 노드로 이동

            }else if(temp->key = key){      // [temp가 가리키는 노드]의 키 값이 key 값과 같은 경우
                if((temp->left == NULL) && (temp->right == NULL)){      // temp의 왼쪽, 오른쪽 자식 노드가 존재하지 않으면(리프 노드이면)
                    if(pre_temp->left == temp){     // pre_temp의 왼쪽 자식 노드가 temp 이면
                        free(temp);                 // 리프 노드인 temp를 메모리 해제
                        pre_temp->left = NULL;      // pre_temp의 왼쪽 자식 노드가 사라졌으므로 NULL 지정
                        return 0;                   // 프로그램 종료
                    }else if(pre_temp->right == temp){  // pre_temp의 오른쪽 자식 노드가 temp 이면
                        free(temp);                 // 리프 노드인 temp를 메모리 해제
                        pre_temp->right = NULL;     // pre_temp의 오른쪽 노드가 사라졌으므로 NULL 지정
                        return 0;                   // 프로그램 종료
                    }
                }
                printf("The node that has the key is not a leaf node.\n");  // 리프 노드에 대한 key 값이 아니면 오류메세지 출력
                return 0;           // 프로그램 종료.
            }
        }
    }
    printf("The Tree is not Exist.\n");     // 트리가 형성되어있지 않을 경우 오류 메세지 출력
}

Node* searchRecursive(Node* ptr, int key)   // 루트 노드부터 시작
{
    if((ptr == NULL) || (ptr->key == key)){     // ptr이 NULL이거나 해당하는 key값이 같으면
        return ptr;                         // ptr 반환
    }
    else if(ptr->key < key){                // ptr의 key값이 인자로 들어온 key값보다 작으면
        return searchRecursive(ptr->right, key);    // ptr의 오른쪽 자식노드로 탐색 시작
    }else if(ptr->key > key){               // ptr의 key값이 인자로 들어온 key값보다 크면
        return searchRecursive(ptr->left, key);     // ptr의 왼쪽 자식 노드로 탐색 시작
    }
}

Node* searchIterative(Node* head, int key)  // 헤드 노드부터 시작
{
    Node* temp = NULL;                  // key값을 가진 노드를 찾기 위한 포인터 temp 선언
    temp = head->left;                  // temp가 루트 노드를 가리키도록 
    
    while(temp){                        // temp가 NULL이 아니면 반복문 재생
        if(temp->key < key){            // 키값이 [temp 노드]의 키값보다 크면
            temp = temp->right;         // 다음 노드의 키값을 확인하기 위해 오른쪽 자식 노드로 이동
        }else if(key < temp->key){      // [temp 노드] 키 값이 입력받은 key값보다 크면
            temp = temp->left;          // 다음 노드의 키 값을 확인하기 위해 왼쪽 자식 노드로 이동
        }
        else if(temp->key == key){      // [temp 노드] 키 값이 입력받은 key값과 같으면
            return temp;                // temp 반환
        }
    }
    return temp;                        // NULL을 리턴
}


int freeBST(Node* head)                 // 트리에 있는 노드들의 메모리를 해제해주기 위한 함수
{
    Free_Node(head->left);              // Free_Node함수를 호출하여 노드들의 메모리를 해제
    free(head);                         // 이후 헤드 노드의 메모리를 해제
    return 0;                           // 함수 종료
}
void Free_Node(Node* ptr)               // 트리에 있는 노드들을 순회하며 메모리를 해제하기 위한 함수
{
  if (ptr){                             // ptr이 NULL 이 아니면
    Free_Node(ptr->left);               // ptr이 가리키는 노드의 왼쪽 자식 노드로 이동
    Free_Node(ptr->right);              // 이후 ptr이 가리키는 노드의 오른쪽 자식 노드로 이동
    free(ptr);                          // 이후 ptr이 가리키는 노드의 메모리 해제
  }
}
