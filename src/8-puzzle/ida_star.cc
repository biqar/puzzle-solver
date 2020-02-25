//
// Created by aislam6 on 1/29/20.
//

#include "../core/node.h"
#include "../core/state.h"
#include "../utill/utills.h"
#include "../core/heuristic.h"

#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <list>

#define INF (1 << 28)

class IdaStarEightPuzzle : public Solver {
public:
    IdaStarEightPuzzle(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path) {
        IdaStarEightPuzzle::init(_initial_state, _goal_state, _heuristic, _print_path);
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

    bool is_found;
    int node_expanded;
    int node_generated;

    void ida_star();

    int run_astar(int max_cost, Node *current_node);
};

int IdaStarEightPuzzle::init(State *_initial_state, State *_goal_state, Heuristic *_heuristic, bool _print_path) {
    goal_state = _goal_state;
    initial_state = _initial_state;
    heuristic = _heuristic;
    is_print_path = _print_path;

    return 1;
}

bool comp(Node *a, Node *b) {
    return (get_total_cost(a) < get_total_cost(b));
}

int IdaStarEightPuzzle::run_astar(int max_cost, Node *current_node) {
    int current_node_total_cost = get_total_cost(current_node);

//    printf("current node depth: %d\n", current_node->depth);
//    print_board(current_node->state);

    if(equal_state(current_node->state, goal_state)) {
        printf("solution found!");
        is_found = true;
        return current_node_total_cost;
    }

    if(current_node_total_cost > max_cost) {
        return current_node_total_cost;
    }

    std::list<Node *> child_list = expand_node(current_node, goal_state, heuristic);
    node_expanded += 1;
    int ret = INF;
    //child_list.sort(comp);
    for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
        node_generated += 1;
        ret = utils::_min(ret, run_astar(max_cost, *it));

        if(is_found) return ret;
    }
    return ret;
}

void IdaStarEightPuzzle::ida_star() {
    int bound = heuristic->guess_distance(initial_state, goal_state);
    int initial_goal_hval = bound;
    is_found = false;
    node_expanded = 0;
    node_generated = 0;

    while(true) {
        node_generated += 1;
        int ret = run_astar(bound, create_new_node(0, initial_goal_hval, NULL, initial_state));

        if(is_found) {
            printf("[8-puzzle] [IDA-Star] generated_nodes: [%d], expanded_node: [%d]\n", node_generated, node_expanded);
            return;
        }

        if(ret == INF) {
            printf("[8-puzzle] [IDA-Star] generated_nodes: [%d], expanded_node: [%d]\n", node_generated, node_expanded);
            exit(EXIT_FAILURE);
        }
        bound = ret;
    }
}

int IdaStarEightPuzzle::run() {
    ida_star();
    return 1;
}

void IdaStarEightPuzzle::destroy() {
    //
}