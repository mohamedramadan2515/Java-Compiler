//
// Created by Admin on 3/21/2017.
//

#ifndef COMPILERPHASE1_NODE_H
#define COMPILERPHASE1_NODE_H

#include <unordered_map>
#include <vector>

using namespace std;

class Node {

public:
  Node(const bool isAccepted, const int type);

  static int getUniqueId();

  int getType() const;

  void setType(int type);

  unordered_map<char, vector<Node *>>* getNext();

  void addEpsillon(Node *node);

  void addNext(char c, Node *node);

  vector<Node *> *getNext(char c);

  int getUid() const;

  void setAccepted(bool accepted);

  bool isIsAccepted() const;

  vector<Node *>* getEps();

private:
  bool isAccepted;
  unordered_map<char, vector<Node *>> next;
  vector<Node *> eps;
  int uid;
  int type;
  static int nextId;
};


#endif //COMPILERPHASE1_NODE_H
