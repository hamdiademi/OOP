// Created by Hamdi on 3/29/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class Pair{
    char *key;
    int value;
    void copy(const Pair &other){
        this->key=new char[strlen(other.key)+1];
        strcpy(this->key,other.key);
        this->value=other.value;
    }
public:
    Pair(char *key="", int value=0){
        this->key=new char[strlen(key)+1];
        strcpy(this->key,key);
        this->value=value;
    }
    Pair(const Pair &other){
        copy(other);
    }
    Pair &operator=(const Pair &other){
        if (this!=&other){
            delete[] key;
            copy(other);
        }
        return *this;
    }
    ~Pair(){
        delete[] key;
    }

    friend ostream &operator<<(ostream &os, const Pair &pair1) {
        os << "'" << pair1.key << "' -> " << pair1.value<<endl;
        return os;
    }
    Pair &operator--(){ //prefix
        --value;
        return *this;
    }
    Pair operator--(int){ //postfix
        Pair copy(*this);
        value--;
        return copy;
    }

    friend Pair operator*( const Pair& p1,const Pair& p2){
        int resultvalue=p1.value*p2.value;
        if (strlen(p1.key)<strlen(p2.key)){
            return Pair(p1.key,resultvalue);
        }
        else{
            return Pair(p2.key,resultvalue);
        }
    }
    friend class Collection;

};

class Collection{
    Pair* pairs;
    int n;
    void copy(const Collection &other){
        this->n=other.n;
        this->pairs=new Pair[other.n];
        for (int i = 0; i < n; ++i) {
            this->pairs[i]=other.pairs[i];
        }
    }
public:

    Collection(Pair *pairs= nullptr, int n=0) {
        this->n=0;
        this->pairs=new Pair[n];
    }
    Collection(const Collection &other){
        copy(other);
    }
    Collection &operator=(const Collection &other){
        if (this!=&other){
            delete[] pairs;
            copy(other);
        }
        return *this;
    }

    Collection &operator+=(Pair &p){
        Pair *tmp=new Pair[n+1];
        for (int i = 0; i < n; ++i) {
            tmp[i]=pairs[i];
        }
        tmp[n]=p;
        n++;
        delete[] pairs;
        pairs=tmp;
        return *this;
    }
    ~Collection(){
        delete[] pairs;
    }

    friend ostream &operator<<(ostream &os, const Collection &collection) {
        os << "Size: "<<collection.n<<endl;
        for (int i = 0; i < collection.n; ++i) {
            os<<collection.pairs[i];
        }
        return os;
    }

    bool operator<(const Collection &rhs) const {
        return pairs > rhs.pairs;
    }
    int greater(int value){
        int count=0;
        for (int i = 0; i < n; ++i) {
            if (pairs[i].value>value){
                count++;
            }
        }
        return count;

    }

};

void read(char *k, float *v) {
    cin >> k;
    cin >> *v;
}
int main() {
    char key[50];
    float value;
    cout << "----- class Pair -----" << endl;
    read(key, &value);
    cout << "----- constructor -----" << endl;
    Pair p1(key, value);
    read(key, &value);
    Pair p2(key, value);
    Pair p3(p1);
    cout << "----- operator << -----" << endl;
    cout << p1;
    cout << p2;
    cout << "----- operator --(int) -----" << endl;
    cout << p1--;
    cout << p1;
    cout << "----- operator -- -----" << endl;
    cout << --p2;
    cout << "----- operator * -----" << endl;
     Pair p = p1 * p2;
    cout << "----- operator = -----" << endl;
    p3 = p;
    cout << p3;

    cout << "----- class Collection -----" << endl;
    cout << "----- constructor -----" << endl;
    Collection k;
    cout << "----- operator += -----" << endl;
    k += p1;
    k += p2;
    k += p3;
    cout << "----- operator << -----" << endl;
    cout << k;
    cout << "----- copy constructor -----" << endl;
    Collection k2(k);
    cout << "----- operator < -----" << endl;
    if(k < k2) {
        cout << "k < k2" << endl;
    } else {
        cout << "k >= k2" << endl;
    }
    k2 += p1;
    if(k < k2) {
        cout << "k < k2" << endl;
    } else {
        cout << "k >= k2" << endl;
    }
    cout << "----- greater -----" << endl;
    int x;
    cin >> x;
    int pp = k.greater(x);
    cout << pp;
    return 0;
}
