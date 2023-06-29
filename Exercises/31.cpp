//
// Created by Hamdi on 6/7/2023.
//
#include<iostream>
#include<cstring>

using namespace std;

class MediaSegment{
protected:
    char title[100];
    char author[100];
    int duration;
    int size;
public:
    MediaSegment(char *title="", char *author="", int duration=0, int size=0) :  duration(duration),size(size) {
        strcpy(this->title,title);
        strcpy(this->author,author);
    }

    friend ostream &operator<<(ostream &os, const MediaSegment &segment) {
        os  << segment.title << " - " << segment.author << " - " << segment.duration
           << " - " << segment.size<<" - ";
        return os;
    }
    virtual float price()const =0;

    const char *getTitle() const {
        return title;
    }

    const char *getAuthor()  {
        return author;
    }

    int getDuration() const {
        return duration;
    }
};
class AudioRecording: virtual public MediaSegment{
protected:
    int format;//0,1,2,3
    short noChanels;
public:
    AudioRecording(char *title, char *author, int duration, int size, int format=0, short noChanels=0) :
    MediaSegment(title,author,duration,size),
    format(format),noChanels(noChanels) {}

    float price()const{
        float total = duration*noChanels;
        if(format==3){
            total+=total*0.5;
        }
        return total;
    }

    friend ostream &operator<<(ostream &os, const AudioRecording &recording) {
        os << static_cast<const MediaSegment &>(recording);
        os<<recording.price()<<endl;
        return os;
    }
};
class VideoRecording: virtual public  MediaSegment{
protected:
    int width;
    int compresion;
public:
    VideoRecording( int width, int compresion):width(width),compresion(compresion){}

    VideoRecording(char *title, char *author, int duration, int size, int width, int compresion) :
    MediaSegment(title,author,duration,size),
    width(width),compresion(compresion) {}

    float price()const{
        float total;
        if (width<=1920){
            total=100*(duration*60); //!!! if duration second remove *60
        }
         if (width>1920){
            total=170*(duration*60);//!
        }
        if (compresion==0){
            total+=total*0.5;
        }
         if(compresion==1){
            total-=total*0.1;
        }
        return total;
    }

    friend ostream &operator<<(ostream &os, const VideoRecording &recording) {
        os << static_cast<const MediaSegment &>(recording);
        os<<recording.width<<" - "<<recording.price(); ///dimension??
        return os;
    }
};
class MusicVideo:  AudioRecording,public VideoRecording {
protected:
    char date[9];
public:
    MusicVideo(char *title, char *author, int duration, int size, int format, short noChanels, int width, int compresion, char *date) :
    AudioRecording(title,author,duration,size,format,noChanels),
    VideoRecording(width,compresion)
    {strcpy(this->date,date);}
    int year()const{
        int y=0;
        for (int i = 4; i < 8; ++i) {
            y*=10;
            y+=i;
        }
        return y;
    }

    float price()const{
        float total=AudioRecording::price()+VideoRecording::price();
        if (year()>2010){
            total+=total*0.3;
        }
        return total;
    }

    friend ostream &operator<<(ostream &os, const MusicVideo &video) {
        ///
        return os;
    }
};


float total_price(MediaSegment **pSegment, int n) {
    float total=0;
    for (int i = 0; i < n; ++i) {
        total+=pSegment[i]->price();
    }
    return total;
}


MediaSegment &cheapest_music_video(MediaSegment **pSegment, int n) {
    float min;
    int flag=1,index=-1;
    for (int i = 0; i < n; ++i) {
        MusicVideo *mv=dynamic_cast<MusicVideo *>(pSegment[i]);

        if (mv){
            if(flag){
                min=pSegment[i]->price();
                flag=0;
            }
            else if(pSegment[i]->price()<min){
                min=pSegment[i]->price();
                index=i;
            }
        }

    }
    return *pSegment[index];
}

int main() {

    int test_case_num;
    cin >> test_case_num;


    // for MediaSegment
    char title[100];
    char author[1000];
    unsigned int size;
    unsigned int duration;


    // for AudioRecording
    //-------------------
    unsigned short channels;

    // AudioFormat:
    // 0 - mp3
    // 1 - wav
    // 2 - ogg
    // 3 - flac
    unsigned short format;


    // for VideoRecording
    //-------------------
    unsigned short width;

    // VideoCompression:
    // 0 - x264
    // 1 - Theora
    // 2 - AV1
    int compression;


    // for MusicVideo
    //-------------------
    char publication_date[9];


    if (test_case_num == 1) {
        cout << "Testing class AudioRecording and operator<<" << std::endl;
        cin.get();
        cin.getline(title, 100);
        cin.getline(author, 100);
        //cin.get();
        cin >> duration >> size;
        cin >> format >> channels;

        AudioRecording a(title, author, duration, size, format, channels);

        cout << a;

    } else if (test_case_num == 2) {
        cout << "Testing class VideoRecording and operator<<" << std::endl;
        cin.get();
        cin.getline(title, 100);
        cin.getline(author, 100);
        //cin.get();
        cin >> duration >> size;
        cin >> width >> compression;

        VideoRecording v(title, author, duration, size, width, compression);

        cout << v;

    } else if (test_case_num == 3) {
        cout << "Testing class MusicVideo and operator<<" << std::endl;

        cin.get();
        cin.getline(title, 100);
        cin.getline(author, 100);
        //cin.get();
        cin >> duration >> size;

        cin >> format >> channels;
        cin >> width >> compression;

        cin.get();
        cin.getline(publication_date, 9);
        MusicVideo mv(title, author, duration, size, format, channels, width, compression, publication_date);

        cout << mv;
    } else if (test_case_num == 4) {
        cout << "Testing function: total_price " << std::endl;

        MediaSegment **m;

        int num_media_segments;
        cin >> num_media_segments;

        // 1 - AudioRecording
        // 2 - VideoRecording
        // 3 - MusicVideo
        short media_type;

        m = new MediaSegment *[num_media_segments];

        for (int i = 0; i < num_media_segments; i++) {

            cin >> media_type;

            cin.get();
            cin.getline(title, 100);
            cin.getline(author, 100);
            //cin.get();
            cin >> duration >> size;

            switch (media_type) {
                case 1:
                    cin >> format >> channels;
                    m[i] = new AudioRecording(title, author, duration, size, format, channels);
                    break;
                case 2:
                    cin >> width >> compression;
                    m[i] = new VideoRecording(title, author, duration, size, width, compression);
                    break;
                case 3:
                    cin >> format >> channels;
                    cin >> width >> compression;
                    cin.get();
                    cin.getline(publication_date, 9);
                    m[i] = new MusicVideo(title, author, duration, size, format, channels, width, compression,
                                          publication_date);
                    break;
            }
        }

        //for (int i=0;i<num_media_segments; i++){
        //    cout << *m[i];
        //}

        cout << "Total price is: " << total_price(m, num_media_segments);

        delete[] m;

    } else if (test_case_num == 5) {
        cout << "Testing function: cheapest_music_video " << std::endl;

        MediaSegment **m;

        int num_media_segments;
        cin >> num_media_segments;

        // 1 - AudioRecording
        // 2 - VideoRecording
        // 3 - MusicVideo
        short media_type;

        m = new MediaSegment *[num_media_segments];

        for (int i = 0; i < num_media_segments; i++) {

            cin >> media_type;

            cin.get();
            cin.getline(title, 100);
            cin.getline(author, 100);
            //cin.get();
            cin >> duration >> size;

            switch (media_type) {
                case 1:
                    cin >> format >> channels;
                    m[i] = new AudioRecording(title, author, duration, size, format, channels);
                    break;
                case 2:
                    cin >> width >> compression;
                    m[i] = new VideoRecording(title, author, duration, size, width, compression);
                    break;
                case 3:
                    cin >> format >> channels;
                    cin >> width >> compression;
                    cin.get();
                    cin.getline(publication_date, 9);
                    m[i] = new MusicVideo(title, author, duration, size, format, channels, width, compression,
                                          publication_date);
                    break;
            }
        }

        cout << cheapest_music_video(m, num_media_segments);

        delete[] m;
    }

    return 0;
}