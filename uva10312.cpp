#include "stdio.h"
#include "string.h"
long long s[30], c[30];
int j;
long long cat(int i) {
	if (c[i] == 0) c[i] = 2*(2*i-1)*cat(i-1)/(i+1);
	return c[i];	
}
long long superC (int i) { 
	if (s[i] == 0) s[i] =  ((6*i -9)*superC(i-1) -(i-3)*superC(i-2))/i  ;
	return s[i];
}
int main() {
	memset(s, 0, sizeof s);
	memset(c, 0, sizeof c);
	s[1]=s[2]=c[0]=1;
	while(scanf("%d",&j)==1){printf("%lld\n",(superC(j)-cat(j-1))); }
	return 0;
}
