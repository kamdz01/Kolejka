#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <Windows.h>

#define MAX_CNT 10

typedef struct {
    char name[256];
    int age;
}Person;


typedef struct node{
    Person entry;
    node* next;
}Node;



typedef struct {
    Node* first;
    Node* last;
    int cnt;
}Queue;



void Queue_init(Queue* queue);
int Queue_is_full(Queue* queue);
int Queue_is_empty(Queue* queue);
int Queue_quantity(Queue* queue);
void Queue_print(Queue* queue);
void Queue_add_node(Queue* queue, Person* person);
void Queue_delete_node(Queue* queue);
void Queue_delete(Queue* queue);
void print_menu(Queue* queue);
void Queue_start();
