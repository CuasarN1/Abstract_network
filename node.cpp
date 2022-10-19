#include "header.h"
#include <random>


vector<Node>::iterator findById(vector<Node> &nodes, string _id) {
    for (auto it = begin(nodes); it != end(nodes); it++) {
        if (it->getId() == _id)
            return it;
    }

    return end(nodes);
}

Node::Node(string _id) {
    id = std::move(_id);
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

vector<int> Node::getEvents() {
    return events;
}

vector<Node> Node::getNeighbours() {
    return neighbours;
}

void Node::setNeighbours(vector<Node> nbrs) {
    neighbours = nbrs;
}

void Node::createEvent() {
    int value;
    value = rand();
    events.push_back(value);
}

void Node::subscribe() {
    set<Node> allGrandnbrs;
    for (auto n : neighbours) {
        auto grandnbrs = n.getNeighbours();
        set<Node> s(grandnbrs.begin(), grandnbrs.end());
        allGrandnbrs.insert(s.begin(), s.end());
    }

    for (auto n : allGrandnbrs) {
        if (n.getId() == id) {
            allGrandnbrs.erase(*this);
            break;
        }
    }

    auto it = allGrandnbrs.cbegin();
    auto r = rand() % allGrandnbrs.size();
    advance(it, r);
    neighbours.push_back(*it);
}

void Node::unsubscribe() {
    auto it = neighbours.cbegin();
    auto r = rand() % neighbours.size();
    advance(it, r);
    neighbours.erase(it);
}

void Node::createNode() {

    //Node newNode()
}
