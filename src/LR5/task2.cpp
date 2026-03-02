#include <stdio.h>
#include <ctype.h>

int main(){
 char n[50],b;
 int e=0,ne=0;
 FILE*f;
 
 printf("Файл: ");scanf("%s",n);
 
 if(!(f=fopen(n,"r")))
  printf("Ошибка");
 else{
  while(!feof(f)){
   b=getc(f);
   if(!feof(f)){
    putchar(b);
    (isspace(b)||iscntrl(b))?e++:ne++;
   }
  }
  fclose(f);
  printf("\n\nПустых: %d\nНепустых: %d\nВсего: %d",e,ne,e+ne);
 }
 return 0;
}