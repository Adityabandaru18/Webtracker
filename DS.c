#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char data[100];
    struct Node* next;
};

struct Node* createNode(char* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->data,data);
    newNode->next=NULL;
    return newNode;
}

void addPage(struct Node** head, char* page) {
    struct Node* newNode = createNode(page);
    if (newNode != NULL) {
        newNode->next = *head;
        *head = newNode;
        printf("Page '%s' added to the history.\n", page);       //Insertion at the Beginning
    }
}

void removePage(struct Node** head, char* page) {
    struct Node* current = *head;
    struct Node* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->data, page) == 0) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                *head = current->next;
            }

            printf("Page '%s' removed from the history.\n", page);

            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("Page '%s' not found in the history.\n", page);
}

void displayHistory(struct Node* head) {
    struct Node* current = head;
    if(current!=NULL){

    printf("Web Page History:\n\n");
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
    printf("\n");
    }
    else{
        printf("Web page history is NULL\n");
    }
}

void freeHistory(struct Node** head) {
    struct Node* current = *head;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

int main() {
    struct Node* webHistory = NULL;
    int choice;
    char page[100];
    do {
        printf("-----Menu------\n");
        printf("1. Add Page\n");
        printf("2. Remove Page\n");
        printf("3. Display History\n");
        printf("4. Exit the code\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character left in the input buffer
        switch (choice) {
            case 1:
                printf("Enter the URL to add: ");
                fgets(page, sizeof(page), stdin);  //Reads character until newline is encountered
                page[strcspn(page, "\n")] = '\0'; // Remove the trailing newline character
                addPage(&webHistory, page);   //Taking address of pointer so we use double pointer **
                break;
            case 2:
                printf("Enter the URL to remove: ");
                fgets(page, sizeof(page), stdin);
                page[strcspn(page, "\n")] = '\0'; // Remove the trailing newline character
                removePage(&webHistory, page);
                break;
            case 3:
                displayHistory(webHistory);
                break;
            case 4:
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    } while (choice != 4);
    printf("Thank you!");
    freeHistory(&webHistory);
}