#include <cstdlib>
#include<iostream>
using namespace std;
#include <cmath>
#include <chrono>
#include <ctime>
using namespace std::chrono;
class Sequence{
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
class SeqArray:public Sequence
{
private:
	int swap(int i, int j);
	int* array;
	int asize;
	int numswaps=0;
	int numcompare=0;
public:
	int len;
    int insert(int value) override;
    int insert(int index, int value) override;
    int insertFirst(int value) override;
    int remove(int value) override;
    int remove(int index, int value) override;
    int removeFirst(int value) override;
    int sort() override;
	SeqArray();
	SeqArray(int size);
	SeqArray(const SeqArray& rhs);
	~SeqArray();
	void operator = (const SeqArray& rhs);
	void fillrandom();
	void printall();
	void sortbubble();
	void sortselection();
	void sortinsertion();
	int getswaps();
	int getcompares();
};
int SeqArray::insert(int value) {
     if (len >= asize) {
        int ns = asize * 2;//doubling the array size
        int* nar = new int[ns];
        for (int i = 0; i < len; i++) {
            nar[i] = array[i];
        }
        delete[] array;
        array = nar;
        asize = ns;
    }
    array[len] = value;
    len++;
    return SUCCESS;
}

int SeqArray::insert(int index, int value) {
    if (index < 0 || index > len) {
        return ERROR;}
     if (len >= asize) {
        int ns = asize * 2;
        int* nar = new int[ns];
        for (int i = 0; i < len; i++) {
            nar[i] = array[i];
        }
        delete[] array;
        array = nar;
        asize = ns;}
    for (int i=len;i>index; i--) {
        array[i]=array[i-1];}
    array[index]=value;
    len++;
    return SUCCESS;
}

int SeqArray::insertFirst(int value) {
    return insert(0, value);}
int SeqArray::remove(int value) {
    int index = -1;
    for(int i =0;i<len; i++){
        if (array[i]==value){
            index = i;
            break;}}
    if(index==-1) {
        return ERROR;}
    for(int i=index; i<len-1; i++){
        array[i] = array[i + 1];}
    len--;
    return SUCCESS;
}

int SeqArray::remove(int index, int value){
    if (index<0 || index>=len){
        return ERROR; }
    if (array[index]!=value) {
        return ERROR;}
    for (int i=index;i<len -1;i++){
        array[i] = array[i + 1];}
    len--;
    return SUCCESS;
}

int SeqArray::removeFirst(int value) {
    return remove(0, value);}
int SeqArray::sort() {
    for (int i=0;i<len-1;i++){
        for (int j = 0; j < len - i - 1; j++){
            if (array[j] > array[j + 1]){
                swap(j,j+1);}}
    }
    return SUCCESS;}
int SeqArray::swap(int i, int j) {
    numswaps++;
    int tmp=array[i];
    array[i]=array[j];
    array[j]=tmp;
    return 1;}
SeqArray::SeqArray(){
    len = 0; asize = 0;
    array = NULL;}
SeqArray::SeqArray(int size) {
    len=size;
    asize=size*2;//double the size
    array = new int[asize];
    for (int i = 0; i < asize; i++) {
        array[i] = 0;}}
SeqArray::~SeqArray(){
    delete[] array;}
SeqArray::SeqArray(const SeqArray& rhs) {
    len = rhs.len;
    asize=rhs.asize;
    array=new int[asize];
    if(len < asize)
    for (int i = 1; i < len; i++) {
            array[i] = rhs.array[i];}}
void SeqArray::fillrandom() {
    srand(2345154798);
    for (int i = 0; i < len; i++) {
        array[i] = rand() % 10000;}}
void SeqArray::printall() {
    char* buffer = new char[len * 4];
    for (int i = 0; i < len - 1; i++) {
        cout<<array[i]<< ", ";}
    cout<<array[len - 1]<<".\n"<<endl;
}
void SeqArray::operator=(const SeqArray& rhs) {
    if (asize!=rhs.asize) {
        delete array;
        len=rhs.len;
        asize=rhs.asize;
        array=new int[asize];}
    for (int i =1;i<len; i++) {
        array[i] = rhs.array[i];}}
void SeqArray::sortbubble() {
    numswaps=0; numcompare=0;
    bool isSorted = false;
    int i = 0, len_1 = len - 1;
    while (isSorted==false) {
        isSorted = true;
        for (int j=0;j<len_1 - i;j++) {
            if (array[j]>array[j + 1]) {
                numcompare++;
                isSorted = false;
                swap(j + 1, j);
            }}
        ++i;
    }
}

void SeqArray::sortselection() {
    numswaps = 0; numcompare = 0;
    int minIndex = 0;
    for (int j=0;j<len;j++) {
        for (int i=j;i<len;i++) {
            if (array[minIndex] > array[i]) {
                numcompare++;
                minIndex = i;}
        }
        swap(j, minIndex);
    }
}


void SeqArray::sortinsertion() {
    numswaps = 0; numcompare = 0;
    for (int i = 1; i < len; i++) {
        int j = i;
        int key = array[i];
        while (key < array[j - 1] && j>0) {
            numcompare++;
            array[j] = array[j - 1];
            --j;
            numswaps++;}
        array[j]=key; numswaps++;}
}
int SeqArray::getswaps() {
    return numswaps;}
int SeqArray::getcompares() {
    return numcompare;}
int main()
{
	clock_t time_req;// to calculate time taken,couldnt make the clock provided in the original main work so did this
	time_req = clock();
    time_point<system_clock> start, end;
    cout<<"Hello World!\n";
    SeqArray s1=SeqArray(1000000);
    s1.fillrandom();
    SeqArray tmp;
    float bs,is,ss;
    //--Check if the sort is working--//
    //s1.printall();
    //s1.sortinsertion();
    //s1.printall();
    
    //--Timing your algorithm--//
    /* Modify the below code to get average of the each sorting algorithm */
    for (int i = 0; i < 10; i++){
        tmp = s1;
        start = system_clock::now();
        tmp.sortbubble();
        end = system_clock::now();
        time_req = clock() - time_req;
        cout << "Bubble - time taken: " << (float)time_req/CLOCKS_PER_SEC << "ms ";
        cout << " - Comparisions : " << tmp.getcompares() << " - Swaps : " << tmp.getswaps() << "\n";
        bs+=(float)time_req/CLOCKS_PER_SEC;
        tmp = s1;
        start = system_clock::now();
        tmp.sortinsertion();
        end = system_clock::now();
        time_req = clock() - time_req;
        cout << "Insertion - time taken: " << (float)time_req/CLOCKS_PER_SEC << "ms ";
        cout << " - Comparisions : " << tmp.getcompares() << " - Swaps : " << tmp.getswaps() <<"\n";
        is+=(float)time_req/CLOCKS_PER_SEC;
        tmp = s1;
        start = system_clock::now();
        tmp.sortselection();
        end = system_clock::now();
        time_req = clock() - time_req;
        cout << "Selection - time taken: " << (float)time_req/CLOCKS_PER_SEC << "ms";
        cout << " - Comparisions : " << tmp.getcompares() << " - Swaps : " << tmp.getswaps() << "\n\n";
		ss+=(float)time_req/CLOCKS_PER_SEC;
        s1.fillrandom();
    }
    cout << endl;
    cout<<"average time for bubble sort="<<(bs/10)<<endl;
    cout<<"average time for insertion sort="<<(is/10)<<endl;
    cout<<"average time for selection sort="<<(ss/10)<<endl;
    
}


