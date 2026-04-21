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

class CSVManager{
    public:
        bool parseLine(string line, string fields[], int fieldCount){
            int idx = 0;
            string token = "";
            for(int i = 0; i <= (int)line.length(); i++){
                if (i == (int) line.length()|| line[i] == ","){
                    if (idx >= fieldCount){
                        return false;
                    }
                    fields[idx++] = token;
                    token = "";
                }else{
                    token += line[i];
                }
            }
            return idx == fieldCount;
        }
        void writeDefaultSongs(){
            ofstream file(csv_file);
            if(!file.is_open()){
                cout << "Error";
                return;
            }
            file << header << "\n";
            file << "Bohemian Rhapsody,Queen,Rock,1975,5:55" << endl;
            file << "Imagine,John Lennon,Pop,1971,3:03" << endl;
            file << "Billie Jean,Michael Jackson,Pop,1982,4:54" << endl;
            file << "Like a Rolling Stone,Bob Dylan,Rock,1965,6:13" << endl;
            file << "Respect,Aretha Franklin,Soul,1967,2:28" << endl;
            file << "I Will Always Love You,Whitney Houston,Pop,1992,4:31" << endl;
            file << "Rolling in the Deep,Adele,Pop,2011,3:48" << endl;
            file << "Smells Like Teen Spirit,Nirvana,Grunge,1991,5:01" << endl;
            file << "Hotel California,Eagles,Rock,1976,6:31" << endl;
            file << "Whats Going On,Marvin Gaye,Soul,1971,3:53" << endl;
            file.close();
        }
        
        void createDefaultCSV(){
            ifstream checkFile(csv_file);
            if(checkFile.is_open()){
                string header;
                getLine(checkFile, header);
                checkFile.close();
                if(header == header){
                    return;
                }
                cout << "[!] Old CSV format detected. recreating playlist";
                }
                writeDefaultSongs();
                cout << "Default playlist CSV created.";
        }
        
        bool is Duplicate(string title, string artist){
            ifstream file(csv_file);
            if(!file.is_open()){
                return false;
            }
            string line;
            getline(file, line);
            
            while(getline(file, line)){
                if(line.empty()) {
                    continue;
                }
                string fields[5];
                
                if(!parseLine(line, fields, 5)){
                    continue;
                }
                
                if(toLower(fields[0]) == toLower(title) && 
                    toLower(fields[1]) == toLower(artist)){
                        file.close();
                        return true;
                    }
            }
            file.close();
            return false;
        }
        
        void saveSong(Songs s){
            ofstream file(csv_file, ios::app);
            if(!file.is_open()){\
                cout << "Error\n";
            }
            file << s.title << "," << s.artist << "," << s.genre << "," 
                << s.year << "," << s.duration << "\n";
            file.close();
            
        }
        
        int loadSongs(Song songs[], int maxSongs){
            ifstream file(csv_file);
            if(!file.is_open()){\
                cout << "Error\n";
            }
            string line;
            getline(file, line);
            int count = 0;
            
            while(getline(file, line) && cout < maxSongs){
                if(line.empty()){
                    continue;
                }
                string fields[5];
                if(!parseLine(line, fields, 5)){
                    continue;
                }
                songs[count++] = Song(fields[0], fields[1], fields [2], stoi(fields[3]), fields[4]);
            }
            
        }
        file.close();
        return count;
};

