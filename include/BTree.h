#pragma once
#include "Appointment.h"
#include <vector>

using namespace std;

class BTreeNode {
public:
    vector<Appointment> appointments;
    vector<BTreeNode*> children;
    bool isLeaf;
    int minDegree;

    BTreeNode(int degree, bool leaf);
    void insertNonFull(const Appointment& appt);
    void splitChild(int index, BTreeNode* child);
    vector<Appointment> search(const string& fromDateTime, const string& toDateTime);
};

class BTree {
private:
    BTreeNode* root;
    int minDegree;

public:
    BTree(int degree);
    void insert(const Appointment& appt);
    vector<Appointment> rangeSearch(const string& fromDateTime, const string& toDateTime);
    void displayAll();
};
