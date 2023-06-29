// Created by Hamdi on 3/29/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class ExistingPodcast{
public:
    void message(){
        cout<<"The podcast is already in the collection"<<endl;
    }
};

class Podcast{
protected:
    char name[100];
    char url[1000];
    float price;
    int discount;
public:
    Podcast(char *name="", char *url="", float price=0, int discount=0) :  price(price),discount(discount) {
        strcpy(this->name,name);
        strcpy(this->url,url);
    }
     virtual float get_price(){
        return price * (1.0 - (this->discount/100.0));
    }

    friend ostream &operator<<(ostream &os, const Podcast &podcast) {
        os << "Podcast: "<<podcast.name << "\nURL: " << podcast.url << "\nregular price: $" << podcast.price;
        if (podcast.discount){
            os<<", bought on discount";
        }
        return os;
    }
    friend istream &operator>>(istream &in, Podcast &p){
        in.get();
        in.getline(p.name,100);
        in.getline(p.url,100);
        in>>p.price>>p.discount;
        return in;
    }

    bool operator==(const Podcast &rhs) const {
        return !strcmp(url,rhs.url);
    }
    friend class Playlist;

};
class StreamingPodcast: public Podcast{
protected:
    float monthlyFee;
    int month;
    int year;
public:
    StreamingPodcast(){}
    StreamingPodcast(char *name, char *url, float price, int discount, float monthlyFee=0, int month=0, int year=0) : Podcast(
            name, url, price, discount), monthlyFee(monthlyFee), month(month), year(year) {}


     float get_price() override{
        float p = Podcast::get_price();

        int months=0;
        if (year<2018){
            month = (12 - this->month) + (2017 - year)*12 + 5;
        }
        else {
            months = 5 - this->month;
        }

        p += months * monthlyFee;

        return p;
    }

    friend ostream &operator<<(ostream &os, const StreamingPodcast &podcast) {
        os << static_cast<const Podcast &>(podcast) << ", monthly fee: $" << podcast.monthlyFee << ", purchased: "<< podcast.month << "-"<< podcast.year<<endl;
        return os;
    }

    friend istream &operator>>(istream &in, StreamingPodcast &sp) {
        in.get();
        in.getline(sp.name,100);
        in.getline(sp.url,100);
        in>>sp.price>>sp.discount;
        in>>sp.monthlyFee>>sp.month>>sp.year;

        return in;
    }

    friend class Playlist;
};

class Playlist {
protected:
    char name[100];
    Podcast** podcasts;
    int n;
private:
    void copy(const Playlist &other){
        strcpy(this->name,other.name);
        this->n=other.n;
        this->podcasts=new Podcast*[other.n];
        for (int i = 0; i < n; ++i) {
            this->podcasts[i]=new Podcast(*other.podcasts[i]);
        }
    }
public:
    Playlist(char *name) {
        strcpy(this->name,name);
        this->n=0;
        podcasts= nullptr;
    }
    Playlist(const Playlist &other){
        copy(other);
    }
    Playlist &operator=(const Playlist &other){
        if (this!=&other){
            delete[]podcasts;
            copy(other);
        }
        return *this;
    }
    ~Playlist(){
        delete[] podcasts;
    }
    Playlist &operator+=(Podcast &p){
        for (int i = 0; i < n; ++i) {
            if (!strcmp(podcasts[i]->name,p.name)){
                throw ExistingPodcast();
            }
        }
        Podcast **tmp=new Podcast*[n+1];
        for (int i = 0; i < n; ++i) {
            tmp[i]=podcasts[i];
        }
        tmp[n]=&p;
        n++;
        delete[]podcasts;
        podcasts=tmp;

        return *this;
    }

    double total_spent() {
        double sum=0;
        for (int i = 0; i < n; ++i) {
            sum += podcasts[i]->get_price();
        }
        return sum;
    }

    friend ostream &operator<<(ostream &os,   Playlist &ps) {
        os<<"\nPlaylist: "<<ps.name<<endl;
        for (int i = 0; i < ps.n; ++i) {
            Podcast * g;
            StreamingPodcast * sg;
            g = &(*ps.podcasts[i]);

            sg = dynamic_cast<StreamingPodcast *> (g);
            if (sg){
                cout<<(*sg);
            }
            else {
                cout<<(*g);
            }
            cout<<"\n";
        }
        return os;
        }





};


int main() {
    int test_case_num;

    cin>>test_case_num;

    // for Podcast
    char podcast_name[100];
    char podcast_url[1000];
    float podcast_price;
    int podcast_discount;

    // for StreamingPodcast
    float sub_podcast_monthly_fee;
    int sub_podcast_month, sub_podcast_year;

    // for Playlist
    char name[100];
    int num_podcasts_in_playlist;

    if (test_case_num == 1){
        cout<<"Testing class Podcast and operator&lt;&lt; for Podcast"<<std::endl;
        cin.get();
        cin.getline(podcast_name,100);
        cin.getline(podcast_url, 1000);
        //cin.get();
        cin>>podcast_price>>podcast_discount;

        Podcast p(podcast_name, podcast_url, podcast_price, podcast_discount);

        cout<<p;
    }
    else if (test_case_num == 2){
        cout<<"Testing class StreamingPodcast and operator&lt;&lt; for StreamingPodcast"<<std::endl;
        cin.get();
        cin.getline(podcast_name,100);
        cin.getline(podcast_url, 1000);
        //cin.get();
        cin>>podcast_price>>podcast_discount;

        cin>>sub_podcast_monthly_fee;
        cin>>sub_podcast_month>>sub_podcast_year;

        StreamingPodcast sp(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
        cout<<sp;
    }
    else if (test_case_num == 3){
        cout<<"Testing operator&gt;&gt; for Podcast"<<std::endl;
        Podcast p;

        cin>>p;

        cout<<p;
    }
    else if (test_case_num == 4){
        cout<<"Testing operator&gt;&gt; for StreamingPodcast"<<std::endl;
        StreamingPodcast sp;

        cin>>sp;

        cout<<sp;
    }
    else if (test_case_num == 5){
        cout<<"Testing class Playlist and operator+= for Playlist"<<std::endl;
        cin.get();
        cin.getline(name,100);
        Playlist u(name);

        int num_user_podcasts;
        int podcast_type;
        cin >>num_user_podcasts;

        try {

            for (int i=0; i<num_user_podcasts; ++i){

                cin >> podcast_type;

                Podcast *g;
                // 1 - Game, 2 - SubscriptionGame
                if (podcast_type == 1){
                    cin.get();
                    cin.getline(podcast_name, 100);
                    cin.getline(podcast_url, 1000);

                    cin>>podcast_price>>podcast_discount;
                    g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
                }
                else if (podcast_type == 2){
                    cin.get();
                    cin.getline(podcast_name, 100);
                    cin.getline(podcast_url, 1000);

                    cin>>podcast_price>>podcast_discount;

                    cin>>sub_podcast_monthly_fee;
                    cin>>sub_podcast_month>>sub_podcast_year;
                    g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
                }

                //cout<<(*g);


                u+=(*g);
            }
        }catch(ExistingPodcast &ex){
            ex.message();
        }

        cout<<u;

    }
    else if (test_case_num == 6){
        cout<<"Testing exception ExistingPodcast for Playlist"<<std::endl;
        cin.get();
        cin.getline(name,100);
        Playlist u(name);

        int num_podcasts_in_playlist;
        int podcast_type;
        cin >>num_podcasts_in_playlist;

        for (int i=0; i<num_podcasts_in_playlist; ++i){

            cin >> podcast_type;

            Podcast *g;
            // 1 - Game, 2 - SubscriptionGame
            if (podcast_type == 1){
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin>>podcast_price>>podcast_discount;
                g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
            }
            else if (podcast_type == 2){
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin>>podcast_price>>podcast_discount;

                cin>>sub_podcast_monthly_fee;
                cin>>sub_podcast_month>>sub_podcast_year;
                g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);

            }
            catch(ExistingPodcast &ex){
                ex.message();
            }
        }
        cout<<u;


    }
    else if (test_case_num == 7){
        cout<<"Testing total_spent method() for Playlist"<<std::endl;
        cin.get();
        cin.getline(name,100);
        Playlist u(name);

        int num_podcasts_in_playlist;
        int podcast_type;
        cin >>num_podcasts_in_playlist;

        for (int i=0; i<num_podcasts_in_playlist; ++i){

            cin >> podcast_type;

            Podcast *g;
            // 1 - Game, 2 - SubscriptionGame
            if (podcast_type == 1){
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin>>podcast_price>>podcast_discount;
                g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
            }
            else if (podcast_type == 2){
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin>>podcast_price>>podcast_discount;

                cin>>sub_podcast_monthly_fee;
                cin>>sub_podcast_month>>sub_podcast_year;
                g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);
            }
            catch(ExistingPodcast &ex){
                ex.message();
            }
        }

        cout<<u;

        cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }
    return 0;
}
