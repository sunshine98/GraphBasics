//
// Created by Administrator on 2017/12/30.
//

#ifndef GRAPHBASICS_SPARSEGRAPH_H
#define GRAPHBASICS_SPARSEGRAPH_H

#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
class DenseGraph{//构建稠密图类，使用邻接矩阵法表示
private:
    int n,m;//n为图的顶点数量，m为边的数量
    bool directed;//是否为有向图
    vector<vector<bool>> g;//构建二维数组g作为邻接表的结构基础，其存储类型为布尔类型
public:
    DenseGraph(int n,bool directed ){//构造函数
        this->n=n;
        this->directed=directed;
        this->m=0;
        for(int i=0;i<n;i++){
            g.push_back(vector<bool>(n, false));//初始化邻接表的关系全部为false，即各节点之间都不连接
        }
         }

    ~DenseGraph(){

    }

    int V(){//返回图中的顶点数量
        return n;
    }
    int E{//返回图中的边数量
            return m;
    };

    void addEdge(int v,int w){//在v节点和w节点之间建立连接关系
        assert(v>=0&&v<n);
        assert(w>=0&&w<n);//防止数组越界访问
        if(hasEdge(v,w)) return;//v节点存在到w节点的边，则不需要进行加边操作，直接返回即可
        g[v][w]= true;
        m++;//增加边的数量
        if(directed){//如果为有向图
           return;
        }
        else{//如果为无向图,则邻接图成对称关系，w节点到v节点之间也一定是存在连接的
            g[w][v]= true;
        }
    }

    bool hasEdge(int v,int w){//判断v节点到w节点之间是否已经存在边
        assert(v>=0&&v<n);//防止越界
        assert(w>=0&&w<n);
        return g[v][w];
    }







};
#endif //GRAPHBASICS_SPARSEGRAPH_H
