#include <stdio.h>
int main(){
char n[50];FILE*f;int c;
printf("Файл: ");scanf("%s",n);
if(!(f=fopen(n,"r")))printf("Ошибка");
else{
 while((c=getc(f))!=EOF) putchar(c);
 printf("\n");  // ← просто добавьте эту строку
 fclose(f);
}
return 0;
}