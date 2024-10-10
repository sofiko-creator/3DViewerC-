#ifndef SHIFT_COMMAND_H
#define SHIFT_COMMAND_H

#include "model.h"
// Конкретная команда изменения перемещения
namespace s21 {
class ShiftCommand : public Command {
 private:
  Model* receiver;
  double x, y, z;

 public:
  ShiftCommand(Model* r, double x_, double y_, double z_)
      : receiver(r), x(x_), y(y_), z(z_) {}
  void execute() const override { receiver->Shift(x, y, z); }
};
}  // namespace s21

#endif  // SRC_SHIFT_COMMAND_H