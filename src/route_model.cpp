#include "route_model.h"
#include <iostream>

RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
    for (int i = 0; i < this->Nodes().size(); i++ ) {
        auto current = this->Nodes()[i];

        // Create node on stack
        RouteModel::Node routeNode (i, this, current);

        // Copy it to the vector
        m_Nodes.push_back(routeNode);

    }
}