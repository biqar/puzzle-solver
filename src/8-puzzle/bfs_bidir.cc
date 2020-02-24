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
    BfsBidirEightPuzzle(State *_initial_state, State *_goal_state, Heuristic *_heuristic) {
        BfsBidirEightPuzzle::init(_initial_state, _goal_state, _heuristic);
    }

    int init(State *_initial_state, State *_goal_state, Heuristic *_heuristic);

    int run();

    void destroy();

private:
    /* Private Data */
    State *goal_state;
    State *initial_state;
    std::queue<Node *> initial_to_goal_q;
    std::queue<Node *> goal_to_initial_q;
    std::map<long long int, int> initial_to_goal_m;
    std::map<long long int, int> goal_to_initial_m;
    bool solution_found;
    int node_expanded;
    Heuristic *heuristic;

    void initial_to_goal_bfs(int depth);
    void goal_to_initial_bfs(int depth);
};

int BfsBidirEightPuzzle::init(State *_initial_state, State *_goal_state, Heuristic *_heuristic) {
    goal_state = _goal_state;
    initial_state = _initial_state;
    heuristic = _heuristic;

    Node *initial_node = create_new_node(0, heuristic->guess_distance(initial_state, goal_state), NULL, initial_state);
    Node *goal_node = create_new_node(0, heuristic->guess_distance(goal_state, initial_state), NULL, goal_state);

    initial_to_goal_q.push(initial_node);
    long long int initial_state_key = construct_board_key(initial_state);
    initial_to_goal_m[initial_state_key] = 0;

    goal_to_initial_q.push(goal_node);
    long long int goal_state_key = construct_board_key(goal_state);
    goal_to_initial_m[goal_state_key] = 0;

    solution_found = false;
    node_expanded = 0;

    return 1;
}

void BfsBidirEightPuzzle::goal_to_initial_bfs(int depth) {
    while(!goal_to_initial_q.empty()) {
        Node *current_node = goal_to_initial_q.front();
        if(current_node->depth >= depth) {
            return initial_to_goal_bfs(depth + 1);
        }

        goal_to_initial_q.pop();
//        printf("current node depth: %d\n", current_node->depth);
//        print_board(current_node->state);

        if(solution_found) {
            printf("[%s] found solution by expending [%d] nodes\n", __func__, node_expanded);
            return;
        }

        long long int current_state_key = construct_board_key(current_node->state);
        if(initial_to_goal_m.find(current_state_key) != initial_to_goal_m.end()) {
            printf("[%s] found solution by expending [%d] nodes\n", __func__, node_expanded);
            solution_found = true;
            return;
        }
        std::list<Node *> child_list = expand_node(current_node, goal_state, heuristic);
        node_expanded += 1;
        for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
            long long int child_state_key = construct_board_key((*it)->state);
            if(goal_to_initial_m.find(child_state_key) == goal_to_initial_m.end()) {
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
//        printf("current node depth: %d\n", current_node->depth);
//        print_board(current_node->state);

        if(solution_found) {
            printf("[%s] found solution by expending [%d] nodes\n", __func__, node_expanded);
            return;
        }

        long long int current_state_key = construct_board_key(current_node->state);
        if(goal_to_initial_m.find(current_state_key) != goal_to_initial_m.end()) {
            printf("[%s] found solution by expending [%d] nodes\n", __func__, node_expanded);
            solution_found = true;
            return;
        }
        std::list<Node *> child_list = expand_node(current_node, goal_state, heuristic);
        node_expanded += 1;
        for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
            long long int child_state_key = construct_board_key((*it)->state);
            if(initial_to_goal_m.find(child_state_key) == initial_to_goal_m.end()) {
                initial_to_goal_q.push(*it);
            }
        }
    }
}

int BfsBidirEightPuzzle::run() {
    initial_to_goal_bfs(DEPTH_ONE);
    return 1;
}

void BfsBidirEightPuzzle::destroy() {
    //
}