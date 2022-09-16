#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <sstream>

#define W 0x57
#define A 0x41
#define S 0x53
#define D 0x44
#define ESC 0x1B
#define left 0x25
#define up 0x26
#define down 0x28
#define right 0x27

using namespace std;

string map[4][4] = {
    {" ", " ", " ", " "},
    {" ", " ", " ", " "},
    {" ", " ", " ", " "},
    {" ", " ", " ", " "}};

void move(char key) {
    if(key=='W') {
        for(int i=0; i<3; i++) {
            for(int y=1; y<4; y++) {
                for(int x=0; x<4; x++) {
                    if(map[y][x]!=" ") {
                        if(map[y-1][x]==" ") {
                            map[y-1][x] = map[y][x];
                            map[y][x] = " ";
                        }
                        if(map[y-1][x]==map[y][x]) {
                            unsigned int num;
                            istringstream(map[y][x]) >> num;
                            map[y-1][x] = to_string(2*num);
                            map[y][x] = " ";
                        }
                    }
                }
            }
        }
        return;
    }
    if(key=='A') {
        for(int i=0; i<3; i++) {
            for(int x=1; x<4; x++) {
                for(int y=0; y<4; y++) {
                    if(map[y][x]!=" ") {
                        if(map[y][x-1]==" ") {
                            map[y][x-1] = map[y][x];
                            map[y][x] = " ";
                        }
                        if(map[y][x-1]==map[y][x]) {
                            unsigned int num;
                            istringstream(map[y][x]) >> num;
                            map[y][x-1] = to_string(2*num);
                            map[y][x] = " ";
                        }
                    }
                }
            }
        }
        return;
    }
    if(key=='S') {
        for(int i=0; i<3; i++) {
            for(int y=2; y>=0; y--) {
                for(int x=0; x<4; x++) {
                    if(map[y][x]!=" ") {
                        if(map[y+1][x]==" ") {
                            map[y+1][x] = map[y][x];
                            map[y][x] = " ";
                        }
                        if(map[y+1][x]==map[y][x]) {
                            unsigned int num;
                            istringstream(map[y][x]) >> num;
                            map[y+1][x] = to_string(2*num);
                            map[y][x] = " ";
                        }
                    }
                }
            }
        }
        return;
    }
    if(key=='D') {
        for(int i=0; i<3; i++) {
            for(int x=2; x>=0; x--) {
                for(int y=0; y<4; y++) {
                    if(map[y][x]!=" ") {
                        if(map[y][x+1]==" ") {
                            map[y][x+1] = map[y][x];
                            map[y][x] = " ";
                        }
                        if(map[y][x+1]==map[y][x]) {
                            unsigned int num;
                            istringstream(map[y][x]) >> num;
                            map[y][x+1] = to_string(2*num);
                            map[y][x] = " ";
                        }
                    }
                }
            }
        }
        return;
    }
}

void spawnNum() {
    unsigned int num;
    unsigned int x;
    unsigned int y;
    bool isspace=false;
    for(int x=0; x<4; x++) {
        for(int y=0; y<4; y++) {
            if(map[y][x]==" ") {
                isspace=true;
                break;
            }
        }
    }
    while(isspace) {
        num = rand()%2;
        x=rand()%4;
        y=rand()%4;
        if(num==0) {
            if(map[y][x]==" ") {
                map[y][x]="2";
                return;
            }
        }
        if(num==1) {
            if(map[y][x]==" ") {
                map[y][x]="4";
                return;
            }
        }
    }
}

bool checkForLoss() {
    for(int y=0; y<4; y++) {
        for(int x=0; x<4; x++) {
            if((x==0&&(y==0||y==3))||(x==3&&(y==0||y==3))) {
                if(x==0&&y==0) {
                    if(!(map[y+1][x]!=map[y][x]&&map[y][x+1]!=map[y][x]&&map[y+1][x]!=" "&&map[y][x+1]!=" "&&map[y+1][x+1]!=" ")) {
                        return false;
                    }
                }
                if(x==0&&y==3) {
                    if(!(map[y-1][x]!=map[y][x]&&map[y][x+1]!=map[y][x]&&map[y-1][x]!=" "&&map[y][x+1]!=" "&&map[y-1][x+1]!=" ")) {
                        return false;
                    }
                }
                if(x==3&&y==0) {
                    if(!(map[y][x-1]!=map[y][x]&&map[y+1][x]!=map[y][x]&&map[y][x-1]!=" "&&map[y+1][x]!=" "&&map[y+1][x-1]!=" ")) {
                        return false;
                    }
                }
                if(x==3&&y==3) {
                    if(!(map[y][x-1]!=map[y][x]&&map[y-1][x]!=map[y][x]&&map[y-1][x]!= " "&&map[y][x-1]!=" "&&map[y-1][x-1]!=" ")) {
                        return false;
                    }
                }
            }
            else {
                if((x==0&&(y!=0&&y!=3))||(x==3&&(y!=0&&y!=3))||(y==0&&(x!=0&&x!=3))||(y==3&&(x!=0&&x!=3))) {
                    if(x==0&&(y!=0&&y!=3)) {
                        if(!(map[y-1][x]!=map[y][x]&&map[y+1][x]!=map[y][x]&&map[y][x+1]!=map[y][x]&&map[y-1][x]!=" "&&map[y+1][x]!=" "&&map[y][x+1]!=" ")) {
                            return false;
                        }
                    }
                    if(x==3&&(y!=0&&y!=3)) {
                        if(!(map[y-1][x]!=map[y][x]&&map[y+1][x]!=map[y][x]&&map[y][x-1]!=map[y][x]&&map[y-1][x]!=" "&&map[y+1][x]!=" "&&map[y][x-1]!=" ")) {
                            return false;
                        }
                    }
                    if(y==0&&(x!=0&&x!=3)) {
                        if(!(map[y][x-1]!=map[y][x]&&map[y][x+1]!=map[y][x]&&map[y+1][x]!=map[y][x]&&map[y][x-1]!=" "&&map[y][x+1]!=" "&&map[y+1][x]!=" ")) {
                            return false;
                        }
                    }
                    if(y==3&&(x!=0&&x!=3)) {
                        if(!(map[y][x-1]!=map[y][x]&&map[y][x+1]!=map[y][x]&&map[y-1][x]!=map[y][x]&&map[y][x-1]!=" "&&map[y][x+1]!=" "&&map[y-1][x]!=" ")) {
                            return false;
                        }
                    }
                }
                else {
                    if(!(map[y-1][x]!=map[y][x]&&map[y+1][x]!=map[y][x]&&map[y][x+1]!=map[y][x]&&map[y][x-1]!=map[y][x]&&map[y-1][x]!=" "&&map[y+1][x]!=" "&&map[y][x+1]!=" "&&map[y][x-1]!=" ")) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void printmap() {
    cout << "+------------------------------------+" << endl;
    int num;
    for(int y=0; y<4; y++) {
        cout<<'|';
        for(int x=0; x<4; x++) {
            if(map[y][x]!=" ") {
                istringstream(map[y][x]) >> num;
                if(num>=0 && num < 10) {
                    cout << "    " << map[y][x] << "    ";
                }
                if(num>=10 && num < 100) {
                    cout << "   " << map[y][x] << "    ";
                }
                if(num>=100 && num < 1000) {
                    cout << "   " << map[y][x] << "   ";
                }
                if(num>=1000 && num < 10000) {
                    cout << "  " << map[y][x] << "   ";
                }
                if(num>=10000 && num < 100000) {
                    cout << "  " << map[y][x] << "  ";
                }
            }
            else {cout << "         ";}
        }
        cout<<"|"<<endl;
    }
    cout << "+------------------------------------+" << endl;
}

int main() {
    srand(time(0));
    map[rand()%4][rand()%4]="2";
    map[rand()%4][rand()%4]="2";
    bool loss=false;
    printmap();
    while(!loss&&!GetAsyncKeyState(ESC)) {
        if(GetAsyncKeyState(W)||GetAsyncKeyState(up)) {
            move('W');
            system("cls");
            spawnNum();
            printmap();
        }
        if(GetAsyncKeyState(A)||GetAsyncKeyState(left)) {
            move('A');
            system("cls");
            spawnNum();
            printmap();
        }
        if(GetAsyncKeyState(S)||GetAsyncKeyState(down)) {
            move('S');
            system("cls");
            spawnNum();
            printmap();
        }
        if(GetAsyncKeyState(D)||GetAsyncKeyState(right)) {
            move('D');
            system("cls");
            spawnNum();
            printmap();
        }
        loss = checkForLoss();
        Sleep(500);
    }
    unsigned int score=0;
    unsigned int num;
    for(int y=0; y<4; y++) {
        for(int x=0; x<4; x++) {
            istringstream(map[y][x]) >> num;
            if(num>score) {
                score = num;
            }
        }
    }
    system("cls");
    cout << "Score: " << score << endl;
    cout << "You Lost" << endl << "Feels Bad" << endl;
    Sleep(1000);
    system("pause");
}