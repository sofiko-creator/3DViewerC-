#ifndef IOBSERVER_H
#define IOBSERVER_H
#include <fstream>
#include <iostream>
#include <list>
#include <string>

namespace s21 {
class IObserver {
 public:
  virtual ~IObserver(){};
  virtual void Update(const std::string &message_from_subject) = 0;
};
}  // namespace s21

#endif  // IOBSERVER_H