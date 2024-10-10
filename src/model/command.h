#ifndef COMMAND_H
#define COMMAND_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
/**
 * Интерфейс Команды объявляет метод для выполнения команд.
 */
class Command {
 public:
  virtual ~Command() {}
  virtual void execute() const = 0;
};
}  // namespace s21

#endif  // SRC_COMMAND_H