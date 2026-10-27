# Competitive Programming Library

The C++ implementations I wrote while preparing for ICPC with my University of Tehran team, from June to December 2025. Most files are a standard algorithm or data structure written as a reusable template, sometimes with a small problem that uses it. I kept them grouped by topic so I could find and adapt them quickly during practice contests.

| Folder | Contents |
| --- | --- |
| [Graph](Graph) | Shortest paths (Dijkstra, Bellman-Ford, Floyd), negative and directed cycles, SCC and 2-SAT, biconnected components, MST, Euler paths, Hamiltonian paths, matching, and counting or ranking routes in DAGs |
| [Tree](Tree) | LCA, centroid decomposition, path and subtree queries, small-to-large merging (sack), virtual trees, treaps and link-cut trees |
| [GraphBeforeExam](GraphBeforeExam) | A second round of graph and tree code: bridges and cut vertices, dynamic bipartiteness, segment-tree merging, and path updates with HLD |
| [Flow](Flow) | Dinic's max flow, min cut, and bipartite matching |
| [DataStructure](DataStructure) | Fenwick trees, sparse tables, segment tree variants, heavy-light decomposition, and Mo's algorithm on arrays and graphs |
| [SegmentTrees](SegmentTrees) | More specialised segment trees: lazy propagation, k-th order statistics, 2-D queries, fractional cascading, and hashing strings under updates |
| [SQRT](SQRT) | Square-root decomposition and Mo's algorithm, including the versions on trees and with updates |
| [DP](DP) | LIS and LCS, bitset knapsack, tiling with broken profiles, digit DP, sum over subsets, rerooting on trees, matrix exponentiation, and the Aliens trick |
| [Combinitorics](Combinitorics) | FFT and NTT, Catalan and Stirling numbers, Lucas's theorem, inclusion-exclusion, Möbius inversion, Burnside's lemma, and counting spanning trees |
| [Strings](Strings) | KMP, hashing, tries, Aho-Corasick, suffix arrays with LCP, suffix automata, palindromic trees, and Lyndon factorization |
| [Geometry](Geometry) | Point and segment primitives, convex hull, and polygon operations |
| [Math](Math) | Modular arithmetic, the Josephus problem, and a few counting problems |
| [Miscellaneous](Miscellaneous) | Monotonic stacks and sliding-window tricks |
| [Fact](Fact) | Notes on useful graph facts and bounds |

Nearly every file compiles on its own with `g++ -std=c++17`. A few are snippets meant to be pasted into a solution.
