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

string randName(Graph g) {
    auto G = g.getList();
    string name, chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    do {
        shuffle(begin(chars), end(chars), random_engine());
        name = chars.substr(0, 8);
    } while(G.find(name) != end(G));

    return name;
}

vector<Node>::iterator findById(vector<Node> &nodes, const string& _id) {
    for (auto it = begin(nodes); it != end(nodes); it++) {
        if (it->getId() == _id)
            return it;
    }

    return end(nodes);
}

Graph randomGraph(int min, int max) {
    int n = rand_int(min, max);
    bool handler;
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
        map <string, bool> nbrs;
        for (int j = 0; j < nbrs_num; j++) {
            handler = bool(rand_int(0, 1));
            nbrs.insert({G_copy[j].getId(), handler});
        }

        G[i].setNeighbours(nbrs);
    }
    Graph g = Graph(G);

    return g;
}

int main() {
	Graph g;
    g = randomGraph(5, 15);

//    string file = "../graph.txt";
//    g = read(file);
    show(g);

    unsigned short P1, P2, P3, P4, P5;

    cout << "Введите через пробел вероятности (от 0 до 100) пяти событий Узла:\n";
    cout << "1.\tУзел сети может создать событие несущее некоторые данные, в рамках тестового задания: случайное число\n";
    cout << "2.\tУзел сети может подписаться на события любого соседа любого своего соседа, кроме самого себя\n";
    cout << "3.\tУзел сети может отписаться от любого своего соседа\n";
    cout << "4.\tУзел может создать новый узел и подписаться на него, при этом новый созданный узел не участвует в текущем обновлении\n";
    cout << "5.\tУзел не выполняет никаких действий\n\n";

    cin >> P1 >> P2 >> P3 >> P4 >> P5;

    if (P1 + P2 + P3 + P4 + P5 == 100) {
        P4 = 100 - P5;
        P3 = P1 + P2 + P3;
        P2 = P1 + P2;

        while (true) {
            g.updateNetwork(P1, P2, P3, P4);
            print_handlers(g);

            if (g.empty())
                break;

            // sleep(1);
        }
    }
    else
        cout << "Сумма вероятностей событий P1..P5 не сходится в 100%";

	return 0;
}
