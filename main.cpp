#include <string>
#include <iostream>
#include <fstream>
#include <new>

using namespace std;

class Node {
public:
    string playerName;
    Node* head;
    Node* next;
    Node* prev;
    
    void CreatePlayers(int numPlayers);
    void PassPotato(int numPasses);
    void EmptyList();
    ~Node();
    
    
};

int main() {
    int passes;
    int players;
    
    Node hotPotato;
    
    hotPotato.CreatePlayers(4);
    hotPotato.PassPotato(3);
}

void Node::CreatePlayers(int numPlayers) {
    ifstream inFile;
    string name;
    Node* firstHead = new (std::nothrow) Node;
    
    inFile.open("/Users/stahl/Desktop/Pierce College/COSCI 136/LAB_4_STAHL_DANIEL/data.txt");
    
    if (!inFile) {
        cout << "File does not exist\n";
        exit(1);
    } else {
        cout << "File ready!\n";
    }
    
    while ((!inFile.eof() && numPlayers > 0) || (!firstHead)) {
        Node* newHead = new (std::nothrow) Node;
        
        inFile >> name;
        
        if (firstHead == nullptr) {
            firstHead->playerName = name;
            firstHead->next = firstHead;
            head = firstHead;
        } else if (!newHead) {
            cout << "Cant allocate memory\n";
        } else {
            newHead->playerName = name;
            newHead->next = firstHead->next;
            firstHead->next = newHead;
            head = newHead;
        }
        
        numPlayers--;
    }
    
    inFile.close();
    cout << "\nPlayers loaded\n";
}

void Node::PassPotato(int numPasses) {
    Node* travList = head;
    
    while (travList != nullptr) {
        cout << travList->playerName << "\n";
        travList = travList->next;
    }
}

void Node::EmptyList() {
    Node* oldHead = head;
    Node* newHead;
    
    while (oldHead != nullptr) {
        newHead = oldHead->next;
        delete oldHead;
        oldHead = newHead;
    }
}

Node::~Node() {
    EmptyList();
}
