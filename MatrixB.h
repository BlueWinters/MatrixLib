//
//
#ifndef MatrixB_h__
#define MatrixB_h__

//#include "Stdafx.h"

namespace MatrixLib
{
	template<class Number>
	class MatrixB
	{
	public:
		MatrixB() :nRow(0), nCol(0), data(NULL)
		{
			
		}

		explicit MatrixB(const MatrixB& _matrix)
		{
			copy(_matrix);
		}

		MatrixB(unsigned int _row, unsigned int _col)
		{
			alloc(_row, _col);
		}

		virtual ~MatrixB()
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
				memset(data, 0, sizeof(Number)*nRow*nCol);
			}
		}

		virtual inline void free()
		{
			nRow = nCol = 0;
			delete[] data;
			data = NULL;
		}

		virtual inline void* datap() const
		{
			return (void*)data;
		}

	public:
		virtual inline void copy(MatrixB& _mat)
		{
			if(_mat.assert() == true)
			{
				alloc(_mat.nRow, _mat.nCol);
				memcpy(data, _mat.data, sizeof(Number)*nRow*nCol);
			}
			else
			{
				// zero matrix
				free();
			}
		}
		
		virtual inline unsigned int rows()
		{
			return nRow;
		}

		virtual inline unsigned int cols()
		{
			return nCol;
		}

		virtual inline unsigned int count()
		{
			return nRow*nCol;
		}

		virtual inline bool assert()
		{
			// is zero matrix
			return (nRow != 0 && nCol != 0 && data != NULL);
		}

		virtual inline void resize(unsigned int _row, unsigned int _col)
		{
			if(_row == 0 || _col == 0)
			{
				free();
			}
			else
			{
				alloc(_row, _col);
			}
		}

		virtual inline void zero()
		{
			// set zero matrix
			free();
		}

		virtual inline bool reshape(unsigned int _row, unsigned int _col)
		{
			if(nRow*nCol != _row*_col)
				return false;

			nRow = _row;
			nCol = _col;
			return true;
		}

	public:
		// get value
		virtual inline Number at(unsigned int _n)
		{
			return data[_n];
		}

		virtual inline Number at(unsigned int _i, unsigned int _j)
		{
			return data[nRow*_j+_i];
		}

		virtual inline Number& atr(unsigned int _n)
		{
			return data[_n];
		}

		virtual inline Number& atr(unsigned int _i, unsigned int _j)
		{
			return data[nRow*_j+_i];
		}

		virtual inline Number* atp(unsigned int _n)
		{
			return &(data[_n]);
		}

		virtual inline Number* atp(unsigned int _i, unsigned int _j)
		{
			return &(data[nRow*_j+_i]);
		}

		// set value
		virtual inline void set(unsigned int _n, Number _number)
		{
			data[_n] = _number;
		}

		virtual inline void set(unsigned int _i, unsigned int _j, Number _number)
		{
			data[nRow*_j+_i] = _number;
		}

		virtual inline void setp(unsigned int _n, Number* _number)
		{
			data[_n] = *_number;
		}

		virtual inline void setp(unsigned int _i, unsigned int _j, Number* _number)
		{
			data[nRow*_j+_i] = *_number;
		}
	};
}

#endif
