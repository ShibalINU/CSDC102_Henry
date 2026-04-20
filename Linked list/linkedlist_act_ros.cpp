#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

#include <unistd.h>
#include <termios.h>
#include <sys/select.h>


using namespace std;
//constants
const string csv_file = "playlist.csv";
const string header = "Title,Artist,Genre,Year,Duration";

//system-only functions


//clear screen
void clearScreen(){
    system("clear");
}

//a function the waits for key presses that detects keypresses without waiting for enter
static struct termios g_oldt;

void serRawMode(bool enable){
    if (enable){
        struct termios newt;
        tcgetattr(STDIN_FILENO, &g_oldt);
        newt = g_oldt;
        new.c_lflag &= ~(ICANON | ECHO);
        tcgetattr = (STDIN_FILENO, TCSANOW, &newt);
    }else{
        tcsetattr(STDIN_FILENO, TCSANOW, &g_oldt);
    }
}

bool KeyPressed(){
    struct timewal tv = {0,0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}


//helper function
string toLower(string str){
    for (int i = 0; i < (int) str.length(); i++){
        str[i] = toLower(str[i]);
    }
    return str;
}

class Song{
    public:
        string title;
        string artist;
        string genre;
        int year;
        string duration; 
        
        Song(){
            year = 0;
        }
        
        Song(string t, string a, string g, int y, string d){
            title = t;
            artist = a;
            genre = g;
            year = y;
            duration = d;
        }
        
        //conver duration into total seconds+
        int convertIntoSeconds() const{
            int colonPos = duration.find(":");
            if(colonPos == (int) string::npos){
                return 0;
            }
            return stoi(duration.substr(0, colonPos)) * 60 
                + stoi(duration.substr(colonPos + 1));
        }
    
    };

class Node{
    public:
    Song song;
    Node* next;
    Node* prev;
    
    node(Song s){
        song = s;
        next = nullptr;
        prev = nullptr;
    }
};
