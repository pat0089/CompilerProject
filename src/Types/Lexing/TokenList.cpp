#include "TokenList.hpp"
#include "Tokens.hpp"

using std::istream;
using std::ostream;

TokenList::TokenList() : _front(nullptr), _back(nullptr) { }

TokenList::TokenList(Token * tokens) : _front(tokens) {
    Token * iterator = _front;
    while (iterator != nullptr) {
        if (iterator->Next() == nullptr) {
            break;
        } else {
            iterator = iterator->Next();
        }
    }
    _back = iterator;
}

TokenList::~TokenList() {
    Token * iterator = _front;
    while (iterator->Next() != nullptr) {
        iterator = iterator->Next();
        delete iterator->Last();
    }
    delete iterator;
}

void TokenList::AddToken(Token *token) {
    if (token != nullptr) {
        if (_front == nullptr && _back == nullptr) {
            _front = _back = token;
        } else if (_back != nullptr) {
            _back->Next(token);
            token->Last(_back);
            _back = token;
        }
    }
}

TokenType TokenList::PeekType() const {
    TokenType temp;
    (_front == nullptr) ? temp = TokenType::None : temp = _front->Type();
    return temp;
}

Token * TokenList::PopFront() {
    Token * toPop = _front;
    _front = _front->Next();
    toPop->Next(nullptr);
    _front->Last(nullptr);
    return toPop;
}

void TokenList::PutbackFront(Token *token) {
    _front->Last(token);
    token->Next(_front);
    _front = token;
}

TokenList::TokenList(const TokenList &toCopy) {
    Token * iterator = toCopy._front;
    while (iterator != nullptr) {
        AddToken(Token::Create(iterator->GetRaw()));
        iterator = iterator->Next();
    }
}

ostream &operator<<(ostream &os, const TokenList &tokenList) {
    Token * iterator = tokenList._front;
    while (iterator != nullptr) {
        os << *iterator << " ";
        iterator = iterator->Next();
    }
    return os;
}

istream &operator>>(istream &is, TokenList &tokenList) {
    while (!is.eof()) {
        tokenList.AddToken(Token::Create(Lexer::LexNextToken(is)));
    }
    return is;
}

Token *TokenList::SeekTo(TokenType type) const {
    Token * iterator = _front;
    while (iterator != nullptr) {
        if (iterator->Type() == type) return iterator;
        iterator = iterator->Next();
    }
    return nullptr;
}

Token * TokenList::SeekAndPop(TokenType type) {
    return PopFromFront(SeekTo(type));
}

Token *TokenList::PopFromFront(Token *token) {
    Token * oldFront = _front;
    _front = token->Next();
    _front->Last(nullptr);
    token->Next(nullptr);
    return oldFront;
}

Token *TokenList::SeekToNextSymbol(SymbolType stype) const {
    auto toCheck = (Symbol *)SeekToNextSymbol();
    while (toCheck != nullptr) {
        if (toCheck->SymType() == stype) {
            return toCheck;
        }
    }
}

Token *TokenList::SeekToNextLiteral() const {
    return SeekTo(TokenType::Literal);
}

Token *TokenList::SeekToNextKeyword(KeywordType ktype) const {
    return SeekTo(TokenType::Keyword);
}

Token * TokenList::SeekToNextIdentifier() const {
    return SeekTo(TokenType::Identifier);
}

Token * TokenList::SeekSymbolPop(SymbolType stype) {
    return PopFromFront(SeekToNextSymbol(stype));
}

Token *TokenList::SeekToNextSymbol() const {
    return SeekTo(TokenType::Symbol);
}

Token *TokenList::PeekFront() {
    return _front;
}
