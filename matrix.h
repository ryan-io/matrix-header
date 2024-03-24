#pragma once
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
struct matrix {
    [[nodiscard]] const T& get(const int rowIndex, const int colIndex) const {
        ValidateIndex(rowIndex, colIndex);
        return m_v2d.at(getIndex(rowIndex, colIndex));
    }

    [[nodiscard]] T getValue(const int rowIndex, const int colIndex) {
        ValidateIndex(rowIndex, colIndex);
        return m_v2d[getIndex(rowIndex, colIndex)];
    }

    void set(const int rowIndex, const int colIndex, T value) {
        ValidateIndex(rowIndex, colIndex);
        m_v2d[getIndex(rowIndex, colIndex)] = value;
    }

    void reverseInPlace() {
        for (int iterator = 0; iterator < m_height; ++iterator) {
            int j = 0, k = m_length - 1;

            for (int iterator2 = 0; j < k; ++iterator2) {
                T jVal = get(iterator, j), kVal = get(iterator, k);
                set(iterator, j, kVal);
                set(iterator, k, jVal);

                k--; j++;
            }
        }
    }

    std::vector<T> reverse() {
        std::vector<T> output = std::vector<T>(m_count);

        for (int iterator = 0; iterator < m_height; ++iterator) {
            int j = 0, k = m_length - 1;

            for (int iterator2 = 0; j < k; ++iterator2) {
                T jVal = getValue(iterator, j),
                    kVal = getValue(iterator, k);

                output[getIndex(iterator, k)] = jVal;
                output[getIndex(iterator, j)] = kVal;

                k--; j++;
            }
        }

        return output;
    }

    void printReverse() {
        auto r = reverse();

        for (int i = 0; i < m_count; ++i) {
            const int row = i / m_length;
            const int col = i % m_length;

            std::cout << r[getIndex(row, col)];

            if (col == m_length - 1)
                std::cout << '\n';
            else
                std::cout << "--";
        }
    }

    void print() const {
        for (int i = 0; i < m_count; ++i) {
            int row = i / m_length;
            int col = i % m_length;

            std::cout << get(row, col);

            if (col == m_length - 1)
                std::cout << '\n';
            else
                std::cout << "--";
        }
    }

    matrix transpose() {
        matrix output = matrix<T>(m_length, m_height);

        for (int i = 0; i < m_count; ++i) {
            int row = i / m_length;
            int col = i % m_length;


        }
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

    /* void transposeInPlaceSq() {
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
     }*/

    [[nodiscard]] int getCount() const {
        return m_count;
    }

    [[nodiscard]] int getLength() const {
        return m_length;
    }

    [[nodiscard]] int getHeight() const {
        return m_height;
    }

    /* matrix rotate90() {
         matrix output = transpose();
         output.reverse();
         return output;
     }

     void rotate90InPlaceSq() {
         transposeInPlaceSq();
         reverse();
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
     }*/

    explicit matrix(const int length, const int height) {
        assert(length > 0 && height > 0);

        m_v2d = std::vector<T>(height * length);
        m_count = length * height;
        m_height = height;
        m_length = length;
    }

private:
    [[nodiscard]] int getIndex(const int row, const int col) const {
        return row * m_length + col;
    }

    void ValidateIndex(const int rowIndex, const int colIndex) const {
        assert(rowIndex < m_height);
        assert(colIndex < m_length);
        assert(rowIndex >= 0);
        assert(colIndex >= 0);
    }

    int m_count{};
    int m_height{};
    int m_length{};
    std::vector<T> m_v2d{};
};
