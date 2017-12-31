//
// Created by Administrator on 2017/12/30.
//

#ifndef GRAPHBASICS_SPARSEGRAPH_H
#define GRAPHBASICS_SPARSEGRAPH_H

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;
class SparseGraph{//构建稀疏图，并使用邻接表结构
private:
    int n,m;//n为图的节点数量,m为图的边数量
    bool directed;//表示图是否为有向图
    vector<vector<int>> g;//使用二维数组来表示邻接表,且数据类型为int类型
public:
    SparseGraph(int n, bool directed){//稀疏图的构造函数
        this->n=n;
        this->m=0;
        this->directed=directed;
        for(int i=0;i<n;i++){
            g.push_back(vector<int>());
        }
    }
    ~SparseGraph(){

    }

    int V(){//返回图中节点的数量
        return n;
    }

    int E(){//返回图中边的数量
        return m;
    }
    //在v与w节点之间加上一条边
    void addEdge(int v,int w){
        assert(v>=0&&v<n);
        assert(w>=0&&w<n);//防止越界
        g[v].push_back(w);//在v的邻接表中加入w节点
        if(v!=w&&!directed) g[w].push_back(v);//v与w不是同一个节点且图不是有向图，才需要执行改该步骤
        m++;
    }

    bool hasEdege(int v,int w) {//判断v节点与w节点之间是否存在边
        assert(v>=0&&v<n);
        assert(w>=0&&w<n);
        for(int i=0;i<g[v].size();i++){//遍历与v节点相连的节点
            if(g[v][i]==w) return true;//如果在邻接串中发现其中某一个节点与w节点相同，则表明v节点与w节点之间已经存在边
        }
        return false;
    }


};
#endif //GRAPHBASICS_SPARSEGRAPH_H
