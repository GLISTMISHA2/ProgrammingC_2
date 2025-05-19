Практическое задание 7. Знакомство с POSIX потоками
Оценка 3. Знакомство с pthread:
Создать поток
Написать программу, которая создает поток с помощью pthread_create(). Использовать атрибуты по умолчанию. Родительский и дочерний потоки должны вывести на экран по 5 строк текста.
#include <stdio.h>
#include <pthread.h>

void *function(void *_) {
    for (int i=1;i<6;i++) {
        printf("Доч. поток %d\n",i);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, function, NULL);
    
    for (int i =1; i<6; i++) {
        printf("Род. поток %d\n",i);
    }
    pthread_join(thread, NULL);
    
}
![image](https://github.com/user-attachments/assets/c7a9bdc1-f44d-456a-a2b0-985196f5b60f)
Ожидание потока
Модифицировать упр.1 так, что родительский поток выводит текст после завершения дочернего потока. Подсказка: pthread_join()
#include <stdio.h>
#include <pthread.h>

void *function(void *_) {
    for (int i = 1; i < 6; i++) {
        printf("Доч. поток %d\n", i);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, function, NULL);
    
    pthread_join(thread, NULL);
    for (int i = 1; i < 6; i++) {
        printf("Род. поток %d\n", i);
    }
    
    return 0;
}
![image](https://github.com/user-attachments/assets/be4b0d7d-0255-4fdf-b77c-f4c9919ca6e8)
Параметры потока
Модифицировать упр.2 так, что основной поток создает 4 потока, исполняющих одну и ту же функцию. Эта функция должна распечатать последовательность текстовых строк, переданных как параметр. Каждый из созданных потоков должен распечатать различные последовательности строк.

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
![image](https://github.com/user-attachments/assets/c8066e4d-4c84-41c2-a58d-0e3445111670)
Завершение нити без ожидания
Добавить сон с помощью sleep() в функцию потоков между выводами строк. Спустя две секунды после создания дочерних потоков основной поток должен прервать работу всех дочерних потоков с помощью pthread_cancel().

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
![image](https://github.com/user-attachments/assets/51c7b67a-bdd5-465e-be81-8c662dbeebeb)
Обработать завершение потока
Модифицировать упр. 4 так, чтобы дочерний поток перед завершение распечатывал сообщение об этом. Использовать pthread_cleanup_push()

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
![image](https://github.com/user-attachments/assets/2313dfb2-ec94-4d52-a828-7ada29dbbc40)
Реализовать простой Sleepsort
Реализовать прикольный алгоритм сортировки Sleepsort с асимптотикой O(N) (по времени). Суть алгоритма: на вход подается массив, пусть будет не более 50 элементов и пусть будет состоять из целочисленных значений. Для каждого элемента массива создается отдельный поток, в который в качестве аргумента передается значение элемента. Сам поток должен уйти в сон с помощью sleep() или usleep() с параметром равным аргументу потока (значение элемента массива), а после вывести на экран значение.

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
![image](https://github.com/user-attachments/assets/1a711c24-8d3c-4ceb-8e2a-a22697ccc832)
Оценка 4. Перемножение матриц:
Синхронизированный вывод
Модифицируйте программу упр. 5 так, чтобы вывод родительского и дочернего потока был синхронизован: сначала родительский поток выводить первую строку, затем дочерний, затем родительский вторую строку и т.д. Использовать mutex.

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
![image](https://github.com/user-attachments/assets/157ed3ac-105c-47dd-b36d-a5dde8a928fa)
Перемножение квадратных матриц NxN
a. Написать функцию произведения двух квадратных матриц A и B размером NxN (на выходе получим матрицу C). Исходные матрицы A и B заполнить единицами в основном потоке с функцией main. Для матриц размером меньше 5 в основном потоке вывести на экран матрицы A, B и C (для проверки правильности работы функции). b. С командной строки считать размер матрицы и количество потоков. Распараллелить перемножение матриц разбив матрицу на равные части между потоками в главной функции по следующему принципу: N / threads, например если размер матрицы N = 8, а потоков 4, то каждый из потоков заберет вычисление N/4 = 2 строки и столбца.

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
![image](https://github.com/user-attachments/assets/9194cdc3-fb3b-4380-8312-3c1a3614dd94)
Время выполнения
Замерить время выполнения с момента создания потоков (до цикла с pthread_create) и до завершения работы потоков (после цикла pthread_join). Позапускать с разным числом потоков и размером матрицы. Построить график в любой программе (excel, python, matlab и т.д.) или онлайн, который покажет зависимость времени выполнения от размера матрицы и количества потоков. Количество потоков от 1 до 128 с любым разумным шагом. Размер матрицы не более 2500, шаг размера матрицы на свое усмотрение.

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
Время выполнения
Замерить время выполнения с момента создания потоков (до цикла с pthread_create) и до завершения работы потоков (после цикла pthread_join). Позапускать с разным числом потоков и размером матрицы. Построить график в любой программе (excel, python, matlab и т.д.) или онлайн, который покажет зависимость времени выполнения от размера матрицы и количества потоков. Количество потоков от 1 до 128 с любым разумным шагом. Размер матрицы не более 2500, шаг размера матрицы на свое усмотрение.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <math.h>

int THREADS, N;
int **A, **B, **C;

void* matrix_mult(void* arg) {
    int thread_id = *(int*)arg;
    int rows_per_thread = N / THREADS;
    int extra_rows = N % THREADS;
    
    int start_row = thread_id * rows_per_thread + (thread_id < extra_rows ? thread_id : extra_rows);
    int end_row = start_row + rows_per_thread + (thread_id < extra_rows ? 1 : 0);
    
    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return NULL;
}

void init_matrices() {
    A = (int**)malloc(N * sizeof(int*));
    B = (int**)malloc(N * sizeof(int*));
    C = (int**)malloc(N * sizeof(int*));
    
    for (int i = 0; i < N; i++) {
        A[i] = (int*)malloc(N * sizeof(int));
        B[i] =  (int*)malloc(N * sizeof(int));
        C[i] = (int*)malloc(N * sizeof(int));
        
        for (int j = 0; j < N; j++) {
            A[i][j] = 1;
            B[i][j] = 1;
        }
    }
}

void free_matrices() {
    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
}

double run_experiment(int n, int threads) {
    N = n;
    THREADS = threads;
    
    init_matrices();
    
    pthread_t *threads_arr = (pthread_t*)malloc(threads * sizeof(pthread_t));
    int *thread_ids = (int*)malloc(threads * sizeof(int));
    
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    for (int i = 0; i < threads; i++) {
        thread_ids[i] = i;
        pthread_create(&threads_arr[i], NULL, matrix_mult, &thread_ids[i]);
    }
    
    for (int i = 0; i < threads; i++) {
        pthread_join(threads_arr[i], NULL);
    }
    
    gettimeofday(&end, NULL);
    
    free(threads_arr);
    free(thread_ids);
    free_matrices();
    
    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
}

int main() {
    // Тестируем разные размеры матриц и количество потоков
    int matrix_sizes[] = {100, 500, 1000, 1500, 2000, 2500};
    int thread_counts[] = {1, 2, 4, 8, 16, 32, 64, 128};
    
    printf("Matrix Size,Threads,Time (s)\n");
    
    for (int i = 0; i < sizeof(matrix_sizes)/sizeof(int); i++) {
        for (int j = 0; j < sizeof(thread_counts)/sizeof(int); j++) {
            double time = run_experiment(matrix_sizes[i], thread_counts[j]);
            printf("%d,%d,%.4f\n", matrix_sizes[i], thread_counts[j], time);
        }
    }
    
    return 0;
}
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
![image](https://github.com/user-attachments/assets/70ec22b6-e942-4fc5-83e7-b0b50cf15b8c)

