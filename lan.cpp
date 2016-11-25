#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define fName "h:/homework/language.txt"
struct mycode{
	char val[15];
	mycode *pnext;
	mycode *prior;
};
struct buffers{
	char str[5];
	char val[8];
	buffers *pnext;
	buffers *prior;
};
void showLinkedListCode(mycode *pHead){
	printf("%s", pHead->val);
	return;
}

void showLinkedListCode_buffer(buffers *pHead){
	printf("%s %s\n", pHead->str,pHead->val);
	return;
}
int isNum(char *buffer){
	int i;
	for(i = 0; i < strlen(buffer); i++){
		if(*(buffer + i) < 48 || *(buffer + i) > 57)
		break;
	}
	return i;
}
buffers *createLinkedList(char *str){
	buffers *pHead = (buffers *)malloc(sizeof(buffers));
	pHead->pnext = NULL;
	pHead->prior = NULL;
	buffers *pnewcode;
	buffers *plast;
	plast = pHead;
	for(int i = 0; i < strlen(str); i++){
		pnewcode = (buffers *)malloc(sizeof(buffers));
		if(isNum((str + i)) != 0){
			int end = isNum((str + i));
			strncpy(pnewcode->val, (str + i), end);
			strcpy(pnewcode->str, "!");
			pnewcode->val[end] = 0;
			plast->pnext = pnewcode;
			pnewcode->prior = plast;
			plast = pnewcode;
			plast->pnext = NULL;
			i += end - 1;
			continue;
		}
		if(strncmp((str + i), "clear", 5) == 0){ 
			strncpy(pnewcode->val, (str + i), 5);
			strcpy(pnewcode->str, "!");
			pnewcode->val[5] = 0;
			plast->pnext = pnewcode;
			pnewcode->prior = plast;
			plast = pnewcode;
			plast->pnext = NULL;
			i += 4;
			continue;
		}
		strncpy(pnewcode->val, (str + i), 1);
		strcpy(pnewcode->str, "!");
		pnewcode->val[1] = 0;
		plast->pnext = pnewcode;
		pnewcode->prior = plast;
		plast = pnewcode;
		plast->pnext = NULL;
	}
	pnewcode = (buffers *)malloc(sizeof(buffers));
	strcpy(pnewcode->val, "#");
	strcpy(pnewcode->str, "!");
	plast->pnext = pnewcode;
	pnewcode->prior = plast;
	plast = pnewcode;
	plast->pnext = NULL;
	return pHead;
}
mycode *createLinkedListFromFile(char *fileName){
	mycode *pHead = (mycode *)malloc(sizeof(mycode));
	pHead->pnext = NULL;
	mycode *pnewcode;
	mycode *plast;
	plast = pHead;
	FILE *fp = fopen(fileName, "rb");
	if(!fp){
		fp=fopen(fileName, "w");
		fprintf(fp, "000 ");
		fclose(fp);
		return NULL;
	}
	while(1){
		pnewcode = (mycode *)malloc(sizeof(mycode));
		fscanf(fp, "%s", pnewcode->val);
		if(strcmp(pnewcode->val, "000") == 0){
			free(pnewcode);
			break;
		}
		plast->pnext = pnewcode;
		plast = pnewcode;
		plast->pnext = NULL;
	}
	return pHead;
}
void showLinkedList(mycode *pHead){
	mycode *p;
	for(p = pHead->pnext; p; p = p->pnext){
		showLinkedListCode(p);
	}
	return;
}
void freeLinkedList(mycode *pHead){
	mycode *thenext;
	mycode *p;
	for(p = pHead; p; p = thenext){
		thenext = p->pnext;
		free(p);
	}
	return;
}
void makeMatrix(mycode *pHead, char *op){
	mycode *p;
	int i = 0;
	int j = 0;
	for(p = pHead->pnext; p; p = p->pnext){
		strcpy((op + i * 12 + j), p->val);
		j ++;
		if(j == 12){
			i ++;
			j = 0;
		}
	}
}
void showLinkedList_buffer(buffers *pHead){
	buffers *p;
	for(p = pHead->pnext; p; p = p->pnext){
		showLinkedListCode_buffer(p);
	}
	return;
}
void freeLinkedList_buffer(buffers *pHead){
	buffers *thenext;
	buffers *p;
	for(p = pHead; p; p = thenext){
		thenext = p->pnext;
		free(p);
	}
	return;
}
bool isConstent(char *buffer){
	for(int i = 0; i < strlen(buffer); i++){
		if(*(buffer + i) < 48 || *(buffer + i) > 57)
		return false;
	}
	return true;
}
bool isVar(char *buffer){
    if(*buffer < 97 || *buffer > 122)return false;
	return true;
}
int isOperate(char *buffer){
	if(strcmp(buffer, "+") == 0) return 1;
	if(strcmp(buffer, "-") == 0) return 2;
	if(strcmp(buffer, "*") == 0) return 3;
	if(strcmp(buffer, "/") == 0) return 4;
	if(strcmp(buffer, "?") == 0) return 5;
	if(strcmp(buffer, "clear") == 0) return 6;
	return -1;
}
int mappingNum(char *buffer){
	if(strcmp(buffer, "=") == 0)return 0;
	if(strcmp(buffer, "?") == 0)return 1;
	if(strcmp(buffer, "+") == 0)return 2;
	if(strcmp(buffer, "-") == 0)return 3;
	if(strcmp(buffer, "*") == 0)return 4;
	if(strcmp(buffer, "/") == 0)return 5;
	if(strcmp(buffer, "(") == 0)return 6;
	if(strcmp(buffer, ")") == 0)return 7;
	if(isVar(buffer))return 8;
	if(isConstent(buffer))return 9;
	if(strcmp(buffer, "clear") == 0)return 10;
	if(strcmp(buffer, "#") == 0)return 11;	
}
buffers *syntaxAnalyzer(mycode *temp, buffers *src, char *str1){
	mycode *plast_temp;
	for(plast_temp = temp; plast_temp->pnext; plast_temp = plast_temp->pnext);
	mycode *newcode_temp;
	buffers *dest = (buffers *)malloc(sizeof(buffers));
	buffers *pnewcode = (buffers *)malloc(sizeof(buffers));
	strcpy(pnewcode->val, "#");
	dest->pnext = pnewcode;
	dest->prior = NULL;
	pnewcode->pnext = NULL;
	pnewcode->prior = dest;
	buffers *plast = pnewcode;
	buffers *p;
	for(p = src->pnext; p; p = p->pnext){
		pnewcode = (buffers *)malloc(sizeof(buffers));
		int i = mappingNum(plast->val);
		int j = mappingNum(p->val);
		if(strncmp((str1 + i * 12 + j), "<", 1) == 0 || strncmp((str1 + i * 12 + j), "=", 1) == 0){
			strcpy(pnewcode->val, p->val);
			strncpy(plast->str, (str1 + i * 12 + j), 1);
			plast->str[1] = 0;
			plast->pnext = pnewcode;
			pnewcode->prior = plast;
			plast = pnewcode;
			plast->pnext = NULL;
			buffers *before = p->prior;
			before->pnext = p->pnext;
			if(p->pnext == NULL && strcmp(p->val, "#") == 0){
				strcpy(plast->str, "!");
				free(p);
				continue;
			}
			p->pnext->prior = before;
			free(p);
			p = before;
		}else if(strncmp((str1 + i * 12 + j), "!", 1) == 0){
			strcpy(plast->str, "!");
			printf("error in %s\n", p->val);
			free(pnewcode);
			break;
		}else{
			strncpy(plast->str, (str1 + i * 12 + j), 1);
			plast->str[1] = 0;
			for(buffers *former = plast; former != dest; former = plast){
				if(strcmp(former->str, "=") == 0 || strcmp(former->str, ">") == 0){
					newcode_temp = (mycode *)malloc(sizeof(mycode));
					plast = former->prior;
					plast->pnext = NULL;
					former->prior = NULL;
					strcpy(newcode_temp->val, former->val);
					free(former);
					plast_temp->pnext = newcode_temp;
					newcode_temp->prior = plast_temp;
					plast_temp = newcode_temp;
					plast_temp->pnext = NULL;
				}else if(strcmp(former->str, "<") == 0){
					break;
				}
			}
			free(pnewcode);
			p = p->prior;
		}
	}
	return dest;
}
char *var2Num(buffers *var, char *op){
	buffers *p;
	buffers *plast;
	for(plast = var; plast->pnext; plast = plast->pnext);
	for(p = plast; p != var; p = p->prior){
		if(strcmp(p->str, op) == 0){
			char str[15];
			strcpy(str, p->val);
			str[strlen(p->val)] = 0;
			return str;
		}
	}
	return NULL;
}
void clearVar(buffers *var){
	buffers *p;
	buffers *thenext;
	for(p = var->pnext; p; p = thenext){
		thenext = p->pnext;
		free(p);
	}
	var->pnext = NULL;
}
mycode *func(buffers *var, mycode *p_temp, mycode *newcode_temp, int op){
	if(op == -1)return p_temp;
	if(op == 5){
		char msg[15];
		if(var2Num(var, p_temp->prior->val) == NULL){
			printf("%s\n", p_temp->prior->val);
		}else{
			strcpy(msg, var2Num(var, p_temp->prior->val));
			printf("%s\n", msg);
		}
		return p_temp;
	}
	if(op == 6){
		clearVar(var);
		return p_temp;
	}
	char op1[15];
	char op2[15];
	strcpy(op2, p_temp->prior->val);
	op2[strlen(p_temp->prior->val)] = 0;
	if(var2Num(var, op2) != NULL){
		strcpy(op2, var2Num(var, op2));
	}
	mycode *before = p_temp->prior;
	strcpy(op1, before->prior->val);
	op1[strlen(before->prior->val)] = 0;
	if(var2Num(var, op1) != NULL){
		strcpy(op1, var2Num(var, op1));
	}
	int tem = 0;
	if(op == 1){
		tem = atoi(op1) + atoi(op2);
	}else if(op == 2){
		tem = atoi(op1) - atoi(op2);
	}else if(op == 3){
		tem = atoi(op1) * atoi(op2);
	}else if(op == 4){
		tem = atoi(op1) / atoi(op2);
	}
	itoa(tem, op1, 10);
	before = p_temp->prior;
	before->pnext = p_temp->pnext;
	p_temp->pnext->prior = before;
	free(p_temp);
	p_temp = before->prior;
	p_temp->pnext = before->pnext;
	before->pnext->prior = p_temp;
	free(before);
	before = p_temp->prior;
	before->pnext = p_temp->pnext;
	p_temp->pnext->prior = before;
	free(p_temp);
	newcode_temp = (mycode *)malloc(sizeof(mycode));
	strcpy(newcode_temp->val, op1);
	p_temp = before->pnext;
	before->pnext = newcode_temp;
	newcode_temp->prior = before;
	newcode_temp->pnext = p_temp;
	p_temp->prior = newcode_temp;
	return before;
}
void makeVar(buffers *var, mycode *temp){
	mycode *p_temp;
	mycode *newcode_temp;
	buffers *p_var;
	buffers *newcode_var;
	buffers *plast;
	for(plast = var; plast->pnext; plast = plast->pnext);
	for(p_temp = temp->pnext; p_temp; p_temp = p_temp->pnext){
		p_temp = func(var, p_temp, newcode_temp, isOperate(p_temp->val));
	}
	p_temp = temp->pnext;
	if(p_temp && p_temp->pnext && strcmp(p_temp->pnext->val, "?") != 0 && strcmp(p_temp->val, "clear") != 0){
		//printf("oop\n");
		newcode_var = (buffers *)malloc(sizeof(buffers));
		strcpy(newcode_var->val, p_temp->val);
		p_temp = p_temp->pnext->pnext;
		strcpy(newcode_var->str, p_temp->val);
		plast->pnext = newcode_var;
		newcode_var->prior = plast;
		plast = newcode_var;
		plast->pnext = NULL;
	}
}
int main(){
	char a[12][12];
	mycode *pHead = createLinkedListFromFile(fName);
	makeMatrix(pHead, &a[0][0]);
	freeLinkedList(pHead);
	char str[128];
	buffers *var = (buffers *)malloc(sizeof(buffers));
	var->pnext = NULL;
	var->prior = NULL;
	while(1){
		gets(str);
		if(strcmp(str, "end") == 0)break;
		mycode *temp = (mycode *)malloc(sizeof(mycode));
		temp->pnext = NULL;
		temp->prior = NULL;
		buffers *src = createLinkedList(str);
		buffers *dest = syntaxAnalyzer(temp, src, &a[0][0]);
		makeVar(var, temp);
		freeLinkedList_buffer(src);
		freeLinkedList(temp);
		freeLinkedList_buffer(dest);
	}
	freeLinkedList_buffer(var);
	return 0;
}