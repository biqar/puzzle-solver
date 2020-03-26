# Puzzle Solver (by using problem solving techniques)

## Project Goal

The goal of this project is to build a generic interactive pluggable application for solving puzzles (i.e. 8-puzzle, 15-puzzle,
n-queen, Sudoku, etc.) using different problem-solving techniques (i.e. informed search, uninformed search, hill-climbing search etc.).
Here by word "pluggable" we mean in solving puzzles user can independently decide the search strategy along with the 
custom heuristic functions. If needed, user can extend this project to device their own solution with a very low effort. 
Besides, this application is designed in a way that, it will be an easy-going platform for benchmarking any puzzles w.r.t. different
state space search strategy, optimization techniques and heuristic functions.

### Search Strategies
A search strategy is defined by picking the order of node expansion, Strategies are evaluated along the following dimensions:
* Completeness: does it always find a solution if one exists?
* Optimality: does it always find a least-cost solution?
* Time complexity: number of nodes generated
* Space complexity: maximum number of nodes in memory

Time and space complexity are measured in terms of
* b: maximum branching factor of the search tree
* d: depth of the optimal solution
* m: maximum length of any path in the state space (may be infinite)

### Uninformed Search Strategies
Uninformed search strategies use only the information available in the problem definition
* Breadth-first search
* Uniform-cost search
* Depth-first search
* Iterative deepening search

### Informed Search
Idea: give the algorithm “hints” about the desirability of different states. Use an evaluation function to rank nodes and select the most promising one for expansion
* Greedy best-first search
* A* search

### Heuristic Function
Heuristic function h(n) estimates the cost of reaching goal from node n

Relaxed heuristic functions
* Pattern Database Heuristics 
* Linear Conflict Heuristics
* Gaschnig’s Heuristics

## Project Structure
The project has several independent parts that we combine to work as a whole. Directory "core" contains two factory 
methods that produce the puzzle solver and heuristic instance based on the parameter passed. Puzzle solutions can be 
implemented in separate directory as we have done for "8-puzzle" here. All the heuristic implementations placed in the 
"heuristic" directory. Directory "utils" all the utility methods that help other functions to operate.

Please keep in mind, this is an active project and project architecture may change without any prior announcement. 
But all the future updates will be maintained in a way so that the project integrity will ke kept, meaning you will not 
face any difficulty in building or running the project.

## How to Build

```
# go to project directory
$ cd puzzle-solver

# build the project
$ make clean && make
```

## How to Run

General run command:
```
./puzzle -problem {PUZZLE_NAME} \
-algo {ALGORITHM_NAME} -mode {MODE} \
-heu {HEURISTIC_METHOD} \
-initial {INITIAL_STATE_OF_THE_GAME} -goal {GOAL_STATE_OF_THE_GAME} \
-board_dim {DIMENSION_OF_THE_BOARD} -mx_sideways_move {MAX_SIDEWAYS_MOVE}\
-print_path {PRINT_INITIAL_TO_GOAL}
```

Here is the parameter definition,
1. **-problem:** Specify the puzzle name to solve, for example, "8-puzzle".
2. **-algo:** Specify the search strategy to solve the puzzle, for example, "A*", "bfs", "dfs", etc.
3. **-mode:** Specify the inner methodology for the search strategy, for example, "bi-directional" bfs, "stack-based" dfs, etc.
4. **-heuristic:** Specify the heuristic function you want to use, for example, "hamming", "manhattan", "euclidean", etc. [default: manhattan]
5. **-initial:** Specify the initial board setup for your puzzle
6. **-goal:** Specify the goal state of your puzzle
7. **-board_dim:** Board dimension, may use representing any square board
8. **-mx_sideways_move:** Maximum allowed sideways move in hill-climbing search
9. **-print_path:** Flag to indicate printing path if solution exist, accepts boolean string, i.e., "true" or "false".

## Motivation of Algorithm Mode
While implementing different algorithms for solving 8-puzzle problem, we found some optimization techniques help the algorithms' 
to be more efficient. These techniques can be rigid or independent w.r.t. the algorithm itself. 
For example, bi-directional search technique is very common in the domain of searching algorithms and can be applied to 
a large number of algorithms. Bi-directional search launch two searches, one from the initial state to the goal state 
and another one from the reverse direction. The key benefit here is it help reduce the search space, as we know the 
search trees grow exponentially by their depth. From table 1, we can find that the bi-directional strategy generates at least 2x 
less nodes comparing to the original algorithms (i.e. Optimized BFS vs. Bi-directional BFS). Fig 1 give a brief idea about the 
state space reduction by bi-directional strategy while applied in BFS. We can also observe in some cases within some constraints 
the original algorithm fails to reach the goal, whereas applying bi-directional approach may help reaching the goal (i.e. 
DLS vs. Bi-directional DLS for input 5). This become possible due to the lower search space generated by bi-directional approaches.

<figure>
    <img align="middle" src="https://github.com/biqar/puzzle-solver/blob/master/resources/bidirectional_search_space_reduction.png" height="400" width="584" alt="bidirectional_search_space_reduction"/>
    <figcaption>Figure 1: Showing search space reduction by bi-directional search</figcaption>
</figure>


Some techniques can be applied to very selective algorithms. For example, DFS is a very well known algorithm in the domain of 
state space search and can be implemented in recursive and non-recursive (stack based) way. The benefit of using stack based 
DFS is avoiding stack overflow due to excessively deep recursions.

## Future Work
* Will solve 8-queen puzzle by different non-classical search strategy.
* Will solve 2 player game by applying  minimax decisions and α–β pruning.
* Found several puzzles that can be tried later
    * [Hidato puzzle](https://rosettacode.org/wiki/Solve_a_Hidato_puzzle)
    * [Knight's tour](https://rosettacode.org/wiki/Knight%27s_tour)
    * [Holy Knight's tour](https://rosettacode.org/wiki/Solve_a_Holy_Knight%27s_tour)
    * [Hopido puzzle](https://rosettacode.org/wiki/Solve_a_Hopido_puzzle)
    * [Numbrix puzzle](https://rosettacode.org/wiki/Solve_a_Numbrix_puzzle)
    * [No connection puzzle](https://rosettacode.org/wiki/Solve_the_no_connection_puzzle)
    * [Peaceful chess queen armies](https://rosettacode.org/wiki/Peaceful_chess_queen_armies)

## Resources
1. [Blog] Problem Solving Techniques part1: https://mhesham.wordpress.com/2010/04/08/problem-solving-techniques-part1/
2. [Blog] Problem Solving Techniques part2: https://mhesham.wordpress.com/tag/depth-limited-search/
