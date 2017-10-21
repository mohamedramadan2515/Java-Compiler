//
// Created by Admin on 3/21/2017.
//

#include "Node.hpp"

Node::Node(const bool isAccepted, const int type) {
  this->isAccepted = isAccepted;
  this->uid = Node::getUniqueId();
  this->type = type;
}

int Node::getUniqueId() {
  return nextId++;
}

void Node::addEpsillon(Node *node) {
    eps.push_back(node);
}

void Node::addNext(char c, Node *node) {
    next[c].push_back(node);
}

int Node::getUid() const {
    return uid;
}

bool Node::isIsAccepted() const {
    return isAccepted;
}

vector<Node *> *Node::getNext(char c) {
    return &next[c];
}

void Node::setAccepted(bool accepted) {
    this->isAccepted = accepted;
}

vector<Node *> *Node::getEps() {
    return &eps;
}

int Node::nextId = 0;

unordered_map<char, vector<Node *>> *Node::getNext() {
    return &next;
}

int Node::getType() const {
    return type;
}

void Node::setType(int type) {
    Node::type = type;
}
