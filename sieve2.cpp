#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

struct Node {
    int key;
    string value;
    bool visited;
    Node* prev;
    Node* next;

    Node(int k, string v) : key(k), value(v), visited(false), prev(nullptr), next(nullptr) {}
};

class SieveCache {
private:
    int capacity;
    int size;
    unordered_map<int, Node*> cache;

    Node* head;
    Node* tail;
    Node* hand;

    void addToHead(Node* node) {
        node->next = head;
        node->prev = nullptr;

        if (head) head->prev = node;
        head = node;

        if (!tail) tail = node;
    }

    void removeNode(Node* node) {
        if (node->prev)
            node->prev->next = node->next;
        else
            head = node->next;

        if (node->next)
            node->next->prev = node->prev;
        else
            tail = node->prev;
    }

    void evict() {
        if (!tail) return; // safety check

        Node* curr = hand ? hand : tail;

        // Find victim
        while (curr->visited) {
            cout << "Second chance to key: " << curr->key << endl;
            curr->visited = false;
            curr = (curr->prev) ? curr->prev : tail;
        }

        cout << "Evicting key: " << curr->key << endl;

        // Save next hand BEFORE deleting
        Node* nextHand = (curr->prev) ? curr->prev : tail;

        cache.erase(curr->key);
        removeNode(curr);
        delete curr;
        size--;

        hand = nextHand;
    }

public:
    SieveCache(int cap) {
        capacity = cap;
        size = 0;
        head = tail = hand = nullptr;
    }

    ~SieveCache() {
        Node* curr = head;
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    void put(int key, string value) {
        // Update existing
        if (cache.count(key)) {
            cache[key]->value = value;
            cache[key]->visited = true;
            cout << "Updated key: " << key << endl;
            return;
        }

        // Evict if full
        if (size >= capacity) {
            evict();
        }

        // Insert new
        Node* node = new Node(key, value);
        addToHead(node);
        cache[key] = node;
        size++;

        // Initialize hand if first node
        if (size == 1)
            hand = node;

        cout << "Inserted key: " << key << endl;
    }

    void get(int key) {
        if (cache.count(key)) {
            cache[key]->visited = true;
            cout << "Hit! Value: " << cache[key]->value << endl;
        } else {
            cout << "Miss! Key not found\n";
        }
    }

    void display() {
        Node* curr = head;

        cout << "\nCache (Head -> Tail): ";
        while (curr) {
            cout << "[" << curr->key << ":" << curr->value 
                 << " v=" << curr->visited << "] ";
            curr = curr->next;
        }

        if (hand)
            cout << "\nHand at key: " << hand->key;

        cout << endl;
    }
};

int main() {
    int cap, choice, key;
    string val;

    cout << "Enter Cache Capacity: ";
    cin >> cap;

    SieveCache cache(cap);

    while (true) {
        cout << "\n--- MENU ---\n";
        cout << "1. Put\n2. Get\n3. Display\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key and value: ";
                cin >> key >> val;
                cache.put(key, val);
                break;

            case 2:
                cout << "Enter key: ";
                cin >> key;
                cache.get(key);
                break;

            case 3:
                cache.display();
                break;

            case 4:
                return 0;

            default:
                cout << "Invalid choice!\n";
        }
    }
}
