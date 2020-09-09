#ifndef QUEUE_B2
#define QUEUE_B2

#include <list>
#include <string>
#include <stdexcept>

template <typename ElementType>
class QueueWithPriority
{
public:
  enum class ElementPriority
  {
    LOW,
    NORMAL,
    HIGH
  };

  void PutElementToQueue(const ElementType& element, ElementPriority priority);
  ElementType GetElementFromQueue();
  void Accelerate();
  bool empty() const;

private:
  std::list<ElementType> low_;
  std::list<ElementType> normal_;
  std::list<ElementType> high_;
};

template <typename ElementType>
void QueueWithPriority<ElementType>::PutElementToQueue(const ElementType& element, ElementPriority priority)
{
  switch(priority)
  {
  case ElementPriority::LOW:
    low_.push_back(element);
    break;
  case ElementPriority::NORMAL:
    normal_.push_back(element);
    break;
  case ElementPriority::HIGH:
    high_.push_back(element);
    break;
  }
}

template <typename ElementType>
ElementType QueueWithPriority<ElementType>::GetElementFromQueue()
{
  if (!high_.empty())
  {
    ElementType element = high_.front();
    high_.pop_front();
    return element;
  }
  else if (!normal_.empty())
  {
    ElementType element = normal_.front();
    normal_.pop_front();
    return element;
  }
  else if (!low_.empty())
  {
    ElementType element = low_.front();
    low_.pop_front();
    return element;
  }
  else
  {
    throw std::invalid_argument("Empty queue!");
  }
}

template <typename ElementType>
void QueueWithPriority<ElementType>::Accelerate()
{
  high_.splice(high_.end(), low_);
}

template <typename ElementType>
bool QueueWithPriority<ElementType>::empty() const
{
  return high_.empty() && normal_.empty() && low_.empty();
}

#endif //QUEUE_B2
