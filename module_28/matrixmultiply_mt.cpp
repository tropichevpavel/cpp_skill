#include <vector>
#include <iostream>
#include <future>

typedef std::vector<std::vector<int>> matrix_t;

bool make_thread = true;

auto multiply_matrix(const matrix_t& matrix1, const matrix_t& matrix2) -> matrix_t
{
	matrix_t tmp;
	std::vector<int> tmp_row;

	int matrix1_rows = matrix1.size(),
		matrix2_rows = matrix2.size(),
		matrix2_columns = matrix2[0].size();

	for (int i = 0; i < matrix1_rows; ++i)
	{
		for (int j = 0; j < matrix2_columns; ++j)
		{
			int tmp_val = 0;
			for (int k = 0; k < matrix2_rows; ++k) tmp_val += matrix1[i][k] * matrix2[k][j];
			tmp_row.push_back(tmp_val);
		}
		tmp.push_back(tmp_row);
		tmp_row.clear();
	}
	return tmp;
}

std::mutex lock_result;

auto multiply_matrix_row(matrix_t& result, const matrix_t& matrix1, const matrix_t& matrix2, const int& matrix1_row) -> void
{
	std::vector<int> tmp_row;

	int matrix2_rows = matrix2.size(),
		matrix2_columns = matrix2[0].size();

	for (int j = 0; j < matrix2_columns; ++j)
	{
		int tmp_val = 0;
		for (int k = 0; k < matrix2_rows; ++k) tmp_val += matrix1[matrix1_row][k] * matrix2[k][j];
		tmp_row.push_back(tmp_val);
	}

	std::lock_guard<std::mutex> tmp_lock(lock_result);
	result[matrix1_row] = std::move(tmp_row);
}

auto multiply_matrix_thread(const matrix_t& matrix1, const matrix_t& matrix2) -> matrix_t
{
	matrix_t tmp;

	const int& matrix1_rows = matrix1.size();

	tmp.resize(matrix1_rows);

	std::vector<std::future<void>> futures;

	for (int i = 0; i < matrix1_rows; ++i)
	{
		futures.push_back(std::async(std::launch::async, multiply_matrix_row, std::ref(tmp), std::ref(matrix1), std::ref(matrix2), i));
	}
	return tmp;
}

auto fill_matrix(matrix_t& matrix, const int& rows, const int& columns) -> void
{
	for (int i = 0; i < rows; ++i)
	{
		std::vector<int> tmp;
		for (int j = 0; j < columns; ++j) tmp.push_back(rand() % 5000000);
		matrix.push_back(tmp);
	}
}

int main()
{
	matrix_t matrix1, matrix2;

	fill_matrix(matrix1, 5000, 20);
	fill_matrix(matrix2, 20, 7000);

	time_t start, end;

	time(&start);
	auto result = multiply_matrix(matrix1, matrix2);
	time(&end);

	std::cout << "The time: " << difftime(end, start) << " seconds" << std::endl;

	// for (auto& column : result)
	// {
	// 	for (auto& row : column)
	// 	{
	// 		std::cout << row << " ";
	// 	}
	// 	std::cout << std::endl;
	// }

	std::cout << std::endl;

	time(&start);
	result = multiply_matrix_thread(matrix1, matrix2);
	time(&end);

	std::cout << "The time: " << difftime(end, start) << " seconds" << std::endl;

	// for (auto& column : result)
	// {
	// 	for (auto& row : column)
	// 	{
	// 		std::cout << row << " ";
	// 	}
	// 	std::cout << std::endl;
	// }

	return 0;
}