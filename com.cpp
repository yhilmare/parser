#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h> 
#define fName "h:/homework/word.txt"
#define fName1 "h:/homework/operate.txt"
#define fName2 "h:/homework/bounds.txt"
#define program "h:/homework/tests.txt"
#define destprogram "h:/homework/test.txt"
#define resultfile "h:/homework/result.txt"
struct my_system{
	char word[12];
	char code[4];
	my_system *pNext;
	my_system *pripor;
};
long getFileLength(char *filenName){
	long fSize;
	FILE *fp = fopen(filenName,"rb");
	if(fp == NULL) return -1;
	fseek(fp,0L,SEEK_END);
	fSize=ftell(fp);
	fclose(fp);
	return fSize;
}
void showEverySingleNode(my_system *pHead){
	
	printf("%s--%s\n", pHead->word, pHead->code);
	return;
}
my_system *createLinkedListByFileWithThePath(char *fNames){
	my_system *pHead = (my_system*)malloc(sizeof(my_system));
	pHead->pNext = NULL;
	pHead->pripor = NULL;
	my_system *plast;
	my_system *pnewloader;
	for(plast = pHead; plast->pNext; plast = plast->pNext);
	FILE *fp = fopen(fNames, "rb");
	if(!fp){
		fp=fopen(fNames, "w");
		fprintf(fp, "000 ");
		fclose(fp);
		return NULL;
	}
	while(!feof(fp))
	{
		pnewloader = (my_system*)malloc(sizeof(my_system));
		fscanf(fp, "%s", pnewloader->word);
		if(strcmp(pnewloader->word,"000") ==0 ){
			free(pnewloader);
			break;
		}
		fscanf(fp, "%s", pnewloader->code);
		plast->pNext = pnewloader;
		pnewloader->pripor = plast;
		plast = pnewloader;
		plast->pNext = NULL;
	}
	fclose(fp);
	return pHead;
}
char *readProgramFromTheFile(char *fileName){	
	long fSize = getFileLength(fileName);
	if(fSize<0){
		printf("发生错误，文件错误\n");
		return NULL;
	}
    FILE *fp = fopen(fileName, "rb");
	if(fp == NULL){
		printf("文件不存在，打开失败\n");
		return 0;
	}
    char *buffer = (char*)malloc(fSize + 1);
    buffer[fSize] = 0;
	fread(buffer,1,fSize,fp);
	fclose(fp);
	return buffer;
}
void showLinkedListWithTheNormalOrder(my_system *pHead){
	for(my_system *p = pHead->pNext; p; p = p->pNext){
		showEverySingleNode(p);
	}
	printf("\n");
	return;
}
void showLinkedListWithTheoppositeOrder(my_system *pHead){
	my_system *plast = NULL;
	for(plast = pHead; plast->pNext; plast = plast->pNext);
	for(1; plast->pripor; plast = plast->pripor){
		showEverySingleNode(plast);
	}
}
void getlinkedListFree(my_system *pHead){	
	my_system *p;
	my_system *thenext;
	for(p=pHead; p; p = thenext){
		thenext = p->pNext;
		free(p);
	}return;
}
char *subStringWithIndex(char *buffer, int begin, int end){
	long length = strlen(buffer);
	if(end < begin) return NULL;
	if(begin < 0) return NULL;
	if(end >= length) return NULL;
	char *newString = (char *)malloc((end - begin) + 2);
	char *str = buffer;
	int j = 0;
	for(int i = begin; i <= end; i++){
		newString[j++] = str[i];
	}
	newString[(end - begin) + 1] = 0;
	return newString;
}
long firstIndexOfString(char *buffer, char *str){
	long length_buffer = strlen(buffer);
	long length_str = strlen(str);
	if(length_str > length_buffer){
		return -1;
	}else if(length_str == length_buffer){
		if(strcmp(buffer, str) == 0) return 0;
		else return -1;
	}
	char *src = buffer;
	for(int i = 0; i < length_buffer; i++){
		if(src[i] == str[0]){		
			char *msg = NULL;
			msg = subStringWithIndex(src, i, (i + length_str - 1));
			if(msg == NULL) return -1;
			if(strcmp(msg, str) == 0){
				return i;
			}
			free(msg);
		}
	}
	return -1;
}
long numberOfSpecifyString(char *buffer, char *str){
	long length_buffer = strlen(buffer);
	long length_str = strlen(str);
	int count = 0;
	if(length_str > length_buffer){
		return -1;
	}else if(length_str == length_buffer){
		if(strcmp(buffer, str) == 0) return 1;
		else return -1;
	}
	char *src = buffer;
	for(int i = 0; i < length_buffer; i++){
		if(src[i] == str[0]){
			char *msg = NULL;
			msg = subStringWithIndex(src, i, (i + length_str - 1));
			if(msg == NULL){
				if(count == 0)return -1;
				else return count;
			}
			if(strcmp(msg, str) == 0){
				count ++;
			}
			free(msg);
		}
	}
	return count;
}
char *addString(char *former, char *last){
	int length_former = strlen(former);
	int length_last = strlen(last);
	char *dest = (char *)malloc(length_former + length_last + 1);
	for(int i = 0; i < length_former; i++){
		dest[i] = former[i];
	}
	for(int i = length_former; i < (length_former + length_last); i++){
		dest[i] = last[i- length_former];
	}
	dest[length_former + length_last] = 0;
	free(former);
	free(last);
	return dest;
}
char *removeStringFromDest(char *buffer, char *src){
	int numberOfSrc = numberOfSpecifyString(buffer, src);
	long length_buffer = strlen(buffer);
	long length_src = strlen(src);
	int i = 1;
	char *result = buffer;
	while((i++) <= numberOfSrc){
		int index = firstIndexOfString(result, src);
		char *former = NULL;
		char *last = NULL;
		if((index - 1) >= 0){
			if(strcmp(src, "\n") == 0){
				former = subStringWithIndex(result, 0, index - 2);
			}else{
				former = subStringWithIndex(result, 0, index - 1);
			}
		}
		if((index + length_src) < strlen(result)){
			last = subStringWithIndex(result, (index + length_src), (strlen(result) - 1));
		}
		if(former == NULL){
			free(result);
			result = last;
		}else{
			if(last == NULL){
				free(result);
				result = former;
			}else{
				free(result);
				result = addString(former, last);
			}	
		}
	}
	return result;
}
char *getRidOfNote(char *buffer){
	int numberOfSrc = numberOfSpecifyString(buffer, "//");
	char *result = buffer;
	int count = 1;
	while((count++) <= numberOfSrc){
		int index = firstIndexOfString(result, "//");
		for(int i = index; 1; i++ ){
			if(result[i] == 10){
				char *str = subStringWithIndex(result, index, (i-2));
				result = removeStringFromDest(result, str);
				break;
			}
		}
	}
	return result;
}
char *getProgramWithFormat(){
	char *buffer = readProgramFromTheFile(program);
	char *result = getRidOfNote(buffer);
	result = removeStringFromDest(result, "\n");
	result = removeStringFromDest(result, " ");
	return result;
}
void writeToFile(char *buffer, char *filename){
	FILE *fp = fopen(filename, "wb");
	fprintf(fp, "%s", buffer);
	fclose(fp);
}
void linkedListWriteToFile(my_system *pHead, char *filename){
	FILE *fp = fopen(filename, "wb");
	for(my_system *p = pHead->pNext; p; p = p->pNext){
		fprintf(fp, "(%s——%s)\n\r", p->word, p->code);
	}
	fclose(fp);
}
bool isWord(char buffer){
	if(buffer >= 65 && buffer <= 90){
		return true;
	}else if(buffer >= 97 && buffer <= 122){
		return true;
	}else{
		return false;
	}
}
bool isNumber(char buffer){
	if(buffer >= 48 && buffer <=57){
		return true;
	}else if(buffer == 46){
		return true;
	}else{
		return false;
	}
}
bool isBound(char buffer){
	if(buffer == 40 || buffer == 41 || buffer == 44 || buffer == 91 || buffer == 93 || buffer == 125 || buffer == 125){
		return true;
	}else if(buffer >=59 && buffer <= 62){
		return true;
	}else{
		return false;
	}
}
bool isOperate(char buffer){
	if(buffer == 42 || buffer == 43 || buffer == 45 || buffer == 47 ){
		return true;
	}else{
		return false;
	}
}
char *removeStringFromDestWithLinkedList(char *buffer, char *src, char *src1, my_system *pHead1){
	
	my_system *plast;
	my_system *pnewcoder;
	for(plast = pHead1; plast->pNext; plast = plast->pNext);
	int numberOfSrc = numberOfSpecifyString(buffer, src);
	long length_buffer = strlen(buffer);
	long length_src = strlen(src);
	int i = 1;
	char *result = buffer;
	while((i++) <= numberOfSrc){
		int index = firstIndexOfString(result, src);
		char *former = NULL;
		char *last = NULL;
		if(index == 0 && strlen(result) == 1){
			free(result);
			result = "";
			pnewcoder = (my_system *)malloc(sizeof(my_system));
			strcpy(pnewcoder->word, src);
			strcpy(pnewcoder->code, src1);
			plast->pNext = pnewcoder;
			pnewcoder->pripor = plast;
			plast = pnewcoder;
			plast->pNext = NULL;
			break;
		}
		if((index - 1) >= 0){
			if(strcmp(src, "\n") == 0){
				former = subStringWithIndex(result, 0, index - 2);
			}else{
				former = subStringWithIndex(result, 0, index - 1);
			}
		}
		if((index + length_src) < strlen(result)){
			last = subStringWithIndex(result, (index + length_src), (strlen(result) - 1));
		}
		if(former == NULL){
			free(result);
			result = last;
		}else{
			if(last == NULL){
				free(result);
				result = former;
			}else{
				free(result);
				result = addString(former, last);
			}	
		}
		pnewcoder = (my_system *)malloc(sizeof(my_system));
		strcpy(pnewcoder->word, src);
		strcpy(pnewcoder->code, src1);
		plast->pNext = pnewcoder;
		pnewcoder->pripor = plast;
		plast = pnewcoder;
		plast->pNext = NULL;
	}
	return result;
}
char *getWord(char *buffer, my_system *pHead, my_system	*pHead1){

	my_system *p;
	for(p = pHead->pNext; p; p = p->pNext){
		buffer = removeStringFromDestWithLinkedList(buffer, p->word, p->code, pHead1);
	}
	return buffer;
}
char *getNumber(char *buffer, my_system	*pHead1){
	int count = 0;
	for(int i = 0; i < strlen(buffer); i++){
		if(isNumber(buffer[i])){
			count ++;
			if(buffer[i+1] == 0 || !isNumber(buffer[i+1])){
				char *temp = subStringWithIndex(buffer, (i - count + 1), i);
				buffer = removeStringFromDestWithLinkedList(buffer, temp, "60", pHead1);
				i = i - count;
				count = 0;
				free(temp);
			}
		}
	}
	return buffer;
}
char *getUserWord(char *buffer, my_system *pHead1){
	int count = 0;
	for(int i = 0; i < strlen(buffer); i++){
		if(isWord(buffer[i])){
			count ++;
			if(isOperate(buffer[i+1]) || isBound(buffer[i+1])){
				char *temp = subStringWithIndex(buffer, (i - count + 1), i);
				buffer = removeStringFromDestWithLinkedList(buffer, temp, "61", pHead1);
				i = i - count;
				count = 0;
				free(temp);
			}
		}
	}
	return buffer;
}
int main(){
    my_system *pHead = createLinkedListByFileWithThePath(fName);
    my_system *pHead1 = createLinkedListByFileWithThePath(fName1);
    my_system *pHead2 = createLinkedListByFileWithThePath(fName2);
    my_system *pHead3 = (my_system *)malloc(sizeof(my_system));
    pHead3->pNext = NULL;
    pHead3->pripor = NULL;
  	/*showLinkedListWithTheNormalOrder(pHead);//关键字 
   	showLinkedListWithTheNormalOrder(pHead1);//操作符 
   	showLinkedListWithTheNormalOrder(pHead2);//界符 */
	char *result = getProgramWithFormat();
	printf("%s\n\n", result);
	writeToFile(result, destprogram);
	result = getWord(result, pHead, pHead3);
	result = getNumber(result, pHead3);
	result = getUserWord(result, pHead3);
	result = getWord(result, pHead2, pHead3);
	result = getWord(result, pHead1, pHead3);
	showLinkedListWithTheNormalOrder(pHead3);
	if(strlen(result) != 0){
		printf("error\n");
	}
	free(result);
	linkedListWriteToFile(pHead3, resultfile);
	getlinkedListFree(pHead);
	getlinkedListFree(pHead1);
	getlinkedListFree(pHead2);
	getlinkedListFree(pHead3);
	return 0;
}