#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
long long int arr[11];
int a;
bool flag;
inline void _init(){arr[0]=1;
  for (int i=1; i<11; i++){
    arr[i]=(2*i)*(2*i-1)*arr[i-1]/(i*i+i);
  }
}
int main(){
  _init();
  flag =false;
  while(scanf("%d",&a)==1){
    if (flag)
      printf("\n");
    flag = true;
    printf("%lld\n",arr[a]);
  }
  return 0;
}
