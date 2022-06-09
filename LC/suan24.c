#include <stdio.h>
#include <stdint.h>

void bubble_sort(uint8_t arr[], uint8_t len) 
{
	uint8_t i, j, temp;
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
	uint8_t input[4];
	uint8_t i,j,tmp;
	printf("请输入4个数字(1-9)：\n");
    scanf("%hhd%hhd%hhd%hhd",&input[0],&input[1],&input[2],&input[3]);
    printf("%d,%d,%d,%d\n",input[0],input[1],input[2],input[3]);

	bubble_sort(input,4);

    printf("%d,%d,%d,%d\n",input[0],input[1],input[2],input[3]);
	

	uint8_t result_p[520][3];
	uint8_t resulti_m[520][3];
	uint8_t num = 0;
	for (i=0; i<3; i++) {
		result_p[num++][0] = input[i] * input[i + 1];

	}
}
