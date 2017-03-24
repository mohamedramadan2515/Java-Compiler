#include <iostream>
#include <assert.h>
#include <stack>
#include <set>
#include <fstream>
#include "automata/Node.h"
#include "parser/AutomataBuilder.h"
#include "utils/string_utils.h"
#include "dfa/DFABuilder.h"
#include "dfa/TableGenerator.h"
#include "minimizer/DFAMinimizer.h"
#include "code_recognizer/Recognizer.h"

using namespace std;

void dfs(Node current, set<int> &vis) {
    vis.insert(current.getUid());
    if (current.isIsAccepted()) {
        cout << "accepted state: " << current.getUid() << endl;
    }
    for (auto &p : *current.getNext()) {
        vector<Node *> nxt = p.second;
        for (int i = 0; i < nxt.size(); i++) {
            cout << current.getUid() << " " << nxt[i]->getUid() << " " << p.first << endl;
            if (vis.find((nxt[i])->getUid()) != vis.end()) {
                continue;
            }
            dfs(*nxt[i], vis);
        }
    }
    for (Node *i: *(current.getEps())) {
        cout << current.getUid() << " " << i->getUid() << endl;
        if (vis.find(i->getUid()) != vis.end()) {
            continue;
        }
        dfs(*i, vis);
    }
}

int main() {
//    Node *n = new Node(false);
//    n->addNext('a', *new Node(true));
//    cout << "hello";
//    vector<Node> *x = n->getNext('a');
//    cout << x->size();
//
//    AutomataBuilder *b = new AutomataBuilder();
//    b->build("C:\\Users\\Admin\\ClionProjects\\CompilerPhase1\\input_grammer.txt");
//    string g = "   dhr  ";
//    g = trim(g);
//    cout << g;
//
//    string l = substitute("id: letter (letter|digit)*", "letter", "a-z | A-Z");
//    cout << l << endl;
//
//    cout << handleRanges("a-z|A-Z|0-9") << endl;
//
//    string line = "digit=0-9";
//    unsigned int idx = line.find('=');
//    string operand = line.substr(0, idx);
//    operand = trim(operand);
//    string val = line.substr(idx + 1);
//    val = trim(val);
//    cout << operand << endl << val << endl;
//
//    cout << infixToPostfix("(\\\\|\\\\)*(abc)(de)") << "h" << endl;

    AutomataBuilder *b = new AutomataBuilder();
    Automata *a = b->build("C:\\\\Users\\\\Admin\\\\ClionProjects\\\\CompilerPhase1\\\\input_grammer.txt");
//    set<int> vis;
//    cout << a->start->getUid() << " " << a->end->getUid() << endl;
//    dfs(*a->start, vis);

//    for (auto e : *b->getAllPossibleInputs()) {
//        cout << e << endl;
//    }
//    Automata *first = new Automata('a');
//    Automata *second = new Automata('b');
//    Automata *third = new Automata('c');
//    first = first->concat(*second);
//    first = first->concat(*third);
//    dfs(*first->start, vis);
//    cout << Node::getType() << endl;
//    cout << Node::getType() << endl;

    DFABuilder *builder = new DFABuilder(a, b->getAllPossibleInputs());
    Node *start = builder->buildDFA();
//    cout << start->getUid() << endl;
//    TableGenerator *tableGenerator = new TableGenerator(builder->getTaken(), b->getAllPossibleInputs());
//    tableGenerator->printTable(cout);
    DFAMinimizer *dfaMinimizer = new DFAMinimizer(start, b->getAllPossibleInputs());
    Node *startMinimized = dfaMinimizer->minimizeDFA();
    TableGenerator *tableGenerator1 = new TableGenerator(startMinimized, b->getAllPossibleInputs());
    ofstream file_out;
    file_out.open("C:\\Users\\Admin\\ClionProjects\\CompilerPhase1\\minimized_table");
    tableGenerator1->printMinimizedTable(file_out);
    Recognizer *recognizer = new Recognizer(startMinimized, b->getTypeMapping());
    ifstream myfile;
    myfile.open("C:\\Users\\Admin\\ClionProjects\\CompilerPhase1\\test_program.txt");

    ofstream output_file;
    output_file.open("C:\\Users\\Admin\\ClionProjects\\CompilerPhase1\\lexical_output");
    recognizer->recognize(output_file, myfile);
    return 0;
}