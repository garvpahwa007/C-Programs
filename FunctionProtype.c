#include <stdio.h>
#include <stdbool.h>

// Function Prototype: Provides the compiler w/ information
//                     and parameters before its actual definition.
//                     Enables type checking and allows functions 
//                     to be used before they're defined.
//                     Improve readability, organizations and 
//                     help prevent errors.

void hello(char name[], int age); //function prototype
bool ageCheck(int age){
    return age >= 16;
}

int main(){
    hello("Sponge Bob" , 30);
    

    if(ageCheck(30)){
        printf("You are old enough to work at rusty crab");
    }
    else{
        printf("You must be 16");
    }
    return 0;
}
void hello(char name[], int age){
    printf("Hello%s\n" , name);
    printf("You are %d years old\n" , age);
}