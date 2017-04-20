//
//
#ifndef Matrix_h__
#define Matrix_h__

#include "Stdafx.h"

namespace Geometric
{
	template<class Number>
	class _GEOMETRIC Matrix
	{
	public:
		// type define Matrix and Number
		typedef typename Matrix<Number> _Matrix;
		typedef typename Number _Number;
		typedef void (*Function)(const Number&);

	public:
		Matrix() :m_i(0), m_j(0), m_data(NULL)
		{
			
		}

		explicit Matrix(const _Matrix& _matrix)
		{
			copy(_matrix);
		}

		virtual ~Matrix()
		{
			free();
		}

	protected:
		// store the matrix length
		unsigned int m_i;
		unsigned int m_j;
		// store the matrix value
		Number* m_data;

	protected:
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

	public:
		inline void alloc(unsigned int _i, unsigned int _j) //throw 
		{
			if(m_i != _i || m_j != _j)
			{
				m_i = _i;
				m_j = _j;
				delete[] m_data;
				m_data = new Number[m_i*m_j];
				set(_Matrix::getDefault());
			}
		}

		inline void free()
		{
			m_i = m_j = 0;
			delete[] m_data;
			m_data = NULL;
		}

		inline void copy(const _Matrix& _matrix)
		{
			alloc(_matrix.m_i, _matrix.m_j);
			for(unsigned int i = 0; i < m_i; i++)
			{
				for(unsigned int j = 0; j < m_j; j++)
				{
					m_data[i*m_i+j] = _matrix.m_data[i*m_i+j];
				}
			}
		}

	public:
		// matrix[0~m_i-1][0~m_j-1]
		inline Number& at(unsigned int _i, unsigned int _j) const
		{
			return m_data[m_i*_i+_j];
		}

		inline Number* atp(unsigned int _i, unsigned int _j) const
		{
			return &(m_data[m_i*_i+_j]);
		}

		inline void set(unsigned int _i, unsigned int _j, const Number& _number)
		{
			m_data[m_i*_i+_j] = _number;
		}

		inline void setp(unsigned int _i, unsigned int _j, const Number* _number)
		{
			m_data[m_i*_i+_j] = *_number;
		}

		inline void set(Number* _number, unsigned int _i, unsigned int _j)
		{
			alloc(_i, _j);
			for(unsigned int i = 0; i < _i; i++)
			{
				for(unsigned int j = 0; j < _j; j++)
				{
					m_data[m_i*i+j] = _number[m_i*i+j];
				}
			}
		}

		inline void set(const Number& _number)
		{
			for(unsigned int i = 0; i < m_i; i++)
			{
				for(unsigned int j = 0; j < m_j; j++)
				{
					m_data[m_i*i+j] = _number;
				}
			}
		}

		inline void zero()
		{
			Number zero(0);
			for(unsigned int i = 0; i < m_i; i++)
			{
				for(unsigned int j = 0; j < m_j; j++)
				{
					m_data[m_i*i+j] = zero;
				}
			}
		}

		inline unsigned int getI() const
		{
			return m_i;
		}

		inline unsigned int getJ() const
		{
			return m_j;
		}

		inline bool isValid() const
		{
			return (m_i != 0 && m_j != 0 && m_data != NULL);
		}

		inline bool hasData() const
		{
			return (m_data != NULL);
		}
		
		inline bool swapRow(unsigned int _row1, unsigned int _row2)
		{
			if(isValid() == true && _row1 < m_i && _row2 < m_i)
			{
				Number tmp;
				for(unsigned int j = 0; j < m_j; j++)
				{
					tmp = m_data[_row1*m_i+j];
					m_data[_row1*m_i+j] = m_data[_row2*m_i+j];
					m_data[_row2*m_i+j] = tmp;
				}
				// finish
				return true;
			}

			return false;
		}

		inline bool swapColumn(unsigned int _column1, unsigned int _column2)
		{
			if(isValid() == true && _column1 < m_j && _column2 < m_j)
			{
				Number tmp;
				for(unsigned int i = 0; i < m_i; i++)
				{
					tmp = m_data[i*m_i+_column1];
					m_data[i*m_i+_column1] = m_data[i*m_i+_column2];
					m_data[i*m_i+_column2] = tmp;
				}
				// finish
				return true;
			}

			return false;
		}

		// elementary transformation: matrix[_row_dst][*]=matrix[dst][*]+matrix[_row_src][*]*_coe
		inline bool transformateRow(unsigned int _row_src, const Number& _coe, unsigned int _row_dst)
		{
			if(isValid() == false || 
				!(_row_src < m_i) || 
				!(_row_dst < m_i))
			{
				return false;
			}

			for(unsigned int j = 0; j < m_j; j++)
			{
				m_data[_row_dst*m_i+j] += m_data[_row_src*m_i+j] * _coe;
			}

			return true;
		}

		// elementary transformation: matrix[*][_row_dst]=matrix[*][dst]+matrix[*][_row_src]*_coe
		inline bool transformateCol(unsigned int _col_src, const Number& _coe, unsigned int _col_dst)
		{
			if(isValid() == false || 
				!(_col_src < m_j) || 
				!(_col_dst < m_j))
			{
				return false;
			}

			for(unsigned int i = 0; i < m_i; i++)
			{
				m_data[i*m_i+_col_dst] += m_data[i*m_i+_col_dst] * _coe;
			}

			return true;
		}

		// resize the matrix
		inline void resize(unsigned int _i, unsigned int _j)
		{
			_Matrix mat(*this);
			unsigned int min_i = (_i < m_i) ? _i : m_i;
			unsigned int min_j = (_j < m_j) ? _j : m_j;

			alloc(_i, _j);
			for(unsigned int i = 0; i < min_i; i++)
			{
				for(unsigned int j = 0; j < min_j; j++)
				{
					m_data[i*m_i+j] = mat.m_data[i*mat.m_i+j];
				}
			}
		}

		inline bool deleteRow(unsigned int _row)
		{
			if(_row < m_i)
			{
				// save a temporary copy
				_Matrix mat(*this);
				
				// resize matrix data buffer
				alloc(m_i-1, m_j);
				// assign value
				for(unsigned int i = 0; i < m_i; i++)
				{
					for(unsigned int j = 0; j < m_j; j++)
					{
						m_data[i*m_i+j] = (i < _row) ? mat.m_data[i*m_i+j] : mat.m_data[(i+1)*m_i+j];
					}
				}
				// finish
				return true;
			}
			// invalid row
			return false;
		}

		inline bool deleteCol(unsigned int _col)
		{
			if(_col < m_i)
			{
				// save a temporary copy
				_Matrix mat(*this);

				// resize matrix data buffer
				alloc(m_i, m_j-1);
				// assign value
				for(unsigned int j = 0; j < m_j; j++)
				{
					for(unsigned int i = 0; i < m_i; i++)
					{
						m_data[i*m_i+j] = (j < _col) ? mat.m_data[i*m_i+j] : mat.m_data[i*m_i+(j+1)];
					}
				}
				// finish
				return true;
			}
			// invalid column
			return false;
		}


	public:
		// _matrix3 = _matrix1 + _matrix2
		static inline bool add(const _Matrix& _matrix1, const _Matrix& _matrix2, _Matrix& _matrix3)
		{
			if(_matrix1.m_i == _matrix2.m_i && _matrix1.m_j == _matrix2.m_j)
			{
				_matrix3.alloc(_matrix1.m_i, _matrix1.m_j);
				unsigned mat_i = _matrix1.m_i;
				unsigned mat_j = _matrix1.m_j;
				for(unsigned int i = 0; i < mat_i; i++)
				{
					for(unsigned int j = 0; j < mat_j; j++)
					{
						_matrix3.m_data[mat_i*i+j] = _matrix1.m_data[mat_i*i+j] + _matrix2.m_data[mat_i*i+j];
					}
				}
				// finish
				return true;
			}

			return false;
		}

		// _matrix3 = _matrix1 - _matrix2
		static inline bool sub(const _Matrix& _matrix1, const _Matrix& _matrix2, _Matrix& _matrix3)
		{
			if(_matrix1.m_i == _matrix2.m_i && _matrix1.m_j == _matrix2.m_j)
			{
				_matrix3.alloc(_matrix1.m_i, _matrix1.m_j);
				unsigned mat_i = _matrix1.m_i;
				unsigned mat_j = _matrix1.m_j;
				for(unsigned int i = 0; i < mat_i; i++)
				{
					for(unsigned int j = 0; j < mat_j; j++)
					{
						_matrix3.m_data[mat_i*i+j] = _matrix1.m_data[mat_i*i+j] - _matrix2.m_data[mat_i*i+j];
					}
				}
				// finish
				return true;
			}

			return false;
		}

		// _matrix3 = _matrix1 * _matrix2
		static inline bool multi(const _Matrix& _matrix1, const _Matrix& _matrix2, _Matrix& _matrix3)
		{
			if(_matrix1.m_j == _matrix2.m_i)
			{
				_matrix3.alloc(_matrix1.m_i, _matrix2.m_j);
				unsigned int mat_i = _matrix1.m_i;
				unsigned int mat_j = _matrix2.m_j;
				unsigned int mat_k = _matrix1.m_j;
				for(unsigned int i = 0; i < mat_i; i++)
				{
					for(unsigned int j = 0; j < mat_j; j++)
					{
						Number tmp;
						for(unsigned int k = 0; k < mat_k; k++)
						{
							tmp += _matrix1.m_data[mat_i*i+k] * _matrix2.m_data[mat_k*k+j];
						}
						_matrix3.m_data[mat_i*i+j] = tmp;
					}
				}
				// finish
				return true;
			}

			return false;
		}

		static inline bool div(const _Matrix& _matrix1, const _Matrix& _matrix2, _Matrix& _matrix3)
		{
			if(_matrix1.isOrderMatrix() == true 
				&& _matrix2.isOrderMatrix() == true
				&& _matrix1.getI() == _matrix2.getI())
			{
				if(_matrix2.inverse(_matrix3) == true)
				{
					_matrix3 *= _matrix1;
					return true;
				}
			}
			// invalid result
			return false;
		}

	public:
		inline _Matrix& operator = (const _Matrix& _matrix)
		{
			alloc(_matrix.m_i, _matrix.m_j);
			for(unsigned int i = 0; i < m_i; i++)
			{
				for(unsigned int j = 0; j < m_j; j++)
				{
					m_data[i*m_i+j] = _matrix.m_data[i*m_i+j];
				}
			}
			return (*this);
		}

	public:
		friend inline bool operator == (const _Matrix& _matrix1, const _Matrix& _matrix2)
		{
			if(_matrix1.m_i != _matrix2.m_i 
				|| _matrix1.m_j != _matrix2.m_j)
				return false;

			unsigned int ni = _matrix1.m_i;
			unsigned int nj = _matrix1.m_j;
			for(unsigned int i = 0; i < ni; i++)
			{
				for(unsigned int j = 0; j < nj; j++)
				{
					if(_matrix1.m_data[ni*i+j] != _matrix2.m_data[ni*i+j])
						return false;
				}
			}
			return true;
		}

		friend inline bool operator != (const _Matrix& _matrix1, const _Matrix& _matrix2)
		{
			if(_matrix1.m_i != _matrix2.m_i 
				|| _matrix1.m_j != _matrix2.m_j)
				return false;
			
			unsigned int ni = _matrix1.m_i;
			unsigned int nj = _matrix1.m_j;
			for(unsigned int i = 0; i < ni; i++)
			{
				for(unsigned int j = 0; j < nj; j++)
				{
					if(_matrix1.m_data[ni*i+j] != _matrix2.m_data[ni*i+j])
						return true;
				}
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
			if(m_i == _matrix.m_i || m_j == _matrix.m_j)
			{
				for(unsigned int i = 0; i < m_i; i++)
				{
					for(unsigned int j = 0; j < m_j; j++)
					{
						m_data[m_i*i+j] += _matrix.m_data[m_i*i+j];	
					}
				}
			}
			return (*this);
		}

		inline _Matrix& operator -= (const _Matrix& _matrix)
		{
			if(m_i == _matrix.m_i || m_j == _matrix.m_j)
			{
				for(unsigned int i = 0; i < m_i; i++)
				{
					for(unsigned int j = 0; j < m_j; j++)
					{
						m_data[m_i*i+j] -= _matrix.m_data[m_i*i+j];	
					}
				}
			}
			return (*this);
		}

		inline _Matrix& operator *= (const _Matrix& _matrix)
		{
			if(m_j == _matrix.m_i)
			{
				_Matrix tmp(*this);
				for(unsigned int i = 0; i < m_i; i++)
				{
					for(unsigned int j = 0; j < _matrix.m_j; j++)
					{
						for(unsigned int k = 0; k < m_j; k++)
						{
							m_data[m_i*i+j] += tmp.m_data[tmp.m_i*i+k] * _matrix.m_data[_matrix.m_i*k+j];
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
			return (isValid() == true && m_i == m_j);
		}

		inline unsigned int getN()
		{
			return m_i;
		}

		inline bool setE()
		{
			if(isOrderMatrix() == true)
			{
				Number zero(0), one(1);
				for(unsigned int i = 0; i < m_i; i++)
				{
					for(unsigned int j = 0; j < m_j; j++)
					{
						m_data[m_i*i+j] = (i == j) ? one : zero;
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

			unsigned int n = m_i;
			Number zero(0);
			for(unsigned int i = 0; i < n; i++)
			{
				for(unsigned int j = 0; j < n; j++)
				{
					// if matrix[i][j]!=0 && i!=j
					if(i != j && m_data[i*n+j] != zero)
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
			for(unsigned int i = 0; i < m_i; i++)
			{
				for(unsigned int j = 0; j < m_j; j++)
				{
					_func(m_data[i*m_i+j]);
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
				_inverse.alloc(_src.m_i, _src.m_j);
				_inverse.setE();
			}

			_Matrix matrix(_src);
			Number zero(0);
			unsigned int n = matrix.m_i;
			for(unsigned int i = 0; i < n; i++)
			{
				// if matrix[i][i]==0, find a matrix[k][i]!=0, k: i+1 to n-1
				// then swap matrix[i][*] and matrix[k][*]
				if(matrix.m_data[i*n+i] == 0)
				{
					unsigned int k = 0;
					for(k = i+1; k < n; k++)
					{
						// find a number: _matrix[k][i]!=0
						if(matrix.m_data[k*n+i] != zero)
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
					factor = matrix.m_data[k*n+i] / matrix.m_data[i*n+i];
					for(unsigned int j = i; j < n; j++)
					{
						matrix.m_data[k*n+j] -= matrix.m_data[i*n+j] * factor;
					}

					for(unsigned int j = 0; j < n; j++)
					{
						_inverse.m_data[k*n+j] -= _inverse.m_data[i*n+j] * factor;
					}
				}
			}

			// matrix diagonalization
			Number factor;
			for(int i = n-1; i < n; i++)//?
			{
				for(int k = i-1; k >= 0; k--)
				{
					factor = matrix.m_data[k*n+i] / matrix.m_data[i*n+i];
					for(int j = i; j >= 0; j--)
					{
						matrix.m_data[k*n+j] -= matrix.m_data[i*n+j] * factor;
					}

					for(int j = n-1; j >=0; j--)
					{
						_inverse.m_data[k*n+j] -= _inverse.m_data[i*n+j] * factor;
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
				unsigned int n = _matrix.m_i;
				_transpose.alloc(n, n);
				for(unsigned int i = 0; i < n; i++)
				{
					for(unsigned int j = 0; j < n; j++)
					{
						_transpose.m_data[i*n+j] = _matrix.m_data[j*n+i];
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
					unsigned int n = _matrix.m_i;
					for(unsigned int i = 0; i < n; i++)
					{
						_value *= _matrix.m_data[i*n+i];
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
				unsigned int n = _matrix.m_i;
				for(unsigned int i = 0; i < n; i++)
				{
					for(unsigned int j = 0; j < n; j++)
					{
						if(i != j && _matrix.m_data[i*n+j] != _matrix.m_data[j*n+i])
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
