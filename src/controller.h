#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <iostream>
#include <memory>  // Для std::unique_ptr
#include <string>

#include "model/Observer/IObserver.h"
#include "model/Observer/ISubject.h"
#include "model/Observer/Observer.h"
#include "model/Observer/Subject.h"
#include "model/command.h"
#include "model/invoker.h"
#include "model/model.h"
#include "model/rotate_command.h"
#include "model/scale_command.h"
#include "model/shift_command.h"

namespace s21 {
class Controller {
 public:
  Controller()
      : subject(std::make_unique<s21::Subject>()),
        observer(std::make_unique<s21::Observer>(*subject)) {}
  ~Controller() = default;

  void Parser(const std::string &filename) { model_->ParseFile(filename); }

  size_t GetNumberVertices() const { return model_->GetNumberVertices(); }

  size_t GetNumberFacets() const { return model_->GetNumberFacets(); }

  void CenterVertices() { model_->CenterVertices(); }

  void InitialScale() { model_->InitialScale(); }

  void Shift(double x, double y, double z) {
    std::unique_ptr<Command> shiftCommand =
        std::make_unique<ShiftCommand>(model_, x, y, z);
    invoker.SetCommand(std::move(shiftCommand));
    invoker.Invoke();
    subject->CreateMessage("Shift object!");
  }

  void Scale(double scale) {
    std::unique_ptr<Command> scaleCommand =
        std::make_unique<ScaleCommand>(model_, scale);
    invoker.SetCommand(std::move(scaleCommand));
    invoker.Invoke();
    subject->CreateMessage("Scale object!");
  }

  void Rotate(double degrees, int ax) {
    std::unique_ptr<Command> rotateCommand =
        std::make_unique<RotateCommand>(model_, degrees, ax);
    invoker.SetCommand(std::move(rotateCommand));
    invoker.Invoke();
    subject->CreateMessage("Rotate object!");
  }

  std::vector<s21::Vertex> GetVertices() const { return model_->GetVertices(); }

  std::vector<unsigned int> GetFacets() const { return model_->GetFacets(); }

  // Для обнуления кол-ва вершин и рёбер перед открытием нового файла
  void SetNumberVertices(int number_vertices) {
    model_->SetNumberVertices(number_vertices);
  }

  void SetNumberFacets(int number_facets) {
    model_->SetNumberFacets(number_facets);
  }

  // Для очистки старой фигуры
  void ClearObj() { model_->ClearObj(); }

 private:
  Model *model_ = Model::getInstance();
  s21::Invoker invoker;
  std::unique_ptr<s21::Subject> subject;
  std::unique_ptr<s21::Observer> observer;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_H_
