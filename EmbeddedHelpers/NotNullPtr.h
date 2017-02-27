#pragma once
#include <stdexcept>

template<typename T>
class NotNullPtr final
{
public:
	explicit NotNullPtr(T* pT) :
		pT_(pT)
	{
		if (pT == nullptr)
			throw std::invalid_argument("Parameter must be not null");
	}

	operator T*() const { return pT_; }
	T& operator *() { return *pT_; }
	T* operator ->() const { return pT_; }

private:
	T* pT_;
};
