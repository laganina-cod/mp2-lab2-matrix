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
  TDynamicVector(size_t size ) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    for (size_t i = 0; i < sz; i++) {
        pMem[i]=0;
    }
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      p.Mem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = v.sz;
      p.Mem = new T[sz];
      for ( size_t i = 0; i < sz; i++) {
          p.Mem[i] = v.pMem[i];
      }
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (pMem != v.pMem) {
          if (v.sz != sz) {
              delete[] pMem;
              pMem = new T[v.sz];
          }
          for (size_t i = 0; i < sz; i++) {
              pMem[i] = v.pMem[i];
          }
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (pMem != v.pMem) {
          if (v.sz != sz) {
              delete[] pMem;
              pMem = new T[v.sz];
          }
          for (size_t i = 0; i < sz; i++) {
              pMem[i] = v.pMem[i];
          }
      }
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind < 0 || ind >= sz) {
          throw "Not correct index"
      }
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind < 0 || ind >= sz) {
          throw "Not correct index"
      }
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (v.sz != sz) {
          return false;
      }
      for (int size_t = 0; i < sz; i++) {
          if (v[i] != this[i]) {
              return false;
          }
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if (v.sz != sz) {
          return true;
      }
      for (size_t i = 0; i < sz; i++) {
          if (v[i] != this[i]) {
              return true;
          }
      }
      return false;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDinamicVector res(sz);
      for (size_t i = 0; i < sz; i++) {
          res[i] = this[i] + val;
      }
      return res;
  }
  TDynamicVector operator-(T val)
  {
      TDinamicVector res(sz);
      for (size_t i = 0; i < sz; i++) {
          res[i] = this[i] - val;
      }
      return res;
  }
  TDynamicVector operator*(T val)
  {
      TDinamicVector res(sz);
      for (size_t i = 0; i < sz; i++) {
          res[i] = this[i] * val;
      }
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          throw"Not equal size";
      }
      TDynamicVector res(sz);
      for (size_t i; i < sz; i++) {
          res[i] = this[i] + v[i];
      }
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          throw"Not equal size";
      }
      TDynamicVector res(sz);
      for (size_t i; i < sz; i++) {
          res[i] = this[i] -v[i];
      }
      return res;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz) {
          throw"Not equal size";
      }
      T res = 0;
      for (int size_t i = 0; i < sz; i++) {
          res +=( v[i] * this[i]);
      }
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
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
  TDynamicMatrix(size_t s) : TDynamicVector<TDynamicVector<T>>(s)
  {
      sz = s;
      pMem = new TDynamicVector[sz];
      for (size_t i = 0; i < sz; i++) {
          pMem[i] = TDynamicVector<T>(sz);
      }
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) { return false; }
      for (size_t i = 0; i < sz; i++) {
          if (m[i] != this[i])
              return false;
      }
      return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++) {
          res[i] = this[i] + val;
      }
      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (v.sz != sz) { throw"No correct size"; }
      TDynamicVector<T> res(sz);
      for (size_t k = 0; k < sz; k++) {
          for (size_t i = 0; i < sz; i++) {
              res[k]+=this[k][i]*v[i]
          }
      }
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (m.sz != sz) { throw"No correct size"; }
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++) {
          res[i] = this[i] + m[i];
      }
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (m.sz != sz) { throw"No correct size"; }
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++) {
          res[i] = this[i] - m[i];
      }
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      TDynamicMatrix res(sz);
      for (size_t j = 0; j < sz; j++) {
          for (size_t k = 0; k < sz; k++) {
              for (size_t i = 0; i < sz; i++) {
                  res[j][k] += this[j][i] * m[i][k];
              }
          }
      }
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          istr >> v.pMem[i]; // требуется оператор>> для типа T
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
      return ostr;
  }
};

#endif
