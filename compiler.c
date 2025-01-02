#include <bits/stdc++.h>
using namespace std;

class Token {
public:
    string type; // Token type as a string (e.g., "KEYWORD", "IDENTIFIER")
    string value; // Actual value of the token (e.g., "int", "x")

    Token(string t, string v) : type(t), value(v) {}
};

class Lexer {
    string code;  // Input source code
    size_t pos;   // Current position in the code

public:
    Lexer(const string &input) : code(input), pos(0) {}

    void skipWhitespace() {
        while (pos < code.length() && isspace(code[pos])) {
            pos++;
        }
    }

    Token getNextToken() {
        skipWhitespace();
        if (pos >= code.length()) return Token("EOF", "");

        char current = code[pos];

        if (isalpha(current)) {
            string identifier;
            while (pos < code.length() && (isalnum(code[pos]) || code[pos] == '_')) {
                identifier += code[pos++];
            }
            if (identifier == "int") return Token("KEYWORD", "int");
            return Token("IDENTIFIER", identifier);
        }

        if (isdigit(current)) {
            string number;
            while (pos < code.length() && isdigit(code[pos])) {
                number += code[pos++];
            }
            return Token("NUMBER", number);
        }

        if (current == '+') {
            pos++;
            return Token("PLUS", "+");
        } else if (current == '-') {
            pos++;
            return Token("MINUS", "-");
        } else if (current == '=') {
            pos++;
            return Token("ASSIGN", "=");
        } else if (current == ';') {
            pos++;
            return Token("SEMICOLON", ";");
        }

        pos++;
        return Token("UNKNOWN", string(1, current));
    }
};

class Parser {
    vector<Token> tokens;
    size_t currentToken;

public:
    Parser(const vector<Token> &toks) : tokens(toks), currentToken(0) {}

    Token peek() {
        if (currentToken < tokens.size()) return tokens[currentToken];
        return Token("EOF", "");
    }

    Token consume() {
        if (currentToken < tokens.size()) return tokens[currentToken++];
        return Token("EOF", "");
    }

    void parseStatement() {
        Token token = consume();
        if (token.type == "KEYWORD" && token.value == "int") {
            Token identifier = consume();
            if (identifier.type != "IDENTIFIER") {
                cout << "Error: Expected an identifier after 'int'.\n";
                return;
            }

            Token assign = consume();
            if (assign.type != "ASSIGN") {
                cout << "Error: Expected '=' after variable name.\n";
                return;
            }

            Token number = consume();
            if (number.type != "NUMBER") {
                cout << "Error: Expected a number after '='.\n";
                return;
            }

            Token semicolon = consume();
            if (semicolon.type != "SEMICOLON") {
                cout << "Error: Expected ';' at the end of the statement.\n";
                return;
            }

            cout << "Parsed successfully: int " << identifier.value << " = " << number.value << ";\n";
        } else {
            cout << "Error: Unknown statement.\n";
        }
    }
};

class CodeGenerator {
public:
    void generateCode(const string &varName, const string &value) {
        cout << "// Pseudo-Assembly Code:\n";
        cout << "MOV R1, " << value << "  // Load value into register R1\n";
        cout << "STORE R1, " << varName << "  // Store R1 value into memory for variable " << varName << endl;
    }
};

int main() {
    // Input source code
    string code = "int x = 5;";

    Lexer lexer(code);
    vector<Token> tokens;
    while (true) {
        Token token = lexer.getNextToken();
        if (token.type == "EOF") break;
        tokens.push_back(token);
    }

    cout << "Tokens:\n";
    for (const auto &token : tokens) {
        cout << "Type: " << token.type << ", Value: " << token.value << endl;
    }

    Parser parser(tokens);
    parser.parseStatement();

    CodeGenerator codeGen;
    codeGen.generateCode("x", "5");

    return 0;
}
