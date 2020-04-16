#include <string>
#include <iostream>
#include <fstream>
#include <new>

using namespace std;

struct Node {
public:
    string playerName;
    Node* next;
};

class ListManager {
private:
    Node* head;
    
public:
    void CreateNode(int numPlayers);
    void PassPotato(int numPasses);
    void DumpList();
    ~ListManager();
};


int main() {
    int passes;
    int players;
    
    ListManager list;
    
    list.CreateNode(2);
    list.PassPotato(2);
}

void ListManager::CreateNode(int numPlayers) {
    ifstream inFile;
    string name;
    head = new (std::nothrow) Node;
    
    inFile.open("/Users/stahl/Desktop/Pierce College/COSCI 136/LAB_4_STAHL_DANIEL/data.txt");
    
    if (!inFile) {
        cout << "File does not exist\n";
        exit(1);
    } else {
        cout << "File ready!\n";
    }
    
    if (!head) {
        cout << "Can't allocate memory\n";
    } else {
        inFile >> name;
        head->playerName = name;
        head->next = head;
    }
    
    while ((!inFile.eof() && numPlayers > 1) && (head)) {
        Node* newHead = new (std::nothrow) Node;
        
        inFile >> name;
        
        if (!newHead) {
            cout << "Cant allocate memory\n";
        } else {
            newHead->playerName = name;
            newHead->next = head->next;
            head->next = newHead;
            head = newHead;
        }
        
        numPlayers--;
    }
    
    inFile.close();
    cout << "\nPlayers loaded\n";
}

void ListManager::PassPotato(int numPasses) {
    Node* travList = head;
    
    cout << travList->playerName << "\n" << travList->next->playerName << "\n";
    
    
}

void ListManager::DumpList() {
    Node* current = head;
    Node* newHead;
    
    while (current != NULL) {
        newHead = current->next;
        delete current;
        current = newHead;
    
    }
}

ListManager::~ListManager() {
    DumpList();
}
