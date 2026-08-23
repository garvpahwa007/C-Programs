#include <stdio.h>
#include <string.h>
    //Logical Operators Practice
    // here we are going to print a birthday message 3 time

void happyBirthday(char name[], int age){
    printf("\nHappy Birthday to you!\n");
    printf("Happy Birthday to you!\n");
    printf("Happy Birthday dear %s!\n", name);
    printf("Happy Birthday to you!\n");
    printf("you are %d years old!\n", age);
}
int main(){
    char name[20];
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove newline character from the name
    int age;
    printf("Enter your age: ");
    scanf("%d", &age);
    happyBirthday(name , age);
    happyBirthday(name , age);
    happyBirthday(name , age);
    return 0;
}