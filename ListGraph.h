#pragma once

#include "Graph.h"
#include "LinkList.h"

namespace data_structure
{
    template <typename V, typename E>
    class ListGraph:public Graph<V, E>
    {
    protected:
        struct Vertex:public Object
        {
            V* data;
            LinkList< Edge<E> > edge;

            Vertex()
            {
                data = NULL;
            }
        };

        LinkList< Vertex* > m_list;
        
    public:
        ListGraph(unsigned int n)
        {
            for(unsigned int i = 0; i < n; i++)
            {
                addVertex();
            }
        }

        // O(n)
        int addVertex()
        {
            int ret = -1;

            Vertex* v = new Vertex();
            if(v)
            {
                m_list.insert(v);
                ret = m_list.length() - 1;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create new vertex object ...")
            }

            return ret;
        }

        // O(n)
        int addVertex(const V& value)
        {
            int ret = addVertex();

            if(ret >= 0)
            {
                setVertex(ret, value);
            }

            return ret;
        }

        // O(n)
        bool setVertex(int i, const V& value)
        {
            bool ret = ((0 <= i) && (i < vCount()));

            if(ret)
            {
                Vertex* vertex = m_list.get(i);
                V* data = vertex->data;

                if(data == NULL)
                {
                    data = new V();
                }
                
                if(data)
                {
                    *data = value;
                    vertex->data = data;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create new vertex value");
                }
            }

            return ret;
        }
        
        // O(n)
        V getVertex(int i)
        {
            V ret;

            if(!getVertex(i, ret))
            {
                THROW_EXCEPTION(IndexOutofBoundsException, "Index i is invalid ...");
            }

            return ret;
        }

        // O(n)
        bool getVertex(int i, V& value)
        {
            bool ret = (0 <= i) && (i < vCount());

            if(ret)
            {
                Vertex* vertex = m_list.get(i);
                if(vertex->data)
                {
                    value = *(vertex->data);
                }
                else
                {
                    THROW_EXCEPTION(InvalidOperationException, "No value assigned to this vertex ...");
                }
            }

            return ret;
        }

        // O(n^2)
        void removeVertex()
        {
            if(m_list.length() > 0)
            {
                int index = m_list.length() - 1;
                Vertex* vertex = m_list.get(index);

                if(m_list.remove(index))
                {
                    for(int i = (m_list.move(0), 0); !m_list.end(); m_list.next(), i++)
                    {
                        int pos = m_list.current()->edge.find(Edge<E>(i, index));
                        if(pos >= 0)
                        {
                            m_list.current()->edge.remove(pos);
                        }
                    }
                    delete vertex->data;
                    delete vertex;
                }
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "N0 vertex in current graph ...");
            }

        }

        // O(n)
        SharedPointer< Array<int> > getAdjacent(int i)
        {
            DynamicArray<int>* ret;

            if((0 <= i) && (i < vCount()))
            {
                Vertex* vertex = m_list.get(i);
                ret = new DynamicArray<int>(vertex->edge.length());

                if(ret)
                {
                    for(int j =  (vertex->edge.move(0), 0); !(vertex->edge.end()); j++, vertex->edge.next())
                    {
                        ret->set(j, vertex->edge.current().end);
                    }
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create Array ...")
                }
            }

            return ret;
        }

        // O(n)
        bool getEdge(int i, int j, E& value)
        {
            bool ret = ((i >= 0) && (i < vCount()) &&  (j >= 0) && (j < vCount()));
            if(ret)
            {
                Vertex* vertex = m_list.get(i);
                
                int pos = vertex->edge.find(Edge<E>(i, j));
                if(pos >= 0)
                {
                    value = vertex->edge.get(pos).data;
                }
                else
                {
                    THROW_EXCEPTION(InvalidOperationException, "No value assigned to this edge ...");
                }
            }
            return ret;
        }

        // O(n)
        E getEdge(int i, int j)
        {
            E ret;

            if(!getEdge(i, j, ret))
            {
                THROW_EXCEPTION(IndexOutofBoundsException, "Index i or j is invalid ...");
            }

            return ret;
        }

        // O(n)
        bool setEdge(int i, int j, const E& value)
        {
            int ret = ((i >= 0) && (i < vCount()) &&  (j >= 0) && (j < vCount()));
            
            if(ret)
            {
                Vertex* vertex = m_list.get(i);
                int pos =  vertex->edge.find(Edge<E>(i, j));
                if(pos >= 0)
                {
                    vertex->edge.set(pos, Edge<E>(i, j, value));
                }
                else
                {
                    vertex->edge.insert(Edge<E>(i, j, value));
                }
            }

            return ret;
        }

        // O(n)
        bool removeEdge(int i, int j)
        {
            int ret = ((i >= 0) && (i < vCount()) &&  (j >= 0) && (j < vCount()));
            
            if(ret)
            {
                Vertex* vertex = m_list.get(i);
                int pos =  vertex->edge.find(Edge<E>(i, j));
                if(pos >= 0)
                {
                    vertex->edge.remove(pos);
                }
            }

            return ret;
        }

        // O(1)
        int vCount()
        {
            return m_list.length();
        }

        // O(n)
        int eCount()
        {
            int ret = 0;

            for(m_list.move(0); !m_list.end(); m_list.next())
            {
                ret+= m_list.current()->edge.length();
            }

            return ret;
        }

        bool isAdjacent(int i, int j)
        {
            bool ret = ((i >= 0) && (i < vCount()) && (j >= 0) && (j < vCount()));
            
            if(ret)
            {
                Vertex* vertex = m_list.get(i);
                ret = (vertex->edge.find(Edge<E>(i, j)) >= 0);
            }

            return ret;
        }

        // O(n^2)
        int ID(int i = 0)
        {
            int ret = 0;

            if((i >= 0) && (i < vCount()))
            {
                for(int j = (m_list.move(0), 0); !m_list.end(); j++, m_list.next())
                {
                    if(m_list.current()->edge.find(Edge<E>(j, i)) >= 0)
                    {
                        ret++;
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(IndexOutofBoundsException, "Index i is invalid ...");
            }

            return ret;
        }

        // O(n)
        int OD(int i = 0)
        {
            int ret = 0;

            if((i >= 0) && (i < vCount()))
            {
                ret = m_list.get(i)->edge.length();
            }
            else
            {
                THROW_EXCEPTION(IndexOutofBoundsException, "Index i is invalid ...");
            }

            return ret;
        }


        ~ListGraph()
        {
            while(m_list.length() > 0)
            {
                Vertex* toDel = m_list.get(0);
                m_list.remove(0);
                delete toDel;
                delete toDel->data;
            }
        }
    };
    
}