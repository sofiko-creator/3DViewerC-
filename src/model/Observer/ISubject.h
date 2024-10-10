#ifndef ISUBJECT_H
#define ISUBJECT_H

#include "IObserver.h"

namespace s21 {

class ISubject {
 public:
  virtual ~ISubject(){};
  virtual void Attach(IObserver *observer) = 0;
  virtual void Detach(IObserver *observer) = 0;
  virtual void Notify() = 0;
};
}  // namespace s21
#endif  // ISISUBJECT_H