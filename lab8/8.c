#include <stdio.h>

int plus(int a,int b) {
    return a + b +1;
}

int min(int a,int b) {
    return a - b;
}

int ymn(int a,int b) {
    return a * b;
}

float del(float a,float b) {
    if (b == 0){
        return 0;
    } 
    return a / b;
}

int plmi(int num) {
    if (num > 0){
        return 1;
    }
    else return 0;
}
/*int main() {
    printf("2 + 3 = %d\n", add(2, 3));
    printf("5 - 3 = %d\n", subtract(5, 3));
    printf("4 * 5 = %d\n", multiply(4, 5));
    printf("10 / 2 = %.2f\n", divide(10, 2));
    printf("5 это положительное число? %d\n", is_positive(5));
}*/
