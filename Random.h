//
//
#ifndef Random_h__
#define Random_h__

#include <vector>
#include <random>
#include <algorithm>

namespace MatrixLib
{
	// distribution base class
	template<typename _Number = double>
	class Distribution
	{
	public:
		Distribution() :device(), gen(device())
		{

		}

		virtual ~Distribution()
		{

		}

	protected:
		// random device object
		// reference: http://en.cppreference.com/w/cpp/numeric/random/random_device
		std::random_device device;
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
			:lower(_lower), upper(_upper), nDis(lower, upper)
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
		std::uniform_real_distribution<_Number> nDis;

	public:
		virtual void sample(std::vector<_Number>& _vec, unsigned int _n)
		{
			_vec.resize(_n);
			for(unsigned int i = 0; i < _n; i++)
			{
				_vec[i] = nDis(gen);
			}
		}

		virtual _Number sample()
		{
			return nDis(gen);
		}

		virtual _Number reset()
		{
			nDis.reset();
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
			:lower(_lower), upper(_upper), uDis(lower, upper)
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
		std::uniform_int_distribution<_Number> uDis;

	public:
		virtual void sample(std::vector<_Number>& _vec, unsigned int _n)
		{
			_vec.resize(_n);
			for(unsigned int i = 0; i < _n; i++)
			{
				_vec[i] = uDis(gen);
			}
		}

		virtual _Number sample()
		{
			return uDis(gen);
		}

		virtual _Number reset()
		{
			uDis.reset();
		}
	};


	// normal distribution object for float number
	// _Number type should be float, double, long double
	template<typename _Number = double>
	class Normal : Distribution<_Number>
	{
	public:
		Normal(_Number _mean = 0.0, _Number _var = 1.0)
			:mean(_mean), var(_var), nDis(mean, var)
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
		std::normal_distribution<_Number> nDis;

	public:
		virtual void sample(std::vector<_Number>& _vec, unsigned int _n)
		{
			_vec.resize(_n);
			for(unsigned int i = 0; i < _n; i++)
			{
				_vec[i] = nDis(gen);
			}
		}

		virtual _Number sample()
		{
			return nDis(gen);
		}

		virtual _Number reset()
		{
			nDis.reset();
		}
	};


	// 
	class Sequence : Distribution<unsigned int>
	{
	public:
		Sequence(unsigned int _lower, unsigned int _upper)
			:lower(_lower), upper(_upper)
		{
			assert();
			initialize();
		}

		Sequence(unsigned int _n)
			:lower(1), upper(_n)
		{
			initialize();
		}

		~Sequence()
		{

		}

	protected:
		//
		unsigned int lower;
		unsigned int upper;
		//
		std::vector<unsigned int> seq;

	protected:
		void assert()
		{
			if(upper <= lower)
				throw ;
		}

		void initialize()
		{
			unsigned int count = upper - lower + 1;
			seq.resize(count);
			for(unsigned int n = 0; n < count; n++)
			{
				seq[n] = n + lower;
			}
		}

	public:
		virtual void sample(std::vector<unsigned int>& _vec)
		{
			std::random_shuffle(seq.begin(), seq.end());
			_vec = seq;
		}

	};
}// end for namespace



#endif