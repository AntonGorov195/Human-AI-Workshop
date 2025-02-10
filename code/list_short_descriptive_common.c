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