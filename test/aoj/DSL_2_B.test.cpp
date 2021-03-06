#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"

#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "../../tools/fastio.cpp"
#include "../../datastructure/binaryindexedtree.cpp"
#undef call_from_test

signed main(){
  int n,q;
  cin>>n>>q;
  BIT<long long> bit(n+100);
  for(int i=0;i<q;i++){
    int c,x,y;
    cin>>c>>x>>y;
    if(c==0) bit.add(x,y);
    if(c==1) cout<<bit.query(x,y+1)<<"\n";
  }
  cout<<flush;
  return 0;
}
