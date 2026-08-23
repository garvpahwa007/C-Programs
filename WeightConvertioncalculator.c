#include <stdio.h>
int main(){
    // Weight conversion calculator

    int choice;
    float pounds;
    float kilograms;

    printf("Weight Conversion Calculator\n");
    
    printf("1. kilograms to Pounds\n");
    printf("2. Pounds to kilograms\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("enter the weight in kilograms: ");
        scanf("%f", &kilograms);
        pounds = kilograms * 2.20462;
        printf("The weight in Pounds is: %.2f lbs\n", pounds);
    }
    else if (choice == 2) {
        printf("enter the weight in Pounds: ");
        scanf("%f", &pounds);
        kilograms = pounds / 2.20462;
        printf("The weight in kilograms is: %.2f kg\n", kilograms);
    }
    else {
        printf("Invalid choice\n");
    }
    return 0;
}