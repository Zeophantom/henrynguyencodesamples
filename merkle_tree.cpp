/*
Implementation of the merkle tree and node classes and helper function to read from an inputed file.
*/

/*
To implement the insert function, I deleted my previous tree that was already made using the clearTree
function I created. After that, I initialize a new vector that would append the newvalue to the end of it
then I call my rebuildTree function with the new vector as an input which is basically just my constructor
The constructor hashes the values of the vector and puts them into a new vector called leaf
then in a while loop, we create a new vector that will store the nodes and append everything in leaf into
the new vector which will then be used inside concatenateHash and pushed into the parent vector.
the root is no set equal to the first leaf
*/

#include "merkle_tree.h"
#include <stdint.h>
#include <queue>

using namespace std;

/* Hash function*/
inline string fnv1a(string const & text) {
    // 64 bit params
    uint64_t constexpr fnv_prime = 1099511628211ULL;
    uint64_t constexpr fnv_offset_basis = 14695981039346656037ULL;
    
    uint64_t hash = fnv_offset_basis;
    
    for(auto c: text) {
        hash ^= c;
        hash *= fnv_prime;
    }

    return to_string(hash);
}

/* Merkle Tree method for computing the hash of the concatenated hashes of children nodes 
   Using the provided hash function, concatenates child hashes from left to right and returns the hash 
   of the concatenation */
string merkleTree::concatenateHash(const vector<Node*>& nodes){
    string merged;
    //concatenate hashes of all inputed nodes 
    for(const Node* node: nodes){
        merged += node->key;
    }

    //take hash of concatenated nodes
    string mergedHash = fnv1a(merged);

    return mergedHash;
}

Node::Node(const string&val)
{
    key = val;
    array<Node*,4> children;
    Node* child0= nullptr;
    Node* child1= nullptr;
    Node* child2 = nullptr;
    Node* child3 = nullptr;

    children = {{child0,child1,child2,child3}};
}

merkleTree::merkleTree()
{
    root = nullptr;
}

merkleTree::merkleTree(const vector<int>& data)
{
    root = nullptr; //sets root to nullptr and makes sure we are using correct data vector for hashing
    this->data = data;

    if (!data.empty())
    {
        vector<Node*> leaf;

        for (int value : data) //calls fnv1a function and stores each value modified inside leaf vector
        {
            string hash = fnv1a(to_string(value));
            leaf.push_back(new Node(hash));
        }

        while (leaf.size() > 1) // create new parent node and iterate through the leaf vector and stores its value inside children vector
        {
            vector<Node*> parent;
            for (int i = 0; i < leaf.size(); i+=4) // every 4 leaf nodes
            {
                vector<Node*> children;
                for (int j = i; j < i + 4 && j < leaf.size(); j++) //each individual leaf node being pushed into vector
                {
                    children.push_back(leaf[j]);
                }
                string hashparent = concatenateHash(children); //concatenate the children and push it into parent node
                parent.push_back(new Node(hashparent));
                parent.back()->children = children; //assign leaf values to the children vector member to use in other functions
            }

            leaf = parent; //set the leaf to parent node
        }
        root = leaf.front(); //set root to very first leaf
    }
}

void merkleTree::printTree(const Node* node, int depth)
{
    
    if (node == nullptr) 
    {
        return;  //if tree is empty do nothing
    }

    queue<pair<const Node*, int>> queue;  //pair of node pointer and its depth
    queue.push(make_pair(node, depth));  //start with the root node

    while (!queue.empty()) 
    {
        pair<const Node*, int> front = queue.front();  // get the front item from the queue
        queue.pop();

        const Node* currentNode = front.first;
        int currentDepth = front.second;

        cout << "Level " << currentDepth << ": ";
        
        cout << currentNode->key << endl;

        for (const Node* child : currentNode->children) //enqueue all children of nodes
        {
            if (child != nullptr) 
            {
                queue.push(make_pair(child, currentDepth + 1));
            }
        }
    }

}

void merkleTree::printRoot() //prints the root of the tree
{
    if(root !=nullptr)
    {
        cout << root->key << endl;
    }
}

vector<int> readIntsFromFile(const string& filename)
{
    vector<int> result;
    fstream file;
    file.open(filename); //opens file
    if (file.is_open()) //while file is open, copy data into vector
    {
        int value;
        while (file >> value)
        {
            result.push_back(value);
        }
        file.close(); //close file once every data is copied over
    }
    else
    {
        cout << "Failed to open file: " << filename << endl; //error check to make sure file is correct
    }

    return result; //returns the vector
}

void merkleTree::overwrite(int originalValue, int newValue)
{
    auto position = find(data.begin(), data.end(), originalValue); //iterates through data vector and finds position of the original value

    if (position != data.end()) 
    {
        *position = newValue; //overwrite original value with the new value
        rebuildTree(); //call rebuildTree function to rebuild tree with new data vector
    }
    else
    {
        cout << "Original Value not found" << endl; //checks to make sure if original value exists inside data vector
    }
}

void merkleTree::clearTree(Node* node)
{
    if (node)
    {
        for(Node* child : node->children) //recursively calls itself to clear all children nodes
        {
            clearTree(child);
        }
        delete node;
    } 
}

void merkleTree::clearTree()
{
    clearTree(root); //calls other clearTree function to clear children nodes
    root = nullptr; //sets root to nullptr so there is no more root
}

void merkleTree::rebuildTree()
{
    clearTree(); //calls clearTree to delete old tree and does the same thing our constructor did

    root = nullptr;
    this->data = data;

    if (!data.empty())
    {
        vector<Node*> leaf;

        for (int value : data)
        {
            string hash = fnv1a(to_string(value));
            leaf.push_back(new Node(hash));
        }

        while (leaf.size() > 1)
        {
            vector<Node*> parent;
            for (int i = 0; i < leaf.size(); i+=4)
            {
                vector<Node*> children;
                for (int j = i; j < i + 4 && j < leaf.size(); j++)
                {
                    children.push_back(leaf[j]);
                }
                string hashparent = concatenateHash(children);
                parent.push_back(new Node(hashparent));
                parent.back()->children = children;
            }

            leaf = parent;
        }
        root = leaf[0];
    }
}

void merkleTree::rebuildTree(vector<int> data)
{
    clearTree(); //clears tree and rebuilds it based on new data vector provided
    
    root = nullptr;
    this->data = data;

    if (!data.empty())
    {
        vector<Node*> leaf;

        for (int value : data)
        {
            string hash = fnv1a(to_string(value));
            leaf.push_back(new Node(hash));
        }

        while (leaf.size() > 1)
        {
            vector<Node*> parent;
            for (int i = 0; i < leaf.size(); i+=4)
            {
                vector<Node*> children;
                for (int j = i; j < i + 4 && j < leaf.size(); j++)
                {
                    children.push_back(leaf[j]);
                }
                string hashparent = concatenateHash(children);
                parent.push_back(new Node(hashparent));
                parent.back()->children = children;
            }

            leaf = parent;
        }
        root = leaf[0];
    }
}

void merkleTree::insert(int newValue)
{
    clearTree(); //delete old tree

    vector<int> newtreedata = data; //create new vector to be hashed
    newtreedata.push_back(newValue);

    rebuildTree(newtreedata); //rebuild based on new vector
}

Node* merkleTree::getRoot() //returns root
{
    return root;
}

void merkleTree::verify() //calculate the root and compare it to old root, if same, then true, if not then false (data tampering)6
{
    vector<Node*> leaf;

    for (int value : data)
    {
        string hash = fnv1a(to_string(value));
        leaf.push_back(new Node(hash));
    }

    while (leaf.size() > 1)
    {
        vector<Node*> parent;
        for (int i = 0; i < leaf.size(); i+=4)
        {
            vector<Node*> children;
            for (int j = i; j < i + 4 && j < leaf.size(); j++)
            {
                children.push_back(leaf[j]);
            }
            string hashparent = concatenateHash(children);
            parent.push_back(new Node(hashparent));
        }

        leaf = parent;
    }    

    if (root->key == leaf[0]->key)  //compares calculated root to old root
    {
        cout << "True" << endl;
    } 

    else 
    {
        cout << "False" << endl;
    }
}