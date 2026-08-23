#include <stdio.h>

int main() {
    int age;

    printf("Enter your age: ");
    scanf("%d", &age);
    
    if (age >= 60) {
        printf("you are a senior citizen");
    }
    else if (age >= 18) {
        printf("you are an adult");
    }
    else if (age < 0) {
        printf("you are not born yet");
    }
    else if (age == 0) {
        printf("you are a newborn");
    }
    else {
        printf("you are a minor");
    }
    return 0;
    }

