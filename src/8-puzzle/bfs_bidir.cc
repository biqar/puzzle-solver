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

#define DEPTH_ONE 1

class BfsBidirEightPuzzle : public Solver {
public:
    BfsBidirEightPuzzle(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path) {
        BfsBidirEightPuzzle::init(_initial_state, _goal_state, _heuristic, _print_path);
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

    std::queue<Node *> initial_to_goal_q;
    std::queue<Node *> goal_to_initial_q;
    std::map<long long int, bool> initial_to_goal_m;
    std::map<long long int, bool> goal_to_initial_m;
    bool solution_found;
    int node_expanded;
    int node_generated;

    void initial_to_goal_bfs(int depth);
    void goal_to_initial_bfs(int depth);
};

int BfsBidirEightPuzzle::init(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path) {
    goal_state = _goal_state;
    initial_state = _initial_state;
    heuristic = _heuristic;
    is_print_path = _print_path;

    Node *initial_node = create_new_node(0, heuristic->guess_distance(initial_state, goal_state), NULL, initial_state);
    initial_to_goal_q.push(initial_node);
    long long int initial_state_key = construct_board_key(initial_state);
    initial_to_goal_m[initial_state_key] = true;

    Node *goal_node = create_new_node(0, heuristic->guess_distance(goal_state, initial_state), NULL, goal_state);
    goal_to_initial_q.push(goal_node);
    long long int goal_state_key = construct_board_key(goal_state);
    goal_to_initial_m[goal_state_key] = true;

    solution_found = false;
    node_expanded = 0;
    node_generated = 2;

    return 1;
}

void BfsBidirEightPuzzle::goal_to_initial_bfs(int depth) {
    while(!goal_to_initial_q.empty()) {
        Node *current_node = goal_to_initial_q.front();
        if(current_node->depth >= depth) {
            return initial_to_goal_bfs(depth + 1);
        }

        goal_to_initial_q.pop();
        node_expanded += 1;

//        printf("current node depth: %d\n", current_node->depth);
//        print_board(current_node->state);

        std::list<Node *> child_list = expand_node(current_node, goal_state, heuristic);
        for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
            long long int child_state_key = construct_board_key((*it)->state);
            if(initial_to_goal_m.find(child_state_key) != initial_to_goal_m.end()) {
                printf("[%s] solution found!\n", __func__);
                solution_found = true;
                return;
            }

            if(goal_to_initial_m.find(child_state_key) == goal_to_initial_m.end()) {
                goal_to_initial_m[child_state_key] = true;
                node_generated += 1;
                goal_to_initial_q.push(*it);
            }
        }
    }
}

void BfsBidirEightPuzzle::initial_to_goal_bfs(int depth) {
    while(!initial_to_goal_q.empty()) {
        Node *current_node = initial_to_goal_q.front();
        if(current_node->depth >= depth) {
            return goal_to_initial_bfs(depth);
        }

        initial_to_goal_q.pop();
        node_expanded += 1;

//        printf("current node depth: %d\n", current_node->depth);
//        print_board(current_node->state);

        std::list<Node *> child_list = expand_node(current_node, goal_state, heuristic);
        for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
            long long int child_state_key = construct_board_key((*it)->state);
            if(goal_to_initial_m.find(child_state_key) != goal_to_initial_m.end()) {
                printf("[%s] solution found!\n", __func__);
                solution_found = true;
                return;
            }

            if(initial_to_goal_m.find(child_state_key) == initial_to_goal_m.end()) {
                initial_to_goal_m[child_state_key] = true;
                node_generated += 1;
                initial_to_goal_q.push(*it);
            }
        }
    }
}

int BfsBidirEightPuzzle::run() {
    if(equal_state(initial_state, goal_state)) {
        printf("solution found!\n");
        if(is_print_path) print_board(initial_state);
        printf("[8-puzzle] [bfs-bidir] generated_nodes: [%d], expanded_node: [%d]\n", node_generated, node_expanded);
        return 1;
    }

    initial_to_goal_bfs(DEPTH_ONE);
    printf("[8-puzzle] [bfs-bidir] generated_nodes: [%d], expanded_node: [%d]\n", node_generated, node_expanded);
    return 1;
}

void BfsBidirEightPuzzle::destroy() {
    //
}