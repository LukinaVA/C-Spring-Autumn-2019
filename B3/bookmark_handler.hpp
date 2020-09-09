#ifndef BOOKMARK_HANDLER_B3
#define BOOKMARK_HANDLER_B3

#include <map>
#include "phone_book.hpp"

class BookmarkHandler
{
public:
  enum class InsertDirection
  {
    before,
    after
  };

  enum class MoveDirection
  {
    first,
    last
  };

  BookmarkHandler();
  void add(const PhoneBook::record_t& rec);
  void store(const std::string& tmpMark, const std::string& name);
  void insert(InsertDirection direction, const std::string& bookmark, const PhoneBook::record_t& rec);
  void erase(const std::string& bookmark);
  void show(const std::string& bookmark);
  void move(const std::string& bookmark, int step);
  void move(const std::string& bookmark, MoveDirection position);

private:
  using bookmarks = std::map<std::string, PhoneBook::iterator>;

  PhoneBook phonebook_;
  bookmarks bookmarks_;
  bookmarks::iterator getBookmarkIterator(const std::string& bookmark);
};

#endif //BOOKMARK_HANDLER_B3
