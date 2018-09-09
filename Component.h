//
// Created by Administrator on 2018/9/9.
//

#ifndef GRAPHBASICS_CONPONENT_H
#define GRAPHBASICS_CONPONENT_H
#include <iostream>
#include <cassert>
using namespace std;
template <typename Graph>
class ComPonent{
private:
    Graph &G;
    bool *visited;
    int ccount;
    int *id;

    void dfs(int v){
            visited[v]= true;
            id[v]=ccount;
            typename Graph::adjIterator adj(G,v);
            for(int i=adj.begin();!adj.end();i=adj.next()){
                    if(!visited[i]){
                            dfs(i);
                    }
            }
    }
public:

    ComPonent(Graph&graph):G(graph){

            visited=new bool[G.V()];
            id=new int[G.V()];
            ccount=0;
            for(int i=0;i<G.V();i++){
                    visited[i]=false;
                    id[i]=-1;
            }
            for(int i=0;i<G.V();i++){
                    if(!visited[i]){
                            dfs(i);
                            ccount++;
                    }
            }

    }

    ~ComPonent(){
            delete[] visited;
            delete[] id;
    }

    int count(){
            return ccount;
    }

    bool isConnect(int v,int w){
            return id[v]==id[w];
    }

};
#endif //GRAPHBASICS_CONPONENT_H
