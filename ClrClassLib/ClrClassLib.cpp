#include "pch.h"

#include "ClrClassLib.h"

namespace ClrClassLib {
	array<array<double>^>^ Class1::setAcc(const double val)
	{
		const auto vecPair = m_instance->totTime({CppNative::eVALUE::ACC, val});
		return makeArray<decltype(vecPair)>(std::move(vecPair));
	}

	array<array<double>^>^ Class1::setRet(const double val)
	{
		const auto vecPair = m_instance->totTime({ CppNative::eVALUE::RET, -val });
		return makeArray<decltype(vecPair)>(std::move(vecPair));
	}

	array<array<double>^>^ Class1::setDist(const double val)
	{
		const auto vecPair = m_instance->totTime({ CppNative::eVALUE::DIST, val });
		return makeArray<decltype(vecPair)>(std::move(vecPair));
	}

	array<array<double>^>^ Class1::setStart(const double val)
	{
		const auto vecPair = m_instance->totTime({ CppNative::eVALUE::V_START, val });
		return makeArray<decltype(vecPair)>(std::move(vecPair));
	}

	array<array<double>^>^ Class1::setCruise(const double val)
	{
		const auto vecPair = m_instance->totTime({ CppNative::eVALUE::V_CRUISE, val });
		return makeArray<decltype(vecPair)>(std::move(vecPair));
	}

	array<array<double>^>^ Class1::setEnd(const double val)
	{
		const auto vecPair = m_instance->totTime({ CppNative::eVALUE::V_END, val });
		return makeArray<decltype(vecPair)>(std::move(vecPair));
	}
}
