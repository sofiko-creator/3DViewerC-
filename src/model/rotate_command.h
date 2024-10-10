#ifndef ROTATE_COMMAND_H
#define ROTATE_COMMAND_H

#include "model.h"
// Конкретная команда изменения размера
namespace s21 {
class RotateCommand : public Command {
 private:
  Model* receiver;
  double degrees;
  int ax;

 public:
  RotateCommand(Model* r, double degrees_, int ax_)
      : receiver(r), degrees(degrees_), ax(ax_) {}
  void execute() const override { receiver->Rotate(degrees, ax); }
};
}  // namespace s21

#endif  // SRC_ROTATE_COMMAND_H