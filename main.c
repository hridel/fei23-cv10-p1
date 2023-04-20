#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct person {
    char name[50];
    int age;
} Person;

typedef struct abstract_element {
    void *data;
    struct abstract_element *next;
} AbstractElement;

AbstractElement *allocate_memory() {
    AbstractElement *element = (AbstractElement *) malloc(sizeof(AbstractElement));
    if (element == NULL) {
        printf("Chyba pri alokovani pameti\n");
        exit(1);
    }
    return element;
}

void read_person(AbstractElement *element) {
    element->data = (void *) malloc(sizeof(Person));
    if (element->data == NULL) {
        printf("Chyba pri alokovani pameti\n");
        exit(1);
    }

    printf("Zadej jmeno: ");
    scanf("%s", ((Person *) element->data)->name);

    printf("Zadej vek: ");
    scanf("%d", &((Person *) element->data)->age);
}

AbstractElement *find_oldest(AbstractElement *head) {
    AbstractElement *oldest = head;
    AbstractElement *current = head->next;

    while (current != NULL) {
        if (((Person *) current->data)->age > ((Person *) oldest->data)->age) {
            oldest = current;
        }
        current = current->next;
    }

    return oldest;
}

AbstractElement *find_youngest(AbstractElement *head) {
    AbstractElement *youngest = head;
    AbstractElement *current = head->next;

    while (current != NULL) {
        if (((Person *) current->data)->age < ((Person *) youngest->data)->age) {
            youngest = current;
        }
        current = current->next;
    }

    return youngest;
}

void free_memory(AbstractElement *head) {
    AbstractElement *current = head;

    while (current != NULL) {
        AbstractElement *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

int main() {
    AbstractElement *head = NULL;
    AbstractElement *current = NULL;

    int count;
    printf("Zadej pocet osob: ");
    scanf("%d", &count);

    // Pridani osob do seznamu
    for (int i = 0; i < count; i++) {
        AbstractElement *element = allocate_memory();
        read_person(element);
        element->next = NULL;

        if (head == NULL) {
            head = element;
        } else {
            current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = element;
        }
    }

    // Vyhledani nejstarsi a nejmladsi osoby
    AbstractElement *oldest = find_oldest(head);
    AbstractElement *youngest = find_youngest(head);

    // Vypsani vysledku
    printf("Nejstarsi osoba je: %s (%d let)\n", ((Person *) oldest->data)->name, ((Person *) oldest->data)->age);
    printf("Nejmladsi osoba je: %s (%d let)\n", ((Person *) youngest->data)->name, ((Person *) youngest->data)->age);

    // Uvolneni pameti
    free_memory(head);

    return 0;
}
