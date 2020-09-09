#ifndef ITERATOR_B3
#define ITERATOR_B3

#include <iterator>

class Iterator: public std::iterator<std::bidirectional_iterator_tag, size_t>
{
public:
  Iterator();
  Iterator(size_t);

  pointer operator ->();
  reference operator *();

  Iterator& operator ++();
  Iterator operator ++(int);
  Iterator& operator --();
  Iterator operator --(int);


  bool operator ==(const Iterator&);
  bool operator !=(const Iterator&);

private:
  size_t index_;
  size_t factorial_;
  size_t getFactorial(size_t index) const;
};

#endif //ITERATOR_B3
