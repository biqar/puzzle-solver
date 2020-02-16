//
// Created by aislam6 on 1/29/20.
//

#include "../core/node.h"
#include "../core/state.h"
#include "../core/solver.h"

#include <stdio.h>
#include <queue>
#include <list>

class AStarEightPuzzle : public Solver {
public:
    AStarEightPuzzle(State *_initial_state, State *_goal_state) {
        AStarEightPuzzle::init(_initial_state, _goal_state);
    }

    int init(State *_initial_state, State *_goal_state);

    int run();

    void destroy();

private:
    /* Private Data */
    State *goal_state;
    State *initial_state;

//    bool comp(Node *a, Node *b);

    void run_astar();
};

//bool AStarEightPuzzle::comp(Node *a, Node *b) {
//    return (get_total_cost(a) < get_total_cost(b));
//}

int AStarEightPuzzle::init(State *_initial_state, State *_goal_state) {
    goal_state = _goal_state;
    initial_state = _initial_state;
    return 0;
}

void AStarEightPuzzle::run_astar() {
    int node_expanded = 0;
    std::queue<Node *> q;
    q.push(create_new_node(0, calculate_manhattan_distance(initial_state, goal_state), NULL, initial_state));

    while(!q.empty()) {
        Node *current_node = q.front(); q.pop();

        printf("current node depth: %d\n", current_node->depth);
        print_board(current_node->state);

        if(equal_state(current_node->state, goal_state)) {
            printf("solution found!");
            break;
        }
        std::list<Node *> child_list = expand_node(current_node, goal_state);
        node_expanded += 1;
        //todo: need to fix this first
        //child_list.sort(comp);
        child_list.sort(AstarNodeComparator());
        for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
            q.push(*it);
        }

        //if(node_expand > 20) break;
    }
    printf("found solution by expending [%d] nodes\n", node_expanded);
}

int AStarEightPuzzle::run() {
    return 1;
}

void AStarEightPuzzle::destroy() {
    //
}