//
//
#ifndef Matrix_h__
#define Matrix_h__

#include "Stdafx.h"
#include <vector>

namespace Matrix
{
	template<class Number>
	class Matrix
	{
	public:
		// type define Matrix and Number
		typedef typename Matrix<Number> _Matrix;
		typedef typename Number _Number;
		typedef void (*Function)(const Number&);

	public:
		Matrix() :nRow(0), nCol(0), data(NULL)
		{
			
		}

		explicit Matrix(const _Matrix& _matrix)
		{
			copy(_matrix);
		}

		Matrix(unsigned int _row, unsigned int _col)
		{
			alloc(_row, _col);
		}

		virtual ~Matrix()
		{
			free();
		}

	protected:
		// store the matrix length
		unsigned int nRow;
		unsigned int nCol;
		// store the matrix value
		// data[0~nRow-1][0~nCol-1]
		Number* data;

	protected:
		// compare matrix size
		static inline bool compareSize(const _Matrix& _matrix1, const _Matrix& _matrix2)
		{
			return (_matrix1.nRow == _matrix2.nRow 
				&& _matrix1.nCol == _matrix2.nCol);
		}

		// compare matrix value
		static inline bool compareValue(const _Matrix& _matrix1, const _Matrix& _matrix2)
		{
			if(_matrix1.nRow != _matrix2.nRow 
				|| _matrix1.nCol != _matrix2.nCol)
				return false;

			unsigned int size = _matrix1.nRow * _matrix1.nCol;
			for(unsigned int n = 0; n < size; n++)
			{
				if(_matrix1.data[n] != _matrix2.data[n])
					return false;
			}
			return true;
		}

		// static object for global use
		static inline _Matrix& object()
		{
			static _Matrix matrix;
			return matrix;
		}

		static inline const Number& getDefault()
		{
			static Number number(0);
			return number;
		}

		static inline void setDefault(const Number& _number)
		{
			Number& number = const_cast<Number&>(getDefault());
			number = _number;
		}

	protected:
		inline void alloc(unsigned int _row, unsigned int _col) //throw 
		{
			if(nRow != _row || nCol != _col)
			{
				nRow = _row;
				nCol = _col;
				delete[] data;
				data = new Number[nRow*nCol];
			}
		}

		inline void free()
		{
			nRow = nCol = 0;
			delete[] data;
			data = NULL;
		}

	public:
		inline void copy(const _Matrix& _mat)
		{
			if(_mat.isValid() == true)
			{
				alloc(_mat.nRow, _mat.nCol);
				memcpy(sizeof(Number)*nRow*nCol, _mat.data, data);
			}
		}

		inline unsigned int getRow()
		{
			return nRow;
		}

		inline unsigned int getCol()
		{
			return nCol;
		}

		inline bool isValid()
		{
			return (nRow != 0 && nCol != 0 && data != NULL);
		}

	public:
		// get value
		inline Number at(unsigned int _n)
		{
			return data[_n];
		}

		inline Number at(unsigned int _i, unsigned int _j)
		{
			return data[nRow*_i+_j];
		}

		inline Number& atr(unsigned int _n)
		{
			return data[_n];
		}

		inline Number& atr(unsigned int _i, unsigned int _j)
		{
			return data[nRow*_i+_j];
		}

		inline Number* atp(unsigned int _n)
		{
			return &(data[_n]);
		}

		inline Number* atp(unsigned int _i, unsigned int _j)
		{
			return &(data[nRow*_i+_j]);
		}

		// set value
		inline void set(unsigned int _n, Number _number)
		{
			data[_n] = _number;
		}

		inline void set(unsigned int _i, unsigned int _j, Number _number)
		{
			data[nRow*_i+_j] = _number;
		}

		inline void setp(unsigned int _n, Number* _number)
		{
			data[_n] = *_number;
		}

		inline void setp(unsigned int _i, unsigned int _j, Number* _number)
		{
			data[nRow*_i+_j] = *_number;
		}

	public:
		inline bool compareSize(const _Matrix& _mat)
		{
			_Matrix::compareSize(*this, _mat)
		}

		inline bool compareValue(const _Matrix& _mat)
		{
			_Matrix::compareValue(*this, _mat)
		}

	public:
		inline void setAll(Number _number)
		{
			for(unsigned int n = 0; n < nCol*nRow; n++)
			{
				data[n] = _number;
			}
		}

		inline void setAll(Number* _number)
		{
			for(unsigned int n = 0; n < nCol*nRow; n++)
			{
				data[n] = *_number;
			}
		}

		inline void setZero()
		{
			setAll(0);
		}



		
	//public:
	//	inline bool swapRow(unsigned int _row1, unsigned int _row2)
	//	{
	//		if(isValid() == true && _row1 < nRow && _row2 < nRow)
	//		{
	//			Number tmp;
	//			for(unsigned int j = 0; j < nCol; j++)
	//			{
	//				tmp = data[_row1*nRow+j];
	//				data[_row1*nRow+j] = data[_row2*nRow+j];
	//				data[_row2*nRow+j] = tmp;
	//			}
	//			// finish
	//			return true;
	//		}

	//		return false;
	//	}

	//	inline bool swapColumn(unsigned int _column1, unsigned int _column2)
	//	{
	//		if(isValid() == true && _column1 < nCol && _column2 < nCol)
	//		{
	//			Number tmp;
	//			for(unsigned int i = 0; i < nRow; i++)
	//			{
	//				tmp = data[i*nRow+_column1];
	//				data[i*nRow+_column1] = data[i*nRow+_column2];
	//				data[i*nRow+_column2] = tmp;
	//			}
	//			// finish
	//			return true;
	//		}

	//		return false;
	//	}

	//	inline bool getRow(unsigned int _row, _Matrix& _mat)
	//	{
	//		_mat.alloc(1, nRow);
	//	}

	//	inline bool getCol(unsigned int _col, _Matrix& _mat)
	//	{

	//	}

	//	// elementary transformation: matrix[_row_dst][*]=matrix[dst][*]+matrix[_row_src][*]*_coe
	//	inline bool transformateRow(unsigned int _row_src, const Number& _coe, unsigned int _row_dst)
	//	{
	//		if(isValid() == false || 
	//			!(_row_src < nRow) || 
	//			!(_row_dst < nRow))
	//		{
	//			return false;
	//		}

	//		for(unsigned int j = 0; j < nCol; j++)
	//		{
	//			data[_row_dst*nRow+j] += data[_row_src*nRow+j] * _coe;
	//		}

	//		return true;
	//	}

	//	// elementary transformation: matrix[*][_row_dst]=matrix[*][dst]+matrix[*][_row_src]*_coe
	//	inline bool transformateCol(unsigned int _col_src, const Number& _coe, unsigned int _col_dst)
	//	{
	//		if(isValid() == false || 
	//			!(_col_src < nCol) || 
	//			!(_col_dst < nCol))
	//		{
	//			return false;
	//		}

	//		for(unsigned int i = 0; i < nRow; i++)
	//		{
	//			data[i*nRow+_col_dst] += data[i*nRow+_col_dst] * _coe;
	//		}

	//		return true;
	//	}

	//	// resize the matrix
	//	inline void resize(unsigned int _i, unsigned int _j)
	//	{
	//		_Matrix mat(*this);
	//		unsigned int min_i = (_i < nRow) ? _i : nRow;
	//		unsigned int min_j = (_j < nCol) ? _j : nCol;

	//		alloc(_i, _j);
	//		for(unsigned int i = 0; i < min_i; i++)
	//		{
	//			for(unsigned int j = 0; j < min_j; j++)
	//			{
	//				data[i*nRow+j] = mat.data[i*mat.nRow+j];
	//			}
	//		}
	//	}

	//	inline bool deleteRow(unsigned int _row)
	//	{
	//		if(_row < nRow)
	//		{
	//			// save a temporary copy
	//			_Matrix mat(*this);
	//			
	//			// resize matrix data buffer
	//			alloc(nRow-1, nCol);
	//			// assign value
	//			for(unsigned int i = 0; i < nRow; i++)
	//			{
	//				for(unsigned int j = 0; j < nCol; j++)
	//				{
	//					data[i*nRow+j] = (i < _row) ? mat.data[i*nRow+j] : mat.data[(i+1)*nRow+j];
	//				}
	//			}
	//			// finish
	//			return true;
	//		}
	//		// invalid row
	//		return false;
	//	}

	//	inline bool deleteCol(unsigned int _col)
	//	{
	//		if(_col < nRow)
	//		{
	//			// save a temporary copy
	//			_Matrix mat(*this);

	//			// resize matrix data buffer
	//			alloc(nRow, nCol-1);
	//			// assign value
	//			for(unsigned int j = 0; j < nCol; j++)
	//			{
	//				for(unsigned int i = 0; i < nRow; i++)
	//				{
	//					data[i*nRow+j] = (j < _col) ? mat.data[i*nRow+j] : mat.data[i*nRow+(j+1)];
	//				}
	//			}
	//			// finish
	//			return true;
	//		}
	//		// invalid column
	//		return false;
	//	}


	//public:
	//	// _matrix3 = _matrix1 + _matrix2
	//	static inline bool add(const _Matrix& _matrix1, const _Matrix& _matrix2, _Matrix& _matrix3)
	//	{
	//		if(_matrix1.nRow == _matrix2.nRow && _matrix1.nCol == _matrix2.nCol)
	//		{
	//			_matrix3.alloc(_matrix1.nRow, _matrix1.nCol);
	//			unsigned mat_i = _matrix1.nRow;
	//			unsigned mat_j = _matrix1.nCol;
	//			for(unsigned int i = 0; i < mat_i; i++)
	//			{
	//				for(unsigned int j = 0; j < mat_j; j++)
	//				{
	//					_matrix3.data[mat_i*i+j] = _matrix1.data[mat_i*i+j] + _matrix2.data[mat_i*i+j];
	//				}
	//			}
	//			// finish
	//			return true;
	//		}

	//		return false;
	//	}

	//	// _matrix3 = _matrix1 - _matrix2
	//	static inline bool sub(const _Matrix& _matrix1, const _Matrix& _matrix2, _Matrix& _matrix3)
	//	{
	//		if(_matrix1.nRow == _matrix2.nRow && _matrix1.nCol == _matrix2.nCol)
	//		{
	//			_matrix3.alloc(_matrix1.nRow, _matrix1.nCol);
	//			unsigned mat_i = _matrix1.nRow;
	//			unsigned mat_j = _matrix1.nCol;
	//			for(unsigned int i = 0; i < mat_i; i++)
	//			{
	//				for(unsigned int j = 0; j < mat_j; j++)
	//				{
	//					_matrix3.data[mat_i*i+j] = _matrix1.data[mat_i*i+j] - _matrix2.data[mat_i*i+j];
	//				}
	//			}
	//			// finish
	//			return true;
	//		}

	//		return false;
	//	}

	//	// _matrix3 = _matrix1 * _matrix2
	//	static inline bool multi(const _Matrix& _matrix1, const _Matrix& _matrix2, _Matrix& _matrix3)
	//	{
	//		if(_matrix1.nCol == _matrix2.nRow)
	//		{
	//			_matrix3.alloc(_matrix1.nRow, _matrix2.nCol);
	//			unsigned int mat_i = _matrix1.nRow;
	//			unsigned int mat_j = _matrix2.nCol;
	//			unsigned int mat_k = _matrix1.nCol;
	//			for(unsigned int i = 0; i < mat_i; i++)
	//			{
	//				for(unsigned int j = 0; j < mat_j; j++)
	//				{
	//					Number tmp;
	//					for(unsigned int k = 0; k < mat_k; k++)
	//					{
	//						tmp += _matrix1.data[mat_i*i+k] * _matrix2.data[mat_k*k+j];
	//					}
	//					_matrix3.data[mat_i*i+j] = tmp;
	//				}
	//			}
	//			// finish
	//			return true;
	//		}

	//		return false;
	//	}

	//	static inline bool div(const _Matrix& _matrix1, const _Matrix& _matrix2, _Matrix& _matrix3)
	//	{
	//		if(_matrix1.isOrderMatrix() == true 
	//			&& _matrix2.isOrderMatrix() == true
	//			&& _matrix1.nRow() == _matrix2.nRow())
	//		{
	//			if(_matrix2.inverse(_matrix3) == true)
	//			{
	//				_matrix3 *= _matrix1;
	//				return true;
	//			}
	//		}
	//		// invalid result
	//		return false;
	//	}

	public:
		inline _Matrix& operator = (const _Matrix& _matrix)
		{
			copy(_matrix);
			return (*this);
		}

	public:
		friend inline bool operator == (const _Matrix& _matrix1, const _Matrix& _matrix2)
		{
			
		}

		friend inline bool operator != (const _Matrix& _matrix1, const _Matrix& _matrix2)
		{
			if(_matrix1.nRow != _matrix2.nRow 
				|| _matrix1.nCol != _matrix2.nCol)
				return true;

			unsigned int size = _matrix1.nRow * _matrix1.nCol;
			for(unsigned int n = 0; n < size; n++)
			{
				if(_matrix1.data[n] != _matrix2.data[n])
					return true;
			}
			return false;
		}

	public:
		friend inline const _Matrix& operator + (const _Matrix& _matrix1, const _Matrix& _matrix2)
		{
			_Matrix& mat = _Matrix::object();
			mat.free();
			Matrix::add(_matrix1, _matrix2, mat);
			return mat;
		}

		friend inline const _Matrix& operator - (const _Matrix& _matrix1, const _Matrix& _matrix2)
		{
			_Matrix& mat = _Matrix::object();
			mat.free();
			Matrix::sub(_matrix1, _matrix2, mat);
			return mat;
		}

		friend inline const _Matrix& operator * (const _Matrix& _matrix1, const _Matrix& _matrix2)
		{
			_Matrix& mat = _Matrix::object();
			mat.free();
			Matrix::multi(_matrix1, _matrix2, mat);
			return mat;
		}

		friend inline const _Matrix& operator / (const _Matrix& _matrix1, const _Matrix& _matrix2)
		{
			_Matrix& mat = _Matrix::object();
			
			return mat;
		}

	public:
		inline _Matrix& operator += (const _Matrix& _matrix)
		{
			if(nRow == _matrix.nRow || nCol == _matrix.nCol)
			{
				for(unsigned int i = 0; i < nRow; i++)
				{
					for(unsigned int j = 0; j < nCol; j++)
					{
						data[nRow*i+j] += _matrix.data[nRow*i+j];	
					}
				}
			}
			return (*this);
		}

		inline _Matrix& operator -= (const _Matrix& _matrix)
		{
			if(nRow == _matrix.nRow || nCol == _matrix.nCol)
			{
				for(unsigned int i = 0; i < nRow; i++)
				{
					for(unsigned int j = 0; j < nCol; j++)
					{
						data[nRow*i+j] -= _matrix.data[nRow*i+j];	
					}
				}
			}
			return (*this);
		}

		inline _Matrix& operator *= (const _Matrix& _matrix)
		{
			if(nCol == _matrix.nRow)
			{
				_Matrix tmp(*this);
				for(unsigned int i = 0; i < nRow; i++)
				{
					for(unsigned int j = 0; j < _matrix.nCol; j++)
					{
						for(unsigned int k = 0; k < nCol; k++)
						{
							data[nRow*i+j] += tmp.data[tmp.nRow*i+k] * _matrix.data[_matrix.nRow*k+j];
						}
					}
				}
			}
			return (*this);
		}

		//inline _Matrix& operator /= (const _Matrix& _matrix)
		//{
		//	return (*this);
		//}

		inline _Matrix& operator + ()
		{
			return (*this);
		}

		inline _Matrix& operator - ()
		{
			return (*this);
		}


		/* operation for N-order matrix */
	public:
		inline bool isOrderMatrix() const
		{
			return (isValid() == true && nRow == nCol);
		}

		inline unsigned int getN()
		{
			return nRow;
		}

		inline bool setE()
		{
			if(isOrderMatrix() == true)
			{
				Number zero(0), one(1);
				for(unsigned int i = 0; i < nRow; i++)
				{
					for(unsigned int j = 0; j < nCol; j++)
					{
						data[nRow*i+j] = (i == j) ? one : zero;
					}
				}
				// finish
				return true;
			}

			return false;
		}

		// if diagonal matrix
		inline bool isDiagonal() const
		{
			if(isOrderMatrix() == false)
			{
				return false;
			}

			unsigned int n = nRow;
			Number zero(0);
			for(unsigned int i = 0; i < n; i++)
			{
				for(unsigned int j = 0; j < n; j++)
				{
					// if matrix[i][j]!=0 && i!=j
					if(i != j && data[i*n+j] != zero)
					{
						return false;
					}
				}
			}

			// finish
			return true;
		}

		// traversal all data number element through function
		inline void traversal(Function _func)
		{
			for(unsigned int i = 0; i < nRow; i++)
			{
				for(unsigned int j = 0; j < nCol; j++)
				{
					_func(data[i*nRow+j]);
				}
			}
		}

	public:
		// get inverse matrix
		static inline bool inverse(const _Matrix& _src, _Matrix& _inverse)
		{
			if(_src.isOrderMatrix() == false)
			{
				return false;
			}
			else
			{
				_inverse.alloc(_src.nRow, _src.nCol);
				_inverse.setE();
			}

			_Matrix matrix(_src);
			Number zero(0);
			unsigned int n = matrix.nRow;
			for(unsigned int i = 0; i < n; i++)
			{
				// if matrix[i][i]==0, find a matrix[k][i]!=0, k: i+1 to n-1
				// then swap matrix[i][*] and matrix[k][*]
				if(matrix.data[i*n+i] == 0)
				{
					unsigned int k = 0;
					for(k = i+1; k < n; k++)
					{
						// find a number: _matrix[k][i]!=0
						if(matrix.data[k*n+i] != zero)
						{
							matrix.swapRow(i, k);
							_inverse.swapRow(i, k);
							break;
						}
					}

					// if i==n-1 and matrix[n-1][n-1]==0, return false
					// if i<n-1 and k==n, return false
					if((i < n - 1 && k == n) || (i == n - 1))
					{
						// do not find any number
						_inverse.free();
						return false;
					}
				}
				else
				{
					// do nothing
				}

				// if matrix[i][i]!=0, do the elementary row transformation of matrix
				Number factor;
				for(unsigned int k = i+1; k < n; k++)
				{
					factor = matrix.data[k*n+i] / matrix.data[i*n+i];
					for(unsigned int j = i; j < n; j++)
					{
						matrix.data[k*n+j] -= matrix.data[i*n+j] * factor;
					}

					for(unsigned int j = 0; j < n; j++)
					{
						_inverse.data[k*n+j] -= _inverse.data[i*n+j] * factor;
					}
				}
			}

			// matrix diagonalization
			Number factor;
			for(int i = n-1; i < n; i++)//?
			{
				for(int k = i-1; k >= 0; k--)
				{
					factor = matrix.data[k*n+i] / matrix.data[i*n+i];
					for(int j = i; j >= 0; j--)
					{
						matrix.data[k*n+j] -= matrix.data[i*n+j] * factor;
					}

					for(int j = n-1; j >=0; j--)
					{
						_inverse.data[k*n+j] -= _inverse.data[i*n+j] * factor;
					}
				}
			}

			// finish
			return true;
		}

		// get transposed matrix
		static inline bool transpose(const _Matrix& _matrix, _Matrix& _transpose)
		{
			if(_matrix.isOrderMatrix() == true)
			{
				unsigned int n = _matrix.nRow;
				_transpose.alloc(n, n);
				for(unsigned int i = 0; i < n; i++)
				{
					for(unsigned int j = 0; j < n; j++)
					{
						_transpose.data[i*n+j] = _matrix.data[j*n+i];
					}
				}
				// finish
				return true;
			}

			// is not N-Order matrix
			return false;
		}

		// get the value of the determinant(matrix)
		static inline bool determinant(const _Matrix& _matrix, Number& _value)
		{
			if(_matrix.isOrderMatrix() == true)
			{
				_Matrix tmp;
				bool flag = inverse(_matrix, tmp);
				if(flag == true && tmp.isDiagonal() == true)
				{
					// not zero
					unsigned int n = _matrix.nRow;
					for(unsigned int i = 0; i < n; i++)
					{
						_value *= _matrix.data[i*n+i];
					}
				}
				else
				{
					// zero
					_value = Number(0);
				}
				// finish
				return true;
			}

			// is not N-Order matrix
			return false;
		}

		// if it is symmetrical
		static inline bool isSymmetrical(const _Matrix& _matrix)
		{
			if(_matrix.isOrderMatrix() == true)
			{
				unsigned int n = _matrix.nRow;
				for(unsigned int i = 0; i < n; i++)
				{
					for(unsigned int j = 0; j < n; j++)
					{
						if(i != j && _matrix.data[i*n+j] != _matrix.data[j*n+i])
						{
							return false;
						}
					}
				}
				// finish check
				return true;
			}

			// is not N-Order matrix
			return false;
		}
	};
}

#endif
