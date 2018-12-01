# B+ Tree

## What is a B+-tree?
Most queries can be executed more quickly if the values are stored in order. But it's not practical to hope to store all the rows in the table one after another, in sorted order, because this requires rewriting the entire table with each insertion or deletion of a row.

This leads us to instead imagine storing our rows in a tree structure. Our first instinct would be a balanced binary search tree like a red-black tree, but this really doesn't make much sense for a database since it is stored on disk. You see, disks work by reading and writing whole blocks of data at once — typically 512 bytes or four kilobytes. A node of a binary search tree uses a small fraction of that, so it makes sense to look for a structure that fits more neatly into a disk block.

Hence the B+-tree, in which each node stores up to d references to children and up to d − 1 keys. Each reference is considered “between” two of the node's keys; it references the root of a subtree for which all values are between these two keys.

## Why we need such?
A B/B+ tree is a common data structure used when dealing with an amount of data that can't be stored in RAM. Since this data would traditionally be stored in a hard disk, each disk access was significantly more costly than a RAM access. In order to alleviate this problem, B trees were made to minimize the number of disk accesses. [Click here for more info.](https://en.wikipedia.org/wiki/B-tree)

## Difference Between B and B+ Tree
One stores data along with keys in its internal nodes (B-Tree) and the other only has keys in its internal nodes. There are use cases for both structures, but the B+ tree tends to be more used.

In the case of this implementation, there are some slight variations compared to a traditional one. The internal nodes keep track of a little data: the minimums of its children nodes.
