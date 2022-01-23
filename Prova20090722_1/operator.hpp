#pragma once
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

// ===============================================================================
// Nel namespace myVectAlgebra potremmo ridefinire gli operatori matematici che coinvolgono
// vettori e scalari
// ===============================================================================

// somma di due vettori : somma componente per componente

template <typename T> std::vector<T> operator+(const std::vector<T> &a, const std::vector<T> &b) {
    assert(a.size() == b.size());  
    std::vector<T> result(a.size());
    for (int i = 0; i < static_cast<int>(a.size()); i++) result[i] = a[i] + b[i];
    return result;
}

// differenza di due vettori componente per componente
// [ preferisco re-implementarlo perche' si fanno meno operazioni rispetto result = a + (-1.*b) ]

template <typename T> std::vector<T> operator-(const std::vector<T> &a, const std::vector<T> &b) {
    assert(a.size() == b.size());  
    std::vector<T> result(a.size());
    for (int i = 0; i < static_cast<int>(a.size()); i++) result[i] = a[i] - b[i];    
    return result;
}

// ===============================================================================  
// prodotto scalare tra due vettori 
// ===============================================================================

template <typename T> T operator*(const std::vector<T> &a, const vector<T> &b) {
  
assert(a.size() == b.size());  
    T sum = 0 ;
    for (int i = 0; i < static_cast<int>(a.size()); i++) sum += a[i] * b[i];
    return sum;
}

// ===============================================================================
// prodotto tra uno scalare e un vettore
// ===============================================================================

template <typename T> std::vector<T> operator*( T c , const std::vector<T> &a) {
    std::vector<T> result(a.size());
    for (int i = 0; i < static_cast<int>(a.size()); i++) result[i] = c * a[i];
    return result;  
}

// ===============================================================================
// prodotto tra un vettore e uno scalare 
// ===============================================================================

template <typename T> std::vector<T> operator*( const std::vector<T> &a , T c) {
    std::vector<T> result(a.size());
    for (int i = 0; i < static_cast<int>(a.size()); i++) result[i] = c * a[i];
    return result;  
}

// ===============================================================================
// divisione tra un vettore e uno scalare 
// ===============================================================================

template <typename T> std::vector<T> operator/( const std::vector<T> &a , T c) {
    std::vector<T> result(a.size());
    for (int i = 0; i < static_cast<int>(a.size()); i++) result[i] = a[i] / c ;
    return result;  
}

// ===============================================================================
// somma ad a un vettore b e il risultato viene messo in a
// ===============================================================================

template <typename T> std::vector<T>& operator+=(std::vector<T>& a, const std::vector<T>& b) {
    assert(a.size() == b.size());  
    for (int i = 0; i < static_cast<int>(a.size()); i++) a[i] += b[i];
    return a;
}

// ===============================================================================
// sottrai ad a un vettore b e il risultato viene messo in a
// ===============================================================================

template <typename T> std::vector<T>& operator-=(std::vector<T>& a, const std::vector<T>& b) {
    assert(a.size() == b.size());  
    for (int i = 0; i < static_cast<int>(a.size()); i++) a[i] -= b[i];
    return a;
}
