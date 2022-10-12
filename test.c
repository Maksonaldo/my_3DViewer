#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "parsing.h"
#include "afins.h"


START_TEST(s21_parsing_test) {
  double matrix[8][3];
  int index[6][5];

  index[0][0] = 1;
  index[0][1] = 3;
  index[0][2] = 4;
  index[0][3] = 2;
  index[1][0] = 5;
  index[1][1] = 7;
  index[1][2] = 8;
  index[1][3] = 6;
  index[2][0] = 5;
  index[2][1] = 6;
  index[2][2] = 1;
  index[2][3] = 2;
  index[3][0] = 8;
  index[3][1] = 7;
  index[3][2] = 4;
  index[3][3] = 3;
  index[4][0] =  6;
  index[4][1] =  8;
  index[4][2] =  3;
  index[4][3] =  1;
  index[5][0] = 2;
  index[5][1] =  4;
  index[5][2] =  7;
  index[5][3] =  5;

  matrix[0][0] = 0.50000;
  matrix[0][1] = 0.500000;
  matrix[0][2] = 0.500000;
  matrix[1][0] = 0.500000;
  matrix[1][1] = 0.500000;
  matrix[1][2] = -0.500000;
  matrix[2][0] = 0.500000;
  matrix[2][1] = -0.500000;
  matrix[2][2] = 0.500000;
  matrix[3][0] = 0.500000;
  matrix[3][1] = -0.500000;
  matrix[3][2] = -0.500000;
  matrix[4][0] =  -0.500000;
  matrix[4][1] =  0.500000;
  matrix[4][2] =  -0.500000;
  matrix[5][0] = -0.500000;
  matrix[5][1] =  0.500000;
  matrix[5][2] =  0.500000;
  matrix[6][0] =  -0.500000;
  matrix[6][1] =  -0.500000;
  matrix[6][2] =  -0.500000;
  matrix[7][0] =  -0.500000;
  matrix[7][1] =  -0.500000;
  matrix[7][2] =  0.500000;
  Data data;
  data = parsing("objects/cube-3d-shape.obj");
  for (int i = 0; i < data.vertexRows; i++) {
    for (int j = 0; j < 3; j++) {
       ck_assert_double_eq_tol(data.vertex[i][j], matrix[i][j], 1e-6);
    }
  }
  for (int i = 0; i < data.indexRows; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(data.index[i][j], index[i][j]);
    }
  }

  //  test_myScaled
  myScaled(data.vertex, data.vertexRows, 1.4);
  for (int i = 0; i <8; i++) {
    for (int j = 0; j < 3; j++) {
      matrix[i][j] = matrix[i][j] * 1.4;
    }
  }
  for (int i = 0; i < data.vertexRows; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(data.vertex[i][j], matrix[i][j], 1e-6);
    }
  }
  freeData(data);
}
END_TEST

START_TEST(s21_translated_test) {
  Data data;
  data = parsing("objects/cube-3d-shape.obj");
  myTranslated(data.vertex, data.vertexRows, X, POSITIVE, 0.8);
  myTranslated(data.vertex, data.vertexRows, Y, POSITIVE, 0.4);
  myTranslated(data.vertex, data.vertexRows, Z, POSITIVE, 1.6);
  ck_assert_double_eq_tol(data.vertex[0][0], 1.300000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[0][1], 0.900000 , 1e-6);
  ck_assert_double_eq_tol(data.vertex[0][2], 2.100000, 1e-6);

  ck_assert_double_eq_tol(data.vertex[1][0], 1.300000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[1][1], 0.900000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[1][2], 1.100000, 1e-6);

  ck_assert_double_eq_tol(data.vertex[2][0], 1.300000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[2][1], -0.100000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[2][2], 2.100000 , 1e-6);

  ck_assert_double_eq_tol(data.vertex[3][0], 1.300000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[3][1], -0.100000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[3][2], 1.100000, 1e-6);

  ck_assert_double_eq_tol(data.vertex[4][0], 0.300000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[4][1], 0.900000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[4][2], 1.100000 , 1e-6);

  ck_assert_double_eq_tol(data.vertex[5][0], 0.300000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[5][1], 0.900000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[5][2], 2.100000, 1e-6);

  ck_assert_double_eq_tol(data.vertex[6][0], 0.300000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[6][1], -0.100000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[6][2], 1.100000, 1e-6);

  ck_assert_double_eq_tol(data.vertex[7][0], 0.300000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[7][1], -0.100000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[7][2], 2.100000, 1e-6);
  freeData(data);
}
END_TEST

START_TEST(s21_translated_negative) {
  Data data;
  data = parsing("objects/cube-3d-shape.obj");
  myTranslated(data.vertex, data.vertexRows, X, NEGATIVE, 12);
  myTranslated(data.vertex, data.vertexRows, Y, NEGATIVE, 7.1);
  myTranslated(data.vertex, data.vertexRows, Z, NEGATIVE, 2.1);
  ck_assert_double_eq_tol(data.vertex[0][0], -11.500000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[0][1], -6.600000 , 1e-6);
  ck_assert_double_eq_tol(data.vertex[0][2], -1.600000 , 1e-6);

  ck_assert_double_eq_tol(data.vertex[1][0], -11.500000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[1][1], -6.600000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[1][2], -2.600000 , 1e-6);

  ck_assert_double_eq_tol(data.vertex[2][0], -11.500000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[2][1], -7.600000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[2][2], -1.600000 , 1e-6);

  ck_assert_double_eq_tol(data.vertex[3][0], -11.500000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[3][1], -7.600000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[3][2], -2.600000 , 1e-6);

  ck_assert_double_eq_tol(data.vertex[4][0], -12.500000 , 1e-6);
  ck_assert_double_eq_tol(data.vertex[4][1], -6.600000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[4][2], -2.600000  , 1e-6);

  ck_assert_double_eq_tol(data.vertex[5][0], -12.500000 , 1e-6);
  ck_assert_double_eq_tol(data.vertex[5][1], -6.600000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[5][2], -1.600000, 1e-6);

  ck_assert_double_eq_tol(data.vertex[6][0], -12.500000 , 1e-6);
  ck_assert_double_eq_tol(data.vertex[6][1], -7.600000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[6][2], -2.600000, 1e-6);

  ck_assert_double_eq_tol(data.vertex[7][0], -12.500000 , 1e-6);
  ck_assert_double_eq_tol(data.vertex[7][1], -7.600000, 1e-6);
  ck_assert_double_eq_tol(data.vertex[7][2], -1.600000, 1e-6);
  freeData(data);
}
END_TEST

START_TEST(s21_rotated_test) {
  Data data;
  data = parsing("objects/cube-3d-shape.obj");
  myRotated(data.vertex, data.vertexRows, X, POSITIVE, 1.6);
  myRotated(data.vertex, data.vertexRows, Y, POSITIVE, 0.8);
  myRotated(data.vertex, data.vertexRows, Z, POSITIVE, 4.2);
  ck_assert_double_eq_tol(data.vertex[0][0], 0.529471, 1e-6);
  ck_assert_double_eq_tol(data.vertex[0][1], 0.476267 , 1e-6);
  ck_assert_double_eq_tol(data.vertex[0][2], 0.492778, 1e-6);

  ck_assert_double_eq_tol(data.vertex[1][0], 0.541345, 1e-6);
  ck_assert_double_eq_tol(data.vertex[1][1], 0.447399, 1e-6);
  ck_assert_double_eq_tol(data.vertex[1][2], -0.506735, 1e-6);

  ck_assert_double_eq_tol(data.vertex[2][0], 0.455872, 1e-6);
  ck_assert_double_eq_tol(data.vertex[2][1], -0.520630, 1e-6);
  ck_assert_double_eq_tol(data.vertex[2][2], 0.520697 , 1e-6);

  ck_assert_double_eq_tol(data.vertex[3][0], 0.467747, 1e-6);
  ck_assert_double_eq_tol(data.vertex[3][1], -0.549498, 1e-6);
  ck_assert_double_eq_tol(data.vertex[3][2], -0.478816, 1e-6);

  ck_assert_double_eq_tol(data.vertex[4][0], -0.455872, 1e-6);
  ck_assert_double_eq_tol(data.vertex[4][1], 0.520630, 1e-6);
  ck_assert_double_eq_tol(data.vertex[4][2], -0.520697 , 1e-6);

  ck_assert_double_eq_tol(data.vertex[5][0], -0.467747, 1e-6);
  ck_assert_double_eq_tol(data.vertex[5][1], 0.549498, 1e-6);
  ck_assert_double_eq_tol(data.vertex[5][2], 0.478816, 1e-6);

  ck_assert_double_eq_tol(data.vertex[6][0], -0.529471, 1e-6);
  ck_assert_double_eq_tol(data.vertex[6][1], -0.476267, 1e-6);
  ck_assert_double_eq_tol(data.vertex[6][2], -0.492778, 1e-6);

  ck_assert_double_eq_tol(data.vertex[7][0], -0.541345, 1e-6);
  ck_assert_double_eq_tol(data.vertex[7][1], -0.447399, 1e-6);
  ck_assert_double_eq_tol(data.vertex[7][2], 0.506735, 1e-6);
  freeData(data);
}
END_TEST

START_TEST(s21_rotated_test_negative) {
  Data data;
  data = parsing("objects/cube-3d-shape.obj");
  myRotated(data.vertex, data.vertexRows, X, NEGATIVE, 8.2);
  myRotated(data.vertex, data.vertexRows, Y, NEGATIVE, 6.3);
  myRotated(data.vertex, data.vertexRows, Z, NEGATIVE, 0.7);
  ck_assert_double_eq_tol(data.vertex[0][0], 0.553896, 1e-6);
  ck_assert_double_eq_tol(data.vertex[0][1], 0.430373 , 1e-6);
  ck_assert_double_eq_tol(data.vertex[0][2], 0.507916, 1e-6);

  ck_assert_double_eq_tol(data.vertex[1][0], 0.443549, 1e-6);
  ck_assert_double_eq_tol(data.vertex[1][1], 0.571664, 1e-6);
  ck_assert_double_eq_tol(data.vertex[1][2], -0.475883, 1e-6);

  ck_assert_double_eq_tol(data.vertex[2][0], 0.550338, 1e-6);
  ck_assert_double_eq_tol(data.vertex[2][1], -0.559521, 1e-6);
  ck_assert_double_eq_tol(data.vertex[2][2], 0.366149 , 1e-6);

  ck_assert_double_eq_tol(data.vertex[3][0], 0.439991, 1e-6);
  ck_assert_double_eq_tol(data.vertex[3][1], -0.418229, 1e-6);
  ck_assert_double_eq_tol(data.vertex[3][2], -0.617650, 1e-6);

  ck_assert_double_eq_tol(data.vertex[4][0], -0.550338, 1e-6);
  ck_assert_double_eq_tol(data.vertex[4][1], 0.559521, 1e-6);
  ck_assert_double_eq_tol(data.vertex[4][2], -0.366149 , 1e-6);

  ck_assert_double_eq_tol(data.vertex[5][0], -0.439991, 1e-6);
  ck_assert_double_eq_tol(data.vertex[5][1], 0.418229, 1e-6);
  ck_assert_double_eq_tol(data.vertex[5][2], 0.617650, 1e-6);

  ck_assert_double_eq_tol(data.vertex[6][0], -0.553896, 1e-6);
  ck_assert_double_eq_tol(data.vertex[6][1], -0.430373, 1e-6);
  ck_assert_double_eq_tol(data.vertex[6][2], -0.507916 , 1e-6);

  ck_assert_double_eq_tol(data.vertex[7][0], -0.443549, 1e-6);
  ck_assert_double_eq_tol(data.vertex[7][1], -0.571664, 1e-6);
  ck_assert_double_eq_tol(data.vertex[7][2], 0.475883, 1e-6);
  freeData(data);
}
END_TEST



int main(void) {
  Suite *s_s21_3d = suite_create("s21_3d");
  TCase *tc_s21_3d = tcase_create("s21_3d_test");
  SRunner *sr = srunner_create(s_s21_3d);
  suite_add_tcase(s_s21_3d, tc_s21_3d);
  tcase_add_test(tc_s21_3d, s21_parsing_test);
  tcase_add_test(tc_s21_3d, s21_translated_test);
  tcase_add_test(tc_s21_3d, s21_rotated_test);
  tcase_add_test(tc_s21_3d, s21_translated_negative);
  tcase_add_test(tc_s21_3d, s21_rotated_test_negative);
  srunner_run_all(sr, CK_ENV);
  srunner_ntests_failed(sr);
  srunner_free(sr);
}
