#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
using namespace std;
using namespace std::chrono;
class node{
public:
    int data;
    node* next;

    node(int value) : data(value), next(nullptr) {}
};

class Sequence
{
public:
    virtual int insert(int) = 0;
    virtual int insert(int, int) = 0;
    virtual int insertFirst(int) = 0;
    virtual int remove(int) = 0;
    virtual int remove(int, int) = 0;
    virtual int removeFirst(int) = 0;
    virtual int sort() = 0;
    const int SUCCESS = 1;
    const int ERROR = 0;
};
class seqlinkedlist:public Sequence{
private:
    node* head;
    int len;
    int numswaps;
    int numcompare;
    void swap(node* node1, node* node2);
public:
    seqlinkedlist();
    ~seqlinkedlist();
    seqlinkedlist& operator=(const seqlinkedlist& rhs);
    int insert(int value) override;
    int insert(int index, int value) override;
    int insertFirst(int value) override;
    int remove(int value) override;
    int remove(int index, int value) override;
    int removeFirst(int value) override;
    int sort() override;
    void fillrandom(int);
    void printall();
    int getswaps();
    int getcompares();
    void sortbubble();
    void sortselection();
    void sortinsertion();
};

seqlinkedlist::seqlinkedlist() : head(nullptr), len(0), numswaps(0), numcompare(0) {}

seqlinkedlist& seqlinkedlist::operator=(const seqlinkedlist& rhs) {
    if (this == &rhs) {
        return *this;}
    while (head!=NULL){
        node* temp = head;
        head = head->next;
        delete temp;
    }
    len=rhs.len;
    node* rhsCurrent=rhs.head;
    node* current=nullptr;
    while(rhsCurrent!=nullptr) {
        node* newnode = new node(rhsCurrent->data);
        if(current==nullptr){
            head=newnode;}
        else{
            current->next = newnode;}
        current = newnode;
        rhsCurrent = rhsCurrent->next;}
    return *this;}
seqlinkedlist::~seqlinkedlist(){
    while(head!=nullptr){
        node* temp=head;
        head=head->next;
        delete temp;}}
int seqlinkedlist::insert(int value){
    return insert(len, value);}
int seqlinkedlist::insert(int index, int value){
    if (index<0 || index>len){
        return ERROR; }
    node* newnode = new node(value);
    if (index==0){
        newnode->next = head;
        head = newnode;}
    else{
        node* current = head;
        for (int i = 0; i < index - 1; i++){
            current = current->next;}
        newnode->next = current->next;
        current->next = newnode;}
    len++;
    return SUCCESS;}
int seqlinkedlist::insertFirst(int value){
    return insert(0, value);}
int seqlinkedlist::remove(int value){
    node* current = head;
    node* prev = nullptr;
    while(current){
        if (current->data==value){
            if (prev){
                prev->next=current->next;}
            else{
                head=current->next;
            }
            delete current;
            len--;
            return SUCCESS; }
        prev=current;
        current=current->next;}
    return ERROR; 
}

int seqlinkedlist::remove(int index, int value){
    if (index<0 || index>=len){
        return ERROR;
    }
    node* current = head;
    node* prev = nullptr;
    for (int i=0; i<index;i++){
        prev = current;
        current = current->next;}
    if (current->data==value){
        if (prev){
            prev->next = current->next;}
        else{
            head = current->next;}
        delete current;
        len--;
        return SUCCESS;}
    return ERROR;
}

int seqlinkedlist::removeFirst(int value){
    return remove(0, value);}
int seqlinkedlist::sort(){}//3 sorting methods already being defined
void seqlinkedlist::swap(node* node1, node* node2){
    int temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
    numswaps++;}
void seqlinkedlist::fillrandom(int x){
    srand(2345154798);
    for (int i=0;i<x;i++){
        insert(rand() % 10000);}}
void seqlinkedlist::printall(){
    node* current = head;
    while (current){
        cout<<current->data<< ", ";
        current = current->next;}
    cout<<endl;}
int seqlinkedlist::getswaps(){
    return numswaps;}
int seqlinkedlist::getcompares(){
    return numcompare;}
void seqlinkedlist::sortbubble(){
    numswaps = 0;
    numcompare = 0;
    bool swapped;
    node* current;
    node* last=nullptr;
    do{
        swapped = false;
        current = head;
        while (current->next!=last){
            if (current->data>current->next->data){
                swap(current,current->next);
                numswaps++;
                swapped=true;}
            current=current->next;
            numcompare++;
        }
        last=current;
    } while(swapped);
}
void seqlinkedlist::sortselection(){
    numswaps = 0;
    numcompare = 0;
    node* current = head;
    node* minnode;
    while (current){
        minnode=current;
        node* innerCurrent=current->next;
        while (innerCurrent){
            numcompare++;
            if (innerCurrent->data<minnode->data){
                minnode = innerCurrent;}
            innerCurrent = innerCurrent->next;}
        swap(current, minnode);
        current=current->next;
    }
}
void seqlinkedlist::sortinsertion(){
    numswaps = 0;
    numcompare = 0;
    node* sorted = nullptr;
    node* current = head;
    while (current){
        node* next=current->next;
        if (!sorted || sorted->data >= current->data){
            current->next = sorted;
            sorted = current;}
        else{
            node* search = sorted;
            while (search->next && search->next->data < current->data){
                search = search->next;
                numcompare++;}
            current->next = search->next;
            search->next = current;}
        current = next;}
    head = sorted;
}
int main()
{
    clock_t time_req;
    float bs =0,is=0,ss=0; // Initialize averages
    cout << "Hello World!\n";
    int nofelements=100000;
    seqlinkedlist s1;
    for (int i=0;i<nofelements;i++){
        s1.insert(rand()%10000);}// Insert random values into the linked list}
    seqlinkedlist tmp;

    //--Timing your algorithm--//
    /* Modify the below code to get the average of each sorting algorithm */
    for (int i=0;i<10;i++){
        tmp = s1;
        time_req = clock();
        tmp.sortbubble();
        time_req = clock() - time_req;
        cout << "Bubble - time taken: " << (float)time_req / CLOCKS_PER_SEC << "s ";
        cout << " - Comparisons : " << tmp.getcompares() << " - Swaps : " << tmp.getswaps() << "\n";
        bs += (float)time_req / CLOCKS_PER_SEC;
        tmp = s1;
        time_req = clock();
        tmp.sortinsertion();
        time_req = clock() - time_req;
        cout << "Insertion - time taken: " << (float)time_req / CLOCKS_PER_SEC << "s ";
        cout << " - Comparisons : " << tmp.getcompares() << " - Swaps : " << tmp.getswaps() << "\n";
        is += (float)time_req / CLOCKS_PER_SEC;
        tmp = s1;
        time_req = clock();
        tmp.sortselection();
        time_req = clock() - time_req;
        cout << "Selection - time taken: " << (float)time_req / CLOCKS_PER_SEC << "s";
        cout << " - Comparisons : " << tmp.getcompares() << " - Swaps : " << tmp.getswaps() << "\n\n";
        ss += (float)time_req / CLOCKS_PER_SEC;
        s1.fillrandom(nofelements);}
    cout<<endl;
    cout<<"Average time for bubble sort="<<(bs/10)<<"s"<<endl;
    cout<<"Average time for insertion sort="<<(is/10)<<"s"<<endl;
    cout<<"Average time for selection sort="<<(ss/10)<<"s"<<endl;

    return 0;
}

