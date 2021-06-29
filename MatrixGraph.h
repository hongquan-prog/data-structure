#pragma once

#include "Graph.h"
#include "DynamicArray.h"

namespace data_structure
{
    template <int N, typename V, typename E>
    class MatrixGraph:public Graph<V, E>
    {
    protected:
        V* m_vertexes[N];
        E* m_edge[N][N];
        int m_eCount;

    public:

        MatrixGraph():m_eCount(0)
        {
            for(int i = 0; i < vCount(); i++)
            {
                m_vertexes[i] = NULL;
                for(int j = 0; j < vCount(); j++)
                {
                    m_edge[i][j] = NULL;
                }
            }
        }

        // O(1)
        V getVertex(int i)
        {
            V ret;

            if(!getVertex(i, ret))
            {
                THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
            }

            return ret;
        }

        // O(1)
        bool getVertex(int i, V& value)
        {
            int ret = ((0 <= i) && (i < vCount()));

            if(ret)
            {
                if(m_vertexes[i])
                {
                    value = *(m_vertexes[i]);
                }
                else
                {
                    THROW_EXCEPTION(InvalidOperationException, "No value assigned to this vertex ...");
                }
            }

            return ret;
        }

        // O(1)
        bool setVertex(int i, const V& value)
        {
            int ret = ((0 <= i) && (i < vCount()));

            if(ret)
            {
                V* data = m_vertexes[i];
                if(NULL == data)
                {
                    data = new V();
                }
                if(data)
                {
                    *data = value;
                    m_vertexes[i] = data;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No memory to store new vertex value ...");
                }
            }
            return ret;
        }

        // O(n)
        SharedPointer< Array<int> > getAdjacent(int i)
        {
            DynamicArray<int>* ret;

            if((0 <= i) && (i < vCount()))
            {
                int n = 0;

                for(int j = 0; j < vCount(); j++)
                {
                    if(m_edge[i][j])
                    {
                        n++;
                    }
                }

                ret = new DynamicArray<int>(n);
                if(ret)
                {   
                    for(int j = 0, n = 0; j < vCount(); j++, n++)
                    {
                        if(m_edge[i][j])
                        {
                            (*ret)[n] = j;
                        }
                    }
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create ret object ...");
                }
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
            }

            return ret;
        }

        // O(1)
        E getEdge(int i, int j)
        {
            E ret;

            if(!getEdge(i, j, ret))
            {
                THROW_EXCEPTION(InvalidParameterException, "Index i or j is invalid ...");
            }

            return ret;
        }

        // O(1)
        bool getEdge(int i, int j, E& value)
        {
            bool ret = ((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()));

            if(ret)
            {
                if(m_edge[i][j])
                {
                    value = *(m_edge[i][j]);
                }
                else
                {
                    THROW_EXCEPTION(InvalidOperationException, "Edge is not exist ...");
                }
            }

            return ret;
        }

        // O(1)
        bool setEdge(int i, int j, const E& value)
        {
            bool ret = ((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()));

            if(ret)
            {
                E* edge = m_edge[i][j];
                if(m_edge[i][j])
                {
                    *edge = value;
                }
                else
                {
                    edge = new E();
                    if(edge)
                    {
                        *edge = value;
                        m_edge[i][j] = edge;
                        m_eCount++;
                    }
                    else
                    {
                        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to store edge value ...");
                    }
                }
            }

            return ret;
        }

        // O(1)
        bool removeEdge(int i, int j)
        {
            bool ret = ((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()));

            if(ret)
            {
                E* edge = m_edge[i][j];
                m_edge[i][j] = NULL;
                if(edge)
                {
                    m_eCount--;
                    delete edge;
                }
            }

            return ret;
        }

        // O(1)
        int vCount()
        {
            return N;
        }

        // O(1)
        int eCount()
        {
            return m_eCount;
        }

        bool isAdjacent(int i, int j)
        {
            bool ret = ((i >= 0) && (i < vCount()) && (j >= 0) && (j < vCount()));
            
            if(ret)
            {
                ret = (m_edge[i][j] != NULL);
            }

            return ret;
        }

        // O(n)
        int OD(int i)
        {
            int ret = 0;

            if((0 <= i) && (i < vCount()))
            {
                ret = 0;
                for(int j = 0; j < vCount(); j++)
                {
                    if(m_edge[i][j])
                    {
                        ret++;
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
            }

            return ret;
        }

        // O(n)
        int ID(int i)
        {
            int ret = 0;

            if((0 <= i) && (i < vCount()))
            {
                for(int j = 0; j < vCount(); j++)
                {
                    if(m_edge[j][i])
                    {
                        ret++;
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
            }

            return ret;
        }

        ~MatrixGraph()
        {
            for(int i = 0; i < vCount(); i++)
            {
                for(int j = 0; j < vCount(); j++)
                {
                    delete m_edge[i][j];
                }
                delete m_vertexes[i];
            }
        }
    };
}