# flam_assignment
## SET1
## Question 1

* Data Structure Design: I use a custom Node class with key, value, and bidirectional pointers, along with dummy nodes (left and right) that act as permanent head and tail markers, simplifying insertion and deletion operations by eliminating edge case handling. 
* Hash Map Integration: The unordered_map<int,Node*> provides O(1) key-to-node mapping, while the doubly linked list maintains the usage order with most recently used items near the tail (right) and least recently used near the head (left).
* Movement Strategy: remove_node() and insert_node() helper functions efficiently unlink nodes from their current position and insert them right before the tail sentinel, effectively marking them as most recently used without traversing the entire list.
* Get Operation: When accessing a key, you check the hash map for existence, and if found, move the corresponding node to the tail position to mark it as recently used, then return its value.
* Put Operation: For insertion/update, you handle existing keys by removing the old node, create a new node with the given key-value pair, insert it at the tail, and maintain capacity by evicting the leftmost node (least recently used) when the cache exceeds its size limit.
* Memory Management: You properly delete evicted nodes to prevent memory leaks, though there's a potential bug in your put method where you call delete mp[key] after mp.erase(key), which should be fixed by storing the node pointer before erasing from the map.
* Time Complexity Achievement: All operations run in O(1) time because hash map lookups, doubly linked list insertions/deletions, and node movements are constant time operations, making this an efficient LRU cache implementation.
## Question 2
* Data Structure & Hashing: I use a vector of vectors containing key-value pairs (vector<vector<pair<int,int>>> arr) with a fixed table size of 10,000 buckets, and employ simple modulo hashing (key % n) to map keys to bucket indices. 
* Collision Resolution: When multiple keys hash to the same index,I store them in the same bucket using a vector, implementing separate chaining where each bucket can hold multiple key-value pairs.
* Put Operation: I first search the target bucket linearly to check if the key already exists - if found, I update its value; otherwise, you append the new key-value pair to the bucket, ensuring both insertion and updates work correctly. 
* Get Operation: I hash the key to find the appropriate bucket, then perform a linear search through that bucket's vector to find the matching key and return its associated value, or -1 if not found.
* Remove Operation: I locate the target bucket, linearly search for the key, and use vector.erase() to remove the element when found, effectively deleting the key-value pair from the map. 

## Question 3
