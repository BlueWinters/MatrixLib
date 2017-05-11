//
//
#ifndef MatrixIO_h__
#define MatrixIO_h__

#include <iostream>
#include <sstream>
#include <fstream>
#include "Matrix.h"


namespace MatrixLib
{
	template<class Matrix>
	void mat2String(const Matrix& _mat, std::string& str)
	{
		std::ostringstream buffer;
		for(unsigned int i = 0; i < _mat.rows(); i++)
		{
			for(unsigned int j = 0; j < _mat.cols(); j++)
			{
				buffer << _mat.at(i,j) << ' ';
			}
			buffer << '\n';
		}
		// output matrix
		str.append(buffer.str());
	}

	template<class Matrix>
	void mat2File(const Matrix& _mat, char* _file)
	{
		std::fstream hfile(_file);
		std::ostringstream buffer;
		std::string str;
		
		mat2String(_mat, str);		
		buffer << '[' << _mat.rows() << ' ' 
			<< _mat.cols() << ']' << endl;
		
		hfile << buffer.str() << endl;
		hfile << str << endl;
		hfile.close();
	}


	template<class Matrix>
	void printMatrix(const Matrix& _mat)
	{
		std::string str;
		mat2String(_mat, str);
		cout << str << endl;
	}

	template<class Matrix>
	void file2Matrix(Matrix& _mat, char* _file)
	{
		std::fstream hfile(_file);
		std::string buffer;

		hfile.getline(buffer);
		if(buffer.front() != '['
			|| buffer.back() != ']')
			return;

		std::istringstream istr(buffer);
		unsigned int row = 0;
		unsigned int col = 0;
		char tmp;
		istr >> tmp >> row >> col >> tmp;

		buffer.clear();
		_mat.resize(row, col);
		for (unsigned int i = 0; i < row; i++)
		{
			hfile.getline(buffer);
			istr.str(buffer);
			for (unsigned int j = 0; j < col; j++)
			{
				double value = 0;
				istr >> value;
				_mat.set(i, j, value);
			}
			buffer.clear();
			istr.clear();
		}

		hfile.close();
	} 
}

#endif