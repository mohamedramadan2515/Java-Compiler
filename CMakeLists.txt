cmake_minimum_required(VERSION 3.6)
project(Java-Compiler)

set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
# set(CMAKE_BUILD_FILES_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIRECTORY}/build)

set(SOURCE_FILES main.cpp automata/Node.cpp automata/Node.hpp automata/Automata.cpp automata/Automata.hpp parser/AutomataBuilder.cpp parser/AutomataBuilder.hpp input_grammer.txt utils/string_utils.hpp utils/string_utils.cpp automata/EmptyAutomata.cpp automata/EmptyAutomata.hpp dfa/DFABuilder.cpp dfa/DFABuilder.hpp dfa/State.cpp dfa/State.hpp dfa/TableGenerator.cpp dfa/TableGenerator.hpp minimizer/DFAMinimizer.cpp minimizer/DFAMinimizer.hpp minimizer/PartitionSet.cpp minimizer/PartitionSet.hpp utils/Constants.cpp utils/Constants.hpp test_program.txt code_recognizer/Recognizer.cpp code_recognizer/Recognizer.hpp ProdRules/ProdRulesParser.cpp ProdRules/ProdRulesParser.hpp ProdRules/ProdOperand.cpp ProdRules/ProdOperand.hpp ProdRules/Terminal.cpp ProdRules/Terminal.hpp ProdRules/NonTerminal.cpp ProdRules/NonTerminal.hpp ProdRules/Expression.cpp ProdRules/Expression.hpp ProdRules/ProdEngine.cpp ProdRules/ProdEngine.hpp language_validation/LanguageValidator.cpp language_validation/LanguageValidator.hpp language_validation/Generator.cpp language_validation/Generator.hpp)

add_executable(Java-Compiler ${SOURCE_FILES})

