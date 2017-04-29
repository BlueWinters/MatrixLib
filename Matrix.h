//
//
#ifndef Matrix_h__
#define Matrix_h__

//#include "Stdafx.h"

namespace MatrixLib
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
		// compare matrix size and value
		static inline bool equal(const _Matrix& _mat1, const _Matrix& _mat2)
		{
			if(_mat1.nRow != _mat2.nRow 
				|| _mat1.nCol != _mat2.nCol)
				return false;

			unsigned int size = _mat1.nRow * _mat1.nCol;
			for(unsigned int n = 0; n < size; n++)
			{
				if(_mat1.data[n] != _mat2.data[n])
					return false;
			}
			return true;
		}

		// compare matrix size
		static inline bool compare(const _Matrix& _mat1, const _Matrix& _mat2)
		{
			return (_mat1.nRow == _mat2.nRow 
				&& _mat1.nCol == _mat2.nCol);
		}

		// compare data address(is the same)
		static inline bool shared(const _Matrix& _mat1, const _Matrix& _mat2)
		{
			if(!_mat1.assert() || !_mat2.assert())
				return false;
			return (_mat1.data == _mat2.data);
		}

		// swap data
		static inline void swap(const _Matrix& _mat1, const _Matrix& _mat2)
		{
			_Number* data = _mat1.data;
			unsigned int nRow = _mat1.nRow();
			unsigned int nCol = _mat1.nCol();

			_mat1.data = _mat2.data;
			_mat1.nRow = _mat2.nRow;
			_mat1.nCol = _mat2.nCol;
			_mat2.data = data;
			_mat2.nRow = nRow;
			_mat2.nCol = nCol;
		}

	public:
		// _mat3 = _mat1 + _mat2
		static inline bool add(const _Matrix& _mat1, const _Matrix& _mat2, const _Matrix& _mat3)
		{
			if(!_Matrix::compareSize(_mat1, _mat2))
				return false;

			unsigned int nRow = _mat1.nRow();
			unsigned int nCol = _mat1.nCol();
			_mat3.alloc(nRow, nCol);
			for(unsigned int n = 0; n < nCol*nRow; n++)
			{
				_mat3.data[n] = _mat1.data[n] + _mat2.data[n];
			}

			return true;
		}

		// _mat2 = _mat1 + _number
		static inline bool add(const _Matrix& _mat1, _Number _number, const _Matrix& _mat2)
		{
			unsigned int nRow = _mat1.nRow();
			unsigned int nCol = _mat1.nCol();
			_mat2.alloc(nRow, nCol);
			for(unsigned int n = 0; n < nCol*nRow; n++)
			{
				_mat2.data[n] = _mat1.data[n] + _number;
			}

			return true;
		}

		// _mat3 = _mat1 - _mat2
		static inline void sub(const _Matrix& _mat1, const _Matrix& _mat2, const _Matrix& _mat3)
		{
			if(!_Matrix::compareSize(_mat1, _mat2))
				return false;

			unsigned int nRow = _mat1.nRow();
			unsigned int nCol = _mat1.nCol();
			_mat3.alloc(nRow, nCol);
			for(unsigned int n = 0; n < nCol*nRow; n++)
			{
				_mat3.data[n] = _mat1.data[n] - _mat2.data[n];
			}

			return true;
		}

		// _mat2 = _mat1 - _number
		static inline bool sub(const _Matrix& _mat1, _Number _number, const _Matrix& _mat2)
		{
			unsigned int nRow = _mat1.nRow();
			unsigned int nCol = _mat1.nCol();
			_mat2.alloc(nRow, nCol);
			for(unsigned int n = 0; n < nCol*nRow; n++)
			{
				_mat2.data[n] = _mat1.data[n] - _number;
			}

			return true;
		}

		// _mat2 = _number - _mat1
		static inline bool sub(_Number _number, const _Matrix& _mat1, const _Matrix& _mat2)
		{
			unsigned int nRow = _mat1.nRow();
			unsigned int nCol = _mat1.nCol();
			_mat2.alloc(nRow, nCol);
			for(unsigned int n = 0; n < nCol*nRow; n++)
			{
				_mat2.data[n] = _number - _mat1.data[n];
			}

			return true;
		}

		// _mat3 = _mat1 * _mat2
		static inline void cross(const _Matrix& _mat1, const _Matrix& _mat2, const _Matrix& _mat3)
		{
			if(_mat1.nCol() != _mat2.nRow())
				return false;

			unsigned int nRow = _mat1.nRow();
			unsigned int nCol = _mat2.nCol();
			unsigned int nInner = _mat2.nRow();
			_mat3.alloc(nRow, nCol);
			for(unsigned int i = 0; i < nRow; i++)
			{
				unsigned int z = 0;
				for(unsigned int j = 0; j < nCol; j++)
				{
					for(unsigned int k = 0; k < nInner; k++)
					{
						// z = _mat1[i][k] + _mat2[k][j] for k = 0:nInner
						z += _mat1.data[nRow*k+i] * _mat2[nInner*j+k];
					}
					_mat3.data[nRow*j+i] = z;
				}
			}

			return true;
		}

		// _mat3 = _mat1 .* _mat2
		static inline void dot(const _Matrix& _mat1, const _Matrix& _mat2, const _Matrix& _mat3)
		{
			if(!_Matrix::compareSize(_mat1, _mat2))
				return false;

			unsigned int nRow = _mat1.nRow();
			unsigned int nCol = _mat1.nCol();
			_mat3.alloc(nRow, nCol);
			for(unsigned int n = 0; n < nCol*nRow; n++)
			{
				_mat3.data[n] = _mat1.data[n] * _mat2.data[n];
			}

			return true;
		}

		// _mat2 = _mat1 .* _number
		static inline bool dot(const _Matrix& _mat1, _Number _number, const _Matrix& _mat2)
		{
			unsigned int nRow = _mat1.nRow();
			unsigned int nCol = _mat1.nCol();
			_mat2.alloc(nRow, nCol);
			for(unsigned int n = 0; n < nCol*nRow; n++)
			{
				_mat2.data[n] = _mat1.data[n] * _number;
			}

			return true;
		}

		// _mat3 = [_mat1 _mat2]
		static inline bool combine1(const _Matrix& _mat1, const _Matrix& _mat2, const _Matrix& _mat3)
		{
			if(_mat1.rows() != _mat2.rows())
				return false;

			_mat3.resize(_mat1.rows(), _mat1.cols() + _mat2.cols());
			for(unsigned int i = 0; i < _mat1.rows(); i++)
			{
				for(unsigned int j = 0; j < _mat1.cols(); j++)
				{
					// _mat3[i][j] = _mat1[i][j]
					_mat3.data[_mat3.rows()*j+i] = _mat1.data[_mat1.rows()*j+i];
				}

				for(unsigned int j = _mat1.cols(); j < _mat2.cols(); j++)
				{
					// _mat3[i][j] = _mat2[i][j]
					_mat3.data[_mat3.rows()*j+i] = _mat2.data[_mat2.rows()*j+i];
				}
			}
		}

		// _mat3 = [_mat1 ; _mat2]
		static inline bool combine2(const _Matrix& _mat1, const _Matrix& _mat2, const _Matrix& _mat3)
		{
			if(_mat1.cols() != _mat2.cols())
				return false;

			_mat3.resize(_mat1.rows() + _mat2.rows(), _mat1.cols());
			for(unsigned int j = 0; j < _mat1.cols(); j++)
			{
				for (unsigned int i = 0; i < _mat1.rows(); i++)
				{
					// _mat3[i][j] = _mat1[i][j]
					_mat3.data[_mat3.rows()*j+i] = _mat1.data[_mat1.rows()*j+i];
				}

				for (unsigned int i = _mat1.rows(); i < _mat2.rows(); i++)
				{
					// _mat3[i][j] = _mat2[i][j]
					_mat3.data[_mat3.rows()*j+i] = _mat2.data[_mat2.rows()*j+i];
				}
			}
		}

	public:
		inline void copy(const _Matrix& _mat)
		{
			if(_mat.assert() == true)
			{
				alloc(_mat.nRow, _mat.nCol);
				memcpy(sizeof(Number)*nRow*nCol, _mat.data, data);
			}
		}

		inline unsigned int rows()
		{
			return nRow;
		}

		inline unsigned int cols()
		{
			return nCol;
		}

		inline bool assert()
		{
			return (nRow != 0 && nCol != 0 && data != NULL);
		}

		inline void resize(unsigned int _row, unsigned int _col)
		{
			return alloc(_row, _col);
		}

		inline bool reshape(unsigned int _row, unsigned int _col)
		{
			if(nRow*nCol != _row*_col)
				return false;

			nRow = _row;
			nCol = _col;
			return true;
		}

	public:
		// get value
		inline Number at(unsigned int _n)
		{
			return data[_n];
		}

		inline Number at(unsigned int _i, unsigned int _j)
		{
			return data[nRow*_j+_i];
		}

		inline Number& atr(unsigned int _n)
		{
			return data[_n];
		}

		inline Number& atr(unsigned int _i, unsigned int _j)
		{
			return data[nRow*_j+_i];
		}

		inline Number* atp(unsigned int _n)
		{
			return &(data[_n]);
		}

		inline Number* atp(unsigned int _i, unsigned int _j)
		{
			return &(data[nRow*_j+_i]);
		}

		// set value
		inline void set(unsigned int _n, Number _number)
		{
			data[_n] = _number;
		}

		inline void set(unsigned int _i, unsigned int _j, Number _number)
		{
			data[nRow*_j+_i] = _number;
		}

		inline void setp(unsigned int _n, Number* _number)
		{
			data[_n] = *_number;
		}

		inline void setp(unsigned int _i, unsigned int _j, Number* _number)
		{
			data[nRow*_j+_i] = *_number;
		}

	public:
		inline bool getRow(unsigned int _rowb, unsigned int _rowe, _Matrix& _mat)
		{
			if(nRow < _rowb || nRow < _rowe
				|| !(_rowb <= _rowe))
				return false;

			unsigned int rows = _rowe - _rowb + 1;
			_mat.alloc(rows, nCol);
			for(unsigned int i = 0; i < rows; i++)
			{
				for(unsigned int j = 0; j < nCol; j++)
				{
					// _mat.data[i][j] = data[_rowb+i][j]
					_mat.data[rows*j+i] = data[nRow*j+(_rowb+i)];
				}
			}

			return true;
		}

		inline bool getRow(unsigned int _row, _Matrix& _mat)
		{
			return getRow(_row, _row, _mat);
		}

		inline bool setRow(unsigned int _rowb, unsigned in _rowe, const _Matrix& _mat)
		{
			if(nRow < _rowb || nRow < _rowe
				|| !(_rowb <= _rowe))
				return false;

			unsigned int rows = _rowe - _rowb + 1;
			if(cols() != _mat.cols() || _mat.rows() != rows)
				return false;

			for(unsigned int i = 0; i < rows; i++)
			{
				for(unsigned int j = 0; j < nCol; j++)
				{
					// data[_rowb+i][j] = _mat.data[i][j];
					data[nRow*j+(_rowb+i)] = _mat.data[_mat.nRow*j+i];
				}
			}

			return true;
		}

		inline bool setRow(unsigned int _rowb, unsigned in _rowe, _Number _number)
		{
			if(nRow < _rowb || nRow < _rowe
				|| !(_rowb <= _rowe))
				return false;

			unsigned int rows = _rowe - _rowb + 1;
			for(unsigned int i = 0; i < rows; i++)
			{
				for(unsigned int j = 0; j < nCol; j++)
				{
					// data[_rowb+i][j] = _number
					data[nRow*j+(_rowb+i)] = _number;
				}
			}

			return true;
		}

		inline bool setRow(unsigned int _row, _Number _number)
		{
			return setRow(_row, _row, _number);
		}

		inline bool getCol(unsigned int _colb, unsigned int _cole, _Matrix& _mat)
		{
			if(nCol < _colb || nCol < _cole
				|| !(_colb <= _cole))
				return false;

			unsigned int cols = _cole - _colb + 1;
			_mat.alloc(nRow, cols);
			for(unsigned int i = 0; i < nRow; i++)
			{
				for(unsigned int j = 0; j < cols; j++)
				{
					// _mat.data[i][j] = data[i][_colb+j]
					_mat.data[nRow*j+i] = data[nRow*j+(_colb+i)];
				}
			}

			return true;
		}

		inline bool getCol(unsigned int _col, _Matrix& _mat)
		{
			return getCol(_col, _col, _mat);
		}

		inline bool setCol(unsigned int _colb, unsigned in _cole, const _Matrix& _mat)
		{
			if(nCol < _colb || nCol < _cole
				|| !(_colb <= _cole))
				return false;

			unsigned int cols = _cole - _colb + 1;
			if(rows() != _mat.rows() || _mat.cols() != cols)
				return false;

			for(unsigned int j = 0; j < cols; j++)
			{
				for(unsigned int i = 0; i < nRow; i++)
				{
					// data[i][_colb+j] = _mat.data[i][j];
					data[nRow*(_colb+j)+i] = _mat.data[_mat.nRow*j+i];
				}
			}

			return true;
		}

		inline bool setCol(unsigned int _colb, unsigned in _cole, _Number _number)
		{
			if(nCol < _colb || nCol < _cole
				|| !(_colb <= _cole))
				return false;

			unsigned int cols = _cole - _colb + 1;
			for(unsigned int j = 0; j < cols; j++)
			{
				for(unsigned int i = 0; i < nRow; i++)
				{
					// data[i][_colb+j] = _number;
					data[nRow*(_colb+j)+i] = _number;
				}
			}

			return true;
		}

		inline bool setCol(unsigned int _col, _Number _number)
		{
			return setCol(_col, _col, _number);
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
			setAll(*_number);
		}

		inline void setZeros()
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
		//	inline _Matrix& operator = (const _Matrix& _matrix) const
		//	{
		//		copy(_matrix);
		//		return (*this);
		//	}

		//public:
		//	friend inline bool operator == (const _Matrix& _matrix1, const _Matrix& _matrix2)
		//	{
		//		
		//	}

		//	friend inline bool operator != (const _Matrix& _matrix1, const _Matrix& _matrix2)
		//	{
		//		if(_matrix1.nRow != _matrix2.nRow 
		//			|| _matrix1.nCol != _matrix2.nCol)
		//			return true;

		//		unsigned int size = _matrix1.nRow * _matrix1.nCol;
		//		for(unsigned int n = 0; n < size; n++)
		//		{
		//			if(_matrix1.data[n] != _matrix2.data[n])
		//				return true;
		//		}
		//		return false;
		//	}

		//public:
		//	friend inline const _Matrix& operator + (const _Matrix& _matrix1, const _Matrix& _matrix2)
		//	{
		//		_Matrix& mat = _Matrix::object();
		//		mat.free();
		//		Matrix::add(_matrix1, _matrix2, mat);
		//		return mat;
		//	}

		//	friend inline const _Matrix& operator - (const _Matrix& _matrix1, const _Matrix& _matrix2)
		//	{
		//		_Matrix& mat = _Matrix::object();
		//		mat.free();
		//		Matrix::sub(_matrix1, _matrix2, mat);
		//		return mat;
		//	}

		//	friend inline const _Matrix& operator * (const _Matrix& _matrix1, const _Matrix& _matrix2)
		//	{
		//		_Matrix& mat = _Matrix::object();
		//		mat.free();
		//		Matrix::multi(_matrix1, _matrix2, mat);
		//		return mat;
		//	}

		//	friend inline const _Matrix& operator / (const _Matrix& _matrix1, const _Matrix& _matrix2)
		//	{
		//		_Matrix& mat = _Matrix::object();
		//		
		//		return mat;
		//	}

		//public:
		//	inline _Matrix& operator += (const _Matrix& _matrix)
		//	{
		//		if(nRow == _matrix.nRow || nCol == _matrix.nCol)
		//		{
		//			for(unsigned int i = 0; i < nRow; i++)
		//			{
		//				for(unsigned int j = 0; j < nCol; j++)
		//				{
		//					data[nRow*i+j] += _matrix.data[nRow*i+j];	
		//				}
		//			}
		//		}
		//		return (*this);
		//	}

		//	inline _Matrix& operator -= (const _Matrix& _matrix)
		//	{
		//		if(nRow == _matrix.nRow || nCol == _matrix.nCol)
		//		{
		//			for(unsigned int i = 0; i < nRow; i++)
		//			{
		//				for(unsigned int j = 0; j < nCol; j++)
		//				{
		//					data[nRow*i+j] -= _matrix.data[nRow*i+j];	
		//				}
		//			}
		//		}
		//		return (*this);
		//	}

		//	inline _Matrix& operator *= (const _Matrix& _matrix)
		//	{
		//		if(nCol == _matrix.nRow)
		//		{
		//			_Matrix tmp(*this);
		//			for(unsigned int i = 0; i < nRow; i++)
		//			{
		//				for(unsigned int j = 0; j < _matrix.nCol; j++)
		//				{
		//					for(unsigned int k = 0; k < nCol; k++)
		//					{
		//						data[nRow*i+j] += tmp.data[tmp.nRow*i+k] * _matrix.data[_matrix.nRow*k+j];
		//					}
		//				}
		//			}
		//		}
		//		return (*this);
		//	}

	public:
		inline void toString()
		{

		}
	};// end for class Matrix
}

#endif
