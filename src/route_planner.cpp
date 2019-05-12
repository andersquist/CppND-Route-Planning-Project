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