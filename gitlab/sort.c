#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void FillInc(long long int a[], int n) {// Заполнение массива возрастающими значениями
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }
}


void FillDec(long long int a[], int n) {// Заполнение массива убывающими значениями
    int k = n;
    for (int i = 0; i < n; i++) {
        a[i] = k;
        k--;
    }
}


void FillRand(long long int a[], int n) {// Заполнение массива случайными значениями
    for (int i = 0; i < n; i++) {
        a[i] = rand();
    }
}

int BubbleSort(long long int a[], int n) {
    int M = 0, C = 0;
    for (int i=0;i<n-1; i++) {
        for (int j=0; j<n-i-1; j++) {
            C++;
            if (a[j]>a[j+1]) {
                M += 3;
                long long int t = a[j];
                a[j]=a[j+1];
                a[j+1]= t;
            }
        }
    }
    return M + C;
}

void PrintMas(long long int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%lld ", a[i]);
    }
    printf("\n");
}


int Ub(long long int a[], int n) {// Тестирование для убывающего массива
    FillDec(a, n);
    return BubbleSort(a, n);
}


int Vz(long long int a[], int n) {// Тестирование для возрастающего массива
    FillInc(a, n);
    return BubbleSort(a, n);
}


int Rd(long long int a[], int n) {// Тестирование для случайного массива
    FillRand(a, n);
    return BubbleSort(a, n);
}

int main() {
    srand(time(NULL)); // Инициализация генератора случайных чисел

    int n1 = 100, n2 = 200, n3 = 300, n4 = 400, n5 = 500;
    int u1, u2, u3, u4, u5;
    int v1, v2, v3, v4, v5;
    int r1, r2, r3, r4, r5;

    
    int teor1 = 2 * n1 * (n1 - 1);
    int teor2 = 2 * n2 * (n2 - 1);// Теоретические оценки
    int teor3 = 2 * n3 * (n3 - 1);
    int teor4 = 2 * n4 * (n4 - 1);
    int teor5 = 2 * n5 * (n5 - 1);

    
    long long int a1_ub[n1], a2_ub[n2], a3_ub[n3], a4_ub[n4], a5_ub[n5];
    long long int a1_vz[n1], a2_vz[n2], a3_vz[n3], a4_vz[n4], a5_vz[n5];// Массивы для каждого случая
    long long int a1_rd[n1], a2_rd[n2], a3_rd[n3], a4_rd[n4], a5_rd[n5];

    
    u1 = Ub(a1_ub, n1);
    u2 = Ub(a2_ub, n2);
    u3 = Ub(a3_ub, n3);
    u4 = Ub(a4_ub, n4);// Вычисление M+C для каждого случая
    u5 = Ub(a5_ub, n5);

    v1 = Vz(a1_vz, n1);
    v2 = Vz(a2_vz, n2);
    v3 = Vz(a3_vz, n3);
    v4 = Vz(a4_vz, n4);
    v5 = Vz(a5_vz, n5);

    r1 = Rd(a1_rd, n1);
    r2 = Rd(a2_rd, n2);
    r3 = Rd(a3_rd, n3);
    r4 = Rd(a4_rd, n4);
    r5 = Rd(a5_rd, n5);

    // Вывод таблицы
    printf(" __________________________________________\n");
    printf("|       |  M+C  |      Фактический M+С     |\n");
    printf("|   N   |       |__________________________|\n");
    printf("|       |Теорет.| Убыв.  |  Случ. |  Возр. |\n");
    printf("|_______|_______|________|________|________|\n");
    printf("|  100  | %5d | %6d | %6d | %6d |\n", teor1, u1, r1, v1);
    printf("|_______|_______|________|________|________|\n");
    printf("|  200  | %5d | %6d | %6d | %6d |\n", teor2, u2, r2, v2);
    printf("|_______|_______|________|________|________|\n");
    printf("|  300  |%5d | %6d | %6d | %6d |\n", teor3, u3, r3, v3);
    printf("|_______|_______|________|________|________|\n");
    printf("|  400  |%5d | %6d | %6d | %6d |\n", teor4, u4, r4, v4);
    printf("|_______|_______|________|________|________|\n");
    printf("|  500  |%5d | %6d | %6d | %6d |\n", teor5, u5, r5, v5);
    printf("|_______|_______|________|________|________|\n");

}
