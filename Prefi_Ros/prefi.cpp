#include <iostream>
#include <time.h>
#include <conio.h>
#include <Windows.h>

using namespace std;

struct Node
{
    string data;
    Node *next;
};
typedef Node *NodePtr;
string randomGen(string border)
{ // Generate random symbol, either $ or ., in a random position between 0 and 40
    int pos1, pos2, random, n1 = 0, n2 = 1;
    char randsym;

    random = (rand() % (n2 - n1 + 1)) + n1;
    if (random == 0)
    {
        randsym = '$';
    }
    else
    {
        randsym = '.';
    }

    pos1 = 1 + rand() % 40;
    pos2 = 1 + rand() % 40;
    while (pos1 == pos2)
    {
        pos2 = 1 + rand() % 40;
    }

    border[pos1] = randsym;
    border[pos2] = randsym;

    return border;
}
void displayList(NodePtr head)
{ // Function to display the list
    NodePtr border = head;

    while (border != NULL)
    {
        cout << border->data << endl;
        border = border->next;
    }
}
void scoreBoard(int score)
{ // Display the score and end game message (depending on the score)
    cout << "Your score: " << score << endl;

    if (score >= 100)
    {
        cout << "Yeah, you win!!" << endl;
    }
    else if (score <= 0)
    {
        cout << "Sorry, you lose..." << endl;
    }
    else
    {               // If either two above condition is not yet reached, the game will continue
        Sleep(100); // The delay of the game, or to control the speed of the game
        system("cls");
    }
}
int keyboardInput(int input, int &kbpos, const char CPPKEYLEFT, const char CPPKEYRIGHT)
{
    if (kbhit())
    { // Getting the input from a keyboard press
        input = getch();
        if (input == CPPKEYLEFT)
        {
            kbpos--;
        }
        else if (input == CPPKEYRIGHT)
        {
            kbpos++;
        }
    }
    return kbpos;
}
int main()
{
    srand(time(NULL)); // Gives random number every time
    int score = 50, kbpos = 20;
    char sym, input;
    const char CPPKEYLEFT = 75, CPPKEYRIGHT = 77; // 75 for left arrow, 77 for right arrow

    string border(42, ' '); // To generate a string with 40 characters
    border[0] = '|', border[41] = '|';

    NodePtr head; // Inserting a Node at the Beginning
    NodePtr newPtr;

    newPtr = new Node;
    newPtr->data = border;
    newPtr->next = NULL;
    head = newPtr;

    for (int i = 0; i <= 20; i++)
    { // Adding an element to the head
        NodePtr newPtr = new Node;
        newPtr->data = border;
        newPtr->next = head;
        head = newPtr;
    }

    while (score < 100 && score > 0)
    {
        cout << "------------- Falling Money --------------" << endl; // Generate header or title

        displayList(head); // Calling the function displayList

        NodePtr newPtr = new Node; // Adding an element to the head only with calling the function randomGen
        newPtr->data = randomGen(border);
        newPtr->next = head;
        head = newPtr;

        NodePtr p, q; // Deleting the Node
        p = head;
        for (int i = 0; i <= 20; i++)
        {
            if (i == 18)
                q = p->next;
            p = p->next;
        }
        string border = q->data;
        if (border[kbpos] == '.')
        { // If U is equal to the position of $ or ., score will increase or decrease depending on the symbol.
            score = score - 15;
            border[kbpos] = 'U';
        }
        else if (border[kbpos] == '$')
        {
            score = score + 10;
            border[kbpos] = 'U';
        }
        else
            border[kbpos] = 'U';
        q->data = border;
        q->next = NULL;
        delete p;
        p = NULL;

        keyboardInput(input, kbpos, CPPKEYLEFT, CPPKEYRIGHT); // Calling the function keyboardInput

        scoreBoard(score); // Calling the function scoreBoard
    }
    Sleep(100);
    system("PAUSE");
}