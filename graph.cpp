#include "header.h"


Graph::~Graph() {  // деструктор графа
	G.clear();
}

Graph::Graph() {  // пустой конструктор графа
	G = vector<Node>();
}

Graph::Graph(const Graph &g) {  // конструктор копирования графа
	G = g.G;
}

Graph::Graph(vector <Node> g) {  // конструктор графа
    G.clear();
    G = std::move(g);
}

bool Graph::operator== (const Graph& g) const {  // оператор равенства графов
	return G == g.getG();
}

bool Graph::empty() {  // функция очистки графа
	return G.empty();
}

vector<Node> Graph::getG() const {  // геттер матрицы смежности графа
	return G;
}

unsigned int Graph::outEdge(const Node& node)  // функция получения исходящих ребер для указанного вершины орграфа
{
    return unsigned(node.getNeighbours().size());
}

unsigned int Graph::inEdge(const Node& node)  // функция получения входящих ребер для указанного вершины орграфа
{
	int cnt = 0;
	for (const auto& e : G) {
        auto nbrs = e.getNeighbours();
        for (auto it= begin(nbrs); it != end(nbrs); it++)
            if (it->first == node.getId())
                cnt++;
    }

    return cnt;
}

void Graph::addN(const Node& node) {  // функция добавления вершины
    auto it = findById(G, node.getId());
    if (it == G.end())
        G.push_back(node);
    else
        cout << "Вершина уже существует" << endl;
}

void Graph::delN(const Node& node)  // функция удаления вершины
{
    auto it = findById(G, node.getId());
    if (it != G.end())
        G.erase(it);
    else
        cout << " Вершины не существует" << endl;
}

map <string, Node> Graph::getList()  // функция получения словаря id: вершина
{
	map <string, Node> nodes_with_id;
	for (auto it = begin(G); it != end(G); it++)
		nodes_with_id.insert({it->getId(), *it});

	return nodes_with_id;
}

void Graph::updateNetwork(unsigned short P1, unsigned short P2,
                          unsigned short P3, unsigned short P4) {
    // функция обновления графа
    vector<Node> newG;

    for (const auto& node : G) {
        auto copy_node = Node(node);
        unsigned short process = rand_int(0, 100);

        if (process <= P1)
            copy_node.createEvent();
        else if (process > P1 and process <= P2)
            copy_node.subscribe(G);
        else if (process > P2 and process <= P3)
            copy_node.unsubscribe();
        else if (process > P3 and process <= P4) {
            string name = randName(*this);
            auto new_node = copy_node.createNode(name);
            newG.push_back(new_node);
        } else if (process > P4) {
            //DO NOTHING
        }

        newG.push_back(copy_node);
    }

    G = newG;

    auto it = begin(G);
    while (it != end(G)) {
        if (inEdge(*it) == 0 and outEdge(*it) == 0)
            G.erase(it);
        else
            it++;
    }
}
