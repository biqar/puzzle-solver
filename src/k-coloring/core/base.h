//
// Created by Islam, Abdullah Al Raqibul on 4/22/20.
//

#ifndef MAPCOLOR_BASE_H
#define MAPCOLOR_BASE_H

#include <map>
#include <string>
#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>

#include "../../utill/utills.h"

/*
 * Note: There are 195 countries in the world, 193 of which are members of the United Nations.
 * If you need to color a larger map with larger nodes, please increase this value to fit your graph.
 * */
#define MAX_NODES               200
#define MAX_COLOR_TRY           10
#define COLOR_UNASSIGNED        -1
#define NOT_FOUND               -1
#define COLOR_MASK(num_color)   ((1 << num_color) - 1)
#define CHK_POW_OF_TWO(N)       (N & (N - 1))
#define IS_SET(N, POS)          (N & (1 << POS))
#define SET(NUM, POS)           (NUM |  (1<<POS))
#define CLR(NUM, POS)           (NUM & ~(1<<POS))
//#define CHK(NUM, POS)           (NUM &  (1<<POS))

class MapColorBase {
public:
    // perform the map coloring
    virtual void do_coloring() {};

    // build the graph by reading the input from file
    void build_graph(const string &filename_);

    // initialize the color domain for each node
    void init_domain();

    // checks whether the full map color assignment is valid or not
    bool is_valid();

    // checks neighbors to confirm whether "node" can assign "color"
    bool is_valid(int node_i, int color);

    // checks available domain to confirm whether "node" can assign "color"
    bool is_valid_in_domain(int node_i, int color);

    // checks whether "node" has any available color left in it's domain
    bool any_valid_color(int node_i);

    // checks whether the "node" is singleton, meaning "node" has a single available color in it's domain
    bool is_singleton(int node_i);

    // get the color assigned to the "node"
    int get_color(int node_i);

    // returns the assigned color with the graph node label
    map<string, int> get_colored_map();

    // print the full map with the assigned color
    void print_colored_map();

    // print the label of the graph nodes
    void print_graph_node_label();

    // return the id of a node (i.e. node can be city/state, we internally map it to a integer id)
    // if the "node_str" doesn't exist, add it to the map and return the assigned node-id
    int get_node_id(const string &node_str);

    // set an integer id for the node
    // if the "node_str" already has an id, don't assign a new one
    void set_node_id(const string &node_str);

    // return a node that has not been colored yet, return -1 if there is no such node
    int get_unassigned_node();

    // return the label of a node
    string get_node_label(const int &node_i);

    // checks whether node_i is a valid node or not
    bool is_valid_node(int node_i);

    // Minimum remaining values - return nodes with minimum remaining valid colors
    void mrv(vector<int> &available_nodes);

    // Degree heuristic - return nodes with max neighbours
    void degree_heuristic(vector<int> &available_nodes);

    // Least constraining value - Return colors which used much
    void lcv(int node_i, map<int, int> &lcv_count);

    // Prepare list of available color for node_i
    void prepare_color_queue(int node_i, priority_queue<pair<int, int> > &pq);

    /* getter/setter */
    int get_num_color();
    void set_num_color(int num_color_);

    int get_num_nodes();
    void set_num_nodes(int num_node_);

    void set_heuristics(bool try_mrv_, bool try_degree_c_, bool try_lcv_);

protected:
    int num_node = 0;
    int num_color = -1;
    int num_bt = 0;

    std::map<string, int> m;
    std::map<int, string> m_rev;

    bool try_mrv = false;
    bool try_degree_c = false;
    bool try_lcv = false;

    // constraint graph
    std::vector<int> c_graph[MAX_NODES];

    // hold assigned color information of the node
    int color_assigned[MAX_NODES];

    // bit mask of the available color domain
    // bit position indicate color; 1 means available, 0 means not available
    int color_domain[MAX_NODES];
};

// build the graph by reading the input from file
void MapColorBase::build_graph(const string &filename_) {
    // initialize the number of nodes
    num_node = 0;

    std::ifstream file(filename_);

    if (!file.is_open()) {
        std::cout << "Couldn't open file " << filename_ << std::endl;
        std::exit(-2);
    }

    string line;
    string src, neigh;
    int src_i, neigh_i;

    // first line will contain how many nodes exist in the graph
    getline(file, line);

    // reading the adjacency list
    while(!file.eof()) {
        if(getline(file, line)) {
            // string stream to parse by space
            std::stringstream ss(line);
            // read source node and map the source identity
            ss >> src;
            src_i = get_node_id(src);
            while(ss >> neigh) {
                // map the neighbor identity
                neigh_i = get_node_id(neigh);

                // insert the edge in the graph
                c_graph[src_i].push_back(neigh_i);
            }
        }
    }

    file.close();
}

// initialize the color domain for each node
void MapColorBase::init_domain() {
    for(int node_i=0; node_i<num_node; node_i+=1) {
        color_assigned[node_i] = COLOR_UNASSIGNED;
        color_domain[node_i] = COLOR_MASK(num_color);
    }
}

// return the id of a node (i.e. node can be city/state, we internally map it to a integer id)
// if the "node_str" doesn't exist, add it to the map and return the assigned node-id
inline int MapColorBase::get_node_id(const string &node_str) {
    if(m.find(node_str) != m.end()) {
        return m[node_str];
    }

    // node is not mapped yet, mapping it now
    m[node_str] = num_node;
    m_rev[num_node] = node_str;
    num_node += 1;

    return m[node_str];
}

// set an integer id for the node
// if the "node_str" already has an id, don't assign a new one
inline void MapColorBase::set_node_id(const string &node_str) {
    if(m.find(node_str) != m.end()) return;

    // node is not mapped yet, mapping it now
    m[node_str] = num_node;
    m_rev[num_node] = node_str;
    num_node += 1;
}

// return a node that has not been colored yet, return -1 if there is no such node
inline int MapColorBase::get_unassigned_node() {
    vector<int> available_nodes;
    for(int node_i=0; node_i<num_node; node_i+=1) {
        if(color_assigned[node_i] == COLOR_UNASSIGNED) available_nodes.push_back(node_i);
    }

    if(try_mrv) {
        mrv(available_nodes);
    }

    if(try_degree_c) {
        degree_heuristic(available_nodes);
    }

    if(available_nodes.size()) {
        std::random_shuffle(available_nodes.begin(), available_nodes.end(), utils::my_random);
        return available_nodes[0];
    }

    return NOT_FOUND;
}

// return the label of a node
inline string MapColorBase::get_node_label(const int &node_i) {
    assert(m_rev.find(node_i) != m_rev.end());
    return m_rev[node_i];
}

// checks whether the full map color assignment is valid or not
bool MapColorBase::is_valid() {
    for(int src_i=0; src_i<num_node; src_i+=1) {
        int sz = c_graph[src_i].size();
        for(int j=0; j<sz; j+=1) {
            int dst_j = c_graph[src_i][j];
            if(color_assigned[src_i] == color_assigned[dst_j]) return false;
        }
    }

    return true;
}

// checks neighbors to confirm whether "node" can assign "color"
bool MapColorBase::is_valid(int node_i, int color) {
    int sz = c_graph[node_i].size();
    for(int j=0; j<sz; j+=1) {
        int dst_j = c_graph[node_i][j];

        // neighbor dst_j of node_i already acquire the color
        if(color_assigned[dst_j] == color) return false;
    }

    return true;
}

// checks available domain to confirm whether "node" can assign "color"
bool MapColorBase::is_valid_in_domain(int node_i, int color) {
    // check whether color is available in the domain of node_i
    if(IS_SET(color_domain[node_i], color)) return true;
    return false;
}

// checks whether "node" has any available color left in it's domain
inline bool MapColorBase::any_valid_color(int node_i) {
    return color_domain[node_i] & COLOR_MASK(num_color);
}

// checks whether the "node" is singleton, meaning "node" has a single available color in it's domain.
// we can simply check whether the color_domain[node_i] holds a number that is a power of 2.
// as we know, if a number is power of 2 then in binary representation the count of 1 will be one.
inline bool MapColorBase::is_singleton(int node_i) {
    if(color_domain[node_i] != 0 && CHK_POW_OF_TWO(color_domain[node_i]) == 0) return true;
    return false;
}

// get the color assigned to the "node"
inline int MapColorBase::get_color(int node_i) {
    return color_assigned[node_i];
}

// returns the assigned color with the graph node label
map<string, int> MapColorBase::get_colored_map() {
    map<string, int> map_color;
    for(int i=0; i<num_node; i+=1) {
        assert(m_rev.find(i) != m_rev.end());
        map_color[m_rev[i]] = color_assigned[i];
    }

    return map_color;
}

// print the full map with the assigned color
void MapColorBase::print_colored_map() {
    std::cout << std::endl << "== begin of printing graph nodes with colors ==" << std::endl;
    for(int i=0; i<num_node; i+=1) {
        assert(color_assigned[i] != COLOR_UNASSIGNED);
        assert(m_rev.find(i) != m_rev.end());
        std::cout << m_rev[i] << " " << color_assigned[i] << std::endl;
    }
    std::cout << "== end of printing graph nodes with colors ==" << std::endl << std::endl;
}

// print the label of the graph nodes
void MapColorBase::print_graph_node_label() {
    std::cout << std::endl << "== begin of printing graph nodes with labels ==" << std::endl;
    for(std::map<string, int>::iterator it = m.begin(); it!=m.end(); it++) {
        std::cout << it->first << " -> " << it->second << std::endl;
    }
    std::cout << "== end of printing graph nodes with labels ==" << std::endl << std::endl;
}

// checks whether node_i is a valid node or not
inline bool MapColorBase::is_valid_node(int node_i) {
    if(node_i < 0 || node_i >= num_node) return false;
    return true;
}

/**
 * Minimum remaining values - return nodes with minimum remaining valid colors
 *
 * @param available_nodes - the list of nodes where the mrv will be applied
 * */
void MapColorBase::mrv(vector<int> &available_nodes) {
    int min_remain = MAX_COLOR_TRY;

    // taking backup of the available nodes
    vector<int> bk(available_nodes.begin(), available_nodes.end());
    int sz = bk.size();

    // clear the list of available nodes
    available_nodes.clear();

    for(int i=0; i<sz; i+=1) {
        int node_i = bk[i];
        int curr_avail_cnt = utils::count_set_bit(color_domain[node_i]);

        if(curr_avail_cnt < min_remain) {
            // new MRV found, clear the mrv node list and insert this node
            available_nodes.clear();
            available_nodes.push_back(node_i);
            min_remain = curr_avail_cnt;
        }
        else if (curr_avail_cnt == min_remain) {
            // this node also has MRV, insert this node to the mrv node list
            available_nodes.push_back(node_i);
        }
    }
}

/**
 * Degree heuristic - return nodes with max neighbours.
 * This heuristic can be applied as a tie breaker of the MRV result.
 *
 * @param available_nodes - list of nodes where the degree heuristic will be applied
 * */
void MapColorBase::degree_heuristic(vector<int> &available_nodes) {
    int mx_degree = -1;

    // taking backup of the available nodes
    vector<int> bk(available_nodes.begin(), available_nodes.end());
    int sz = bk.size();

    // clear the list of available nodes
    available_nodes.clear();

    for(int i=0; i<sz; i+=1) {
        int node_i = bk[i];
        int curr_degree = c_graph[node_i].size();

        if(curr_degree > mx_degree) {
            // new higher degree found, clear the degree node list and insert this node
            available_nodes.clear();
            available_nodes.push_back(node_i);
            mx_degree = curr_degree;
        }
        else if(curr_degree == mx_degree) {
            // this node also has higher degree, insert this node to the degree node list
            available_nodes.push_back(node_i);
        }
    }
}

/**
 * Algorithm of Least Constraining Value:
 * --------------------------------------
 * We are trying to assign value for variable "o", available values for "o" is 0-9
 *
 * sums = {0:0, 1:0, 2:0, 3:0, 4:0, 5:0, 6:0, 7:0, 8:0, 9:0}
 * For i from 0 to 9:
 *  plug "o=i" into the constraint formulas
 *  For each neighbor "N" of "o" in the constraint graph:
 *      sums[i] += the number of values remaining for "N"
 *
 * It picks "i" so that:
 * sums[i] = MAX{sums[i] | for all "i" that is a member of "O",s valid values}
 *
 * @param node_i is the node for whom we will find the LCV
 * @param lcv_count will hold the LCV count of the available colors
 * */
// Least constraining value - Return colors which used much
void MapColorBase::lcv(int node_i, map<int, int> &lcv_count) {
    int neighbors = c_graph[node_i].size();

    // retrieving available colors for node_i
    for(int color=0; color<num_color; color+=1) {
        // this color is available in the domain of node_i
        if(IS_SET(color_domain[node_i], color)) {
            lcv_count[color] = 0;

            // looping over neighbors of node_i
            for(int j=0; j<neighbors; j+=1) {
                int node_j = c_graph[node_i][j];

                // color is not assigned to neighbor node_j
                if(color_assigned[node_j] == COLOR_UNASSIGNED) {
                    // get available color count of the node_j
                    int curr_count = utils::count_set_bit(color_domain[node_j]);
                    // this color is available in the domain of node_j,
                    // so reduce the count considering this color will be assigned to node_i
                    if(IS_SET(color_domain[node_j], color)) curr_count -= 1;

                    lcv_count[color] += curr_count;
                }
            }
        }
    }
}

// Prepare list of available color for node_i
void MapColorBase::prepare_color_queue(int node_i, priority_queue<pair<int, int> > &pq) {
    map<int, int> color_map;

    // if lcv heuristic is available
    if(try_lcv) {
        // retrieving available colors with proper LCV count
        lcv(node_i, color_map);
    }
    else {
        // retrieving available colors for node_i
        for(int color=0; color<num_color; color+=1) {
            if(IS_SET(color_domain[node_i], color)) color_map[color] = 0;
        }
    }

    // iterating over map and insert value to the priority_queue
    map<int, int>::iterator itr;
    for(itr = color_map.begin(); itr != color_map.end(); ++itr) {
        // first element of the priority queue element will hold the LCV count
        pq.push(make_pair(itr->second, itr->first));
    }
}

/* getter/setter */
int MapColorBase::get_num_color() {
    return num_color;
}

void MapColorBase::set_num_color(int num_color_) {
    num_color = num_color_;
}

int MapColorBase::get_num_nodes() {
    return num_node;
}

void MapColorBase::set_num_nodes(int num_node_) {
    num_node = num_node_;
}

void MapColorBase::set_heuristics(bool try_mrv_, bool try_degree_c_, bool try_lcv_) {
    try_mrv = try_mrv_;
    try_degree_c = try_degree_c_;
    try_lcv = try_lcv_;
}

#endif //MAPCOLOR_BASE_H