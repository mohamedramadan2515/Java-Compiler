//
// Created by Ramadan on 4/24/2017.
//

#include "LanguageValidator.h"
#include "../ProdRules/ProdRulesParser.h"
#include "../ProdRules/Expression.h"
#include "../utils/string_utils.h"
void LanguageValidator::validate(ofstream &out) {
    ifstream input;
    input.open(tokensFilePath);
    stack<ProdOperand*> validateStack;
    validateStack.push(ProdRulesParser::getEndOfExp());
    validateStack.push((ProdOperand *) start);
    printStack(validateStack,out);
    while (!input.eof()) {
        string token;
        getline(input, token);
        token = trim(token);
        if(token == "")continue;
        if(validateStack.empty()){
            out << "error extra token " << token << "\n";
        }
        else{
            bool handledToken = false;
            while(!handledToken && !validateStack.empty()) {
                if (Terminal *v = dynamic_cast<Terminal *>(validateStack.top())) {
                    Terminal *top = (Terminal *) validateStack.top();
                    if (top->getName() == token) {
                        handledToken = true;
                    } else {
                        out << "error missing " << top->getName() << ", inserted\n";
                    }

                    validateStack.pop();
                } else {
                    NonTerminal* nonTerminal = (NonTerminal*)validateStack.top();
                    Terminal* terminal = terminalsMap[token];
                    if(table->find({nonTerminal,terminal}) != table->end()){
                        Expression* associatedExp = table->at({nonTerminal,terminal});
                        vector<ProdOperand*> expOperands = associatedExp->getOperands();
                        validateStack.pop();
                        if(expOperands.size() == 1 && expOperands[0]->getName() == "\\S"){ // sync
                            out << "Synch pop stack\n";
                        }else if(expOperands.size() == 1 && expOperands[0] == ProdRulesParser::getEps()){ // eps
                            out << "Eps\n";
                        }else{ // normal
                            for(int i = expOperands.size()-1 ; i>=0 ; i--){
                                string x = expOperands[i]->getName();
                                validateStack.push(expOperands[i]);
                            }
                        }
                    }else{ // error
                        handledToken = true;
                        out << "error illegal " << validateStack.top()->getName() << " discard " << token << "\n";

                    }

                }
                printStack(validateStack,out);
            }
            if(!handledToken && validateStack.empty()){
                out << "error extra token " << token << "\n";
            }
        }
    }
    while(validateStack.size() > 0){
        out << "error missing " << validateStack.top()->getName() << ", inserted\n";
        validateStack.pop();
    }
}

void LanguageValidator::printStack(stack<ProdOperand *> s, ofstream &out) {
    while(s.size() > 1){
        string x = s.top()->getName();
        out << s.top()->getName() << " ";
        s.pop();
    }
    out << "\n";
}
