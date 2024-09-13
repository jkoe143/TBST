/*-------------------------------------------
Project 3: Threaded Binary search tree test cases
Course: CS 251, Summer 2024, UIC
System: Advanced zyLab system
Author: Jason Park
-------------------------------------------*/
#include "bstt.h"
#include <gtest/gtest.h>
using namespace std;


//test case for default constructor
TEST(bstt, empty_constructor) {
    //testing bstt with int keys/values
    {
        bstt<int, int> tree;
        ASSERT_EQ(tree.size(), 0); //checks size
        int value;
        ASSERT_EQ(tree.search(1,value), false);//verifies search fails for non-existing key
    }

    //testing bstt with string keys/double values
    {
        bstt<string, double> tree;
        ASSERT_EQ(tree.size(), 0); //checks size
        double doubleValue;
        ASSERT_EQ(tree.search("key", doubleValue), false);//verifies search fails for non-existing key
    }

    //testing bstt with char keys/string values
    {
        bstt<char, string> tree;
        ASSERT_EQ(tree.size(), 0); //checks size
        string stringValue;
        ASSERT_EQ(tree.search('a', stringValue), false);//verifies search fails for non-existing key
    }  
}


//Test case for bstt copy constructor
TEST(bstt, copyConstructor){
    //testing copy consturctor with int keys and int value
    {
        bstt<int, int> tree;
        tree.insert(5, 200);
        tree.insert(1, 2);
        tree.insert(2, 4);
        tree.insert(3, 6);
        tree.insert(6, 13);

        bstt<int, int> copiedTree(tree); //copy is created of the tree

        ASSERT_EQ(tree.size(), copiedTree.size()); //ensure sizes are equal after copying

        int num;
        for (int i = 1; i <= 6; i++) {
            if (i == 4) {
                continue;
            }
            ASSERT_EQ(copiedTree.search(i, num), true);//verify that each key exists
            ASSERT_EQ(num, tree[i]); //verify that the values match in copied tree
        }

        copiedTree.insert(7, 14); //modify the copied tree
        ASSERT_EQ(copiedTree.size(), 6); //check size
        ASSERT_EQ(tree.size(), 5); //ensure original tree remained the same
    }

    //testing copy consturctor with double keys and double value
    {
        bstt<double, double> tree;
        tree.insert(5.5, 200.1);
        tree.insert(1.1, 2.2);
        tree.insert(2.2, 4.4);
        tree.insert(3.3, 6.6);
        tree.insert(6.6, 13.13);

        bstt<double, double> copiedTree(tree); //copy is created of the tree

        ASSERT_EQ(tree.size(), copiedTree.size()); //ensure sizes are equal after copying

        double num;
        double values[] = {1.1, 2.2, 3.3, 5.5, 6.6};
        for (double i : values) {
            ASSERT_EQ(copiedTree.search(i, num), true); //verify that each key exists
            ASSERT_EQ(num, tree[i]); //verify that the values match in copied tree
        }

        copiedTree.insert(7.7, 14.14); //modify the copied tree
        ASSERT_EQ(copiedTree.size(), 6);
        ASSERT_EQ(tree.size(), 5); //ensure original tree remained the same
    }

    //testing copy consturctor with string keys and double value
    {
        bstt<string, double> tree;
        tree.insert("apples", 1.2);
        tree.insert("banana", 2.3);
        tree.insert("cola", 3.4);
        tree.insert("diet cola", 4.5);
        tree.insert("fire", 5.6);

        bstt<string, double> copiedTree(tree); //copy is created of the tree

        ASSERT_EQ(tree.size(), copiedTree.size()); //ensure sizes are equal after copying

        double num;
        ASSERT_EQ(copiedTree.search("apples", num), true); //verify that the values match in copied tree
        ASSERT_EQ(num, 1.2);

        ASSERT_EQ(copiedTree.search("cola", num), true);
        ASSERT_EQ(num, 3.4);

        copiedTree.insert("grape", 6.7);
        ASSERT_EQ(copiedTree.size(), 6);
        ASSERT_EQ(tree.size(), 5);

        //ensure original tree remained the same
        ASSERT_EQ(copiedTree.search("grape", num), true);
        ASSERT_EQ(num, 6.7);
        ASSERT_EQ(tree.search("grape", num), false);
    }
}


//test case for destructor/clear() function
TEST(bstt, destructor){
    //testing destructor with int keys and int value
    {
        bstt<int, int> tree;
        tree.insert(5, 200);
        tree.insert(1, 2);
        tree.insert(2, 4);
        tree.insert(3, 6);
        tree.insert(6, 13);

        ASSERT_EQ(tree.size(), 5);//check initial size
        //destructor is called when tree goes out of scope
    }

    //tests clear() function with int keys/int value
    {
        bstt<int, int> tree;
        tree.insert(5, 200);
        tree.insert(15, 150);
        tree.insert(10, 100);
        tree.insert(25, 250);

        ASSERT_EQ(tree.size(), 4); //check initial size
        tree.clear(); //clear the tree
        ASSERT_EQ(tree.size(), 0); //check size after
    }

    //tests clear() function with int keys/int value after copying
    {
        bstt<int, int> tree; 
        tree.insert(2, 4);
        tree.insert(5, 200);
        tree.insert(1, 2);
        bstt<int, int> copiedTree(tree); //creates a copy 
        ASSERT_EQ(copiedTree.size(), 3); //checks size
        copiedTree.clear(); //clear
        ASSERT_EQ(copiedTree.size(), 0); //checks size again
    }

    //tests clear() function with double keys/double value after copying
    {
        bstt<double, double> tree;
        tree.insert(1.1, 2.2);
        tree.insert(2.2, 3.3);
        tree.insert(3.3, 4.4);
        bstt<double, double> copiedTree(tree);  //creates a copy 

        ASSERT_EQ(copiedTree.size(), 3);  //checks size
        double num;
        ASSERT_EQ(copiedTree.search(1.1, num), true);
        ASSERT_EQ(copiedTree.search(2.2, num), true);

        copiedTree.clear();
        ASSERT_EQ(copiedTree.size(), 0);
        ASSERT_EQ(copiedTree.search(1.1, num), false);
        ASSERT_EQ(copiedTree.search(2.2, num), false);
    }

    //tests clear() function with string keys/char value after copying
    {
        bstt<string, char> tree;
        tree.insert("apples", 'a');
        tree.insert("bored", 'b');
        tree.insert("cola", 'c');
        bstt<string, char> copiedTree(tree);

        ASSERT_EQ(copiedTree.size(), 3);
        char value;
        ASSERT_EQ(copiedTree.search("apples", value), true);
        ASSERT_EQ(copiedTree.search("bored", value), true);

        copiedTree.clear();
        ASSERT_EQ(copiedTree.size(), 0);
        ASSERT_EQ(copiedTree.search("apples", value), false);
        ASSERT_EQ(copiedTree.search("cola", value), false);
    }
}


// test case for bstt assignment operator functionality
TEST(bstt, assignmentOperator){
    // test assignment operator with int keys/int values
    {
        bstt<int, int> tree;
        tree.insert(5, 200);
        tree.insert(1, 2);
        tree.insert(2, 4);
        tree.insert(3, 6);
        tree.insert(4, 8);

        bstt<int, int> assignedTree;
        assignedTree = tree; // perform assignment

        // Verify that sizes are equal after assignment
        ASSERT_EQ(tree.size(), assignedTree.size());

        int num;
        // Check each key in the original tree is present and values are preserved
        for(int i = 1; i < 6; i ++){
            ASSERT_EQ(assignedTree.search(i,num), true);
            ASSERT_EQ(num, tree[i]);
        }

        assignedTree.clear(); 
        ASSERT_EQ(assignedTree.size(), 0); // Ensure assigned tree is cleared
        ASSERT_EQ(tree.size(), 5); // Original tree size remains unchanged
    }

    // test assignment operator with double keys/double values
    {
        bstt<double, double> tree;
        tree.insert(5.5, 200.1);
        tree.insert(1.1, 2.2);
        tree.insert(2.2, 4.4);
        tree.insert(3.3, 6.6);
        tree.insert(4.4, 8.8);

        bstt<double, double> assignedTree;
        assignedTree = tree;

        // Verify that sizes are equal after assignment
        ASSERT_EQ(tree.size(), assignedTree.size());

        double num;
        double keys[] = {1.1, 2.2, 3.3, 4.4, 5.5};
        // Check each key in the original tree is present and values are preserved
        for(double key: keys){
            ASSERT_EQ(assignedTree.search(key,num), true);
            ASSERT_EQ(num, tree[key]);
        }

        assignedTree.clear();
        ASSERT_EQ(assignedTree.size(), 0); // Ensure assigned tree is cleared
        ASSERT_EQ(tree.size(), 5); // Original tree size remains unchanged
    }

    // test assignment operator with string keys/char values
    {
        bstt<string, char> tree;
        tree.insert("apples", 'a');
        tree.insert("bored", 'b');
        tree.insert("cola", 'c');
        tree.insert("dream", 'd');
        tree.insert("enoki", 'e');

        bstt<string, char> assignedTree;
        assignedTree = tree;

        // Verify that sizes are equal after assignment
        ASSERT_EQ(tree.size(), assignedTree.size());

        char value;
        string keys[] = {"apples", "bored", "cola", "dream", "enoki"};
        // Check each key in the original tree is present and values are preserved
        for(const string& key: keys){
            ASSERT_EQ(assignedTree.search(key,value), true);
            ASSERT_EQ(value, tree[key]);
        }

        assignedTree.clear();
        ASSERT_EQ(assignedTree.size(), 0); // Ensure assigned tree is cleared
        ASSERT_EQ(tree.size(), 5); // Original tree size remains unchanged
    }
}


// test case for bstt size method
TEST(bstt, size){
    // test with int keys and int values
    {
        bstt<int, int> tree;
        ASSERT_EQ(tree.size(), 0); // initially, the tree should be empty

        tree.insert(5, 200);
        tree.insert(1, 2);
        ASSERT_EQ(tree.size(), 2); // size should reflect the number of elements inserted

        tree.clear(); // clear the tree
        ASSERT_EQ(tree.size(), 0); // size should be 0 after clearing
    }

    // test with int keys and double values
    {
        bstt<int, double> tree;
        ASSERT_EQ(tree.size(), 0); // initially, the tree should be empty

        tree.insert(5, 200.5);
        tree.insert(1, 2.3);
        tree.insert(3, 3.2);
        ASSERT_EQ(tree.size(), 3); // size should reflect the number of elements inserted

        tree.clear(); // clear the tree
        ASSERT_EQ(tree.size(), 0); // size should be 0 after clearing
    }

    // test with char keys and string values
    {
        bstt<char, string> tree;
        ASSERT_EQ(tree.size(), 0); // initially, the tree should be empty

        tree.insert('c', "crime");
        tree.insert('f', "fries");
        ASSERT_EQ(tree.size(), 2); // size should reflect the number of elements inserted

        tree.clear(); // clear the tree
        ASSERT_EQ(tree.size(), 0); // size should be 0 after clearing
    }
}


// test case for bstt search method
TEST(bstt, search){
    // test with int keys and int values
    {
        bstt<int, int> tree;
        tree.insert(5, 200);
        tree.insert(1, 2);
        tree.insert(2, 4);
        tree.insert(3, 6);
        tree.insert(6, 13);

        int num;
        //search existing keys and verify the values returned
        ASSERT_EQ(tree.search(5, num), true);
        ASSERT_EQ(num, 200); 
        ASSERT_EQ(tree.search(1, num), true); 
        ASSERT_EQ(num, 2); 
        ASSERT_EQ(tree.search(3, num), true); 
        ASSERT_EQ(num, 6); 
        ASSERT_EQ(tree.search(6, num), true); 
        ASSERT_EQ(num, 13);
        // search non-existing keys
        ASSERT_EQ(tree.search(10, num), false); 
        ASSERT_EQ(tree.search(4, num), false); 
    }

    // test with string keys and int values
    {
        bstt<string, int> tree;
        tree.insert("5", 200);
        tree.insert("1", 2);
        tree.insert("2", 4);
        tree.insert("3", 6);
        tree.insert("6", 13);

        //search existing keys and verify the values returned
        int num;
        ASSERT_EQ(tree.search("5", num), true); 
        ASSERT_EQ(num, 200); 
        ASSERT_EQ(tree.search("1", num), true);
        ASSERT_EQ(num, 2); 
        ASSERT_EQ(tree.search("3", num), true);
        ASSERT_EQ(num, 6); 
        ASSERT_EQ(tree.search("6", num), true); 
        ASSERT_EQ(num, 13); 
        // search non-existing keys
        ASSERT_EQ(tree.search("10", num), false);
        ASSERT_EQ(tree.search("4", num), false);
    }

    // test with char keys and double values
    {
        bstt<char, double> tree;
        tree.insert('e', 200.2);
        tree.insert('f', 2.2);
        tree.insert('s', 4.4);
        tree.insert('c', 6.6);
        tree.insert('d', 13.3);

        //search existing keys and verify the values returned
        double num;
        ASSERT_EQ(tree.search('e', num), true); 
        ASSERT_EQ(num, 200.2);
        ASSERT_EQ(tree.search('f', num), true); 
        ASSERT_EQ(num, 2.2); 
        ASSERT_EQ(tree.search('c', num), true); 
        ASSERT_EQ(num, 6.6); 
        ASSERT_EQ(tree.search('d', num), true); 
        ASSERT_EQ(num, 13.3); 

        // search non-existing keys
        ASSERT_EQ(tree.search('z', num), false); 
        ASSERT_EQ(tree.search('x', num), false); 
    }
}


// test case for bstt insert method
TEST(bstt, insert) {   
    // int keys and int values
    {
        bstt<int, int>  tree2; 
        tree2.insert(5, 200);
        tree2.insert(1, 1);
        tree2.insert(2, 2);
        tree2.insert(3, 3);
        tree2.insert(6, 110);
        tree2.insert(7, 107);
        tree2.insert(9, 109);
        tree2.insert(8, 108);
        tree2.insert(4, 108);

        ASSERT_EQ(tree2.size(), 9); // ensure size is correct after insertions

        int key;
        tree2.begin();
        int i = 1;
        while (tree2.next(key)) { // iterate through the tree keys in order
            ASSERT_EQ(key,i); // verify the order of keys
            i++;
        }

        int originalSize = tree2.size();
        tree2.insert(5,250); // inserting a duplicate key should not change size
        ASSERT_EQ(tree2.size(), originalSize); // size remains unchanged

        int num;
        ASSERT_EQ(tree2.search(5, num), true); // verify existing key and value
        ASSERT_EQ(num, 200);
        ASSERT_EQ(tree2.search(9, num), true); // verify existing key and value
        ASSERT_EQ(num, 109);
    }
    
    // string keys and int values
    {
        bstt<string, int> tree;
        tree.insert("ice", 10);
        tree.insert("cream", 15);
        tree.insert("shield", 25);

        ASSERT_EQ(tree.size(), 3); // ensure size is correct after insertions

        int value;
        ASSERT_EQ(tree.search("ice", value), true); // verify existing key and value
        ASSERT_EQ(value, 10);
        ASSERT_EQ(tree.search("hammer", value), false); // verify non-existing key
    }
    
    // char keys and double values
    {
        bstt<char, double> tree;
        tree.insert('p', 10.0);
        tree.insert('c', 15.0);
        tree.insert('s', 25.0);

        ASSERT_EQ(tree.size(), 3); // ensure size is correct after insertions

        double value;
        ASSERT_EQ(tree.search('p', value), true); // verify existing key and value
        ASSERT_EQ(value, 10.0);
        ASSERT_EQ(tree.search('y', value), false); // verify non-existing key
    }
}


// test case for bstt operator[] method
TEST(bstt, operatorIndex){
    // int keys and int values
    {   //build tree
        bstt<int, int> tree;
        tree.insert(5, 200);
        tree.insert(1, 2);
        tree.insert(2, 4);
        tree.insert(3, 6);
        tree.insert(4, 8);

       
        ASSERT_EQ(tree[5], 200); 
        ASSERT_EQ(tree[1], 2);
        ASSERT_EQ(tree[2], 4);
        ASSERT_EQ(tree[3], 6);
        ASSERT_EQ(tree[4], 8);

        // accessing non-existing key should return default value
        ASSERT_EQ(tree[6], int{}); 
        ASSERT_EQ(tree[10], int{}); 
    }
    
    // double keys and string values
    {   //build tree
        bstt<double, string> tree;
        tree.insert(5.5, "zebra");
        tree.insert(1.1, "unicorn");
        tree.insert(2.2, "griffin");
        tree.insert(3.3, "manticore");
        tree.insert(4.4, "pheonix");

        // verify existing key and value
        ASSERT_EQ(tree[5.5], "zebra"); 
        ASSERT_EQ(tree[1.1], "unicorn");
        ASSERT_EQ(tree[2.2], "griffin");
        ASSERT_EQ(tree[3.3], "manticore");
        ASSERT_EQ(tree[4.4], "pheonix");

        // accessing non-existing key should return default value
        ASSERT_EQ(tree[6.2], string{}); 
        ASSERT_EQ(tree[10.3], string{}); 
    }
}


// test case for bstt operator() method
TEST(bstt, operatorToRight){
    // int keys and int values
    {   //build tree
        bstt<int, int> tree; 
        tree.insert(5, 200);
        tree.insert(1, 2);
        tree.insert(2, 4);
        tree.insert(3, 6);
        tree.insert(4, 8);
        tree.insert(6, 13);
        tree.insert(7, 14);
        
        //verify sucessors
        ASSERT_EQ(tree(5), 6); 
        ASSERT_EQ(tree(3), 4); 

        ASSERT_EQ(tree(6), 7);
        ASSERT_EQ(tree(1), 2); 
        //access non-existing key should return default value
        ASSERT_EQ(tree(10), int{}); 
        ASSERT_EQ(tree(0), int{}); 
    }
    
    // int keys and string values
    {   //build tree
        bstt<int, string> tree; 
        tree.insert(5, "zebra");
        tree.insert(1, "unicorn");
        tree.insert(2, "griffin");
        tree.insert(3, "manticore");
        tree.insert(4, "pheonix");
        tree.insert(6, "dragon");
        
        //verify sucessors
        ASSERT_EQ(tree(5), 6); 
        ASSERT_EQ(tree(1), 2); 
        ASSERT_EQ(tree(3), 4);
        //access non-existing key should return default value
        ASSERT_EQ(tree(6), int{});
        ASSERT_EQ(tree(10), int{}); 
        ASSERT_EQ(tree(0), int{}); 
    }
}


// test case for bstt begin method
TEST(bstt, begin){
    // int keys and int values
    {
        bstt<int, int>  tree; 
        tree.insert(5, 200);
        tree.insert(1, 2);
        tree.insert(2, 4);
        tree.insert(3, 6);
        tree.insert(4, 8);
        tree.insert(6, 13);
        tree.insert(7, 14);

        tree.begin();
        int key;

        ASSERT_EQ(tree.next(key), true); // check if next() returns true
        ASSERT_EQ(key, 1); // check the first key

        int correctKeys[] = {1,2,3,4,5,6,7};
        for(int i = 1; i < 7; i++){
            ASSERT_EQ(tree.next(key), true); // check next() for ordered keys
            ASSERT_EQ(key, correctKeys[i]);
        }
        ASSERT_EQ(tree.next(key), false); // check if next() returns false at the end
    }
    
    // double keys and int values
    {
        bstt<double, int>  tree; 
        tree.insert(5.5, 200);
        tree.insert(1.1, 2);
        tree.insert(2.2, 4);
        tree.insert(3.3, 6);
        tree.insert(4.4, 8);
        tree.insert(6.6, 13);
        tree.insert(7.7, 14);

        tree.begin();
        double key;

        ASSERT_EQ(tree.next(key), true); // check if next() returns true
        ASSERT_EQ(key, 1.1); // check the first key

        double correctKeys[] = {1.1,2.2,3.3,4.4,5.5,6.6,7.7};
        for(int i = 1; i < 7; i++){
            ASSERT_EQ(tree.next(key), true); // check next() for ordered keys
            ASSERT_EQ(key, correctKeys[i]);
        }
        ASSERT_EQ(tree.next(key), false); // check if next() returns false at the end
    }
}


// test case for bstt next method
TEST(bstt, next){
    // int keys and int values
    {
        bstt<int, int>  tree; 
        tree.insert(10, 100);
        tree.insert(3, 30);
        tree.insert(4, 40);
        tree.insert(7, 70);
        tree.insert(1, 10);
        tree.insert(5, 50);
        tree.insert(12, 120);
        
        tree.begin();
        int key;
        int correctKeys[] = {1, 3, 4, 5, 7, 10, 12};
        for(int i = 0; i < 7; i++){
            ASSERT_EQ(tree.next(key), true); // check next() for ordered keys
            ASSERT_EQ(key, correctKeys[i]);
        }
        ASSERT_EQ(tree.next(key), false); // check if next() returns false at the end
    }
    
    // int keys and double values
    {
        bstt<int, double>  tree; 
        tree.insert(10, 100.4);
        tree.insert(3, 30.3);
        tree.insert(4, 40.5);
        tree.insert(7, 70.6);
        tree.insert(1, 10.1);
        tree.insert(5, 50.3);
        tree.insert(12, 120.2);
        
        tree.begin();
        int key;
        int correctKeys[] = {1, 3, 4, 5, 7, 10, 12};
        for(int i = 0; i < 7; i++){
            ASSERT_EQ(tree.next(key), true); // check next() for ordered keys
            ASSERT_EQ(key, correctKeys[i]);
        }
        ASSERT_EQ(tree.next(key), false); // check if next() returns false at the end
    }
}


//test case for bstt dump 
TEST(bstt, dump){
    //integer keys and integer values
    {   //makes tree
        bstt<int, int> tree;
        tree.insert(30, 30);
        tree.insert(15, 15);
        tree.insert(50, 50);
        tree.insert(8, 8);
        tree.insert(25, 25);
        tree.insert(70, 70);
        tree.insert(20, 20);
        tree.insert(28, 28);
        tree.insert(60, 60);

        tree.dump(cout); //dump tree sturctures
        ASSERT_EQ(tree.size(), 9); //check if size is correct

        //check successor for various keys
        ASSERT_EQ(tree(8), 15); 
        ASSERT_EQ(tree(15), 25);
        ASSERT_EQ(tree(20), 25);
        ASSERT_EQ(tree(25), 28);
        ASSERT_EQ(tree(28), 30);
        ASSERT_EQ(tree(30), 50);
        ASSERT_EQ(tree(50), 70);
        ASSERT_EQ(tree(60), 70);
        ASSERT_EQ(tree(70), int{}); //checks successor where it should return default
    }
    
    //integer keys and integer values
    {   //makes tree
        bstt<double, string> tree;
        tree.insert(5.5, "zebra");
        tree.insert(1.1, "unicorn");
        tree.insert(2.2, "griffin");
        tree.insert(3.3, "manticore");
        tree.insert(4.4, "pheonix");
        tree.insert(6.6, "dragon");
        tree.insert(7.7, "phoenix");

        tree.dump(cout);  //makes tree
        ASSERT_EQ(tree.size(), 7); //check if size is correct

        //check successor for various keys
        ASSERT_EQ(tree(1.1), 2.2);
        ASSERT_EQ(tree(2.2), 3.3);
        ASSERT_EQ(tree(3.3), 4.4);
        ASSERT_EQ(tree(4.4), 5.5);
        ASSERT_EQ(tree(5.5), 6.6);
        ASSERT_EQ(tree(6.6), 7.7);
        ASSERT_EQ(tree(7.7), double{}); //checks successor where it should return default
    }
}


struct Student{
    string name;
    int age;
};


//tests bstt with custom struct
TEST(bstt, structTest){
    bstt<int, Student> tree;
    tree.insert(1, {"Jason", 20});
    tree.insert(2, {"Bob", 21});
    tree.insert(3, {"Saul", 25});

    ASSERT_EQ(tree.size(), 3); //checks if size is correct 

    Student student;
    //makes sure that everything was added correctly to the tree
    ASSERT_EQ(tree.search(2, student), true);
    ASSERT_EQ(student.name, "Bob");
    ASSERT_EQ(student.age, 21);
}


class Book{
public:
    string title;
    string author;
};


//tests bstt with custom class
TEST(bstt, classTest){
    bstt<int, Book> tree;
    tree.insert(1, {"Book1", "Author1"});
    tree.insert(2, {"Book2", "Author2"});
    tree.insert(3, {"Book3", "Author3"});

    ASSERT_EQ(tree.size(), 3); //checks if size is correct 

    Book book;
    //makes sure that everything was added correctly to the tree
    ASSERT_EQ(tree.search(2, book), true);
    ASSERT_EQ(book.title, "Book2");
    ASSERT_EQ(book.author, "Author2");
}




