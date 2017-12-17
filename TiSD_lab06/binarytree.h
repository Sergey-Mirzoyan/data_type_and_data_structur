//
// Created by serych on 05.12.16.
//
#ifndef LABA6_TISD_BINARYTREE_H
#define LABA6_TISD_BINARYTREE_H

#include <vector>
#include <fstream>
#include "Deque.h"

using namespace std;

template<class T>
struct Node {
    Node<T> *left = NULL;
    Node<T> *right = NULL;
    T data;
    unsigned int id;
    Node(T _data, unsigned int _id) : data(_data), id(_id) {}
};

template<class T>
class BinaryTree {
private:
    //void printWays(int elemWidth = 1, int cencerTab = 40);
    Node<T> *root = NULL;
    unsigned int idcounter = 0;
    unsigned int tmpidcounter = 0;

    void CLRrecursiveVector(Node<T> *node, vector<T> &vect);

    void LCRrecursiveVector(Node<T> *node, vector<T> &vect);

    void RCLrecursiveVector(Node<T> *node, vector<T> &vect);

    void LRCrecursiveVector(Node<T> *node, vector<T> &vect);


    vector<T> AcrossWalkVector();

    Node<T>* remove_recursive(Node<T> *node, T data);

    Node<T> *FindMin(Node<T> *root);

    void addNodeToShower(Node<T> *node, ofstream *shower, bool full);

    void createShowerNodeLabels(Node<T> *node, ofstream *shower, bool full);
    void createShowerNodeLabelsExcludeEqual(Node<T> *node, ofstream *shower, bool full, vector<T>& eqaulities);
public:
    void addNode(T data);

    void remove(T data);

    vector<T> LRCVector();

    void visualize(bool full = false, string filename = "graph.gr", string pic = "graph.png");
    void visualizeColorRepeating(bool full = false, string filename = "graph.gr", string pic = "graph.png");

    void removeDublicates();

    unsigned long memory();
};

template<class T>
void BinaryTree<T>::addNode(T data) {
    Node<T> *newNode = new(nothrow)  Node<T>(data, idcounter);
    idcounter++;
    if (!newNode)
        throw ("Cannot allocate memory");
    if (root == NULL) {
        root = newNode;
        return;
    }
    Node<T> *tmp = root;
    while (1) {
        if (data <= tmp->data) {
            if (tmp->left != NULL) {
                tmp = tmp->left;
            } else {
                tmp->left = newNode;
                break;
            }
        } else {
            if (tmp->right != NULL) {
                tmp = tmp->right;
            } else {
                tmp->right = newNode;
                break;
            }
        }
    }
}

template<class T>
void BinaryTree<T>::CLRrecursiveVector(Node<T> *node, vector<T> &vect) {
    if (node != NULL) {
        vect.push_back(node->data);
        CLRrecursiveVector(node->left, vect);
        CLRrecursiveVector(node->right, vect);
    }
}

template<class T>
void BinaryTree<T>::LCRrecursiveVector(Node<T> *node, vector<T> &vect) {
    if (node != NULL) {
        LCRrecursiveVector(node->left, vect);
        vect.push_back(node->data);
        LCRrecursiveVector(node->right, vect);
    }
}

template<class T>
void BinaryTree<T>::LRCrecursiveVector(Node<T> *node, vector<T> &vect) {
    if (node != NULL) {
        LCRrecursiveVector(node->left, vect);
        LCRrecursiveVector(node->right, vect);
        vect.push_back(node->data);
    }
}

template<class T>
vector<T> BinaryTree<T>::LRCVector() {
    vector<T> ans;
    LRCrecursiveVector(root, ans);
    return ans;
}

template<class T>
void BinaryTree<T>::RCLrecursiveVector(Node<T> *node, vector<T> &vect) {
    if (node != NULL) {
        RCLrecursiveVector(node->right, vect);
        vect.push_back(node->data);
        RCLrecursiveVector(node->left, vect);
    }
}

template<class T>
vector<T> BinaryTree<T>::AcrossWalkVector() {
    Deque<Node<T> *> queue;
    vector<T> answer;
    if (root == NULL)
        return answer;
    queue.PushBack(root);
    while (!queue.IsEmpty()) {
        if (queue.GetFront()->left != NULL) {
            queue.PushBack(queue.GetFront()->left);
        }
        if (queue.GetFront()->right != NULL) {
            queue.PushBack(queue.GetFront()->right);
        }
        answer.push_back(queue.PopFront()->data);
    }
    return answer;
}

template<class T>
void BinaryTree<T>::createShowerNodeLabels(Node<T>* node, ofstream* shower, bool full) {
    if (full && node == NULL) {
        tmpidcounter++;
        *shower << tmpidcounter << " [label=\"\'\'\"];" << endl;
    }
    if (node) {
        *shower << node->id << " [label=\"\'" << node->data << "\'\"];" << endl;
        createShowerNodeLabels(node->left, shower, full);
        createShowerNodeLabels(node->right, shower, full);
    }
}

template<class T>
void BinaryTree<T>::createShowerNodeLabelsExcludeEqual(Node<T>* node, ofstream* shower, bool full, vector<T>& eqaulities) {
    if (full && node == NULL) {
        tmpidcounter++;
        *shower << tmpidcounter << " [label=\"\'\'\"];" << endl;
    }
    if (node) {
        bool one = true;
        for (int i = 0; i < eqaulities.size(); i++) {
            if (node->data == eqaulities[i]) {
                one = false;
                break;
            }
        }
        if (!one)
            *shower << node->id << " [label=\"\'" << node->data << "\'\" ,fillcolor=\"blue\" ,style=\"filled\"];" << endl;
        else
            *shower << node->id << " [label=\"\'" << node->data << "\'\"];" << endl;
        createShowerNodeLabelsExcludeEqual(node->left, shower, full, eqaulities);
        createShowerNodeLabelsExcludeEqual(node->right, shower, full, eqaulities);
    }
}

template<class T>
void BinaryTree<T>::addNodeToShower(Node<T>* node, ofstream* shower, bool full) {
    if (node != NULL) {
        if (node->left)
            *shower << node->id << "->" << node->left->id << endl;
        else if (full) {
            tmpidcounter++;
            *shower << node->id << "->" << tmpidcounter << endl;
        }
        if (node->right)
            *shower << node->id << "->" << node->right->id << endl;
        else if (full) {
            tmpidcounter++;
            *shower << node->id << "->" << tmpidcounter << endl;
        }
        addNodeToShower(node->left, shower, full);
        addNodeToShower(node->right, shower, full);
    }
}

template<class T>
void BinaryTree<T>::visualize(bool full, string filename, string pic) {
    tmpidcounter = idcounter;
    ofstream out;
    out.open(filename);
    out << "digraph G{\nforcelabels=true;\n";
    createShowerNodeLabels(root, &out, full);
    tmpidcounter = idcounter;
    addNodeToShower(root, &out, full);
    out << "}";
    out.close();
    string script1 = "/usr/bin/dot -Tpng " + filename + " -o " + pic;
    system(script1.data());
    string script2 = "/usr/bin/xdg-open " + pic;
    system(script2.data());
}


template<class T>
void BinaryTree<T>::visualizeColorRepeating(bool full, string filename, string pic) {
    ofstream out;
    vector<T> v = AcrossWalkVector();
    vector<T> equalentrys;
    vector<int> counts;
    vector<T> singles;
    bool donotadd = false;
    for (int i = 0; i < v.size(); i++) {
        donotadd = false;
        for (int j = 0; j < equalentrys.size(); j++) {
            if (v[i] == equalentrys[j]) {
                donotadd = true;
                counts[j]++;
            }
        }
        if (!donotadd) {
            equalentrys.push_back(v[i]);
            counts.push_back(1);
        }
    }
    for (int i = 0; i < counts.size(); i++) {
        if (counts[i] > 1) {
            singles.push_back(equalentrys[i]);
        }
    }
    out.open(filename);
    out << "digraph G{\nforcelabels=true;\n";
    createShowerNodeLabelsExcludeEqual(root, &out, full, singles);
    addNodeToShower(root, &out, full);
    out << "}";
    out.close();
    string script1 = "/usr/bin/dot -Tpng " + filename + " -o " + pic;
    system(script1.data());
    string script2 = "/usr/bin/xdg-open " + pic;
    system(script2.data());
}

template<class T>
void BinaryTree<T>::remove(T data) {
    root = remove_recursive(root, data);
}

template<class T>
void BinaryTree<T>::removeDublicates() {
    vector<T> v = AcrossWalkVector();
    vector<T> equalentrys;
    vector<int> counts;
    bool donotadd = false;
    for (int i = 0; i < v.size(); i++) {
        donotadd = false;
        for (int j = 0; j < equalentrys.size(); j++) {
            if (v[i] == equalentrys[j]) {
                donotadd = true;
                counts[j]++;
            }
        }
        if (!donotadd) {
            equalentrys.push_back(v[i]);
            counts.push_back(1);
        }
    }
    for (int i = 0; i < counts.size(); i++) {
        if (counts[i] > 1) {
            for (int j = 0; j < counts[i]; j++) {
                remove(equalentrys[i]);
            }
        }
    }
}

template<class T>
Node<T>* BinaryTree<T>::FindMin(Node<T>* root){
    while(root->left != NULL) root = root->left;
    return root;
}

template<class T>
Node<T>* BinaryTree<T>::remove_recursive(Node<T> *node, T data){
    if(node == NULL) return node;
    else if(data < node->data) node->left = remove_recursive(node->left,data);
    else if(data > node->data) node->right = remove_recursive(node->right, data);
    else {
        // Case 1: No Child
        if(node->left == NULL && node->right == NULL){
            delete node;
            node = NULL;
            // Case 2: one child
        } else if(node->left == NULL){
            Node<T> *temp = node;
            node = node->right;
            delete temp;
        } else if(node->right == NULL){
            Node<T> *temp = node;
            node = node->left;
            delete temp;
        } else{
            Node<T> *temp = FindMin(node->right);
            node->data = temp->data;
            node->right = remove_recursive(node->right, temp->data);
        }
    }
    return node;
}

template<class T>
unsigned long BinaryTree<T>::memory() {
    vector<T> v = AcrossWalkVector();
    return v.size() * (sizeof(Node<T>) - sizeof(unsigned int));
}

#endif
