## Segment Trees

> #### Implementation 1 ( Classic )

- It follows the numbering of the tree nodes in the order of a BFS traversal (level-order traversal). 
- Using this traversal the children of vertex v are 2v+1 and 2v+2 respectively. 
- However if n is not a power of two, this method will skip some indices and leave some parts of the array t unused. 
- The memory consumption is limited by 4n, even though a Segment Tree of an array of n elements requires only 2n−1 vertices.

> #### Implementation 2 ( Memory Efficient )
 
- In this implementation we renumber the vertices of the tree in the order of an Euler tour traversal (pre-order traversal), and we write all these vertices next to each other.
- Lets look at a vertex at index v, and let him be responsible for the segment [l,r], and let mid=(l+r)/2. It is obvious that the left child will have the index v+1. 
- The left child is responsible for the segment [l,mid], i.e. in total there will be 2∗(mid−l+1)−1 vertices in the left child's subtree. 
- Thus we can compute the index of the right child of v. The index will be v+2∗(mid−l+1). By this numbering we achieve a reduction of the necessary memory to 2n.