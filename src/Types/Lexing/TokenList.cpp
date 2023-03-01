#include "TokenList.hpp"
#include "Tokens.hpp"

using std::istream;
using std::ostream;
using std::deque;

TokenList::TokenList() : _tokens(new deque<Token *>) { }

TokenList::~TokenList() {
    while (!_tokens->empty()) {
        auto temp = PopFront();
        delete temp;
    }
    delete _tokens;
}

/// Peeks at the type of the front token
/// \return token type
TokenType TokenList::PeekType() const {
    return _tokens->front()->Type();
}

/// Peeks at the front of the list
/// \return pointer to Token at front
Token * TokenList::PeekFront() const {
    return _tokens->front();
}

/// Copy Constructor
/// \param toCopy list to copy
TokenList::TokenList(const TokenList &toCopy) : _tokens(new deque<Token *>) {
    for (auto & _token : *toCopy._tokens) {
        _tokens->emplace_back(_token->Clone());
    }
}

/// Stream output operator
/// \param os output operator
/// \param tokenList token list to output
/// \return reference to output stream
ostream &operator<<(ostream &os, const TokenList &tokenList) {
    for (auto & _token : *tokenList._tokens) {
        os << *_token << "\n";
    }
    return os;
}

/// Stream input operator
/// \param is input stream
/// \param tokenList token list to read in to
/// \return reference to input stream
istream &operator>>(istream &is, TokenList &tokenList) {
    while (!is.eof()) {
        auto checkForNull = Token::Create(Lexer::LexNextToken(is), Lexer::GetCurChar(), Lexer::GetCurLine());
        if (checkForNull != nullptr) tokenList._tokens->emplace_back(checkForNull);
    }
    return is;
}

/// Pop the token off the front of the list
/// \return the token we popped off
Token * TokenList::PopFront() {
    if (_tokens->front() != nullptr) {
        Token *toPop = _tokens->front();
        _tokens->pop_front();
        return toPop;
    }
    return nullptr;
}

Token &TokenList::operator[](int i) {
    return *_tokens->at(i);
}

/// Verify the token list contains close characters for each open one
/// \return All braces match one another
bool TokenList::Verify() const {
    return match_all_braces();
}

/// Matches all open braces, brackets, and parentheses with their respective closes
/// \return whether or not all braces have a open and close match
bool TokenList::match_all_braces() const {

    std::stack<SymbolType> st;

    for (auto temp : *_tokens) {
        TokenType type = temp->Type();
        if (type != TokenType::Symbol) continue;
        auto *stemp = (Symbol *) temp;
        SymbolType stype = stemp->SymType();

        if (stype != SymbolType::Open_Brace &&
            stype != SymbolType::Open_Bracket &&
            stype != SymbolType::Open_Parenthesis &&
            stype != SymbolType::Close_Brace &&
            stype != SymbolType::Close_Bracket &&
            stype != SymbolType::Close_Parenthesis
                )
            continue;

        if (stype == SymbolType::Open_Brace ||
            stype == SymbolType::Open_Bracket ||
            stype == SymbolType::Open_Parenthesis
                ) {
            st.push(stype);
        } else {
            //break the loop if met:
            if (st.empty()) return false;
            if (st.top() == SymbolType::Open_Brace && stype != SymbolType::Close_Brace) return false;
            if (st.top() == SymbolType::Open_Bracket && stype != SymbolType::Close_Bracket) return false;
            if (st.top() == SymbolType::Open_Parenthesis && stype != SymbolType::Close_Parenthesis) return false;
            st.pop();
        }
    }
    return st.empty();
}

/// Puts back the given token to the front of the list of tokens
/// \param t token to put back
void TokenList::PutbackFront(Token *t) {
    _tokens->push_front(t);
}

/// Is the list empty?
/// \return list is empty or not
bool TokenList::Empty() {
    return _tokens->empty();
}
