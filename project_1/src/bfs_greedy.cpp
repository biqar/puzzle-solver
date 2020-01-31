//
// Created by aislam6 on 1/29/20.
//

#include "node.h"
#include "state.h"

#include <stdio.h>
#include <queue>
#include <vector>
#include <map>
#include <list>

State *goal_state;
State *initial_state;
std::map <long long int, bool> m;

struct comp {
    bool operator() (Node *a, Node *b) {
        return a->h_cost > b->h_cost;
    }
};

std::priority_queue< Node *, std::vector< Node * >, comp > Q;

void run_bfs_greedy() {
    int node_expanded = 0;
    Q.push(create_new_node(0, calculate_manhattan_distance(initial_state, goal_state), NULL, initial_state));

    while(!Q.empty()) {
        Node *current_node = Q.top(); Q.pop();

        long long int current_state_key = construct_board_key(current_node->state);
        if(m.find(current_state_key) != m.end()) {
            continue;
        }

        printf("current node depth: %d\n", current_node->depth);
        print_board(current_node->state);

        if(equal_state(current_node->state, goal_state)) {
            printf("solution found!");
            break;
        }
        std::list<Node *> child_list = expand_node(current_node, goal_state);
        node_expanded += 1;
        for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
            long long int child_state_key = construct_board_key((*it)->state);
            if(m.find(child_state_key) == m.end()) {
                Q.push(*it);
            }
        }

        m[current_state_key] = true;
        //if(node_expand > 20) break;
    }
    printf("found solution by expending [%d] nodes\n", node_expanded);
}

int main() {
    goal_state = construct_goal_state();
    initial_state = construct_initial_state();
    run_bfs_greedy();
    return 0;
}