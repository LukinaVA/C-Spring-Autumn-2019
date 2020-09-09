#include "handler.hpp"

Handler::Handler(size_t lineWidth) :
    lineWidth_(lineWidth),
    prevElementType_(),
    text_()
{ }

void Handler::inputAndCheckText()
{
  while (std::cin)
  {
    char ch = (std::cin >> std::ws).get();

    if (isalpha(ch))
    {
      std::cin.unget();
      readWord();
    }
    else if (ch == '-')
    {
      if (std::cin.peek() == '-')
      {
        std::cin.unget();
        readHyphen();
      }
      else
      {
        std::cin.unget();
        readNumber();
      }
    }
    else if ((isdigit(ch)) || (ch == '+'))
    {
      std::cin.unget();
      readNumber();
    }
    else if (ispunct(ch))
    {
      std::cin.unget();
      readPunctuation();
    }
  }
}

void Handler::formatAndPrintText()
{
  size_t tmpLength = 0;
  std::list<Handler::element_t> string;

  for (auto& element : text_)
  {
    switch (element.elementType_)
    {
      case Handler::element_t::Hyphen:
      {
        if (tmpLength + 4 > lineWidth_)
        {
          tmpLength = reformatString(string);
        }
        string.push_back(element_t{element_t::Space, " " });
        string.push_back(element);
        tmpLength += element.str_.length() + 1;
        break;
      }
      case element_t::Number:
      case element_t::Word:
      {
        if (tmpLength + element.str_.length() + 1 > lineWidth_)
        {
          printString(string);
          string.clear();
          tmpLength = 0;
        }
        else if (!string.empty())
        {
          string.push_back(element_t{element_t::Space, " " });
          tmpLength++;
        }
        string.push_back(element);
        tmpLength += element.str_.length();
        break;
      }
      case element_t::Punctuation:
      {
        if (tmpLength + 1 > lineWidth_)
        {
          tmpLength = reformatString(string);
        }
        string.push_back(element);
        tmpLength += element.str_.length();
        break;
      }
      case element_t::Space:
      {
        break;
      }
    }
  }
  if (!string.empty())
  {
    printString(string);
  }
}

void Handler::readWord()
{
  element_t element{element_t::Word , "" };

  while ((std::isalpha<char>(std::cin.peek(), std::locale())) || (std::cin.peek() == '-'))
  {
    char ch = std::cin.get();
    element.str_.push_back(ch);
    if ((ch == '-') && (std::cin.peek() == '-'))
    {
      element.str_.pop_back();
      std::cin.unget();
      break;
    }
  }

  if (element.str_.size() > 20)
  {
    throw std::invalid_argument("Length of word > 20 symbols!");
  }

  prevElementType_ = element_t::Word;
  text_.push_back(element);
}

void Handler::readNumber()
{
  element_t element{element_t::Number, "" };
  const char decimalPoint = std::use_facet<std::numpunct<char>>(std::locale()).decimal_point();
  bool was_decimal = false;

  do
  {
    char ch = std::cin.get();
    if (ch == decimalPoint)
    {
      if (was_decimal)
      {
        throw std::invalid_argument("Invalid number!");
      }
      was_decimal = true;
    }
    element.str_.push_back(ch);
  } while ((std::isdigit<char>(std::cin.peek(), std::locale())) || ((std::cin.peek() == decimalPoint)));

  if (element.str_.size() > 20)
  {
    throw std::invalid_argument("Length of number > 20 symbols!");
  }

  prevElementType_ = element_t::Number;
  text_.push_back(element);
}

void Handler::readHyphen()
{
  if (text_.empty())
  {
    throw std::invalid_argument("Text can`t start with punctuation!");
  }

  element_t element{element_t::Hyphen, "" };
  while (std::cin.peek() == '-')
  {
    element.str_.push_back(std::cin.get());
  }

  if (element.str_.size() != 3)
  {
    throw std::invalid_argument("Wrong hyphen number!");
  }
  if (prevElementType_ == element_t::Hyphen)
  {
    throw std::invalid_argument("Hyphen after hyphen!");
  }
  if ((prevElementType_ == element_t::Punctuation) && (text_.back().str_ != ","))
  {
    throw std::invalid_argument("Hyphen after punctuation!");
  }
  prevElementType_ = element_t::Hyphen;
  text_.push_back(element);
}

void Handler::readPunctuation()
{
  if (text_.empty())
  {
    throw std::invalid_argument("Text can`t start with punctuation!");
  }

  element_t element{element_t::Punctuation, "" };
  element.str_.push_back(std::cin.get());

  if (prevElementType_ == element_t::Hyphen)
  {
    throw std::invalid_argument("Punctuation after hyphen!");
  }
  if (prevElementType_ == element_t::Punctuation)
  {
    throw std::invalid_argument("Punctuation after punctuation!");
  }

  prevElementType_ = element_t::Punctuation;
  text_.push_back(element);
}

void Handler::printString(const std::list<Handler::element_t>& str)
{
  for (const auto& iter : str)
  {
    std::cout << iter.str_;
  }
  std::cout << "\n";
}

size_t Handler::reformatString(std::list<Handler::element_t>& str)
{
  size_t tmpLength = 0;
  std::list<Handler::element_t> tmpString;

  while (!str.empty())
  {
    tmpString.push_front(str.back());
    tmpLength += str.back().str_.length();
    str.pop_back();
    if ((tmpString.front().elementType_ == element_t::Word) || (tmpString.front().elementType_ == element_t::Number))
    {
      break;
    }
  }

  printString(str);
  str = tmpString;
  return tmpLength;
}
