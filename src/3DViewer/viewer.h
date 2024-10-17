#ifndef VIEWER_H
#define VIEWER_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>
#include <string>

#include "../controller.h"

class Viewer : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT
 public:
  explicit Viewer(QWidget *parent = nullptr);

  QColor bg_color = Qt::white;
  QColor line_color = Qt::black;
  QColor point_color = Qt::black;
  std::string name_to_file;
  float point_size;
  int point_type;
  int line_type;
  float line_size;
  int projection_type;
  void parseOBJ();
  void shift_view(double shifted, int ax);
  void scale_view(double scale);
  void rotate_view(double degrees, int ax);
  void projection_view();
  int number_of_vertices;
  int number_of_lines;
  void free_data();

 protected:
  std::vector<s21::Vertex> vertices_;
  std::vector<unsigned int> facets_;
  s21::Controller controller_;
  void initializeGL() override;
  void paintGL() override;
  void initOpenGL();
  void drawPoints();
  void drawLines();
};

#endif  // VIEWER_H
