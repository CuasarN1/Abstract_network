#pragma once
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <set>
#include <random>
#include <unistd.h>

using namespace std;


/*класс узла*/
class Node {
public:
    explicit Node(string id); // конструктор узла
    Node(const Node &n); // конструктор-копия узла
    virtual ~Node(); // деструктор узла
    bool operator== (const Node &n) const; // оператор равенства узлов
    bool operator< (const Node &n) const; // оператор сравнения узлов
    string getId() const; // геттер id
    vector<int> getEvents() const; // геттер вектора событий
    map<string, bool> getNeighbours() const; // геттер списка соседей
    void setNeighbours(map<string, bool> nbrs); // сеттер списка соседей
    void handlerCount(const Node& node); // обработчик "имя_отправителя -> имя_получателя: N = число_событий_полученных_от_этого_отправителя"
    void handlerSum(const Node& node); // обработчик "имя_отправителя -> имя_получателя: S = сумма_всех_чисел_полученных_от_этого_отправителя"

    /*действия узла*/
    void subscribe(const vector <Node>& G); // подписаться на случайного соседа соседа
    void unsubscribe(); // отписаться от соседа
    void createEvent(); // создать событие (случайное число от 0 до 1000)
    Node createNode(const string& name); // создать узел и подписаться на него

private:
    vector<int> events; // события
    string id; // id
    map<string, bool> neighbours; // соседи
};

/*класс графа*/
class Graph {
public:
	bool operator== (const Graph& g) const; // оператор равенства графов
    explicit Graph(vector <Node> g); // конструктор
	Graph(); // пустой граф
	Graph(const Graph &g); // конструктор-копия графа
	virtual ~Graph(); // деструктор графа
	bool empty(); // проверка на пустой граф
	static unsigned int outEdge(const Node& node); // подсчет количества подписок вершины node
    unsigned int inEdge(const Node& node); // подсчет количества подписок на вершину node
    vector <Node> getG() const; // геттер графа
	void addN(const Node& n); // добавить узел
	void delN(const Node& n); // удалить узел
    map <string, Node> getList(); //список узлов
    void updateNetwork(unsigned short P1, unsigned short P2,
                       unsigned short P3, unsigned short P4); // метод обновления сети

private:
    vector <Node> G; //список вершин
};

/*доп функции*/
vector<Node>::iterator findById(vector<Node> &nodes, const string& _id); // поиск узла по id
Graph randomGraph(int min, int max); // генерация случайного графа (min-max диапазон количества вершин)
string randName(Graph g); // случайное имя узла уникальное для графа g
int rand_int(int min, int max); // случайное число в диапазоне min-max
mt19937 random_engine(); // вихрь Мерсенна

/*IO*/
Graph read(const string& path); // чтение графа из файла
void write(const Graph& g); // запись графа в файл
void show(const Graph& g); // вывод графа в консоль
void print_handlers(const Graph& g); // вывод в консоль обработчиков событий для всех подписок
