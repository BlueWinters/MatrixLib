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

		inline void free()
		{
			nRow = nCol = 0;
			delete[] data;
			data = NULL;
		}

	public:
		inline void copy(const MatrixB& _mat)
		{
			if(_mat.assert() == true)
			{
				alloc(_mat.nRow, _mat.nCol);
				memcpy(sizeof(Number)*nRow*nCol, _mat.data, data);
			}
			else
			{
				// zero matrix
				free();
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
			// is zero matrix
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
	};
}

#endif
