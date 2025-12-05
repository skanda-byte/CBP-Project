#include <unordered_map>
#include <string>
#include<iostream>
using namespace std;
class LRUCache {
    struct Node {
        string key;
        string value;
        Node* prev;
        Node* next;
        Node(string k, string v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    int capacity;
    unordered_map<string, Node*> mp;
    Node* head;
    Node* tail;

public:
    LRUCache(int cap) : capacity(cap) {
        head = new Node("", "");
        tail = new Node("", "");
        head->next = tail;
        tail->prev = head;
    }

    void addNode(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(Node* node) {
        Node* p = node->prev;
        Node* n = node->next;
        p->next = n;
        n->prev = p;
    }

    string get(string key) {
        if (mp.find(key) == mp.end()) return "";
        Node* node = mp[key];
        removeNode(node);
        addNode(node);
        return node->value;
    }

    void put(string key, string value) {
        if (mp.find(key) != mp.end()) {
            Node* node = mp[key];
            removeNode(node);
            delete node;
            mp.erase(key);
        }

        if (mp.size() == capacity) {
            Node* lru = tail->prev;
            removeNode(lru);
            mp.erase(lru->key);
            delete lru;
        }

        Node* newNode = new Node(key, value);
        addNode(newNode);
        mp[key] = newNode;
    }
    vector<pair<string,string>> get_all() {
    vector<pair<string, string>> result;
    Node* curr = head->next;

    while (curr != tail) {
        result.push_back({curr->key, curr->value});
        curr = curr->next;
    }
    return result;
}

};
