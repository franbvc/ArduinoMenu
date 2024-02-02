#include "token.hpp"
#include <cctype>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

#define TOKENIZE(C, T)                                                         \
  case C:                                                                      \
    t = tk::Token(tk::T);                                                      \
    break;

vector<char> readChars(string filename) {
  vector<char> charVec;
  string line;
  ifstream toRead(filename);

  if (toRead.is_open()) {
    while (getline(toRead, line)) {
      for (char c : line) {
        charVec.push_back(c);
      }
      charVec.push_back('\n');
    }
    toRead.close();
  }

  return charVec;
}

bool isWordFirstChar(char c) { return isalpha(c) || c == '_'; }

bool isWordMiddleChar(char c) { return isalpha(c) || isdigit(c) || c == '_'; }

string selectWord(vector<char> chars, int &index) {
  string s = "";
  char c;
  s += chars[index];
  index++;

  while (index < chars.size()) {
    c = chars[index];
    if (!isWordMiddleChar(c))
      break;

    s += c;
    index++;
  }

  return s;
}

int selectNumber(vector<char> chars, int &index) {
  string s = "";
  char c;
  s += chars[index];
  index++;

  while (index < chars.size()) {
    c = chars[index];
    if (!isdigit(c))
      break;

    s += chars[index];
    index++;
  }

  return stoi(s);
}

tk::Token charToToken(char c) {
  tk::Token t;

  switch (c) {
    TOKENIZE(':', COLON)
    TOKENIZE('.', DOT)
    TOKENIZE('-', HYPHEN)
    TOKENIZE(' ', SPACE)
    TOKENIZE('\r', LINE_BREAK)
    TOKENIZE('\n', LINE_BREAK)
  default:
    string err = "Lexical error: invalid token";
    throw runtime_error(err + c);
  }

  return t;
}

vector<tk::Token> getTokens(vector<char> chars) {
  vector<tk::Token> tokenList;
  int index = 0;
  char c;

  while (index < chars.size()) {
    c = chars[index];

    if (isWordFirstChar(c)) {
      string word = selectWord(chars, index);
      tokenList.push_back(tk::Token(tk::WORD, word));
      continue;
    }

    if (isdigit(c)) {
      int num = selectNumber(chars, index);
      tokenList.push_back(tk::Token(tk::NUMBER, num));
      continue;
    }

    tokenList.push_back(charToToken(c));
    index++;
  }

  return tokenList;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    perror("No filename passed as argument");
    return 1;
  }

  vector<char> chars = readChars(argv[1]);
  vector<tk::Token> tokens = getTokens(chars);

  for (int i = 0; i < tokens.size(); i++) {
    tk::Token t = tokens[i];
    tk::TokenType typ = t.getType();

    cout << "Token " << i << ": " << t.getTypeAsString();

    if (typ == tk::NUMBER)
      cout << " -> " << get<int>(t.getValue());

    if (typ == tk::WORD)
      cout << " -> " << get<string>(t.getValue());
    cout << endl;
  }

  return 0;
}
