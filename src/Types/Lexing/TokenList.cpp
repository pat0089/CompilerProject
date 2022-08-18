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

Token &TokenList::operator[](int i) {
    return *_tokens->at(i);
}


bool TokenList::Verify() const {
    return match_all_braces();
}

bool TokenList::match_all_braces() const {

    std::stack<SymbolType> st;

    for (int i = 0; i < _tokens->size(); i++) {
        Token *temp = _tokens->at(i);
        TokenType type = temp->Type();
        if (type != TokenType::Symbol) continue;
        auto *stemp = (Symbol *) temp;
        SymbolType stype = stemp->SymType();

        if (stype != SymbolType::Open_Brace &&
            stype != SymbolType::Open_Bracket &&
            stype != SymbolType::Open_Chevron &&
            stype != SymbolType::Open_Parenthesis &&
            stype != SymbolType::Close_Brace &&
            stype != SymbolType::Close_Bracket &&
            stype != SymbolType::Close_Chevron &&
            stype != SymbolType::Close_Parenthesis
                )
            continue;

        if (stype == SymbolType::Open_Brace ||
            stype == SymbolType::Open_Bracket ||
            stype == SymbolType::Open_Chevron ||
            stype == SymbolType::Open_Parenthesis
                ) {
            st.push(stype);
        } else {
            //break the loop if met:
            if (st.empty()) return false;
            if (st.top() == SymbolType::Open_Brace && stype != SymbolType::Close_Brace) return false;
            if (st.top() == SymbolType::Open_Bracket && stype != SymbolType::Close_Bracket) return false;
            if (st.top() == SymbolType::Open_Chevron && stype != SymbolType::Close_Chevron) return false;
            if (st.top() == SymbolType::Open_Parenthesis && stype != SymbolType::Close_Parenthesis) return false;
            st.pop();
        }
    }
    return st.empty();
}
