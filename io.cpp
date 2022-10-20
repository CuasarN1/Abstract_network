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
        node.setNeighbours(neighbours);
        G.push_back(node);
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
            cout << it->first << '(' << it->second << ')';
            prev(end(nbrs))->first == it->first ? cout << ';' : cout << ", ";
        }
        if (nbrs.empty())
            cout << ';';
        cout << endl;
    }
    cout << endl;
}

void print_handlers(const Graph& g) {
    auto G = g.getG();
    for (auto to : g.getG()) {
        for (const auto& nbr : to.getNeighbours()) {
            auto from = findById(G, nbr.first);
            if (from != end(G)) {
                if (nbr.second)
                    to.handlerSum(*from);
                else
                    to.handlerCount(*from);
            }
        }
    }
    cout << endl;
}
