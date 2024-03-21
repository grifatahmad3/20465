/* Open University, Systems Labs 20465, Semester 2024B, Maman 11, Question 02.
** Author: Ahmad Grifat
** Homework desription: printing and calculating how much suffixes are there 
*********************** in str that start with the char c.
*/


#include <stdio.h>

#define MAX 128

int my_suffix(char str[], char c){
    int num = 0, i=1;
    if(str[0]=='\0') return 0;
    while(str[i]!='\0'){
        if(str[i]==c){
            printf("%s\n", (str+i));
            num++;
        }
        i++;
    }
    return num;
}

void welcome_message(void){
    printf("\nHello!\n");
    printf("Please enter a letter followed by a line which you would like to find all\n");
    printf("suffixes that start with that letter in:\n");
}

int main(void){

    char str[MAX];
    char c, k;
    int i=0, suffixes;

    welcome_message();
    while((c=getchar())==' '|| c=='\t' || c=='\n')
        ;
    /*c = getchar();*/
    while((k=getchar())==' '|| k=='\t' || k=='\n')
        ;
    while(k!=EOF && k!='\n'){
        str[i++] = k;
        k=getchar();
    }
    str[i]='\0';

    printf("\nYou entered the letter \'%c\', ", c);
    printf("and the line:\n%s\n", str);

    printf("\nThe suffixes are:\n");
    suffixes = my_suffix(str, c);
    printf("\nand they are %d in number.\n\nHave a nice day.\n", suffixes);


    return 0;
}
