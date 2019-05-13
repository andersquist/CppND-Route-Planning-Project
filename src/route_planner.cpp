#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    start_node = &m_Model.FindClosestNode(start_x, start_y);
    end_node = &m_Model.FindClosestNode(end_x, end_y);

}

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    std::vector<RouteModel::Node> path_found;
    float total_distance = 0.0;

    RouteModel::Node* next = current_node;
    while (next != nullptr) {
        path_found.push_back(*next);

        if (next->parent != nullptr)
            total_distance += next->distance(*next->parent);

        next = next->parent;
    }
    distance = total_distance * m_Model.MetricScale();
    return path_found;
}

void RoutePlanner::AStarSearch() {
    start_node->visited = true;
    open_list.push_back(start_node);

    RouteModel::Node *current_node = nullptr;

    while(open_list.size() > 0) {
        current_node = NextNode();

        if (current_node->distance(*end_node) == 0.0) {
            m_Model.path = ConstructFinalPath(current_node);
            return;
        } else {
            AddNeighbors(current_node);
        }
    }

}

float RoutePlanner::CalculateHValue(const RouteModel::Node *otherNode) {
    return end_node->distance(*otherNode);
}

RouteModel::Node* RoutePlanner::NextNode() {

    // Sorting so that the lowest is last
    std::sort(open_list.begin(), open_list.end(),
            [](const RouteModel::Node* left, const RouteModel::Node* right)
            { return (left->g_value + left->h_value) > (right->g_value + right->h_value); });

    // get lowest and remove it
    auto* next = open_list[open_list.size() - 1];
    open_list.pop_back();
    return next;
}

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    current_node->FindNeighbors();
    for (auto neighbour : current_node->neighbors) {
        neighbour->parent = current_node;
        neighbour->g_value = current_node->g_value + current_node->distance(*neighbour);
        neighbour->h_value = CalculateHValue(neighbour);
        open_list.push_back(neighbour);
        neighbour->visited = true;
    }

}