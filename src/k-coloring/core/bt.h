//
// Created by Islam, Abdullah Al Raqibul on 4/23/20.
//

#ifndef MAPCOLOR_BT_H
#define MAPCOLOR_BT_H

#include "base.h"
#include "../../utill/utills.h"

class MapColorBacktracking : public MapColorBase {
public:
    MapColorBacktracking(const string &file_name_, const int &num_color_, bool try_mrv_, bool try_degree_c_, bool try_lcv_) {
        //todo: we need to find a way to guarantee the following function calls in-this-order
        set_heuristics(try_mrv_, try_degree_c_, try_lcv_);
        build_graph(file_name_);
        set_num_color(num_color_);
        if(num_color_ > 0) init_domain();
    }

    void do_coloring();
private:
    bool bt_func(int n_node);
};

/**
 * bt_func - recursively color the graph
 * @param curr_node to assign color
 * @param n_node representing number of colored nodes
 * @return true @if it is possible to color the graph with the num_colors
 * */
bool MapColorBacktracking::bt_func(int n_node) {
    // colored all the nodes, check whether this is a valid assignment
    if(n_node == num_node) {
        if(is_valid()) return true;
        return false;
    }

    int curr_node = get_color_unassigned_node();

    for(int color=0; color < num_color; color+=1) {
        // blindly assigning the color
        color_assigned[curr_node] = color;

        // trying to color the next node with the assignment of current node
        if(bt_func(n_node+1)) return true;

        // release the assignment, will try with the next color
        color_assigned[curr_node] = -1;
        num_bt += 1;
    }
    // it is not possible to color the map with the num_colors
    return false;
}

void MapColorBacktracking::do_coloring() {
    struct timespec start, end;

    //print_graph_node_label();

    if(num_color < 0) {
        clock_gettime(CLOCK_REALTIME, &start);
        for(int num_color_=1; num_color_<MAX_COLOR_TRY; num_color_+=1) {
            set_num_color(num_color_);
            init_domain();
            if(bt_func(0)) break;
        }
        clock_gettime(CLOCK_REALTIME, &end);

        assert(num_color != -1);
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

#endif //MAPCOLOR_BT_H
