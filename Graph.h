#pragma once

#include "Sort.h"
#include "DynamicArray.h"
#include "LinkQueue.h"
#include "Object.h"
#include "Exception.h"
#include "SharedPointer.h"

namespace data_structure
{
    template<typename E>
    struct Edge:public Object
    {
        int begin;
        int end;
        E data;

        Edge(int i = -1, int j = -1)
        {
            begin = i;
            end = j;
        }

        Edge(int i, int j, const E& value)
        {
            begin = i;
            end = j;
            data = value;
        }

        bool operator == (const Edge<E>& value)
        {
            return (value.begin == this->begin) && (value.end == this->end);
        }

        bool operator != (const Edge<E>& value)
        {
            return !(*this == value);
        }

        bool operator > (const Edge<E>& value)
        {
            return (this->data > value.data);
        }

        bool operator >= (const Edge<E>& value)
        {
            return !((*this) < value);
        }

        bool operator < (const Edge<E>& value)
        {
            return (this->data < value.data);
        }

        bool operator <= (const Edge<E>& value)
        {
            return !((*this) > value);
        }
    };

    template<typename V, typename E>
    class Graph:public Object
    {
        protected:
        SharedPointer< Array< Edge<E> > > getUndirectedEdges()
        {
            DynamicArray< Edge<E> >* ret = NULL;

            if(asUndirected())
            {
                LinkQueue< Edge<E> > queue;

                for(int i = 0; i < vCount(); i++)
                {
                    for(int j = 0; j < vCount(); j++)
                    {
                        if(isAdjacent(i, j))
                        {
                            queue.add(Edge<E>(i, j, getEdge(i, j)));
                        }
                    }
                }

                ret = queueToArray(queue);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "Prim operation is for undirection graph only ...");
            }

            return ret;
        }

        int find(Array<int>& p, int v)
        {
            while(p[v] != -1)
            {
                v = p[v];
            }

            return v;
        }
            
        public:
            virtual V getVertex(int i) = 0;
            virtual bool getVertex(int i, V& value) = 0;
            virtual bool setVertex(int i, const V& value) = 0;
            virtual SharedPointer< Array<int> > getAdjacent(int i) = 0;
            virtual E getEdge(int i, int j) = 0;
            virtual bool getEdge(int i, int j, E& value) = 0;
            virtual bool setEdge(int i, int j, const E& value) = 0;
            virtual bool removeEdge(int i, int j) = 0;
            virtual int vCount() = 0;
            virtual int eCount() = 0;
            virtual bool isAdjacent(int i, int j) = 0;
            virtual int OD(int i) = 0;
            virtual int ID(int i) = 0;
            virtual int TD(int i)
            {
                return ID(i) + OD(i);
            }

            bool asUndirected()
            {
                bool ret = true;

                for(int i = 0; i < vCount(); i++)
                {
                    for(int j = 0; j < vCount(); j++)
                    {
                        if(isAdjacent(i, j))
                        {
                            ret = (ret && isAdjacent(j, i) && (getEdge(i, j) == getEdge(j, i)));
                        }
                    }
                }

                return ret;
            }

            SharedPointer< Array< Edge<E> > > prim(const E& LIMIT)
            {
                LinkQueue< Edge<E> > ret;

                if(asUndirected())
                {
                    DynamicArray<int> adjVex(vCount());
                    DynamicArray<int> mark(vCount());
                    DynamicArray<int> cost(vCount());
                    SharedPointer< Array<int> > aj = NULL;
                    bool end = false;
                    int v = 0;

                    // 初始化数组
                    for(int i = 0; i < vCount(); i++)
                    {
                        adjVex[i] = -1;
                        mark[i] = false;
                        cost[i] = LIMIT;
                    }

                    // 标记第一个顶点，并将邻接顶点的权值和位置全部记录下来
                    mark[v] = true;
                    aj = getAdjacent(v);
                    for(int j = 0; j < aj->length(); j++)
                    {
                        cost[(*aj)[j]] = getEdge(v , (*aj)[j]);
                        adjVex[(*aj)[j]] = v;
                    }

                    for(int i = 0; (i < vCount()) && !end; i++)
                    {
                        E m = LIMIT;
                        int k = -1;

                        // 从邻接顶点中找到距离最近的
                        for(int j = 0; j < vCount(); j++)
                        {
                            if(!mark[j] && (cost[j] < m))
                            {
                                m = cost[j];
                                k = j;
                            }
                        }

                        end = (k == -1);
                        if(!end)
                        {
                            // 此处的adjVex[k]就是集合T中的顶点,k为集合F中的顶点
                            ret.add(Edge<E>(adjVex[k], k, getEdge(adjVex[k], k)));
                            // 标记k为集合T顶点
                            mark[k] = true;
                            // 获取k的邻接顶点，把所有的权值和顶点记录下来
                            aj = getAdjacent(k);
                            for(int j = 0; j < aj->length(); j++)
                            {
                                // 邻接顶点未被标记为集合T中,并且权值比记录的更小，此时才会更新权值和邻接顶点的点
                                if(!mark[(*aj)[j]] && (getEdge(k, (*aj)[j]) < cost[(*aj)[j]]))
                                {
                                    cost[(*aj)[j]] = getEdge(k, (*aj)[j]);
                                    adjVex[(*aj)[j]] = k;
                                }
                            }
                        }
                    }
                }
                else
                {
                    THROW_EXCEPTION(InvalidOperationException, "Prim operation is for undirection graph only ...");
                }

                if(ret.length() != (vCount() - 1))
                {
                    THROW_EXCEPTION(InvalidOperationException, "No enough edges from prim operation ...");
                }

                return  queueToArray(ret);
            }

            SharedPointer< Array< Edge<E> > > kruskal(const bool MINMUM = true)
            {
                LinkQueue< Edge<E> > ret;
                DynamicArray<int> pre(vCount());
                SharedPointer< Array< Edge<E> > > edges = getUndirectedEdges();
                
                // 初始化数组
                for(int i = 0; i < pre.length(); i++)
                {
                    pre[i] = -1;
                }

                // 希尔排序，由小到大
                Sort::Shell(*edges, MINMUM);

                for(int i = 0; (i < edges->length()) && (ret.length() < vCount() - 1); i++)
                {
                    // 查找最短边的
                    int begin = find(pre, (*edges)[i].begin);
                    int end = find(pre, (*edges)[i].end);

                    if(begin != end)
                    {
                        pre[end] = begin;
                        ret.add((*edges)[i]);
                    }
                }

                if(ret.length() != (vCount() -1))
                {
                    THROW_EXCEPTION(InvalidOperationException, "No enough edges from kruskal operation ...");
                }

                return  queueToArray(ret);
            }

            SharedPointer< Array<int> > dijkstra(int begin, int end, const E& LIMIT)
            {
                LinkQueue<int> ret;

                if((begin >= 0) && (begin < vCount()) && (end >= 0) && (end < vCount()))
                {
                    DynamicArray<E> dist(vCount());
                    DynamicArray<bool> mark(vCount());
                    DynamicArray<int> path(vCount());

                    // 初始化标记数组
                    for(int i = 0; i < mark.length(); i++)
                    {
                        mark[i] = false;
                        path[i] = -1;
                        // 将起始顶点对应的邻接顶点的距离进行记录
                        dist[i] = (isAdjacent(begin, i) ? (path[i] = begin, getEdge(begin, i)) : (LIMIT));
                    }
                    // 将起始顶点放入集合S中
                    mark[begin] = true;
                    

                    for(int i = 0; i < vCount(); i++)
                    {
                        E m = LIMIT;
                        int u = -1;

                        for(int j = 0; j < vCount(); j++)
                        {
                            if(!mark[j] && (dist[j] < m))
                            {   
                                m = dist[j];
                                u = j;
                            }
                        }

                        if(u == -1)
                        {
                            break;
                        }

                        mark[u] = true;

                        for(int j = 0; j < vCount(); j++)
                        {
                            if(!mark[j] && isAdjacent(u, j) && (dist[u] + getEdge(u, j) < dist[j]))
                            {   
                                dist[j] = dist[u] + getEdge(u, j);
                                path[j] = u;
                            }
                        }
                    }

                    LinkStack<int> s;
                    // 将终止顶点放入栈中
                    s.push(end);
                    for(int j = path[end]; j != -1; j = path[j])
                    {
                        s.push(j);
                    }

                    while (s.size() > 0)
                    {
                        ret.add(s.top());
                        s.pop();
                    }

                    if(ret.length() < 2)
                    {
                        THROW_EXCEPTION(ArithmeticException, "There is no path from begin to end ...")
                    }
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException, "Index i j  is invalid ...");
                }

                return queueToArray(ret);
            }

            template<typename T>
            static DynamicArray<T>* queueToArray(LinkQueue<T>& queue)
            {
                DynamicArray<T>* ret = new DynamicArray<T>(queue.length());
                if(ret)
                {
                    for(int i = 0; i < ret->length(); i++)
                    {
                        ret->set(i, queue.front());
                        queue.remove();
                    }
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No Memory to create ret object ...");
                }
                return ret;
            }

            SharedPointer< Array<int> > BFS(int i)
            {
                DynamicArray<int>* ret = NULL;

                if((i >= 0) && (i < vCount()))
                {
                    LinkQueue<int> q;
                    LinkQueue<int> r;
                    DynamicArray<bool> visited(vCount());

                    for(int j = 0; j < visited.length(); j++)
                    {
                        visited[i] = false;
                    }

                    q.add(i);

                    while(q.length() > 0)
                    {
                        int v = q.front();
                        q.remove();

                        if(!visited[v])
                        {
                            SharedPointer< Array<int> > adj = getAdjacent(v);
                            for(int j = 0; j < adj->length(); j++)
                            {
                                q.add((*adj)[j]);
                            }

                            visited.set(v, true);
                            r.add(v);
                        }
                    }
                    ret = queueToArray(r);
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
                }
                return ret;
            }

            SharedPointer< Array<int> > DFS(int i)
            {
                DynamicArray<int>* ret = NULL;

                if((i >= 0) && (i < vCount()))
                {
                    LinkStack<int> s;
                    LinkQueue<int> r;
                    DynamicArray<bool> visited(vCount());

                    for(int j = 0; j < visited.length(); j++)
                    {
                        visited[j] = false;
                    }

                    s.push(i);

                    while(s.size() > 0)
                    {
                        int v = s.top();
                        s.pop();

                        if(!visited[v])
                        {
                            SharedPointer< Array<int> > adj = getAdjacent(v);
                            for(int j = adj->length() - 1; j >= 0 ; j--)
                            {
                                s.push((*adj)[j]);
                            }
                            
                            r.add(v);
                            visited[v] = true;
                        }
                    }
                    ret = queueToArray(r);
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
                }

                return ret;
            }
    };

    template<typename V, typename E>
    void DFS(Graph<V,E>& g, int v, Array<bool>& visited, LinkQueue<int>& ret)
    {
        if((v >= 0) && (v < g.vCount()))
        {
            ret.add(v);
            visited[v] = true;
            SharedPointer< Array<int> > adj = g.getAdjacent(v);

            for(int i = 0; i < adj->length(); i++)
            {
                if(!visited[(*adj)[i]])
                {
                    DFS(g, (*adj)[i], visited, ret);
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Vertex v is invalid ...");
        }
    }

    template<typename V, typename E>
    SharedPointer< Array<int> > DFS(Graph<V,E>& g, int v)
    {
        DynamicArray<int>* ret = NULL;
        DynamicArray<bool> visited(g.vCount());
        LinkQueue<int> queue;

        for(int i = 0; i < visited.length(); i++)
        {
            visited[i] = false;
        }

        DFS(g, v, visited, queue);
        ret = g.queueToArray(queue);

        return ret;
    }


}