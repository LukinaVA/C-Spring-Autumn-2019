#include <iostream>
#include <algorithm>

#include "bookmark_handler.hpp"

BookmarkHandler::BookmarkHandler()
{
  bookmarks_["current"] = phonebook_.begin();
}

void BookmarkHandler::add(const PhoneBook::record_t& rec)
{
  phonebook_.pushBack(rec);
  if (phonebook_.begin() == std::prev(phonebook_.end()))
  {
    bookmarks_["current"] = phonebook_.begin();
  }
}

void BookmarkHandler::store(const std::string& tmpMark, const std::string& newMark)
{
  auto bookmarkIterator = getBookmarkIterator(tmpMark);
  if (bookmarkIterator != bookmarks_.end())
  {
    bookmarks_.emplace(newMark, bookmarkIterator->second);
  }
}

void BookmarkHandler::insert(BookmarkHandler::InsertDirection direction, const std::string& bookmark, const PhoneBook::record_t& rec)
{
  auto bookmarkIterator = getBookmarkIterator(bookmark);

  if (bookmarkIterator->second == phonebook_.end())
  {
    add(rec);
    return;
  }
  if (bookmarkIterator != bookmarks_.end())
  {
    auto pos = (direction == InsertDirection::before) ? bookmarkIterator->second : std::next(bookmarkIterator->second);
    phonebook_.insert(pos, rec);
  }
}

void BookmarkHandler::erase(const std::string& bookmark)
{
  auto bookmarkIterator = getBookmarkIterator(bookmark);

  if (bookmarkIterator != bookmarks_.end())
  {
    auto eraseIterator = bookmarkIterator->second;

    auto find = [&](auto& iterator)
    {
        if (iterator.second == eraseIterator)
        {
          if (std::next(iterator.second) == phonebook_.end())
          {
            iterator.second = phonebook_.prev(eraseIterator);
          }
          else
          {
            iterator.second = phonebook_.next(eraseIterator);
          }
        }
    };

    std::for_each(bookmarks_.begin(), bookmarks_.end(), find);

    phonebook_.erase(eraseIterator);
  }
}

void BookmarkHandler::show(const std::string& bookmark)
{
  auto bookmarkIterator = getBookmarkIterator(bookmark);

  if (bookmarkIterator != bookmarks_.end())
  {
    if (phonebook_.empty())
    {
      std::cout << "<EMPTY>\n";
      return;
    }
    phonebook_.show(bookmarkIterator->second);
  }
}

void BookmarkHandler::move(const std::string& bookmark, int step)
{
  auto bookmarkIterator = getBookmarkIterator(bookmark);

  if (bookmarkIterator != bookmarks_.end())
  {
    bookmarkIterator->second = phonebook_.move(bookmarkIterator->second, step);
  }
}

void BookmarkHandler::move(const std::string& bookmark, BookmarkHandler::MoveDirection dir)
{
  auto bookmarkIterator = getBookmarkIterator(bookmark);

  if (bookmarkIterator != bookmarks_.end())
  {
    bookmarkIterator->second = (dir == BookmarkHandler::MoveDirection::first) ? phonebook_.begin() : std::prev(phonebook_.end());
  }
}

BookmarkHandler::bookmarks::iterator BookmarkHandler::getBookmarkIterator(const std::string& bookmark)
{
  auto bookmarkIterator = bookmarks_.find(bookmark);

  if (bookmarkIterator != bookmarks_.end())
  {
    return bookmarkIterator;
  }
  else
  {
    std::cout << "<INVALID BOOKMARK>\n";
    return bookmarks_.end();
  }
}
