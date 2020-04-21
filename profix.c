/*
 * postfix.c
 *
 *  2020 Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10                       // 스택의 최대 크기
#define MAX_EXPRESSION_SIZE 20                  // 각 expression의 최대 크기

 /* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum {
    lparen = 0,  /* ( 왼쪽 괄호 */
    rparen = 9,  /* ) 오른쪽 괄호*/
    times = 7,   /* * 곱셈 */
    divide = 6,  /* / 나눗셈 */
    plus = 5,    /* + 덧셈 */
    minus = 4,   /* - 뺄셈 */
    operand = 1 /* 피연산자 */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixPush(char x)                        // postfix를 postfixStack에 Push하기 위한 함수
{
    postfixStack[++postfixStackTop] = x;        // 들어온 문자 x를 Top를 한단계 높여주고 postfixStack에 저장
}

char postfixPop()                               // postfixStack에 있는 문자를 Pop하기 위한 함수
{
    char x;                                     // postfixStack안에 들어있는 문자를 Pop할 변수 x 선언
    if (postfixStackTop == -1)                   // postfixStack안에 아무것도 없으면
        return '\0';                            // '\0'을 Pop
    else {                                      // postfixStack안에 문자가 있으면
        x = postfixStack[postfixStackTop--];    // Top위치에 있는 문자를 꺼내어 x에 저장
    }                                           // 이후 Top을 한단계 내림
    return x;                                   // postfixStack 안에 있던 문자를 Pop
}


void evalPush(int x)                            // 계산된 수를 evalStack에 Push하기 위한 함수
{
    evalStack[++evalStackTop] = x;              // 들어온 수 x를 Top을 한단계 높여주고 evalStack의 Top부분에 저장
}

int evalPop()                                   // 계산이 완료된 값을 Pop하여 받기 위한 함수
{
    if (evalStackTop == -1)                      // 만약 스택에 아무런 숫자도 들어있지 않으면
        return -1;                              // -1값을 출력
    else                                        // 스택에 수가 들어있으면
        return evalStack[evalStackTop--];       // 그 수를 Pop
}


/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()                                 // 중위표기법으로 표기된 연산을 받기위한 함수
{
    printf("Type the expression >>> ");         // 연산을 입력받고
    scanf("%s", infixExp);                       // 입력받은 연산을 infixExp에 저장
}

precedence getToken(char symbol)                // 들어온 문자를 토큰으로 변환해주는 함수
{
    switch (symbol) {
    case '(': return lparen;
    case ')': return rparen;
    case '+': return plus;
    case '-': return minus;
    case '/': return divide;
    case '*': return times;
    default: return operand;
    }

}

precedence getPriority(char x)                  // getToken()함수를 호출하기 위한 함수
{
    return getToken(x);
}

/**
 * 문자 하나를 전달 받아, postfixExp에 추가
 */
void charCat(char* c)
{
    if (postfixExp == '\0')                     // postfixExp에 '\0'이 들어가있으면 (아무것도 없으면)
        strncpy(postfixExp, c, 1);              // c를 복사하여 postfixEXP에 저장한다
    else                                        // 다른 문자가 들어와있으면
        strncat(postfixExp, c, 1);              // c를 postfixExp에 이어붙인다.
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이욯하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()                                // infix를 postfix로 변환하기 위한 함수
{
    /* infixExp의 문자 하나씩을 읽기위한 포인터 */
    char* exp = infixExp;
    char x; /* 문자 하나를 임시로 저장하기 위한 변수 */

    /* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
    while (*exp != '\0')                        // 만약 exp에 저장되어 있는 문자가 '\0'이면 반복문을 빠져나온다.
    {
        x = getToken(*exp);                     // x에 exp가 받은 문자를 저장
        if (x == operand) {                     // x가 operand이면
            charCat(exp++);                     // postfixExp에 바로 저장하고 다음 연산을 위해 exp 증가
        }
        else if (x != operand) {                // x가 operand가 아니면
            if (x == lparen) {                                  // x가 '('일 때,
                postfixPush(*exp++);                            // postfixStack에 (을 저장
                x = getToken(*exp);                             // x에 exp가 받은 문자를 저장
                while (x != rparen) {                           // x가 ) 일때 반복문을 벗어나 Stack안에 저장된 연산자들을 (가 나올때 까지 postfixExp에 저장

                    if (x == operand) {                         // x가 operand이면
                        charCat(exp++);                         // postfixExp에 저장, 다음연산을 위해 exp 증가

                    }
                    else if (x == lparen) {                     // 만약 x가 또 (이면
                        postfixPush(*exp++);                    // postfixStack에 저장, 다음 연산을 위해 exp 증가

                    }
                    else {                                      // x가 ( 이 아니면
                        if (postfixStackTop < 0) {              // postfixStack에 아무것도 없을 경우
                            postfixPush(*exp++);                // exp에 저장되어 있는 문자를 postfixStack에 저장

                        }
                        else {                                  // postfixStack에 문자가 들어있을 경우
                            if (x >= 6) {                       // x가 *, /, ) 일때,
                                if (!(postfixStack[postfixStackTop] == ')')) {          // postfixStack의 Top에 )이 저장되어 있지 않으면
                                if (!( x == '(')){
                                        if (getToken(postfixStack[postfixStackTop]) >= x || (getToken(postfixStack[postfixStackTop]) == x + 1)) { // top이 *, /보다 크거나 같으면
                                            charCat(&postfixStack[postfixStackTop]);        // top에 저장되어있는 문자를 postfixExp에 붙이고
                                            postfixPop();                                   // Pop하여 스택에 있는 문자를 삭제
                                            postfixPush(*exp++);                            // postfixStack에 x를 Push
                                        }
                                        else postfixPush(*exp++);                           // top이 +, -이면 그냥 Stack에 저장
                                    }
                                }
                            }
                            else if (x < 6) {                     // x가 +, -일때
                                if (!(postfixStack[postfixStackTop] == ')')) {          // postfix의 StackTop이 ) 이 아닐 경우,
                                    if (!( x == '(')){
                                        if (getToken(postfixStack[postfixStackTop]) >= 6) { // postfix의 StackTop이 *, / 이면
                                            charCat(&postfixStack[postfixStackTop]);        // postfix의 StackTop을 postfixExp에 붙이고
                                            postfixPop();                                   // Pop!
                                            postfixPush(*exp++);                            // 이후 x를 Push!
                                        }                                
                                        else {                                              // postfix의 StackTop이 +, -, ( 이면
                                            if (!(postfixStack[postfixStackTop] == '(')) {    // postfix의 StackTop이 ( 가 아닐 경우에
                                                charCat(&postfixStack[postfixStackTop]);    // postfix의 StackTop을 postfixExp에 붙이고
                                                postfixPop();                               // Pop!
                                                postfixPush(*exp++);                        // x를 Push
                                            }
                                            else {                                          // postfix의 StackTop이 ( 일 경우 다음 계산을 위해 exp++;
                                                postfixPush(*exp++);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    x = getToken(*exp);                         // 연산이 끝난 후 반복문이 실행되기 직전, getToken()함수 호출 
                }                                               // x가 )을 벗어나면 Stack안에 저장된 연산자들을 postfixExp에 저장
                postfixPush(*exp++);                            // )이 나오면 postfixStack에 저장
                x = getToken(*exp);
                if (x >= 6) {                                   // 만약 )을 빠져나왔는데 )뒤에 오는 연산자가 *, / 이면
                    for (int i = postfixStackTop; i > -1; i--) {        // ) 뒤에 나온 *, / 를 먼저 Pop을 시키면 오류가 생기므로
                        if (postfixStack[i] == ')') {                   // 스택안에 원소가 ) 일 경우 Pop
                            postfixPop();
                        }
                        else if (postfixStack[i] == '(')                // 스택안에 원소가 ( 일경우
                        {
                            postfixPop();                               // Pop을 하고
                            postfixPush(*exp++);                        // ) 뒤에 오는 연산자가 *, / 였으므로 연산자를 Push
                            if(*exp != '('){                            // ) 뒤에 오는 연산자 뒤에 ( 가 오지 않을 경우
                                charCat(exp++);                         // 연산자 뒤에는 반드시 operand가 오기 때문에 바로 postfixExp에 저장
                                i++;                                    // 또 연산자가 추가적으로 되었기 때문에 postfixStackTop에 맞추기 위해 i++;
                            }                                           // ( 가 올 경우 i값을 변경하지 않고 그대로 진행
                        }                                               // i = StackTop -1 인채로 진행된다.
                        else
                        {                                               // (, )이 아닌 연산자일 경우 postfixExp에 저장하고
                            charCat(&postfixStack[i]);                  // Pop!
                            postfixPop();
                        }
                    }
                }
                else {                                                  // )을 빠져나왔는데 뒤에오는 연산자가 +, -이면
                    for (int i = postfixStackTop; i > -1; i--) {        // ( )을 빠져나와도 연산에 오류가 없기 때문에
                        if (postfixStack[i] == ')' || postfixStack[i] == '(') {       // 스택에 (, ) 이 저장되어있으면
                            postfixPop();                               // Stack에서 제외
                        }
                        else {                                          // (, )이 아니면
                            charCat(&postfixStack[i]);                  // postfixExp에 저장하고
                            postfixPop();                               // Pop
                        }
                    }
                }
            }
            else if (x != lparen) {                                     // x가 ( 이 아닐때,
                if (postfixStackTop < 0) {                              // postfixStack에 아무 문자도 없으면
                    postfixPush(*exp++);                                // 처음 들어오는 연산자를 Push
                }
                else {
                    if (x >= 6) {             // x가 *, / 일때
                        if (!(postfixStack[postfixStackTop] == ')')) {              // postfixStack의 Top에 저장되어 있는 문자가 ) 가 아닐때
                            if (x != rparen) {                                      // )이 두번 연속 입력되어 오는 경우가 아니면 (x도, Stack의 Top도 ')'가 아니면 )
                                if (getToken(postfixStack[postfixStackTop]) >= x || (getToken(postfixStack[postfixStackTop]) == x + 1)) { // Top이 *, /보다 크거나 같으면 (x가 *, / 이므로)
                                    charCat(&postfixStack[postfixStackTop]);        // Top을 postfixExp에 붙이고
                                    postfixPop();                                   // 이후 Top에 저장된 문자를 Pop.
                                    postfixPush(*exp++);                            // x를 Push.
                                }
                                else postfixPush(*exp++);                           // Top이 +, -이면 x를 Stack에 저장
                            }
                            else exp++;                                             // (a+b+c) 일 경우 마지막 )이 왔을 때 계산하지 않고 exp++
                        }
                    }
                    else if (x < 6) { // x가 +, -일때                                // Top 이전에 저장되어 있는 값이 있을 수 있으므로
                        if (!(postfixStack[postfixStackTop] == ')')) {              // Top이 ) 이 아닐 경우,
                            if (getToken(postfixStack[postfixStackTop]) >= 6) {     // postfix의 StackTop이 *, / 이면
                                charCat(&postfixStack[postfixStackTop]);            // postfix의 StackTop을 postfixExp에 붙이고
                                postfixPop();                                       // Stack의 Top에 저장된 문자를 Pop.
                            }
                            else {                                                  // 이후 x값은 아래를 진행한 후 저장
                                if (!(postfixStack[postfixStackTop] == '(')) {
                                    if (getToken(postfixStack[postfixStackTop]) < 6) {  // postfix의 StackTop이 +, -이면
                                        charCat(&postfixStack[postfixStackTop]);        // postfix의 StackTop을 postfixExp에 붙이고 (x와 postfixStackTop의 우선순위가 같으므로)
                                        postfixPop();                                   // postfix의 StackTop를 Pop
                                        postfixPush(*exp++);                            // x를 Push.
                                    }
                                    else postfixPush(*exp++);                           // x가 +, -이고 postfix의 Stacktop이 *,/일때, 일을 처리한 후 x를 push
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = postfixStackTop; i > -1; i--) {                  // Operand,(, ) 가 끝나고 postfixStack에 남아있는 연산자들을 계산
        if (postfixStack[i] == '(' || postfixStack[i] == ')') {   // 스택안에 원소가 (, )일 경우 Pop
            postfixPop();
        }
        else {                                                  // (, )이 아닌 연산자일 경우 postfixExp에 저장하고
            charCat(&postfixStack[i]);                          // Pop
            postfixPop();
        }
    }
    charCat(exp);                                               // '\0' postfixExp에 저장
}
void debug()                                                    // infixExp, postfixExp, eval의 결과값, postfix의 스택에 남아있는 것들을 출력하는 함수
{
    printf("\n---DEBUG\n");
    printf("infixExp =  %s\n", infixExp);                       // infixExp 출력
    printf("postExp =  %s\n", postfixExp);                      // postfixExp 출력
    printf("eval result = %d\n", evalResult);                   // eval 결과값 출력

    printf("postfixStack : ");
    for (int i = 0; i < MAX_STACK_SIZE; i++)                    // postfixStack에 남아있는 문자 출력
        printf("%c  ", postfixStack[i]);

    printf("\n");

}

void reset()                                                    // 리셋하는 함수
{                                                               // 연산을 하는데에 필요한 변수들 초기화
    infixExp[0] = '\0';
    postfixExp[0] = '\0';

    for (int i = 0; i < MAX_STACK_SIZE; i++)
        postfixStack[i] = '\0';

    postfixStackTop = -1;
    evalStackTop = -1;
    evalResult = 0;
}

void evaluation()                                               // postfixExp를 바탕으로 연산을 하는 evaluation 함수
{
    /* postfixExp, evalStack을 이용한 계산 */
    char* exp = postfixExp;             // postfiXExp의 문자를 하나씩 읽기 위한 포인터
    char x;                             // 문자 하나를 임시로 저장하기 위한 변수
    int num1 = 0, num2 = 0;             // postfixExp에 있는 문자를 숫자로 바꾸어 evalStack에 넣은 수들을 연산하기 전 꺼내놓기 위한 변수들

                                        // postfixExp에 있는 문자를 읽어 x에 저장
    while (*exp != '\0') {                // exp가 '\0'이 나올 때 까지
        x = getToken(*exp);
        if (x == operand) {
            evalPush(*exp++ - '0');          // x는 문자이므로 아스키코드로 나타내면 '문자' - 48
        }
        else {
            num2 = evalPop();           // num2에 evalStackTop에 있는 수를 Pop하여 num2에 저장
            num1 = evalPop();           // 이후 다음 연산하기 위한 수도 Pop하여 num1에 저장

            switch (x) {
            case plus: evalPush(num1 + num2); break;        // num1 + num2 하여 evalStack에 저장
            case minus: evalPush(num1 - num2); break;       // num1 - num2 하여 evalStack에 저장
            case times: evalPush(num1 * num2); break;       // num1 * num2 하여 evalStack에 저장
            case divide: evalPush(num1 / num2); break;      // num1 / num2 하여 evalStack에 저장
            }
            exp++;                      // 다음 연산을 위해 exp++
        }
    }
    evalResult = evalPop();             // evalResult에 결과값을 저장
}

int main()                              // 메인함수 시작
{
    char command;                       // 명령어 입력을 위한 변수 command 선언

    printf("[----- [Kwon Dong Cheon] [2017038072] -----]\n");

    do {
        printf("----------------------------------------------------------------\n");
        printf("               Infix to Postfix, then Evaluation               \n");
        printf("----------------------------------------------------------------\n");
        printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);         // 명령어 입력

        switch (command) {
        case 'i': case 'I':             // command == i || command == I 이면
            getInfix();                 // getInfix() 실행
            break;                      // switch 탈출
        case 'p': case 'P':             // command == p || command == P 이면
            toPostfix();                // topostfix() 실행
            break;                      // switch 탈출
        case 'e': case 'E':             // command == e || command == E 이면
            evaluation();               // evaluation() 실행
            break;                      // switch 탈출
        case 'd': case 'D':             // command == d || command == D 이면
            debug();                    // debug() 실행
            break;                      // switch 탈출
        case 'r': case 'R':             // command == r || command == R 이면
            reset();                    // reset() 실행
            break;                      // switch 탈출
        case 'q': case 'Q':             // command == q || command == Q 이면
            break;                      // switch 탈출
        default:                        // 그외 다른 명령어를 입력할 경우
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");              // 오류메세지 출력
            break;                      //switch 탈출
        }

    } while (command != 'q' && command != 'Q');     // command == q || command == Q 일 경우, 반복문을 탈출

    return 0;       // 프로그램 종료.
}
