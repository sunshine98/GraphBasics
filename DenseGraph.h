//
// Created by Administrator on 2017/12/30.
//

#ifndef GRAPHBASICS_DENSEGRAPH_H
#define GRAPHBASICS_DENSEGRAPH_H

#include <cassert>
#include <iostream>
#include <vector>
#include "Edge.h"

using namespace std;

template<typename Weight>
class DenseGraph {//构建稠密图类，使用邻接矩阵法表示
private:
    int n, m;//n为图的顶点数量，m为边的数量
    bool directed;//是否为有向图
    vector<vector<Edge<Weight> *>> g;//构建二维数组g作为邻接表的结构基础，其存储类型为布尔类型
public:
    DenseGraph(int n, bool directed) {//构造函数
        this->n = n;
        this->directed = directed;
        this->m = 0;
        //下面为初始化n*n的矩阵，每一个g[i][j]指向一个Edge，即一条边的信息
        g = vector<vector<Edge<Weight> *>>(n, vector<Edge<Weight> *>(n, NULL));

    }

    ~DenseGraph() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                delete g[i][j];
            }
        }
    }

    int V() {//返回图中的顶点数量
        return n;
    };

    int E() {//返回图中的边数量
        return m;
    };

    void addEdge(int v, int w, Weight weight) {//在v节点和w节点之间建立连接关系
        assert(v >= 0 && v < n);
        assert(w >= 0 && w < n);//防止数组越界访问
        if (hasEdge(v, w)) {//若重复连边，则进行替换操作，删除原来的边信息，重置边信息
            delete g[v][w];
            if (v != w && !directed) {//如果为无向图，则另一对边信息也需要删除
                delete[] g[w][v];
            }
            m--;
        }
        //添加一个新边
        g[v][w] = new Edge<Weight>(v, w, weight);
        //如果是无向图的话另一条边也要加上去
        if (v != w && !directed) {
            g[w][v] = new Edge<Weight>(w, v, weight);
        }
        m++;

    }

    bool hasEdge(int v, int w) {//判断v节点到w节点之间是否已经存在边
        assert(v >= 0 && v < n);//防止越界
        assert(w >= 0 && w < n);
        return g[v][w] != NULL;
    }

    void show() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (g[i][j]) {//g[i][j]存在着边
                    cout << g[i][j]->wt() << "\t";
                } else {
                    cout << "NULL\t";
                }
            }
        }
    }

    class adjIterator {//构建稠密图的相邻节点迭代器
    private:
        DenseGraph &G;//需要进行操作的图的引用
        int v;//需要遍历的节点
        int index;//index指向迭代器正在访问的元素

    public:
        adjIterator(DenseGraph &graph, int v) : G(graph) {//生成一个迭代器的构造函数
            assert(v >= 0 && v < G.n);
            this->index = -1;
            this->v = v;
        }

        ~adjIterator() {};

//因为邻接矩阵结构的特殊性，即邻接矩阵中的一个节点其关联链表中的元素并不是都有效
        //必须值为true才有效，因此并不能保证直接从第一个元素开始访问，所以index初始化为-1
        Edge<Weight> *begin() {
            index = -1;
            return next();
        }

        Edge<Weight> *next() {
            for (index += 1; index < G.V(); index++) {
                if (G.g[v][index] == true) {//只把真正有效的元素返回出去
                    return G.g[v][index];
                }
            }
            return NULL;
        }

        bool end() {
            return index >= G.V();//判断是否遍历完成
        }

    };


};

#endif //GRAPHBASICS_DENSEGRAPH_H
