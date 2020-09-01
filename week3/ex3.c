#include <stdio.h> 
#include <stdlib.h>

struct Node {
    int value;
    struct Node* nextNode;
};

struct Node* construct_node(int value) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->nextNode = NULL;
    return newNode;
}

void print_list(struct Node* list) {
    struct Node* curNode = list;
    while (curNode != NULL) {
        printf("%d", curNode->value);
        curNode = curNode->nextNode;
        if (curNode != NULL) {
            printf(", ");
        }
    }
    printf("\n");
}

void insert_node(struct Node** list, int index, int insertValue) {
    if (list == NULL) {
        // in case if it's the first element, just place it as an initial node
        if (index != 0) {
            // if index doesn't match, do nothing
            return;
        }
        // create the node and put it in place
        struct Node* newNode = construct_node(insertValue);
        *list = newNode;
    }
    else {
        // find place at which to put the new node
        struct Node* curNode = *list;
        struct Node* prevNode;
        int curIndex = 0;
        if (index == 0) {
            struct Node* newNode = construct_node(insertValue);
                newNode->nextNode = curNode;
            *list = newNode;
        }
        else {
            while (curNode != NULL && curIndex < index) {
                prevNode = curNode;
                curNode = curNode->nextNode;
                curIndex++;
            }
            // create the node and put it in place if we actually found the needed node
            if (curIndex == index) {
                struct Node* newNode = construct_node(insertValue);
                newNode->nextNode = curNode;
                prevNode->nextNode = newNode;
            }
        }
    }
}

void delete_node(struct Node** list, int deleteIndex) {
    if (*list == NULL) {
        return;
    }
    if (deleteIndex == 0) {
        *list = (*list)->nextNode;
        return;
    }

    // find the node to delete
    struct Node* curNode = *list;
    struct Node* prevNode;
    int curIndex = 0;
    while (curNode->nextNode != NULL && curIndex < deleteIndex) {
        prevNode = curNode;
        curNode = curNode->nextNode;
        curIndex++;
    }
    // if we actually found the needed node, delete it
    if (curIndex == deleteIndex) {
        prevNode->nextNode = curNode->nextNode;
    }
}

int main() {
    struct Node* list = NULL;
    
    for (int i = 0; i < 9; i++) {
        printf("insert %d at index %d:\n", i+2, i);
        insert_node(&list, i, i+2);
        print_list(list);
        printf("\n");
    }

    printf("insert %d at index %d:\n", 123, 0);
    insert_node(&list, 0, 123);
    print_list(list);
    printf("\n");

    printf("insert %d at index %d:\n", 1337, 3);
    insert_node(&list, 3, 1337);
    print_list(list);
    printf("\n");

    printf("delete node with index %d:\n", 9);
    delete_node(&list, 9);
    print_list(list);
    printf("\n");

    printf("delete node with index %d:\n", 0);
    delete_node(&list, 0);
    print_list(list);
    printf("\n");

    printf("delete node with index %d:\n", 3);
    delete_node(&list, 3);
    print_list(list);
    printf("\n");
    return 0;
}