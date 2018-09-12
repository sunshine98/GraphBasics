//
// Created by Administrator on 2018/9/9.
//

#ifndef GRAPHBASICS_CONPONENT_H
#define GRAPHBASICS_CONPONENT_H

#include <iostream>
#include <cassert>

using namespace std;

template<typename Graph>
class ComPonent {//ComPonent为一个计算图联通分量有关的类
private:
    Graph &G;//接受需要检测的图
    bool *visited;//visited数组用来记录节点是否被访问过
    int ccount;//记录联通分量的个数
    int *id;//id数组记录每个节点所在的联通分量的编号

    void dfs(int v) {//dfs主函数
        visited[v] = true;
        id[v] = ccount;//给节点分配上相对应的联通分量的序号
        typename Graph::adjIterator adj(G, v);
        for (int i = adj.begin(); !adj.end(); i = adj.next()) {//遍历节点的所有邻节点，并对其使用dfs深度算法
            if (!visited[i]) {
                dfs(i);
            }
        }
    }

public:

    ComPonent(Graph &graph) : G(graph) {

        visited = new bool[G.V()];
        id = new int[G.V()];
        ccount = 0;
        for (int i = 0; i < G.V(); i++) {//初始化visited数组，使所有的节点都为未访问状态
            visited[i] = false;
            id[i] = -1;//初始化所有节点的联通分量编号为-1
        }
        for (int i = 0; i < G.V(); i++) {//对所有节点进行dfs操作
            if (!visited[i]) {
                dfs(i);
                ccount++;
            }
        }

    }

    ~ComPonent() {
        delete[] visited;
        delete[] id;
    }

    int count() {//返回图中含有的联通分量的个数
        return ccount;
    }

    bool isConnect(int v, int w) {//判断两个节点是否处于同一个联通分量上
        return id[v] == id[w];
    }

};

#endif //GRAPHBASICS_CONPONENT_H
