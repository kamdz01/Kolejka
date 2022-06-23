#include "lib.h"


//#define FUNC_OUT


void Queue_init(Queue* queue)
{
    queue->cnt = 0;
    queue->first = nullptr;
    queue->last = nullptr;
}

int Queue_is_full(Queue* queue)
{
    if (queue->cnt >= MAX_CNT)
    {
#ifdef FUNC_OUT
        printf("Kolejka pelna :(\n");
#endif // FUNC_OUT

        return 0;
    }
#ifdef FUNC_OUT
    printf("W kolejce jest jeszcze miejsce :)\n");
#endif // FUNC_OUT
    return 1;
}
int Queue_is_empty(Queue* queue)
{
    if (queue->cnt > 0)
    {
#ifdef FUNC_OUT
        printf("W kolejce juz cos jest\n");
#endif // FUNC_OUT
        return 1;
    }
#ifdef FUNC_OUT
    printf("Kolejka pusta\n");
#endif // FUNC_OUT
    return 0;
}

int Queue_quantity(Queue* queue)
{
    return queue->cnt;
}

void Queue_print(Queue* queue) {
    if (!Queue_is_empty(queue))
    {
        printf("\nKolejka pusta\n");
        return;
    }
    int licznik = 1;
    printf("\nWyswietlam aktualna kolejke: \n");
    Node* cursor = queue->first;
    printf("%d. %s  %d lat\n", licznik, cursor->entry.name, cursor->entry.age);
    while (cursor->next != NULL) {
        licznik++;
        cursor = cursor->next;
        printf("%d. %s  %d lat\n", licznik, cursor->entry.name, cursor->entry.age);
    }
}

void Queue_add_node(Queue* queue, Person* person)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    if (!Queue_is_full(queue))
    {
        printf("\nBrak miejsca w kolejce - nie dodano osoby :( \n");
        return;
    }
    if (temp == nullptr)
    {
        printf("\nBlad alokowania pamieci\n");
        return;
    }
    temp->entry = *person;
    temp->next = nullptr;
    if (queue->first == nullptr)
    {
        queue->first = temp;
        queue->last = temp;
        queue->cnt++;
    }
    else
    {
        if (queue->cnt < MAX_CNT)
        {
            queue->last->next = temp;
            queue->last = temp;
            queue->cnt++;
        }
    }
#ifdef FUNC_OUT
    Queue_print(queue);
#endif // FUNC_OUT
}

void Queue_delete_node(Queue* queue)
{
    queue->cnt--;
    if (queue->cnt <= 0)
    {
        //queue->first = nullptr;
        //queue->last = nullptr;
        //queue->cnt = 0;
        Queue_init(queue);
#ifdef FUNC_OUT
        Queue_print(queue);
#endif // FUNC_OUT
        return;
    }
    Node* temp = queue->first->next;
    free(queue->first);
    queue->first = temp;
#ifdef FUNC_OUT
    Queue_print(queue);
#endif // FUNC_OUT
}

void Queue_delete(Queue* queue)
{
    while (queue->cnt > 0)
    {
        Queue_delete_node(queue);
    }
}

void print_menu(Queue* queue)
{
    int choice = 0;
    do
    {
        if (queue->cnt == 0)
        {
            printf("\nWitamy w sklepie komputerowym brzoskwinie.net. Masz szczescie - jestes pierwszym klientem i kolejka jest jeszcze pusta! Wybierz co chcesz z nia zrobic\n");
        }

        printf("\nCo chcesz zrobic z kolejka? Wybierz odpowiednia opcje z menu: \n1. Dodanie osoby do kolejki - wcisnij 1\n2. Usuniecie osoby z kolejki - wcisnij 2\n3. Wyswietlenie calej kolejki - wcisnij 3\n4. Sprawdzanie czy kolejka jest pusta - wcisnij 4\n5. Sprawdzanie czy kolejka jest pelna - wcisnij 5\n6. Usuwanie calej kolejki - 6\n7. Powrot do domu - wcisnij 7\n");
        scanf_s("%d", &choice);
        while (getchar() != '\n');

#ifdef WIN32
system("cls");
#else
printf("\\033[2J\\033[H");
#endif


        switch (choice)
        {
        case 0:
            printf("\nPodano bledne dane\n");
            
            break;
        case 1:
            if (!Queue_is_full(queue))
            {
                printf("\nBrak miejsca w kolejce - nie mo¿na dodaæ kolejnej osoby :( \n");
            }
            else
            {
                Person temp;
                printf("Podaj imie osoby dodawanej do kolejki: \n");
                scanf_s("%s", &temp.name, (unsigned int)sizeof(temp.name));
                while (getchar() != '\n');
                printf("Podaj wiek osoby dodawanej do kolejki: \n");
                scanf_s("%d", &temp.age);
                while (getchar() != '\n');
                if (temp.age <= 0)
                {
                    printf("Podano bledny wiek\n");
                }
                else
                {
                    Queue_add_node(queue, &temp);
                    printf("Poprawnie dodano osobe do kolejki\n");
                }
            }
            
            break;
        case 2:
            if (!Queue_is_empty(queue))
            {
                printf("\nKolejka jest pusta. Nie mozna nikogo usunac\n");
            }
            else
            {
                Queue_delete_node(queue);
                printf("\nPoprawnie usunieto osobe z kolejki\n");
            }
            
            break;
        case 3:
            Queue_print(queue);
            
            break;
        case 4:
            if (!Queue_is_empty(queue))
            {
                printf("\nKolejka jest pusta\n");
            }
            else
            {
                printf("\nKolejka nie jest pusta\n");
            }
            
            break;
        case 5:
            if (!Queue_is_full(queue))
            {
                printf("\nKolejka jest pelna\n");
            }
            else
            {
                printf("\nKolejka nie jest pelna\n");
            }
            
            break;
        case 6:
            Queue_delete(queue);
            printf("\nPoprawnie usunieto wszystkie osoby z kolejki\n");
            
            break;
        case 7:
            printf("\nKolejka jest dla ciebie za dluga. Wracasz do domu.\n");
            break;

        default:
            printf("\nPodano bledne dane\n");
            
            break;
        }
    } while (choice != 7);

}

void Queue_start()
{
    Queue queue;
    Queue_init(&queue);
    print_menu(&queue);
    Queue_delete(&queue);
}

