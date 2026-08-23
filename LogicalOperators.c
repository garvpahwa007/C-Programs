#include <stdio.h>
int main(){
    int temp;
    printf("Enter the temperature in Celsius: ");
    scanf("%d", &temp);

    if (temp >0 && temp <30){
        printf("The weather is pleasant.\n");

    }
    else {
        printf("The weather is not pleasant.\n");
    }
    return 0;
}