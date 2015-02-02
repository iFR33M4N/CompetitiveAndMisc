/*
	Excuse all typos
	
	Flip Five Solution and explanation
	
	In flip five we must find the minimum number of flips to get from an empty
	board to the state that we recieve as input.
	
	...		***
	...	->	.*.
	...		...
	
	The rules are that every time we press on one square, it an all squares 
	adjacently vertical or horizontal must also flip to its opposite state, 
	off >> on and on >> off
	
	...		->*..			**.
	...		  ... 	>>>		*..
	...		  ... (becomes)	...
	
	The flip function can be expressed as a simple Xor operation and we can
	use a bitmask to express our current board
	
	.*.		010		we can then line them		.*.		
	***	 =	111		up in a binary string;		***	 =	01011010
	.*.		010 		top row lasy, bottom first	.*.
	
	and finally express them in integer values
	
	.*.
	***	 =	010111010 = 186 
	.*.
	
	orientation does not matter since the board is symetrical;
	in my soultion, the first coloumn first row is 1<<0.
	
	We will express all possible options(flips) in bitmask (ints) and flip(^ Xor)
	with the current board. 
	186 as shown above is the flip integer representation when the center piece
	of the board is activated.
*/
#include <bits/stdc++.h> //This is a great header to use, full standard c++ library in one line
#define _ ios_base::sync_with_stdio(0);cin.tie(0); 
// If you're not using c++ for competitive programming, you should
using namespace std;

/*
	The algorithm we are using is the BFS as shown by Kip
	but the heuristic we are using is a memoized lookup array;
	where we save and compare each board state and number of lips to get there
	from the intial blank state;in a sort of Dijkstra-esque implimentation.
	
*/

int flips[9]={416,464,200,308,186,89,38,23,11}; //the pregenerated flips in a array
int state;	//the current state of the board
int dist, num; 	//the distance and number of problems
int ans; //the input which we then use output the answer
int arr[1<<9]; //our memoized table
char wi; //used to read in the input

void bfs(){
	//Initializing all of the look up weights in our table to some infinity 
	memset(arr, 999999, sizeof arr); arr[0]=0; //except the initial blank board
	
	/*
		We will go through all possible flips that can be made from the board
		
									    ...
									    ...		(Intitial state)
									    ...
					                                    /|\
								          /  |  \
								        /    |	  \
				(...)		 	 	      /      |      \		(...)			(...)
								    /        |        \
		**.		***		.**		*..	    .*.		..*		...		...		...
		*..		.*.		..*		**.	    ***		.**		*..		.*.		..*
		...		...		...		*..	    .*.		..*		**.		***		.**
		
		All of these states are given an integer representation (we'll call it i)
		then evaluated with their lookup table (the i-th element) and are given 
		a weighted distance of 1 which is then saved to i-th address. Then it will
		be added to a queue. From this queue we we will keep poping and iterating
		through till we have gone through all possible states.
	*/
	queue<pair<int,int>> qii; qii.push( make_pair(0, 0)); 
	//initializing the queue of pair objects (x,y) and adding the intial state
	
	while(!qii.empty()){ //While we still have states to evaluate
		dist=qii.front().first+1; 
		//assign dist to the diestance of the state from the intial plus a weight of one
		
		state=qii.front().second; qii.pop(); //assign the state that pops from queue
		for (int i=0; i<9; i++){//iterate through all possibilities
			if (dist<arr[state^flips[i]]){//and if one is optimal
				arr[state^flips[i]]=dist; //save it to the table
				qii.push(make_pair(dist,state^flips[i])); 
				//and pop the new state to queue with new distance
			}
		}
	} 
} //thus ends are bfs function to generate a memoized table 
int main(){
	bfs(); //generate
	cin>>num; //take in the number of problems
	while(num--){ //while we still got problems 
		ans=0; //setup the input
		for(int i=8; i>=0; i--){ cin>>wi;//iterate through each square
			if(wi=='*') ans+=(1<<(i)); //if on, turn it on in the int representation
		} 
		cout<<arr[ans]<<endl; //return the pregenerated value
	}
	return 0;
} //done