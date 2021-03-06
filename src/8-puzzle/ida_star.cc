//
// Created by aislam6 on 1/29/20.
//

#include "core/node.h"
#include "core/state.h"
#include "../utill/utills.h"
#include "../core/heuristic.h"

#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <list>

#define INF (200)

class IdaStarEightPuzzle : public Solver {
public:
    IdaStarEightPuzzle(void *_parameter) {
        IdaStarEightPuzzle::init(_parameter);
    }

    int init(void *_parameter);

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
    std::map<long long int, bool> m;

    void ida_star();

    int run_astar(int max_cost, Node *current_node);
};

int IdaStarEightPuzzle::init(void *_parameter) {
    goal_state = ((EightPuzzleInitParam *)_parameter)->_goal_state;
    initial_state = ((EightPuzzleInitParam *)_parameter)->_initial_state;
    heuristic = ((EightPuzzleInitParam *)_parameter)->_heuristic;
    is_print_path = ((EightPuzzleInitParam *)_parameter)->_print_path;

    return 1;
}

bool comp(Node *a, Node *b) {
    return (get_total_cost(a) < get_total_cost(b));
}

int IdaStarEightPuzzle::run_astar(int max_cost, Node *current_node) {
    int current_node_total_cost = get_total_cost(current_node);

//    printf("current node depth: %d\n", current_node->depth);
//    print_board(current_node->state); printf("\n");

    if(equal_state(current_node->state, goal_state)) {
        printf("solution found!\n");
        is_found = true;
        return current_node_total_cost;
    }

    if(current_node_total_cost > max_cost) {
        return current_node_total_cost;
    }

    std::list<Node *> child_list = expand_node(current_node, goal_state, heuristic);
    node_expanded += 1;
    node_generated += child_list.size();
    int ret = INF;
    //child_list.sort(comp);
    for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
        long long int child_state_key = construct_board_key((*it)->state);
        if(m.find(child_state_key) == m.end()) {
            m[child_state_key] = true;
            ret = utils::_min(ret, run_astar(max_cost, *it));
            if (is_found) return ret;
        }
    }
    return ret;
}

void IdaStarEightPuzzle::ida_star() {
    int bound = heuristic->guess_distance(new EightPuzzleHeuristicParam(initial_state, goal_state));
    int initial_goal_hval = bound;
    is_found = false;
    node_expanded = 0;
    node_generated = 0;

    while(true) {
        m.clear();
        m[construct_board_key(initial_state)] = true;
        node_generated += 1;
//        printf("bound: %d\n", bound);
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