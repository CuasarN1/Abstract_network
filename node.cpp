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

vector<pair<Node, bool>> Node::getNeighbours() const {
    return neighbours;
}

void Node::setNeighbours(vector<pair<Node, bool>> nbrs) {
    neighbours = std::move(nbrs);
}

void Node::createEvent() {
    int value = rand_int(0, INT_MAX);
    events.push_back(value);
}

void Node::subscribe() {
    set<Node> s, allGrandnbrs;
    for (const auto& n : neighbours) {
        auto grandnbrs = n.first.getNeighbours();
        s.clear();
        for (const auto& node : grandnbrs) {
            s.insert(node.first);
        }
        allGrandnbrs.insert(s.begin(), s.end());
    }

    if (!allGrandnbrs.empty()) {
        for (const auto& n: allGrandnbrs) {
            if (n.getId() == id) {
                allGrandnbrs.erase(*this);
                break;
            }
        }

        auto it = allGrandnbrs.cbegin();
        auto r = rand_int(0, int(allGrandnbrs.size()));
        advance(it, r);
        bool handler = bool(rand_int(0, 1));
        neighbours.emplace_back(*it, handler);
    }
}

void Node::unsubscribe() {
    auto it = neighbours.cbegin();
    auto r = rand_int(0, int(neighbours.size()) - 1);
    advance(it, r);
    neighbours.erase(it);
}

Node Node::createNode(string name) {
    auto new_node = Node(std::move(name));
    bool handler = bool(rand_int(0, 1));
    neighbours.emplace_back(new_node, handler);

    return new_node;
}

void Node::handlerCount(const Node& node) {
    int count = int(node.getEvents().size());

    cout << node.getId() + " - > " + id + ": " + to_string(count) + '\n';
}

void Node::handlerSum(const Node& node) {
    auto evnts  = node.getEvents();
    unsigned int sum = 0;

    for (auto e : evnts)
        sum += e;

    cout << node.getId() + " - > " + id + ": " + to_string(sum) + '\n';
}
