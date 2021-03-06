#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H"

#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "../../tools/fastio.cpp"
#include "../../segtree/basic/chien.cpp"
#undef call_from_test

signed main(){
  int n,q;
  cin>>n>>q;

  auto f=[](int a,int b){return min(a,b);};
  auto g=[](int a,int b){return a+b;};
  SegmentTree<int, int> seg(f,g,g,INT_MAX,0);
  seg.build(vector<int>(n,0));

  for(int i=0;i<q;i++){
    int c;
    cin>>c;
    if(c==0){
      int s,t,x;
      cin>>s>>t>>x;
      seg.update(s,t+1,x);
    }
    if(c==1){
      int s,t;
      cin>>s>>t;
      cout<<seg.query(s,t+1)<<"\n";
    }
  }
  cout<<flush;
  return 0;
}
