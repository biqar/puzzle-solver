//
// Created by aislam6 on 1/29/20.
//

#include "core/node.h"
#include "core/state.h"
#include "../core/heuristic.h"

#include <stdio.h>
#include <queue>
#include <list>

class BfsEightPuzzle : public Solver {
public:
    BfsEightPuzzle(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path) {
        BfsEightPuzzle::init(_initial_state, _goal_state, _heuristic, _print_path);
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

    std::queue<Node *> q;
    std::map<long long int, bool> m;        //mapping already generated nodes
    int node_expanded;
    int node_generated;

    void run_bfs();
};

int BfsEightPuzzle::init(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path) {
    goal_state = _goal_state;
    initial_state = _initial_state;
    heuristic = _heuristic;
    is_print_path = _print_path;

    q.push(create_new_node(0, heuristic->guess_distance(new EightPuzzleHeuristicParam(initial_state, goal_state)), NULL, initial_state));
    m[construct_board_key(initial_state)] = true;

    node_expanded = 0;
    node_generated = 1;

    return 1;
}

void BfsEightPuzzle::run_bfs() {
    while(!q.empty()) {
        Node *current_node = q.front(); q.pop();
        node_expanded += 1;

        //printf("current node depth: %d\n", current_node->depth);
        //print_board(current_node->state); printf("\n");

        if(equal_state(current_node->state, goal_state)) {
            printf("solution found!\n");
            if(is_print_path) print_path(current_node);
            break;
        }
        std::list<Node *> child_list = expand_node(current_node, goal_state, heuristic);
        for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
            long long int child_node_key = construct_board_key((*it)->state);
            if(m.find(child_node_key) == m.end()) {
                m[child_node_key] = true;
                q.push(*it);
                node_generated += 1;
            }
        }
    }
}

int BfsEightPuzzle::run() {
    run_bfs();
    printf("[8-puzzle] [bfs] generated_nodes: [%d], expanded_node: [%d]\n", node_generated, node_expanded);
    return 1;
}

void BfsEightPuzzle::destroy() {
    //
}