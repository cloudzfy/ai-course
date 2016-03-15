## Homework #2: Adversarial Search

**Introduction**

In this project, you will write a program to determine the next move for a player in the Reversi game using the Greedy, Minimax, and Alpha-Beta pruning algorithms with positional weight evaluation functions.

The rules of the Reversi game can be found at [http://en.wikipedia.org/wiki/Reversi](http://en.wikipedia.org/wiki/Reversi) [1] and interactive examples can be found at [http://www.samsoft.org.uk/reversi/](http://www.samsoft.org.uk/reversi/) [2]. In the Othello version of this game, the game begins with four disks placed in a square in the middle of the grid, two facing light-up, two pieces with the dark side up, with same-colored disks on a diagonal with each other. However, in this assignment, the starting position will be specified in the input file and may be different.

**Tasks**

In this assignment, you will write a program to determine the next move by implementing the following algorithms:

1. Greedy;
2. Minimax;
3. Alpha-Beta;

In addition, we will have the competition, which is voluntary and for a bonus prize. You will create an agent that can play this game against another agent. The competition is optional and will not affect your grade in the course.

**Legal moves and Flips/Captures**

Assume that the current position is as shown in the left image below and that the current turn is Black’s. Black must place a piece with the black side up on the board in such a position that there exists at least one straight (horizontal, vertical, or diagonal) occupied line between the new piece and another black piece, with one or more contiguous light pieces between them. The right image shows all the legal moves available to the Black player (see the translucent circles below that highlight the legal Black moves). If one player cannot make a valid move, play passes back to the other player.
