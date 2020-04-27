//
// Created by Islam, Abdullah Al Raqibul on 4/23/20.
//

#ifndef MAPCOLOR_BT_FC_ST_H
#define MAPCOLOR_BT_FC_ST_H

#include "base.h"
#include "../../utill/utills.h"

class MapColorBacktrackingFCSt : public MapColorBase {
public:
    MapColorBacktrackingFCSt(const string &file_name_, const int &num_color_) {
        //todo: we need to find a way to guarantee the following function calls in-this-order
        build_graph(file_name_);
        set_num_color(num_color_);
        if(num_color_ > 0) init_domain();
    }

    void do_coloring();
private:
    bool bt_func(int n_node);
    void forward_checking(int node_i, int color, vector<int> &marked_nodes);
    void revert_forward_checking(int color, vector<int> &marked_nodes);
    int get_color_unassigned_singleton_node();
};

void MapColorBacktrackingFCSt::forward_checking(int node_i, int color, vector<int> &marked_nodes) {
    int sz = c_graph[node_i].size();
    for(int j=0; j<sz; j+=1) {
        int neigh_j = c_graph[node_i][j];
        if(IS_SET(color_domain[neigh_j], color)) {
            color_domain[neigh_j] = CLR(color_domain[neigh_j], color);
            marked_nodes.push_back(neigh_j);
        }
    }
}

void MapColorBacktrackingFCSt::revert_forward_checking(int color, vector<int> &marked_nodes) {
    int sz = marked_nodes.size();
    for(int j=0; j<sz; j+=1) {
        int node_j = marked_nodes[j];

        color_domain[node_j] = SET(color_domain[node_j], color);
    }
}

// return a singleton node that has not been colored yet, return -1 if there is no such node
inline int MapColorBacktrackingFCSt::get_color_unassigned_singleton_node() {
    for(int node_i=0; node_i<num_node; node_i+=1) {
        if(color_assigned[node_i] == COLOR_UNASSIGNED && is_singleton(node_i)) return node_i;
    }
    return NOT_FOUND;
}

/**
 * bt_func - recursively color the graph
 * @param curr_node to assign color
 * @param n_node representing number of colored nodes
 * @return true @if it is possible to color the graph with the num_colors
 * */
bool MapColorBacktrackingFCSt::bt_func(int n_node) {
    // colored all the nodes, check whether this is a valid assignment
    if(n_node == num_node) {
        if(is_valid()) return true;
        return false;
    }

    int curr_node = get_color_unassigned_singleton_node();
    if(curr_node == NOT_FOUND) curr_node = get_color_unassigned_node();

    for(int color=0; color < num_color; color+=1) {
        // check whether this color exist in the domain of this node
        if(is_valid_in_domain(curr_node, color)) {
            // forward checking will make this color unavailable to the neighboring nodes
            // marked_nodes will track the nodes which has been forwardly checked in this step
            vector<int> marked_nodes;

            color_assigned[curr_node] = color;
            forward_checking(curr_node, color, marked_nodes);

            // trying to color the next node with the assignment of current node
            if(bt_func(n_node+1)) return true;

            // release the assignment, will try with the next color
            color_assigned[curr_node] = COLOR_UNASSIGNED;
            revert_forward_checking(color, marked_nodes);
            num_bt += 1;
        }
    }
    // it is not possible to color the map with the num_colors
    return false;
}

void MapColorBacktrackingFCSt::do_coloring() {
    struct timespec start, end;

    if(num_color < 0) {
        clock_gettime(CLOCK_REALTIME, &start);
        for(int num_color_=1; num_color_<MAX_COLOR_TRY; num_color_+=1) {
            set_num_color(num_color_);
            init_domain();
            if(bt_func(0)) break;
        }
        clock_gettime(CLOCK_REALTIME, &end);

        assert(num_color != NOT_FOUND);
        printf("The chromatic number for the given graph: %d\n", num_color);
        printf("Backtracking happened: %d\n", num_bt);
        printf("Time taken finding the chromatic number: %ld us\n", (long int) (utils::time_diff(start, end) / 1e3));
    }
    else {
        clock_gettime(CLOCK_REALTIME, &start);
        bool is_colored = bt_func(0);
        clock_gettime(CLOCK_REALTIME, &end);
        printf("It is %s to color the graph using %d colors\n", is_colored ? "POSSIBLE" : "NOT POSSIBLE", num_color);
        printf("Backtracking happened: %d\n", num_bt);
        printf("Time taken for this attempt: %ld us\n", (long int) (utils::time_diff(start, end) / 1e3));
    }
}

#endif //MAPCOLOR_BT_FC_ST_H
