// Created by Hamdi on 3/29/2023.
//
#include <iostream>
#include <cstring>
using namespace std;
class Exeption{
    int n;
public:
    explicit Exeption(int n) : n(n) {}

    void message(){
        cout<<"Index '"<<n<<"' is out of bounds"<<endl;
    }
};

using namespace std;
class String{
    char* str;
    int n;
    void copy(const String &other){
        this->n=other.n;
        this->str=new char[other.n];
        for (int i = 0; i < n; ++i) {
            this->str[i]=other.str[i];
        }
    }
public:
    String(char* word="") {
        this->n=strlen(word);
        this->str=new char[n+1];
        for (int i = 0; i < n; ++i) {
            this->str[i]=word[i];
        }
    }
    String(const String &other){
        copy(other);
    }
    String &operator=(const String &other){
        if (this!=&other){
            delete[]str;
            copy(other);
        }
        return *this;
    }
    char operator[](int i){
        if (i<0 || i>n-1){
            throw Exeption(i);
        }else {
            return str[i];
        }
    }

    friend ostream &operator<<(ostream &os, const String &string1) {
        for (int i = 0; i < string1.n; ++i) {
            os<< string1.str[i];
        }

        return os;
    }
    ~String(){
        delete[]str;
    }

    int getn() const {
        return n;
    }
    int size(){
        int count=0;
        for (int i = 0; i < n; ++i) {
            count+=str[i];
        }
        return count;
    }

};
///
class StringBuilder{
    String* strings;
    int n;
    int capacity;
    void copy(const StringBuilder &other){
        this->capacity=other.capacity;
        this->n=other.n;
        this->strings=new String[other.capacity];
        for (int i = 0; i < n; ++i) {
            this->strings[i]=other.strings[i];
        }
    }
public:
     StringBuilder(int capacity) : capacity(capacity) {
        this->capacity=capacity;
        this->n=0;
        this->strings=new String[capacity];
         for (int i = 0; i < n; ++i) {
             this->strings[i]=strings[i];
         }
    }
    StringBuilder(const StringBuilder &other){
        copy(other);
    }
    StringBuilder &operator=(const StringBuilder &other){
        if (this!=&other){
            delete[]strings;
            copy(other);
        }
        return *this;
    }
    StringBuilder &operator+=(String &s) {
            int size=0;
        for (int i = 0; i < n; ++i) {
              size+=strings[i].getn()+2;
        }
        if (size+s.getn()>capacity){
            capacity*=2;
            if (size + s.getn() > capacity) {
                capacity = size + s.getn();
            }
        }


            String *tmp = new String[capacity];
            for (int i = 0; i < n; ++i) {
                tmp[i] = strings[i];
            }
            tmp[n] = s;
            n++;


            delete[]strings;
            strings = tmp;
            return *this;
    }




    friend ostream &operator<<(ostream &os, const StringBuilder &builder) {
        os <<"Capacity: "<< builder.capacity<<endl;
        int count=0;
        for (int i = 0; i < builder.n; ++i) {
            count+=builder.strings[i].getn();
        }
        os <<"Size: "<<count<<endl;
        os <<"Contents: ";
        for (int i = 0; i < builder.n; ++i) {
            os << builder.strings[i];
        }
        return os;
    }
    ~StringBuilder(){
        delete[]strings;
    }
};
// your code here

int main() {
    int n;
    cin >> n;
    StringBuilder sb(n);
    cin >> n;
    for(int i = 0; i < n; ++i) {
        char input[100];
        cin >> input;
        String s(input);
        int x;
        cin >> x;
        try {
            cout << "s[" << x << "] = " << s[x] << endl;

        }catch(Exeption &e){
            e.message();
        }

         sb += s;
    }
    cout << sb;
    return 0;
}