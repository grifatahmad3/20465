/* PartialSums calculates the partial sums of an int array and returns an array such that
 * each element represents tha partial of sum of the original array until that element.
 * Open University, 20465 System Labs, Semseter 2024B.
 * Author: Ahmad Grifat
 */

#include <stdio.h>
#include <stdlib.h>

void welcomeMessage() {
    printf("\n\t\tWelcome!\nPlease enter the size of the array followed by\nthe array elements:\n");
}


int* partialSums(int* array, int size) {
    int i=0;
    int *newArray;
    if(array==NULL)
        return NULL;
    newArray = (int*)malloc((size) * sizeof(int));
    if(newArray==NULL)
        return NULL;


    *(newArray+i) = *(array+i);
    i++;
    while(i<size) {
        *(newArray+i) = *(array+i) + *(newArray+i-1);
        i++;
    }

    return newArray;
}


void printResult(int *array, int *newArray, int size) {
    int i=0;
    printf("\nThank you!\nHere are the results:\n\n");
    printf("Array size = %d\n", size);
    printf("Original array: ");
    while (i<size) {
        printf("%d ", *(array+i));
        i++;
    }
    printf("\nThe partial sums array: ");
    i=0;
    while (i<size) {
        printf("%d ", *(newArray+i));
        i++;
    }
    printf("\n\nHopefully that was helpful.\nSee you next time!\n");
}


int main(void) {
    int *array, *newArray;
    int size, num, i=0;

    welcomeMessage();
    scanf(" %d", &size);
    array = (int*)malloc(size * sizeof(int));
    if(array==NULL) {
        printf("\nCouldn't allocate memory!\nExiting...");
        return 1;
    }

    while(i<size && scanf(" %d", &num)==1) {
        *(array+i)=num;
        i++;
    }

    newArray = partialSums(array, size);
    if(newArray==NULL) {
        printf("\nCouldn't allocate memory!\nExiting...");
        return 1;
    }

    printResult(array, newArray, size);

    free(array);
    free(newArray);
    return 0;
}
