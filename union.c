/*
  For the first problem where given an array of dots and their connections
  . . . ._. .
        |
  . . ._._. .
  ._. . . . .
  Find the number of groups of connected dots; in the case above 2

  The Input file given begins with range and domain of dots
  it then gives which dots are connected by placing the order pairs side by SideMenu
  i.e. (1,2)(2,3)

  the sample input looks something like the figure below (ascii art)
    1 2 3 4 5
  0 . . . . . . . .

  1 . . . . .
      |
  2 . ._. . .  ... continues ...
        |
  3 . . . . .
        |
  4 . . ._. .
          |
  5 . . . . .

    .

    .

    .

  This would've be a great chance do a flood fill approach,
  where while going through the graph, upon finding a connected edge
  assign it a unique number along with all its connected components that
  are visited through Breath First Search. But instead, since the input
  I asked in class would be presented as an adjacency matrix, I thought it
  would be simpler to do union set.

  This is code was not enhanced to handle errors, bugs, overflow, and other possible issues.
*/

#include <stdio.h>
#include <string.h>

// I thought it would be easier to flatend the grid.
int *arr;
int *cnts; // This is the ranking counting array

int findSet(int i){
  // returns the root set and reduces branching
  return (arr[i]==i) ? i : ( arr[i] = findSet(arr[i]) );
}

void unionSet(int i, int j) {
  if (!(findSet(i) == findSet(j))) { // new connection
    int x = findSet(j), y = findSet(i); // get root

    // the smaller set will join the larger
    if (cnts[x] > cnts[y]) {
      arr[y] = x;
      cnts[x] += cnts[y]; // adding the size to the larger set
      cnts[y] = 0; // smaller set is now empty
    } else {
      arr[x] = y;
      cnts[y] += cnts[x];
      cnts[x] = 0;
    }
  }
}

int main( int argc, char* argv[]) {
  FILE *fp;
  char str[999]; // Buffer
  fp = fopen( argv[1], "r" );
  if (fp) {
    int height, width, x1, y1, x2, y2, i;
    fscanf( fp, "%d%d", &width, &height);
    arr = malloc((height * width) * sizeof(int));
    cnts = malloc((height * width) * sizeof(int));
    for ( i = 0; i < (height * width); i++ ) {
      arr[i]=i; // all vertices are initalized to be a set with a root of themselves
      cnts[i]=1; // all sets have intially one element
    }
    while(fscanf(fp, "%s", str)!=EOF) {
      // scanning the string %*[^0123456789]%d will take in any integer
      // and since we're expecting 4 integers
      sscanf( str, "%*[^0123456789]%d%*[^0123456789]%d%*[^0123456789]%d%*[^0123456789]%d",
                &x1, &y1, &x2, &y2);

      // as if the y coordinate was a floor and x coordinate, the room number
      unionSet(height*y1 + x1, height*y2 + x2);
    }
    // Go and count the number of connected sets
    int numOfSets = 0;
    for ( i = 0; i < (height * width); i++)
      if (cnts[i] > 1) {
        numOfSets++;
      }
    printf("\n%d\n", numOfSets);
    fclose(fp);
    free(cnts);
    free(arr);
  }
}
