// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
	size_t sz;
	T* pMem;
public:
	TDynamicVector(size_t size = 1) : sz(size)
	{
		if (sz <= 0)
			throw out_of_range("Vector size should be greater than zero");
		if (sz > MAX_VECTOR_SIZE)
			throw out_of_range("This is too much");
		pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
	}
	TDynamicVector(T* arr, size_t s) : sz(s)
	{
		assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
		pMem = new T[sz];
		std::copy(arr, arr + sz, pMem);
	}
	TDynamicVector(const TDynamicVector& v)
	{
		if (v.pMem == nullptr) {
			sz = 0;
			pMem = nullptr;
		}
		else {
			sz = v.sz;
			pMem = new T[sz];
			std::copy(v.pMem, v.pMem + sz, pMem);
		}
	}
	TDynamicVector(TDynamicVector&& v)// noexcept
	{
		pMem = nullptr;
		swap(v, *this);
	}
	~TDynamicVector()
	{
		if (pMem != nullptr) {
			delete[]pMem;
			sz = 0;
		}
	}
	TDynamicVector& operator=(const TDynamicVector& v)
	{
		if (pMem != nullptr) {
			delete[]pMem;
			sz = 0;
		}
		if (v.pMem == nullptr) {
			sz = 0;
			pMem == nullptr;
		}
		else {
			sz = v.sz;
			pMem = new T[sz];
			std::copy(v.pMem, v.pMem + sz, pMem);
		}
		return *this;
	}
	TDynamicVector& operator=(TDynamicVector&& v)// noexcept
	{
		if (&v != this) {
			if (pMem != nullptr) {
				delete[]pMem;
				sz = 0;
			}
			sz = v.sz;
			pMem = v.pMem;
			v.sz = 0;
			v.pMem = nullptr;
		}
		else {
			throw "This is the same";
		}
		return *this;
	}

	size_t size() /*const noexcept*/ { return sz; }

	// индексация
	T& operator[](size_t ind)
	{
		if ((ind < 0) || (ind > sz)) {
			throw "out of range";
		}
		if (pMem == nullptr) {
			throw "It's empty";
		}
		return pMem[ind];
	}
	const T& operator[](size_t ind) const
	{
		if ((ind < 0) || (ind > sz)) {
			throw "out of range";
		}
		if (pMem == nullptr) {
			throw "It's empty";
		}
		return pMem[ind];
	}
	// индексация с контролем
	T& at(size_t ind)
	{
		if ((ind < 0) || (ind > sz)) {
			throw "out of range";
		}
		if (pMem == nullptr) {
			throw "It's empty";
		}
		return pMem[ind];
	}
	const T& at(size_t ind) const
	{
		if ((ind < 0) || (ind > sz)) {
			throw "out of range";
		}
		if (pMem == nullptr) {
			throw "It's empty";
		}
		return pMem[ind];
	}

	// сравнение
	bool operator==(const TDynamicVector& v)// const noexcept
	{
		if (sz != v.sz) {
			return false;
		}
		for (int i = 0; i < sz; i++) {
			if (pMem[i] != v.pMem[i]) {
				return false;
			}
		}
		return true;
	}
	bool operator!=(const TDynamicVector& v)// const noexcept
	{
		if (sz != v.sz) {
			return true;
		}
		for (int i = 0; i < sz; i++) {
			if (pMem[i] != v.pMem[i]) {
				return true;
			}
		}
		return false;
	}

	// скалярные операции
	TDynamicVector operator+(T val)
	{
		TDynamicVector tdv(*this);
		for (int i = 0; i < sz; i++) {
			tdv.pMem[i] += val;
		}
		return tdv;
	}
	TDynamicVector operator-(T val)
	{
		TDynamicVector tdv(*this);
		for (int i = 0; i < sz; i++) {
			tdv.pMem[i] -= val;
		}
		return tdv;
	}
	TDynamicVector operator*(T val)
	{
		TDynamicVector tdv(*this);
		for (int i = 0; i < sz; i++) {
			tdv.pMem[i] *= val;
		}
		return tdv;
	}

	// векторные операции
	TDynamicVector operator+(const TDynamicVector& v)
	{
		if (sz != v.sz) {
			throw "different sizes";
		}
		TDynamicVector tdv(*this);
		for (int i = 0; i < sz; i++) {
			tdv.pMem[i] += v.pMem[i];
		}
		return tdv;
	}
	TDynamicVector operator-(const TDynamicVector& v)
	{
		if (sz != v.sz) {
			throw "different sizes";
		}
		TDynamicVector tdv(*this);
		for (int i = 0; i < sz; i++) {
			tdv.pMem[i] -= v.pMem[i];
		}
		return tdv;

	}
	T operator*(const TDynamicVector& v)// noexcept(noexcept(T()))
	{
		if (sz != v.sz) {
			throw "different sizes";
		}
		T scalar = 0;
		for (int i = 0; i < sz; i++) {
			scalar += pMem[i] * v.pMem[i];
		}
		return scalar;
	}


	friend void swap(TDynamicVector& lhs, TDynamicVector& rhs)// noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.pMem, rhs.pMem);
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			istr >> v.pMem[i]; // требуется оператор>> для типа T
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
		return ostr;
	}
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
	using TDynamicVector<TDynamicVector<T>>::pMem;
	using TDynamicVector<TDynamicVector<T>>::sz;
public:
	using TDynamicVector<TDynamicVector<T>>::size;
	using TDynamicVector<TDynamicVector<T>>::at;
	TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
	{
		if (sz > MAX_MATRIX_SIZE)
			throw out_of_range("This is too much");
		for (size_t i = 0; i < sz; i++)
			pMem[i] = TDynamicVector<T>(sz);
	}

	using TDynamicVector<TDynamicVector<T>>::operator[];

	// сравнение
	bool operator==(const TDynamicMatrix& m) const //noexcept
	{
		if (sz != m.sz) {
			return false;
		}
		for (int i = 0; i < sz; i++) {
			if (pMem[i] != m.pMem[i]) {
				return false;
			}
		}
		return true;
	}

	// матрично-скалярные операции
	TDynamicMatrix operator*(const T& val)
	{
		TDynamicMatrix tdm(*this);
		for (int i = 0; i < sz; i++) {
			tdm.pMem[i] *= val;//check
		}
		return tdm;
		////////////////
	}

	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v)
	{
		if (sz != v.sz) {
			throw "different sizes";
		}
		TDynamicVector<T> tdv(v.sz);
		for (int i = 0; i < sz; i++) {
			for (int k = 0; k < sz; k++) {
				//tdv.pMem[i] += pMem[k] * m.pMem[k];
				tdv[i] = tdv[i] + pMem[i][k] + v[k];
			}
		}
		return tdv;
	}

	// матрично-матричные операции
	TDynamicMatrix operator+(const TDynamicMatrix& m)
	{
		if (sz != m.sz) {
			throw "different sizes";
		}
		TDynamicMatrix tdm(*this);
		for (int i = 0; i < sz; i++) {
			tdm.pMem[i] = pMem[i] + m.pMem[i];
		}
		return tdm;
		////////////////
	}
	TDynamicMatrix operator-(const TDynamicMatrix& m)
	{
		if (sz != m.sz) {
			throw "different sizes";
		}
		TDynamicMatrix tdm(*this);
		for (int i = 0; i < sz; i++) {
			tdm.pMem[i] = pMem[i] - m.pMem[i];//check
		}
		return tdm;
		////////////////
	}
	TDynamicMatrix operator*(const TDynamicMatrix& m)
	{
		TDynamicMatrix tdm(*this);
		for (int i = 0; i < m.sz; i++) {
			for (int j = 0; j < m.sz; j++) {
				for (int k = 0; k < m.sz; k++) {
					tdm.pMem[i][j] = tdm.pMem[i][j] + pMem[i][k] * m.pMem[k][j];
				}
			}
		}
		return tdm;
		////////////////
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicMatrix& m)
	{
		for (size_t i = 0; i < m.sz; i++)
			istr >> m.pMem[i];
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
	{
		for (size_t i = 0; i < m.sz; i++)
			ostr << m.pMem[i] << endl;
		return ostr;
	}
};

#endif
