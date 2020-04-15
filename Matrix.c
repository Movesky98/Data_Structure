#include <stdio.h>
#include <stdlib.h>		
#include <time.h>

// row와 col이 제대로 입력되었는지 확인하는 함수
int check_row_and_col(int row, int col);
// malloc()을 이용해 row x col크기의 2차원 배열을 만들어 반환하는 함수
int** create_matrix(int row, int col);
// create_matrix()에서 할당받은 메모리를 해제하는 함수 (연산 종료 후)
int free_matrix(int** matrix, int row, int col);
// row x col 매트릭스를 출력하는 함수
void print_matrix(int** matrix, int row, int col);


// 랜덤된 값들을 매트릭스에 할당해주는 함수
int fill_data(int** matrix, int row, int col);
// A의 전치행렬 T를 구현하는 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
// 행렬 합계 = matrix_a + matrix_b
int addition_matrix(int** matrix_a, int** matrix_b, int** matrix_sum, int row, int col);
// 연산 결과 = matrix_a - matrix_b
int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub, int row, int col);
// 연산 결과 = matrix_a x matrix_t
int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col);


int main() {
	srand((unsigned int)time(NULL));					// 무작위의 수를 생성하기 위해 rand함수에 시드()를 넣어줌
	int row = 0, col = 0;								// 행렬의 행과 열을 나타내기 위한 변수
	int** Matrix_A = NULL;								// 행렬 A를 나타내기 위한 이중 포인터 변수 Matrix_A 선언 및 초기화
	int** Matrix_B = NULL;								// 행렬 B를 나타내기 위한 이중 포인터 변수 Matrix_B 선언 및 초기화
	int** Matrix_T = NULL;								// 행렬 A의 전치행렬 T를 나타내기 위한 이중 포인터 변수 Matrix_T 선언 및 초기화

	int** Matrix_Sum = NULL;							// 행렬 A + B를 나타내기 위한 이중 포인터 변수 Matrix_Sum 선언 및 초기화
	int** Matrix_Sub = NULL;							// 행렬 A - B를 나타내기 위한 이중 포인터 변수 Matrix_Sub 선언 및 초기화
	int** Matrix_Axt = NULL;							// 행렬 A x T를 나타내기 위한 이중 포인터 변수 Matrix_Axt 선언 및 초기화

	printf("[----- [Dong Cheon Kwon] [2017038072] -----]\n\n");

	do {
		printf("Please enter a value for row : ");		// 행렬의 행, row 입력
		scanf("%d", &row);
		printf("Please enter a value for col : ");		// 행렬의 열, col 입력
		scanf("%d", &col);
	} while (check_row_and_col(row, col) == -1);		// row와 col의 값이 제대로 되어있으면 check_row_and_col()는 1을 반환한다
														// 반대로 제대로 할당되어지지 않으면 -1을 반환한다.

	Matrix_A = create_matrix(row, col);					// 이중 포인터 변수 Matrix_A,
	Matrix_B = create_matrix(row, col);					// Matrix_B,
	Matrix_Sum = create_matrix(row, col);				// Matrix_Sum(== A + B)
	Matrix_Sub = create_matrix(row, col);				// Matrix_Sub(== A - B)
	Matrix_Axt = create_matrix(row, row);				// Matrix_Axt(== A x T)
	Matrix_T = create_matrix(col, row);					// Matrix_T (행렬 A의 전치행렬 T)
														// 위와 같은 이중 포인터 변수에 행렬을 나타내기 위한 create_matrix() 함수 호출

	fill_data(Matrix_A, row, col);						// Matrix_A에 수를 할당해줄 fill_data() 함수 호출
	printf("Matrix A\n");								// print_matrix() 함수를 호출하여 행렬 A 출력
	print_matrix(Matrix_A, row, col);					

	fill_data(Matrix_B, row, col);						// Matrix_B에 수를 할당해줄 fill_data() 함수 호출
	printf("Matrix B\n");								// print_matrix() 함수를 호출하여 행렬 B 출력
	print_matrix(Matrix_B, row, col);


	addition_matrix(Matrix_A, Matrix_B, Matrix_Sum, row, col);		// 행렬 A와 B의 합 A + B를 계산하는 addition_matrix() 함수 호출
	transpose_matrix(Matrix_A, Matrix_T, row, col);					// 행렬 A의 전치행렬 T를 만들어내는 transpose_matrix() 함수 호출
	subtraction_matrix(Matrix_A, Matrix_B, Matrix_Sub, row, col);	// 행렬 A와 B의 차, A - B를 계산하는 subtraction_matrix() 함수 호출
	multiply_matrix(Matrix_A, Matrix_T, Matrix_Axt, row, col);		// 행렬 A, A의 전치행렬 T의 곱 A x T 를 계산하는 multiply_matrix() 함수 호출


	printf("Matrix A + B\n");							// print_matrix() 함수를 호출하여 A + B 출력
	print_matrix(Matrix_Sum, row, col);

	
	printf("Matrix A - B\n");							// print_matrix() 함수를 호출하여 A - B 출력
	print_matrix(Matrix_Sub, row, col);

	
	printf("Matrix A's Tranpose_Matrix T\n");			// print_matrix() 함수를 호출하여 행렬 A의 전치행렬 T를 출력
	print_matrix(Matrix_T, col, row);

	
	printf("Matrix A x T\n");							// print_matrix() 함수를 호출하여 행렬 A와 전치행렬 T의 곱, A x T 출력
	print_matrix(Matrix_Axt, row, row);


	free_matrix(Matrix_A, row, col);					// 이중 포인터 변수 Matrix_A,
	free_matrix(Matrix_B, row, col);					// Matrix_B,
	free_matrix(Matrix_Sum, row, col);					// Matrix_Sum,
	free_matrix(Matrix_Sub, row, col);					// Matrix_Sub,
	free_matrix(Matrix_Axt, row, row);					// Matrix_Axt,
	free_matrix(Matrix_T, col, row);					// Matrix_T 에 할당되었던 메모리를 해제하기 위한 free_matrix() 함수 호출
	
	return 0;		// 프로그램 종료.
}

int check_row_and_col(int row, int col) {				// row와 col이 제대로 입력되었는지 확인하는 함수
	if (row <= 0 || col <= 0) {													// row, col이 0보다 작으면
		printf("Please check the value of row and col again.\n");				// 오류 메세지 출력
		return -1;																// 비정상 종료 -1 반환
	} else if(row > 0 && col > 0){												// row, col이 0보다 크면
		return 1;																// 정상 종료 1 반환
	}
	else printf("Please check the value of row and col again.\n");				// 혹은 row, col이 숫자가 아닌 다른 데이터가 할당 될 경우
		return -1;																// 비정상 종료 -1 반환
}
int** create_matrix(int row, int col) {											// malloc()을 이용해 row x col크기의 2차원 배열을 만들어 반환하는 함수 정의

	int** Reserve_Matrix = NULL;												// malloc()을 이용해 메모리를 할당 받을 이중 포인터 변수 선언
	int i = 0;

	/* 전처리 검사 */
	if (row <= 0 || col <= 0) {													// row, col 값이 제대로 들어오지 않았으면
		printf("Please check the value of row and col again.\n");				// 오류 메세지 출력
		return -1;																// 이후 비정상 종료 -1 반환
	}


	Reserve_Matrix = (int**)malloc(sizeof(int*) * row);							// row, col 값이 제대로 들어와 메모리를 동적으로 할당받음
	for (i = 0; i < row; i++) {
		Reserve_Matrix[i] = (int*)malloc(sizeof(int) * col);					// 행렬, 2차원 배열이므로 다음과 같이 할당을 받는다.
	}

	/*후처리 검사*/
	if (Reserve_Matrix == NULL) {												// 만약 Reserve_Matrix가 제대로 메모리를 할당받지 않았으면
		printf("proper actions for unexpected conditions");						// 오류 메세지 출력
		return -1;																// 비정상 종료 -1 반환
	}

	return Reserve_Matrix;														// 오류가 없으면 다음과 같이 정상 종료, Reserve_Matrix 반환

}
int free_matrix(int** matrix, int row, int col) {								// 받았던 메모리를 연산이 종료된 후 해제시켜줄 함수 정의
	int i = 0;

	if (matrix == NULL) {														// 이미 메모리가 해제되어 있거나 할당받지 않았을 경우
		printf("You have already released the memory allocated.\n");			// 메모리가 해제되어있다는 메세지와 함께
		return -1; 																// 비정상 종료 -1 반환
	}

	for (i = 0; i < row; i++) {													// matrix는 2차원 배열과 비슷하게 메모리를 동적할당 받았으므로
		free(matrix[i]);														// 배열의 열에 할당 받은 메모리를 해제 후
	}
	free(matrix);																// matrix의 전체 할당받은 메모리를 해제
	matrix = NULL;
	
	if(matrix != NULL){															// 메모리 해제가 제대로 안이루어졌을 경우
		printf("Matrix is not properly initialized.\n");						// 오류 메세지 출력
		return -1;																// 비정상종료 -1 반환
	}

	return 1;																	// 제대로 되었을 경우 정상 종료 1 반환
}
void print_matrix(int** matrix, int row, int col) {								// 행렬 matrix를 나타내기 위한 print_matrix() 함수 정의
	int i = 0, j = 0;
	
	if(matrix == NULL){															// matrix가 제대로 메모리를 할당받지 않으면
		printf("Matrix is not created\n");										// 오류메세지 출력
	}

	for (i = 0; i < row; i++) {													// matrix에 할당되어있는 데이터 값을 출력
		for (j = 0; j < col; j++) {
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}
int fill_data(int** matrix, int row, int col) {									// 메모리를 할당받은 2차원 배열에 데이터를 할당해줄 fill_data() 함수 정의
	int i = 0, j = 0;

	if(matrix == NULL){															// matrix가 메모리를 할당받지 않았을 경우
		printf("Matrix is not created\n");
		return -1;																// 오류 메세지 출력과 비정상 종료 -1 반환
	}

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {										
			matrix[i][j] = rand() % 20;											// 메모리를 동적할당 받았으면 데이터를 할당해줌
			if(matrix[i][j] < 0 || matrix[i][j] >= 20){							// 제대로 데이터가 할당되어지지 않으면
				printf("Invalid number assigned while program was running.\n");	// 오류메세지 출력
				return -1;														// 비정상 종료 -1 반환
			}
		}
	}

	return 1;																	// 모든것이 제대로 이루어지면 정상 종료 1 반환
}
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) {			// 행렬 A의 전치행렬 T를 계산하기위한 transpose_matrix() 함수 정의
	int i = 0, j = 0;

	if(matrix == NULL || matrix_t == NULL){										// 들어온 두 이중 포인터 변수중 하나라도 메모리를 할당받지 않았을 경우
		printf("Matrix is not created\n");										// 오류 메세지 출력
		return -1;																// 비정상 종료 -1 반환
	}

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			matrix_t[j][i] = matrix[i][j];										// 전치행렬 T를 계산하기 위한 데이터 할당
			if(matrix_t[j][i] != matrix[i][j]){									// 이때, 데이터가 제대로 할당되어지지 않았으면
				printf("Invalid number assigned while program was running.\n");	// 오류메세지 출력
				return -1;														// 비정상 종료 -1 반환
			}
		}
	}

	return 1;																	// 모든것이 제대로 이루어졌을 경우 정상 종료 1 반환
}
int addition_matrix(int** matrix_a, int** matrix_b, int** matrix_sum, int row, int col)		// 행렬 A + B 를 계산하기위한 addtion_matrix() 함수 정의
{
	int i = 0, j = 0;

	if(matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL){				// 매개변수로 받은 3개의 이중 포인터 변수중 메모리를 할당받지 않았을 경우
		printf("Matrix is not created\n");										// 오류 메세지 출력
		return -1;																// 비정상 종료 -1 반환
	}

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];					// 행렬 A + B를 계산하기 위한 데이터 할당
			if(matrix_sum[i][j] != matrix_a[i][j] + matrix_b[i][j]){			// 이것이 제대로 이루어지지 않았을 경우
				printf("Invalid number assigned while program was running.\n");	// 오류메세지 출력
				return -1;														// 비정상 종료 -1 반환
			}
		}
	}
	return 1;																	// 정상 종료 1 반환
}
int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub, int row, int col) {	// 행렬 A - B를 계산하기 위한 subtraction_matrix() 함수 정의
	int i = 0, j = 0;

	if(matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL){				// 매개변수로 받은 3개의 이중 포인터 변수 중 메모리를 할당받지 않았을 경우
		printf("Matrix is not created\n");										// 오류 메세지 출력
		return -1;																// 비정상 종료 -1 반환
	}

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];					// A - B를 계산하기 위한 데이터 할당
			if(matrix_sub[i][j] != matrix_a[i][j] - matrix_b[i][j]){			// 제대로 이루어지지 않았을 경우
				printf("Invalid number assigned while program was running.\n");	// 오류 메세지 출력
				return -1;														// 비정상 종료 -1 반환
			}
		}
	}
	return 1;																	// 정상종료 1 반환
}
int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col) {		// 행렬 A x T를 계산하기 위한 multiply_matrix() 함수 정의
	int i = 0, j = 0, k = 0;
	int sum = 0;

	if(matrix_a == NULL || matrix_t == NULL || matrix_axt == NULL){				// 매개변수로 받은 3개의 이중 포인터 변수 중 메모리를 할당받지 않았을 경우
		printf("Matrix is not created\n");										// 오류 메세지 출력
		return -1;																// 비정상 종료 -1 반환
	}

	for (i = 0; i < row; i++) {
		for (j = 0; j < row; j++) {												// 연산을 하기 전 A x T의 계산을 받을 변수 초기화
			matrix_axt[i][j] = 0;
		}
	}


	for (i = 0; i < row; i++) {
		for (j = 0; j < row; j++) {
			for (k = 0; k < col; k++) {											// A x T를 계산하기 위한 데이터 할당
				matrix_axt[i][j] += matrix_a[i][k] * matrix_t[k][j];	
				sum += matrix_a[i][k] * matrix_t[k][j];							// A x T가 제대로 할당되어있는지 알기 위해 따로 만들어 놓은 변수 sum
			}
			if(matrix_axt[i][j] != sum){										// 할당 받은 데이터 값이 sum과 다른 경우
				printf("Invalid number assigned while program was running.\n");	// 오류 메세지 출력
				return -1;														// 비정상 종료 -1 반환 
			}
			sum = 0;															// 다시 계산하기위한 sum 초기화
		}
	}
	return 0;																	// 정상 종료 1 반환
}
