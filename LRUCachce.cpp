#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    int key, val;
    Node* prev;
    Node* next;

    Node(int k, int v) {
        key=k;
        val=v;
        prev=next=NULL;
    }
};

class LRUCache {
private:
    int capacity;
    unordered_map<int, Node*> cacheMap;
    Node* head;
    Node* tail;

public:
    LRUCache(int cap) {
        capacity=cap;

        head=new Node(-1,-1);
        tail=new Node(-1,-1);

        head->next=tail;
        tail->prev=head;
    }

    void remove(Node* node) {
        node->prev->next=node->next;
        node->next->prev=node->prev;
    }

    void insert(Node* node) {
        node->next=head->next;
        node->prev=head;
        head->next->prev=node;
        head->next=node;
    }

    int get(int key) {
        if(cacheMap.find(key)==cacheMap.end()) {
            return -1;
        }

        Node* node=cacheMap[key];
        remove(node);
        insert(node);

        return node->val;
    }

    void put(int key, int val) {
        if(cacheMap.find(key)!=cacheMap.end()){
            Node* existing=cacheMap[key];
            remove(existing);
            cacheMap.erase(key);
        }

        if(cacheMap.size()==capacity){   // memory limit exceed
            Node* lru=tail->prev;
            remove(lru);
            cacheMap.erase(lru->key);
        }

        Node* newNode=new Node(key, val);
        insert(newNode);
        cacheMap[key]=newNode;
    }

    void display() {
        Node* temp=head->next;
        cout << "LRU Cache: ";

        while(temp!=tail) {
            cout << "[" << temp->key << ":" << temp->val << "] ";
            temp=temp->next;
        }
        cout << endl;
    }
};

int main() {

    int capacity;
    cout << "Enter cache capacity: ";
    cin >> capacity;

    LRUCache cache(capacity);

    int choice;

    while (true) {
        cout << "\n--- LRU Cache Menu ---\n";
        cout << "1. PUT\n";
        cout << "2. GET\n";
        cout << "3. DISPLAY\n";
        cout << "4. EXIT\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int key, val;
            cout << "Enter key and val: ";
            cin >> key >> val;
            cache.put(key, val);
        }
        else if (choice == 2) {
            int key;
            cout << "Enter key: ";
            cin >> key;
            int result = cache.get(key);
            cout << "val: " << result << endl;
        }
        else if (choice == 3) {
            cache.display();
        }
        else if (choice == 4) {
            break;
        }
        else {
            cout << "Invalid choice\n";
        }
    }

    return 0;
}