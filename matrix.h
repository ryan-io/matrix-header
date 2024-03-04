#pragma once
#include <iostream>
#include <string>
#include <vector>

template <typename T>
struct matrix {
	const T& get(const int rowIndex, const int colIndex) const {
		ValidateIndex(rowIndex, colIndex);

		const std::vector<T>& row = m_v2d[rowIndex];
		const T& col = row[colIndex];

		return col;
	}

	T getValue(const int rowIndex, const int colIndex) const {
		ValidateIndex(rowIndex, colIndex);

		const std::vector<T>& row = m_v2d[rowIndex];
		const T col = row[colIndex];
		return col;
	}

	void set(const int row, const int col, const T value) {
		setByIndex(row - 1, col - 1, value);
	}

	void setByIndex(const int rowIndex, const int colIndex, const T value) {
		ValidateIndex(rowIndex, colIndex);

		std::vector<T>& row = m_v2d.at(rowIndex);
		T& col = row.at(colIndex);
		col = value;
	}

	int getCount() const {
		return m_count;
	}

	int getLength() const {
		return m_length;
	}

	int getHeight() const {
		return m_height;
	}

	matrix transpose() {
		matrix output = matrix<int>(m_height, m_length);

		for (int x = 0; x < m_height; ++x) {
			for (int y = 0; y < m_length; y++) {
				std::vector<T>& rowO = m_v2d[x];
				T colO = rowO[y];

				std::vector<T>& rowN = output.m_v2d[y];
				T& colN = rowN[x];

				colN = colO;
			}
		}

		return output;
	}

	void transposeInPlaceSq() {
		if (m_height != m_length)
			throw std::exception("Matrix must be square to transpose in place.");

		for (int x = 0; x < m_height; ++x) {
			for (int y = x; y < m_length; y++) {
				if (x == y)
					continue;

				T val1 = getValue(x, y);
				T val2 = getValue(y, x);

				setByIndex(x, y, val2);
				setByIndex(y, x, val1);
			}
		}
	}

	void print() const {
		std::cout << '\n';

		for (int i = 0; i < m_height; ++i) {
			for (int j = 0; j < m_length; j++) {
				const T& v = get(i, j);
				std::cout << std::to_string(v) << ' ';

				if (j == m_length - 1)
					std::cout << '\n';
			}
		}
	}

	explicit matrix(const int length, const int height) {
		m_v2d = std::vector<std::vector<T>>(height);
		
		for (int z = 0; z < height; ++z) {
			m_v2d[z] = std::vector<T>(length);
		}

		m_count = length * height;
		m_height = height;
		m_length = length;
	}

private:
	void ValidateIndex(const int rowIndex, const int colIndex) const {
		if (rowIndex >= m_height)
			throw std::out_of_range("Row index cannot be greater than the height of the matrix");

		if (colIndex >= m_length)
			throw std::out_of_range("Column index cannot be greater than the length of the matrix");

		if (rowIndex < 0)
			throw std::out_of_range("Row index is less than zero");

		if (colIndex < 0)
			throw std::out_of_range("Column index is less than zero");
	}

	std::vector<std::vector<T>> m_v2d{};
	int m_count{};
	int m_height{};
	int m_length{};
};
