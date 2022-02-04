#include "TokenList.hpp"
#include "Tokens.hpp"

using std::istream;
using std::ostream;
using std::deque;

TokenList::TokenList() : _tokens(new deque<Token *>) { }

TokenList::~TokenList() { delete _tokens; }

void TokenList::AddToken(Token * token) {
    _tokens->push_back(token);
}

TokenType TokenList::PeekType() const {
    return _tokens->front()->Type();
}

Token * TokenList::Front() const {
    return _tokens->front();
}

TokenList::TokenList(const TokenList &toCopy) : _tokens(new deque<Token *>) {
    for (auto i = toCopy._tokens->begin(); i != toCopy._tokens->end(); i++) {
        auto checkForNull = Token::Create((*i)->GetRaw());
        if (checkForNull != nullptr) _tokens->push_back(checkForNull);
    }
}

ostream &operator<<(ostream &os, const TokenList &tokenList) {
    for (auto i = tokenList._tokens->begin(); i != tokenList._tokens->end(); i++) {
        os << *(*i) << " ";
    }
    return os;
}

istream &operator>>(istream &is, TokenList &tokenList) {
    while (!is.eof()) {
        auto checkForNull = Token::Create(Lexer::LexNextToken(is));
        if (checkForNull != nullptr) tokenList._tokens->emplace_back(checkForNull);
    }
    return is;
}

Token * TokenList::SeekToNext(TokenType type, Token * from) {
    //deque<Token>::iterator start;
    //if (from != nullptr) {}
    auto start = _tokens->begin();
    if (from != nullptr) start = std::find(_tokens->begin(), _tokens->end(), from);

    for (auto cur = start; cur != _tokens->end(); cur++) {
        if ((*cur)->Type() == type && *cur != from) return *cur;
    }
    return nullptr;
}

Token * TokenList::SeekToNextSymbol(SymbolType stype) {
    for (auto i = SeekToNext(TokenType::Symbol); i != nullptr; i = SeekToNext(TokenType::Symbol, i)) {
        auto * symCast = (Symbol*)i;
        if (symCast->SymType() == stype) {
            return i;
        }
    }
    return nullptr;
}

Token * TokenList::SeekToNextKeyword(KeywordType ktype) {
    for (auto i = SeekToNext(TokenType::Keyword); i != nullptr; i = SeekToNext(TokenType::Keyword, i)) {
        auto * keyCast = (Keyword*)i;
        if (keyCast->KeyType() == ktype) {
            return i;
        }
    }
    return nullptr;
}

Token * TokenList::SeekToNextLiteral() {
    return SeekToNext(TokenType::Literal);
}

Token * TokenList::SeekToNextSymbol() {
    return SeekToNext(TokenType::Symbol);
}

Token * TokenList::SeekToNextKeyword() {
    return SeekToNext(TokenType::Keyword);
}

Token * TokenList::SeekToNextIdentifier() {
    return SeekToNext(TokenType::Identifier);
}

Token * TokenList::PopFront() {
    if (_tokens->front() != nullptr) {
        Token *toPop = _tokens->front();
        _tokens->pop_front();
        return toPop;
    }
    return nullptr;
}

TokenList *TokenList::SeekToPop(Token *toPopAfter) {
    auto toReturn = new TokenList();
    auto i = _tokens->front();
    while (i != toPopAfter) {
        i = _tokens->front();
        toReturn->_tokens->push_back(_tokens->front());
        _tokens->pop_front();
    }
    return toReturn;
}
