#ifndef HANDLER_B8
#define HANDLER_B8

#include <list>
#include <locale>
#include <string>
#include <iostream>

class Handler
{
public:
  struct element_t
  {
    enum type_e
    {
      Word,
      Space,
      Number,
      Hyphen,
      Punctuation
    };
    type_e elementType_;
    std::string str_;
  };

  Handler(size_t lineWidth = 40);

  void inputAndCheckText();
  void formatAndPrintText();

private:
  size_t lineWidth_;
  element_t::type_e prevElementType_;
  std::list<element_t> text_;

  void readWord();
  void readNumber();
  void readHyphen();
  void readPunctuation();
  void printString(const std::list<Handler::element_t>& str);
  size_t reformatString(std::list<Handler::element_t>& str);
};

#endif //HANDLER_B8
