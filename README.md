# astar

A c++ implementation of the A\* search algorithm using a priority queue and a templated weight-type. The algorithm finds the shortest path between two nodes on a weighted graph.

A `node` uses a templated `cost_type` and contains a `vector` of `edge`s and two `cost_type` values: `tentative` and `heuristic`. An `edge` is a pair of `node*` and `cost_type`. The `path` method takes two `node&` and returns a `cost_type` of the sum of the weighs of all of the `edge`s along the shortest possible path between the two `node`s. If a path does not exist, `std::numeric_limits<cost_type>::max()` is returned. If a path was found, the `tentative` values of all of the `node`s along the path are equal to the sum of the weights of all the `edge`s along the shortest possible path from the `start` `node` to the `node`. This means you can retrace the shortest path by starting at the `goal` `node` and following the `node`s with the smallest `tentative` values until you reach the `start` node. *Minimal code example below.*
```cpp
#include <iostream>
#include "astar.hpp"

int main(){
  astar::node<unsigned> n0, n1, n2; // Three nodes.
  n0.edges.emplace_back(&n1, 1u); // Add a path with a cost of 1 from n0 to n1
  std::cout << astar::path(n0, n1) << std::endl; // The shortest path from n0 to n1 should be 1
  std::cout << astar::path(n0, n2) << std::endl; /* The shortest path from n0 to n2 should be
                                                    std::numeric_limits<unsigned>::max */
}
```
