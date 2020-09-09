#include "phone_book.hpp"

#include <iostream>

void PhoneBook::show(iterator rec) const
{
  std::cout << rec->number << ' ' << rec->name << '\n';
}

void PhoneBook::pushBack(const record_t& rec)
{
  records_.push_back(rec);
}

void PhoneBook::replace(iterator tmpRec, const record_t& newRec)
{
  *tmpRec = newRec;
}

void PhoneBook::insert(iterator pos, const record_t& rec)
{
  records_.insert(pos, rec);
}

PhoneBook::iterator PhoneBook::begin()
{
  return records_.begin();
}

PhoneBook::iterator PhoneBook::end()
{
  return records_.end();
}

PhoneBook::iterator PhoneBook::next(iterator pos)
{
  if (pos != records_.end())
  {
    return ++pos;
  }
  else
  {
    return pos;
  }
}

PhoneBook::iterator PhoneBook::prev(iterator pos)
{
  if (pos != records_.begin())
  {
    return --pos;
  }
  else
  {
    return pos;
  }
}

PhoneBook::iterator PhoneBook::move(PhoneBook::iterator rec, int n)
{
  if (n >= 0)
  {
    while (std::next(rec) != records_.end() && (n > 0))
    {
      rec = next(rec);
      --n;
    }
  }
  else
  {
    while (rec != records_.begin() && (n < 0))
    {
      rec = prev(rec);
      ++n;
    }
  }
  return rec;
}

PhoneBook::iterator PhoneBook::erase(iterator pos)
{
  return records_.erase(pos);
}

bool PhoneBook::empty() const
{
  return records_.empty();
}
