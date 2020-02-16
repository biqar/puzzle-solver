//
// Created by Islam, Abdullah Al Raqibul on 1/30/20.
//

#ifndef NODE_H
#define NODE_H

#include "state.h"
#include <list>
#include <iostream>
#include <stdlib.h>

typedef struct Node {
    int depth;
    int h_cost;
    Node *parent;
    State *state;
} Node;

inline Node *create_new_node(int _depth, int _h_cost, Node *_parent, State *_state) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    if(new_node == NULL) {
        exit(EXIT_FAILURE);
    }

    new_node->depth = _depth;
    new_node->h_cost = _h_cost;
    new_node->parent = _parent;
    new_node->state = _state;

    return new_node;
}

inline std::list<Node *> expand_node(Node *current_node, State *goal_state) {
    State *new_state;
    Node *child;
    std::list<Node *> ret;

    if(current_node->state->move != DOWN && (new_state = move_to_new_state(current_node->state, UP)) != NULL) {
        child = create_new_node(current_node->depth + 1, calculate_manhattan_distance(new_state, goal_state), current_node, new_state);
        ret.push_back(child);
    }
    if(current_node->state->move != UP && (new_state = move_to_new_state(current_node->state, DOWN)) != NULL) {
        child = create_new_node(current_node->depth + 1, calculate_manhattan_distance(new_state, goal_state), current_node, new_state);
        ret.push_back(child);
    }
    if(current_node->state->move != LEFT && (new_state = move_to_new_state(current_node->state, RIGHT)) != NULL) {
        child = create_new_node(current_node->depth + 1, calculate_manhattan_distance(new_state, goal_state), current_node, new_state);
        ret.push_back(child);
    }
    if(current_node->state->move != RIGHT && (new_state = move_to_new_state(current_node->state, LEFT)) != NULL) {
        child = create_new_node(current_node->depth + 1, calculate_manhattan_distance(new_state, goal_state), current_node, new_state);
        ret.push_back(child);
    }

    return ret;
}

inline int get_total_cost(Node *node) {
    return node->depth + node->h_cost;
}

inline int get_total_cost(int depth, int h_cost) {
    return (depth + h_cost);
}

struct AstarNodeComparator {
    bool operator ()(Node *a, Node *b) {
        return (get_total_cost(a) < get_total_cost(b));
    }
};

#endif //NODE_H
