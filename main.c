#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    void *next;
    int data;
} Node;

Node *head = NULL;

// add a node
Node *addNode(int data)
{
    Node *newNode = NULL;

    // if head == null, this is a new node
    if (head == NULL)
    {
        newNode = malloc(sizeof(Node));

        // there might be issues with the malloc operation
        if (newNode == NULL)
            return NULL;

        newNode->data = data;
        head = newNode;
        newNode->next = NULL;
    }
    else
    {
        // else make new node
        newNode = malloc(sizeof(Node));

        // there might be issues with the malloc operation
        if (newNode == NULL)
            return NULL;

        newNode->data = data;
        // point node to head
        newNode->next = head;
        // point head to new node
        head = newNode;
    }

    return newNode;
}

// remove a node from list
int removeNode(int data)
{
    Node *current = head;
    Node *prev = head;
    while (current != NULL)
    {
        if (current->data == data)
        {
            // if current node is the list head
            if (current == head)
            {
                head = current->next;
            }
            else
            {
                // take previous
                prev->next = current->next;
                free(current);
                current = NULL;
            }
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

// insert a node into a position into the list
int insertNode(int data, int pos)
{
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL)
        return 0;

    newNode->data = data;

    if (pos == 0)
    {
        newNode->next = head;
        head = newNode;
        return 1;
    }

    Node *current = head;
    int current_pos = 0;
    while (current != NULL && current_pos < pos - 1)
    {
        current = current->next;
        current_pos++;
    }
    if (current == NULL)
    {
        // pos not valid
        free(newNode);
        return 0;
    }

    // at the desired position
    newNode->next = current->next; // point newNode.next to prev.next (always to the new node first)
    current->next = newNode;       // point prev to newNode,
    return 1;

    return 0;
}

// print
void printList()
{
    Node *current = head;
    printf("(%d)->", current->data);
    current = current->next;
    while (current != NULL)
    {
        printf("%d->", current->data);
        current = current->next;
    }

    printf("\n");
    return;
}

void printMenu()
{
    printf("you have the following options:\n");
    printf("\t1. Add a node to the list.\n");
    printf("\t2. Remove a node from the list.\n");
    printf("\t3. Insert a node to the list.\n");
    printf("\t4. Print your list.\n");
    printf("\t5. Quit.\n");
}

int main(int argc, char **argv)
{
    int option = -1;
    int data;
    int pos;
    while (option != 5)
    {
        printMenu();
        int num_received = scanf("%d", &option);
        if (num_received == 1 && option > 0 && option <= 5)
        {
            switch (option)
            {
            case 1:
                printf("What data should i insert?:\n");
                scanf("%d", &data);
                Node *new = addNode(data);
                printList();
                break;
            case 2:
                printf("What data should i remove?:\n");
                printList();
                scanf("%d", &data);
                int success = removeNode(data);
                if (success)
                    printList();
                if (!success)
                    printf("Element not found!\n");
                break;
            case 3:
                printf("What data should i insert?:\n");
                scanf("%d", &data);
                printf("Where should i insert it?\n");
                scanf("%d", &pos);
                int insert_success = insertNode(data, pos);
                if (insert_success)
                    printList();
                if (!insert_success)
                    printf("Insert failed!\n");
                // insert
                break;
            case 4:
                printList();
                break;
            case 5:
                break;
            }
        }
    }
    printf("End.");
    return 0;
}