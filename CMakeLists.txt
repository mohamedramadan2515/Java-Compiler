cmake_minimum_required(VERSION 3.6)
project(CompilerPhase1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp automata/Node.cpp automata/Node.h automata/Automata.cpp automata/Automata.h parser/AutomataBuilder.cpp parser/AutomataBuilder.h input_grammer.txt utils/string_utils.h utils/string_utils.cpp automata/EmptyAutomata.cpp automata/EmptyAutomata.h dfa/DFABuilder.cpp dfa/DFABuilder.h dfa/State.cpp dfa/State.h dfa/TableGenerator.cpp dfa/TableGenerator.h minimizer/DFAMinimizer.cpp minimizer/DFAMinimizer.h minimizer/PartitionSet.cpp minimizer/PartitionSet.h utils/Constants.cpp utils/Constants.h test_program.txt code_recognizer/Recognizer.cpp code_recognizer/Recognizer.h)
add_executable(CompilerPhase1 ${SOURCE_FILES})