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
#include "ProdRules/ProdRulesParser.h"
#include "ProdRules/ProdEngine.h"
#include "language_validation/Generator.h"

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
    AutomataBuilder *b = new AutomataBuilder();
    Automata *a = b->build("C:\\CompilerPhase1\\input_grammer.txt");
    DFABuilder *builder = new DFABuilder(a, b->getAllPossibleInputs());
    Node *start = builder->buildDFA();
    DFAMinimizer *dfaMinimizer = new DFAMinimizer(start, b->getAllPossibleInputs());
    Node *startMinimized = dfaMinimizer->minimizeDFA();
    TableGenerator *tableGenerator1 = new TableGenerator(startMinimized, b->getAllPossibleInputs());
    ofstream file_out;
    file_out.open("C:\\CompilerPhase1\\minimized_table");
    tableGenerator1->printMinimizedTable(file_out);
    ifstream myfile;
    myfile.open("C:\\CompilerPhase1\\test_program.txt");
    Recognizer *recognizer = new Recognizer(startMinimized, b->getTypeMapping(), myfile);

    ofstream output_file;
    output_file.open("C:\\CompilerPhase1\\lexical_output");
    recognizer->recognize(output_file);
    output_file << "$\n";
    output_file << flush;
    ofstream symbol_table_file;
    symbol_table_file.open("C:\\CompilerPhase1\\symbol_table.txt");

    for (auto symbol: recognizer->symbolTable) {
        symbol_table_file << symbol.first << "\t" << symbol.second << endl;
    }

//    ProdRulesParser *parser = new ProdRulesParser("C:\\CompilerPhase1\\phase2.txt");
//    parser->parse();
//    cout<< "NonTerminals:\n";
//    for(NonTerminal* t : *(parser->getNonTerminals())){
//        cout << t->getName() << "\n";
//        vector<Expression*> v = t->getExp();
//        for(Expression* e : v){
//            for(ProdOperand* p : e->getExp()){
//                cout << p->getName() << " " ;
//            }
//            cout << "\n";
//        }
//    }
    Generator* generator = new Generator("C:\\CompilerPhase1\\lexical_output");
    generator->generate();
    return 0;
}