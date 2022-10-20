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
#include <utility>

using namespace std;

/*класс узла*/
class Node {
public:
    explicit Node(string id);
    Node(const Node &n);
    virtual ~Node();
    bool operator== (const Node &n) const;
    bool operator< (const Node &n) const;
    string getId() const;
    vector<int> getEvents() const;
    vector<pair<Node, bool>> getNeighbours() const;
    void setNeighbours(vector<pair<Node, bool>> nbrs);
    void handlerCount(const Node& node);
    void handlerSum(const Node& node);

    void subscribe();
    void unsubscribe();
    void createEvent();
    Node createNode(string name);

private:
    vector<int> events;
    string id;
    vector<pair<Node, bool>> neighbours;
};

/*класс графа*/
class Graph {
public:
	bool operator== (const Graph& g) const; //сравнение графов
    explicit Graph(vector <Node> g); //конструктор
	Graph(); //пустой граф
	Graph(const Graph &g); //конструктор-копия
	virtual ~Graph(); //деструктор графа
	bool empty(); //проверка на пустой граф
	static unsigned int outEdge(const Node& node); //подсчет количества исходящих ребер из вершины р
    unsigned int inEdge(const Node& node); //подсчет количества входящих ребер из вершины р
    vector <Node> getG() const; // геттер графа
	void addN(const Node& n); // добавить вершину
	void delN(const Node& n); // удалить вершину
    map <string, Node> getList(); //список вершин
    void updateNetwork(unsigned short P1, unsigned short P2,
                unsigned short P3, unsigned short P4); // метод обновления сети

private:
    vector <Node> G; //список вершин
};

/*доп функции*/
vector<Node>::iterator findById(vector<Node> &nodes, const string& _id);
Graph randomGraph(int min, int max);
string randName(Graph g);
int rand_int(int min, int max);
mt19937 random_engine();
vector<pair<Node, bool>>::iterator find(vector<pair<Node, bool>> &vec, const Node& node);


/*IO*/
Graph read(const string& path);
void write(const Graph& g);
void show(const Graph& g);
void print_handlers(const Graph& g);
