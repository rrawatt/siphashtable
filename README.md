# siphashtable
This project implements a simple HashMap data structure in C++ using SipHash as the hash function. It demonstrates the principles of modularity, data encapsulation, and linked-list-based collision resolution.

Features

    HashMap Data Structure:
        Supports basic operations: insert, deleteKey, and search.
        Handles collisions using separate chaining with linked lists.
        Uses SipHash for secure and efficient hashing.

    SipHash Algorithm:
        A lightweight cryptographic hash function ideal for secure hashing of short inputs.
        Designed for fast and reliable performance in hash tables.

Code Explanation
1. SipHash Implementation

The SipHash algorithm is implemented in siphash.cpp and declared in siphash.h. It takes a string input and produces a 64-bit hash value.
Key Points:

    Initialization: Internal state variables are initialized with constants and secret keys (SIPHASH_KEY1, SIPHASH_KEY2).
    Compression: The input is processed in blocks, with each block contributing to the internal state via bitwise operations.
    Finalization: The final hash value is computed after processing all input blocks and mixing the state further.

2. HashMap Class

The HashMap class is implemented in main.cpp. It uses a vector of linked lists to manage key-value pairs.
Key Components:

    Constructor: Initializes the hash map with a default capacity (100) and an empty table.

    Hash Function: Uses SipHash to compute the hash value for a given key, ensuring uniform distribution and minimizing collisions.

    Insert Operation:
        Computes the bucket index using the hash function.
        If the bucket is empty, it inserts the new node.
        If the bucket is occupied, it inserts the new node at the head of the linked list.

    Delete Operation:
        Locates the node matching the key in the appropriate bucket.
        Removes the node from the linked list, updating pointers as necessary.

    Search Operation:
        Traverses the linked list in the appropriate bucket to find a matching key.
        Returns the value if found; otherwise, returns an error message.

3. Main Program

The htab.cpp file includes the HashMap implementation and tests its functionality. It demonstrates:

    Insertion of key-value pairs into the hash map.
    Searching for keys and retrieving values.
    Deleting keys and verifying the deletion.
