#include <stdio.h>
#include <stdbool.h>
int main() {

    float price = 10.00;
    int student_input = 0;
    printf("Are you a student? (1 for yes, 0 for no): ");
    if (scanf("%d", &student_input) != 1) {
        return 1;
    }
    bool is_student = student_input != 0;
    int senior_input = 0;
    printf("Are you a senior citizen? (1 for yes, 0 for no): ");
    if (scanf("%d", &senior_input) != 1) {
        return 1;
    }
    bool is_senior = senior_input != 0;

    // student discount is 10% and senior citizen discount is 20

    if (is_student) {
        if (is_senior) {
            price = price * 0.7; // 30% discount for both
        } else {
            price = price * 0.9; // 10% discount for student
        }
    }
    else if (is_senior) {
        price = price * 0.8; // 20% discount for senior citizen
    }
    printf("The final price of the movie ticket is: $%.2f\n", price);
    return 0;
}