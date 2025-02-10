#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Float linked list implementation in C.
Warning: All functions that take the linked list assumes that its not null and correctly initialized.
 */

typedef struct node {
    struct node* next;
    float value;
} Node;

typedef struct {
    Node* head;
} LinkedList;

LinkedList create_list() {
    LinkedList list = { 0 };
    return list;
}
// Creates a linked list from an array
LinkedList create_list_from_arr(float* arr, size_t count) {
    LinkedList list;
    if(count < 1) {
        return list;
    }
    Node* current = malloc(sizeof(Node));
    assert(current);
    list.head = current;
    list.head->value = arr[0];
    for(size_t i = 1; i < count; i++) {
        // Uses calloc to initialize the "next" field to NULL.
        Node* next = calloc(1, sizeof(Node));
        // Make sure calloc works.
        assert(next);
        next->value = arr[i];
        current->next = next;
        current = next;
    }
    return list;
}
void insert_head(LinkedList* list, float value) {
    Node* head = malloc(sizeof(Node));
    assert(head);
    head->value = value;
    Node* temporary = list->head;
    list->head = head;
    head->next = temporary;
}
// Insert the value as the new tail of the linked list
Node* insert_tail(LinkedList* list, float value) {
    if(!list->head) {
        // If the list is empty, adding the tail is the same as adding a new head.
        insert_head(list, value);
        return list->head;
    }
    Node* tail = calloc(1, sizeof(Node));
    assert(tail);
    Node* current = list->head;
    while(current->next) {
        current = current->next;
    }
    current->next = tail;
    return tail;
}
// Finds the node with the given value
Node* find_node(LinkedList* list, float value) {
    Node* current = list->head;
    while(current) {
        if(current->value == value) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
typedef bool(LinkedListFilterFunc)(Node* node, void* data);
// Free element from the linked list that match the given function and return the number of elements filtered.
size_t filter(LinkedList* list, LinkedListFilterFunc func, void* data) {
    size_t filtered = 0;
    if(!list->head) {
        return;
    }
    Node placeholder = { 0 };
    placeholder.next = list->head;
    Node* previous = &placeholder;
    Node* current = previous->next;
    while(current) {
        if(func(current, data)) {
            filtered++;
            previous->next = current->next;
            Node* temporary = current;
            current = current->next;
            free(temporary);
            continue;
        }
        current = current->next;
    }
    return filtered;
}
size_t list_item_count(LinkedList* list) {
    size_t count = 0;
    Node* current = list->head;
    while(current) {
        count++;
        current = current->next;
    }
    return count;
}
void free_list(LinkedList* list) {
    Node* current = list->head;
    while(current) {
        Node* temporary = current;
        current = current->next;
        free(temporary);
    }
    list->head = NULL;
}
void print_list(LinkedList* list) {
    printf("Linked List");
    Node* current = list->head;
    while(current) {
        printf("->%.3f", current->value);
        current = current->next;
    }
    printf("\n");
    return;
}