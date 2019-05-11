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
    Node* closest_node = nullptr;
    Node node;

    for(int node_index : node_indices)
    {
        node = parent_model->SNodes()[node_index];
        if (!node.visited && this->distance(node) != 0.0)
        {
            if (closest_node == nullptr || this->distance(node) < this->distance(*closest_node))
            {
                closest_node = &parent_model->SNodes()[node_index];
            }
        }
    }
    return closest_node;
}

void RouteModel::Node::FindNeighbors() {
    for (const auto* roads : parent_model->node_to_road[this->index])
    {
        std::vector<int> indices = parent_model->Ways()[roads->way].nodes;
        Node * neighbor = FindNeighbor(indices);
        if (neighbor != nullptr)
        {
            neighbors.push_back(neighbor);
        }
    }
}