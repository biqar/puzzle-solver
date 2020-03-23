//
// Created by aislam6 on 1/29/20.
//

#include "core/node.h"
#include "core/state.h"
#include "../core/heuristic.h"

#include <stdio.h>
#include <stack>
#include <list>
#include <map>

class DfsStackEightPuzzle : public Solver {
public:
    DfsStackEightPuzzle(void *_parameter) {
        DfsStackEightPuzzle::init(_parameter);
    }

    int init(void *_parameter);

    int run();

    void destroy();

private:
    /* Private Data */
    State *goal_state;
    State *initial_state;
    Heuristic *heuristic;
    bool is_print_path = false;

    std::map<long long int, bool> m;
    std::stack<Node *> s;
    int node_expanded;
    int node_generated;

    void run_dfs_stack();
};

int DfsStackEightPuzzle::init(void *_parameter) {
    goal_state = ((EightPuzzleInitParam *)_parameter)->_goal_state;
    initial_state = ((EightPuzzleInitParam *)_parameter)->_initial_state;
    heuristic = ((EightPuzzleInitParam *)_parameter)->_heuristic;
    is_print_path = ((EightPuzzleInitParam *)_parameter)->_print_path;

    s.push(create_new_node(0, heuristic->guess_distance(new EightPuzzleHeuristicParam(initial_state, goal_state)), NULL, initial_state));
    m[construct_board_key(initial_state)] = true;

    node_expanded = 0;
    node_generated = 0;

    return 1;
}

void DfsStackEightPuzzle::run_dfs_stack() {
    if(equal_state(initial_state, goal_state)) {
        printf("solution found!\n");
        if(is_print_path) print_board(initial_state);
        printf("\n");
        return;
    }

    while(!s.empty()) {
        Node *current_node = s.top(); s.pop();
        node_expanded += 1;

//        printf("current node depth: %d\n", current_node->depth);
//        print_board(current_node->state); printf("\n");

        std::list<Node *> child_list = expand_node(current_node, goal_state, heuristic);
        for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
            long long int child_state_key = construct_board_key((*it)->state);
            if(equal_state((*it)->state, goal_state)) {
                printf("solution found!\n");
                return;
            }
            if(m.find(child_state_key) == m.end()) {
                node_generated += 1;
                m[child_state_key] = true;
                s.push(*it);
            }
        }
    }
}

int DfsStackEightPuzzle::run() {
    run_dfs_stack();
    printf("[8-puzzle] [dfs-stack] generated_nodes: [%d], expanded_node: [%d]\n", node_generated, node_expanded);
    return 1;
}

void DfsStackEightPuzzle::destroy() {
    //
}