#include "header.h"

mt19937 random_engine() {
    random_device rd;
    mt19937 rng(rd());
    return rng;
}

int rand_int(int min, int max) {
    auto rng = random_engine();
    uniform_int_distribution<int> uni(min,max);
    int n = uni(rng);
    return n;
}


Graph randomGraph(int min, int max) {
    int n = rand_int(min, max);
    vector<Node> G;
    for (int i = 1; i <= n; i++) {
        string name = "N_" + to_string(i);
        Node node = Node(name);
        G.push_back(node);
    }

    for (int i = 0; i < G.size(); i++) {
        int nbrs_num = rand_int(0, n - 1);
        vector<Node> G_copy(G);
        G_copy.erase(begin(G_copy) + i);
        shuffle(begin(G_copy), end(G_copy), random_engine());
        for (int j = 0; j < n - 1 - nbrs_num; j++)
            G_copy.pop_back();
        G[i].setNeighbours(G_copy);
    }

    Graph g = Graph(G);

    return g;
}

vector<Node>::iterator findById(vector<Node> &nodes, const string& _id) {
    for (auto it = begin(nodes); it != end(nodes); it++) {
        if (it->getId() == _id)
            return it;
    }

    return end(nodes);
}

void update_network() {

}

int main() {
	Graph g;
	string P1, P2;
//    string file = "../graph.txt";
//    g = read(file);
    g = randomGraph(5, 15);
    show(g);
	
	return 0;
}
