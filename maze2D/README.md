## MAZE2D

Create a random 2D maze generator with size 'n' (n > 3).

Example:
``` txt
n = 11 (* = wall, A = start, B = end)  

***********
*A  *    B*
*** * *****
* * * *   *
* * * * * *
*   *   * *
* *** *** *
*   * *   *
*** *** * *
*       * *
***********
``` 

The 'start' position A must be in the same position of the example. The 'limit' positions must be walls.
The 'end' position B must be in a randon position. You must find the shortest path between A and B.
If there's no path from A to B, another maze must be created.

Implement the method ``` txt createMaze2D( n ) ```

This method will print the maze generated in the same way that in the example.
Don't forget to print the shortest path between A and B using '+'.

## GO TO ACTION!

It will be a litle hard... 

``` txt
run.bat
``` 

If you are not using VS 2017 Community, please change the path in that batch.