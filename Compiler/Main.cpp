#include <iostream>
#include <fstream>
#include <string>
#include "Include/Token.hpp"
#include "Lexer/Lexer.hpp"

std::string ReadFile(const std::string& Filename) {
    std::ifstream File(Filename);
    if (!File.is_open()) {
        std::cerr << "Error: Could not open file " << Filename << std::endl;
        exit(1);
    }
    return std::string(
        std::istreambuf_iterator<char>(File),
        std::istreambuf_iterator<char>()
    );
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file.val>" << std::endl;
        return 1;
    }
    std::string Filename = argv[1];
    if (Filename.size() < 4 || Filename.substr(Filename.size() - 4) != ".val") {
        std::cerr << "Error: Expected a .val file" << std::endl;
        return 1;
    }
    std::string Source = ReadFile(argv[1]);
    Lexer L = Lexer{Source};
    auto Tokens = L.Tokenize();
    for (const auto& token : Tokens) {
    std::cout << "{ Type: " << TokenTypeToString(token.Type) << ", Value: " << token.Value 
              << ", Line: " << token.Line << ", Col: " << token.Column << "}" << std::endl;
    }
    return 0;
}