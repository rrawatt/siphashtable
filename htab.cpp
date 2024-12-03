#include <iostream>
#include <vector>
#include <string>
#include "siphash.h"

using namespace std;

struct Node {
    string key;
    string value;
    Node* next;

    Node(const string& key, const string& value) : key(key), value(value), next(nullptr) {}
};

class HashMap {
private:
    int capacity;
    int numOfElements;
    vector<Node*> table;

    int siphashFunction(const string& key) const {
        return siphash(key) % capacity;
    }

public:
    HashMap(int capacity = 100) : capacity(capacity), numOfElements(0), table(capacity, nullptr) {}

    void insert(const string& key, const string& value) {
        int bucketIndex = siphashFunction(key);
        Node* newNode = new Node(key, value);

        if (!table[bucketIndex]) {
            table[bucketIndex] = newNode;
        } else {
            newNode->next = table[bucketIndex];
            table[bucketIndex] = newNode;
        }
        numOfElements++;
    }

    void deleteKey(const string& key) {
        int bucketIndex = siphashFunction(key);
        Node* curr = table[bucketIndex];
        Node* prev = nullptr;

        while (curr) {
            if (curr->key == key) {
                if (prev) {
                    prev->next = curr->next;
                } else {
                    table[bucketIndex] = curr->next;
                }
                delete curr;
                numOfElements--;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        cout << "Key not found" << endl;
    }

    string search(const string& key) const {
        int bucketIndex = siphashFunction(key);
        Node* curr = table[bucketIndex];

        while (curr) {
            if (curr->key == key) {
                return curr->value;
            }
            curr = curr->next;
        }
        return "None\n";
    }
};

