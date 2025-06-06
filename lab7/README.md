## **Практическое задание 7. Знакомство с POSIX потоками**


### **Оценка 3. Знакомство с pthread:**
1.	Создать поток

Написать программу, которая создает поток с помощью pthread_create(). Использовать атрибуты по умолчанию. Родительский и дочерний потоки должны вывести на экран по 5 строк текста.
```c
#include <stdio.h>
#include <pthread.h>

void *function(void *_){
    for (int i=1;i<6;i++){
        printf("Доч. поток %d\n",i);}
    return NULL;
}


int main(){
    pthread_t thread;
    pthread_create(&thread, NULL,function,NULL);
    for (int i=1;i<6;i++){
        printf("Род. поток %d\n",i);}
}
```
![image](https://github.com/user-attachments/assets/5693a247-cb5a-424b-9f42-8d095dc04d87)


2.	Ожидание потока

Модифицировать упр.1 так, что родительский поток выводит текст после завершения дочернего потока. Подсказка: pthread_join()
```c
#include <stdio.h>
#include <pthread.h>

void *function(void *_){
    for (int i=1;i<6;i++){
        printf("Доч. поток %d\n",i);}
    return NULL;
}


int main(){
    pthread_t thread;
    pthread_create(&thread, NULL,function,NULL);
    for (int i=1;i<6;i++){
        printf("Род. поток %d\n",i);}
    pthread_join(thread, NULL);
}
```
![image](https://github.com/user-attachments/assets/744bbf3c-9746-4234-94db-1480fcb68fc2)


3.	Параметры потока

Модифицировать упр.2 так, что основной поток создает 4 потока, исполняющих одну и ту же функцию. Эта функция должна распечатать последовательность текстовых строк, переданных как параметр. Каждый из созданных потоков должен распечатать различные последовательности строк.
```c
#include <stdio.h>
#include <pthread.h>

void *function(void *_){
    char* message= (char*)_;
    for (int i=1;i<6;i++){
        printf(".поток %d  |  %s%d\n",i,message,i);}
    return NULL;
}


int main(){
    pthread_t thread[4];
    char* message[]={"qwerty1","qwerty2","qwerty3","qwerty4"};

    for (int i=0;i<4;i++){
        pthread_create(&thread[i], NULL,function,message[i]);
        pthread_join(thread[i], NULL);}
}
```
![image](https://github.com/user-attachments/assets/750846d6-0c53-425f-b2ec-90383204eedb)


4.	Завершение нити без ожидания

Добавить сон с помощью sleep() в функцию потоков между выводами строк. Спустя две секунды после создания дочерних потоков основной поток должен прервать работу всех дочерних потоков с помощью pthread_cancel().
```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *function(void *_){
    char* message= (char*)_;
    for (int i=1;i<6;i++){
        printf(".поток %d  |  %s%d\n",i,message,i);
        sleep(1);}
    return NULL;
}


int main(){
    pthread_t thread[4];
    char* message[]={"qwerty1","qwerty2","qwerty3","qwerty4"};

    for (int i=0;i<4;i++){
        pthread_create(&thread[i], NULL,function,message[i]);}

    sleep(2);

    for (int i=0;i<4;i++){
        pthread_cancel(thread[i]);}
}
```
![image](https://github.com/user-attachments/assets/99d3468a-3a2f-44cc-b6fd-a6c3a9d41597)


5.	Обработать завершение потока

Модифицировать упр. 4 так, чтобы дочерний поток перед завершение распечатывал сообщение об этом. Использовать pthread_cleanup_push()
```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void clean(void *_){
    char* message= (char*)_;
    printf("поток %s завершен\n",message);}

void *function(void *_){
    char* message= (char*)_;
    pthread_cleanup_push(clean,message);
    for (int i=1;i<6;i++){
        printf(".поток %d  |  %s%d\n",i,message,i);
        sleep(1);}
    pthread_cleanup_pop(0);
    return NULL;
}

int main(){
    pthread_t thread[4];
    char* message[]={"qwerty1","qwerty2","qwerty3","qwerty4"};

    for (int i=0;i<4;i++){
        pthread_create(&thread[i], NULL,function,message[i]);}

    sleep(2);

    for (int i=0;i<4;i++){
        pthread_cancel(thread[i]);}
    for (int i=0;i<4;i++){
        pthread_join(thread[i],NULL);}
}
```
![image](https://github.com/user-attachments/assets/251a62c7-7a65-4045-a356-c51ed22af3dd)


6. Реализовать простой Sleepsort

Реализовать прикольный алгоритм сортировки Sleepsort с асимптотикой O(N) (по времени). Суть алгоритма: на вход подается массив, пусть будет не более 50 элементов и пусть будет состоять из целочисленных значений. Для каждого элемента массива создается отдельный поток, в который в качестве аргумента передается значение элемента. Сам поток должен уйти в сон с помощью sleep() или usleep() с параметром равным аргументу потока (значение элемента массива), а после вывести на экран значение.
```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *sleepsort(void *_){
    int qwerty=*(int*)_;
    sleep(qwerty);
    printf("поток со временем %d завершился\n",qwerty);
    return NULL;
}

int main(){
    int arr[]={1,9,3,5,10};
    int n = sizeof(arr)/sizeof(arr[0]);
    pthread_t thread[n];
    for (int i=0;i<n;i++){
        pthread_create(&thread[i],NULL,sleepsort, &arr[i]);
    }
    for (int i=0;i<n;i++){
        pthread_join(thread[i],NULL);
    }
}
```
![image](https://github.com/user-attachments/assets/44e430ab-ae43-4ffe-a9f1-6d944653e649)


### **Оценка 4. Перемножение матриц:**

7.	Синхронизированный вывод

Модифицируйте программу упр. 5 так, чтобы вывод родительского и дочернего потока был синхронизован: сначала родительский поток выводить первую строку, затем дочерний, затем родительский вторую строку и т.д. Использовать mutex. 

```c
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int turn = 0;

void* child_thread(void* _) {
    for (int i=1;i<6;i++) {
        while (1){
            pthread_mutex_lock(&mutex);
            if (turn==1) break;
            pthread_mutex_unlock(&mutex);}

        printf("Дочер. поток: %d\n", i);
        turn=0;
        pthread_mutex_unlock(&mutex);}
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid,NULL,child_thread,NULL);

    for (int i=1;i<6;i++) {
        while (1) {
            pthread_mutex_lock(&mutex);
            if (turn== 0) break;
            pthread_mutex_unlock(&mutex);}

        printf("Главн. поток: %d\n", i);
        turn=1;
        pthread_mutex_unlock(&mutex);}

    pthread_join(tid, NULL);
    pthread_mutex_destroy(&mutex);
}
```
![image](https://github.com/user-attachments/assets/b3a289ff-d22d-4695-93ab-edfe29eab38c)


8.	Перемножение квадратных матриц NxN

a.	Написать функцию произведения двух квадратных матриц A и B размером NxN (на выходе получим матрицу C). Исходные матрицы A и B заполнить единицами в основном потоке с функцией main. Для матриц размером меньше 5 в основном потоке вывести на экран матрицы A, B и C (для проверки правильности работы функции).
b.	С командной строки считать размер матрицы и количество потоков. Распараллелить перемножение матриц разбив матрицу на равные части между потоками в главной функции по следующему принципу: N / threads, например если размер матрицы N = 8, а потоков 4, то каждый из потоков заберет вычисление N/4 = 2 строки и столбца.

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int THREADS,N,**A,**B,**C;

void* umnozhenie(void* _) {
    int thread_id=*(int*)_;
    int stroki=N/THREADS;
    int start=thread_id*stroki;
    int end=start+stroki;
    
    for (int i=start;i<end;i++) {
        for (int j=0;j<N;j++) {
            C[i][j]= 0;
            for (int k= 0; k<N;k++) {
                C[i][j]+=A[i][k]*B[k][j];}}}
}

int main(int argc, char* argv[]){

    N=atoi(argv[1]);
    THREADS=atoi(argv[2]);


    A=(int**)malloc(N*sizeof(int*));
    B=(int**)malloc(N*sizeof(int*));
    C=(int**)malloc(N*sizeof(int*));
    for (int i = 0; i < N; i++) {
        A[i] = (int*)malloc(N * sizeof(int));
        B[i] = (int*)malloc(N * sizeof(int));
        C[i] = (int*)malloc(N * sizeof(int));}

    for (int i=0;i<N;i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = 1;
            B[i][j] = 1;
        }
    }

    pthread_t threads[THREADS];
    int thread_ids[THREADS];
    for (int i=0;i<THREADS;i++) {
        thread_ids[i] =i;
        pthread_create(&threads[i], NULL, umnozhenie, &thread_ids[i]);}

    for (int i=0;i<THREADS;i++) {
        pthread_join(threads[i], NULL);}

    printf("Результат:\n");
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            printf("%d ",C[i][j]);
        }
    printf("\n");}

    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);free(B);free(C);
}
```

![image](https://github.com/user-attachments/assets/b8d5eeed-b54e-4dbd-9566-1241ec69e3c9)


9.	Время выполнения

Замерить время выполнения с момента создания потоков (до цикла с pthread_create) и до завершения работы потоков (после цикла pthread_join). Позапускать с разным числом потоков и размером матрицы. Построить график в любой программе (excel, python, matlab и т.д.) или онлайн, который покажет зависимость времени выполнения от размера матрицы и количества потоков. Количество потоков от 1 до 128 с любым разумным шагом. Размер матрицы не более 2500, шаг размера матрицы на свое усмотрение.

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>


int THREADS,N,**A,**B,**C;
void* umnozhenie(void* _) {
    int thread_id=*(int*)_;
    int stroki=N/THREADS;
    int start=thread_id*stroki;
    int end=start+stroki;
    
    for (int i=start;i<end;i++) {
        for (int j=0;j<N;j++) {
            C[i][j]= 0;
            for (int k= 0; k<N;k++) {
                C[i][j]+=A[i][k]*B[k][j];}}}
}

int main(int argc, char* argv[]){
    N=atoi(argv[1]);
    THREADS=atoi(argv[2]);


    A=(int**)malloc(N*sizeof(int*));
    B=(int**)malloc(N*sizeof(int*));
    C=(int**)malloc(N*sizeof(int*));
    for (int i = 0; i < N; i++) {
        A[i] = (int*)malloc(N * sizeof(int));
        B[i] = (int*)malloc(N * sizeof(int));
        C[i] = (int*)malloc(N * sizeof(int));}

    for (int i=0;i<N;i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = 1;
            B[i][j] = 1;
        }
    }
    

    pthread_t threads[THREADS];
    int thread_ids[THREADS];
    struct timeval start, end;
    gettimeofday(&start,NULL);

    for (int i=0;i<THREADS;i++) {
        thread_ids[i] =i;
        pthread_create(&threads[i], NULL, umnozhenie, &thread_ids[i]);}

    for (int i=0;i<THREADS;i++) {
        pthread_join(threads[i], NULL);}

    gettimeofday(&end,NULL);
    double time=(end.tv_sec-start.tv_sec)+(end.tv_usec-start.tv_usec)/1e6;
    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);free(B);free(C);
    printf("%f",time);
}
```
```py
import matplotlib.pyplot as plt

x=[0, 16, 256, 1000, 1700,2500]
y1=[0, 0.000305, 0.082239, 5.490029, 34.863328,158.239867,]
y2=[0,0.000400,0.042056,2.528819,15.982726,75.219546]
y3=[0,0.000564,0.048222,1.230541,4.469586,19.826122]
y4=[0,0.001988,0.043858,1.042493,3.284425,14.604082]
y5=[0,0.013242,0.046186,0.994964,3.094185,14.312091]
fig, ax = plt.subplots()

ax.plot(x, y1, label='1')

ax.plot(x, y2, label='2')
ax.plot(x, y3, label='8')
ax.plot(x, y4, label='32')
ax.plot(x, y5, label='128')

ax.legend()
plt.show()
```
![{BD41456A-DA8D-444F-9EBE-34377878DCCD}](https://github.com/user-attachments/assets/fd847b00-6f21-4c1c-8a57-108afc2de211)


