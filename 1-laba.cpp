#include <iostream>
#include <string>

struct Node {
    std::string name;
    int age;
    double salary;
    Node* next;
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}
    void addToBeginning(std::string name, int age, double salary) {
        Node* newNode = new Node{ name, age, salary, head };
        head = newNode;
    }

    void addToEnd(std::string name, int age, double salary) {
        Node* newNode = new Node{ name, age, salary, nullptr };
        if (!head) {
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }

    void addAfter(std::string targetName, std::string name, int age, double salary) {
        Node* current = head;
        while (current && current->name != targetName) {
            current = current->next;
        }
        if (current) {
            Node* newNode = new Node{ name, age, salary, current->next };
            current->next = newNode;
        }
    }

    void addBefore(std::string targetName, std::string name, int age, double salary) {
        if (!head) return;
        if (head->name == targetName) {
            addToBeginning(name, age, salary);
            return;
        }
        Node* current = head;
        while (current->next && current->next->name != targetName) {
            current = current->next;
        }
        if (current->next) {
            Node* newNode = new Node{ name, age, salary, current->next };
            current->next = newNode;
        }
    }

    void remove(std::string targetName) {
        if (!head) return;
        if (head->name == targetName) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* current = head;
        while (current->next && current->next->name != targetName) {
            current = current->next;
        }
        if (current->next) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }
    void displayList() {
        Node* current = head;
        while (current) {
            std::cout << "Name: " << current->name << ", Age: " << current->age << ", Salary: " << current->salary << std::endl;
            current = current->next;
        }
    }
};

int main() {
    LinkedList myList;
    myList.addToBeginning("Nikita", 25, 50000.0);
    myList.addToEnd("Anya", 30, 60000.0);
    myList.addAfter("Nikita", "Egor", 28, 55000.0);
    myList.addBefore("Anya", "Airat", 35, 70000.0);
    myList.displayList();
    myList.remove("Anya");
    myList.displayList();
    return 0;
}