#ifndef TOKEN_HPP
#define TOKEN_HPP

#define TYPE_AS_STRING(t)                                                      \
  case t:                                                                      \
    return #t;

#include <string>
#include <variant>
namespace tk {

enum TokenType {
  MAIN_OPTION,
  SUB_OPTION,
  COLON,
  DOT,
  HYPHEN,
  SPACE,
  LINE_BREAK,
  NUMBER,
  WORD,
  NONE,
};

typedef std::variant<int, double, bool, std::string> TokenValue;

class Token {
private:
  TokenType type;
  TokenValue value;

public:
  // Default constructor
  Token() : type(NONE) {} // Default value for integer
  Token(TokenType t) : type(t) {}
  Token(TokenType t, int intValue) : type(t), value(intValue) {}
  Token(TokenType t, double doubleValue) : type(t), value(doubleValue) {}
  Token(TokenType t, bool boolValue) : type(t), value(boolValue) {}
  Token(TokenType t, std::string stringValue) : type(t), value(stringValue) {}

  TokenType getType() const { return type; }
  TokenValue getValue() const { return value; }
  std::string getTypeAsString() const {
    switch (type) {
      TYPE_AS_STRING(MAIN_OPTION);
      TYPE_AS_STRING(SUB_OPTION);
      TYPE_AS_STRING(COLON);
      TYPE_AS_STRING(DOT);
      TYPE_AS_STRING(HYPHEN);
      TYPE_AS_STRING(SPACE);
      TYPE_AS_STRING(LINE_BREAK);
      TYPE_AS_STRING(NUMBER);
      TYPE_AS_STRING(WORD);
      TYPE_AS_STRING(NONE);
    }
  }
};

} // namespace tk

#endif // !TOKEN_HPP
