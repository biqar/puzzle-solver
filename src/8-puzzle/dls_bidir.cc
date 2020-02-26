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

#define MAX_DEPTH 20

class DlsBidirEightPuzzle : public Solver {
public:
    DlsBidirEightPuzzle(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path) {
        DlsBidirEightPuzzle::init(_initial_state, _goal_state, _heuristic, _print_path);
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

    std::map<long long int, bool> forward_m;
    std::map<long long int, bool> backward_m;
    int node_expanded;
    int node_generated;
    bool is_found;

    void run_dls_backward(Node *current_node);

    void run_dls_forward(Node *current_node);
};

int DlsBidirEightPuzzle::init(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path) {
    goal_state = _goal_state;
    initial_state = _initial_state;
    heuristic = _heuristic;
    is_print_path = _print_path;

    forward_m[construct_board_key(initial_state)] = true;
    backward_m[construct_board_key(goal_state)] = true;

    node_expanded = 0;
    node_generated = 1;
    is_found = false;

    return 1;
}

void DlsBidirEightPuzzle::run_dls_backward(Node *current_node) {
//    printf("current node depth: %d\n", current_node->depth);
//    print_board(current_node->state);

    if(current_node->depth > MAX_DEPTH) return;

    long long int current_state_key = construct_board_key(current_node->state);
    if(forward_m.find(current_state_key) != forward_m.end()) {
        printf("[%s] solution found!\n", __func__);
        is_found = true;
        return;
    }
    std::list<Node *> child_list = expand_node(current_node, goal_state, heuristic);
    node_generated += child_list.size();
    node_expanded += 1;
    for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
        long long int child_state_key = construct_board_key((*it)->state);
        if(backward_m.find(child_state_key) == backward_m.end()) {
            backward_m[child_state_key] = true;
            run_dls_backward(*it);
            if(is_found) return;
        }
    }
}

void DlsBidirEightPuzzle::run_dls_forward(Node *current_node) {
//    printf("current node depth: %d\n", current_node->depth);
//    print_board(current_node->state);

    if(current_node->depth > MAX_DEPTH) return;

    if(equal_state(current_node->state, goal_state)) {
        printf("[%s] solution found!\n", __func__);
        is_found = true;
        return;
    }

    std::list<Node *> child_list = expand_node(current_node, goal_state, heuristic);
    node_generated += child_list.size();
    node_expanded += 1;
    for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
        long long int child_state_key = construct_board_key((*it)->state);
        if(forward_m.find(child_state_key) == forward_m.end()) {
            forward_m[child_state_key] = true;
            run_dls_forward(*it);
            if(is_found) return;
        }
    }
}

int DlsBidirEightPuzzle::run() {
    run_dls_forward(create_new_node(0, heuristic->guess_distance(initial_state, goal_state), NULL, initial_state));
    if(!is_found) {
        node_generated += 1;
        run_dls_backward(create_new_node(0, heuristic->guess_distance(goal_state, initial_state), NULL, goal_state));
    }

    printf("[8-puzzle] [dls-bidir] generated_nodes: [%d], expanded_node: [%d]\n", node_generated, node_expanded);
    return 1;
}

void DlsBidirEightPuzzle::destroy() {
    //
}