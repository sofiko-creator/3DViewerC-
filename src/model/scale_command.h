#ifndef SCALE_COMMAND_H
#define SCALE_COMMAND_H

#include "model.h"
// Конкретная команда изменения размера
namespace s21 {
class ScaleCommand : public Command {
 private:
  Model* receiver;
  double scale;

 public:
  ScaleCommand(Model* r, double scale_) : receiver(r), scale(scale_) {}
  void execute() const override { receiver->Scale(scale); }
};
}  // namespace s21

#endif  // SRC_SCALE_COMMAND_H