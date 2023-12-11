cmake_minimum_required (VERSION 3.8)

project ("Cir-C" VERSION 0.1.0.0)

add_executable (Cir-C)
target_sources (Cir-C PRIVATE "Cir-C.cpp" "FileManager.h" "MessageManager.h" "Lexer.h" "Token.h" "Toolbox.h" "UnitTestingRoom.h")

install(TARGETS Cir-C)
