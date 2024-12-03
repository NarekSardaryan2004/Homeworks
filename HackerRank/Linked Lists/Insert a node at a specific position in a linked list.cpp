SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* llist, int data, int position) {
     SinglyLinkedListNode* newNode = new SinglyLinkedListNode(data);
     
     if (position == 0) {
        newNode->next = llist;
        return newNode;
     }
     
     SinglyLinkedListNode* current = llist;
     for (int i = 1; i < position && current != nullptr; ++i) {
        current = current->next;
     }
     
     if (current == nullptr) return llist;
     
     newNode->next = current->next;
     current->next = newNode;
     
     return llist;
}
