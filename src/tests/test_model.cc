#include <gtest/gtest.h>

#include "../controller.h"

#define S21_EPS 1e-6

TEST(Parser, Test_1) {
  s21::Controller controller;
  std::string filename = "";
  EXPECT_THROW(controller.Parser(filename), std::runtime_error);
  controller.ClearObj();
}

TEST(Parser, Test_2) {
  std::string filename = "./objects/test.txt";
  s21::Controller controller;
  controller.Parser(filename);
  controller.CenterVertices();
  controller.InitialScale();
  EXPECT_EQ(controller.GetNumberVertices(), 8);
  EXPECT_EQ(controller.GetNumberFacets(), 12);
  EXPECT_EQ(controller.GetFacets().size(), 72);
  EXPECT_EQ(controller.GetFacets()[0], 0);
  EXPECT_EQ(controller.GetFacets()[1], 6);
  EXPECT_EQ(controller.GetFacets()[2], 6);
  EXPECT_EQ(controller.GetFacets()[3], 4);
  EXPECT_EQ(controller.GetFacets()[4], 4);
  EXPECT_EQ(controller.GetFacets()[5], 0);
  EXPECT_EQ(controller.GetFacets()[6], 0);
  EXPECT_EQ(controller.GetFacets()[7], 2);
  EXPECT_EQ(controller.GetFacets()[8], 2);
  EXPECT_EQ(controller.GetFacets()[9], 6);
  EXPECT_EQ(controller.GetFacets()[10], 6);
  EXPECT_EQ(controller.GetFacets()[11], 0);
  EXPECT_EQ(controller.GetFacets()[12], 0);
  EXPECT_EQ(controller.GetFacets()[13], 3);
  EXPECT_EQ(controller.GetFacets()[14], 3);
  EXPECT_EQ(controller.GetFacets()[15], 2);
  EXPECT_EQ(controller.GetFacets()[16], 2);
  EXPECT_EQ(controller.GetFacets()[17], 0);
  EXPECT_EQ(controller.GetFacets()[18], 0);
  EXPECT_EQ(controller.GetFacets()[19], 1);
  EXPECT_EQ(controller.GetFacets()[20], 1);
  EXPECT_EQ(controller.GetFacets()[21], 3);
  EXPECT_EQ(controller.GetFacets()[22], 3);
  EXPECT_EQ(controller.GetFacets()[23], 0);
  EXPECT_EQ(controller.GetFacets()[24], 2);
  EXPECT_EQ(controller.GetFacets()[25], 7);
  EXPECT_EQ(controller.GetFacets()[26], 7);
  EXPECT_EQ(controller.GetFacets()[27], 6);
  EXPECT_EQ(controller.GetFacets()[28], 6);
  EXPECT_EQ(controller.GetFacets()[29], 2);
  EXPECT_EQ(controller.GetFacets()[30], 2);
  EXPECT_EQ(controller.GetFacets()[31], 3);
  EXPECT_EQ(controller.GetFacets()[32], 3);
  EXPECT_EQ(controller.GetFacets()[33], 7);
  EXPECT_EQ(controller.GetFacets()[34], 7);
  EXPECT_EQ(controller.GetFacets()[35], 2);
  EXPECT_EQ(controller.GetFacets()[36], 4);
  EXPECT_EQ(controller.GetFacets()[37], 6);
  EXPECT_EQ(controller.GetFacets()[38], 6);
  EXPECT_EQ(controller.GetFacets()[39], 7);
  EXPECT_EQ(controller.GetFacets()[40], 7);
  EXPECT_EQ(controller.GetFacets()[41], 4);
  EXPECT_EQ(controller.GetFacets()[42], 4);
  EXPECT_EQ(controller.GetFacets()[43], 7);
  EXPECT_EQ(controller.GetFacets()[44], 7);
  EXPECT_EQ(controller.GetFacets()[45], 5);
  EXPECT_EQ(controller.GetFacets()[46], 5);
  EXPECT_EQ(controller.GetFacets()[47], 4);
  EXPECT_EQ(controller.GetFacets()[48], 0);
  EXPECT_EQ(controller.GetFacets()[49], 4);
  EXPECT_EQ(controller.GetFacets()[50], 4);
  EXPECT_EQ(controller.GetFacets()[51], 5);
  EXPECT_EQ(controller.GetFacets()[52], 5);
  EXPECT_EQ(controller.GetFacets()[53], 0);
  EXPECT_EQ(controller.GetFacets()[54], 0);
  EXPECT_EQ(controller.GetFacets()[55], 5);
  EXPECT_EQ(controller.GetFacets()[56], 5);
  EXPECT_EQ(controller.GetFacets()[57], 1);
  EXPECT_EQ(controller.GetFacets()[58], 1);
  EXPECT_EQ(controller.GetFacets()[59], 0);
  EXPECT_EQ(controller.GetFacets()[60], 1);
  EXPECT_EQ(controller.GetFacets()[61], 5);
  EXPECT_EQ(controller.GetFacets()[62], 5);
  EXPECT_EQ(controller.GetFacets()[63], 7);
  EXPECT_EQ(controller.GetFacets()[64], 7);
  EXPECT_EQ(controller.GetFacets()[65], 1);
  EXPECT_EQ(controller.GetFacets()[66], 1);
  EXPECT_EQ(controller.GetFacets()[67], 7);
  EXPECT_EQ(controller.GetFacets()[68], 7);
  EXPECT_EQ(controller.GetFacets()[69], 3);
  EXPECT_EQ(controller.GetFacets()[70], 3);
  EXPECT_EQ(controller.GetFacets()[71], 1);
  controller.ClearObj();
}

TEST(Scale, Test_1) {
  std::string filename = "./objects/test.txt";
  s21::Controller controller;
  controller.Parser(filename);
  size_t n = controller.GetVertices().size();
  std::vector<double> arr_x(n);
  std::vector<double> arr_y(n);
  std::vector<double> arr_z(n);

  for (size_t i = 0; i < n; ++i) {
    arr_x[i] = controller.GetVertices()[i].x;
    arr_y[i] = controller.GetVertices()[i].y;
    arr_z[i] = controller.GetVertices()[i].z;
  }
  int x = 2;
  controller.Scale(x);
  for (size_t i = 0; i < n; ++i) {
    EXPECT_EQ(controller.GetVertices()[i].x, arr_x[i] * x);
    EXPECT_EQ(controller.GetVertices()[i].y, arr_y[i] * x);
    EXPECT_EQ(controller.GetVertices()[i].z, arr_z[i] * x);
  }
  controller.ClearObj();
  arr_x.clear();
  arr_y.clear();
  arr_z.clear();
}

TEST(Scale, Test_2) {
  std::string filename = "./objects/test.txt";
  s21::Controller controller;
  controller.Parser(filename);
  size_t n = controller.GetVertices().size();
  std::vector<double> arr_x(n);
  std::vector<double> arr_y(n);
  std::vector<double> arr_z(n);
  for (size_t i = 0; i < n; ++i) {
    arr_x[i] = controller.GetVertices()[i].x;
    arr_y[i] = controller.GetVertices()[i].y;
    arr_z[i] = controller.GetVertices()[i].z;
  }
  int x = 5;
  controller.Scale(x);
  for (size_t i = 0; i < n; ++i) {
    EXPECT_EQ(controller.GetVertices()[i].x, arr_x[i] * x);
    EXPECT_EQ(controller.GetVertices()[i].y, arr_y[i] * x);
    EXPECT_EQ(controller.GetVertices()[i].z, arr_z[i] * x);
  }
  controller.ClearObj();
  arr_x.clear();
  arr_y.clear();
  arr_z.clear();
}

TEST(Shift, Test_1) {
  std::string filename = "./objects/test.txt";
  s21::Controller controller;
  controller.Parser(filename);
  size_t n = controller.GetVertices().size();
  std::vector<double> arr_x(n);
  std::vector<double> arr_y(n);
  std::vector<double> arr_z(n);
  for (size_t i = 0; i < n; ++i) {
    arr_x[i] = controller.GetVertices()[i].x;
    arr_y[i] = controller.GetVertices()[i].y;
    arr_z[i] = controller.GetVertices()[i].z;
  }
  int x = 5, y = 3, z = -7;
  controller.Shift(x, y, z);
  for (size_t i = 0; i < n; ++i) {
    EXPECT_EQ(controller.GetVertices()[i].x, arr_x[i] + x);
    EXPECT_EQ(controller.GetVertices()[i].y, arr_y[i] + y);
    EXPECT_EQ(controller.GetVertices()[i].z, arr_z[i] + z);
  }
  controller.ClearObj();
  arr_x.clear();
  arr_y.clear();
  arr_z.clear();
}

TEST(Shift, Test_2) {
  std::string filename = "./objects/test.txt";
  s21::Controller controller;
  controller.Parser(filename);
  size_t n = controller.GetVertices().size();
  std::vector<double> arr_x(n);
  std::vector<double> arr_y(n);
  std::vector<double> arr_z(n);
  for (size_t i = 0; i < n; ++i) {
    arr_x[i] = controller.GetVertices()[i].x;
    arr_y[i] = controller.GetVertices()[i].y;
    arr_z[i] = controller.GetVertices()[i].z;
  }
  int x = 24.05, y = 19.88, z = 5;
  controller.Shift(x, y, z);
  for (size_t i = 0; i < n; ++i) {
    EXPECT_NEAR(controller.GetVertices()[i].x, arr_x[i] + x, S21_EPS);
    EXPECT_NEAR(controller.GetVertices()[i].y, arr_y[i] + y, S21_EPS);
    EXPECT_NEAR(controller.GetVertices()[i].z, arr_z[i] + z, S21_EPS);
  }
  controller.ClearObj();
  arr_x.clear();
  arr_y.clear();
  arr_z.clear();
}

TEST(Rotate, Test_1) {
  std::string filename = "./objects/test.txt";
  s21::Controller controller;
  controller.Parser(filename);
  size_t n = controller.GetVertices().size();
  std::vector<double> arr_x(n);
  std::vector<double> arr_y(n);
  std::vector<double> arr_z(n);
  for (size_t i = 0; i < n; ++i) {
    arr_x[i] = controller.GetVertices()[i].x;
    arr_y[i] = controller.GetVertices()[i].y;
    arr_z[i] = controller.GetVertices()[i].z;
  }
  double degrees = 24.05;
  int ax = 0;
  controller.Rotate(degrees, ax);
  for (size_t i = 0; i < n; ++i) {
    EXPECT_NEAR(controller.GetVertices()[i].x, arr_x[i], S21_EPS);
    EXPECT_NEAR(controller.GetVertices()[i].y,
                arr_y[i] * cos(degrees * M_PI / 180) -
                    arr_z[i] * sin(degrees * M_PI / 180),
                S21_EPS);
    EXPECT_NEAR(controller.GetVertices()[i].z,
                arr_y[i] * sin(degrees * M_PI / 180) +
                    arr_z[i] * cos(degrees * M_PI / 180),
                S21_EPS);
  }
  controller.ClearObj();
  arr_x.clear();
  arr_y.clear();
  arr_z.clear();
}

TEST(Rotate, Test_2) {
  std::string filename = "./objects/test.txt";
  s21::Controller controller;
  controller.Parser(filename);
  size_t n = controller.GetVertices().size();
  std::vector<double> arr_x(n);
  std::vector<double> arr_y(n);
  std::vector<double> arr_z(n);
  for (size_t i = 0; i < n; ++i) {
    arr_x[i] = controller.GetVertices()[i].x;
    arr_y[i] = controller.GetVertices()[i].y;
    arr_z[i] = controller.GetVertices()[i].z;
  }
  double degrees = 24.05;
  int ax = 1;
  controller.Rotate(degrees, ax);
  for (size_t i = 0; i < n; ++i) {
    EXPECT_NEAR(controller.GetVertices()[i].x,
                arr_x[i] * cos(degrees * M_PI / 180) +
                    arr_z[i] * sin(degrees * M_PI / 180),
                S21_EPS);
    EXPECT_NEAR(controller.GetVertices()[i].y, arr_y[i], S21_EPS);
    EXPECT_NEAR(controller.GetVertices()[i].z,
                -arr_x[i] * sin(degrees * M_PI / 180) +
                    arr_z[i] * cos(degrees * M_PI / 180),
                S21_EPS);
  }
  controller.ClearObj();
  arr_x.clear();
  arr_y.clear();
  arr_z.clear();
}

TEST(Rotate, Test_3) {
  std::string filename = "./objects/test.txt";
  s21::Controller controller;
  controller.Parser(filename);
  size_t n = controller.GetVertices().size();
  std::vector<double> arr_x(n);
  std::vector<double> arr_y(n);
  std::vector<double> arr_z(n);
  for (size_t i = 0; i < n; ++i) {
    arr_x[i] = controller.GetVertices()[i].x;
    arr_y[i] = controller.GetVertices()[i].y;
    arr_z[i] = controller.GetVertices()[i].z;
  }
  double degrees = 24.05;
  int ax = 3;
  controller.Rotate(degrees, ax);
  for (size_t i = 0; i < n; ++i) {
    EXPECT_NEAR(controller.GetVertices()[i].x,
                arr_x[i] * cos(degrees * M_PI / 180) -
                    arr_y[i] * sin(degrees * M_PI / 180),
                S21_EPS);
    EXPECT_NEAR(controller.GetVertices()[i].y,
                arr_x[i] * sin(degrees * M_PI / 180) +
                    arr_y[i] * cos(degrees * M_PI / 180),
                S21_EPS);
    EXPECT_NEAR(controller.GetVertices()[i].z, arr_z[i], S21_EPS);
  }
  controller.ClearObj();
  arr_x.clear();
  arr_y.clear();
  arr_z.clear();
}

TEST(Seters, Test_1) {
  std::string filename = "./objects/test.txt";
  s21::Controller controller;
  controller.Parser(filename);
  EXPECT_EQ(controller.GetNumberVertices(), 8);
  EXPECT_EQ(controller.GetNumberFacets(), 12);
  controller.SetNumberVertices(0);
  controller.SetNumberFacets(0);
  EXPECT_EQ(controller.GetNumberVertices(), 0);
  EXPECT_EQ(controller.GetNumberFacets(), 0);
  controller.ClearObj();
}

// Запустите тесты
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}