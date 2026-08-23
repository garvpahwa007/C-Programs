#include <stdio.h>
int main() {
    // Calculator for basic arithmetic operations
    double num1, num2, result;
    char operator;

    printf("Enter first number: ");
    scanf("%lf", &num1);
    printf("Enter an operator (+, -, *, /): ");
    scanf(" %c", &operator);
    printf("Enter second number: ");
    scanf("%lf", &num2);
    
    switch (operator) {
        case '+':
            result = num1 + num2;
            printf("Result: %.4lf\n", result);
            break;
        case '-':
            result = num1 - num2;
            printf("Result: %.4lf\n", result);
            break;
        case '*':
            result = num1 * num2;
            printf("Result: %.4lf\n", result);
            break;
        case '/':
            if (num2 == 0) {
                printf("Error: Division by zero is not allowed.\n");
            } else {
                result = num1 / num2;
                printf("Result: %.4lf\n", result);
            }
            break;
        default:
            printf("Error: Invalid operator.\n");
    }
    printf("Thank you for using the calculator!\n");
    return 0;
}
   