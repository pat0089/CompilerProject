#include "Token.hpp"
#include <regex>
using std::string;
using std::ostream;
using std::istream;

Token::Token() {
    _readCharacters = "";
    _type = None;
}

Token::Token(const string& chars, const Type& type) {
    _readCharacters = chars;
    _type = type;
}

Token::Token(const string& chars) {
    _readCharacters = chars;
    _type = ParseType(chars);
}

string Token::GetRaw() const {
    return _readCharacters;
}

Token::Type Token::GetType() const {
    return _type;
}

Token::Type Token::ParseType(const string &toParse) {
    if (regex_match(toParse, Lexer::isKeyword)) {
        return Keyword;
    }
    else if (regex_match(toParse, Lexer::isParenthesis)) {
        return Parenthesis;
    }
    else if (regex_match(toParse, Lexer::isBrace)) {
        return Brace;
    }
    else if (regex_match(toParse, Lexer::isSemicolon)) {
        return Semicolon;
    }
    else if (regex_match(toParse, Lexer::isIdentifier)) {
        return Identifier;
    }
    else if (regex_match(toParse, Lexer::isLiteral_int)) {
        return Literal_int;
    }
    else {
        return None;
    }
}

istream &operator>>(istream &is, Token &token) {
    char cur;
    char last = 0;
    string curChar;
    string toTokenize;
    //algorithm:
    //read in a character until we reach a symbol or a whitespace
    //is symbol:
    //      the string is empty, return the symbol itself
    //      string to return isn't empty, then put back the character and return the current string
    //is character:
    //      if the character read is numeric and the last character was alphabetical (and vice versa),
    //      put back the last character and return the string
    //
    //      else add the character to the string
    while (is.get(cur)) {
        if (isspace(cur)) {
            if (last != 0) {
                break;
            }
        } else {
            curChar.push_back(cur);
            if (std::regex_match(curChar, Lexer::isSymbol)) {
                if (toTokenize.empty()) {
                    toTokenize = curChar;
                } else {
                    is.putback(cur);
                }
                break;
            } else {
                if (isalpha(cur) && isdigit(last) || isalpha(last) && isdigit(cur)) {
                    is.putback(cur);
                    break;
                } else if (isalpha(cur) || isdigit(cur)) {
                    toTokenize.push_back(cur);
                }
            }
            last = cur;
            curChar.erase();
        }
    }
    token.Set(toTokenize);
    return is;
}

ostream &operator<<(ostream &os, Token &token) {
    if (!token._readCharacters.empty() && token._type != Token::None) {
        os << "Token: " << token._readCharacters << "\n";
        os << "Type: " << token.TypeString() << "\n";
    }
    return os;
}

void Token::Set(const string & toSet) {
    _type = ParseType(toSet);
    _readCharacters = toSet;
}

string Token::TypeString() const {
    switch (_type) {
        case Semicolon:
            return "Semicolon";
        case Identifier:
            return "Identifier";
        case Keyword:
            return "Keyword";
        case Brace:
            return "Brace";
        case Parenthesis:
            return "Parenthesis";
        case Literal_int:
            return "Literal-int";
        case None:
            return "";
    }
}
