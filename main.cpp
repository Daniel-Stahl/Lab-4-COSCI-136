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

void GameMenu();

int main() {
    GameMenu();
}

void GameMenu() {
    int passes;
    int players;
    char userChoice;
    ListManager list;
    
    cout << "Welcome to Pass the Potato Game!\n";
    
    do {
        do {
            cout << "How many players?: ";
            cin >> players;
        
            cout << "\n";
        
        cout << "How many passes?: ";
        cin >> passes;
        
        cout << "\n";
            
            if (players <= 0 || passes < 0) {
                cout << "Number of players and passes must be a positive number\n";
            }
            
        } while(players <= 0 || passes < 0); // Error message
        list.CreateNode(players);
        list.PassPotato(passes);
        
        do {
            cout << "Do you want to play again? (Y/N) ";
            cin >> userChoice;
            
            if (!cin) {
                cout << "That is not a valid option, please try again.\n";
                cin.clear();
                cin.ignore(100, '\n');
            }
        } while (!cin);
    } while (userChoice == 'y' || userChoice == 'Y');
    
    
    
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
    }
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
            cout << "Player " << delNodePos << " is out!\n";
            
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



