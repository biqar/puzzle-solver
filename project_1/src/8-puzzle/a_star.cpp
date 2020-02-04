//
// Created by aislam6 on 1/29/20.
//

#include "../core/node.h"
#include "../core/state.h"

#include <stdio.h>
#include <queue>
#include <list>

State *goal_state;
State *initial_state;

bool comp(Node *a, Node *b) {
    return (get_total_cost(a) < get_total_cost(b));
}

void run_astar() {
    int node_expanded = 0;
    std::queue<Node *> q;
    q.push(create_new_node(0, calculate_manhattan_distance(initial_state, goal_state), NULL, initial_state));

    while(!q.empty()) {
        Node *current_node = q.front(); q.pop();

        printf("current node depth: %d\n", current_node->depth);
        print_board(current_node->state);

        if(equal_state(current_node->state, goal_state)) {
            printf("solution found!");
            break;
        }
        std::list<Node *> child_list = expand_node(current_node, goal_state);
        node_expanded += 1;
        child_list.sort(comp);
        for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
            q.push(*it);
        }

        //if(node_expand > 20) break;
    }
    printf("found solution by expending [%d] nodes\n", node_expanded);
}

int main() {
    goal_state = construct_goal_state();
    initial_state = construct_initial_state();
    run_astar();
    return 0;
}