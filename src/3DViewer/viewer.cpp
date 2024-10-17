#define GL_SILENCE_DEPRECATION
#include "viewer.h"

#include <iostream>

Viewer::Viewer(QWidget *parent) : QOpenGLWidget{parent}, controller_() {}
void Viewer::initializeGL() { initializeOpenGLFunctions(); }

void Viewer::parseOBJ() {
  free_data();
  controller_.Parser(name_to_file);  // парсим файл
  number_of_vertices = controller_.GetNumberVertices();
  number_of_lines = controller_.GetNumberFacets();
  controller_.CenterVertices();
  controller_.InitialScale();
  vertices_ = controller_.GetVertices();
  facets_ = controller_.GetFacets();
}

void Viewer::paintGL() {
  initOpenGL();
  drawPoints();
  drawLines();
}

void Viewer::initOpenGL() {
  glEnable(GL_DEPTH_TEST);
  glClearColor(bg_color.redF(), bg_color.greenF(), bg_color.blueF(), 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  projection_view();
}

void Viewer::drawPoints() {
  glVertexPointer(3, GL_DOUBLE, 0, vertices_.data());
  glPointSize(point_size / 5.0f);
  if (point_type == 0) {
    glEnable(GL_POINT_SMOOTH);
  }
  if (point_type != 2) {
    glEnableClientState(GL_VERTEX_ARRAY);
    // Устанавливаем цвет для всех вершин
    glColor3f(point_color.redF(), point_color.greenF(), point_color.blueF());
    glDrawArrays(GL_POINTS, 0, vertices_.size());
    glDisableClientState(GL_VERTEX_ARRAY);
  }
  if (point_type == 0) {
    glDisable(GL_POINT_SMOOTH);
  }
}

void Viewer::drawLines() {
  if (number_of_lines > 0) {
    if (line_type == 1) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1, 26);
    }
    glLineWidth(line_size / 15.0f);
    if (line_type != 2) {
      // Включаем клиентское состояние массива вершин:
      glEnableClientState(GL_VERTEX_ARRAY);
      // Устанавливаем цвет линий:
      glColor3f(line_color.redF(), line_color.greenF(), line_color.blueF());
      // Отрисовываем линии с использованием индексов из массива граней
      // (facets):
      glDrawElements(GL_LINES, facets_.size(), GL_UNSIGNED_INT, facets_.data());
      // Отключаем состояние массива вершин:
      glDisableClientState(GL_VERTEX_ARRAY);
      // Отключаем прерывистую линию, если она была включена:
      if (line_type == 1) {
        glDisable(GL_LINE_STIPPLE);
      }
    }
  }
}

void Viewer::shift_view(double shifted, int ax) {
  if (ax == 0) {
    controller_.Shift(shifted, 0, 0);
  } else if (ax == 1) {
    controller_.Shift(0, shifted, 0);
  } else {
    controller_.Shift(0, 0, shifted);
  }
  vertices_ = controller_.GetVertices();
  update();
}
void Viewer::scale_view(double scale) {
  controller_.Scale(scale);
  vertices_ = controller_.GetVertices();
  update();
}

void Viewer::rotate_view(double degrees, int ax) {
  controller_.Rotate(degrees, ax);
  vertices_ = controller_.GetVertices();
  update();
}

void Viewer::projection_view() {
  if (projection_type == 0) {
    glOrtho(-1, 1, -1, 1, 0, 15);
    glTranslated(0, 0, -6);
  } else {
    glFrustum(-1, 1, -1, 1, 5, 20);
    glTranslated(0, 0, -8);
  }
}

void Viewer::free_data() { controller_.ClearObj(); }