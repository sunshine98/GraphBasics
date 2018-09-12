//
// Created by Administrator on 2018/9/11.
//

#ifndef GRAPHBASICS_PATH_H
#define GRAPHBASICS_PATH_H

#include <stack>
#include <iostream>
#include "cassert"
#include "vector"


using namespace std;
template <typename Graph>
class Path{
private:
    Graph &G;//引用需要进行路径查询的图
    int s;//s为source的意思。即需要寻路的源（起始）节点
    bool* visited;//记录节点是否被访问过
    int * from;//数组用来记录每个节点的上一个节点编号

       void dfs(int v){//我自己规定dfs算法的传入的参数v必须为未被访问的节点
            visited[v]= true;//设置传入节点visited状态为true
           typename Graph::adjIterator adj(G,v);//提取出图中v节点所有邻边的迭代器
           for (int i = adj.begin(); !adj.end() ; i=adj.next()) {
            if(!visited[i]){
                from[i]=v;//此时访问状态从v节点跳到了与其相邻节点之一的i节点
                dfs(i);//继续对i节点进行深度搜索
            }
           }

       }



public:
    Path(Graph &G, int s) : G(G), s(s) {
        assert(s>=0&&s<=G.V());//检查参数，防止越界访问
        visited=new bool[G.V()];//构造visited数组
        from=new int[G.V()];//构造from数组
        //下面是初始化工作
        for (int i = 0; i < G.V(); i++){
            visited[i]=false;
            from[i]=-1;
        }

        //执行dfs算法，把寻路需要使用到的数据准备好
        //即完成visited和from数组的数据准备
        dfs(s);

    }

    virtual ~Path() {
        delete [] visited;
        delete [] from;
    }

    //判断两点之间是否有路
    bool hasPath(int w){//w为寻路终点
        assert(w>=0&&w<G.V());
        return visited[w];
    }


    //执行寻路算法
    void path(int w,vector<int> &vec){//传入终点w和一个空的向量vec从来存储路径
        assert(w>=0&&w<G.V());
        stack <int> stack1;
        while(w!=-1){
            stack1.push(w);//把s到w的路径逆序压入栈中，再从栈中取出来时就是顺序了
            w=from[w];//起始点s的from[s]一直没被重置过，为初始值-1
        }
        vec.clear();
        while(!stack1.empty()){//从栈中取出路径，此时的路径为顺序
            vec.push_back(stack1.top());//顺序压入向量中
            stack1.pop();
        }

    }


    //显示寻路算法算出来的路径
    void showPath(int w){
        vector<int> vec;
        path(w,vec);//到此时vec从空向量变成了一个存储着路径序列的向量
        //控制输出格式
        cout<<"the route from  "<<s<<" to "<<w<<" is :"<<endl;
        for (int i = 0;i!=vec.size() ; i++) {
            if(i==vec.size()-1){
                cout<<vec[i]<<endl;
            }
            else{
                cout<<vec[i]<<"->";
            }
        }

    }

};
#endif //GRAPHBASICS_PATH_H
