#pragma once

#include <limits>
#include <cmath>
#include <unordered_map>
#include "model.h"
#include <iostream>
#include <vector>

class RouteModel : public Model {

  public:
    class Node : public Model::Node {
      public:
        // Add public Node variables and methods here.
        Node * parent = nullptr;
        float h_value = std::numeric_limits<float>::max();
        float g_value = 0.0;
        bool visited = false;
        std::vector<Node *> neighbors;
        
        Node(){}
        Node(int idx, RouteModel * search_model, Model::Node node) : Model::Node(node), parent_model(search_model), index(idx) {}

        float distance(const Node& otherNode ) const { return sqrt( pow(this->x - otherNode.x, 2) + pow(this->y - otherNode.y,2)); }
      private:
        // Add private Node variables and methods here.
        int index;
        RouteModel * parent_model = nullptr;
    };
    
    // Add public RouteModel variables and methods here.
    RouteModel(const std::vector<std::byte> &xml);  
    std::vector<Node> path; // This variable will eventually store the path that is found by the A* search.
    auto &SNodes() { return m_Nodes; };
    auto &GetNodeToRoadMap() const noexcept { return node_to_road; };

  private:
    // Add private RouteModel variables and methods here.
    void CreateNodeToRoadHashmap();

    std::vector<Node> m_Nodes;
    std::unordered_map<int, std::vector<const Model::Road*>> node_to_road;

};
