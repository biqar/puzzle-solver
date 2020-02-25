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

#define IDS_BIDIR_MAX_DEPTH 400

class IdsBidirEightPuzzle : public Solver {
public:
    IdsBidirEightPuzzle(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path) {
        IdsBidirEightPuzzle::init(_initial_state, _goal_state, _heuristic, _print_path);
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

    std::map<long long int, int> initial_to_goal_m;
    std::map<long long int, int> goal_to_initial_m;
    int node_expanded;
    int node_generated;

    bool initial_to_goal_dls(Node *current_node, int depth_limit);

    bool goal_to_initial_dls(Node *current_node, int depth_limit);

    void run_iddfs_bidir();
};

int IdsBidirEightPuzzle::init(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path) {
    goal_state = _goal_state;
    initial_state = _initial_state;
    heuristic = _heuristic;
    is_print_path = _print_path;

    node_expanded = 0;
    node_generated = 0;

    return 1;
}

bool IdsBidirEightPuzzle::initial_to_goal_dls(Node *current_node, int depth_limit) {
//    printf("current node depth: %d\n", current_node->depth);
//    print_board(current_node->state);

    if(current_node->depth > IDS_BIDIR_MAX_DEPTH) return false;

    if(equal_state(current_node->state, goal_state)) {
        printf("[%s] solution found!\n", __func__);
        return true;
    }
    std::list<Node *> child_list = expand_node(current_node, goal_state, heuristic);
    node_expanded += 1;
    node_generated += child_list.size();
    for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
        long long int child_state_key = construct_board_key((*it)->state);
        if(initial_to_goal_m.find(child_state_key) == initial_to_goal_m.end()) {
            initial_to_goal_m[child_state_key] = current_node->depth + 1;
            bool res = initial_to_goal_dls(*it, depth_limit);
            if(res) return res;
        }
    }
    return false;
}

bool IdsBidirEightPuzzle::goal_to_initial_dls(Node *current_node, int depth_limit) {
    //printf("current node depth: %d\n", current_node->depth);
    //printf("board_key: %lld\n", construct_board_key(current_node->state));
    //print_board(current_node->state);

    if(current_node->depth > IDS_BIDIR_MAX_DEPTH) return false;

    long long int current_state_key = construct_board_key(current_node->state);
    if(initial_to_goal_m.find(current_state_key) != initial_to_goal_m.end()) {
        printf("[%s] solution found!\n", __func__);
        return true;
    }

    std::list<Node *> child_list = expand_node(current_node, goal_state, heuristic);
    node_expanded += 1;
    node_generated += child_list.size();
    for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
        long long int child_state_key = construct_board_key((*it)->state);
        if(goal_to_initial_m.find(child_state_key) == goal_to_initial_m.end()) {
            goal_to_initial_m[child_state_key] = current_node->depth + 1;
            bool res = goal_to_initial_dls(*it, depth_limit);
            if(res) return res;
        }
    }
    return false;
}

void IdsBidirEightPuzzle::run_iddfs_bidir() {
    long long int initial_state_key = construct_board_key(initial_state);
    long long int goal_state_key = construct_board_key(goal_state);
    for(int depth=0; depth < IDS_BIDIR_MAX_DEPTH; depth+=1) {
        initial_to_goal_m.clear();
        goal_to_initial_m.clear();
        node_generated += 1;

        initial_to_goal_m[initial_state_key] = 0;
        if(initial_to_goal_dls(create_new_node(0, heuristic->guess_distance(initial_state, goal_state), NULL, initial_state), depth)) {
//            printf("found solution by expending [%d] nodes at depth: %d\n", node_expanded, initial_to_goal_m[goal_state_key]);
            printf("[8-puzzle] [ids-bidir] generated_nodes: [%d], expanded_node: [%d]\n", node_generated, node_expanded);
            break;
        }
        goal_to_initial_m[goal_state_key] = 0;
        if(goal_to_initial_dls(create_new_node(0, heuristic->guess_distance(goal_state, initial_state), NULL, goal_state), depth)) {
            //todo: need to fix the depth here ...
//            printf("found solution by expending [%d] nodes at depth: %d\n", node_expanded, goal_to_initial_m[initial_state_key]);
            printf("[8-puzzle] [ids-bidir] generated_nodes: [%d], expanded_node: [%d]\n", node_generated, node_expanded);
            break;
        }
    }
}

int IdsBidirEightPuzzle::run() {
    run_iddfs_bidir();
    return 1;
}

void IdsBidirEightPuzzle::destroy() {
    //
}