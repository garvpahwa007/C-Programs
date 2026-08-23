#include<stdio.h>
 
int square(int num){
    return num * num;
}
int main() {
    int x = square(5);
    int y = square(10);
    printf("Square of 5 is %d\n", x);
    printf("Square of 10 is %d\n", y);
    return 0;
}