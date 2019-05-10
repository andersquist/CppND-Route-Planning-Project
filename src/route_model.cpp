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

    CreateNodeToRoadHashmap();
}

void RouteModel::CreateNodeToRoadHashmap() {
    for(const Model::Road& road : Roads()) {
        if (road.type != Model::Road::Type::Footway) {
            for(auto node_idx : Ways()[road.way].nodes) {
                if (node_to_road.find(node_idx) == node_to_road.end()) {
                    node_to_road[node_idx] = std::vector<const Model::Road*>();
                }
                node_to_road[node_idx].push_back( &road );
            }
        }
    }
}

RouteModel::Node* RouteModel::Node::FindNeighbor(const std::vector<int>& node_indices) {
    RouteModel::Node* closest_node = nullptr;

    for(int i = 0; i < node_indices.size(); i++)
    {
        Node node = parent_model->SNodes()[i];
        if (!node.visited && this->distance(node) != 0.0)
        {
            if (closest_node == nullptr || this->distance(node) < this->distance(*closest_node))
            {
                closest_node = &parent_model->SNodes()[i];
            }
        }
    }

    return closest_node;
}