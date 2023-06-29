//
// Created by Hamdi on 3/30/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class Word{
private:
    char*word;
    void copy(const Word &other){
        this->word=new char [strlen(other.word)+1];
        strcpy(this->word,other.word);
    }
public:
    Word(char *word="UNDEFINED"){
        this->word=new char [strlen(word)+1];
        strcpy(this->word,word);
    }
    Word(const Word &other){
        copy(other);
    }
    Word &operator=(Word &other){
        if(this==&other){
            return *this;
        }
        delete[]word;
        copy(other);
        return *this;
    }
    ~Word(){
        delete[]word;
    }
    void print(){
        cout<<word<<" ";
    }
};
class Sentence{
    Word *word;
    int n;
    int capacity;
    void copy (const Sentence &other){
        this->capacity=other.capacity;
        this->n=other.n;
        this->word=new Word[other.capacity];
        for (int i = 0; i < n; ++i) {
            this->word[i]=other.word[i];
        }
    }
public:
    Sentence(int capacity=10){
        this->capacity=capacity;
        n=0;
        this->word=new Word[capacity];
        this->word=word;
    }
    Sentence(const Sentence &other){
        copy(other);
    }
    Sentence &operator=(Sentence &other){
        if (this==&other){
            return *this;
        }
        delete[]word;
        copy(other);
        return *this;
    }

    ~Sentence() {
        delete[]word;
    }
    void increasecapacity(){
        Word *tmp = new Word [capacity+10];
        for (int i = 0; i < n; ++i) {
            tmp[i]=word[i];
        }
        delete[]word;
        word=tmp;
        capacity+=10;
    }

    void add(Word &w){
        if (capacity==n){
            increasecapacity();
        }
        word[n]=w;
        n++;
    }
    void print(){
        for (int i = 0; i < n; ++i){
            word[i].print();
        }
        cout<<endl;

    }
    void swap(int i, int j){
        Word tmp;
        tmp=word[i];
        word[i]=word[j];
        word[j]=tmp;

    }

};


int main(){

    int n;
    cin >> n;
    cin.get();
    cout << "CONSTRUCTOR" << endl;
    Sentence s;
    cout << "ADD WORD" << endl;
    for (int i = 0; i < n; ++i) {
        char w[100];
        cin.getline(w, 100);
        Word word(w);
        s.add(word);
    }
    cout << "PRINT SENTENCE" << endl;
    s.print();
    cout << "COPY" << endl;
    Sentence x = s;
    cout << "SwAP" << endl;
    x.swap(n / 2, n / 3);
    x.print();
    cout << "ORIGINAL" << endl;
    s.print();

    return 0;
}
