#pragma once
#include <cassert>
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

	matrix rotate90() {
		matrix output = transpose();
		output.reverse();
		return output;
	}

	void rotate90InPlaceSq() {
		transposeInPlaceSq();
		reverse();
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
		assert(length > 0 && height > 0, "Length or height were 0 or less than 0");

		m_v2d = std::vector<std::vector<T>>(height);

		for (int z = 0; z < height; ++z) {
			m_v2d[z] = std::vector<T>(length);
		}

		m_count = length * height;
		m_height = height;
		m_length = length;
	}

private:
	void reverse() {
		for (int i = 0; i < m_height; ++i) {
			int j = 0, k = m_length - 1;
			std::vector<T>& row = m_v2d[i];

			for (int l = 0; j < k; l++) {	// l < m_height/2 works also
				T jVal = row[j], kVal = row[k];
				row[j] = kVal; row[k] = jVal;

				k--; j++;
			}
		}
	}

	void ValidateIndex(const int rowIndex, const int colIndex) const {
		assert(rowIndex < m_height, "Row index cannot be greater than the height of the matrix");
		assert(colIndex < m_length, "Column index cannot be greater than the length of the matrix");
		assert(rowIndex >= 0, "Row index is less than zero");
		assert(colIndex >= 0, "Column index is less than zero");
	}

	std::vector<std::vector<T>> m_v2d{};
	int m_count{};
	int m_height{};
	int m_length{};
};
