#include <utility>

#include "header.h"


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
    neighbours = std::move(nbrs);
}

void Node::createEvent() {
    int value = rand_int(0, 1);
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
    auto r = rand_int(0, int(allGrandnbrs.size()));
    advance(it, r);
    neighbours.push_back(*it);
}

void Node::unsubscribe() {
    auto it = neighbours.cbegin();
    auto r = rand_int(0, int(neighbours.size()));
    advance(it, r);
    neighbours.erase(it);
}

void Node::createNode() {

    //Node newNode()
}
