//
// Created by Ramadan on 4/24/2017.
//

#include "Generator.h"
#include "../ProdRules/ProdEngine.h"
#include "LanguageValidator.h"

void Generator::generate() {
    ProdEngine* engine = new ProdEngine("C:\\CompilerPhase1\\phase2.txt");
    LanguageValidator* validator = new LanguageValidator(engine->getTable(),tokensFilePath,engine->getStart(),engine->getTerminalsMap());
    ofstream out;
    out.open("C:\\CompilerPhase1\\phase_2_output_validation.txt");
    validator->validate(out);
}
