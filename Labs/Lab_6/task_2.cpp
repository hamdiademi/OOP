//
// Created by Hamdi on 4/29/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class Book{
    char *name;
    int *isbn;
    int pages;
    void copy(const Book &other){
        this->name=new char[strlen(other.name)+1]; strcpy(this->name,other.name);
        this->isbn=new int[5];
        for (int i = 0; i < 5; ++i) {
            this->isbn[i]=other.isbn[i];
        }
        this->pages=other.pages;
    }
public:
    Book(char*name="", int *isbn=new int[0],int pages=0):pages(pages){
        this->name=new char[strlen(name)+1]; strcpy(this->name,name);
        this->isbn=new int[5];
        for (int i = 0; i < 5; ++i) {
            this->isbn[i]=isbn[i];
        }
    }

    Book(const Book &other){
        copy(other);
    }
    ~Book(){
        delete[]name;
        delete[]isbn;
    }
    //operator =
    Book &operator=(const Book &other){
        if (this!=&other){
            delete[]name;
            delete[]isbn;
            copy(other);
        }
        return *this;
    }

    //operator ==
    bool operator==(const Book & other){
        for (int i = 0; i < 5; ++i) {
            if (this->isbn[i]!=other.isbn[i]){
                return false;
            }
        }
        return true;
    }

    //operator <<
    friend ostream & operator<<(ostream &out,const Book &book) {
        out << "Title: " << book.name << " ISBN: [ ";
        for (int i = 0; i < 5; ++i) {
            out << book.isbn[i] << " ";
        }
        out << "]";

        return out;
    }
    int getPages() const{
        return pages;
    }
};

class BorrowABook{
    char name[101];
    Book *book;
    int nrofbook;
    void copy(const BorrowABook &other){
        strcpy(this->name,other.name);
        this->nrofbook=other.nrofbook;
        this->book=new Book[other.nrofbook];
        for (int i = 0; i < nrofbook; ++i) {
            this->book[i]=other.book[i];
        }
    }
public:
    BorrowABook(char *name=""){
        strcpy(this->name,name);
        this->book=new Book[0];
        this->nrofbook=0;
    }
    BorrowABook(const BorrowABook &other){
        copy(other);
    }
    ~BorrowABook(){
        delete[]book;
    }

    // operator =
    BorrowABook &operator=(const BorrowABook &other){
        if(this!=&other){
            delete[]book;
            copy(other);
        }
        return *this;
    }

    //operator+=
    BorrowABook &operator+=(const Book & other){
        Book *tmp=new Book[nrofbook+1];
        for (int i = 0; i < nrofbook; ++i) {
            tmp[i]=book[i];
        }
        tmp[nrofbook++]=other;
        delete[]book;
        book=tmp;
        return *this;
    }
    //operator -=
    BorrowABook &operator-=(const Book & other){
        Book *tmp=new Book[nrofbook-1];
        int j=0;
        for (int i = 0; i < nrofbook; ++i) {
         if(book[i]==other){
             continue;
         } else{
             tmp[j]=book[i];
             j++;
         }
        }
        nrofbook--;
       delete[]book;
        book=tmp;
        return *this;
    }
    void printNumberOfPages(int max){
        cout<<name<<endl;
        for (int i = 0; i < nrofbook; ++i) {
            if(book[i].getPages()>max){
                cout<<book[i]<<endl;
            }
        }
    }

};

int main()
{
    BorrowABook library("FINKI-Library");
    int n;
    cin>>n;

    for (int i=0;i<n;i++)
    {
        char title[100];
        int isbn[5];
        int pages;

        cin>>title;

        for (int i=0;i<5;i++)
            cin>>isbn[i];

        cin>>pages;

        Book nov=Book(title,isbn,pages);

        //adding a new book
        library+=nov;
    }

    //the book which has the same isbn as some previous one
    char title[100];
    int isbn[5];
    int pages;
    cin>>title;
    for (int i=0;i<5;i++)
        cin>>isbn[i];
    cin>>pages;

    Book greshka=Book(title,isbn,pages);

    //deleting a book
    library-=greshka;

    library.printNumberOfPages(150);

    return 0;
}