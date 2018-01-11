/*
  Problem: Given 2 arrays of strings, find if there are any shared strings
  Input will have the strings divided by commas and each array on a seperate line

  firstArray = "hi,hello,holla"
  secondArray = "guttentag,hi,bonjour"

  It would be ideal to write this in java.
  The java API for strings is great but we will assume limited resources,
  so no JVM. Instead C++14 will be used. We will be using a Map for storring
  each strings as a key in the Mapping struct. The sortAndMatch struct will
  come to the same conclusion doing as it's named.

  These implementations will ignore repeating strings in the sets.
  1 match, 1 count.

  Strings with case differences will be treated as unique strings.
*/
#include <iostream>
#include <memory>
#include <fstream>
#include <string.h>
#include <map>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;

typedef std::vector<string> vecS;

//A function to break up the input into a vector of strings
vecS split(string str) {
  vecS arr;
  string delimiter = ","; // our strings are seperated by commas
  size_t pos = 0;
  string sub;
  while ( true ) {
    pos = str.find(delimiter); //finding the comma
    sub = str.substr(0, pos); //taking the sub-sting

    // This commented line is for case insensitivty
    // std::transform(sub.begin(), sub.end(), sub.begin(), ::tolower);

    arr.push_back(sub);      //push to the vector
    str.erase(0, pos + delimiter.length()); //pop it of the inputStyle

    // Finish once there is no index(npos)
    if(pos == string::npos) break;
  }
  return arr;
}

// A parent for both implementations vectors
struct Splitting {
protected:
  vecS arr1, arr2;
  int copies = 0;
public:
  virtual ~Splitting() = default;
  Splitting( string str1, string str2 ){
    arr1 = split(str1);
    arr2 = split(str2);
  }
};

/*
  In this approach we shall sort the arrays and go through them; incrementing
  the index of the set with the lowest string
*/
struct SortAndMatch: public Splitting {
  typedef Splitting super;

  virtual ~SortAndMatch() = default;

  SortAndMatch(string str1, string str2):Splitting( str1, str2 ) {
    // quicksort
    std::sort(arr1.begin(),arr1.end());
    std::sort(arr2.begin(),arr2.end());

    for(int i = 0, j = 0; i < arr1.size(), j < arr2.size(); ) {
      if (arr1[i].compare(arr2[j]) == 0) { // A match
        copies++;
        cout<<arr1[i]<<endl;

        // We will then skip over all equivalent elements proceeding in both sets
        int k;
        for ( k =i+1; (arr1[i].compare(arr1[k]) == 0) && k < arr1.size(); k++) ;
        i=k; // push index up to unique string
        for ( k=j+1; (arr2[j].compare(arr2[k]) == 0) && (k < arr2.size()); k++) ;
        j=k; // for both sets
      } else if (arr1[i].compare(arr2[j]) < 0) { // if not a match move pass the lowest
        i++;
      } else {
        j++;
      }
    }
    cout << "Number of Shared strings: " << copies << endl;
  }
};

struct Mapping: public Splitting {
protected:
  std::map<string, bool> leMap;
public:
  virtual ~Mapping() = default;

  Mapping( string str1, string str2):Splitting( str1, str2 ) {
    for (int i = 0; i < arr1.size(); i++) {
      leMap[arr1[i]]=true; //Mapping out all unique strings in the first set
    }
    for (int i = 0; i < arr2.size(); i++) {
      if (leMap[arr2[i]]) { // A shared string
        cout<< arr2[i] << endl;
        copies++;
        leMap[arr2[i]]=false; //so it doesn't get counted with a duplicate
      }
    }
    cout << "Number of Shared strings: " << copies << endl;
  }
};

int main(int argc, char* argv[]) {
  //C++14 clean memory usage.
  using std::make_unique;
  using std::unique_ptr;

  std::ifstream infile;
  infile.open(argv[1]);
  string str1, str2, str1_2, str2_2;
  infile >> str1 >> str2;
  // std::cin >> str1 >> str2; in the case of manual testing
  cout << str1 << endl << str2<< endl;
  // copies
  str1_2 = str1;
  str2_2 = str2;

  // Using a Map to Match
  unique_ptr<Mapping> mapExample = make_unique<Mapping>(str1,str2);

  // Sorting and Matching
  unique_ptr<SortAndMatch> sortExample = make_unique<SortAndMatch>(str1_2,str2_2);
}
// Could of also been done with bipartite matching or network flow
// but is a little much for this problem
