//
// Created by aislam6 on 1/29/20.
//

#include "../core/node.h"
#include "../core/state.h"
#include "../core/heuristic.h"

#include <stdio.h>
#include <queue>
#include <list>

class BfsEightPuzzle : public Solver {
public:
    BfsEightPuzzle(State *_initial_state, State *_goal_state, Heuristic *_heuristic) {
        BfsEightPuzzle::init(_initial_state, _goal_state, _heuristic);
    }

    int init(State *_initial_state, State *_goal_state, Heuristic *_heuristic);

    int run();

    void destroy();

private:
    /* Private Data */
    State *goal_state;
    State *initial_state;
    Heuristic *heuristic;

    void run_bfs();
};

int BfsEightPuzzle::init(State *_initial_state, State *_goal_state, Heuristic *_heuristic) {
    goal_state = _goal_state;
    initial_state = _initial_state;
    heuristic = _heuristic;
    return 1;
}

void BfsEightPuzzle::run_bfs() {
    int node_expanded = 0;
    std::queue<Node *> q;
    q.push(create_new_node(0, heuristic->guess_distance(initial_state, goal_state), NULL, initial_state));

    while(!q.empty()) {
        Node *current_node = q.front(); q.pop();

        printf("current node depth: %d\n", current_node->depth);
        print_board(current_node->state);

        if(equal_state(current_node->state, goal_state)) {
            printf("solution found!");
            break;
        }
        std::list<Node *> child_list = expand_node(current_node, goal_state, heuristic);
        node_expanded += 1;
        for (std::list<Node *>::iterator it=child_list.begin(); it != child_list.end(); ++it) {
            q.push(*it);
        }

        //if(node_expand > 20) break;
    }
    printf("found solution by expending [%d] nodes\n", node_expanded);
}

int BfsEightPuzzle::run() {
    run_bfs();
    return 1;
}

void BfsEightPuzzle::destroy() {
    //
}