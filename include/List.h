#ifndef LIST_H
#define LIST_H
#include <stdio.h> 
#include <vector>

// Template class to allow the list to store any data type
template <class T>
class Node {
    public:
        T value;
        Node<T>* next;
        Node<T>* previous;
        Node(T val) {
            value = val;
            next = NULL;
            previous = NULL;
        }
};

template <class T>
class List {
    public:
        List() {
            start = NULL;
            end = NULL;
            size = 0;
        }

        void freeMemory() {
            // Deletes all nodes except the first one, as required by the game (first node holds the hero pointer)
            Node<T>* loopingNode = start->next;
            while (loopingNode) {
                size--;
                Node<T>* temp = loopingNode;
                loopingNode = loopingNode->next;
                delete temp->value;
                delete temp;
            }
            start->next = NULL;
            end = start;
        }

        T pop(int n = -1) {
            // Removes a node from either the start or end based on the argument; defaults to removing the last node (-1)
            if (size == 0) {
                printf("No item found!\n");
                return T(); 
            } else {
                if (n == -1) {
                    if (size == 1) {
                        Node<T>* toBeDeleted = end;
                        start = NULL;
                        end = NULL;
                        size -= 1;
                        T x = toBeDeleted->value;
                        delete toBeDeleted;
                        return x;
                    } else {
                        Node<T>* toBeDeleted = end;
                        end = end->previous;
                        end->next = NULL;
                        size -= 1;
                        T x = toBeDeleted->value;
                        delete toBeDeleted;
                        return x;
                    }
                } else {
                    if (size == 1) {
                        Node<T>* toBeDeleted = end;
                        start = NULL;
                        end = NULL;
                        size -= 1;
                        T x = toBeDeleted->value;
                        delete toBeDeleted;
                        return x;
                    } else {
                        Node<T>* toBeDeleted = start;
                        start = start->next;
                        start->previous = NULL;
                        size -= 1;
                        T x = toBeDeleted->value;
                        delete toBeDeleted;
                        return x;
                    }
                }
            }
        }

        T remove_at(int index) {
            // Deletes the node at the specified index and returns its value; returns default T if index is invalid
            Node<T>* loopingNode = start;
            int counter = 0;
            while (loopingNode) {
                if (counter == index) {
                    Node<T>* next = loopingNode->next;
                    Node<T>* previous = loopingNode->previous;
                    if (next == NULL) {
                        end = previous;
                    } else {
                        next->previous = previous;
                    }

                    if (previous == NULL) {
                        start = next;
                    } else {
                        previous->next = next;
                    }
                    size--;
                    T x = loopingNode->value;
                    delete loopingNode;
                    return x;
                }
                loopingNode = loopingNode->next;
                counter += 1;
            }
            printf("Index %d out of bounds!\n", index);
            return T(); 
        }

        void add(T val) {
            // Appends a new node with the given value to the end of the list
            if (size == 0) {
                start = new Node<T>(val);
                end = start;
                size += 1;
            } else {
                Node<T>* addingNode = new Node<T>(val);
                end->next = addingNode;
                addingNode->previous = end;
                end = addingNode;
                size += 1;
            }
        }

        T getValueAt(int index) {
            // Retrieves the value at the specified index; returns default T if index is invalid
            Node<T>* loopingNode = start;
            int counter = 0;
            while (loopingNode) {
                if (counter == index) {
                    return loopingNode->value;
                }
                loopingNode = loopingNode->next;
                counter += 1;
            }
            printf("Index %d out of bounds!\n", index);
            return T(); 
        }

        void print() {
            Node<T>* loopingNode = start;
            printf("Size: %d {", size);
            while (loopingNode) {
                printf("%d,", (int)loopingNode->value); 
                loopingNode = loopingNode->next;
            }
            printf("}\n");
        }

        int getCount() {
            return size;
        }
        Node<T>* getStart() {
            return start;
        }
        Node<T>* getEnd() {
            return end;
        }

        bool HasTank = false;

    private:
        int size;
        Node<T>* start;
        Node<T>* end;
};

#endif // LIST_H