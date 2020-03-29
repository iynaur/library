#ifndef call_from_test
#include <bits/stdc++.h>
using namespace std;

#endif
//BEGIN CUT HERE
struct Vertex{
  void* handle;
  int idx;
  Vertex(int idx=-1):handle(nullptr),idx(idx){}
};

template<typename T>
struct Farthest{
  struct pi{
    T dist;
    int idx;
    pi():dist(0),idx(-1){}
    pi(T dist,int idx):dist(dist),idx(idx){}
    bool operator<(const pi &o)const{return dist<o.dist;}
    pi operator+(const T e)const{return pi(dist+e,idx);}
  };
  pi md,lf,rg;
  T len;
  Farthest(){}
  Farthest(T l,int f,int t):lf(l,t),rg(l,f),len(l){}
  Farthest(pi md,pi lf,pi rg,T len):
    md(md),lf(lf),rg(rg),len(len){}
  void toggle(){swap(lf,rg);}
  static Farthest compress(Farthest x,Vertex*,Farthest y){
    return Farthest(
      max(x.rg,y.lf),
      max(x.lf,y.lf+x.len),
      max(y.rg,x.rg+y.len),
      x.len+y.len);
  }
  static Farthest rake(Farthest x,Farthest y,Vertex*){
    return Farthest(pi(),max(x.lf,y.rg+x.len),max(x.rg,y.rg),x.len);
  }
};
//END CUT HERE
#ifndef call_from_test
//INSERT ABOVE HERE

#define call_from_test
#include "toptree.cpp"
#undef call_from_test

signed KUPC2020_G(){
  cin.tie(0);
  ios::sync_with_stdio(0);
  const char newl = '\n';

  const size_t LIM = 1e6;
  using Cluster = Farthest<long long>;
  TopTree<Vertex, Cluster, LIM> T(Cluster(0,-1,-1));

  int n;
  cin>>n;

  vector<Vertex*> vs(n);
  for(int i=0;i<n;i++)
    vs[i]=T.create(Vertex(i));

  vector<int> as(n),bs(n),ds(n);
  for(int i=1;i<n;i++){
    cin>>as[i]>>bs[i]>>ds[i];
    as[i]--;bs[i]--;
    T.link(vs[as[i]],Cluster(ds[i],as[i],bs[i]),vs[bs[i]]);
  }

  int q;
  cin>>q;

  int cur=0;
  for(int i=0;i<q;i++){
    int t;
    cin>>t;
    if(t==1){
      int x;
      cin>>x;
      x--;
      cur=x;
    }
    if(t==2){
      int y;
      cin>>y;
      T.cut(vs[as[y]],vs[bs[y]]);
    }
    if(t==3){
      int z;
      cin>>z;
      T.link(vs[as[z]],Cluster(ds[z],as[z],bs[z]),vs[bs[z]]);
    }
    auto dist=T.expose(vs[cur])->dat.md.dist;
    vector<int> ans;
    while(1){
      auto res=T.expose(vs[cur])->dat.md;
      if(dist!=res.dist) break;
      ans.emplace_back(res.idx);
      break;
    }
    sort(ans.begin(),ans.end());
    cout<<ans.size();
    for(int v:ans) cout<<" "<<v+1;
    cout<<newl;
  }

  return 0;
}

signed main(){
  KUPC2020_G();
  return 0;
}
#endif