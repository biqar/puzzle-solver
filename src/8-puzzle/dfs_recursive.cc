//
// Created by aislam6 on 1/29/20.
//

#include "../core/node.h"
#include "../core/state.h"
#include "../core/heuristic.h"

#include <stdio.h>
#include <stack>
#include <list>
#include <map>

class DfsRecursivEightPuzzle : public Solver {
public:
    DfsRecursivEightPuzzle(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path) {
        DfsRecursivEightPuzzle::init(_initial_state, _goal_state, _heuristic, _print_path);
    }

    int init(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path);

    int run();

    void destroy();

private:
    /* Private Data */
    State *goal_state;
    State *initial_state;
    Heuristic *heuristic;
    bool is_print_path = false;

    std::map<long long int, bool> m;
    int node_expanded;
    int node_generated;

    bool run_dfs_recursive(Node *current_node);
};

int DfsRecursivEightPuzzle::init(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path) {
    goal_state = _goal_state;
    initial_state = _initial_state;
    heuristic = _heuristic;
    is_print_path = _print_path;

    node_expanded = 0;
    node_generated = 1;
    m[construct_board_key(initial_state)] = true;

    return 1;
}

bool DfsRecursivEightPuzzle::run_dfs_recursive(Node *current_node) {
    if(equal_state(current_node->state, goal_state)) {
        printf("solution found!\n");
        return true;
    }

    std::list<Node *> child_list = expand_node(current_node, goal_state, heuristic);
    node_expanded += 1;
    node_generated += child_list.size();
    for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
        long long int child_state_key = construct_board_key((*it)->state);
        if(m.find(child_state_key) == m.end()) {
            m[child_state_key] = true;
            bool ret = run_dfs_recursive(*it);
            if(ret) return ret;
        }
    }
    return false;
}

int DfsRecursivEightPuzzle::run() {
    run_dfs_recursive(create_new_node(0, heuristic->guess_distance(initial_state, goal_state), NULL, initial_state));
    printf("[8-puzzle] [dfs-recursive] generated_nodes: [%d], expanded_node: [%d]\n", node_generated, node_expanded);
    return 1;
}

void DfsRecursivEightPuzzle::destroy() {
    //
}