# k-coloring

## Problem Formulation

In graph theory, graph coloring is an assignment problem which is computationally a NP-complete problem. The basic formulation of 
this problem is, we need to assign a color to every vertices of a graph in such a way that no two adjacent vertices are assigned to the 
same color. It is also well known as vertex coloring.

Graph coloring problem can be transformed to a Constraint Satisfaction Problem (CSP). A CSP is composed of the following components:
1. A set of variables X1, X2, ..., Xn with domains (possible values) D1, D2, ..., Dn
2. A set of constraints C1, C2, ..., Cm
3. Each constraint Ci limits the values that a subset of variables can take, e.g., V1 != V2

For graph coloring problem, we can consider,
1. Variables: vertices of the graph
2. Domains: different colors (i.e. red, green, blue)
3. Constraints: no two countries sharing a border have the same color

A k-coloring of a graph thus is an assignment of k colors, one to each vertex, in such a way that no two vertices sharing a edge have the same color.
In this project, I will experiment with graph coloring techniques and compare the observed results in the context of USA and Australia maps. 
We can either find the chromatic number of a graph or test whether a graph can be colored with a MAX_COLOR number. The chromatic number 
of a graph G, written as χ(G), is the smallest number of colors needed to color G. To keep it flexible, I considered both of them.

## Input Format

We consider the constraint graph as a directed one, meaning if there is a bi-directional constraint between A & B then
you need to put both the edges A-B and B-A in your input.

The first line of the input file will contain an integer N, representing the number of vertices in the input graph.
The next N lines will contain the adjacency list of the vertices. Every vertex will be a single word (without any space).
Adjacency list elements will be separated by the space. A graph representing Australian map is given here,

```
7
Western-Australia Northern-Territory South-Australia
Queensland Northern-Territory South-Australia New-South-Wales
New-South-Wales Victoria South-Australia Queensland
Victoria South-Australia New-South-Wales
Tasmania
Northern-Territory Western-Australia South-Australia Queensland
South-Australia Western-Australia Northern-Territory Queensland New-South-Wales Victoria
```

## Implementation Domain

To solve k-coloring problem, currently I have implemented the following algorithms and heuristic functions.

| Graph Coloring Algorithms | Parameter token for this algorithm |
| --- | --- |
| Depth first search only | bt |
| Depth first search <br>+ forward checking | bt-fc |
| Depth first search <br>+ forward checking <br>+ propagation through singleton domains | bt-fc-st |
| Depth first search <br>+ forward checking <br>+ propagation through reduced domains (AC-2/AC-3) | - |

Currently I have implemented the following heuristic functions:

| Heuristic Functions | Parameter token for this application |
| --- | --- |
| Minimum Remaining Values (MRV) | -mrv |
| Degree Heuristic | -degree_heu |
| Least Constraining Value (LCV) | -lcv |

MRV and Degree heuristic is applied on the variable (i.e. vertex) selection and LCV is used to select the value (i.e. color). 
I have implemented the MRV and Degree Heuristic as a filter that can work individually over a list of available vertices.
Details about this heuristic function has been discussed in separate section.

Please keep in mind that, for the current implementation all the parameter token specified above is expected to be exact matched.

## How to Run

General run command:
```
./puzzle -problem {PUZZLE_NAME} \
-algo {ALGORITHM_NAME} \
-file {INPUT_FILE} -mcolor {MAX_ALLOCABLE_COLOR} \
-print_path {PRINT_INITIAL_TO_GOAL} \
-mrv -degree_heu -lcv
```

Here is the parameter definition,
1. **-problem:** Specify the puzzle name to solve, for example, "n-queen".
2. **-algo:** Specify the search strategy to solve the puzzle, for example, "A*", "bfs", "dfs", etc.
3. **-file:** Input file containing constraint graph.
4. **-mcolor:** Maximum allowed color, value -1 means we need to find the chromatic number, value (>0) means we need to color the graph by using this number of colors.
5. **-print_path:** Flag to indicate printing the color assignment after running the coloring algorithm, accepts boolean string, i.e., "true" or "false".
6. **-mrv:** Flag to indicate whether we will apply heuristic Minimum Remaining Values (MRV) for selecting the next vertex to color.
7. **-degree_heu:** Flag to indicate whether we will apply heuristic Minimum Remaining Values (MRV) for selecting the next vertex to color.
8. **-lcv:** Flag to indicate whether we will apply heuristic Minimum Remaining Values (MRV) for selecting the next vertex to color.

## Basic Algorithm Description & Run Commands

For k-coloring, here is the list of run commands for different implemented variations of the backtrack search algorithm -

* Default Backtrack Search

Implemented standard Backtrack search algorithm, picked a random unassigned vertex if no heuristic specified (i.e. MRV, Degree Heuristic, etc).

Run command:
```
./puzzle -problem map-color -algo bt -file aus.in -mcolor -1 -print_path false
```

* Backtrack Search + Forward Checking

Improvised Backtrack search algorithm with forward checking. While assigning a color to a vertex, removed this color from the neighboring
vertices' color domain. This will thus reduce the color choices for the future vertices.

Run command:
```
./puzzle -problem map-color -algo bt-fc -file aus.in -mcolor 3 -print_path false
```

* Backtrack Search + Forward Checking + Singleton Propagation

Further improvised Backtrack search algorithm with singleton propagation. Besides reducing the color choices for the future vertices,
we further check whether there are any vertex that has a single available color in it's domain. Those vertices are called singleton vertex.
If such a single vertex is found, push that vertex to assign color. The intuition is, as singleton vertex has only single color available
in it's color domain, assigning that color for those vertices will reduce the number of failure attempts.

Run command:
```
./puzzle -problem map-color -algo bt-fc-st -file aus.in -mcolor 3 -print_path false
```

## Heuristics for Improving the Performance of Backtracking

There are several heuristic function exist that can help the backtracking algorithm

**To choose a vertex:**

* Choose the vertex with the minimum remaining values ("MRV" heuristic)
* In case of a tie, choose the vertex that is involved in the most constraints with other variables ("degree" heuristic).

**To order the values:**

Suppose a vertex has been chosen to be assigned a color. Heuristic "least-constraining-value" helps ordering the values for that node.
It prefers the value that rules out the fewest choices for the neighboring variables in the constraint graph.

Algorithm of Least Constraining Value:
```
    Suppose, we are trying to assign value for variable "o", available values for "o" is 0-9.

    sums = {0:0, 1:0, 2:0, 3:0, 4:0, 5:0, 6:0, 7:0, 8:0, 9:0}
    For i from 0 to 9:
        plug "o=i" into the constraint formulas
        For each neighbor "N" of "o" in the constraint graph:
            sums[i] += the number of values remaining for "N"
    
    It picks "i" so that:
        sums[i] = MAX{sums[i] | for all "i" that is a member of "o"'s valid values}
```

## Performance Characterization

### How to reproduce

To reproduce the performance evaluation, please run the following commands:

```
> cd puzzle-solver

# Do map color with finding chromatic number (dataset Australia):
> ./puzzle -problem map-color -algo bt        -file src/k-coloring/input/aus.in -mcolor -1 -print_path false
> ./puzzle -problem map-color -algo bt-fc     -file src/k-coloring/input/aus.in -mcolor -1 -print_path false
> ./puzzle -problem map-color -algo bt-fc-st  -file src/k-coloring/input/aus.in -mcolor -1 -print_path false

# Do map color with finding chromatic number (dataset USA):
> ./puzzle -problem map-color -algo bt        -file src/k-coloring/input/usa.in -mcolor -1 -print_path false
> ./puzzle -problem map-color -algo bt-fc     -file src/k-coloring/input/usa.in -mcolor -1 -print_path false
> ./puzzle -problem map-color -algo bt-fc-st -file src/k-coloring/input/usa.in -mcolor -1 -print_path false

# Do map color with the given color (dataset Australia):

> ./puzzle -problem map-color -algo bt        -file src/k-coloring/input/aus.in -mcolor 3 -print_path false
> ./puzzle -problem map-color -algo bt-fc     -file src/k-coloring/input/aus.in -mcolor 3 -print_path false
> ./puzzle -problem map-color -algo bt-fc-st  -file src/k-coloring/input/aus.in -mcolor 3 -print_path false

# Do map color with the given color (dataset USA):
> ./puzzle -problem map-color -algo bt        -file src/k-coloring/input/usa.in -mcolor 4 -print_path false
> ./puzzle -problem map-color -algo bt-fc     -file src/k-coloring/input/usa.in -mcolor 4 -print_path false
> ./puzzle -problem map-color -algo bt-fc-st  -file src/k-coloring/input/usa.in -mcolor 4 -print_path false
```

### Performance Evaluation Without Heuristic

Here is the table of execution time needed for graph coloring algorithms without heuristics:

<table>
  <thead>
    <tr>
      <th>Input Graph</th>
      <th>Graph Coloring Algorithms</th>
      <th>Run 1</th>
      <th>Run 2</th>
      <th>Run 3</th>
      <th>Run 4</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td align="middle" rowspan="3">USA</td>
      <td align="middle">Depth first search only</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking</td>
      <td align="middle">281984 us</td>
      <td align="middle">3378414 us</td>
      <td align="middle">4631376 us</td>
      <td align="middle">769989 us</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking + <br>propagation through singleton domains</td>
      <td align="middle">575873 us</td>
      <td align="middle">163093 us</td>
      <td align="middle">2771744 us</td>
      <td align="middle">641766 us</td>
    </tr>
    <tr>
      <td align="middle" rowspan="3">Australia</td>
      <td align="middle">Depth first search only</td>
      <td align="middle">226 us</td>
      <td align="middle">143 us</td>
      <td align="middle">273 us</td>
      <td align="middle">429 us</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking</td>
      <td align="middle">40 us</td>
      <td align="middle">41 us</td>
      <td align="middle">39 us</td>
      <td align="middle">31 us</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking + <br>propagation through singleton domains</td>
      <td align="middle">25 us</td>
      <td align="middle">27 us</td>
      <td align="middle">39 us</td>
      <td align="middle">34 us</td>
    </tr>
    <tr>
      <td colspan="6" align="middle">Table 1: </td>
    </tr>
  </tbody>
</table>

Here is the table of number of backtrack needed for graph coloring algorithms without heuristics:

<table>
  <thead>
    <tr>
      <th>Input Graph</th>
      <th>Graph Coloring Algorithms</th>
      <th>Run 1</th>
      <th>Run 2</th>
      <th>Run 3</th>
      <th>Run 4</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td align="middle" rowspan="3">USA</td>
      <td align="middle">Depth first search only</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking</td>
      <td align="middle">92576</td>
      <td align="middle">828784</td>
      <td align="middle">1637795</td>
      <td align="middle">238686</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking + <br>propagation through singleton domains</td>
      <td align="middle">459294</td>
      <td align="middle">128535</td>
      <td align="middle">2323570</td>
      <td align="middle">443788</td>
    </tr>
    <tr>
      <td align="middle" rowspan="3">Australia</td>
      <td align="middle">Depth first search only</td>
      <td align="middle">454</td>
      <td align="middle">157</td>
      <td align="middle">566</td>
      <td align="middle">454</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking + <br>propagation through singleton domains</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
      <td align="middle">7</td>
    </tr>
    <tr>
      <td colspan="6" align="middle">Table 2: </td>
    </tr>
  </tbody>
</table>

**Observations:**

### Performance Evaluation With Heuristic

Here is the table of execution time needed for graph coloring algorithms with Vertex Selection heuristics (i.e. MRV & Degree):

<table>
  <thead>
    <tr>
      <th>Input Graph</th>
      <th>Graph Coloring Algorithms</th>
      <th>Run 1</th>
      <th>Run 2</th>
      <th>Run 3</th>
      <th>Run 4</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td align="middle" rowspan="3">USA</td>
      <td align="middle">Depth first search only</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking</td>
      <td align="middle">303 us</td>
      <td align="middle">235 us</td>
      <td align="middle">189 us</td>
      <td align="middle">272 us</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking + <br>propagation through singleton domains</td>
      <td align="middle">182 us</td>
      <td align="middle">246 us</td>
      <td align="middle">164 us</td>
      <td align="middle">181 us</td>
    </tr>
    <tr>
      <td align="middle" rowspan="3">Australia</td>
      <td align="middle">Depth first search only</td>
      <td align="middle">366 us</td>
      <td align="middle">323 us</td>
      <td align="middle">365 us</td>
      <td align="middle">375 us</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking</td>
      <td align="middle">30 us</td>
      <td align="middle">40 us</td>
      <td align="middle">27 us</td>
      <td align="middle">41 us</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking + <br>propagation through singleton domains</td>
      <td align="middle">27 us</td>
      <td align="middle">26 us</td>
      <td align="middle">26 us</td>
      <td align="middle">27 us</td>
    </tr>
    <tr>
      <td colspan="6" align="middle">Table 3: </td>
    </tr>
  </tbody>
</table>

Here is the table of number of backtrack needed for graph coloring algorithms with Vertex Selection heuristics (i.e. MRV & Degree):

<table>
  <thead>
    <tr>
      <th>Input Graph</th>
      <th>Graph Coloring Algorithms</th>
      <th>Run 1</th>
      <th>Run 2</th>
      <th>Run 3</th>
      <th>Run 4</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td align="middle" rowspan="3">USA</td>
      <td align="middle">Depth first search only</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking + <br>propagation through singleton domains</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
    </tr>
    <tr>
      <td align="middle" rowspan="3">Australia</td>
      <td align="middle">Depth first search only</td>
      <td align="middle">680</td>
      <td align="middle">599</td>
      <td align="middle">680</td>
      <td align="middle">703</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking + <br>propagation through singleton domains</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
    </tr>
    <tr>
      <td colspan="6" align="middle">Table 4: </td>
    </tr>
  </tbody>
</table>

Here is the table of execution time needed for graph coloring algorithms with Value Selection heuristics (i.e. LCV):

<table>
  <thead>
    <tr>
      <th>Input Graph</th>
      <th>Graph Coloring Algorithms</th>
      <th>Run 1</th>
      <th>Run 2</th>
      <th>Run 3</th>
      <th>Run 4</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td align="middle" rowspan="3">USA</td>
      <td align="middle">Depth first search only</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking</td>
      <td align="middle">1973316 us</td>
      <td align="middle">168692 us</td>
      <td align="middle">34670 us</td>
      <td align="middle">290577 us</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking + <br>propagation through singleton domains</td>
      <td align="middle">311 us</td>
      <td align="middle">1063312 us</td>
      <td align="middle">1751548 us</td>
      <td align="middle">335 us</td>
    </tr>
    <tr>
      <td align="middle" rowspan="3">Australia</td>
      <td align="middle">Depth first search only</td>
      <td align="middle">269 us</td>
      <td align="middle">444 us</td>
      <td align="middle">339 us</td>
      <td align="middle">435 us</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking</td>
      <td align="middle">31 us</td>
      <td align="middle">29 us</td>
      <td align="middle">30 us</td>
      <td align="middle">48 us</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking + <br>propagation through singleton domains</td>
      <td align="middle">210 us</td>
      <td align="middle">26 us</td>
      <td align="middle">30 us</td>
      <td align="middle">27 us</td>
    </tr>
    <tr>
      <td colspan="6" align="middle">Table 5: </td>
    </tr>
  </tbody>
</table>

Here is the table of number of backtrack needed for graph coloring algorithms with Value Selection heuristics (i.e. LCV):

<table>
  <thead>
    <tr>
      <th>Input Graph</th>
      <th>Graph Coloring Algorithms</th>
      <th>Run 1</th>
      <th>Run 2</th>
      <th>Run 3</th>
      <th>Run 4</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td align="middle" rowspan="3">USA</td>
      <td align="middle">Depth first search only</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking</td>
      <td align="middle">89511</td>
      <td align="middle">8820</td>
      <td align="middle">46354</td>
      <td align="middle">580161</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking + <br>propagation through singleton domains</td>
      <td align="middle">0</td>
      <td align="middle">1316432</td>
      <td align="middle">781374</td>
      <td align="middle">0</td>
    </tr>
    <tr>
      <td align="middle" rowspan="3">Australia</td>
      <td align="middle">Depth first search only</td>
      <td align="middle">533</td>
      <td align="middle">551</td>
      <td align="middle">694</td>
      <td align="middle">650</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
      <td align="middle">9</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking + <br>propagation through singleton domains</td>
      <td align="middle">7</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
    </tr>
    <tr>
      <td colspan="6" align="middle">Table 6: </td>
    </tr>
  </tbody>
</table>

Here is the table of execution time needed for graph coloring algorithms with all the possible heuristics (i.e. MRV, Degree, LCV):

<table>
  <thead>
    <tr>
      <th>Input Graph</th>
      <th>Graph Coloring Algorithms</th>
      <th>Run 1</th>
      <th>Run 2</th>
      <th>Run 3</th>
      <th>Run 4</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td align="middle" rowspan="3">USA</td>
      <td align="middle">Depth first search only</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking</td>
      <td align="middle">383 us</td>
      <td align="middle">282 us</td>
      <td align="middle">553 us</td>
      <td align="middle">359 us</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking + <br>propagation through singleton domains</td>
      <td align="middle">185 us</td>
      <td align="middle">199 us</td>
      <td align="middle">305 us</td>
      <td align="middle">214 us</td>
    </tr>
    <tr>
      <td align="middle" rowspan="3">Australia</td>
      <td align="middle">Depth first search only</td>
      <td align="middle">371 us</td>
      <td align="middle">337 us</td>
      <td align="middle">328 us</td>
      <td align="middle">457 us</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking</td>
      <td align="middle">31 us</td>
      <td align="middle">31 us</td>
      <td align="middle">44 us</td>
      <td align="middle">31 us</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking + <br>propagation through singleton domains</td>
      <td align="middle">27 us</td>
      <td align="middle">27 us</td>
      <td align="middle">28 us</td>
      <td align="middle">27 us</td>
    </tr>
    <tr>
      <td colspan="6" align="middle">Table 7: </td>
    </tr>
  </tbody>
</table>

Here is the table of number of backtrack needed for graph coloring algorithms with all the possible heuristics (i.e. MRV, Degree, LCV):

<table>
  <thead>
    <tr>
      <th>Input Graph</th>
      <th>Graph Coloring Algorithms</th>
      <th>Run 1</th>
      <th>Run 2</th>
      <th>Run 3</th>
      <th>Run 4</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td align="middle" rowspan="3">USA</td>
      <td align="middle">Depth first search only</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
      <td align="middle">-</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking</td>
      <td align="middle">81</td>
      <td align="middle">81</td>
      <td align="middle">81</td>
      <td align="middle">99</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking + <br>propagation through singleton domains</td>
      <td align="middle">207</td>
      <td align="middle">207</td>
      <td align="middle">207</td>
      <td align="middle">207</td>
    </tr>
    <tr>
      <td align="middle" rowspan="3">Australia</td>
      <td align="middle">Depth first search only</td>
      <td align="middle">680</td>
      <td align="middle">599</td>
      <td align="middle">599</td>
      <td align="middle">680</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
    </tr>
    <tr>
      <td align="middle">Depth first search + <br>forward checking + <br>propagation through singleton domains</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
      <td align="middle">0</td>
    </tr>
    <tr>
      <td colspan="6" align="middle">Table 8: </td>
    </tr>
  </tbody>
</table>

**Observations:**

## Future Works
* Apply propagation through domain reduction (AC-2/AC-3) with backtrack search.
* Try implementing other advance algorithms like hill-climbing search, simulated annealing search, genetic algorithm, local and stochastic beam search, etc.

## Resources
* [Web] List of Neighboring States: https://state.1keydata.com/bordering-states-list.php
* [Web] US State Information: https://people.sc.fsu.edu/~jburkardt/datasets/states/states.html
* [Web] Heuristics for use in backtracking constraint-satisfaction search: https://people.cs.pitt.edu/~wiebe/courses/CS2710/lectures/constraintSat.example.txt