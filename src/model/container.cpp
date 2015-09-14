#include "container.h"
#include <iostream>

void Container::draw() {
	for (auto& node : children) {
		node->draw();
	}
}