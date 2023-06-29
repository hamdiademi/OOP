#include<iostream>
#include<cstring>
using namespace std;

class RatingMissingException { };

class Person {
private:
    char name[20];
    int year;
public:
    Person (char *name, int year) {
        strcpy(this->name, name);
        this->year = year;
    }
    Person () {
        strcpy(this->name, "");
    }

    char const * getName() {
        return name;
    }
    int getYear() {
        return year;
    }
    void print() {cout << name << " (" << year << ")";}
};

class Song {
protected:
    Person performer[10];
    int nofPer;
    int *ratings;
    int nofRat;
private:
    char title[30];

    void copy(const Song &other){
        strcpy(this->title, other.title);
        this->nofPer = other.nofPer;
        for (int i = 0; i < other.nofPer; i++) this->performer[i] = other.performer[i];
        this->nofRat = other.nofRat;
        this->ratings = new int[other.nofRat];
        for (int i = 0; i < other.nofRat; i++) this->ratings[i] = other.ratings[i];
    }

public:
    Song(char *title="", Person *performers= nullptr, int numberPerformers=0, int *ratings= nullptr, int numberRatings=0) {
        strcpy(this->title, title);
        this->nofPer = numberPerformers;
        for (int i = 0; i < numberPerformers; i++) this->performer[i] = performers[i];
        this->nofRat = numberRatings;
        this->ratings = new int[numberRatings];
        for (int i = 0; i < numberRatings; i++) this->ratings[i] = ratings[i];

    }
    Song(const Song &other) {
        copy(other);
    }
    Song operator=(const Song &other) {
        if (this!=&other){
            delete[]ratings;
            copy(other);
        }
        return *this;
    }

    // complete the class
    virtual float getTotalRating() {
        if(nofRat <= 0) {
            throw RatingMissingException();
        }

        float a = 0, b = 11;
        for(int i = 0; i < nofRat; i++) {
            if(ratings[i] > a) {
                a = ratings[i];
            }
            if(ratings[i] < b) {
                b = ratings[i];
            }
        }

        return (a + b) / 2;
    }

    virtual void print() {
        for(int i = 0; i < nofPer; i++) {
            performer[i].print();
            if(i != nofPer - 1) {
                cout << ",";
            }
        }
        cout << ":" << title << "\n";
    }

    Person getPerformer(int i) {
        return performer[i];
    }

    int getNofPer() const {
        return nofPer;
    }
    ~Song() {
        delete [] ratings;
    }

};

class Movie {
protected:
    char *title;
    int popularity;
private:
    void copy (const Movie& other) {
        this->title = new char[strlen(other.title) + 1];
        strcpy(this->title, other.title);
        this->popularity = other.popularity;
    }
public:
    Movie(char *title="", int popularity=0) {
        this->popularity = popularity;
        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);
    }
    Movie(const Movie &other) {
        copy(other);
    }
    Movie operator=(const Movie &other) {
        if (this!=&other){
            delete[]title;
            copy(other);
        }
        return *this;
    }

    int getMoviePopularity() {
        return popularity;
    }
    char* getMovieTitle() {
        return title;
    }
    ~Movie() {delete [] title;}

};

class MovieSong: public Song,public Movie{
    int popularityofSong;
public:
    MovieSong(char *title, Person *performers, int numberPerformers, int *ratings, int numberRatings, char *title1,int popularity,int popularityofSong=0):
    Song(title, performers, numberPerformers, ratings, numberRatings),
    Movie(title1, popularity), popularityofSong(popularityofSong)  {}


    float getTotalRating(){
        return Song::getTotalRating() * ((float)popularityofSong / (float)getMoviePopularity());
    }
    void print() {
        Song::print();
        cout << "Movie:" << getMovieTitle() << "\n";
    }
    ~MovieSong() { }
};

double averageRating(Song** songs, int n) {
    double s = 0;
    int ct = 0;

    for(int i = 0; i < n; i++) {
        MovieSong *ms =dynamic_cast<MovieSong*>(songs[i]);
        if(ms) {
            try {
                s += ms->getTotalRating();
            } catch(RatingMissingException& e) {
                s += 5;
            }
            ct++;
        }
    }

    return s / ct;
}

void printSongs(char* performer, Song** songs, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < songs[i]->getNofPer(); j++) {
            if(!strcmp(performer, songs[i]->getPerformer(j).getName())) {
                songs[i]->print();
            }
        }
    }
}

int main() {

    Person performers[10];
    int year, numberOfPerformers, ratings[20], rating, numberOfRatings, type, popularity, songPopularity;
    char name[40], title[30],title1[30], perfomer[30];

    cin >> type;

    if (type == 1) //test class MovieSong
    {
        cout << "-----TEST MovieSong-----" << endl;
        cin >> title >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++) {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++) {
            cin >> rating;
            ratings[i] = rating;
        }
        cin >> title >> popularity >> songPopularity;


        MovieSong ok(title, performers, numberOfPerformers, ratings, numberOfRatings, title, popularity, songPopularity);
        cout << "Object of class MovieSong is created";

    } else if (type == 2) // function print in song
    {
        cout << "-----TEST print-----" << endl;
        cin >> title >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++)
        {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++)
        {
            cin >> rating;
            ratings[i] = rating;
        }

        Song k(title, performers, numberOfPerformers, ratings, numberOfRatings);
        k.print();

    } else if (type == 3) // function getTotalRating
    {
        cout << "-----TEST getTotalRating-----" << endl;
        cin >> title >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++)
        {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++)
        {
            cin >> rating;
            ratings[i] = rating;
        }

        Song k(title, performers, numberOfPerformers, ratings, numberOfRatings);
        cout << "Total rating: " << k.getTotalRating() << endl;

    } else if (type == 4) //funkcija getTotalRating vo MovieSong
    {
        cout << "-----TEST getTotalRating-----" << endl;
        cin >> title >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++)
        {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++)
        {
            cin >> rating;
            ratings[i] = rating;
        }
        cin >> title >> popularity >> songPopularity;

        MovieSong fp(title, performers, numberOfPerformers, ratings, numberOfRatings, title, popularity, songPopularity);
        cout << "Total rating: " << fp.getTotalRating() << endl;

    } else if (type == 5) //funkcija print vo MovieSong
    {
        cout << "-----TEST print -----" << endl;
        cin >> title >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++)
        {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++)
        {
            cin >> rating;
            ratings[i] = rating;
        }
        cin >> title1 >> popularity >> songPopularity;

        MovieSong fp(title, performers, numberOfPerformers, ratings, numberOfRatings, title1, popularity, songPopularity);
        fp.print();

    } else if (type == 6) //all classes
    {
        cout << "-----TEST Song and MovieSong-----" << endl;
        cin >> title >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++)
        {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++)
        {
            cin >> rating;
            ratings[i] = rating;
        }
        cin >> title >> popularity >> songPopularity;

        Song *p = new MovieSong(title, performers, numberOfPerformers, ratings, numberOfRatings, title, popularity, songPopularity);
        p->print();
        cout << "Total rating: " << p->getTotalRating() << endl;
        delete p;


    } else if (type == 7) // function average rating
    {
        cout << "-----TEST average rating-----" << endl;
        int k, opt;
        cin >> k;
        Song **pesni = new Song*[k];
        for (int j = 0; j < k; j++) {
            cin >> opt; //1 Song 2 MovieSong
            cin >> title >> numberOfPerformers;
            for (int i = 0; i < numberOfPerformers; i++)
            {
                cin >> name >> year;
                performers[i] = Person(name, year);
            }
            cin >> numberOfRatings;
            for (int i = 0; i < numberOfRatings; i++)
            {
                cin >> rating;
                ratings[i] = rating;
            }
            if (opt == 1) {
                pesni[j] = new Song(title, performers, numberOfPerformers, ratings, numberOfRatings);
            } else {
                cin >> title >> popularity >> songPopularity;
                pesni[j] = new MovieSong(title, performers, numberOfPerformers, ratings, numberOfRatings, title, popularity, songPopularity);
            }
        }

        cout << "Average rating of the songs is " << averageRating(pesni, k);
        for (int j = 0; j < k; j++) delete pesni[j];
        delete [] pesni;

    } else if (type == 8) // function print songs
    {
        cout << "-----TEST print songs-----" << endl;
        int k, opt;
        cin >> k;
        Song **pesni = new Song*[k];
        for (int j = 0; j < k; j++) {
            cin >> opt; //1 Song 2 MovieSong
            cin >> title >> numberOfPerformers;
            for (int i = 0; i < numberOfPerformers; i++)
            {
                cin >> name >> year;
                performers[i] = Person(name, year);
            }
            cin >> numberOfRatings;
            for (int i = 0; i < numberOfRatings; i++)
            {
                cin >> rating;
                ratings[i] = rating;
            }
            if (opt == 1) {
                pesni[j] = new Song(title, performers, numberOfPerformers, ratings, numberOfRatings);
            } else {
                cin >> title1 >> popularity >> songPopularity;
                pesni[j] = new MovieSong(title, performers, numberOfPerformers, ratings, numberOfRatings, title1, popularity, songPopularity);
            }
        }
        cin >> perfomer;
        cout << "Songs of " << perfomer << " are:" << endl;
        printSongs(perfomer, pesni, k);
        for (int j = 0; j < k; j++) delete pesni[j];
        delete [] pesni;

    }


    return 0;
}

