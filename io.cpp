#include "header.h"


Graph read(const string& path) {
	ifstream in;
	in.open(path);

	string P1, P2, ln;
    vector <string> lines;
	vector<Node> G;
    map<string, map<string, bool>> matrix;
    map<string, bool> neighbours;

    while (getline(in, ln))
        lines.push_back(ln);

    for (auto line : lines) {
        P1 = "";
        int i = 0;
        while (line[i] != ' ') {
            P1 += line[i];
            i++;
        }

        i += 3;
        neighbours.clear();
        while (line[i] != ';') {
            P2 = "";
            bool handler;
            while (line[i] != '-') {
                P2 += line[i];
                i++;
            }
            i++;
            handler = line[i] == '1';
            i++;
            neighbours.insert({P2, handler});
            if (line[i] == ',')
                i += 2;
            if (line[i] == ';')
                break;
        }

        Node node = Node(P1);
        G.push_back(node);
        matrix.insert({P1, neighbours});
    }

    for (const auto& it : matrix) {
        string from = it.first;
        auto to = it.second;
        auto node = findById(G, from);

        vector<pair<Node, bool>> nbrs;
        for (const auto& n : to) {
            auto neighbour = findById(G, n.first);
            nbrs.emplace_back(*neighbour, n.second);
        }

        node->setNeighbours(nbrs);
    }

    return Graph(G);
}

void write(const Graph& g) {
	string path = "../output.txt";
	ofstream of;
	of.open(path);

    //TODO

	of.close();
}

void show(const Graph& g) {
	auto G = g.getG();

    for (const auto& node : G) {
        cout << node.getId() << " : ";

        auto nbrs = node.getNeighbours();
        for (auto it = begin(nbrs); it != end(nbrs); it++) {
            cout << it->first.getId() << '(' << it->second << ')';
            prev(end(nbrs))->first.getId() == it->first.getId() ? cout << ';' : cout << ", ";
        }
        if (nbrs.empty())
            cout << ';';
        cout << endl;
    }
    cout << endl;
}

void print_handlers(const Graph& g) {
    auto G = g.getG();
    for (auto node : g.getG()) {
        for (const auto& nbr : node.getNeighbours()) {
            if (nbr.second) {
                node.handlerSum(*findById(G, nbr.first.getId()));
            }
            else
                node.handlerCount(*findById(G, nbr.first.getId()));
        }
    }
}