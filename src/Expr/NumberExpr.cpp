#include "NumberExpr.hpp"
#include "VisitorExpr.hpp"
#include <iostream>

template <class T>
NumberExpr<T>::NumberExpr(T number, SourceSector position) : Expr(position),
                                                              number(number)
{
}

template <class T>
void NumberExpr<T>::visit(VisitorExpr *visitor)
{
    visitor->visitNumber(this);
}

template <class T>
T NumberExpr<T>::get_number()
{
    return number;
}

//template class NumberExpr<uint8_t>;
//template class NumberExpr<uint16_t>;
//template class NumberExpr<uint32_t>;
template class NumberExpr<uint64_t>;

//template class NumberExpr<int8_t>;
//template class NumberExpr<int16_t>;
//template class NumberExpr<int32_t>;
template class NumberExpr<int64_t>;

template class NumberExpr<float>;
//template class NumberExpr<double>;