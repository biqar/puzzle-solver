//
// Created by aislam6 on 1/29/20.
//

#include "node.h"
#include "state.h"

#include <stdio.h>
#include <queue>
#include <list>
#include <map>

#define MAX_DEPTH 400

State *goal_state;
State *initial_state;
std::map <long long int, bool> m;
int node_expanded;

bool run_dls(Node *current_node, int depth_limit) {
    //printf("current node depth: %d\n", current_node->depth);
    //printf("board_key: %lld\n", construct_board_key(current_node->state));
    //print_board(current_node->state);

    if(current_node->depth > MAX_DEPTH) return false;

    if(equal_state(current_node->state, goal_state)) {
        printf("found solution by expending [%d] nodes\n", node_expanded);
        return true;
    }
    std::list<Node *> child_list = expand_node(current_node, goal_state);
    node_expanded += 1;
    for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
        long long int child_state_key = construct_board_key((*it)->state);
        if(m.find(child_state_key) == m.end()) {
            m[child_state_key] = true;
            bool res = run_dls(*it, depth_limit);
            if(res) return res;
        }
    }
    return false;
}

void run_iddfs() {
    for(int depth=0; depth < MAX_DEPTH; depth+=1) {
        m.clear();
        m[construct_board_key(initial_state)] = true;
        node_expanded = 0;
        if(run_dls(create_new_node(0, calculate_manhattan_distance(initial_state, goal_state), NULL, initial_state), depth)) {
            printf("found solution by expending [%d] nodes at depth: %d\n", node_expanded, depth);
            break;
        }
    }
}

int main() {
    goal_state = construct_goal_state();
    initial_state = construct_initial_state();
    run_iddfs();
    return 0;
}