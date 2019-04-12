#pragma once
#include <map>
#include <vector>
#include <iostream>

/*

Class:			Matrix
Description:	class with all required matrix set uo methodsa and data structure 

*/

/// typedef for long type
using ULONG = unsigned long;

class Matrix
{
public:
	Matrix() {};
	~Matrix() {};
	/// Accessor to matrix
	std::vector< std::vector<ULONG>> & getValue() { return m_matrix; };
	/// Add value into matrix
	bool addValue(ULONG row, ULONG col, ULONG val)
	{
		ULONG origSize = m_matrix.size();
		return (m_matrix[row][col] = val);
		return (origSize < m_matrix.size());
	};
	/// Accessor and mutators
	bool setRowCount(ULONG k) { return (m_rowCount = k); };
	const ULONG & getRowCount() { return m_rowCount; };
	bool setColCount(ULONG k) { return(m_colCount = k); };
	const ULONG & getColCount() { return m_colCount; };

	/// set fors and cols
	void askForRowCol() {
		std::cout << "How many rows in matrix_0" << std::endl;
		std::cin >> m_rowCount;
		std::cout << "How many columns in matrix_0" << std::endl;
		std::cin >> m_colCount;
	}

	/// final loop to multiply matricies
	void matrixMulti_2(ULONG & i, ULONG & j, Matrix & matrix_0, Matrix matrix_1) {
		for (ULONG k = 0; k < matrix_0.getColCount(); ++k)
		{
			m_matrix[i][j] += matrix_0.getValue()[i][k] * matrix_1.getValue()[k][j];
		}
	}
	/// second loop of matric multipication
	void matrixMulti_1(ULONG & i, Matrix & matrix_0, Matrix matrix_1) {
		for (ULONG j = 0; j < matrix_1.getColCount(); ++j) {
			matrixMulti_2(i, j, matrix_0, matrix_1);
		}
	}
	/// first loop of a matrix multiplication
	void setMatrixMulti(Matrix & matrix_0, Matrix matrix_1) {
		for (ULONG i = 0; i < matrix_0.getRowCount(); ++i) {
			matrixMulti_1(i, matrix_0, matrix_1);
		}
	}

	/// auto fill i nmatrix with min and max values
	bool autoFillMatrix(ULONG min, ULONG max)
	{
		// clear matrix
		this->clear();
		// loop row counr
		for (size_t i = 0; i < m_rowCount; i++)
		{
			std::vector<ULONG> tempVec;
			// loop col count
			for (size_t k = 0; k < m_colCount; k++)
			{
				// add vector and add randome value into it
				auto count = ULONG(rand() % max + min);
				tempVec.push_back(count);
				// safety check for out or range values
				if (tempVec[k] > max || tempVec[k] < min)
					return false;
			}
			m_matrix.push_back(tempVec);
		}
		return true;
	};
	/// clear matric data list
	void clear() { m_matrix.clear(); }

private:
	std::vector< std::vector<ULONG>> m_matrix;
	ULONG m_rowCount;
	ULONG m_colCount;
};
