//
// Created by aislam6 on 1/29/20.
//

#include "../core/node.h"
#include "../core/state.h"
#include "../core/heuristic.h"

#include <stdio.h>
#include <queue>
#include <list>
#include <map>

#define IDS_MAX_DEPTH 40

class IdsEightPuzzle : public Solver {
public:
    IdsEightPuzzle(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path) {
        IdsEightPuzzle::init(_initial_state, _goal_state, _heuristic, _print_path);
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

    bool run_dls(Node *current_node, int depth_limit);

    void run_iddfs();
};

int IdsEightPuzzle::init(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path) {
    goal_state = _goal_state;
    initial_state = _initial_state;
    heuristic = _heuristic;
    is_print_path = _print_path;

    node_expanded = 0;
    node_generated = 0;

    return 1;
}

bool IdsEightPuzzle::run_dls(Node *current_node, int depth_limit) {
//    printf("depth_limit: %d\n", depth_limit);
//    printf("current node depth: %d\n", current_node->depth);
//    print_board(current_node->state); printf("\n");

    if(current_node->depth > IDS_MAX_DEPTH) return false;

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
            bool res = run_dls(*it, depth_limit);
            if(res) return res;
        }
    }
    return false;
}

void IdsEightPuzzle::run_iddfs() {
    for(int depth=0; depth < IDS_MAX_DEPTH; depth+=1) {
        m.clear();
        m[construct_board_key(initial_state)] = true;
        node_generated += 1;
        if(run_dls(create_new_node(0, heuristic->guess_distance(initial_state, goal_state), NULL, initial_state), depth)) {
//            printf("found solution by expending [%d] nodes at depth: %d\n", node_expanded, depth);
            printf("[8-puzzle] [ids] generated_nodes: [%d], expanded_node: [%d]\n", node_generated, node_expanded);
            break;
        }
    }
}

int IdsEightPuzzle::run() {
    run_iddfs();
    return 1;
}

void IdsEightPuzzle::destroy() {
    //
}