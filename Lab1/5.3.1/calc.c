#include <stdlib.h>
#include "calc.h"
int main(void){
	char op;
	char s[20], a[10], b[10];
	float ans;
	FILE* ptr = fopen("answer.txt", "r");
	fscanf(ptr, "%f", &ans);
	fclose(ptr);
	system("clear");
	printf(">> ");
	scanf("%[^\n]%*c", s);
	sscanf(s, "%s %c %s", a, &op, b);
	while(strcmp(a, "EXIT") != 0){
		arithmetic(&ans, a, b, op);
		ptr = fopen("answer.txt", "w");
		fprintf(ptr, "%f", ans);
		fclose(ptr);
		getchar();
		system("clear");
		printf(">> ");
		scanf(" %[^\n]%*c", s);
		sscanf(s, "%s %c %s", a, &op, b);
	}
	return 0;
}
