
class Node{
public:
    int key,val;
    Node *next,*prev;
    Node(int a,int b){
        key = a;
        val = b;
        next = nullptr;
        prev = nullptr;
    }
};

class LRUCache {
    Node *left, *right;
    unordered_map<int,Node*> mp;
    int size;
public:
    LRUCache(int capacity) {
        left = new Node(0,0);
        right = new Node(0,0);
        left->next = right;
        right->prev = left;
        size = capacity;
    }

    void remove_node(Node* node)
    {
        Node* prev = node->prev;
        Node* next = node->next;
        prev->next = next;
        next->prev = prev;
    }

    void insert_node(Node* node)
    {
        Node* prev = right->prev;
        prev->next = node;
        right->prev=  node;
        node->next = right;
        node->prev = prev;
    }
    
    int get(int key) {
        if(mp.count(key)){
            remove_node(mp[key]);
            insert_node(mp[key]);
            return mp[key]->val;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(mp.count(key)){
            remove_node(mp[key]);
            mp.erase(key);
            delete mp[key];
        }
        Node* node = new Node(key,value);
        insert_node(node);
        mp[key]=node;

        if(mp.size()>size)
        {
            Node* lru = left->next;
            remove_node(lru);
            mp.erase(lru->key);
            delete lru;
        }
    }
};

