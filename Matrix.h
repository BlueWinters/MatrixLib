//
//
#ifndef Matrix_h__
#define Matrix_h__

#include <cmath>
#include "MatrixB.h"


namespace MatrixLib
{
	template<class Number>
	class Matrix : public MatrixB<Number>
	{
	public:
		// type define Matrix and Number
		typedef typename Matrix<Number> _Matrix;
		typedef typename Number _Number;
		typedef void (*Function)(const Number&);

	public:
		Matrix() :MatrixB()
		{

		}

		explicit Matrix(const _Matrix& _matrix)
			:MatrixB(_matrix)
		{
			
		}

		Matrix(unsigned int _row, unsigned int _col)
			:MatrixB(_row, _col)
		{
			alloc(_row, _col);
		}

		virtual ~Matrix()
		{
			
		}

	public:
		// compare matrix size
		static inline bool compareSize(const _Matrix& _mat1, const _Matrix& _mat2)
		{
			return (_mat1.rows() == _mat2.rows() 
				&& _mat1.cols() == _mat2.cols());
		}

		// compare matrix size and value
		static inline bool isEqual(const _Matrix& _mat1, const _Matrix& _mat2)
		{
			if(_mat1.rows() != _mat2.rows() 
				|| _mat1.cols() != _mat2.cols())
				return false;

			unsigned int size = _mat1.rows() * _mat1.cols();
			for(unsigned int n = 0; n < size; n++)
			{
				if(_mat1.at(n) != _mat2.at(n))
					return false;
			}
			return true;
		}

		// compare data address(is the same)
		static inline bool isShared(const _Matrix& _mat1, const _Matrix& _mat2)
		{
			if(!_mat1.assert() || !_mat2.assert())
				return false;
			return (_mat1.data == _mat2.data);
		}

		// swap data
		static inline void swapMatrix(const _Matrix& _mat1, const _Matrix& _mat2)
		{
			_Number* data = _mat1.data;
			unsigned int nrow = _mat1.rows();
			unsigned int ncol = _mat1.cols();

			_mat1.data = _mat2.data;
			_mat1.nRow = _mat2.rows();
			_mat1.nCol = _mat2.cols();
			_mat2.data = data;
			_mat2.nRow = nrow;
			_mat2.nCol = ncol;
		}

	public:
		// _mat3 = _mat1 + _mat2
		static inline bool toAdd(_Matrix& _mat1, _Matrix& _mat2, _Matrix& _mat3)
		{
			if(!_Matrix::compare(_mat1, _mat2))
				return false;

			unsigned int nrow = _mat1.rows();
			unsigned int ncol = _mat1.cols();
			_mat3.alloc(nrow, ncol);
			for(unsigned int n = 0; n < ncol*nrow; n++)
			{
				_mat3.atr(n) = _mat1.at(n) + _mat2.at(n);
			}

			return true;
		}

		// _mat2 = _mat1 + _number
		static inline bool toAdd(_Matrix& _mat1, _Number _number, _Matrix& _mat2)
		{
			unsigned int nrow = _mat1.rows();
			unsigned int ncol = _mat1.cols();
			_mat2.alloc(nrow, ncol);
			for(unsigned int n = 0; n < ncol*nrow; n++)
			{
				_mat2.atr(n) = _mat1.at(n) + _number;
			}

			return true;
		}

		// _mat3 = _mat1 - _mat2
		static inline void toSub(_Matrix& _mat1, _Matrix& _mat2, _Matrix& _mat3)
		{
			if(!_Matrix::compare(_mat1, _mat2))
				return false;

			unsigned int nrow = _mat1.rows();
			unsigned int ncol = _mat1.cols();
			_mat3.alloc(nrow, ncol);
			for(unsigned int n = 0; n < ncol*nrow; n++)
			{
				_mat3.atr(n) = _mat1.at(n) - _mat2.at(n);
			}

			return true;
		}

		// _mat2 = _mat1 - _number
		static inline bool toSub(_Matrix& _mat1, _Number _number, _Matrix& _mat2)
		{
			unsigned int nrow = _mat1.rows();
			unsigned int ncol = _mat1.cols();
			_mat2.alloc(nrow, ncol);
			for(unsigned int n = 0; n < ncol*nrow; n++)
			{
				_mat2.atr(n) = _mat1.at(n) - _number;
			}

			return true;
		}

		// _mat2 = _number - _mat1
		static inline bool toSub(_Number _number, _Matrix& _mat1, _Matrix& _mat2)
		{
			unsigned int nrow = _mat1.rows();
			unsigned int ncol = _mat1.cols();
			_mat2.alloc(nrow, ncol);
			for(unsigned int n = 0; n < ncol*nrow; n++)
			{
				_mat2.atr(n) = _number - _mat1.atr(n);
			}

			return true;
		}

		// _mat3 = _mat1 * _mat2
		static inline void toCross(_Matrix& _mat1, _Matrix& _mat2, _Matrix& _mat3)
		{
			if(_mat1.cols() != _mat2.rows())
				return false;

			unsigned int nrow = _mat1.rows();
			unsigned int ncol = _mat2.cols();
			unsigned int inner = _mat2.rows();
			_mat3.alloc(nrow, ncol);
			for(unsigned int i = 0; i < nrow; i++)
			{
				unsigned int z = 0;
				for(unsigned int j = 0; j < ncol; j++)
				{
					for(unsigned int k = 0; k < inner; k++)
					{
						// z = _mat1[i][k] + _mat2[k][j] for k = 0:nInner
						z += _mat1.at(i,k) * _mat2.at(k,j);
					}
					// _mat[i][j] = z
					_mat3.at(i,j) = z;
				}
			}

			return true;
		}

		// _mat3 = _mat1 .* _mat2
		static inline void toDot(_Matrix& _mat1, _Matrix& _mat2, _Matrix& _mat3)
		{
			if(!_Matrix::compare(_mat1, _mat2))
				return false;

			unsigned int nrow = _mat1.rows();
			unsigned int ncol = _mat1.cols();
			_mat3.alloc(nrow, ncol);
			for(unsigned int n = 0; n < ncol*nrow; n++)
			{
				_mat3.atr(n) = _mat1.at(n) * _mat2.at(n);
			}

			return true;
		}

		// _mat2 = _mat1 .* _number
		static inline bool toDot(_Matrix& _mat1, _Number _number, _Matrix& _mat2)
		{
			unsigned int nrow = _mat1.rows();
			unsigned int ncol = _mat1.cols();
			_mat2.alloc(nrow, ncol);
			for(unsigned int n = 0; n < ncol*nrow; n++)
			{
				_mat2.atr(n) = _mat1.at(n) * _number;
			}

			return true;
		}

		// _mat2 = _mat1 .^ _number
		static inline bool toPower(_Matrix& _mat1, _Number _number, _Matrix& _mat2)
		{
			unsigned int nrow = _mat1.rows();
			unsigned int ncol = _mat1.cols();
			_mat2.alloc(nrow, ncol);
			for(unsigned int n = 0; n < ncol*nrow; n++)
			{
				_mat2.atr(n) = pow(_mat1.at(n), _number);
			}

			return true;
		}

		// _mat3 = [_mat1 _mat2]
		static inline bool combineRow(_Matrix& _mat1, _Matrix& _mat2, _Matrix& _mat3)
		{
			if(_mat1.rows() != _mat2.rows())
				return false;

			_mat3.resize(_mat1.rows(), _mat1.cols() + _mat2.cols());
			for(unsigned int i = 0; i < _mat1.rows(); i++)
			{
				for(unsigned int j = 0; j < _mat1.cols(); j++)
				{
					// _mat3[i][j] = _mat1[i][j]
					_mat3.atr(i,j) = _mat1.at(i,j);
				}

				unsigned int colb = _mat1.cols();
				for(unsigned int j = 0; j < _mat2.cols(); j++)
				{
					// _mat3[i][colb+j] = _mat2[i][j]
					_mat3.atr(i,colb+j) = _mat2.at(i,j);
				}
			}
		}

		// _mat3 = [_mat1 ; _mat2]
		static inline bool combineCol(_Matrix& _mat1, _Matrix& _mat2, _Matrix& _mat3)
		{
			if(_mat1.cols() != _mat2.cols())
				return false;

			_mat3.resize(_mat1.rows() + _mat2.rows(), _mat1.cols());
			for(unsigned int j = 0; j < _mat1.cols(); j++)
			{
				for (unsigned int i = 0; i < _mat1.rows(); i++)
				{
					// _mat3[i][j] = _mat1[i][j]
					_mat3.atr(i,j) = _mat1.at(i,j);
				}

				unsigned int rowb = _mat2.rows();
				for (unsigned int i = 0; i < _mat2.rows(); i++)
				{
					// _mat3[rowb+i][j] = _mat2[i][j]
					_mat3.atr(rowb+i,j) = _mat2.at(i,j);
				}
			}
		}

	public:
		inline unsigned int rowsEnd()
		{
			return (rows() - 1);
		}

		inline unsigned int colsEnd()
		{
			return (cols() - 1);
		}

	public:
		inline void setAll(Number _number)
		{
			for(unsigned int n = 0; n < cols()*rows(); n++)
			{
				atr(n) = _number;
			}
		}

		inline void setAll(Number* _number)
		{
			setAll(*_number);
		}

		inline void setZeros(unsigned int _row, unsigned int _col)
		{
			resize(_row, _col);
			setAll((Number)0);
		}

		inline void setOnes(unsigned int _row, unsigned int _col)
		{
			resize(_row, _col);
			setAll((Number)1);
		}

		inline bool isEqual(Number _number)
		{
			for (unsigned int i = 0; i < rows(); i++)
			{
				for (unsigned int j = 0; j < cols(); j++)
				{
					if(at(i,j) != _number)
						return false;
				}
			}
			// all i,j: data[i][j] == _number
			return true;
		}

		inline bool isZeros()
		{
			isEqual((Number)0);
		}

		inline bool isOnes()
		{
			isEqual((Number)1);
		}

	public:
		// rows
		inline bool getRow(unsigned int _rowb, unsigned int _rowe, _Matrix& _mat)
		{
			if(!(_rowb < rows()) || !(_rowe < rows())
				|| !(_rowb <= _rowe))
				return false;

			unsigned int nrow = _rowe - _rowb + 1;
			_mat.alloc(nrow, cols());
			for(unsigned int i = 0; i < nrow; i++)
			{
				for(unsigned int j = 0; j < cols(); j++)
				{
					// _mat.data[i][j] = data[_rowb+i][j]
					_mat.atr(i,j) = at(_rowb+i,j);
				}
			}

			return true;
		}

		inline bool getRow(unsigned int _row, _Matrix& _mat)
		{
			return getRow(_row, _row, _mat);
		}

		inline bool setRow(unsigned int _rowb, unsigned int _rowe, _Matrix& _mat)
		{
			if(!(_rowb < rows()) || !(_rowe < rows())
				|| !(_rowb <= _rowe))
				return false;

			unsigned int nrow = _rowe - _rowb + 1;
			if(cols() != _mat.cols() || _mat.rows() != nrow)
				return false;

			for(unsigned int i = 0; i < nrow; i++)
			{
				for(unsigned int j = 0; j < cols(); j++)
				{
					// data[_rowb+i][j] = _mat.data[i][j];
					atr(_rowb+i,j) = _mat.at(i,j);
				}
			}

			return true;
		}

		inline bool setRow(unsigned int _rowb, unsigned int _rowe, _Number _number)
		{
			if(!(_rowb < rows()) || !(_rowe < rows())
				|| !(_rowb <= _rowe))
				return false;

			unsigned int nrow = _rowe - _rowb + 1;
			for(unsigned int i = 0; i < nrow; i++)
			{
				for(unsigned int j = 0; j < cols(); j++)
				{
					// data[_rowb+i][j] = _number
					atr(_rowb+i,j) = _number;
				}
			}

			return true;
		}

		inline bool setRow(unsigned int _row, _Number _number)
		{
			return setRow(_row, _row, _number);
		}

		// columns
		inline bool getCol(unsigned int _colb, unsigned int _cole, _Matrix& _mat)
		{
			if(!(_colb < cols()) || !(_cole < cols())
				|| !(_colb <= _cole))
				return false;

			unsigned int ncol = _cole - _colb + 1;
			_mat.alloc(rows(), ncol);
			for(unsigned int i = 0; i < rows(); i++)
			{
				for(unsigned int j = 0; j < ncol; j++)
				{
					// _mat.data[i][j] = data[i][_colb+j]
					_mat.atr(i,j) = at(i,_colb+j);
				}
			}

			return true;
		}

		inline bool getCol(unsigned int _col, _Matrix& _mat)
		{
			return getCol(_col, _col, _mat);
		}

		inline bool setCol(unsigned int _colb, unsigned int _cole, _Matrix& _mat)
		{
			if(!(_colb < cols()) || !(_cole < cols())
				|| !(_colb <= _cole))
				return false;

			unsigned int ncol = _cole - _colb + 1;
			if(rows() != _mat.rows() || _mat.cols() != ncol)
				return false;

			for(unsigned int j = 0; j < ncol; j++)
			{
				for(unsigned int i = 0; i < rows(); i++)
				{
					// data[i][_colb+j] = _mat.data[i][j];
					atr(i,_colb+j) = _mat.at(i,j);
				}
			}

			return true;
		}

		inline bool setCol(unsigned int _colb, unsigned int _cole, _Number _number)
		{
			if(!(_colb < cols()) || !(_cole < cols())
				|| !(_colb <= _cole))
				return false;

			unsigned int ncol = _cole - _colb + 1;
			for(unsigned int j = 0; j < ncol; j++)
			{
				for(unsigned int i = 0; i < rows(); i++)
				{
					// data[i][_colb+j] = _number;
					atr(i,_colb+j) = _number;
				}
			}

			return true;
		}

		inline bool setCol(unsigned int _col, _Number _number)
		{
			return setCol(_col, _col, _number);
		}

	public:
		// data = [data[0~_rowb-1][:] ; _mat ; data[_rowb:end][:]]
		inline bool insertRow(unsigned int _rowb, _Matrix& _mat)
		{
			if(!(cols() == _mat.cols())
				|| !(_rowb < rows()))
				return false;

			unsigned int bfrow =  rows();
			unsigned int insrow = _mat.rows();
			_Matrix mat1, mat2;
			
			getRow(0, _rowb-1, mat1);
			getRow(_rowb, bfrow-1, mat2);
			
			resize(bfrow+insrow, _mat.cols());
			
			setRow(0, _rowb-1, mat1);
			setRow(_rowb, _rowb+insrow-1, _mat);
			setRow(_rowb+insrow, rows()-1, mat2);
			return true;
		}

		// data = [data[:][0~_colb] _mat data[:][_colb:end]]
		inline bool insertCol(unsigned int _colb, _Matrix& _mat)
		{
			if(!(rows() == _mat.rows())
				|| !(_colb < cols()))
				return false;

			unsigned int bfcol = cols();
			unsigned int inscol = _mat.cols();
			_Matrix mat1, mat2;

			getCol(0, _colb-1, mat1);
			getCol(_colb, bfcol-1, mat2);

			resize(_mat.rows(), bfcol+inscol);

			setCol(0, _colb-1, mat1);
			setCol(_colb, _colb+inscol-1, _mat);
			setCol(_colb+inscol, cols()-1, mat2);
			return true;
		}


	public:
		inline bool meanRow(_Matrix& _mat)
		{
			if(assert() == false)
				return false;

			_mat.resize(rows(), 1);
			for (unsigned int i = 0; i < rows(); i++)
			{
				_Number sum = 0;
				for (unsigned int j = 0; j < cols(); j++)
				{
					// sum all in one row
					sum += at(i,j);
				}
				_mat.atr(i,1) = sum / cols();
			}
		}

		inline bool meanCol(_Matrix& _mat)
		{
			if(assert() == false)
				return false;

			_mat.resize(cols(), 1);
			for (unsigned int j = 0; j < cols(); j++)
			{
				_Number sum = at(0,j);
				for (unsigned int i = 0; i < rows(); i++)
				{
					// sum all in one row
					sum += at(i,j);
				}
				_mat.atr(j,1) = sum / rows();
			}
		}

		inline bool maxRow(_Matrix& _mat)
		{
			if(assert() == false)
				return false;

			_mat.resize(rows(), 1);
			for (unsigned int i = 0; i < rows(); i++)
			{
				_Number max = at(i,0);
				for (unsigned int j = 0; j < cols(); j++)
				{
					if(at(i,j) > max)
						max = at(i,j);
				}
				_mat.atr(i,1) = max;
			}
		}

		inline bool maxCol(_Matrix& _mat)
		{
			if(assert() == false)
				return false;

			_mat.resize(cols(), 1);
			for (unsigned int j = 0; j < cols(); j++)
			{
				_Number max = at(0,j);
				for (unsigned int i = 0; i < rows(); i++)
				{
					if(at(i,j) > max)
						max = at(i,j);
				}
				_mat.atr(j,1) = max;
			}
		}

		inline bool minRow(_Matrix& _mat)
		{
			if(assert() == false)
				return false;

			_mat.resize(rows(), 1);
			for (unsigned int i = 0; i < rows(); i++)
			{
				_Number min = at(i,0);
				for (unsigned int j = 0; j < cols(); j++)
				{
					if(at(i,j) < min)
						min = at(i,j);
				}
				_mat.atr(i,1) = min;
			}
		}

		inline bool minCol(_Matrix& _mat)
		{
			if(assert() == false)
				return false;

			_mat.resize(cols(), 1);
			for (unsigned int j = 0; j < cols(); j++)
			{
				_Number min = at(0,j);
				for (unsigned int i = 0; i < rows(); i++)
				{
					if(at(i,j) < min)
						min = at(i,j);
				}
				_mat.atr(j,1) = min;
			}
		}

	public:
		inline bool swapRow(unsigned int _row1, unsigned int _row2)
		{
			if(assert() == false
				|| !(_row1 < rows()) || !(_row2 < rows()))
				return false;

			_Number tmp;
			for(unsigned int j = 0; j < cols(); j++)
			{
				// data[_row1][j] <==> data[_row2][j]
				tmp = at(_row1,j);
				atr(_row1,j) = at(_row2,j);
				atr(_row2,j) = tmp;
			}

			return true;
		}

		inline bool swapCol(unsigned int _col1, unsigned int _col2)
		{
			if(assert() == false
				|| !(_col1 < cols()) || !(_col2 < cols()))
				return false;

			_Number tmp = 0;
			for (unsigned int i = 0; i < rows(); i++)
			{
				// data[i][_col1] <==> data[i][_col2]
				tmp = at(i,_col1);
				atr(i,_col1) = at(i,_col2);
				atr(i,_col2) = tmp;
			}

			return true;
		}

	public:
		inline void getTranspose(_Matrix& _mat)
		{
			if(assert() == false)
			{
				// zeros matrix
				_mat.free();
			}

			_mat.resize(cols(), rows());
			for (unsigned int i = 0; i < cols(); i++)
			{
				for (unsigned int j = 0; j < rows(); j++)
				{
					// _mat.data = data'
					_mat.atr(i,j) = at(j,i);
				}
			}
		}

	public:
		inline _Matrix& operator = (_Matrix& _mat) const
		{
			copy(_mat);
			return (*this);
		}

	public:
		inline void toString()
		{
			string buffer;
			ostringstream sstr;
			for(unsigned int i = 0; i < rows(); i++)
			{
				for(unsigned int j = 0; j < cols(); j++)
				{
					sstr << at(i,j) << ' ';
				}
				sstr << '\n';
			}
			// output matrix
			cout << sstr.str() << endl;
		}
	};
}




#endif