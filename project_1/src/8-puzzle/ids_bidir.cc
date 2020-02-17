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
    IdsBidirEightPuzzle(State *_initial_state, State *_goal_state, Heuristic *_heuristic) {
        IdsBidirEightPuzzle::init(_initial_state, _goal_state, _heuristic);
    }

    int init(State *_initial_state, State *_goal_state, Heuristic *_heuristic);

    int run();

    void destroy();

private:
    /* Private Data */
    State *goal_state;
    State *initial_state;
    std::map<long long int, int> initial_to_goal_m;
    std::map<long long int, int> goal_to_initial_m;
    bool solution_found;
    int node_expanded;
    Heuristic *heuristic;

    bool initial_to_goal_dls(Node *current_node, int depth_limit);

    bool goal_to_initial_dls(Node *current_node, int depth_limit);

    void run_iddfs_bidir();
};

int IdsBidirEightPuzzle::init(State *_initial_state, State *_goal_state, Heuristic *_heuristic) {
    goal_state = _goal_state;
    initial_state = _initial_state;
    heuristic = _heuristic;

    return 1;
}

bool IdsBidirEightPuzzle::initial_to_goal_dls(Node *current_node, int depth_limit) {
    //printf("current node depth: %d\n", current_node->depth);
    //printf("board_key: %lld\n", construct_board_key(current_node->state));
    //print_board(current_node->state);

    if(current_node->depth > IDS_BIDIR_MAX_DEPTH) return false;

    if(equal_state(current_node->state, goal_state)) {
        printf("found solution by expending [%d] nodes\n", node_expanded);
        return true;
    }
    std::list<Node *> child_list = expand_node(current_node, goal_state, heuristic);
    node_expanded += 1;
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

    if(equal_state(current_node->state, initial_state)) {
        printf("found solution by expending [%d] nodes\n", node_expanded);
        return true;
    }

    long long int current_state_key = construct_board_key(current_node->state);
    if(initial_to_goal_m.find(current_state_key) != initial_to_goal_m.end()) {
        printf("found solution by expending [%d] nodes\n", node_expanded);
        return true;
    }

    std::list<Node *> child_list = expand_node(current_node, goal_state, heuristic);
    node_expanded += 1;
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
        node_expanded = 0;

        initial_to_goal_m[initial_state_key] = 0;
        if(initial_to_goal_dls(create_new_node(0, heuristic->guess_distance(initial_state, goal_state), NULL, initial_state), depth)) {
            printf("found solution by expending [%d] nodes at depth: %d\n", node_expanded, initial_to_goal_m[goal_state_key]);
            break;
        }
        goal_to_initial_m[goal_state_key] = 0;
        if(goal_to_initial_dls(create_new_node(0, heuristic->guess_distance(goal_state, initial_state), NULL, goal_state), depth)) {
            //todo: need to fix the depth here ...
            printf("found solution by expending [%d] nodes at depth: %d\n", node_expanded, goal_to_initial_m[initial_state_key]);
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