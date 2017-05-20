//
//
#ifndef Random_h__
#define Random_h__

#include <vector>
#include <random>

namespace MatrixLib
{
	// distribution base class
	template<typename _Number = double>
	class Distribution
	{
	public:
		Distribution() :rdev(), gen(rdev())
		{

		}

		virtual ~Distribution()
		{

		}

	protected:
		// random device object
		// reference: http://en.cppreference.com/w/cpp/numeric/random/random_device
		std::random_device rdev;
		std::mt19937 gen;

	public:
		virtual _Number sample() = 0;
		virtual void sample(std::vector<_Number>& _vec, unsigned int _n) = 0;
		virtual void reset() = 0;
	};


	// uniform distribution object for float number
	// _Number type should be float, double, long double
	template<typename _Number = double>
	class UniformFloat : Distribution<_Number>
	{
	public:
		UniformFloat(_Number _lower = 0.0, _Number _upper = 1.0)
			:lower(_lower), upper(_upper), ndist(lower, upper)
		{

		}

		virtual ~UniformFloat()
		{

		}

	protected:
		// uniform distribution: [lower upper]
		_Number lower;
		_Number upper;
		// distribution object
		// reference: http://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
		std::uniform_real_distribution<_Number> ndist;

	public:
		virtual void sample(std::vector<_Number>& _vec, unsigned int _n)
		{
			_vec.resize(_n);
			for(unsigned int i = 0; i < _n; i++)
			{
				_vec[i] = ndist(gen);
			}
		}

		virtual _Number sample()
		{
			return ndist(gen);
		}

		virtual _Number reset()
		{
			ndist.reset();
		}
	};


	// uniform distribution object for unsigned number
	// _Number type should be short, int, long, long long, unsigned short, 
	//						  unsigned int, unsigned long, or unsigned long long
	template<typename _Number = unsigned int>
	class UniformInt : Distribution<_Number>
	{
	public:
		UniformInt(_Number _lower, _Number _upper)
			:lower(_lower), upper(_upper), ndist(lower, upper)
		{

		}

		virtual ~UniformInt()
		{

		}

	protected:
		// uniform distribution: [lower upper]
		_Number lower;
		_Number upper;
		// distribution object
		// reference: http://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
		std::uniform_int_distribution<_Number> ndist;

	public:
		virtual void sample(std::vector<_Number>& _vec, unsigned int _n)
		{
			_vec.resize(_n);
			for(unsigned int i = 0; i < _n; i++)
			{
				_vec[i] = ndist(gen);
			}
		}

		virtual _Number sample()
		{
			return ndist(gen);
		}

		virtual _Number reset()
		{
			ndist.reset();
		}
	};


	// normal distribution object for float number
	// _Number type should be float, double, long double
	template<typename _Number = double>
	class Normal : Distribution<_Number>
	{
	public:
		Normal(_Number _mean = 0.0, _Number _var = 1.0)
			:mean(_mean), var(_var), ndist(mean, var)
		{

		}

		virtual ~Normal()
		{

		}

	protected:
		// uniform distribution: [lower upper]
		_Number mean;
		_Number var;
		// distribution object
		std::normal_distribution<_Number> ndist;

	public:
		virtual void sample(std::vector<_Number>& _vec, unsigned int _n)
		{
			_vec.resize(_n);
			for(unsigned int i = 0; i < _n; i++)
			{
				_vec[i] = ndist(gen);
			}
		}

		virtual _Number sample()
		{
			return ndist(gen);
		}

		virtual _Number reset()
		{
			ndist.reset();
		}
	};
}// end for namespace



#endif