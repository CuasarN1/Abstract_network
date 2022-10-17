#include "header.h"


Graph read(const string& path) {
	ifstream in;
	in.open(path);

	string P1, P2, line;
    vector <string> lines;
	vector<Node> G;
    map<string, vector<string>> matrix;
    vector<string> neighbours;

    while (getline(in, line))
        lines.push_back(line);

    int i = 0;
    for (auto line : lines) {
        P1 = "";
        int j = 0;
        while (line[j] != ' ') {
            P1 += line[j];
            j++;
        }

        j += 3;
        neighbours.clear();
        while (line[j] != ';') {
            P2 = "";
            while (line[j] != ',' and line[j] != ';') {
                P2 += line[j];
                j++;
            }
            neighbours.push_back(P2);
            if (line[j] == ',')
                j += 2;
            if (line[j] == ';')
                break;
        }

        Node node = Node(P1);
        G.push_back(node);
        matrix.insert({P1, neighbours});
    }

    for (auto it : matrix) {
        string from = it.first;
        vector<string> to = it.second;
        auto node = findById(G, from);

        vector<Node> nbrs;
        for (auto n : to) {
            auto neighbour = findById(G, n);
            nbrs.push_back(*neighbour);
        }

        node->setNeighbours(nbrs);
    }

    return Graph(G);
}

void write(Graph g) {
	string path = "../output.txt";
	ofstream of;
	of.open(path);

    //TODO

	of.close();
}

void show(Graph g) {
	auto G = g.getG();

    for (auto node : G) {
        cout << node.getId() << " : ";

        auto nbrs = node.getNeighbours();
        for (auto it = begin(nbrs); it != end(nbrs); it++) {
            cout << it->getId();
            prev(end(nbrs))->getId() == it->getId() ? cout << ';' : cout << ", ";
        }
        if (nbrs.size() == 0)
            cout << ';';
        cout << endl;
    }
}