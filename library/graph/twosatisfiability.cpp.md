---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: graph/twosatisfiability.cpp
<a href="../../index.html">Back to top page</a>

* category: graph
* <a href="{{ site.github.repository_url }}/blob/master/graph/twosatisfiability.cpp">View this file on GitHub</a>
    - Last commit date: 2019-10-26 15:31:15 +0900




## Depends On
* :heavy_check_mark: <a href="stronglyconnectedcomponent.cpp.html">graph/stronglyconnectedcomponent.cpp</a>


## Verified With
* :heavy_check_mark: <a href="../../verify/test/aoj/3102.test.cpp.html">test/aoj/3102.test.cpp</a>


## Code
{% raw %}
```cpp
#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "stronglyconnectedcomponent.cpp"
#undef call_from_test

#endif
//BEGIN CUT HERE
struct TwoSat{
  int n;
  SCC scc;
  TwoSat(int n):n(n),scc(n*2){}
  int negate(int v){return (n+v)%(n*2);}
  void add_if(int u,int v){
    // u -> v <=> !v -> !u
    scc.add_edge(u,v);
    scc.add_edge(negate(v),negate(u));
  }
  void add_or(int u,int v){
    // u or v <=> !u -> v
    add_if(negate(u),v);
  }
  void add_nand(int u,int v){
    // u nand v <=> u -> !v
    add_if(u,negate(v));
  }
  void set_true(int v){
    //  v <=> !v ->  v
    scc.add_edge(negate(v),v);
  }
  void set_false(int v){
    // !v <=>  v -> !v
    scc.add_edge(v,negate(v));
  }
  vector<int> build(){
    scc.build();
    vector<int> res(n);
    for(int i=0;i<n;i++){
      if(scc[i]==scc[n+i]) return {};
      res[i]=scc[i]>scc[n+i];
    }
    return res;
  }
};
//END CUT HERE
#ifndef call_from_test
signed CFR441_C(){
  int n,m;
  scanf("%d %d",&n,&m);

  vector<vector<int>> G(n);
  for(int i=0;i<n;i++){
    int k;
    scanf("%d",&k);
    G[i].assign(k,0);
    for(int &v:G[i]){
      scanf("%d",&v);
      v--;
    }
  }
  auto NG=[](){puts("No");exit(0);};

  TwoSat ts(m);
  auto add_edge=
    [&](vector<int> &as,vector<int> &bs){
      int x=min(as.size(),bs.size());
      int i;
      for(i=0;i<x;i++){
        if(as[i]==bs[i]) continue;
        if(as[i]<bs[i]){
          ts.add_if(bs[i],as[i]);
        }else{
          ts.set_true(as[i]);
          ts.set_false(bs[i]);
        }
        break;
      }
      if((i==x)&&(as.size()>bs.size())) NG();
    };

  for(int i=0;i+1<n;i++)
    add_edge(G[i],G[i+1]);

  auto vs=ts.build();
  if(vs.empty()) NG();

  vector<int> ans;
  for(int i=0;i<m;i++)
    if(vs[i]) ans.emplace_back(i);

  puts("Yes");
  printf("%d\n",(int)ans.size());
  for(int i=0;i<(int)ans.size();i++){
    if(i) printf(" ");
    printf("%d",ans[i]+1);
  }
  puts("");

  return 0;
}
/*
  verified 2019/06/20
  http://codeforces.com/contest/875/problem/C
*/

signed YUKI_274(){
  int n,m;
  cin>>n>>m;
  vector<int> l(n),r(n);
  for(int i=0;i<n;i++) cin>>l[i]>>r[i],r[i]++;

  auto check=[&](int al,int ar,int bl,int br){
               return max(al,bl)<min(ar,br);};

  TwoSat ts(n);
  for(int i=0;i<n;i++){
    for(int j=0;j<i;j++){
      if(check(l[i],r[i],l[j],r[j])) ts.add_nand(i,j);
      if(check(l[i],r[i],m-r[j],m-l[j])) ts.add_nand(i,ts.negate(j));
      if(check(m-r[i],m-l[i],l[j],r[j])) ts.add_nand(ts.negate(i),j);
      if(check(m-r[i],m-l[i],m-r[j],m-l[j]))
        ts.add_nand(ts.negate(i),ts.negate(j));
    }
  }

  cout<<(ts.build().empty()?"NO":"YES")<<endl;
  return 0;
}
/*
  verified 2019/10/24
  https://yukicoder.me/problems/no/274
*/

signed YUKI_470(){
  int n;
  cin>>n;
  vector<string> u(n);
  for(int i=0;i<n;i++) cin>>u[i];

  auto NO=[](){cout<<"Impossible"<<endl;exit(0);};

  if(n>=100) NO();

  TwoSat ts(n);
  for(int i=0;i<n;i++){
    for(int j=0;j<i;j++){
      auto &as=u[i];
      auto &bs=u[j];
      if(as[0]==bs[0]&&as[1]==bs[1])
        ts.add_nand(i,j);

      if(as[0]==bs[1]&&as[1]==bs[2])
        ts.add_nand(i,ts.negate(j));

      if(as[1]==bs[0]&&as[2]==bs[1])
        ts.add_nand(ts.negate(i),j);

      if(as[1]==bs[1]&&as[2]==bs[2])
        ts.add_nand(ts.negate(i),ts.negate(j));

      if(as[0]==bs[0]) ts.add_nand(ts.negate(i),ts.negate(j));
      if(as[0]==bs[2]) ts.add_nand(ts.negate(i),j);
      if(as[2]==bs[0]) ts.add_nand(i,ts.negate(j));
      if(as[2]==bs[2]) ts.add_nand(i,j);
    }
  }

  auto res=ts.build();
  if(res.empty()) NO();

  for(int i=0;i<n;i++){
    if(res[i])
      cout<<u[i][0]<<u[i][1]<<" "<<u[i][2]<<endl;
    else
      cout<<u[i][0]<<" "<<u[i][1]<<u[i][2]<<endl;
  }
  return 0;
}
/*
  verified 2019/10/24
  https://yukicoder.me/problems/no/470
*/

signed main(){
  //CFR441_C();
  //YUKI_274();
  //YUKI_470();
  return 0;
}
#endif

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
