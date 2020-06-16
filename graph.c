/* 다음과 같이 구현되도록 코드를 작성하였습니다.
*  1,5까지 차례대로 입력하고 다리를 놓아주면
*  Vertex    Edge                                   Vertex      Edge
*    1   ->   2 -> 3 -> NULL    3을 삭제할 경우,       1    ->    2 -> NULL
*    2   ->   1 -> 4 -> NULL                          2    ->    1 -> 4 -> NULL
*    3   ->   1 -> NULL                              NULL
*    4   ->   2 -> 5 -> NULL                          4    ->    2 -> 5 -> NULL
*    5   ->   4 -> NULL                               5    ->    4 -> NULL
*
* 여기서 Vertex 6을 추가하여 (1, 6)의 다리를 놓아주면
*  Vertex   Edge
*    1   ->   2 -> 6 -> NULL
*    2   ->   1 -> 4 -> NULL
*    6   ->   1 -> NULL
*    4   ->   2 -> 5 -> NULL
*    5   ->   4 -> NULL
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 20 /* you can change value 20 */

typedef struct Vertex {
    int num;                /* vertex number */
    struct Vertex* link;    /* link to a next adjacent vertext */
} Vertex;

typedef struct VertexHead {
    Vertex* head;           /* linked list of all adjacent vertices */
} VertexHead;

typedef struct Graph {
    VertexHead* vlist;      /* list of all vertices: vlist[MAX_VERTEX] */
} Graph;


Graph* createGraph(Graph* graph);  /* empty graph creation */
int destroyGraph(Graph* graph); /* deallocating all allocated memory */
int insertVertex(Graph* graph, int v_num); /* vertex insertion */
int deleteVertex(Graph* graph, int v_num); /* vertex deletion */
int insertEdge(Graph* graph, int v1_num, int v2_num);   /* new edge creation between two vertices */
int deleteEdge(Graph* graph, int v1_num, int v2_num);   /* edge removal */
void depthFS(Graph* graph);      /* depth first search using stack */
void breadthFS(Graph* graph);    /* breadth first search using queue */
int printGraph(Graph* graph);   /* printing graph with vertices and edges */
int Check_vlist(Graph* graph, int vertex);      // vlist에 해당하는 Vertex가 존재하는지 확인하기 위한 함수
int Check_visit_list(Graph* graph, Vertex* Search_Node, int* visit_list);   // 해당 Vertex가 방문했는지 기록하기 위한 함수
Vertex* Move_next(Graph* graph, Vertex* Search_Vertex);     // Edge의 num과 같은 값을 가진 Vertex로 이동하기 위한 함수

Vertex* DFS_stack[MAX_VERTEX];      // 깊이 우선 탐색을 스택으로 나타내기 위한 변수
int top = -1;                       // 스택에 마지막으로 들어온 원소의 위치를 나타내는 top

Vertex* pop();                      // 스택에 있는 원소를 빼내기 위한 함수
void push(Vertex* push_Vertex);     // 스택에 원소를 삽입하기 위한 함수

Vertex* BFS_Queue[MAX_VERTEX];      // 너비 우선 탐색을 큐로 나타내기 위한 변수
int front = -1;						// 원형 큐에서 사용하기 위한 변수 front
int rear = -1;                      // 원형 큐에서 사용하기 위한 변수 rear

Vertex* deQueue();                      // 큐에 있는 원소를 빼내기 위한 함수
void enQueue(Vertex* Search_Vertex);    // 큐에 원소를 삽입하기 위한 함수

int vertex_count = 0;          // 그래프에 삽인된 Vertex들의 개수를 세기 위한 변수 vertex_count
int delete_count = 0;          // 그래프에서 삭제된 Vertex들의 개수를 세기 위한 변수 delete_count

int main() {
    char command;                                   // 명령어를 입력 받기 위한 변수 command
    int v1_num;                                     // 그래프에 Vertex를 입력받기 위한 변수 v1_num
    int v2_num;                                     // 그래프에 Edge를 insert할 때, Vertex 두개를 받기위한 변수 v2_num
    Graph* graph = NULL;                            // 그래프를 나타내기 위한 포인터 변수 graph

    printf("[----- [Kwon_DongCheon] [2017038072] -----]\n");

    do {
        printf("----------------------------------------------------------------\n");
        printf("                         Graph                                  \n");
        printf("----------------------------------------------------------------\n");
        printf(" CreateGraph    = z          Print         = p  \n");
        printf(" Insert Vertex  = i          Delete Vertex = d  \n");
        printf(" Insert Edge    = e          Delete Edge   = g  \n");
        printf(" DepthFS        = f          BreadthFS     = b  \n");
        printf(" Quit           = q  \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);             // 명령어 입력

        switch (command) {
        case 'z': case 'Z':                 // z or Z를 입력 받으면
            graph = createGraph(graph);     // 그래프 초기화
            break;
        case 'p': case 'P':                 // p or P를 입력 받으면
            printGraph(graph);              // 그래프에 있는 Vertex들을 출력
            break;
        case 'i': case 'I':                 // i or I를 입력 받으면
            printf("Vertex Number : ");     
            scanf("%d", &v1_num);           // 양의 정수 입력
            insertVertex(graph, v1_num);    // Vertex를 삽입한다.
            break;
        case 'd': case 'D':                 // d or D를 입력 받으면
            printf("Vertex Number : ");
            scanf("%d", &v1_num);           // 양의 정수 입력
            deleteVertex(graph, v1_num);    // 해당하는 Vertex 삭제
            break;
        case 'e': case 'E':                     // e or E를 입력 받으면
            printf("Vertex Number (ex:1 2) : ");
            scanf("%d %d", &v1_num, &v2_num);   // 다리를 형성할 Vertex들을 입력
            insertEdge(graph, v1_num, v2_num);  // (v1_num, v2_num) Edge 형성
            break;
        case 'g': case 'G':                     // e or E를 입력 받으면
            printf("Vertex Number (ex:1 2) : ");
            scanf("%d %d", &v1_num, &v2_num);   // 다리를 삭제할 Vertex들을 입력
            deleteEdge(graph, v1_num, v2_num);  // 해당 Edge를 삭제한다.
            break;
        case 'f': case 'F':                 // f or F를 입력 받으면
            depthFS(graph);                 // 깊이 우선 탐색 함수 호출
            printf("\n");
            break;
        case 'b': case 'B':                 // t or T를 입력 받으면
            breadthFS(graph);               // 너비 우선 탐색 함수 호출
            printf("\n");
            break;
        case 'q': case 'Q':                 // q or Q를 입력 받으면
            destroyGraph(graph);            // 프로그램을 종료하기 전, 동적할당 받은 메모리들을 해제시켜주기 위한 함수 호출
            break;
        default:                            // 그 외 다른 명령어를 입력 받으면
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");      // 오류 메세지 출력
            break;
        }

    } while (command != 'q' && command != 'Q');   // q or Q를 입력 받으면 반복문을 빠져나온다.

    return 1;           // 프로그램 종료.
}


Graph* createGraph(Graph* graph) {      /* empty graph creation */
    int i = 0;      // 반복문을 운영하기 위한 변수 i

    if (graph != NULL) {        // 그래프가 비어있지 않으면
        destroyGraph(graph);    // 초기화 시키기 위해 동적할당을 받은 메모리들을 해제시켜준다.
    }

    graph = (Graph*)malloc(sizeof(Graph));      // 우선 graph를 동적할당 받고
    graph->vlist = (VertexHead*)malloc(sizeof(VertexHead) * MAX_VERTEX);    // Vertex들이 표현될 공간인 vlist를 MAX_VERTEX 크기만큼 동적할당 

    for (i = 0; i < MAX_VERTEX; i++) {          // vlist의 각 head들을 NULL로 초기화
        ((graph->vlist) + i)->head = NULL;
    }

    return graph;               // 형성된, 초기화된 그래프를 반환
}


int destroyGraph(Graph* graph) {    /* deallocating all allocated memory */
    int i = 0;                      // 반복문을 운영하기 위한 변수 i
    Vertex* temp = NULL;            // Vertex와 Edge를 가리킬 포인터 변수 temp
    Vertex* delete_Vertex = NULL;   // 삭제할 Vertex를 가리킬 포인터 변수 delete_Vertex

    if (graph == NULL) {            // 그래프가 이미 비어있으면
        return 1;                   // 정상 종료
    }

    for (i = 0; i < delete_count + vertex_count; i++) {     // 그래프의 동적할당된 메모리들을 반복문을 이용해 해제
        temp = (graph->vlist + i)->head;            // temp를 각 vlist의 head로 지정

        if ((graph->vlist + i)->head != NULL) {     // 만약 vlist의 head에 Vertex가 존재하면

            while (temp != NULL) {
                delete_Vertex = temp;               // vlist의 head부터 Edge까지 메모리 해제
                temp = temp->link;
                free(delete_Vertex);
            }
            (graph->vlist + i)->head = NULL;        // vlist의 head가 없어졌으므로 NULL로 지정
        }
    }
    free(graph->vlist);         // 동적할당 받았던 vlist의 메모리 해제
  
    free(graph);                // 동적할당 받았던 graph의 메모리 해제
    graph = NULL;               // 이후 graph를 NULL로 지정

    delete_count = 0;           // Vertex들이 모두 없어졌으므로 delete_count = 0;
    vertex_count = 0;           // Vertex들이 없어졌으므로 vertex_count = 0
    return 1;
}

/* 이미 들어간 Vertex가 있었을 경우도 생각해야함. */

int insertVertex(Graph* graph, int v_num) {      /* vertex insertion */
    int i = 0;                  // 반복문을 운용하기 위한 변수 i

    if (graph == NULL) {                            // 그래프가 형성되어있지 않을 경우
        printf("You didn't form a graph.\n");       // 오류메세지 출력
        return 0;                                   // 함수 종료
    }

    if(Check_vlist(graph, v_num) == 1){             // 벌텍스가 이미 존재할 경우 Check_vlist()함수에서 1을 반환
        printf("The vertex is already Exist\n");    // 이미 존재한다는 메세지 출력
        return 1;                                   // 함수 종료
    }
    
    Vertex* temp = (Vertex*)malloc(sizeof(Vertex)); // Vertex를 삽입하기 위해 동적할당을 받음
    i = 0;  // i = 0부터

    while ((graph->vlist + i)->head != NULL) {      // 그래프에 들어있는 Vertex들의 개수가 Max_Vertex를 넘었는지 확인하기 위해
        i++;                                        // 반복문을 이용
    }

    if (i == MAX_VERTEX) {                          // 중간 점검. 만약 graph에서 Vertex의 최댓값을 넘었을 경우(더이상 못넣을 경우)
        printf("Maximum Vertex value exceeded.\n"); // 오류메세지 출력
        return 0;                                   // 함수 종료
    }

    temp->num = v_num;                  // 삽입할 Vertex에 입력한 정수를 저장
    temp->link = NULL;                  // Vertex를 삽입하므로 Edge가 없기때문에 NULL로 저장
    (graph->vlist + i)->head = temp;    // 해당 Vertex를 vlist에 삽입

    if(vertex_count++ == 0)             // 만약 Vertex가 첫번째로 삽입되는 Vertex이고
        if(delete_count > 0)            // 이미 이전에 삭제된 Vertex가 있고 그 값이 증가해 있다면
            delete_count--;             // delete_count값 감소

    if(vertex_count + delete_count >= MAX_VERTEX){
        vertex_count = 0, delete_count = 0;
        for(i = 0; i < MAX_VERTEX; i++){
            if((graph->vlist+i)->head != NULL)
                vertex_count++;
        }
        delete_count = MAX_VERTEX - vertex_count;
    }

    return 1;
}

/* 해당 Vertex를 삭제하였을 경우, 기존에 있던 Edge도 삭제해야함 */
int deleteVertex(Graph* graph, int v_num) {               /* vertex deletion */

    if (graph == NULL) {                            // 그래프가 형성되어있지 않을 경우
        printf("You didn't form a graph.\n");       // 오류메세지 출력
        return 0;                                   // 함수 종료
    }

    int i = 0;                      // 반복문을 운영하기 위한 변수 i
    Vertex* temp = NULL;            // 삭제할 Vertex와 Edge를 가리킬 포인터 변수 temp
    Vertex* Delete_Vertex = NULL;   // 해당 Vertex의 메모리를 해제할 포인터 변수 Delete_Vertex

    if(Check_vlist(graph, v_num) == 0){     // 입력된 값이 그래프의 Vertex에 존재하는지 확인해주는 함수
        printf("You have entered Vertex that does not exist in the graph.\n");  // 해당 Vertex값이 존재하지 않으면
        return 0;                           // 오류메세지를 출력하고 함수 종료
    }


    for (i = 0; i < vertex_count + delete_count; i++) {     // 해당 값이 존재하면 반복문 시작
        if((graph->vlist+i)->head != NULL){
            if ((graph->vlist + i)->head->num == v_num) {           // vlist의 헤드. 즉, vertex가 v_num이면
                                                                    // 해당 Vertex가 있는 연결리스트 삭제
                temp = (graph->vlist + i)->head;                    // temp가 vlist의 Vertex를 가리키도록 지정

                while(temp != NULL){                                // temp가 NULL이 될때까지
                    Delete_Vertex = temp;                           // 해당 Vertex의 인접리스트(Edge)들을 삭제
                    temp = temp->link;                              // Vertex를 포함하여 삭제
                    free(Delete_Vertex);
                }

                (graph->vlist + i)->head = NULL;                    // 해당 Vertex를 삭제하였으므로 NULL 로 지정
                vertex_count--;                                     // 삽입되어 있는 Vertex의 개수 감소
                if(vertex_count == 0)                               // 만약 마지막 Vertex를 삭제했으면
                    delete_count = 0;                               // delete_count = 0
                else                                                // 마지막 Vertex를 삭제한게 아니면
                    delete_count++;                                 // delete_count 증가


            }
            else if((graph->vlist + i)->head->num != v_num){        // vlist의 헤드. 즉, Vertex가 v_num이 아니면 
                                                                    // 해당 Vertex의 Edge 삭제
                temp = (graph->vlist + i)->head;                    // temp를 Vlist의 Vertex로 지정
                Delete_Vertex = temp->link;                         // Delete_Vertex를 temp의 다음 노드로 지정

                while(Delete_Vertex != NULL){                       // Delete_Vertex가 NULL이 될떄까지
                    if(Delete_Vertex->num != v_num){                // Delete_Vertex->num이 입력된 값과 같지 않으면
                        temp = temp->link;                          // 값을 찾기위해 이동
                        Delete_Vertex = temp->link;
                    }
                    else if(Delete_Vertex->num == v_num){           // Delete_Vertex->num이 입력된 값과 같으면
                        temp->link = Delete_Vertex->link;           // temp의 link를 Delete_Vertex의 다음 노드로 지정하고
                        free(Delete_Vertex);                        // Delete_Vertex를 삭제
                        break;
                    }
                }
            }
        }
    }
}

/* 이미 놓여진 Edge가 있었을 경우도 생각 해야함. */
int insertEdge(Graph* graph, int v1_num, int v2_num) {        /* new edge creation between two vertices */

    if(Check_vlist(graph, v1_num) == 0 || Check_vlist(graph, v2_num) == 0){     // v2_num, v1_num이 그래프에 있는지 조사
        printf("You have entered Vertex that does not exist in the graph.\n");  // 둘중 하나라도 없으면 오류메시지 출력
        return 0;   // 함수종료
    }

    int i = 0;          // 반복문을 운용하기 위한 변수 i
    Vertex* V1 = (Vertex*)malloc(sizeof(Vertex));       // (a ,b)일 경우 a, b 양쪽에 대입해야하므로
    Vertex* V2 = (Vertex*)malloc(sizeof(Vertex));       // 동적할당을 두개 선언해준다.
    Vertex* temp = NULL;                                // 삽입될 위치를 가리키는 temp

    V1->num = v1_num;               // 각 V1,V2에 입력된 값을 대입
    V2->num = v2_num;               

    for(i = 0; i < delete_count + vertex_count; i++){   // 반복문 시작
        if((graph->vlist+i)->head != NULL){             // 만약 Vertex가 존재하면
            if((graph->vlist+i)->head->num == v1_num){  // 해당 Vertex가 입력된 값과 같은지 비교

                temp = (graph->vlist + i)->head;        // 만약 값이 같으면 temp를 Vertex로 지정

                while(temp->link != NULL){              // Vertex의 인접리스트(Edge)의 끝에 도달할때까지
                    temp = temp->link;                  // temp 값 이동
                    if(temp->num == v2_num){            // 만약 이미 Edge가 놓여있을 경우
                        printf("The Edge is already Placed.\n");    // 오류 메시지 출력
                        return 1;                       // 함수 종료
                    }
                }                                       // 이미 Edge가 놓여있지 않으면
                temp->link = V2;                        // Vertex의 Edge 마지막에 V2를 이어붙이고
                V2->link = NULL;                        // V2의 link에 NULL 지정
            }
            else if((graph->vlist+i)->head->num == v2_num){ // 만약 Vertex가 입력된 값과 같으면

                temp = (graph->vlist +i)->head;             // temp가 해당 Vertex를 가리키도록 지정

                while(temp->link != NULL){                  // temp가 Vertex의 인접리스트(Edge)의 끝에 도달할때까지
                    temp = temp->link;                      // temp 값 이동
                    if(temp->num == v1_num){                // 만약 이미 (Edge)값이 존재하면
                        printf("The Edge is already Placed.\n");    // 오류메시지 출력
                        return 1;                           // 함수 종료
                    }
                }

                temp->link = V1;                            // Vertex의 인접리스트(Edge)의 마지막에는 V1을 지정
                V1->link = NULL;                            // V1이 마지막 Edge이므로 link에 NULL지정
            }
        }
    }

    return 1;                                               // 함수 종료
}

/* 해당하는 Vertex가 없을 경우를 생각 해야함 */
/* 해당하는 edge가 없을 경우 */
int deleteEdge(Graph* graph, int v1_num, int v2_num) {     /* edge removal */
    int i = 0;                              // 반복문을 운용하기 위한 변수 i
    Vertex* temp = NULL;                    // 삭제할 Edge를 찾기 위한 temp
    Vertex* Delete_Vertex = NULL;           // Edge를 메모리 해제함으로써 삭제하기 위한 Delete_Vertex

    if(Check_vlist(graph, v1_num) == 0 || Check_vlist(graph, v2_num) == 0){     // 입력된 두 값 중 하나라도 그래프에 Vertex에 저장되어있지 않으면
        printf("You have entered Vertex that does not exist in the graph.\n");  // 오류메시지 출력
        return 0;           // 함수종료
    }

    for(i = 0; i < delete_count + vertex_count; i++){           // 반복문 시작
        if((graph->vlist+i)->head != NULL){                     // 만약 Vertex가 존재하고
            if((graph->vlist+i)->head->num == v1_num || (graph->vlist + i)->head->num == v2_num){       // Vertex의 값이 v1_num이나 v2_num과 같으면

                if((graph->vlist + i)->head->num == v1_num){        // Vertex의 값이 v1_num 과 같으면

                    temp = (graph->vlist + i)->head;                // temp가 Vertex를 가리키도록 지정하고
                    Delete_Vertex = temp->link;                     // Delete_Vertex는 temp의 다음 노드를 가리키도록 지정

                    while(Delete_Vertex->num != v2_num){            // Delete_Vertex의 num이 v2_num과 같을 때까지 반복문 실행
                        temp = temp->link;                          // temp를 이동
                        Delete_Vertex = temp->link;                 // Delete_Vertex를 이동
                        if(Delete_Vertex == NULL){                  // 만약 Delete_Vertex가 마지막까지 이동하여 NULL이 되었을 경우
                            printf("Edge %d to %d already does not exist.\n", v1_num, v2_num);      // 오류 메시지 출력
                            return 0;               // 함수종료
                        }
                    }
                    temp->link = Delete_Vertex->link;       // [삭제할 Edge]의 이전 Edge가 [삭제할 Edge]의 다음 Edge를 가리키도록 지정 
                    free(Delete_Vertex);                    // 해당 Edge 삭제
                }
                else if((graph->vlist + i)->head->num == v2_num){       // Vertex의 값이 v2_num 과 같으면
                    temp = (graph->vlist+i)->head;                      // temp가 Vertex를 가리키도록 지정하고
                    Delete_Vertex = temp->link;                         // Delete_Vertex는 temp의 다음 노드를 가리키도록 지정

                    while(Delete_Vertex->num != v1_num){                // Delete_Vertex의 num이 v1_num과 같을 때까지 반복문 실행
                        temp = temp->link;                              // temp를 이동
                        Delete_Vertex = temp->link;                     // Delete_Vertex를 이동
                        if(Delete_Vertex == NULL){                      // 만약 Delete_Vertex가 마지막까지 이동하여 NULL이 되었을 경우
                            printf("Edge %d to %d already does not exist.\n", v1_num, v2_num);      // 오류 메시지 출력
                            return 0;       // 함수종료
                        }
                    }
                    temp->link = Delete_Vertex->link;       // [삭제할 Edge]의 이전 Edge가 [삭제할 Edge]의 다음 Edge를 가리키도록 지정 
                    free(Delete_Vertex);                    // 해당 Edge 삭제
                }
            }
        }
    }
    return 1;
}

void depthFS(Graph* graph) {        /* depth first search using stack */
    int visit_list[MAX_VERTEX];     // 방문했다는 기록을 남기기위한 visit_list[]
    int i = 0;                      // 반복문을 운용하기 위한 변수 i
    Vertex* Search_Vertex = NULL;   // Vertex를 찾아가며 Stack에 push, pop할 포인터 변수 Search_Vertex

    for (i = 0; i < delete_count + vertex_count; i++) { // 반복문 실행
        if ((graph->vlist + i)->head != NULL) {         // Vertex가 존재하는 곳에
            visit_list[i] = 1;                          // visit_list[i] = 1;
        }
    }

    Search_Vertex = graph->vlist->head; // Search_Vertex를 그래프의 첫 Vertex로 지정
    push(Search_Vertex);                // Stack에 push하고 시작
    i = Check_visit_list(graph, Search_Vertex, visit_list); // Search_Vertex가 가리키는 수의 위치를 받아서
    visit_list[i] = 0;                  // Stack에 push하였으므로 방문했다고 표시

    while (top != -1) {                 // Stack이 비어있을 때까지 반복문 실행
        Search_Vertex = pop();          // Search_Vertex에 Stack에 있는 값을 pop하고
        printf(" [ %d ] ", Search_Vertex->num);     // pop된 값을 출력
        Search_Vertex = Move_next(graph, Search_Vertex);    // pop된 값(수)을 가진 Vertex를 찾아 Search_Vertex에 저장

        while(Search_Vertex->link != NULL){         // Search_Vertex의 link필드가 NULL을 가리킬때까지
            Search_Vertex = Search_Vertex->link;    // Search_Vertex 는 다음 노드로 이동
            i = Check_visit_list(graph, Search_Vertex, visit_list);     // 다음 노드로 이동했을때 위치를 i에 저장
            if(i != -1){                            // 만약 visit_list[i] 가 방문하지 않았으면
                visit_list[i] = 0;                  // 해당 Vertex를 방문했다고 지정
                push(Search_Vertex);                // 방문하지 않았던 해당 Vertex를 Stack에 저장
            }
        }
        
    }
}
void breadthFS(Graph* graph) {      /* breadth first search using queue */
    front = 0, rear = 0;                // front와 rear을 0으로 초기화
    int visit_list[MAX_VERTEX];         // 방문했다는 기록을 남기기위한 visit_list[]
    int i = 0;                          // 반복문을 운용하기 위한 변수 i
    Vertex* Search_Vertex = NULL;       // Vertex를 찾아가며 Queue에 enQueue, deQueue할 포인터 변수 Search_Vertex

    for (i = 0; i < delete_count + vertex_count; i++) {     // 반복문 실행
        if ((graph->vlist + i)->head != NULL) {             // Vertex가 존재하는 곳에
            visit_list[i] = 1;                              // visit_list[i] = 1;
        }       
    }

    Search_Vertex = graph->vlist->head;                     // Search_Vertex를 그래프의 첫 Vertex로 지정
    enQueue(Search_Vertex);                                 // Queue에 enQueue하고 시작
    i = Check_visit_list(graph, Search_Vertex, visit_list); // Search_Vertex가 가리키는 수의 위치를 받아서
    visit_list[i] = 0;                                      // Stack에 push하였으므로 방문했다고 표시

    while(front != rear){                                   // Queue가 비어있을 때까지 반복문 실행
        Search_Vertex = deQueue();                          // Search_Vertex에 Queue에 있는 값을 deQueue하고
        printf(" [ %d ] ", Search_Vertex->num);             // deQueue한 값을 출력
        Search_Vertex = Move_next(graph, Search_Vertex);    // deQueue한 값(수)을 가진 Vertex를 찾아 Search_Vertex에 저장

        while(Search_Vertex->link != NULL){                 // Search_Vertex의 link필드가 NULL을 가리킬때까지
            Search_Vertex = Search_Vertex->link;            // Search_Vertex 는 다음 노드로 이동
            i = Check_visit_list(graph, Search_Vertex, visit_list);     // 다음 노드로 이동했을때 위치를 i에 저장
            if(i != -1){                                    // 만약 visit_list[i] 가 방문하지 않았으면
                visit_list[i] = 0;                          // 해당 Vertex를 방문했다고 지정
                enQueue(Search_Vertex);                     // 방문하지 않았던 해당 Vertex를 Stack에 저장
            }
        }
    }
}

int printGraph(Graph* graph) {              /* printing graph with vertices and edges */
    int i = 0;          // 반복문을 운용하기 위한 변수 i

    if(graph == NULL){  // 그래프가 형성되어 있지 않으면
        printf("You didn't form a graph.\n");   // 오류 메세지 출력
        return 0;       // 함수 종료
    }

    Vertex* temp = NULL;    // Vertex와 Edge를 가리킬 포인터 변수 temp

    printf("Vertex\tEdge\t\n");         // Vertex와 Edge 출력

    for(i = 0; i < delete_count + vertex_count; i++){       // 반복문 실행
        if((graph->vlist+i)->head != NULL){                 // Vertex가 존재하면
            
            printf("[ %d ] :\t", (graph->vlist+i)->head->num);  // Vertex부터 출력
        
            temp = (graph->vlist+i)->head->link;            // temp가 Vertex의 Edge를 가리키도록 지정

            while(temp != NULL){                            // 해당 Vertex의 모든 Edge 출력
                printf("[ %d ]\t", temp->num);
                temp = temp->link;
            }
            printf("\n");
        }
    }
    printf("\n\n delete_count : %d\t vertex_count : %d\t\n", delete_count, vertex_count);        // 마지막으로 delete_count, vertex_count 출력
    return 1;
}  

int Check_vlist(Graph* graph, int vertex){      // vlist에 해당하는 Vertex가 존재하는지 확인하기 위한 함수
    int i = 0;      // 반복문을 돌리기 위한 변수 i

    for(i = 0; i < delete_count + vertex_count; i++){   // 반복문 실행
        if((graph->vlist+i)->head != NULL)              // Vertex가 존재하면
            if((graph->vlist+i)->head->num == vertex)   // Vertex의 값이 입력된 vertex값과 같은지 비교
                break;                                  // 같으면 함수를 종료한다.
    }

    if(i == delete_count + vertex_count){       // 만약 존재하는 Vertex의 끝까지 돌려도 못찾았다면
        return 0;                               // 해당 vertex가 존재하지 않다는 문구 출력 후 종료
    }else return 1;                             // 해당 vertex가 존재할 경우 1을 반환 후 종료

}

Vertex* pop(){  // Stack에 있는 원소를 pop하기 위한 함수
    return DFS_stack[top--];    // Stack에 있는 원소를 pop하고 top--;
}

void push(Vertex* push_Vertex){ // Stack에 원소를 push하기 위한 함수
    DFS_stack[++top] = push_Vertex; // Stack의 ++top 위치에 해당 vertex push
}

int Check_visit_list(Graph* graph, Vertex* Search_Node, int* visit_list){   // 해당 Vertex가 방문했는지 기록하기 위한 함수
    int i = 0;      // 반복문을 돌리기 위한 변수 i

    for(i = 0; i < delete_count + vertex_count; i++){       // 반복문 실행
        if((graph->vlist+i)->head != NULL){                 // vlist에 Vertex가 존재하면
            if((graph->vlist+i)->head->num == Search_Node->num){    // 해당 Vertex가 찾고자하는 Edge의 숫자와 같은지 비교
                if(visit_list[i] == 1){         // 해당하는 Vertex가 방문하지 않았으면
                    return i;                   // Vertex의 위치를 반환
                }
                else return -1;                 // 방문하였으면 -1을 반환
            }
        }
    }
    printf("Error\n");                          // 오류가 났으면 메세지를 보내고
    return -1;                                  // -1을 반환
}

Vertex* Move_next(Graph* graph, Vertex* Search_Vertex) {            // Edge의 num과 같은 값을 가진 Vertex로 이동하기 위한 함수
    int i = 0;                  // 반복문을 돌리기 위한 변수 i
    for (i = 0; i < delete_count + vertex_count; i++) {     // 반복문 시작
        if ((graph->vlist + i)->head != NULL) {             // Vertex가 존재하면
            if (Search_Vertex->num == (graph->vlist + i)->head->num)    // 해당 Vertex와 Edge가 가진 num이 같은지 비교
                return (graph->vlist + i)->head;            // 같으면 해당 Vertex의 위치를 반환
        }
    }
    printf("Error\n");      // 오류일 경우 메세지 출력
    return NULL;            // NULL 반환
}

Vertex* deQueue(){
    if(front == rear){								// 큐가 비워져있으면
        printf("Circular Queue Is Empty!");;		// 비워져있을 경우 경고 출력
        return NULL;
    }
	else {											// 원소가 들어있을 경우
    	front = (front + 1) % MAX_VERTEX;		    // front값을 증가시키고 (POP)
		return BFS_Queue[front];					// Pop하여 원소를 빼냄
	}
}

void enQueue(Vertex* Search_Vertex){
    rear = (rear + 1) % MAX_VERTEX;				    // 원소를 넣으면 rear의 값이 증가해야 하므로

	if(rear == front){								// Queue의 rear과 front가 같으면
		if(rear == 0 || front == 0){ 				// rear이 0이거나 front가 0이면
			rear = MAX_VERTEX - 1;				    // rear에 MAX_QUEUE_SIZE -1을 저장한다.
		}
		else 										// 둘중 하나가가 0이 아니면
			rear = (rear - 1) % MAX_VERTEX;	    	// rear에 (rear -1) % MAX_QUEUE_SIZE를 저장한다
			printf("Circular Queue Is Full!");		// 꽉 채워져 있으므로 경고 출력
	}else
		BFS_Queue[rear] = Search_Vertex;   			// 꽉 채워져있지 않을경우 Queue에 원소를 Push
}
