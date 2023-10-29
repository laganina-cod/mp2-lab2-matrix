#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int>m(5);
	m[1][1] = 4;
	m[2][2]= 3;
	TDynamicMatrix<int> m1(m);
	EXPECT_EQ(4, m1[1][1]);
	EXPECT_EQ(3, m1[2][2]);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int>m(5);
	TDynamicMatrix<int>m1(m);
	m[1][1] = 4;
	m[2][2] = 3;
	EXPECT_NE(m[1][1], m1[1][1]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int>m(5);
	EXPECT_EQ(5, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int>m(5);
	m[1][1] = 4;
	EXPECT_EQ(4, m[1][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int>m(5);
	
	ASSERT_ANY_THROW(m[-1][0] = 4);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int>m(5);

	ASSERT_ANY_THROW(m[MAX_MATRIX_SIZE + 1][0] = 4);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(3);
	ASSERT_NO_THROW(m = m);
	m[1][1] = 1;
	m = m;
	EXPECT_EQ(1, m[1][1]);
	EXPECT_EQ(0, m[0][0]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(3);
	for (int i = 0; i < 3; i++) {
		m[i][i] = i;
	}
	m1 = m;
	EXPECT_EQ(0, m1[0][0]);
	EXPECT_EQ(1, m1[1][1]);
	EXPECT_EQ(2, m1[2][2]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> v(3);
	TDynamicMatrix<int> v1(5);
	v1 = v;
	EXPECT_EQ(3, v1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> v(3);
	v[1][1] = 1;
	v[0][0] = 1;
	v[2][2] = 1;
	TDynamicMatrix<int> v1(5);
	v1 = v;
	EXPECT_EQ(1, v1[0][0]);
	EXPECT_EQ(1, v1[1][1]);
	EXPECT_EQ(1, v1[2][2]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> v(3);
	v[0][0] = 1;
	v[1][1] = 2;
	v[2][2] = 3;
	TDynamicMatrix<int> v1(v);
	EXPECT_EQ(v, v1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> v(3);
	v[0][0] = 1;
	v[1][1] = 2;
	v[2][2] = 3;
	EXPECT_EQ(v, v);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> v(3);
	TDynamicMatrix<int> v1(5);
	EXPECT_NE(v, v1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(3);
	m1[0][0] = 3;
	m = m1 + m;
	EXPECT_EQ(3, m[0][0]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(5);
	ASSERT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(3);
	m1[0][0] = 3;
	m[0][0] = 1;
	m = m1 -m;
	EXPECT_EQ(2, m[0][0]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(5);
	ASSERT_ANY_THROW(m - m1);
}

