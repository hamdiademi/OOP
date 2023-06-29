//
// Created by Hamdi on 5/23/2023.
//

#include<iostream>
#include<cstring>
using namespace std;

class UserAlreadyExistsException {
    char username[50];
public:
    UserAlreadyExistsException(char *username){
        strcpy(this->username,username);
    }

    void showMessage(){
        cout<<"User with username "<< username <<" already exists!"<<endl;
    }
};

class UserNotFoundException {
    char username[50];
public:
    UserNotFoundException(char *username){
        strcpy(this->username,username);
    }

    void showMessage(){
        cout<<"User with username "<< username<<" was not found!"<<endl;
    }
};

class FriendsLimitExceededException {
    int limit;
public:
     FriendsLimitExceededException(int limit) : limit(limit) {}

    void showMessage(){
        cout<<"Can't have more than "<< limit <<" friends."<<endl;
    }
};

class User {
private:
    char username[50];
    int age;
    int friends;
    static int limit;
public:
    User(char *username = "", int age = 18) : age(age) {
        strcpy(this->username, username);
        friends = 0;
    }

    friend ostream &operator<<(ostream &os, const User &user) {
        os << "Username: " << user.username << " Age: " << user.age << " # of friends: " << user.friends;
        return os;
    }

    User &operator++() {
        if(friends >= limit){
            --friends;
            throw FriendsLimitExceededException(limit);


        } else {
            ++friends;
            return *this;
        }

    }

    friend class SocialNetwork;


    static void setLimit(int friends) {
        limit=friends;
    }
};
int User::limit=3;

class SocialNetwork {
private:
    User *users;
    int n;
public:
    SocialNetwork() {
        n = 0;
        users = new User[n];
    }

    SocialNetwork &operator+=(User &u) {
        for (int i = 0; i < n; ++i) {
            if(strcmp(users[i].username,u.username)==0){
                throw UserAlreadyExistsException(users[i].username);
            }
        }

        User *tmp = new User[n + 1];
        for (int i = 0; i < n; i++) {
            tmp[i] = users[i];
        }
        tmp[n++] = u;
        delete[] users;
        users = tmp;
        return *this;

    }

    void friendRequest(char *firstUsername, char *secondUsername) {
        int flag1=1,flag2=1;
        for (int i = 0; i < n; i++) {
            if (strcmp(users[i].username, firstUsername) == 0) {
                flag1=0;
                for (int j = 0; j < n; j++) {
                    if (strcmp(users[j].username, secondUsername) == 0) {
                        flag2=0;
                        if (users[i].friends<User::limit && users[j].friends<User::limit){
                            ++users[i];
                            ++users[j];
                        }
                        else
                            throw FriendsLimitExceededException(User::limit);
                        return;
                    }
                }
            }
        }
        if (flag2)
        {
            throw UserNotFoundException(secondUsername);
        }
        else if (flag1)
        {
            throw UserNotFoundException(firstUsername);
        }
    }
//
//    void friendRequest(char *firstUsername, char *secondUsername) {
//        int flag1=1,flag2=1;
//        for (int i = 0; i < n; i++) {
//            if (strcmp(users[i].username, firstUsername) == 0) {
//                flag1=0;
//                for (int j = 0; j < n; j++) {
//                    if (strcmp(users[j].username, secondUsername) == 0) {
//                        flag2=0;
//                        ++users[i];
//                        ++users[j];
//                        return;
//                    }
//                }
//            }
//        }
//        if (flag1){
//            throw UserNotFoundException(firstUsername);
//        } else if (flag2){
//            throw UserNotFoundException(secondUsername);
//        }
//
//
//
//    }

    friend ostream &operator<<(ostream &os, const SocialNetwork &network) {
        os << "Users: " << endl;
        for (int i=0;i<network.n;i++) {
            os << network. users[i] << endl;
        }
        return os;
    }
};


int main() {
    SocialNetwork sn;
    int n;
    cin >> n;
    for (int i=0;i<n;i++){
        char username[50]; int age;
        cin >> username >> age;

        try {
            User u(username, age);
            sn += u;
        } catch (UserAlreadyExistsException &e) {
            e.showMessage();
        }


    }

    cout << "Registration of users " << endl;
    cout << sn << endl;
    cout << "Friend requests " << endl;

    int friendships;
    cin >> friendships;
    for (int i=0;i<friendships;i++){
        char username1[50], username2[50];
        try {
            try {

                cin >> username1 >> username2;
                sn.friendRequest(username1, username2);
            } catch (UserNotFoundException &e) {
                e.showMessage();
            }
        }catch (FriendsLimitExceededException &e){
            e.showMessage();

        }
    }

    cout << sn << endl;

    cout << "CHANGE STATIC VALUE" << endl;

    int maxFriends;
    cin >> maxFriends;
    cin >> friendships;
    User::setLimit(maxFriends);
    for (int i=0;i<friendships;i++){
        char username1[50], username2[50];
        try {
            try {

                cin >> username1 >> username2;
                sn.friendRequest(username1, username2);
            } catch (UserNotFoundException &e) {
                e.showMessage();
            }
        }catch (FriendsLimitExceededException &e){
            e.showMessage();

        }

    }
    cout << sn;
    return 0;
}