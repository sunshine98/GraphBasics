//
// Created by Administrator on 2018/9/16.
//

#ifndef GRAPHBASICS_EDGE_H
#define GRAPHBASICS_EDGE_H

#include <iostream>
#include <cassert>

using namespace std;

template<typename Weight>
class Edge {
private:
    int a, b;//分别为边的两个端点
    Weight weight;//两端点之间边的权重
public:
    Edge(int a, int b, Weight weight) : a(a), b(b), weight(weight) {}

    Edge() {}

    virtual ~Edge() {

    }

    int V() {//返回第一个端点
        return a;
    }

    int W() {//返回第二个端点
        return b;
    }

    Weight wt() {//返回边的权值
        return weight;
    }

    int other(int x) {//返回给定端点的另一个端点
        return x == a ? b : a;//若x为a,则返回b;若x为b则返回a
    }

    // 输出边的信息
    friend ostream &operator<<(ostream &os, const Edge &e) {
        os << e.a << "-" << e.b << ": " << e.weight;
        return os;
    }

    // 边的大小比较, 是对边的权值的大小比较
    bool operator<(Edge<Weight> &e) {
        return weight < e.wt();
    }

    bool operator<=(Edge<Weight> &e) {
        return weight <= e.wt();
    }

    bool operator>(Edge<Weight> &e) {
        return weight > e.wt();
    }

    bool operator>=(Edge<Weight> &e) {
        return weight >= e.wt();
    }

    bool operator==(Edge<Weight> &e) {
        return weight == e.wt();
    }
};

#endif //GRAPHBASICS_EDGE_H
