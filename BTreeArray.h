//
// Created by lhq on 2022/2/17.
//

#ifndef BTREEARRAY_H
#define BTREEARRAY_H

#include "BTree.h"
#include "RangeArray.h"

namespace data_structure
{
    template <typename T>
    class BTreeArray : public Array<T>
    {
    private:
        RangeArray<T> m_value;
        RangeArray<bool> m_mark;
        int m_height;

    public:
        BTreeArray(int height)
            : m_value(1, (1 << height) - 1), m_mark(1, (1 << height) - 1), m_height(height)
        {
            for (int i = m_value.lower(); i <= m_value.upper(); i++)
            {
                m_mark[i] = false;
            }

            this->m_array = NULL;
        }

        BTreeArray(const BTreeArray &tree)
            : m_value(tree.m_value), m_mark(tree.m_mark), m_height(tree.height)
        {
            this->m_array = NULL;
        }

        virtual bool set(int i, const T &value)
        {
            bool tmp;
            bool ret = m_mark.get(i, tmp);

            if (ret && ((m_mark.lower() <= i) && (i <= m_mark.upper())))
            {
                m_mark[i] = true;
                m_value[i] = value;
                ret = true;
            }

            return ret;
        }

        virtual bool get(int i, T &value)
        {
            bool exist;
            bool ret = m_mark.get(i, exist);

            if (ret && exist)
            {
                m_value.get(i, value);
            }

            return ret;
        }

        void remove(int i)
        {
            if ((m_mark.lower() <= i) && (i <= m_mark.upper()))
            {
                m_mark[i] = false;
                remove(left(i));
                remove(right(i));
            }
        }

        T &operator[](int i)
        {
            if (m_mark[i])
            {
                return m_value[i];
            }
            else
            {
                THROW_EXCEPTION(IndexOutofBoundsException, "[] failed!");
            }
        }

        T operator[](int i) const
        {
            return const_cast<BTreeArray<T> &>(*this)[i];
        }

        virtual int length(void) const
        {
            return (1 << m_height) - 1;
        }

        int height() const
        {
            return m_height;
        }

        int count() const
        {
            int ret = 0;

            for (int i = m_mark.lower(); i <= m_mark.upper(); i++)
            {
                if (m_mark[i])
                {
                    ret++;
                }
            }

            return ret;
        }

        int left(int i) const
        {
            return 2 * i;
        }

        int right(int i) const
        {
            return 2 * i + 1;
        }

        int parent(int i) const
        {
            return i >> 1;
        }

        bool isNull(int i) const
        {
            return !((m_mark.lower() <= i) && (i <= m_mark.upper()) && (m_mark[i]));
        }

        void resize(int height)
        {
            int len = (1 << height) - 1;
            RangeArray<T> mark(1, len);
            RangeArray<T> value(1, len);
            len = (len < length()) ? (len) : (length());

            for (int i = 1; i <= len; i++)
            {
                mark[i] = m_mark[i];
                value[i] = m_value[i];
            }

            for (int i = len + 1; i <= mark.upper(); i++)
            {
                mark[i] = false;
            }

            m_mark = mark;
            m_value = value;
            m_height = height;
        }

        int find(const T &value) const
        {
            int ret = -1;

            for (int i = m_mark.lower(); i <= m_mark.upper(); i++)
            {
                if (m_mark[i] && m_value[i] == value)
                {
                    ret = i;
                    break;
                }
            }

            return ret;
        }

        void clear()
        {
            remove(1);
        }
    };
}

#endif // DATA_STRUCTURE_BTREEARRAY_H
