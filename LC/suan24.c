#include <stdio.h>
#include <stdint.h>
#include <string.h>

void bubble_sort(int arr[], int len) 
{
	int i, j, temp;
    for (i = 0; i < len - 1; i++)
    	for (j = 0; j < len - 1 - i; j++)
			if (arr[j] < arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
}

void main()
{
	int input[4];
	int i,j,k,m,n;
	int tmp = 0;
	int status = 0;
	printf("请输入4个数字(1-9)：\n");
    scanf("%d%d%d%d", &input[0], &input[1], &input[2], &input[3]);
    for (i = 0; i < 4; i++) {
		if (input[i] > 9 || input[i] < 0) {
			printf("the %dth input is not in the range [1 - 9]. \n", i + 1);
			status = 1;
		}
	}
	if (status)
		return;
	printf("the calculate dates are: %d,%d,%d,%d\n", input[0], input[1], input[2], input[3]);
	bubble_sort(input, 4);
    //printf("%d,%d,%d,%d\n", input[0], input[1], input[2], input[3]);
	
	int cnt2 = 0;
	int cnt3 = 0;
	int result_3[300][3] = {0};
	char process3[300][20];
	char process2[300][20];
	char process23[2][300][20];
	
	int num_3 = 0;
	int result_2[300][2] = {0};
	char process24[300][40];
	int num_2 = 0;
	int num_tmp = 0;
	char result[2][300][20];
	int solution = 0;
	int solution_rel = 0;
	
	for (i = 0; i < 3; i++) {
		for (j = i + 1; j < 4; j++) {
			num_tmp = 0;		
			for (k = 0; k < 4; k++) {				
				if ((k != i) && (k != j))
					result_3[num_3][num_tmp++] = input[k];
			}
			
			result_3[num_3][2] = input[i] * input[j];
			sprintf(process3[num_3++], "%d * %d = %d", input[i], input[j], input[i] * input[j]);
			
			result_3[num_3][0] = result_3[num_3 - 1][0];
			result_3[num_3][1] = result_3[num_3 - 1][1];
			result_3[num_3][2] = input[i] + input[j];
			sprintf(process3[num_3++], "%d + %d = %d", input[i], input[j], input[i] + input[j]);
			
			if ((input[i] - input[j]) > 0) {
				result_3[num_3][0] = result_3[num_3 - 1][0];
				result_3[num_3][1] = result_3[num_3 - 1][1];
				result_3[num_3][2] = input[i] - input[j];
				sprintf(process3[num_3++], "%d - %d = %d", input[i], input[j], input[i] - input[j]);
			}
			
			if (((input[i] % input[j]) == 0) && (input[j] != 1)) {
				result_3[num_3][0] = result_3[num_3 - 1][0];
				result_3[num_3][1] = result_3[num_3 - 1][1];
				result_3[num_3][2] = input[i] / input[j];
				sprintf(process3[num_3++], "%d / %d = %d", input[i], input[j], input[i] / input[j]);
			}
		}
	}
	
	for (m = 0; m < num_3; m++) {
		//printf("%s\n", process3[m]);
		//printf("%d,%d,%d\n", result_3[m][0], result_3[m][1], result_3[m][2]);
		bubble_sort(result_3[m], 3);
		//printf("%d,%d,%d\n", result_3[m][0], result_3[m][1], result_3[m][2]);		
		
		for (i = 0; i < 2; i++) {
			for (j = i + 1; j < 3; j++) {
				for (k = 0; k < 3; k++) {				
					if ((k != i) && (k != j))
						result_2[num_2][0] = result_3[m][k];
				}
				result_2[num_2][1] = result_3[m][i] * result_3[m][j];
				sprintf(process2[num_2], "%d * %d = %d", result_3[m][i], result_3[m][j], result_3[m][i] * result_3[m][j]);
				strcpy(process23[1][num_2], process2[num_2]);
				strcpy(process23[0][num_2], process3[m]);
				num_2++;
				
				result_2[num_2][0] = result_2[num_2 - 1][0];
				result_2[num_2][1] = result_3[m][i] + result_3[m][j];
				sprintf(process2[num_2], "%d + %d = %d", result_3[m][i], result_3[m][j], result_3[m][i] + result_3[m][j]);
				strcpy(process23[1][num_2], process2[num_2]);
				strcpy(process23[0][num_2], process3[m]);
				num_2++;
				
				if ((result_3[m][i] - result_3[m][j]) > 0) {
					result_2[num_2][0] = result_2[num_2 - 1][0];
					result_2[num_2][1] = result_3[m][i] - result_3[m][j];
					sprintf(process2[num_2], "%d - %d = %d", result_3[m][i], result_3[m][j], result_3[m][i] - result_3[m][j]);
					strcpy(process23[1][num_2], process2[num_2]);
					strcpy(process23[0][num_2], process3[m]);
					num_2++;
				}
				
				if (((result_3[m][i] % result_3[m][j]) == 0) && result_3[m][j] != 1) {
					result_2[num_2][0] = result_2[num_2 - 1][0];
					result_2[num_2][1] = result_3[m][i] / result_3[m][j];
					sprintf(process2[num_2], "%d / %d = %d", result_3[m][i], result_3[m][j], result_3[m][i] / result_3[m][j]);
					strcpy(process23[1][num_2], process2[num_2]);
					strcpy(process23[0][num_2], process3[m]);
					num_2++;
				}
			}
		}
		
		for (n = tmp; n < num_2; n++) {
			//printf("%d,%d\n", result_2[n][0], result_2[n][1]);
			bubble_sort(result_2[n], 2);
			//printf("%d,%d\n", result_2[n][0], result_2[n][1]);
			
			if ((result_2[n][0] * result_2[n][1]) == 24) {
				sprintf(process24[solution], "%d * %d = %d", result_2[n][0], result_2[n][1], result_2[n][0] * result_2[n][1]);
				strcpy(result[0][solution], process23[0][n]);
				strcpy(result[1][solution], process23[1][n]);
				printf("%s, %s, %s\n", result[0][solution], result[1][solution], process24[solution]);
				solution++;
			}
			if ((result_2[n][0] + result_2[n][1]) == 24) {
				sprintf(process24[solution], "%d + %d = %d", result_2[n][0], result_2[n][1], result_2[n][0] + result_2[n][1]);
				strcpy(result[0][solution], process23[0][n]);
				strcpy(result[1][solution], process23[1][n]);
				printf("%s, %s, %s\n", result[0][solution], result[1][solution], process24[solution]);
				solution++;
			}
			if ((result_2[n][0] - result_2[n][1]) == 24) {
				sprintf(process24[solution], "%d - %d = %d", result_2[n][0], result_2[n][1], result_2[n][0] - result_2[n][1]);
				strcpy(result[0][solution], process23[0][n]);
				strcpy(result[1][solution], process23[1][n]);
				printf("%s, %s, %s\n", result[0][solution], result[1][solution], process24[solution]);
				solution++;
			}
			if (((result_2[n][0] / result_2[n][1]) == 24) && (result_2[n][1] != 1)) {
				sprintf(process24[solution], "%d / %d = %d", result_2[n][0], result_2[n][1], result_2[n][0] / result_2[n][1]);
				strcpy(result[0][solution], process23[0][n]);
				strcpy(result[1][solution], process23[1][n]);
				printf("%s, %s, %s\n", result[0][solution], result[1][solution], process24[solution]);
				solution++;
			}			
		}
		tmp = num_2;
	}
	printf("solution = %d \n\n",solution);
	for (i = 0; i < solution; i++) {
		for (j = i + 1; j < solution; j++) {
			if ((strcmp(result[0][i], result[1][j]) == 0) && (strcmp(result[1][i], result[0][j]) == 0)) {
				status = 1;
				break;
			}
		}
		if (status) {
			status = 0;
			continue;
		} else {
			printf("%s, %s, %s\n", result[0][i], result[1][i], process24[i]);
			solution_rel++;
		}
	}
	printf("solution_rel = %d \n\n",solution_rel);
	
	
	for (i = 0; i < 3; i++)
		for (j = i + 1; j < 4; j++)
			cnt3 += 4;
	for (m = 0; m < cnt3; m++)
		for (i = 0; i < 2; i++)
			for (j = i + 1; j < 3; j++)
				cnt2 += 4;
	printf("num_2=%d,num_3=%d\n", num_2, num_3);
	printf("cnt2=%d,cnt3=%d\n", cnt2, cnt3);
}
