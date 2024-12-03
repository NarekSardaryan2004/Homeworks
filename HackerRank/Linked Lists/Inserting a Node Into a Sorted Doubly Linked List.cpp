DoublyLinkedListNode* sortedInsert(DoublyLinkedListNode* llist, int data) {
    DoublyLinkedListNode* newNode = new DoublyLinkedListNode(data);
    
    if (llist == nullptr) return newNode;
    
    if (data <= llist->data) {
        newNode->next = llist;
        llist->prev = newNode;
        return newNode;
    }
    
    DoublyLinkedListNode* current = llist;
    while (current->next != nullptr && current->next->data < data) {
        current = current->next;
    }
    
    newNode->next = current->next;
    
    if (current->next != nullptr) {
        current->next->prev = newNode;
    }
    
    current->next = newNode;
    current->prev = current;
    
    return llist;
}
