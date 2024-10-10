#ifndef INVOKER_H
#define INVOKER_H

#include <memory>  // Для использования unique_ptr

#include "command.h"

namespace s21 {

class Invoker {
 private:
  // Ссылка на команду, которую должен выполнить Invoker
  std::unique_ptr<Command> command_;

 public:
  // Метод для установки команды
  void SetCommand(std::unique_ptr<Command> command) {
    command_ = std::move(command);  // Передача владения командой
  }

  // Метод для выполнения команды
  void Invoke() const {
    if (command_) {
      command_->execute();
    }
  }
};

}  // namespace s21

#endif  // INVOKER_H
