#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

int isNumber(char * a){
	for(int i = 0; i < strlen(a); i++){
		if(!isdigit(a[i])){
			return 0;
		}
	}
	return 1;
}

void arithmetic(float * ans, char * a, char * b, char op){
	if((isNumber(a) == 1 || strcmp(a, "ANS") == 0) && (isNumber(b) == 1 || strcmp(b, "ANS") == 0)){
		switch (op){
		case '+':
			if(strcmp(a, "ANS") == 0 && strcmp(b, "ANS") != 0){
				*ans += (float)atoi(b);
			}
			else if(strcmp(a, "ANS") != 0 && strcmp(b, "ANS") == 0){
				*ans += (float)atoi(a);
			}
			else if (strcmp(a, "ANS") == 0 && strcmp(b, "ANS") == 0){
				*ans += *ans;
			}
			else *ans = (float)atoi(a) + (float)atoi(b);
			printf("%.0f\n", *ans);
			break;
		case '-':
			if(strcmp(a, "ANS") == 0 && strcmp(b, "ANS") != 0){
				*ans -= (float)atoi(b);
			}
			else if(strcmp(a, "ANS") != 0 && strcmp(b, "ANS") == 0){
				*ans -= (float)atoi(a);
			}
			else if (strcmp(a, "ANS") == 0 && strcmp(b, "ANS") == 0){
				*ans = 0;
			}
			else *ans = (float)atoi(a) - (float)atoi(b);
			printf("%.0f\n", *ans);
			break;
		case 'x':
			if(strcmp(a, "ANS") == 0 && strcmp(b, "ANS") != 0){
				*ans *= (float)atoi(b);
			}
			else if(strcmp(a, "ANS") != 0 && strcmp(b, "ANS") == 0){
				*ans *= (float)atoi(a);
			}
			else if (strcmp(a, "ANS") == 0 && strcmp(b, "ANS") == 0){
				*ans *= *ans;
			}
			else *ans = (float)atoi(a) * (float)atoi(b);
			printf("%.0f\n", *ans);
			break;
		case '/':
			if(strcmp(b, "0") == 0){
				printf("MATH ERROR\n");
			}
			else{
				if(strcmp(a, "ANS") == 0 && strcmp(b, "ANS") != 0){
					*ans /= (float)atoi(b);
				}
				else if(strcmp(a, "ANS") != 0 && strcmp(b, "ANS") == 0){
					*ans = (float)atoi(a) / *ans;
				}
				else if (strcmp(a, "ANS") == 0 && strcmp(b, "ANS") == 0){
					*ans = 1;
				}
				else *ans = (float)atoi(a) / (float)atoi(b);
				printf("%.2f\n", *ans);
			}
			break;
		case '%':
			if(strcmp(b, "0") == 0){
				printf("MATH ERROR\n");
			}
			else{
				if(strcmp(a, "ANS") == 0 && strcmp(b, "ANS") != 0){
					*ans = (div((int)(*ans), atoi(b))).quot;
				}
				else if(strcmp(a, "ANS") != 0 && strcmp(b, "ANS") == 0){
					*ans = (div(atoi(a), (int)(*ans))).quot;
				}
				else if (strcmp(a, "ANS") == 0 && strcmp(b, "ANS") == 0){
					*ans = 1;
				}
				else *ans = (div(atoi(a), atoi(b))).quot;
				printf("%.0f\n", *ans);
			}
			break;
		default:
			printf("SYNTAX ERROR\n");
			break;
		}
	}
	else printf("SYNTAX ERROR\n");
}
