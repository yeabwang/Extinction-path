#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <vector>
using namespace std;
///Double Linked list


/**
    created template so that the list can be used for any data type
**/
template <class T>
class Node{
    public:
        T value;
        Node<T>* next;
        Node<T>* previous;
        Node(T val){
            value=val;
            next=NULL;
            previous=NULL;
        }

};




template <class T>
class List{
    public:
        List()
        {
            start=NULL;
            end=NULL;
            size=0;
        }

        void freeMemory()
        {
            /***
                removes all elements except first, because it is the requirement of our game (first node stores pointer to hero)
            ***/
            Node<T>* loopingNode = start->next;
            while(loopingNode)
            {
                size--;
                Node<T>*temp = loopingNode;
                loopingNode=loopingNode->next;
                delete temp->value;
                delete temp;
            }
            start->next = NULL;
            end=start;

        }


        T pop(int n=-1)
        {
            /***
                removes node from either start or end, depending on argument.
                default is -1 which makes pop to remove last node.
                if the argument is changed it will remove starting node
            ***/
            if(size==0){
                cerr<<"No item found!\n";
                return NULL;
            }
            else{
                if (n==-1)
                {
                    if(size==1){
                        start=NULL;
                        Node<T>* toBeDeleted= end;
                        end=NULL;
                        size-=1;
                        T x =toBeDeleted->value;
                        delete toBeDeleted;
                        return x;
                    }
                    else{
                        Node<T>* toBeDeleted= end;
                        end = end->previous;
                        end->next=NULL;
                        size-=1;
                        T x= toBeDeleted->value;
                        delete toBeDeleted;
                        return x;
                    }
                }
                else
                {
                    if(size==1){
                        start=NULL;
                        Node<T>* toBeDeleted= end;
                        end=NULL;
                        size-=1;
                         T x =toBeDeleted->value;
                        delete toBeDeleted;
                        return x;
                    }
                    else{
                        Node<T>* toBeDeleted= start;
                        start = start->next;
                        start->previous=NULL;
                        size-=1;
                        T x =toBeDeleted->value;
                        delete toBeDeleted;
                        return x;
                    }
                }
            }

        }

        T remove_at(int index)
        {
            ///removes element from a specific index
            Node<T>* loopingNode = start;
            int counter=0;
            while(loopingNode){
                if (counter==index)
                    {
                        Node<T>* next = loopingNode->next;
                        Node<T>* previous = loopingNode->previous;
                        if (next==NULL)
                        {
                            end = previous;
                        }
                        else
                            {
                                next->previous = previous;
                            }

                        if (previous==NULL)
                        {
                            start = next;
                        }
                        else
                            {
                                previous->next = next;
                            }
                        size--;
                        delete loopingNode;
                        return loopingNode->value;
                        break;
                    }

                loopingNode = loopingNode->next;
                counter+=1;
            }

        }

        void add(T val)
        {
            ///adds new node
            if (size==0){
                start = new Node<T>(val);
                end=start;
                size += 1;
            }
            else{
                Node<T>* addingNode = new Node<T>(val);
                end->next = addingNode;//previous ending node
                addingNode->previous = end;//keeping track of previous node too
                end = addingNode;//new ending node
                size += 1;
            }
        }

        T getValueAt(int index)
        {
            ///returns a value at specific index
            Node<T>* loopingNode = start;
            int counter=0;
            while(loopingNode){
                if (counter==index)
                {
                    return loopingNode->value;
                }

                loopingNode = loopingNode->next;
                counter+=1;
            }
            return -1;

        }

        void print()
        {
            Node<T>* loopingNode = start;
            cout<<"Size: "<<size<<" "<<"{";
                while(loopingNode){
                    cout<<loopingNode->value<<",";
                    loopingNode = loopingNode->next;

                }
                cout<<"}"<<endl;


        }
        friend ostream& operator<< (ostream& o, const List& lst)
        {
            Node<T>* loopingNode = lst.start;
            o<<"{";
                while(loopingNode){
                    o<<loopingNode->value<<",";
                    loopingNode = loopingNode->next;

                }
                o<<"}"<<endl;
                return o;

        }
        int getCount(){
            return size;
        }
        Node<T>* getStart(){
            return start;
        }
        Node<T>* getEnd(){
            return end;
        }

        bool HasTank = false;


        private:
        int size;
        Node<T>* start;
        Node<T>* end;

};










#endif // LIST_H
