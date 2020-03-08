#pragma once
#include <type_traits>
#include <limits>
#include <cmath>
#include <array>
#include <vector>

namespace CppNative {

	enum class eVALUE
	{
		DIST, ACC, RET, V_START, V_CRUISE, V_END
	};

	class CalcTime
	{
	public:
		CalcTime() {}
		~CalcTime() {}
		double Get(eVALUE val) const;
		using vecPair	= std::vector<std::pair<double, double>>;
		using cdbl		= const double;
		vecPair totTime(const std::pair<eVALUE, double>& calcVar);
		vecPair totTime(cdbl dist, cdbl acc, cdbl ret, cdbl v0, cdbl v1, cdbl v2);

	private:
		double m_dist	= 100;
		double m_acc	= 1.0;
		double m_ret	= -1.0;
		std::array<double, 3U> m_vel{ 0.0, 10.0, 0.0 }; /* Start, cruise, stop */

		double calcTime(cdbl v0, cdbl v1) const noexcept;
		double calcTimeCru() const;
		double calcMaxVel() const;
		vecPair calcVector() const;

		/* Functions that could be moved to a library */
		template<typename T>
		bool inRange(const T first, const T mid, const T last) const;
		
		template<typename T, size_t N>
		bool isLessThenAbsEpsInArr(const std::array<T, N>& arr) const;
	};

	/* Check if the input values is in a range a > b > c or a < b < c */
	template<typename T>
	inline bool CalcTime::inRange(const T a, const T b, const T c) const
	{
		static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value, "Not a floating point or integral value");
		return !(std::min(a, c) > b) && !(b > std::max(a, c));
	}

	/* Find a value less then epsilon in array */
	template<typename T, size_t N>
	inline bool CalcTime::isLessThenAbsEpsInArr(const std::array<T, N>& arr) const
	{
		constexpr T eps = std::numeric_limits<T>::epsilon();
		auto func = [eps](const T& i) {
			return std::fabs(i) < eps;
		};
		return std::find_if(arr.cbegin(), arr.cend(), func) != arr.cend();
	}
}
