#include "Lexer.hpp"
using std::regex;

const regex Lexer::isKeyword = regex("int|char|return");
const regex Lexer::isIdentifier = regex("[a-zA-Z]+");
const regex Lexer::isParenthesis = regex("\\(|\\)");
const regex Lexer::isBrace = regex("\\{|\\}");
const regex Lexer::isSemicolon = regex("\\;");
const regex Lexer::isLiteral_int = regex("[0-9]+");
const regex Lexer::isSymbol = regex("\\(|\\)|\\{|\\}|\\;|\\+|\\-|\\*|\\/|\\=");