#include <string>
#include <iostream>
#include <fstream>
#include <new>

using namespace std;

struct Node {
public:
    int playerNum;
    Node* next;
};

class ListManager {
private:
    Node* head;
    
public:
    void CreateNode(int numPlayers);
    void PassPotato(int numPasses);
    void DeleteNode(Node*& nodeRef);
    void DumpList();
    ~ListManager();
};


int main() {
    int passes;
    int players;
    
    ListManager list;
    
    list.CreateNode(5);
    list.PassPotato(1);
}

void ListManager::CreateNode(int numPlayers) {
    ifstream inFile;
    int num;
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
        inFile >> num;
        head->playerNum = num;
        head->next = head;
    }
    
    while ((!inFile.eof() && numPlayers > 1) && (head)) {
        Node* newHead = new (std::nothrow) Node;
        
        inFile >> num;
        
        if (!newHead) {
            cout << "Cant allocate memory\n";
        } else {
            newHead->playerNum = num;
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
    Node* next;
    Node* prev;
    int delNodePos;
    
    while (travList != travList->next) {
        for (int x = 0; x <= numPasses; ++x) {
            next = travList->next;
            prev = travList;
            travList = next;
        }
        
        if (travList != prev) {
            delNodePos = travList->playerNum;
            cout << "Delete: Player " << delNodePos << "\n";
            
            DeleteNode(prev);
        }
    }
    
    cout << "Winner is: Player " << travList->playerNum << "\n";
}

void ListManager::DeleteNode(Node*& nodeRef) {
    Node* temp = nodeRef;
    Node* deleteNode = temp->next;
    temp->next = deleteNode->next;
    
    if (deleteNode == head) {
        head = temp->next;
    }
    
    delete deleteNode;
}

void ListManager::DumpList() {
    Node* current = head;
    Node* nextNode;

    while (current != current->next) {
        nextNode = current->next;
        current->next = nextNode->next;
        
        delete nextNode;
    }

    delete current;
}

ListManager::~ListManager() {
    DumpList();
}



