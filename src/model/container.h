#pragma once

#include "Node.h"
#include <vector>

class Container : public Node {

private:
	std::vector<NodePtr> children;

public:
	Container() : Node() {

	}
	void draw();
	void add(NodePtr node) {
		children.push_back(node);
	}

	~Container() {
		
	}
};