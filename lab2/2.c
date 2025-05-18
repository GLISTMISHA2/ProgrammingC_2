#include <stdio.h>
#include <stdlib.h>
struct node {// создаем узел с указателем на предыдущий узел, данные и следующий узел
    struct node *prev;
    int data;
    struct node *next;
};

typedef struct node node_t;// сокращаем

node_t *newNode(int data){
    node_t *new_node = (node_t *)malloc(sizeof(node_t));// выделяем память для нового узла
    new_node->prev = NULL;
    new_node->data = data;
    new_node->next = NULL;// все на нул потомуто узел еще не связан с остальными
    return new_node;
}

void printList(node_t *head){
    node_t *cur = head;//начинаем с головы
    while (cur){// пока не равно нул
        printf("%d ",cur->data);// печатаем нынешний
        cur = cur->next;// переходим на следующий узел
    }
    printf("\n");
}
node_t* appendBack(node_t* head,int data){// добавляем новый элемент в конец 
    node_t* new_node = newNode(data);
    
    if (head == NULL) return new_node;// если нет начала создаем новый узел

    node_t *cur = head;
    while (cur->next != NULL) cur = cur->next;
    
    cur->next = new_node;
    new_node->prev = cur; // связываем с предыдущим
    return head;
}
node_t* createList(){
    node_t* head = NULL; // начинаем с пустого списка
    while (1){
        int n;
        scanf("%d",&n);
        if(n != 0) head = appendBack(head,n);// если не 0 - добавляем в список
        else break;
    }
    return head;
}
void LinkLists(node_t* head1, node_t* head2){
    while (head1 != NULL && head2 != NULL){// пока оба списка не закончились
        head1->prev = head2;//Связываем текущий узел первого списка с текущим узлом второго
        head1 = head1->next;// Переходим к следующему узлу в первом списке
        head2 = head2->next;// Переходим к следующему узлу во втором списке
    }
    while (head1 != NULL) {// обрезаем список. если первый список длинее
        head1->next = NULL;
        head1 = head1->next;
    }
}
void NaViList(node_t* S){
    node_t* cur = S;
    char input,choice;
    int t = 1;
    while (t != 0) {
        printf("Текукщий элемент %d\n",cur->data);
        printf("S - вниз D - Вправо 0 - Для выхода\n");
        scanf(" %c", &input);

        if (input == '0') break;// выход если 0
        switch (input) {
            case 'D': // движение вправо 
                if (cur->next) {//если есть следующий узел
                    cur = cur->next;// переходим к нему
                } else {
                    printf("Достигнут конец списка. Вернуться в начало? Y/N\n");
                    scanf(" %c", &choice);
                    if (choice == 'Y') cur = S;  
                    else t = 0;
                }
                break;
            case 'S':// вниз 
                if (cur->prev) cur = cur->prev; // переходим к предыдущенму
                break;
        }
    }
}
int main() {
    node_t* list_1 = createList();
    node_t* list_2 = createList();
    node_t* head1 = list_1;
    node_t* head2 = list_2;
    LinkLists(head1, head2);

    printList(list_1);
    printList(list_2);

    node_t* S = head1; // начинаем навигацию с головы первого списка
    NaViList(S); // проводим навигацию
}
