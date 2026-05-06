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

        cache.push_front(key);
        mp[key] = {cache.begin(), false};

        if (cache.size() == 1)
            hand = cache.begin();
    }

    void evict() {
        while (true) {

            if (mp[*hand].second == false) {
                cout << "Evict: " << *hand << endl;

                mp.erase(*hand);
                hand = cache.erase(hand);

                if (hand == cache.end())
                    hand = cache.begin();

                break;
            }

            // second chance
            mp[*hand].second = false;

            ++hand;
            if (hand == cache.end())
                hand = cache.begin();
        }
    }

    void display() {
        cout << "Cache: ";
        for (int x : cache) {
            cout << x << "(" << mp[x].second << ") ";
        }
        cout << endl;
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
