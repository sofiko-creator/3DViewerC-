#ifndef OBSERVER_H
#define OBSERVER_H

#include <cstdlib>

#include "Subject.h"

namespace s21 {
class Observer : public IObserver {
 public:
  Observer(Subject &subject) : subject_(subject) {
    this->subject_.Attach(this);  // Добавляем себя в список наблюдателей
  }
  virtual ~Observer() {
    RemoveMeFromTheList();  // Удаляем себя из списка наблюдателей
  }

  void Update(const std::string &message_from_subject) override {
    message_from_subject_ = message_from_subject;
    PrintInfo();  // Логируем получение сообщения
  }

  void RemoveMeFromTheList() {
    subject_.Detach(this);  // Удаляем наблюдателя из списка
    const char *homeDir = std::getenv("HOME");
    std::ofstream outFile(
        std::string(homeDir) + "/CPP4_3DViewer_v2.0-1/src/log.txt",
        std::ios_base::app);  // Логируем удаление
    if (outFile.is_open()) {
      outFile << "Observer removed from the list.\n";
    }
  }

  void PrintInfo() {
    const char *homeDir = std::getenv("HOME");
    std::ofstream outFile(
        std::string(homeDir) + "/CPP4_3DViewer_v2.0-1/src/log.txt",
        std::ios_base::app);
    if (outFile.is_open()) {
      outFile << "Observer: a new message is available --> "
              << this->message_from_subject_ << "\n";
    }
  }

 private:
  std::string message_from_subject_;
  Subject &subject_;
};
}  // namespace s21
#endif  // OBSERVER_H
