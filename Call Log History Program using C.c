#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#define MAX 50
struct node {
    long data;
    char name[MAX];
    struct node *next;
    struct node *prev;
    time_t t;
};
struct node *head = NULL;
struct node *tail = NULL;

void dial_new_call() {
    long n;
    time_t tm;
    printf("Enter a phone number to call: ");
    scanf("%ld", &n);
    tm = time(NULL); 
    if (head != NULL) {
        struct node *ptr;
        ptr = tail;
        while (ptr != NULL && ptr->data != n) {
            ptr = ptr->prev;
        }
        if (ptr != NULL) {
            if (ptr->prev != NULL) {
                ptr->prev->next = ptr->next;
            }
            if (ptr->next != NULL) {
                ptr->next->prev = ptr->prev;
            }
            free(ptr);
        }
    }
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    if (head == NULL) {
        head = temp;
        head->data = n;
        strcpy(head->name, "");
        head->prev = NULL;
        head->next = NULL;
        head->t = tm; 
        tail = head;
    } else {
        tail->next = temp;
        temp->data = n;
        strcpy(temp->name, "");
        temp->prev = tail;
        temp->next = NULL;
        temp->t = tm; 
        tail = temp;
    }
}
void dial_from_contacts() {
    char n[MAX];
    time_t tm;
    printf("Enter a contact name to call: ");
    scanf("%s", n);
    tm = time(NULL); 
    struct node *ptr = tail;
    while (ptr != NULL && strcmp(ptr->name, n) != 0) {
        ptr = ptr->prev;
    }
    if (ptr != NULL) {
        if (ptr->prev != NULL) {
            ptr->prev->next = ptr->next;
        }
        if (ptr->next != NULL) {
            ptr->next->prev = ptr->prev;
        }
        free(ptr);
    }
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    strcpy(temp->name, n);
    if (head == NULL) {
        head = temp;
        head->data = 0;
        head->prev = NULL;
        head->next = NULL;
        head->t = tm; 
        tail = head;
    } else {
        tail->next = temp;
        temp->prev = tail;
        temp->data = 0;
        temp->next = NULL;
        temp->t = tm; 
        tail = temp;
    }
}
void recent_call() {
    if (tail != NULL) {
        if (tail->data != 0) {
            printf("The latest phone number you dialed is: \n%ld \t %s", tail->data, ctime(&(tail->t)));
        } else {
            printf("The latest contact you dialed is: \n%s \t %s", tail->name, ctime(&(tail->t)));
        }
    } else {
        printf("No recent calls.\n");
    }
}
void display_call_history() {
    struct node *temp;
    temp = tail;
    printf("Your recently dialed phone numbers are: \n");
    while (temp != NULL) {
        if (temp->data != 0) {
            printf("%ld \t %s", temp->data, ctime(&(temp->t)));
        } else {
            printf("%s \t %s", temp->name, ctime(&(temp->t)));
        }
        temp = temp->prev;
    }
}
int main() {
    int choice;
    printf("--------------------------------------------------------------------------------------\n");
    printf("CALL LOG HISTORY PROGRAM USING THE CONCEPT OF DOUBLY LINKED LIST AND STACKS\n");
    printf("                      BY TARLANA VIDYA 23MIA1176\n");
    printf("--------------------------------------------------------------------------------------\n");
    printf("1. For dialing the phone number of your wish.\n");
    printf("2. For dialing a number from the contact list.\n");
    printf("3. For viewing the most recent phone number you dialed.\n");
    printf("4. For viewing the phone numbers you dialed.\n");
    printf("5. Exit.\n");
    printf("--------------------------------------------------------------------------------------\n");
    while (1) {
        printf("Enter the choice of your wish: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                dial_new_call();
                printf("--------------------------------------------------------------------------------------\n");
                break;
            case 2:
                dial_from_contacts();
                printf("--------------------------------------------------------------------------------------\n");
                break;
            case 3:
                recent_call();
                printf("--------------------------------------------------------------------------------------\n");
                break;
            case 4:
                display_call_history();
                printf("--------------------------------------------------------------------------------------\n");
                break;
            case 5:
                exit(0);
            default:
                printf("You chose an invalid choice\n");
        }
    }
    return 0;
}