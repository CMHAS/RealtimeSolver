#pragma once
#include "CalcTime.h"

using namespace System;
using namespace System::Diagnostics;

namespace ClrClassLib {
	
	template<class T>
	public ref class MyObject
	{
	protected:
		T* m_instance;
	public:
		MyObject() { m_instance = new T; }
		virtual ~MyObject() { this->!MyObject(); }
		!MyObject() {
			if (m_instance != nullptr) {
				delete m_instance;
			}
		}
	};

	public ref class Class1 : MyObject<CppNative::CalcTime>
	{
		template<typename T>
		array<array<double>^>^ makeArray(T&& vec);
	public:
		~Class1() { m_instance->~CalcTime(); }
		array<array<double>^>^ setAcc(const double val);
		array<array<double>^>^ setRet(const double val);
		array<array<double>^>^ setDist(const double val);
		array<array<double>^>^ setStart(const double val);
		array<array<double>^>^ setCruise(const double val);
		array<array<double>^>^ setEnd(const double val);

	};

	template<typename T>
	inline array<array<double>^>^ Class1::makeArray(T&& vec)
	{
		array<array<double>^>^ arr = gcnew array<array<double>^>(static_cast<int>(vec.size()));
		int i{0};
		for (const auto& [time, vel] : vec) {
			arr[i++] = gcnew array<double>{ time, vel };
		}
		return arr;
	}
}
