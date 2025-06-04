class MyHashMap {
public:
    int n = 10000;
    vector<vector<pair<int,int>>> arr;

    MyHashMap() 
    {
        arr.resize(n);  
    }

    void put(int key, int value) {
        int k=key % n;
        for (int i=0;i<arr[k].size();i++) 
        {

            if (arr[k][i].first == key)
            {
                arr[k][i].second = value;
                return;
            }
        }
        arr[k].push_back({key, value});
    }

    int get(int key) {
        int k=key % n;
        for (int i=0;i<arr[k].size();i++) 
        {

            if (arr[k][i].first == key) {
                return arr[k][i].second;
            }
        }
        return -1;
    }

    void remove(int key) {
        int k = key % n;
        for (int i = 0; i < arr[k].size(); i++) {
            if (arr[k][i].first == key) {
                arr[k].erase(arr[k].begin() + i);
                return;
            }
        }
    }
};
