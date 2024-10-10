#ifndef SUBJECT_H
#define SUBJECT_H

#include <cstdlib>

#include "ISubject.h"

namespace s21 {
class Subject : public ISubject {
 public:
  virtual ~Subject() {}

  /**
   * Методы управления подпиской.
   */
  void Attach(IObserver *observer) override {
    list_observer_.push_back(observer);
  }
  void Detach(IObserver *observer) override { list_observer_.remove(observer); }
  void Notify() override {
    std::list<IObserver *>::iterator iterator = list_observer_.begin();
    HowManyObserver();
    while (iterator != list_observer_.end()) {
      (*iterator)->Update(message_);
      ++iterator;
    }
  }

  void CreateMessage(std::string message = "Empty") {
    this->message_ = message;
    Notify();
  }
  void HowManyObserver() {
    const char *homeDir = std::getenv("HOME");
    std::ofstream outFile(
        std::string(homeDir) + "/CPP4_3DViewer_v2.0-1/src/log.txt",
        std::ios_base::app);  // Открываем файл в режиме добавления
    if (outFile.is_open()) {
      outFile << "There are " << list_observer_.size()
              << " observers in the list.\n";
    }
  }

 private:
  std::list<IObserver *> list_observer_;
  std::string message_;
};
}  // namespace s21
#endif  // SUBJECT_H