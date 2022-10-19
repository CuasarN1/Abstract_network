#pragma once
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <set>
#include <random>
#include <algorithm>
#include <ctime>

using namespace std;

//const int INF = INT_MAX;

/*класс узла*/
class Node {
public:
    Node(string id);
    bool operator== (const Node &n) const;
    bool operator< (const Node &n) const;
    string getId() const;
    vector<int> getEvents();
    vector<Node> getNeighbours();
    void setNeighbours(vector<Node> nbrs);


private:
    vector<int> events;
    string id;
    vector<Node> neighbours;

    void subscribe();
    void unsubscribe();
    void createEvent();
    void createNode();


};

/*класс графа*/
class Graph {
public:
	bool operator== (const Graph g) const; //сравнение графов
    explicit Graph(vector <Node> g); //конструктор
	Graph(); //пустой граф
	Graph(const Graph &g); //конструктор-копия
	~Graph(); //деструктор графа
	bool empty(); //проверка на пустой граф
	int getN(); //количество вершин
	int OutEdge(string p); //подсчет количества исходящих ребер из вершины р
	int InEdge(string p); //подсчет количества входящих ребер из вершины р
    vector <Node> getG() const; // геттер графа
	void addN(Node n); // добавить вершину
	void delN(const Node& n); // удалить вершину

private:
	unsigned int n; //количество вершин
    vector <Node> G; //список вершин
    map <string, Node> getList(); //список вершин
};

/*доп функции*/
vector<Node>::iterator findById(vector<Node> &nodes, const string& _id);
Graph randomGraph(int min, int max);
string randName(Graph g);
int rand_int(int min, int max);
mt19937 random_engine();

/*IO*/
bool check(map <string, map<string, int>> m);
Graph read(const string& path);
void write(Graph g);
void show(Graph g);
