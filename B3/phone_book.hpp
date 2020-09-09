#ifndef PHONE_BOOK_B3
#define PHONE_BOOK_B3

#include <list>
#include <string>

class PhoneBook
{
public:
  struct record_t
  {
    std::string name;
    std::string number;
  };

  using container = std::list<record_t>;
  using iterator = container::iterator;

  void show(iterator rec) const;
  void pushBack(const record_t& rec);
  void replace(iterator tmpRec, const record_t& newRec);
  void insert(iterator pos, const record_t& rec);

  iterator begin();
  iterator end();
  iterator next(iterator pos);
  iterator prev(iterator pos);
  iterator move(iterator rec, int n);
  iterator erase(iterator pos);

  bool empty() const;

private:
  container records_;
};

#endif //PHONE_BOOK_B3
