/*-------------------------------------------
Project 3: Threaded Binary search tree
Course: CS 251, Summer 2024, UIC
System: Advanced zyLab system
Author: Jason Park
-------------------------------------------*/

#pragma once
#include <iostream>
using namespace std;


template<typename KeyT, typename ValueT>
class bstt {
private: //NODE struct used for implementing the tree
    struct NODE {
        KeyT   Key;
        ValueT Value;
        NODE*  Left;
        NODE*  Right;
        bool   isThreaded;
    };

    NODE* Root;  // pointer to root node of tree (nullptr if empty)
    int   Size;  // # of nodes in the tree (0 if empty)
    NODE* pointer; //pointer added for usage in begin() and next() function

public:
    //default constructor that creates an empty tree
    //no pararmeters and doesn't return anything
    bstt() {
        Root = nullptr; //initializes root to null and size to 0
        Size = 0;
    }


    //purpose is to recursively create a "deep copy" of the tree given the root node
    //takes in node which is the root node to the tree that will be copied
    //returns a pointer to the root node of the copied tree
    NODE* copyTree(NODE* node){
        if(node == nullptr){ //base case - if node is nullptr, simply return nullptr
            return nullptr; 
        }
        //a new node is created and the key, value, and threaded status are copied
        NODE* copyNode = new NODE;
        copyNode->Key = node->Key;
        copyNode->Value = node->Value;
        copyNode->isThreaded = node->isThreaded;

        //left part of the tree is copied recursively
        copyNode->Left = copyTree(node->Left);
        //if node is threaded, the copy's right is pointed to the original tree's right
        if(node->isThreaded == true){
            copyNode->Right = node->Right;  
        } else{ //else, recursively copy the right part of the tree
            copyNode->Right = copyTree(node->Right);
        }
        return copyNode; //root of the new copied subtree is returned
    }
  

    //creates a "deep copy" of the bstt object tree
    //takes in other- bstt object that will be copied
    //does not return anything per se
    bstt(const bstt& other) {
        Size = other.Size; //copies the size from the other tree
        Root = copyTree(other.Root); //calls the copyTree function to create a copy
    }


	//a destructor called automatically when tree is about to be destroyed
    //destroys the tree and frees all allocated memories
    virtual ~bstt() {
        clear();//calls the clear function
    }
    

    //opeartor clears "this" tree and then makes a copy of the "other" tree.
    //takes in a paramter of other, the tree that will be copied
    //returns a reference to the modified tree
    bstt& operator=(const bstt& other) {
        clear(); //clears the current tree
        Size = other.Size; //copies the tree size
        Root = copyTree(other.Root); //copies the tree itself
        return *this; //returns the object 
    }


    //purpose is to recursively delete ALL nodes in the subtree at "current"
    //takes in NODE* current which is a pointer to the root of the subtree that will be deleted
    //returns nothing: void
    void clearTree(NODE* current){
        if(current == nullptr) { //base case: if current node is nullptr, return
            return;
        }

        clearTree(current->Left); //recursively deletes the left subtree
        if(current->isThreaded == false) { //if right subtree is not threaded, recursively deletes it
            clearTree(current->Right);
        }

        delete current; //deletes the CURRENT node
    }

    
    //clears the contents of the tree, resetting the tree to empty.
    //no parameters and returns nothing
    void clear() {
        clearTree(Root); //recursively deletes all nodes in tree
        Root = nullptr; //point root to null
        Size = 0; //sets size to 0
    }

    
    //returns the # of nodes in the tree, 0 if empty.
    //no paramters, returns an integer that represents the node numbers
    // Time complexity:  O(1) 
    int size() const {
        return Size;
    }

    
    // Searches the tree for the given key, returning true if found
    // and false if not.  If the key is found, the corresponding value
    // is returned via the reference parameter.
    // takes in key- key that will be searched for
    // takes in value - reference parameter that the value is stored once found
    // Time complexity:  O(lgN) on average
    // returns true if key is found in tree, else false
    bool search(KeyT key, ValueT& value) const {
        NODE* current = Root; //starts the search at the root of the tree
        if(current == nullptr){ 
            return false;
        }

        do{
            if (current == nullptr) { //checks if the current node is null
                return false;
            }
            if(key == current->Key){ //checks if the key matches the current node's key
                value = current->Value; //if so assigns the node's value to the reference value
                return true; //returns true
            } else if(key < current->Key){ //checks if key is less than current node's key
                current = current->Left; //moves to the left child node
            } else if(key > current->Key){ //checks if key is greater than current node's key
                if(current->isThreaded == true){ //checks if the current node is threaded
                    return false; //if so, there is no right child so returns false
                }
                current = current->Right; //moves to the right child
            }
        } while(current != nullptr); //continue unitl current node is null
        
        return false;//returns false(key not found)
    }

    
    // inserts the given key into the tree; if the key has already been insert then
    // the function returns without changing the tree.
    // takes in key - the key to insert in the tree
    // value - the value that is associated with the key
    // Time complexity:  O(lgN) on average
    // void: returns nothing
    void insert(KeyT key, ValueT value) {
        //a new node is created and left child, right child, threaded flag are all initialized
        NODE* myNode = new NODE;
        myNode->Left = nullptr;
        myNode->Right = nullptr;
        myNode->isThreaded = true;
        myNode->Key = key; //sets the key of the new node
        myNode->Value = value; //sets the value associated with that key

        NODE* upperNode = nullptr;//pointer that tracks the upper node during traversal of the tree
        NODE* currentNode = Root; //starts traversal from the ROOT of the tree

        if (Root == nullptr) { //if tree is empty, the new node is set as the root
            Root = myNode;
            Size += 1;
            return;
        }
    
        //traverses through the tree to find the right position to insert the new node
        while (currentNode != nullptr) { 
            upperNode = currentNode; //updates uppder node to current node
            if (key < currentNode->Key) { //key is less than current node's key
                if (currentNode->Left == nullptr) { //left child is null, so inserted at this position
                    currentNode->Left = myNode;
                    myNode->Right = currentNode;
                    break;
                }
                currentNode = currentNode->Left; //move to the left child
            } else if (key > currentNode->Key) { //key is greater than current node's key
                if (currentNode->isThreaded == true || currentNode->Right == nullptr) {
                    //threaded or no right child, inserted at this position
                    myNode->Right = currentNode->Right;
                    currentNode->Right = myNode;
                    currentNode->isThreaded = false;
                    break;
                }
                currentNode = currentNode->Right; //moves to the right child
            } else if(key == currentNode->Key){ //key already exists in the tree
                delete myNode; //the created node is deleted 
                return; //return without any modification
            }
        } 
        Size += 1; //size of the tree is incremented if the insertion was successful
    }

    
    // returns the value for the given key; if the key is not found,
    // the default value ValueT{} is returned.
    // takes in key - the key to search for in tree
    // Time complexity:  O(lgN) on average
    // returns the value associated with key, if not, returns ValueT{}
    ValueT operator[](KeyT key) const {
        NODE* current = Root; //search is started from the root of the tree

        //the tree is traversed to find the node with the right key
        do{
            if (current == nullptr) { //if current node is nullptr, return default value
                return ValueT{ };
            }
            if(key == current->Key){ //key matches the current node key
                return current->Value; //value associated with the key is returned
            } else if(key < current->Key){ //key is less than the current node's key
                current = current->Left; //moves to the left child
            } else if(key > current->Key){ //key is greater than current node's key
                if(current->isThreaded){ //current node is threaded
                    return ValueT{}; //returns default value
                }
                current = current->Right; //moves to the right child
            }
        } while(current != nullptr); //ends once current hits null

        return ValueT{ }; //returns default value if nothing is found
    }

  
    // Finds the key in the tree, and returns the key to the "right".
    // If the right is threaded, this will be the next inorder key.
    // if the right is not threaded, it will be the key of whatever
    // node is immediately to the right.
    // If no such key exists, or there is no key to the "right", the
    // default key value KeyT{} is returned.
    // takes in key - the key to search for in the tree
    // returns the key that is "right" to the given key, if not found returns KeyT{}
    // Time complexity:  O(lgN) on average
    KeyT operator()(KeyT key) const {
        NODE* current = Root; //search begins from the root of the tree
        //tree is traversed to find the node given the key

        do { 
            if (current == nullptr) { //if current node is nullptr, returns default value
                return KeyT{ };
            }
            if(key == current->Key){ //key matches the current node's key
                if(current->isThreaded == true){ //current node is threaded
                    if (current->Right == nullptr) { //right node is not threaded
                        return KeyT{ }; //returns default value
                    }
                    return current->Right->Key; //retursnt the threaded key on the right
                }
                if(current->Right != nullptr){ //if not threaded, checks the right child
                    return current->Right->Key; //returns the key of the right node
                }
            } else if(key < current->Key){ //key is less than current node's key
                current = current->Left; //moves to the left child 
            } else if(key > current->Key){ //key is greater than current node's key
                if(current->isThreaded == true){ //current node is threaded
                    return KeyT{ }; //returns default value
                }
                current = current->Right; //moves to right 
            }
        } while(current != nullptr);

        return KeyT{ }; //returns default key value if nothing is found
    }

    
    // Resets internal state for an inorder traversal.  After the 
    // call to begin(), the internal state denotes the first inorder
    // key; this ensure that first call to next() function returns
    // the first inorder key.
    // no parameters taken in
    // void: returns nothing
    // Space complexity: O(1)
    // Time complexity:  O(lgN) on average
    void begin() {
        NODE* current = Root; //starts the traversal from the root 
        if(current == nullptr){ //if tree is empty
            pointer = nullptr; //pointer is set to null
            return;
        }
        //moves to the left side of the tree to find the node furthest at left
        while(current->Left != nullptr){ 
            current = current->Left;
        }
        //internal pointer is set to the node at the furthest left
        if(current != nullptr){
            pointer = current;
        }
    }

    
    // Uses the internal state to return the next inorder key, and 
    // then advances the internal state in anticipation of future
    // calls.  If a key is in fact returned (via the reference 
    // parameter), true is also returned.
    // False is returned when the internal state has reached null,
    // meaning no more keys are available.  This is the end of the
    // inorder traversal.
    // takes in key - refernence parameter to store the next inorder key
    // returns true if there is a valid next key to return, else false
    // Space complexity: O(1)
    // Time complexity:  O(lgN) on average
    bool next(KeyT& key) {
        if(pointer == nullptr){ //if pointer is null, no keys to return 
            return false; 
        }
        key = pointer->Key; //set current key as the pointer's key value

        if(pointer->isThreaded == true){  //pointer is moved to the next inorder node
            pointer = pointer->Right;
        } else{
            pointer = pointer->Right; 
            //pointer is moved to the furthest left node in the right subtree
            while(pointer != nullptr && pointer->Left != nullptr){ 
                pointer = pointer->Left;
            }
        }
        return true; //returns true if a key is returned
    }


    //recursively traverses the tree in an inorder way and prints each node
    //reports (key, value) pairs for non-threaded nodes and (key, value, THREAD) for threaded nodes.
    //takes in current - pointer to current node processed, out - reference to the output stream where tree nodes are printed
    // void: returns nothing
    void printBST(NODE* current, ostream& out) const{
        //base case: if current is null, returns 
        if(current == nullptr){
            return;
        }
        //recursively prints the left subtree
        printBST(current->Left, out);

        //prints current node's key and value
        out << "(" << current->Key << "," << current->Value;

        //if current node is threaded and has a right child, prints the key of right child
        if(current->isThreaded == true){
            if(current->Right != nullptr){
                out << "," << current->Right->Key;
            }
        }
        out << ")" << endl;
        if(current->isThreaded == false){ //if current node is not threaded, recursively prints right subtree
            printBST(current->Right, out);
        }
    }

    
    // dumps the contents of the tree to the output stream, using a
    // recursive inorder traversal.
    // takes in output -reference to outputstream where tree is printed(dumped)
    //void: returns nothing
    void dump(ostream& output) const {
        output << "**************************************************" << endl;
        output << "********************* BSTT ***********************" << endl;

        output << "** size: " << this->size() << endl;

        printBST(Root, output); //tree is printed by calling printBST function

        output << "**************************************************" << endl;
    }	
};
