//
// Created by aislam6 on 1/29/20.
//

#include "node.h"
#include "state.h"

#include <stdio.h>
#include <stack>
#include <list>
#include <map>

State *goal_state;
State *initial_state;
std::map <long long int, bool> m;
int node_expanded;

void run_dfs_stack() {
    std::stack<Node *> s;
    s.push(create_new_node(0, calculate_manhattan_distance(initial_state, goal_state), NULL, initial_state));
    m[construct_board_key(initial_state)] = true;

    while(!s.empty()) {
        Node *current_node = s.top(); s.pop();

        //printf("current node depth: %d\n", current_node->depth);
        //printf("board_key: %lld\n", construct_board_key(current_node->state));
        //print_board(current_node->state);

        //if(node_expanded > 400) return;

        if(equal_state(current_node->state, goal_state)) {
            printf("found solution by expending [%d] nodes\n", node_expanded);
            break;
        }
        std::list<Node *> child_list = expand_node(current_node, goal_state);
        node_expanded += 1;
        for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
            long long int child_state_key = construct_board_key((*it)->state);
            if(m.find(child_state_key) == m.end()) {
                m[child_state_key] = true;
                s.push(*it);
            }
        }
    }
}

int main() {
    goal_state = construct_goal_state();
    initial_state = construct_initial_state();
    node_expanded = 0;
    run_dfs_stack();

    return 0;
}