#include "Matrices.h"
#include <iomanip>
namespace Matrices
{

	Matrix::Matrix(int _rows, int _cols)
	{
		a.resize(_rows); //resize vector 1
		for (int i = 0; i < _rows; i++) //resize vector2 within vector1 & initialize each cell to 0
		{
			a[i].resize(_cols, 0);
		}
		//assign member variables to respective values
		rows = _rows;
		cols = _cols;
	}


	///usage:  c = a + b;
	Matrix operator+(const Matrix& a, const Matrix& b)
	{
		if (!(a.getCols() == b.getCols() && a.getRows() == b.getRows())) //if rows and columns are NOT equal
		{
			throw runtime_error("Error: dimensions must agree");
		}
		else //rows and cols ARE equal
		{
			Matrix c(a.getRows(), a.getCols()); //construct new matrix with same dimensions
			for (int i = 0; i < a.getRows(); i++)
			{
				for (int j = 0; j < a.getCols(); j++)
				{
					c(i, j) = a(i, j) + b(i, j); //c cell equals sum of a + b cells
				}
			}
			return c;
		}
	}

	///Matrix multiply
	///usage:  c = a * b;
	Matrix operator*(const Matrix& a, const Matrix& b)
	{
		if (!(a.getCols() == b.getRows())) //if num of cols in a does NOT equal num of rows in b
		{
			throw runtime_error("Error: dimensions must agree");
		}
		else //num cols in a == num rows in b
		{
			Matrix c(a.getRows(), b.getCols()); //matrix c dimensions == a's rows * b's cols
			double sum;
			for (int k = 0; k < b.getCols(); k++)
			{
				for (int i = 0; i < a.getRows(); i++)
				{
					sum = 0;
					for (int j = 0; j < a.getCols(); j++)
					{
						sum += a(i, j) * b(j, k);
					}
					c(i, k) = sum;
				}

			}
			return c;
		}
	}

	///Matrix comparison.
	///usage:  a == b
	bool operator==(const Matrix& a, const Matrix& b)
	{
		if (!(a.getCols() == b.getCols() && a.getRows() == b.getRows()))
		{
			return false;
		}
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				if (!(abs(a(i, j) - b(i, j) < 0.001))) //if cell a is NOT approx equal to cell b
				{
					return false;
				}
			}
		}
		return true; //size and values are equal
	}

	///Matrix comparison.
	///usage:  a != b
	bool operator!=(const Matrix& a, const Matrix& b) //this is literally the exact opposite output of the == function
	{
		if (!(a.getCols() == b.getCols() && a.getRows() == b.getRows()))
		{
			return true;
		}
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				if (!(abs(a(i, j) - b(i, j) < 0.001)))
				{
					return true;
				}
			}
		}
		return false;
	}

	///Output matrix
	///Separate columns by ' ' and rows by '\n'
	ostream& operator<<(ostream& os, const Matrix& a)
	{
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				os << setw(10) << a(i, j) << ' ';
			}
			os << endl;
		}
		return os;
	}


	//declarations for the rotation/translation/scaling matrixes

	RotationMatrix::RotationMatrix(double theta)
		: Matrix(2, 2)
	{
		(*this)(0, 0) = cos(theta);
		(*this)(0, 1) = -sin(theta);
		(*this)(1, 0) = sin(theta);
		(*this)(1, 1) = cos(theta);
	}


	ScalingMatrix::ScalingMatrix(double scale)
		: Matrix(2, 2)
	{
		(*this)(0, 0) = scale;
		(*this)(0, 1) = 0;
		(*this)(1, 0) = 0;
		(*this)(1, 1) = scale;
	}


	TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols)
		: Matrix(2, nCols)
	{
		for (int j = 0; j < nCols; j++)
		{
			(*this)(0, j) = xShift;
			(*this)(1, j) = yShift;
		}
	}

}

