// Created by Hamdi on 3/29/2023.
//
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

class Character{
    char ch;
public:
    Character(){}
     Character( char ch): ch(ch){

    }

    friend ostream &operator<<(ostream &os, const Character &character) {
        os << character.ch;
        return os;
    }

    char getCh() const {
        return ch;
    }

};

class CharSequence{
    Character* characters;
    int n;
    void copy(const CharSequence &other){
        this->n=other.n;
        this->characters=new Character[other.n];
        for (int i = 0; i < n; ++i) {
            this->characters[i]=other.characters[i];
        }
    }
public:
    //CharSequence(){}

    CharSequence(const char *str=""){
        this->n=strlen(str);
        this->characters=new Character[n];
        for (int i = 0; i < n; ++i) {
            this->characters[i]=str[i];
        }
    }
    CharSequence(const CharSequence &other){
        copy(other);
    }
    CharSequence &operator=(const CharSequence &other){
        if (this!=&other){
            delete[] characters;
            copy(other);
        }
        return *this;
    }
    ~CharSequence(){
        delete[]characters;
    }
    CharSequence &operator+=(const Character &ch){
        Character *tmp=new Character[n+1];
        for (int i = 0; i < n; ++i) {
            tmp[i]=characters[i];
        }
        tmp[n]=ch;
        n++;
        delete[]characters;
        characters=tmp;
        return *this;

    }

    friend ostream &operator<<(ostream &os, const CharSequence &s) {
        for (int i = 0; i < s.n; ++i) {
            os<<s.characters[i];
        }
        return os;
    }
    Character &operator [](int i){
       return characters[i];
    }

    int operator[](char c){
        int count=0;
        for (int i = 0; i < n; ++i) {
            if (characters[i].getCh()==c){
                count++;
            }
        }
        return count;
    }

    CharSequence toUpperCase(){
        Character *tmp=new Character[n];
        for (int i = 0; i < n; ++i) {
            tmp[i]=toupper(characters[i].getCh());
        }
        delete[]characters;
        characters=tmp;
        return *this;
    }

    bool operator==(const CharSequence &rhs) const {
        if (rhs.n == n) {
            for (int i = 0; i < n; ++i) {

                if (rhs.characters[i].getCh()!=characters[i].getCh()){
                    return false;
                }

            }
            return true;
        }
        return false;

    }

};

int main() {
    int n;
    cin >> n;

    if(n == 1) {
        cout << "Testing Character class" << endl;
        cout << "Character constructor" << endl;
        char c;
        cin >> c;
        Character cc(c);
        cout << "OK" << endl;
        cout << "Character operator <<" << endl;
        cout << cc << endl;
    } else if(n == 2) {
        cout << "Testing CharSequence constructors" << endl;
        char word[100];
        cin >> word;
        CharSequence cs1(word);
        cout << cs1 << endl;
    }
    else if(n == 3) {
        cout << "Testing CharSequence copy constructor and operator[int]" << endl;
        CharSequence cs("Some sequence");
        CharSequence copy(cs);
        cs[0] = 'X';
        cout << "Original: " << cs << endl;
        cout << "Copy: " << copy << endl;
    }
    else if(n == 4) {
        cout << "Testing CharSequence =operator and operator[int]" << endl;
        CharSequence cs("Some sequence");
        CharSequence copy;
        copy = cs;
        cs[0] = 'X';
        cout << "Original: " << cs << endl;
        cout << "Copy: " << copy << endl;
    }
    else if(n == 5) {
        cout << "Testing CharSequence operator+=" << endl;
        CharSequence cs;
        char word[100];
        cin >> word;
        int len = strlen(word);
        for(int i = 0; i < len; ++i) {
            cs += Character(word[i]);
        }
        cout << cs << endl;
    }
    else if(n == 6) {
        cout << "Testing CharSequence operator[char]" << endl;
        CharSequence cs("If you don't read the newspaper, you're uninformed. If you read the newspaper, you're mis-informed.");
        cout << cs['e'] << endl;
    }
    else if(n == 7) {
        cout << "Testing CharSequence toUpperCase" << endl;
        CharSequence cs("If you tell the truth, you don't have to remember anything");
        cout << cs.toUpperCase() << endl;
    }
    else if(n == 8) {
        cout << "Testing CharSequence operator ==" << endl;
        CharSequence cs1("abc");
        CharSequence cs2("abc");
        CharSequence cs3("abcd");
        CharSequence cs4("xyz");
        cout << (cs1 == cs2) << endl;
        cout << (cs1 == cs3) << endl;
        cout << (cs2 == cs4) << endl;
    }

    return 0;
}
