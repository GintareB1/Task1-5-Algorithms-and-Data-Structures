#include <iostream>
#include <fstream>
#include <string>

struct Node {
    std::string content;
    Node* yes;
    Node* no;

    Node(const std::string& c) : content(c), yes(nullptr), no(nullptr) {}
};

Node* loadTree(const std::string& filename);
Node* loadTreeHelper(std::ifstream& inFile);
void saveTree(Node* root, const std::string& filename);
void saveTreeHelper(Node* node, std::ofstream& outFile);
void deleteTree(Node* node);
void playGame(Node* root);
void addKnowledge(Node* node);
void displayMenu();


int main() {
    std::string filename = "data.txt";
    Node* root = loadTree(filename);
    
    if (!root) {
        root = new Node("Is it an animal?");
        root->yes = new Node("a mammal");
        root->no = new Node("a reptile");
    }

    bool playing = true;
    while (playing) {
        playGame(root);

        std::cout << "Do you want to play again? (yes/no): ";
        std::string answer;
        std::cin >> answer;
        playing = (answer == "yes");
    }

    saveTree(root, filename);
    deleteTree(root);

    return 0;
}

Node* loadTree(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) return nullptr;
    return loadTreeHelper(inFile);
}


Node* loadTreeHelper(std::ifstream& inFile) {
    std::string line;
    if (!std::getline(inFile, line) || line == "#") return nullptr;

    Node* node = new Node(line);
    node->yes = loadTreeHelper(inFile);
    node->no = loadTreeHelper(inFile);

    return node;
}

void saveTree(Node* root, const std::string& filename) {
    std::ofstream outFile(filename);
    saveTreeHelper(root, outFile);
}

void saveTreeHelper(Node* node, std::ofstream& outFile) {
    if (!node) {
        outFile << "#" << std::endl;
        return;
    }

    outFile << node->content << std::endl;
    saveTreeHelper(node->yes, outFile);
    saveTreeHelper(node->no, outFile);
}

void deleteTree(Node* node) {
    if (!node) return;

    deleteTree(node->yes);
    deleteTree(node->no);
    delete node;
}

void playGame(Node* root) {
    Node* current = root;
    Node* parent = nullptr;
    bool isYesChild = false;

    while (current->yes && current->no) {
        std::cout << current->content << " (yes/no): ";
        std::string answer;
        std::cin >> answer;

        parent = current;
        if (answer == "yes") {
            current = current->yes;
            isYesChild = true;
        } else {
            current = current->no;
            isYesChild = false;
        }
    }

    std::cout << "Is it " << current->content << "? (yes/no): ";
    std::string answer;
    std::cin >> answer;

    if (answer == "yes") {
        std::cout << "I guessed it!\n";
    } else {
        addKnowledge(current);
    }
}

void addKnowledge(Node* node) {
    std::cout << "I give up. What were you thinking of? ";
    std::cin.ignore();
    std::string correctAnswer;
    std::getline(std::cin, correctAnswer);

    std::cout << "Give me a question to distinguish " << correctAnswer << " from " << node->content << ": ";
    std::string newQuestion;
    std::getline(std::cin, newQuestion);

    std::cout << "What is the answer for " << correctAnswer << "? (yes/no): ";
    std::string answer;
    std::cin >> answer;

    Node* correctNode = new Node(correctAnswer);
    Node* currentAnswerNode = new Node(node->content);

    node->content = newQuestion;
    if (answer == "yes") {
        node->yes = correctNode;
        node->no = currentAnswerNode;
    } else {
        node->yes = currentAnswerNode;
        node->no = correctNode;
    }
}
