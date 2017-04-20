//
//
#ifndef Number_h__
#define Number_h__

#include <sstream>
#include "Stdafx.h"
#include "Gmath.h"


namespace Geometric
{
	class _GEOMETRIC Real
	{
	public:
		Real(double _value)
		{
			m_value = _value;
		}

		explicit Real(const Real& _real)
		{
			m_value = _real.m_value;
		}

		Real()
		{
			m_value = 0;
		}

		~Real()
		{

		}

	public:
		// actual value of this object
		double m_value;

	protected:
		// static object for global use
		static inline Real& object()
		{
			static Real real;
			return real;
		}

	public:
		inline Real& operator = (const Real& _real)
		{
			m_value = _real.m_value;
			return (*this);
		}

		inline Real& operator = (double _value)
		{
			m_value = _value;
			return (*this);
		}

	public:
		friend inline bool operator == (const Real& _real1, const Real& _real2)
		{
			return (_real1.m_value == _real2.m_value);
		}

		friend inline bool operator != (const Real& _real1, const Real& _real2)
		{
			return (_real1.m_value != _real2.m_value);
		}

		friend inline bool operator < (const Real& _real1, const Real& _real2)
		{
			return (_real1.m_value < _real2.m_value);
		}

		friend inline bool operator <= (const Real& _real1, const Real& _real2)
		{
			return (_real1.m_value <= _real2.m_value);
		}

		friend inline bool operator > (const Real& _real1, const Real& _real2)
		{
			return (_real1.m_value > _real2.m_value);
		}

		friend inline bool operator >= (const Real& _real1, const Real& _real2)
		{
			return (_real1.m_value >= _real2.m_value);
		}

	public:
		// static object is used for operator(+,-,*,/) override
		friend inline const Real& operator + (const Real& _real1, const Real& _real2)
		{
			Real& real = Real::object();
			real = _real1.m_value + _real2.m_value;
			return (real);
		}

		friend inline const Real& operator - (const Real& _real1, const Real& _real2)
		{
			Real& real = Real::object();
			real = _real1.m_value - _real2.m_value;
			return (real);
		}

		friend inline const Real& operator * (const Real& _real1, const Real& _real2)
		{
			Real& real = Real::object();
			real = _real1.m_value * _real2.m_value;
			return (real);
		}

		friend inline const Real& operator / (const Real& _real1, const Real& _real2)
		{
			Real& real = Real::object();
			real = _real1.m_value / _real2.m_value;
			return (real);
		}

	public:
		inline Real& operator += (const Real& _real)
		{
			m_value += _real.m_value;
			return (*this);
		}

		inline Real& operator -= (const Real& _real)
		{
			m_value -= _real.m_value;
			return (*this);
		}

		inline Real& operator *= (const Real& _real)
		{
			m_value *= _real.m_value;
			return (*this);
		}

		inline Real& operator /= (const Real& _real)
		{
			m_value /= _real.m_value;
			return (*this);
		}

	public:
		inline Real& operator ++ ()
		{
			m_value++;
			return (*this);
		}

		inline Real& operator -- ()
		{
			m_value--;
			return (*this);
		}

		inline Real& operator + ()
		{
			return (*this);
		}

		inline Real& operator - ()
		{
			Real& real = Real::object();
			real.m_value = - m_value;
			return (real);
		}
	};


	//
	class _GEOMETRIC Fraction
	{
	public:
		Fraction(int _a, unsigned int _b) 
		{
			// forbid: b=0 
			m_a = _a;
			m_b = (_b != 0) ? _b : 1;
		}

		Fraction(double _value)
		{
			set(_value);
		}

		explicit Fraction(const Fraction& _fra)
		{
			// forbid: b=0 
			m_a = _fra.m_a;
			m_b = (_fra.m_b != 0) ? _fra.m_b : 1;
		}

		Fraction()
		{
			// default value is 0(a=0, b=1)
			m_a = 0;
			m_b = 1;
		}

		~Fraction()
		{

		}

	public:
		// fraction=a/b, m_a contains the sign of fraction
		int m_a;
	protected:
		unsigned int m_b;

	protected:
		static inline Fraction& object()
		{
			static Fraction fra;
			return fra;
		}

	public:
		inline void simplify()
		{
			if(m_b != 1)
			{
				unsigned int divisor = Gmath::toGreatDivisor(m_a, m_b);
				m_a /= static_cast<int>(divisor);
				m_b /= divisor;
			}
		}

		inline void set(int _a, unsigned int _b)
		{
			m_a = _a;
			m_b = (_b != 0) ? _b : 1;
			simplify();
		}

		inline void set(double _value)
		{
			std::stringstream sbuffer;
			std::string str;
			sbuffer << _value;
			str = sbuffer.str();

			m_a = 0;
			m_b = 1;
			
			// for example: "-1234.56"
			// m_a=-123456, m_b=100
			unsigned int dot_pos = str.find('.');
			// set m_a
			for(unsigned int i = str.size()-1; i >= 0 ; i++)
			{
				char cur = str[i];
				// there maybe exist '-' or '.'
				if('1' <= cur && cur <= '9')
				{
					// char '1'-->47
					m_a = m_a * 10 + ((int)cur - 47);
				}
			}
			// set m_b
			for(unsigned int i = dot_pos; i < str.size(); i++)
			{
				char cur = str[i];
				if('1' <= cur && cur <= '9')
				{
					m_b = m_b * 10;
				}
			}

			if(str.find('-') != std::string::npos)
			{
				m_a = -m_a;
			}

			simplify();
		}

		inline bool isValid()
		{
			return (m_b != 0);
		}

		inline bool isPositive()
		{
			return (m_a > 0 && m_b != 0);
		}

		inline bool isZero()
		{
			return (m_a == 0 && m_b != 0);
		}

	public:
		inline Fraction& operator = (const Fraction& _fra)
		{
			m_a = _fra.m_a;
			m_b = _fra.m_b;
			return (*this);
		}

	public:
		friend inline bool operator == (const Fraction& _fra1, const Fraction& _fra2)
		{
			return ((_fra1.m_a * _fra2.m_b - _fra1.m_b * _fra2.m_a) == 0);
		}

		friend inline bool operator != (const Fraction& _fra1, const Fraction& _fra2)
		{
			return ((_fra1.m_a * _fra2.m_b - _fra2.m_b * _fra2.m_a) != 0);
		}

	public:
		friend inline bool operator < (const Fraction& _fra1, const Fraction& _fra2)
		{
			return ((_fra1.m_a * _fra2.m_b - _fra1.m_b * _fra2.m_a) < 0);
		}

		friend inline bool operator <= (const Fraction& _fra1, const Fraction& _fra2)
		{
			return ((_fra1.m_a * _fra2.m_b - _fra1.m_b * _fra2.m_a) <= 0);
		}

		friend inline bool operator > (const Fraction& _fra1, const Fraction& _fra2)
		{
			return ((_fra1.m_a * _fra2.m_b - _fra1.m_b * _fra2.m_a) > 0);
		}

		friend inline bool operator >= (const Fraction& _fra1, const Fraction& _fra2)
		{
			return ((_fra1.m_a * _fra2.m_b - _fra1.m_b * _fra2.m_a) >= 0);
		}

	public:
		// static object is used for operator(+,-,*,/) override
		friend inline const Fraction& operator + (const Fraction& _fra1, const Fraction& _fra2)
		{
			Fraction& fra = Fraction::object();
			unsigned int base = Gmath::toLeastMultiple(_fra1.m_b, _fra2.m_b);
			fra.m_a = _fra1.m_a * base / _fra1.m_b + _fra2.m_a * base / _fra2.m_b;
			fra.m_b = base;
			return fra;
		}

		friend inline const Fraction& operator - (const Fraction& _fra1, const Fraction& _fra2)
		{
			Fraction& fra = Fraction::object();
			unsigned int base = Gmath::toLeastMultiple(_fra1.m_b, _fra2.m_b);
			fra.m_a = _fra1.m_a * base / _fra1.m_b - _fra2.m_a * base / _fra2.m_b;
			fra.m_b = base;
			return fra;
		}

		friend inline const Fraction& operator * (const Fraction& _fra1, const Fraction& _fra2)
		{
			Fraction& fra = Fraction::object();
			fra.m_a = _fra1.m_a * _fra2.m_a;
			fra.m_b = _fra1.m_b * _fra2.m_b;
			return fra;
		}

		friend inline const Fraction& operator / (const Fraction& _fra1, const Fraction& _fra2)
		{
			Fraction& fra = Fraction::object();
			fra.m_a = _fra1.m_a * _fra2.m_b;
			fra.m_b = _fra1.m_b * _fra2.m_a;
			return fra;
		}

	public:
		inline Fraction& operator += (const Fraction& _fra)
		{
			unsigned int base = Gmath::toLeastMultiple(m_b, _fra.m_b);
			m_a = m_a * base / m_b + _fra.m_a * base / _fra.m_b;
			m_b = base;
			return (*this);
		}

		inline Fraction& operator -= (const Fraction& _fra)
		{
			unsigned int base = Gmath::toLeastMultiple(m_b, _fra.m_b);
			m_a = m_a * base / m_b - _fra.m_a * base / _fra.m_b;
			m_b = base;
			return (*this);
		}

		inline Fraction& operator *= (const Fraction& _fra)
		{
			m_a *= _fra.m_a;
			m_b *= _fra.m_b;
			return (*this);
		}

		inline Fraction& operator /= (const Fraction& _fra)
		{
			if(_fra.m_a != 0 && _fra.m_b != 0)
			{
				m_a *= _fra.m_b;
				m_b *= _fra.m_a;
			}

			return (*this);
		}

		inline Fraction& operator ++ ()
		{
			m_a += static_cast<int>(m_b);
			return (*this);
		}

		inline Fraction& operator -- ()
		{
			m_a -= static_cast<int>(m_b);
			return (*this);
		}

		inline Fraction& operator + ()
		{
			return (*this);
		}

		inline Fraction& operator - ()
		{
			Fraction& fra = Fraction::object();
			fra.m_a = - m_a;
			return (fra);
		}

	};


	template<typename Number>
	class _GEOMETRIC Complex
	{
	public:
		typedef typename Complex<Number> _Complex;
		typedef typename Number _Number;

	public:
		Complex(Number _a, Number _b)
		{
			m_a = _a;
			m_b = _b;
		}

		Complex(double _value)
		{
			m_a = _value;
			m_b = 0;
		}

		explicit Complex(const Complex& _complex)
		{
			m_a = _complex.m_a;
			m_b = _complex.m_b;
		}

		Complex()
		{
			m_a = 0;
			m_b = 0;
		}

		~Complex()
		{

		}

	public:
		// complex=a+bi
		Number m_a;
		Number m_b;
		
	protected:
		static inline _Complex& object()
		{
			static _Complex cpl;
			return cpl
		}

	public:
		inline _Complex& operator = (const _Complex& _complex)
		{
			m_a = _complex.m_a;
			m_b = _complex.m_b;
			return (*this);
		}

	public:
		friend inline bool operator == (const _Complex& _complex1, const _Complex& _complex2)
		{
			return (_complex1.m_a == _complex2.m_a && _complex1.m_b == _complex2.m_b);
		}

		friend inline bool operator != (const _Complex& _complex1, const _Complex& _complex2)
		{
			return (_complex1.m_a != _complex2.m_a || _complex1.m_b != _complex2.m_b);
		}

	public:
		friend inline const _Complex& operator + (const _Complex& _cpl1, const _Complex& _cpl2)
		{
			_Complex& cpl = _Complex::object();
			cpl.m_a = _cpl1.m_a + _cpl2.m_a;
			cpl.m_b = _cpl1.m_b + _cpl2.m_b;
			return cpl;
		}

		friend inline const _Complex& operator - (const _Complex& _cpl1, const _Complex& _cpl2)
		{
			_Complex& cpl = _Complex::object();
			cpl.m_a = _cpl1.m_a - _cpl2.m_a;
			cpl.m_b = _cpl1.m_b - _cpl2.m_b;
			return cpl;
		}

		friend inline const _Complex& operator * (const _Complex& _cpl1, const _Complex& _cpl2)
		{
			_Complex& cpl = _Complex::object();
			cpl.m_a = _cpl1.m_a * _cpl2.m_a - _cpl1.m_b * _cpl2.m_b;
			cpl.m_b = _cpl1.m_a * _cpl2.m_b + _cpl1.m_b * _cpl2.m_a;
			return cpl;
		}

		friend inline const _Complex& operator / (const _Complex& _cpl1, const _Complex& _cpl2)
		{
			_Complex& cpl = _Complex::object();
			Number den = _cpl2.m_a * _cpl2.m_a + _cpl2.m_b * _cpl2.m_b
			cpl.m_a = (_cpl1.m_a * _cpl2.m_a + _cpl1.m_b * _cpl2.m_b) / den;
			cpl.m_b = (_cpl1.m_b * _cpl2.m_a - _cpl1.m_a * _cpl2.m_b) / den;
			return cpl;
		}

	public:
		inline _Complex& operator += (const _Complex& _complex)
		{
			m_a += _complex.m_a;
			m_b += _complex.m_b;
			return (*this);
		}

		inline _Complex& operator -= (const _Complex& _complex)
		{
			m_a -= _complex.m_a;
			m_b -= _complex.m_b;
			return (*this);
		}

		inline _Complex& operator *= (const _Complex& _complex)
		{
			// (a+bi)*(m+ni)=(am-bn)+(bm+an)i
			m_a = m_a * _complex.m_a - m_b * _complex.m_b;
			m_b = m_a * _complex.m_b + m_b * _complex.m_b;
			return (*this);
		}

		inline _Complex& operator /= (const _Complex& _complex)
		{
			// (a+bi)/(m+ni)=(am+bn)+(bm-an)i
			double den = _complex.m_a * _complex.m_a + _complex.m_b * _complex.m_b;
			m_a = (m_a * _complex.m_a + m_b * _complex.m_b) / den;
			m_b = (m_b * _complex.m_b - m_a * _complex.m_b) / den;
			return (*this);
		}

		inline _Complex& operator - ()
		{
			_Complex& cpl = _Complex::object();
			cpl.m_a = - m_a;
			cpl.m_b = - m_b;
			return cpl;
		}

		inline _Complex& operator + ()
		{
			return (*this);
		}
	};
}

#endif
