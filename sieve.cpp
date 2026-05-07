#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

class SieveCache {
    int capacity;
    list<int> cache;

    // key -> (iterator, visited flag)
    unordered_map<int, pair<list<int>::iterator, bool>> mp;

    list<int>::iterator hand;

public:
    SieveCache(int cap) {
        capacity = cap;
        hand = cache.end(); // Represents NULL initially
    }

    void access(int key) {
        // HIT
        if (mp.count(key)) {
            mp[key].second = true;
            cout << "Hit\n";
            return;
        }

        // MISS
        cout << "Miss\n";

        if (cache.size() == capacity) {
            evict();
        }

        // Insert new item at the head
        cache.push_front(key);
        mp[key] = {cache.begin(), false};
    }

    void evict() {
        auto obj = hand;
        
        // If hand is NULL (or at end), start at the tail
        if (obj == cache.end()) {
            obj = --cache.end(); 
        }

        while (true) {
            // Found victim
            if (mp[*obj].second == false) {
                cout << "Evict: " << *obj << "\n";

                // Move hand to the object just before the victim (towards head)
                if (obj == cache.begin()) {
                    hand = --cache.end(); // wrap around to tail
                } else {
                    hand = std::prev(obj);
                }

                mp.erase(*obj);
                cache.erase(obj);
                break;
            }

            // Second chance: Reset visited bit to 0
            mp[*obj].second = false;

            // Move towards the head
            if (obj == cache.begin()) {
                obj = --cache.end(); // wrap around to tail
            } else {
                --obj; 
            }
        }
    }

    void display() {
        cout << "Cache (Head -> Tail): ";
        for (int x : cache) {
            cout << x << "[" << mp[x].second << "] ";
        }
        
        if (hand != cache.end()) {
            cout << " | Hand is pointing at: " << *hand;
        } else {
            cout << " | Hand is NULL";
        }
        cout << "\n";
    }
};

int main() {
    int cap;
    cout << "Enter cache capacity: ";
    cin >> cap;

    SieveCache cache(cap);

    int choice, key;

    while (true) {
        cout << "\n===== MENU =====\n";
        cout << "1. Access key\n";
        cout << "2. Display cache\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key: ";
                cin >> key;
                cache.access(key);
                break;

            case 2:
                cache.display();
                break;

            case 3:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice!\n";
        }
    }
}
