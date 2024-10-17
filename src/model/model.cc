#include "model.h"

// Определение статической переменной-члена
s21::Model* s21::Model::instance = nullptr;

s21::Model::Model() : number_vertices_(0), number_facets_(0) {}

s21::Model::~Model() { ClearObj(); }

// Методы

void s21::Model::ParseFile(const std::string file_name) {
  std::ifstream inputFile(file_name);
  if (!inputFile.is_open()) {
    throw std::runtime_error("Ошибка при открытии файла!");
  }
  std::string line;
  while (std::getline(inputFile, line)) {
    if (line[0] == 'v' && line[1] == ' ') {
      ParseLineV(line.substr(2));
    } else if (line[0] == 'f' && line[1] == ' ') {
      ParseLineF(line.substr(2));
    }
  }
  inputFile.close();
}

void s21::Model::ParseLineV(const std::string line) {
  double x, y, z;
  std::istringstream iss(line);
  if (iss >> x >> y >> z) {
    vertices_.emplace_back(x, y, z);
    number_vertices_++;
  } else {
    // std::cerr << "Ошибка чтения данных из строки!" << std::endl;
    throw std::runtime_error("Ошибка чтения данных из строки!");
  }
}

void s21::Model::ParseLineF(const std::string line) {
  int num_vertices_on_current_face = 0;  // количество вершин на текущей грани
  std::vector<int> vertices_indexes;
  ScanLineF(line, &num_vertices_on_current_face, vertices_indexes);

  for (int i = 0; i < num_vertices_on_current_face; i++) {
    if (vertices_indexes[i] < 1) {
      vertices_indexes[i] = number_vertices_ + vertices_indexes[i] + 1;
    }
    if (vertices_indexes[i] > number_vertices_) {
      num_vertices_on_current_face = 0;
    }
  }
  if (num_vertices_on_current_face > 0) {
    ++number_facets_;
    for (int i = 1; i < num_vertices_on_current_face; i++) {
      facets_.push_back(vertices_indexes[i - 1] - 1);
      facets_.push_back(vertices_indexes[i] - 1);
    }
    facets_.push_back(vertices_indexes[num_vertices_on_current_face - 1] - 1);
    facets_.push_back(vertices_indexes[0] - 1);
  }
  vertices_indexes.clear();
}

void s21::Model::ScanLineF(std::string line, int* num_vertices_on_current_face,
                           std::vector<int>& vertices_indexes) {
  int v_1, v_2, v_3;
  int matches;
  bool found;
  std::istringstream stream(line);
  while (true) {
    // Пропустить ведущие пробелы
    while (std::isspace(stream.peek())) {
      stream.get();
    }
    found = false;
    // Считывание в формате v/vt/vn
    if (stream >> v_1) {
      if (stream.peek() == '/') {
        stream.get();
        if (stream.peek() == '/') {
          // Формат v//vn
          stream.get();
          if (stream >> v_3) {
            matches = 2;
          } else {
            matches = 0;
            throw std::runtime_error(
                "Ошибка: некорректный формат v//vn в строке: " + line);
          }
        } else if (stream >> v_2) {
          if (stream.peek() == '/') {
            // Формат v/vt/vn
            stream.get();
            if (stream >> v_3) {
              matches = 3;
            } else {
              matches = 2;
            }
          } else {
            matches = 2;  // Формат v/vt
          }
        } else {
          matches = 1;  // Формат v/
        }
      } else {
        matches = 1;  // Формат v
      }
      if (matches >= 1) {
        (*num_vertices_on_current_face)++;
        vertices_indexes.push_back(v_1);
        found = true;
      }
    }
    if (!found) {
      break;
      throw std::runtime_error("Ошибка чтения данных из строки F: " + line);
    }
  }
}

int s21::Model::NumberVertices() { return (int)vertices_.size(); }

void s21::Model::CenterVertices() {
  double x_min = 0, x_max = 0, y_min = 0, y_max = 0, z_min = 0, z_max = 0;
  FindMaxMinValues(&x_min, &x_max, &y_min, &y_max, &z_min, &z_max);
  for (int i = 0; i < number_vertices_; i++) {
    vertices_[i].x = vertices_[i].x - x_min / 2 - x_max / 2;
    vertices_[i].y = vertices_[i].y - y_min / 2 - y_max / 2;
    vertices_[i].z = vertices_[i].z - z_min / 2 - z_max / 2;
  }
}

void s21::Model::Scale(double scale) {
  for (int i = 0; i < number_vertices_; i++) {
    vertices_[i].x *= scale;
    vertices_[i].y *= scale;
    vertices_[i].z *= scale;
  }
}

void s21::Model::Rotate(double degrees, int ax) {
  degrees = degrees * M_PI / 180;
  if (ax == 0) {
    for (int i = 0; i < number_vertices_; i++) {
      double y = vertices_[i].y;
      double z = vertices_[i].z;

      vertices_[i].y = y * cos(degrees) - z * sin(degrees);
      vertices_[i].z = y * sin(degrees) + z * cos(degrees);
    }
  } else if (ax == 1) {
    for (int i = 0; i < number_vertices_; i++) {
      double x = vertices_[i].x;
      double z = vertices_[i].z;

      vertices_[i].x = x * cos(degrees) + z * sin(degrees);
      vertices_[i].z = -x * sin(degrees) + z * cos(degrees);
    }
  } else {
    for (int i = 0; i < number_vertices_; i++) {
      double x = vertices_[i].x;
      double y = vertices_[i].y;

      vertices_[i].x = x * cos(degrees) - y * sin(degrees);
      vertices_[i].y = x * sin(degrees) + y * cos(degrees);
    }
  }
}

void s21::Model::Shift(double x, double y, double z) {
  for (int i = 0; i < number_vertices_; i++) {
    vertices_[i].x += x;
    vertices_[i].y += y;
    vertices_[i].z += z;
  }
}

void s21::Model::InitialScale() {
  double x_min = 0, x_max = 0, y_min = 0, y_max = 0, z_min = 0, z_max = 0;
  double max = 0;
  FindMaxMinValues(&x_min, &x_max, &y_min, &y_max, &z_min, &z_max);
  max = x_max - x_min;
  if (y_max - y_min > max) {
    max = y_max - y_min;
  }
  if (z_max - z_min > max) {
    max = z_max - z_min;
  }
  double scale_number = 1.4 / max;
  Scale(scale_number);
}

void s21::Model::FindMaxMinValues(double* x_min, double* x_max, double* y_min,
                                  double* y_max, double* z_min, double* z_max) {
  for (int i = 0; i < number_vertices_; i++) {
    if (i == 0) {
      *x_min = vertices_[i].x;
      *x_max = *x_min;
      *y_min = vertices_[i].y;
      *y_max = *y_min;
      *z_min = vertices_[i].z;
      *z_max = *z_min;
    } else {
      if (vertices_[i].x > *x_max) {
        *x_max = vertices_[i].x;
      } else if (vertices_[i].x < *x_min) {
        *x_min = vertices_[i].x;
      }

      if (vertices_[i].y > *y_max) {
        *y_max = vertices_[i].y;
      } else if (vertices_[i].y < *y_min) {
        *y_min = vertices_[i].y;
      }

      if (vertices_[i].z > *z_max) {
        *z_max = vertices_[i].z;
      } else if (vertices_[i].z < *z_min) {
        *z_min = vertices_[i].z;
      }
    }
  }
}

// Геттеры

int s21::Model::GetNumberVertices() const { return number_vertices_; }

int s21::Model::GetNumberFacets() const { return number_facets_; }

const std::vector<s21::Vertex>& s21::Model::GetVertices() const {
  return vertices_;
}

const std::vector<unsigned int>& s21::Model::GetFacets() const {
  return facets_;
}

// Сеттеры

void s21::Model::SetNumberVertices(int number_vertices) {
  number_vertices_ = number_vertices;
}

void s21::Model::SetNumberFacets(int number_facets) {
  number_facets_ = number_facets;
}

void s21::Model::ClearObj() {
  if (!vertices_.empty()) {
    vertices_.clear();
  }
  if (!facets_.empty()) {
    facets_.clear();
  }
  number_vertices_ = 0;
  number_facets_ = 0;
}