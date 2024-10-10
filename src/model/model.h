#ifndef MODEL_H
#define MODEL_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "command.h"
namespace s21 {

class Model {
 public:
  struct Vertex {
    double x, y, z;
    Vertex(double x, double y, double z) : x(x), y(y), z(z) {}
  };

  // Конструкторы
 private:
  // Приватный конструктор, чтобы предотвратить создание объекта через new
  Model();
  ~Model();

 public:
  // Методы
  // Приватный копирующий конструктор и оператор присваивания для предотвращения
  // копирования
  Model(const Model&) = delete;
  Model& operator=(const Model&) = delete;

  // Статическая переменная-член, которая хранит единственный экземпляр
  static Model* instance;

  // Статический метод для получения экземпляра Model
  static Model* getInstance() {
    if (instance == nullptr) {
      instance = new Model();  // Lazy initialization
    }
    return instance;
  }
  /**
   * @brief Метод ParseFile предназначен для разбора текстового файла,
   * содержащего информацию о вершинах и грани модели. Если разбор проходит
   * успешно, координаты вершин добавляются в vertices_, а грани добавляются в
   * faces_.
   * @param file_name имя текстового файла, содержащего информацию о вершинах и
   * грани модели.
   */
  void ParseFile(const std::string file_name);

  /**
   * @brief Метод ParseLineV предназначен для разбора строки, содержащей
   * координаты вершины в формате x y z, и добавления этих координат в список
   * вершин модели. Если разбор строки проходит успешно, координаты добавляются
   * в vertices_, а счетчик количества вершин увеличивается. Если строка не
   * содержит корректные данные, выбрасывается исключение.
   * @param line строка, содержащая координаты вершины, разделенные пробелами.
   */
  void ParseLineV(const std::string line);

  /**
   * @brief Парсит строку, представляющую грань многоугольника, и обновляет
   * внутреннее представление модели.
   *
   * Этот метод анализирует входную строку, извлекая индексы вершин, которые
   * образуют грань. Если индексы меньше 1, они конвертируются в общее
   * количество вершин, добавляя их к `number_vertices_`. Если индексы превышают
   * общее количество вершин, количество вершин текущей грани сбрасывается.
   * Затем индексы вершин используются для формирования списка граней.
   *
   * @param line Строка, представляющая грань многоугольника, которую нужно
   * проанализировать.
   */
  void ParseLineF(const std::string line);

  /**
   * @brief Метод ScanLineF обрабатывает строку, содержащую данные о гранях
   * 3D-модели в формате OBJ.
   *
   * Этот метод анализирует строку, представляющую грани модели, и извлекает
   * индексы вершин, а также при необходимости текстурные и нормальные векторы.
   * Он полезен для разбора файлов формата OBJ, используемых в приложениях
   * 3D-графики.
   *
   * @param line Строка, содержащая информацию о гранях модели.
   * @param num_vertices_on_current_face Указатель на целочисленное значение,
   *        где будет храниться количество вершин на текущей грани после разбора
   * строки.
   * @param vertices_indexes Вектор, в который будут добавлены индексы вершин,
   *        извлеченные из строки.
   *
   * @note Убедитесь, что строка корректна и соответствует спецификации формата
   * OBJ. Метод не обрабатывает ошибки, связанные с неправильным форматом
   * строки.
   */
  void ScanLineF(std::string line, int* num_vertices_on_current_face,
                 std::vector<int>& vertices_indexes);

  /**
   * @brief Метод PrintVertices печатает список вершин модели.
   */
  void PrintVertices();  // print vertices

  /**
   * @brief Метод PrintFacets печатает список граней модели.
   */
  void PrintFacets();  // print facets

  /**
   * @brief Метод NumberVertices возвращает количество вершин в модели.
   * @return количество вершин в модели
   */
  int NumberVertices();

  void CenterVertices();

  // command
  void Scale(double scale);
  // command
  void Rotate(double degrees, int ax);
  // command
  void Shift(double x, double y, double z);

  void InitialScale();

  void FindMaxMinValues(double* x_min, double* x_max, double* y_min,
                        double* y_max, double* z_min, double* z_max);

  // Геттеры

  int GetNumberVertices() const;

  int GetNumberFacets() const;

  const std::vector<s21::Model::Vertex>& GetVertices() const;

  const std::vector<unsigned int>& GetFacets() const;

  // Сеттеры

  void SetNumberVertices(int number_vertices);
  void SetNumberFacets(int number_facets);

  // Чистка
  void ClearObj();

  // Константы

  // const double kM_PI = 3.14159265358979323846;

 private:
  int number_vertices_;           //количество вершин
  int number_facets_;             //количество граней
  std::vector<Vertex> vertices_;  //вершины

  //грани (polygons) [n1, n2, n2, n3, n3, n4, ...]
  std::vector<unsigned int> facets_;
};

}  // namespace s21

#endif  // SRC_MODEL_H