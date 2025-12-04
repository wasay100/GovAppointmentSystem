#include "BTree.h"
#include <iostream>

using namespace std;

// BTreeNode Constructor
BTreeNode::BTreeNode(int degree, bool leaf) {
    minDegree = degree;
    isLeaf = leaf;
}

// Insert into non-full node
void BTreeNode::insertNonFull(const Appointment& appt) {
    int i = appointments.size() - 1;

    if (isLeaf) {
        appointments.push_back(appt);
        while (i >= 0 && appointments[i].getDateTime() > appt.getDateTime()) {
            appointments[i + 1] = appointments[i];
            i--;
        }
        appointments[i + 1] = appt;
    }
    else {
        while (i >= 0 && appointments[i].getDateTime() > appt.getDateTime()) {
            i--;
        }
        i++;

        if (children[i]->appointments.size() == 2 * minDegree - 1) {
            splitChild(i, children[i]);
            if (appointments[i].getDateTime() < appt.getDateTime()) {
                i++;
            }
        }
        children[i]->insertNonFull(appt);
    }
}

// Split child node
void BTreeNode::splitChild(int index, BTreeNode* child) {
    BTreeNode* newNode = new BTreeNode(child->minDegree, child->isLeaf);
    int mid = minDegree - 1;

    for (int j = 0; j < minDegree - 1; j++) {
        newNode->appointments.push_back(child->appointments[mid + 1 + j]);
    }

    if (!child->isLeaf) {
        for (int j = 0; j < minDegree; j++) {
            newNode->children.push_back(child->children[mid + 1 + j]);
        }
    }

    appointments.insert(appointments.begin() + index, child->appointments[mid]);
    children.insert(children.begin() + index + 1, newNode);

    child->appointments.resize(mid);
    if (!child->isLeaf) {
        child->children.resize(mid + 1);
    }
}

// Range search
vector<Appointment> BTreeNode::search(const string& fromDateTime, const string& toDateTime) {
    vector<Appointment> results;

    for (const auto& appt : appointments) {
        if (appt.getDateTime() >= fromDateTime && appt.getDateTime() <= toDateTime) {
            results.push_back(appt);
        }
    }

    if (!isLeaf) {
        for (auto child : children) {
            vector<Appointment> childResults = child->search(fromDateTime, toDateTime);
            results.insert(results.end(), childResults.begin(), childResults.end());
        }
    }

    return results;
}

// BTree Constructor
BTree::BTree(int degree) {
    root = nullptr;
    minDegree = degree;
}

// Insert into BTree
void BTree::insert(const Appointment& appt) {
    if (root == nullptr) {
        root = new BTreeNode(minDegree, true);
        root->appointments.push_back(appt);
    }
    else {
        if (root->appointments.size() == 2 * minDegree - 1) {
            BTreeNode* newRoot = new BTreeNode(minDegree, false);
            newRoot->children.push_back(root);
            newRoot->splitChild(0, root);
            root = newRoot;
        }
        root->insertNonFull(appt);
    }
}

// Range search in BTree
vector<Appointment> BTree::rangeSearch(const string& fromDateTime, const string& toDateTime) {
    if (root == nullptr) {
        return vector<Appointment>();
    }
    return root->search(fromDateTime, toDateTime);
}

// Display all appointments
void BTree::displayAll() {
    if (root == nullptr) {
        cout << "No appointments found." << endl;
        return;
    }

    vector<Appointment> all = root->search("0000-00-00 00:00", "9999-12-31 23:59");
    cout << "=== All Appointments ===" << endl;
    for (const auto& appt : all) {
        cout << "City: " << appt.city << " | Office: " << appt.office << endl;
        cout << "Date: " << appt.date << " | Time: " << appt.time << endl;
        cout << "CNIC: " << appt.cnic << " | Name: " << appt.name << endl;
        cout << "Confirmation: " << appt.confirmationCode << endl;
        cout << "---" << endl;
    }
}
