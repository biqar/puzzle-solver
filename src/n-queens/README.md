# n-queens

## Problem Formulation

Given an integer N > 3, place N queens in an NxN board in such a way that no queens can attack each other. 
According to the chess rule, a queen is able to attack another queen if and only if both queens occupy 
the same row, column or diagonal on the board.

In this part of the project, we will start from a random board state and apply different variation of hill-climbing search to 
find a board configuration where all the queens will be placed in a way so that they don’t able to attack each other.

## Implementation Domain

To solve n-queen problem, currently we have implemented different variation of hill-climbing search, they are:

| Hill-Climbing variations | Is Complete? | Parameter token for this mode |
| --- | --- | --- |
| Default Hill-Climbing search | No | - |
| Random-best-choice Hill-Climbing search | No | random-best |
| Stochastic Hill-Climbing search | No | stochastic |
| First-choice Hill-Climbing search | No | first-choice |
| Hill-Climbing search with sideways move | No | sideways-move |
| Random-restart Hill-Climbing search without sideways move | Yes | random-restart |
| Random-restart Hill-Climbing search with sideways move | Yes | random-restart-sways-move |

For Hill-Climbing search algorithm, if you do not specify any particular mode in the program parameter, 
`Default Hill-Climbing search` will be considered.

Please keep in mind that, for the current implementation all the names specified above is actually expected as the parameter name.

## How to Run

General run command:
```
./puzzle -problem {PUZZLE_NAME} \
-algo {ALGORITHM_NAME} -mode {MODE} \
-board_dim {DIMENSION_OF_THE_BOARD} -mx_sideways_move {MAX_SIDEWAYS_MOVE}\
-print_path {PRINT_INITIAL_TO_GOAL}
```

Here is the parameter definition,
1. **-problem:** Specify the puzzle name to solve, for example, "n-queen".
2. **-algo:** Specify the search strategy to solve the puzzle, for example, "A*", "bfs", "dfs", etc.
3. **-mode:** Specify the inner methodology for the search strategy, for example, "bi-directional" bfs, "stack-based" dfs, etc.
4. **-board_dim:** Board dimension, may use representing any square board
5. **-mx_sideways_move:** Maximum allowed sideways move in hill-climbing search
6. **-print_path:** Flag to indicate printing path if solution exist, accepts boolean string, i.e., "true" or "false".

## Basic Algorithm Description & Run Commands

For n-queen, here is the list of run commands for different implemented modes of the hill-climbing search algorithm -

* Default Hill-Climbing search

Implemented standard Hill-Climbing search algorithm, picked the best possible successor from a board configuration. 
If found multiple best possible successor, picked the first one.

Run command:
```
./puzzle -problem n-queen -algo hill-climbing -mode na -board_dim 10 -mx_sideways_move 0 -print_path false
```

* Random-best-choice Hill-Climbing search

Stored all the possible best successors in memory and picked a random one from them. Not memory efficient like the previous one.
The motivation of this implementation is to know whether the selection of best successor has any impact on the performance.

Run command:
```
./puzzle -problem n-queen -algo hill-climbing -mode random-best -board_dim 10 -mx_sideways_move 0 -print_path false
```

* Stochastic Hill-Climbing search

Stochastic hill climbing chooses the successor at random from among the uphill moves. This usually converges more 
slowly than steepest ascent, but in some state landscapes, it finds better solutions.

Run command:
```
./puzzle -problem n-queen -algo hill-climbing -mode stochastic -board_dim 10 -mx_sideways_move 0 -print_path false
```

* First-choice Hill-Climbing search

First-choice hill climbing generates successors until one is generated that is better than the current state.
This is a good strategy when a state has many (e.g., thousands) of successors.

Run command:
```
./puzzle -problem n-queen -algo hill-climbing -mode first-choice -board_dim 10 -mx_sideways_move 0 -print_path false
```

<figure>
    <img align="middle" src="https://github.com/biqar/puzzle-solver/blob/master/resources/state_space_landscape.png" height="400" width="584" alt="state_space_landscape"/>
    <figcaption>Figure 1: State-space landscape</figcaption>
</figure>

* Hill-Climbing search with sideways move

The default Hill-climbing algorithm halts if it reaches a plateau where the best successor has the same value 
as the current state. This implementation allows a sideways move in the hope that the plateau is really a shoulder.
An infinite loop will occur whenever the algorithm reaches a flat local maximum that is not a shoulder. So 
passes a parameter to the program to provide a limit on the number of consecutive sideways moves allowed.

Run command:
```
./puzzle -problem n-queen -algo hill-climbing -mode sideways-move -board_dim 10 -mx_sideways_move 10 -print_path false
```

* Random-restart Hill-Climbing search without sideways move

It conducts a series of hill-climbing searches from randomly generated initial states, until a goal is found.
It is complete with probability 1 to reach the goal, because it will eventually generate a goal state as the initial state.

Run command:
```
./puzzle -problem n-queen -algo hill-climbing -mode random-restart -board_dim 10 -mx_sideways_move 0 -print_path false
```

* Random-restart Hill-Climbing search with sideways move

Allowed to walk in the plateau to see whether it is a shoulder or not.

Run command:
```
./puzzle -problem n-queen -algo hill-climbing -mode random-restart-sways-move -board_dim 10 -mx_sideways_move 10 -print_path false
```

## Performance Characterization

All the tests performed on 10x10 chess board. Used 10 as the maximum limit of sideways move. While finding successor, moved 
the row cursor in the range of highest possible UP and DOWN limit.

### How to reproduce

To reproduce the performance evaluation, please run scripts kept in "benchmark/n-queen" directory. You will get bash scripts to 
run different hill-climbing algorithms to solve custom  n-queen problem. You can pass the board dimension and maximum number of 
consecutive steps in sideways move as the parameter of the program. You can save the output of these scripts in a file and use 
the parser python script to parse it. For incomplete searches you should use parser "parser_incomplete_search.py" and for 
complete searches you should use "parser_complete_search.py". Here I am giving the steps to reproduce the evaluation 
(one for incomplete search and another for complete search).

```
#incomplete search [Default Hill-Climbing search]
> cd benchmark/n-queen
> ./hill_climbing-benchmark.sh > hill_climbing-benchmark.out
> python3 parser_incomplete_search.py hill_climbing-benchmark.out

#complete search [Random-restart Hill-Climbing search without sideways move]
> cd benchmark/n-queen
> ./hill_climbing_rr-benchmark.sh > hill_climbing_rr-benchmark.out
> python3 parser_complete_search.py hill_climbing_rr-benchmark.out
```

### Performance of Incomplete Searches

| Incomplete Searches | Success Rate (in %) | Avg. steps in success | Avg. steps in failure |
| --- | --- | --- | --- |
| Default Hill-Climbing search | 5.4 | 5.26 | 4.92 |
| Random-best-choice Hill-Climbing search | 6.8 | 5.21 | 5.04 |
| Stochastic Hill-Climbing search | 6.0 | 8.03 | 7.41 |
| First-choice Hill-Climbing search | 6.2 | 8.32 | 8.18 |
| Hill-Climbing search with sideways move | 19.6 | 6.59 | 15.33 |

**Observations:**
1. Picking a random from the best successors performs better than picking the first one.
2. Stochastic and First-choice Hill-Climbing search has less impact on performance for 10x10 board configuration.
3. Hill-Climbing search with sideways move has better success rate with a increased number of steps required in failure cases.
4. Without sideways move, it required less steps in failure cases.

<table>
  <tr>
    <td>
       <img align="left" src="https://github.com/biqar/puzzle-solver/blob/master/resources/n-queen_success_rate_incomplete_search.png" alt="n-queen_success_rate_incomplete_search"/>
    </td>
    <td><img align="left" src="https://github.com/biqar/puzzle-solver/blob/master/resources/n-queen_step_comparison_incomplete_search.png" alt="n-queen_step_comparison_incomplete_search"/>
    </td>
    <td><img align="left" src="https://github.com/biqar/puzzle-solver/blob/master/resources/n-queen_complete_searches.png" alt="n-queen_complete_searches"/>
    </td>
  </tr>
  <tr>
    <td align="middle">Figure 2 (a): Incomplete Searches' Success Rate Comparison</td>
    <td align="middle">Figure 2 (b): Incomplete searches' Step Comparison</td>
    <td align="middle">Figure 2 (c): Comparison of Complete Searches</td>
  </tr>
  <tr>
    <td colspan="3" align="middle">Figure 2: Comparing performance of different algorithms for solving n-queen</td>
  </tr>
</table>

### Performance of Complete Searches

| Complete Searches | Success Rate (in %) | Avg. steps | Avg. restart |
| --- | --- | --- | --- |
| Random-restart Hill-Climbing search without sideways move | 100 | 74.43 | 14.03 |
| Random-restart Hill-Climbing search with sideways move | 100 | 71.33 | 4.19 |

**Observations:**
1. Random-restart Hill-Climbing search perform better with sideways move and reduces the number of restarts 70%.

## Future Works
* Do analysis on complete searches' random restart required count distribution chart 
* Do similar performance test on higher dimension board.
* Do performance characterization of sideways move (impact on increasing limit of sideways move for fixed board dimension).
* Do compare performance (w.r.t. execution time) of backtracking Vs. Random-restart Hill-Climbing search w/wo sideways walk for smaller board.

## Resources
* [Blog-post] The 8 Queens Problem (An Introduction): https://kushalvyas.github.io/gen_8Q.html