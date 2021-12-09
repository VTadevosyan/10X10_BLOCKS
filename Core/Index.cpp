/// 10 X 10

/**
  * @file Core/Index.cpp
 **/

#include "Core/Index.hpp"

#include <qdebug.h>

namespace Core {

Index Index::posToIndex(const QPointF& p, int w, int h) noexcept
{
    return Index(p.y() / h, p.x() / w);
}

bool Index::operator< (const Index& i) const noexcept
{
    if (m_row < i.m_row) {
        return true;
    } else if (m_row == i.m_row) {
        return m_col < i.m_col;
    }
    return false;
}

Index::Index(int r, int c)
    : m_row(r)
    , m_col(c)
{

}

Index::Index()
    : m_row(-1)
    , m_col(-1)
{

}

int Index::row() const noexcept
{
    return m_row;
}

int Index::column() const noexcept
{
    return m_col;
}

bool Index::isValid() const noexcept
{
    return (m_row >= 0 && m_row < 10) && (m_col >= 0 && m_col < 10);
}

} /// Core namespace
