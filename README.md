# flam_assignment
## SET1

## Question 2
* Data Structure & Hashing: I use a vector of vectors containing key-value pairs (vector<vector<pair<int,int>>> arr) with a fixed table size of 10,000 buckets, and employ simple modulo hashing (key % n) to map keys to bucket indices. 
* Collision Resolution: When multiple keys hash to the same index,I store them in the same bucket using a vector, implementing separate chaining where each bucket can hold multiple key-value pairs.
* Put Operation: I first search the target bucket linearly to check if the key already exists - if found, I update its value; otherwise, you append the new key-value pair to the bucket, ensuring both insertion and updates work correctly. 
* Get Operation: I hash the key to find the appropriate bucket, then perform a linear search through that bucket's vector to find the matching key and return its associated value, or -1 if not found.
* Remove Operation: I locate the target bucket, linearly search for the key, and use vector.erase() to remove the element when found, effectively deleting the key-value pair from the map. 
