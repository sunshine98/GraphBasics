//
// Created by Administrator on 2018/9/12.
//

#ifndef GRAPHBASICS_SHORTPATH_H
#define GRAPHBASICS_SHORTPATH_H

#include <iostream>
#include <cassert>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

template<typename Graph>
class shortPath {
private:
    Graph &G;//接受需要检测的图
    bool *visited;//visited数组用来记录节点是否被访问过
    int s;//s为source的意思。即需要寻路的源（起始）节点
    int *ord;//ord为一个记录各节点到原点之间距离的数组
    int *from;//数组用来记录每个节点的上一个节点编号
public:
    shortPath(Graph &G, int s) : G(G), s(s) {
        assert(s >= 0 && s < G.V());
        //构造辅助数组
        visited = new bool[G.V()];
        ord = new int[G.V()];
        from = new int[G.V()];
        //初始化辅助数组
        for (int i = 0; i < G.V(); i++) {
            visited[i] = false;
            ord[i] = -1;
            from[i] = -1;
        }

        //层序遍历关键代码
        queue<int> q;//准备层序遍历关键工具——辅助队列
        //初始化基础数据
        q.push(s);//源点先入列
        visited[s] = true;//只要入列的节点visited状态就标记为true
        ord[s] = 0;//源点到源点的距离为0
        //利用循环补充剩下的数据
        while (!q.empty()) {
            int v = q.front();//获取队列首元素
            typename Graph::adjIterator adj(G, v);//获取v节点的所有邻节点的迭代器
            //把其所有邻节点中未进入队列等待的节点都加入队列中
            for (int i = adj.begin(); !adj.end(); i = adj.next()) {
                if (!visited[i]) {
                    q.push(i);
                    //下面维护节点关系数据
                    visited[i] = true;//只要成功进入队列的节点就置visited状态为true
                    from[i] = v;//记录前置节点
                    ord[i] = ord[v] + 1;//记录距离
                }
            }
            q.pop();//队列首节点所有工作已经全部完成，可以退出队列了

        }


    }

    virtual ~shortPath() {
        delete[] visited;
        delete[] ord;
        delete[] from;

    }


    //判断两点之间是否有路
    bool hasPath(int w) {//w为寻路终点
        assert(w >= 0 && w < G.V());
        return visited[w];
    }


    //执行寻路算法
    void path(int w, vector<int> &vec) {//传入终点w和一个空的向量vec从来存储路径
        assert(w >= 0 && w < G.V());
        stack<int> stack1;
        while (w != -1) {
            stack1.push(w);//把s到w的路径逆序压入栈中，再从栈中取出来时就是顺序了
            w = from[w];//起始点s的from[s]一直没被重置过，为初始值-1
        }
        vec.clear();
        while (!stack1.empty()) {//从栈中取出路径，此时的路径为顺序
            vec.push_back(stack1.top());//顺序压入向量中
            stack1.pop();
        }

    }

    //显示寻路算法算出来的路径
    void showPath(int w) {
        vector<int> vec;
        path(w, vec);//到此时vec从空向量变成了一个存储着路径序列的向量
        //控制输出格式
        cout << "the route from  " << s << " to " << w << " is :" << endl;
        for (int i = 0; i != vec.size(); i++) {
            if (i == vec.size() - 1) {
                cout << vec[i] << endl;
            } else {
                cout << vec[i] << "->";
            }
        }

    }


    //查询任意一个节点w到源点s之间的最短距离
    int length(int w) {
        assert(w >= 0 && w < G.V());
        return ord[w];
    }


};


#endif //GRAPHBASICS_SHORTPATH_H
