#include<iostream>
#include<unordered_map>
using namespace std;

class Node {
    public:
        int key;
        Node* prev;
        Node* next;

        Node(int k) {
            key = k;
            prev = next = NULL;
        }
};

class LRUCache {
    private: 
        int capacity;
        Node* head;
        Node* tail;
        unordered_map<int, Node*> map;
    public: 
        LRUCache(int cap) {
            capacity = cap;
            head = tail = NULL;
        }

        void modeToHead(Node* node) {
            if (node == head) {
                return;
            }
            if (node == tail)
            {
                tail = tail->prev;
                tail->next = NULL;
            }
            else {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
            node->prev = NULL;
            node->next = head;
            head->prev = node;
            head = node;
        }

        void addNodeToFront(Node* node) {
            node->prev = NULL;
            node->next = head;
            if (head != NULL) {
                head->prev = node;
            }
            else {
                tail = node;
            }
            head = node;
        }

        void removeTail() {
            if (tail != NULL) {
                if(tail==head) {
                    head = tail = NULL;
                }
                else {
                    tail = tail->prev;
                    tail->next = NULL;
                }
            }
        }

        void refer(int page) {
            if (map.find(page) == map.end())
            {
                Node* node = new Node(page);
                if (map.size() >= capacity) {
                    map.erase(tail->key);
                    removeTail();
                }
                addNodeToFront(node);
                map[page] = node;
            }
            else {
                Node* node = map[page];
                moveToHead(node);
            }
        }

        void displayCache() {
            cout << "Cache: ";
            Node* node = head;
            while(node != NULL) {
                cout << node->key << " ";
                node = node->next;
            }
            cout<<endl;
        }
 };

 int main() {
    LRUCache cache(3);
    cache.refer(1);
    cache.displayCache();
    cache.refer(2);
    cache.displayCache();
    cache.refer(3);
    cache.displayCache();
    cache.refer(4);
    cache.displayCache();
    cache.refer(2);
    cache.displayCache();
    cache.refer(1);
    cache.displayCache();
    cache.refer(3);
    cache.displayCache();
    cache.refer(2);
    cache.displayCache();
    cache.refer(4);
    cache.displayCache();

    return 0;
 }