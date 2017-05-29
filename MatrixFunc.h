//
//
#ifndef MatrixFunc_h__
#define MatrixFunc_h__

#include "Matrix.h"

namespace MatrixLib
{
	/*
	   abstract:
		  determine whether the specify element of matrix is nan/inf
	   reference:
	      http://en.cppreference.com/w/cpp/numeric/math/isnan
	   function:
	      isNan: whether the element is number or not
		  isInf: whether the element is finite or not
		  isExistNan: 
		  isExistInf:
	*/

	// _mat(_n) == nan
	template<class Number = double>
	bool isNan(Matrix<Number>& _mat, unsigned int _n)
	{
		return isnan(_mat.at(_n));
	}

	// _mat(_i,_j) == nan
	template<class Number = double>
	bool isNan(Matrix<Number>& _mat, unsigned int _i, unsigned int _j)
	{
		return isnan(_mat.at(_i, _j));
	}

	// for all i,j, exist (_mat(i,j) == nan)?
	template<class Number = double>
	bool isExistNan(Matrix<Number>& _mat)
	{
		unsigned int row = _mat.rows();
		unsigned int col = _mat.cols();
		for(unsigned int n = 0; n < row*col; n++)
		{
			// exist?
			if(isnan(_mat.at(n)) == true)
				return true;
		}
		//
		return false;
	}

	// _mat(_n) == inf
	template<class Number = double>
	bool isInf(Matrix<Number>& _mat, unsigned int _n)
	{
		return isinf(_mat.at(_n));
	}

	// _mat(_i,_j) == inf
	template<class Number = double>
	bool isInf(Matrix<Number>& _mat, unsigned int _i, unsigned int _j)
	{
		return isinf(_mat.at(_i, _j));
	}

	// for all i,j, exist (_mat(i,j) == inf)?
	template<class Number = double>
	bool isExistInf(Matrix<Number>& _mat)
	{
		unsigned int row = _mat.rows();
		unsigned int col = _mat.cols();
		for(unsigned int n = 0; n < row*col; n++)
		{
			// exist?
			if(isinf(_mat.at(n)) == true)
				return true;
		}
		//
		return false;
	}

	/*
	   abstract:
		  calculate some special value of the matrix
	   function:
		  getNormL0:
	      getNormL1:
		  getNormL2:
		  getNormInf:
		  getNormF:
	*/

	// 
	template<class Number = double>
	unsigned int getNormL0(Matrix<Number>& _mat)
	{
		unsigned int norms = 0;
		unsigned int row = _mat.rows();
		unsigned int col = _mat.cols();
		for(unsigned int n = 0; n < row*col; n++)
		{
			// _mat[n] == 0 ?
			if(_mat.at(n) == 0)
				norms++;
		}
		//
		return norms;
	}

	// 
	template<class Number = double>
	Number getNormL1(Matrix<Number>& _mat)
	{
		Matrix<Number> csum;

		csum.resize(1, _mat.cols());
		for(unsigned int j = 0; j < _mat.cols(); j++)		
		{
			for(unsigned int i = 0; i < _mat.rows(); i++)
			{
				csum.atr(1,j) += abs(_mat.at(i,j));
			}
		}
		//
		return csum.maxEle();
	}

	// 
	template<class Number = double>
	Number getNormL2(Matrix<Number>& _mat)
	{

	}

	// 
	template<class Number = double>
	Number getNormInf(Matrix<Number>& _mat)
	{
		Matrix<Number> rsum;

		rsum.resize(_mat.rows(), 1);
		for(unsigned int i = 0; i < _mat.rows(); i++)
		{
			for(unsigned int j = 0; j < _mat.cols(); j++)		
			{
				rsum.atr(i,1) += abs(_mat.at(i,j));
			}
		}
		//
		return rsum.maxEle();
	}

	// 
	template<class Number = double>
	void getNormF(Matrix<Number>& _mat)
	{
		Number norms = 0;
		unsigned int row = _mat.rows();
		unsigned int col = _mat.cols();
		for(unsigned int n = 0; n < row*col; n++)
		{
			// _mat[n] == 0 ?
			norms += pow(_mat.at(n),2);
		}
		//
		return sqrt(norms);
	}


	/*
	   abstract:
		  get a special matrix
	   function:
	      getZeros:
		  getOnes:
		  getEyes:
		  getRandu:
		  getRandn:
		  getMagic:
		  getVander:
	*/

	// 
	template<class Number = double>
	void getZeros(Matrix<Number>& _mat, unsigned int _rows, unsigned int _cols)
	{
		_mat.resize(_rows, _cols);
		_mat.setAll(0);
	}

	// 
	template<class Number = double>
	void getOnes(Matrix<Number>& _mat, unsigned int _rows, unsigned int _cols)
	{
		_mat.resize(_rows, _cols);
		_mat.setAll(1);
	}

	//
	template<class Number = double>
	void getEyes(Matrix<Number>& _mat, unsigned int _n)
	{
		_mat.resize(_n, _n);
		_mat.setAll(0);
		for(unsigned int n = 0; n < _mat.rows(); n++)
		{
			// diagonal number is 1
			_mat.atr(n, n) = 1;
		}
	}

	//
	template<class Number = double>
	void getMagic(Matrix<Number>& _mat, unsigned int _n)
	{

	}

	//
	template<class Number = double>
	void getVander(Matrix<Number>& _mat, Matrix<Number>& _v)
	{

	}

	//
	template<class Number = double>
	void randUniformf(Matrix<Number>& _mat, unsigned int _rows, unsigned int _cols)
	{
		_mat.resize(_rows, _cols);
		_mat.randUniformf(_rows, _cols);
	}

	//
	template<class Number = double>
	void randUniformi(Matrix<Number>& _mat, unsigned int _rows, unsigned int _cols)
	{
		_mat.resize(_rows, _cols);
		_mat.randUniformi(_rows, _cols);
	}

	//
	template<class Number = double>
	void randNormal(Matrix<Number>& _mat, unsigned int _rows, unsigned int _cols)
	{
		_mat.resize(_rows, _cols);
		_mat.randNormal(_rows, _cols);
	}

	//
	template<class Number = double>
	void randPermutation(Matrix<Number>& _mat, unsigned int _n)
	{
		_mat.resize(_n, _n);
	}

	/*
	   abstract:
		  specify function of N-order matrix
	   function:
	      isOrderMatrix:
		  isSymmetric:
		  isDiagonal:
		  getInverse:
	*/

	//
	template<class Number = double>
	bool isOrderMatrix(Matrix<Number>& _mat, bool _throw = false)
	{
		if(_mat.assert() == false)
		{
			// it is zeros matrix
			throw MatrixThrow_IsOrderMatrix;
		}
		
		return (_mat.rows() == _mat.cols()) ? true:false;
	}

	//
	template<class Number = double>
	bool isSymmetric(Matrix<Number>& _mat)
	{
		if(isOrderMatrix(_mat) == false)
		{
			// is order matrix
			return false;
		}

		for(unsigned int i = 0; i < _mat.rows(); i++)
		{
			for(unsigned int j = i; j < _mat.cols(); j++)
			{
				// if _mat[i][j] != _mat[j][i]
				if(_mat.at(i,j) != _mat.at(j,i))
					return false;
			}
		}
		// finishing compare
		return true;
	}

	//
	template<class Number = double>
	bool isDiagonal(Matrix<Number>& _mat)
	{
		if(isOrderMatrix(_mat) == false)
		{
			// is order matrix
			return false;
		}

		for(unsigned int i = 0; i < _mat.rows(); i++)
		{
			for(unsigned int j = 0; j < _mat.cols(); j++)
			{
				// if _mat[i][j] != _mat[j][i]
				if(i != j && _mat.at(i,j) != _mat.at(j,i))
					return false;
			}
		}
		// finishing compare
		return true;
	}

	//
	template<class Number = double>
	void getInverse(Matrix<Number>& _mat, Matrix<Number>& _inv)
	{

	}

	template<class Number = double>
	Number getTrace(Matrix<Number>& _mat)
	{

	}

	template<class Number = double>
	Number getRank(Matrix<Number>& _mat)
	{

	}

	template<class Number = double>
	void getEigen(Matrix<Number>& _mat, Matrix<Number>& _eig, Matrix<Number>& _u)
	{

	}
}




#endif