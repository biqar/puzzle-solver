# n-queens

## Problem Formulation

Given an integer N > 3, place N queens in an NxN board in such a way that no queens can attack each other. 
According to the chess rule, a queen is able to attack another queen if and only if both queens occupy 
the same row, column or diagonal on the board.

## Implementation Domain

To solve n-queen problem, currently we have implemented different variation of hill-climbing search, they are:

| Hill-Climbing variations | Parameter token for this mode |
| --- | --- |
| Default Hill-Climbing search | - |
| Hill-Climbing search with sideways move | sideways-move |
| Random-restart Hill-Climbing search with sideways move | random-restart-sways-move |
| Random-restart Hill-Climbing search without sideways move | random-restart |

For Hill-Climbing search algorithm, if you do not specify any particular mode in the program parameter, 
`Default Hill-Climbing search` will be considered.

Please keep in mind that, for the current implementation all the names specified above is actually expected as the parameter name.
