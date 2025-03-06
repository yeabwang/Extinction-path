//#include <iostream>
//#include <vector>
//using namespace std;
//
//template <class T>
//class Node{
//    public:
//        T value;
//        Node<T>* next;
//        Node<T>* previous;
//        Node(T val){
//            value=val;
//            next=NULL;
//            previous=NULL;
//        }
//};
//
//
//
//
//
//template <class T>
//class List{
//    public:
//        List(){
//            start=NULL;
//            end=NULL;
//            size=0;
//        }
//
//
//        void pop(){
//            cout<<"size: "<<size<<endl;
//            if(size==0){
//                cerr<<"No item found!\n";
//            }
//            else{
//                if(size==1){
//                    start=NULL;
//                    Node<T>* toBeDeleted= end;
//                    end=NULL;
//                    size-=1;
//                    delete toBeDeleted;
//                }
//                else{
//                    Node<T>* toBeDeleted= end;
//                    end = end->previous;
//                    end->next=NULL;
//                    size-=1;
//                    delete toBeDeleted;
//                }
//            }
//
//        }
//
//        T remove_at(int index)
//        {
//            Node<T>* loopingNode = start;
//            int counter=0;
//            while(loopingNode){
//                    cout<<"counter"<<counter<<endl;
//                if (counter==index)
//                    {
//                        Node<T>* next = loopingNode->next;
//                        cout<<"Next: "<<next<<endl;
//                        Node<T>* previous = loopingNode->previous;
//                        cout<<"previous: "<<previous<<endl;
//                        cout<<"Start: "<<start<<endl;
//                        if (next==NULL)
//                        {
//
//                            end = previous;
//
//                        }
//                        else
//                            {
//                                next->previous = previous;
//                            }
//
//                        if (previous==NULL)
//                        {
//                            start = next;
//                        }
//                        else
//                            {
//                                previous->next = next;
//                            }
//                        size--;
//                        delete loopingNode;
//                        return loopingNode->value;
//                        break;
//                    }
//
//                loopingNode = loopingNode->next;
//                counter+=1;
//            }
//
//        }
//
//        void add(T val){
//            cout<<"Val: "<<val<<endl;
//            if (size==0){
//                start = new Node<T>(val);
//                end=start;
//                size += 1;
//            }
//            else{
//                Node<T>* addingNode = new Node<T>(val);
//                end->next = addingNode;//previous ending node
//                addingNode->previous = end;//keeping track of previous node too
//                end = addingNode;//new ending node
//                size += 1;
//            }
//        }
//
//        int getValueAt(int index){
//            Node<T>* loopingNode = start;
//            int counter=0;
//            //cout<<"Looping: "<<loopingNode<<endl;
//            while(loopingNode){
//                //  cout<<loopingNode->value<<endl;
//                if (counter==index){
//                //    cout<<loopingNode->value<<endl;
//                    return loopingNode->value;
//                }
//
//                loopingNode = loopingNode->next;
//                counter+=1;
//            }
//            return -1;
//
//        }
//
//        bool Send_back(int index){
//            if (index<=0 || index>size-1 )
//                return false;
//            else{
//                Node<T>* loopingNode = start;
//                int counter=0;
//                while(loopingNode){
//                    if (counter==index){//cout<<loopingNode->value<<endl;
//                        break;
//                    }
//                    loopingNode = loopingNode->next;
//                    counter+=1;
//                }
//
//                Node<T>* loopingPrevious=loopingNode->previous;
//                if (loopingPrevious->previous==NULL){
//
//                    Node<T>* LNP=loopingNode->previous;
//                    Node<T>* LNN=loopingNode->next;
//                    Node<T>* PNP=loopingPrevious->previous;
//                    Node<T>* PNN=loopingPrevious->next;
//                    loopingNode->next = LNP;
//                    loopingPrevious->next = LNN;
//                    loopingNode->previous = PNP;
//                    loopingPrevious->previous = PNN;
//                    start = loopingNode;
//                }
//                else if (loopingNode->next==NULL){
//                    loopingPrevious->previous->next=loopingNode;
//                    Node<T>* LNP=loopingNode->previous;
//                    Node<T>* LNN=loopingNode->next;
//                    Node<T>* PNP=loopingPrevious->previous;
//                    Node<T>* PNN=loopingPrevious->next;
//                    loopingNode->next = LNP;
//                    loopingPrevious->next = LNN;
//                    loopingNode->previous = PNP;
//                    loopingPrevious->previous = PNN;
//                    end = loopingPrevious;
//                }
//                else{
//                    loopingPrevious->previous->next=loopingNode;
//                    Node<T>* LNP=loopingNode->previous;
//                    Node<T>* LNN=loopingNode->next;
//                    Node<T>* PNP=loopingPrevious->previous;
//                    Node<T>* PNN=loopingPrevious->next;
//                    loopingNode->next = LNP;
//                    loopingPrevious->next = LNN;
//                    loopingNode->previous = PNP;
//                    loopingPrevious->previous = PNN;
//                }
//                return true;
//            }
//        }
//        void print(){
//            Node<T>* loopingNode = start;
//            cout<<"Size: "<<size<<" "<<"{";
//                while(loopingNode){
//                    cout<<loopingNode->value<<",";
//                    loopingNode = loopingNode->next;
//
//                }
//                cout<<"}"<<endl;
//
//        }
//        friend ostream& operator<< (ostream& o, const List& lst)
//        {
//            Node<T>* loopingNode = lst.start;
//            o<<"{";
//                while(loopingNode){
//                    o<<loopingNode->value<<",";
//                    loopingNode = loopingNode->next;
//
//                }
//                o<<"}"<<endl;
//
//        }
//        int getCount(){
//            return size;
//        }
//        Node<T>* getStart(){
//            return start;
//        }
//        Node<T>* getEnd(){
//            return end;
//        }
//        private:
//        int size;
//        Node<T>* start;
//        Node<T>* end;
//
//};
//
//
//
//
//
//
//
//
