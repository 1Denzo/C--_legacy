#include <stdio.h>
#include <string.h>

int poisk(FILE*f,char*s){
 char b[1024];int ln=0,c=0;rewind(f);
 while(fgets(b,1024,f)){
  ln++;char*p=b;
  while((p=strstr(p,s))){c++;printf("Стр %d поз %d\n",ln,p-b+1);p++;}
 }
 printf("Найдено: %d\n",c);return c;
}

int main(){
 char n[50],s[100];FILE*f;
 printf("Файл: ");scanf("%s",n);
 if(!(f=fopen(n,"r")))printf("Ошибка");
 else{
  while(!feof(f))putchar(getc(f));
  printf("\nПодстрока: ");scanf("%s",s);
  poisk(f,s);fclose(f);
 }
 return 0;
}