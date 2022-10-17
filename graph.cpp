#include "header.h"

Graph::~Graph() {
	n = 0;
	G.clear();
}

Graph::Graph() {
	G.clear();
    n = 0;
}

Graph::Graph(const Graph &g) {
	this->n = g.n;
	this->G = g.G;
}

Graph::Graph(vector <Node> g) {
    G.clear();
    n = G.size();
    G = std::move(g);
}

//bool Graph::operator== (Graph &g) {
//	return 	n == g.n and G == g.getG();
//}

bool Graph::empty() {
	return G.empty();
}

vector<Node> Graph::getG() {
	return G;
}

int Graph::getN()
{
	return n;
}

int Graph::OutEdge(string p)
{
	auto it = findById(G, p);
	if (it == G.end())
		return 0;
	else
		return it->getNeighbours().size();
}

int Graph::InEdge(string p)
{
	int cnt = 0;
	for (auto node : G) {
        auto nbrs = node.getNeighbours();
        if (findById(nbrs, p) != end(nbrs))
            cnt++;
    }

    return cnt;
}

void Graph::addN(Node node) {
    auto it = findById(G, node.getId());
    if (it == G.end()) {
        G.push_back(node);
        n++;
    } else
        cout << "Вершина уже существует" << endl;
}

void Graph::delN(Node node)
{
    auto it = findById(G, node.getId());
    if (it != G.end()) {
        G.erase(it);
        n--;
    } else
        cout << " Вершины не существует" << endl;
}

map <string, Node> Graph::getList()
{
	map <string, Node> nodes_with_id;
	for (auto it = begin(G); it != end(G); it++)
		nodes_with_id.insert({it->getId(), *it});

	return nodes_with_id;
}
