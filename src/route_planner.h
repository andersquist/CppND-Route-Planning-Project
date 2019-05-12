#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "route_model.h"


class RoutePlanner {
  public:
    RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y);
    // Add public variables or methods declarations here.
    float Distance() const { return distance; };

  private:
    // Add private variables or methods declarations here.
    std::vector<RouteModel::Node> ConstructFinalPath(RouteModel::Node *current_node);
    RouteModel &m_Model;
    RouteModel::Node *start_node;
    RouteModel::Node *end_node;
    float distance;
};
