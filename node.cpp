#include "header.h"


Node::Node(string _id) {
    id = std::move(_id);
}

Node::Node(const Node &n) {
    id = n.getId();
    neighbours = n.getNeighbours();
    events = n.getEvents();
}

Node::~Node() {
    id.clear();
    neighbours.clear();
    events.clear();
}

bool Node::operator== (const Node &n) const {
    return id == n.getId();
}

bool Node::operator<(const Node &n) const {
    return id < n.getId();
}

string Node::getId() const {
    return id;
}

vector<int> Node::getEvents() const {
    return events;
}

map<string, bool> Node::getNeighbours() const {
    return neighbours;
}

void Node::setNeighbours(map<string, bool> nbrs) {
    neighbours = std::move(nbrs);
}

void Node::createEvent() {
    int value = rand_int(0, 1000);
    events.push_back(value);
}

void Node::subscribe(const vector <Node>& G) {
    set<string> s, allGrandnbrs;
    for (const auto& n : G) {
        auto grandnbrs = n.getNeighbours();
        s.clear();
        for (const auto& node : grandnbrs) {
            s.insert(node.first);
        }
        allGrandnbrs.insert(s.begin(), s.end());
    }

    if (!allGrandnbrs.empty()) {
        for (const auto& n: allGrandnbrs) {
            if (n == id) {
                allGrandnbrs.erase(this->getId());
                break;
            }
        }

        auto it = allGrandnbrs.cbegin();
        auto r = rand_int(0, int(allGrandnbrs.size()));
        advance(it, r);
        bool handler = bool(rand_int(0, 1));
        neighbours.insert({*it, handler});
    }
}

void Node::unsubscribe() {
    if (!neighbours.empty()) {
        auto it = neighbours.cbegin();
        auto r = rand_int(0, int(neighbours.size()) - 1);
        advance(it, r);
        neighbours.erase(it);
    }
}

Node Node::createNode(const string& name) {
    auto new_node = Node(name);
    bool handler = bool(rand_int(0, 1));
    neighbours.insert({name, handler});

    return new_node;
}

void Node::handlerCount(const Node& node) {
    int count = int(node.getEvents().size());

    cout << node.getId() + " - > " + id + ": " + to_string(count) + " (eventCnt)\n";
}

void Node::handlerSum(const Node& node) {
    auto evnts  = node.getEvents();
    unsigned long long sum = 0;

    for (auto e : evnts)
        sum += e;

    cout << node.getId() + " - > " + id + ": " + to_string(sum) + " (eventSum)\n";
}
