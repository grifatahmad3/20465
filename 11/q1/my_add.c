/* Open University, Systems Labs 20465, Semester 2024B, Maman 11, Question 01.
** Author: Ahmad Grifat
** Homework desription: addition of two decimals in binary form.
*/

#include <stdio.h>

/*This is the maximum width of priting in binary, can be changed to the width of the desired print*/
#define BITS 32 

/* Printing number in binary */
void print_in_binary(unsigned int num){
    int i;
    unsigned mask = 1<<(BITS-1);
    for(i=0; i<BITS; i++){
        if(num&mask) printf("1");
        else printf("0");
        mask/=2;
    }
}


unsigned int my_add(unsigned int a, unsigned int b){
    unsigned int result = 0, carry = 0;
    int i;

    printf("\nFirst number: ");
    print_in_binary(a);
    printf(",\nSecond number: ");
    print_in_binary(b);

    result = a + b; /*Fix here*/

    printf(",\nResult: ");
    print_in_binary(result);

    return result;
}

void welcome_message(void){
    printf("\nHello.\n");
    printf("Here you enter two unsigned numbers to add.\n");
    printf("The numbers are to be decimal and up to 6 digits in width.\n");
    printf("Enter the numbers please:\n");
    return;
}

void goodbye_message(unsigned int result, unsigned int a, unsigned int b){
    printf("\n\nIn summary:\nfirst number was %u,\nSecond number was %u,\n", a, b);
    printf("The result of the addition is %u.\n", result);
    printf("\nHave a nice day.\n");
}

int main(void){

    unsigned int a, b, result;

    welcome_message();
    scanf(" %u", &a);
    scanf(" %u", &b);
    printf("\nFirst number is %u, second number is %u.\n", a, b);

    result = my_add(a, b);
    goodbye_message(result, a, b);
    return 0;
}