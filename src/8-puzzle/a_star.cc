//
// Created by aislam6 on 1/29/20.
//

#include "../core/node.h"
#include "../core/state.h"
#include "../core/solver.h"
#include "../core/heuristic.h"

#include <stdio.h>
#include <queue>
#include <map>
#include <list>

class AStarEightPuzzle : public Solver {
public:
    AStarEightPuzzle(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path) {
        AStarEightPuzzle::init(_initial_state, _goal_state, _heuristic, _print_path);
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

    std::priority_queue<Node *, vector<Node *>, NodeComparatorOnTotalCost> q;
    std::map<long long int, bool> m;        //mapping already explored nodes
    int node_expanded;
    int node_generated;

    void run_astar();
};

int AStarEightPuzzle::init(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path) {
    goal_state = _goal_state;
    initial_state = _initial_state;
    heuristic = _heuristic;
    is_print_path = _print_path;

    node_expanded = 0;
    node_generated = 1;
    q.push(create_new_node(0, heuristic->guess_distance(initial_state, goal_state), NULL, initial_state));

    return 1;
}

void AStarEightPuzzle::run_astar() {
    if(equal_state(initial_state, goal_state)) {
        printf("solution found!\n");
        if(is_print_path) print_board(initial_state);
        return;
    }
    while(!q.empty()) {
        Node *current_node = q.top(); q.pop();

//        printf("current node depth: %d\n", current_node->depth);
//        print_board(current_node->state);

        long long int current_node_key = construct_board_key(current_node->state);
        if(m.find(current_node_key) != m.end()) {
            continue;
        }
        node_expanded += 1;

        std::list<Node *> child_list = expand_node(current_node, goal_state, heuristic);
        for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
            if(equal_state((*it)->state, goal_state)) {
                printf("solution found!\n");
                if(is_print_path) print_path(*it);
                return;
            }

            long long int child_node_key = construct_board_key((*it)->state);
            if(m.find(child_node_key) == m.end()) {
                q.push(*it);
                node_generated += 1;
            }
        }
        m[current_node_key] = true;
    }
}

int AStarEightPuzzle::run() {
    run_astar();
    printf("[8-puzzle] [A-Star] generated_nodes: [%d], expanded_node: [%d]\n", node_generated, node_expanded);
    return 1;
}

void AStarEightPuzzle::destroy() {
    //
}