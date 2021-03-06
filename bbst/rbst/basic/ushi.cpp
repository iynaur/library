#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "base.cpp"
#undef call_from_test

#endif
//BEGIN CUT HERE
template<typename Tp>
struct NodeBase{
  using T = Tp;
  NodeBase *l,*r,*p;
  size_t cnt;
  bool rev;
  T val,dat;
  NodeBase():cnt(1),rev(0){l=r=p=nullptr;}
  NodeBase(T val):
    cnt(1),rev(0),val(val),dat(val){l=r=p=nullptr;}
};

template<typename Node, size_t LIM>
struct Ushi : BBSTBase<Node, LIM>{
  using super = BBSTBase<Node, LIM>;

  using T = typename Node::T;

  using F = function<T(T, T)>;
  using S = function<T(T)>;

  F f;
  S flip;
  T ti;

  Ushi(F f,T ti):super(),f(f),ti(ti){
    flip=[](T a){return a;};
  }

  Ushi(F f,S flip,T ti):
    super(),f(f),flip(flip),ti(ti){}

  T query(const Node *a){
    return a?a->dat:ti;
  }

  using super::count;
  Node* recalc(Node *a){
    a->cnt=count(a->l)+1+count(a->r);
    a->dat=a->val;
    if(a->l) a->dat=f(a->l->dat,a->dat);
    if(a->r) a->dat=f(a->dat,a->r->dat);
    return a;
  }

  using super::toggle;
  void toggle(Node *a){
    swap(a->l,a->r);
    a->dat=flip(a->dat);
    a->rev^=1;
  }

  // remove "virtual" for optimization
  virtual Node* eval(Node* a){
    if(a->rev){
      if(a->l) toggle(a->l);
      if(a->r) toggle(a->r);
      a->rev=false;
    }
    return recalc(a);
  }

  using super::merge;
  using super::split;

  T query(Node *&a,size_t l,size_t r){
    auto s=split(a,l);
    auto t=split(s.second,r-l);
    auto u=t.first;
    T res=query(u);
    a=merge(s.first,merge(u,t.second));
    return res;
  }

  Node* set_val(Node *a,size_t k,T val){
    assert(k<count(a));
    a=eval(a);
    size_t num=count(a->l);
    if(k<num) a->l=set_val(a->l,k,val);
    if(k>num) a->r=set_val(a->r,k-(num+1),val);
    if(k==num) a->val=val;
    return recalc(a);
  }

  T get_val(Node *a,size_t k){
    return super::find_by_order(a,k)->val;
  }

  void dump(Node* a,typename vector<T>::iterator it){
    if(!count(a)) return;
    if(a->rev){
      if(a->l) toggle(a->l);
      if(a->r) toggle(a->r);
      a->rev=false;
    }
    dump(a->l,it);
    *(it+count(a->l))=a->val;
    dump(a->r,it+count(a->l)+1);
  }

  // destroy data
  vector<T> dump(Node* a){
    vector<T> vs(count(a));
    dump(a,vs.begin());
    return vs;
  }
};
//END CUT HERE
#ifndef call_from_test
//INSERT ABOVE HERE

// test toggle
signed HAPPYQUERY_C(){
  cin.tie(0);
  ios::sync_with_stdio(0);

  int n;
  cin>>n;
  vector<int> vs(n);
  for(int i=0;i<n;i++) cin>>vs[i];

  int q;
  cin>>q;
  vector<int> ts(q);
  vector<int> ls(q),rs(q);
  vector<int> ps(q),xs(q);
  vector<int> as(q),bs(q),cs(q),ds(q);
  for(int i=0;i<q;i++){
    cin>>ts[i];
    if(ts[i]==1) cin>>ls[i]>>rs[i],ls[i]--;
    if(ts[i]==2) cin>>ps[i]>>xs[i],ps[i]--;
    if(ts[i]==3){
      cin>>as[i]>>bs[i]>>cs[i]>>ds[i];
      as[i]--;cs[i]--;
    }
  }

  using ll = long long;
  auto f=[](ll a,ll b){return a+b;};
  ll ti=0;

  using Node=NodeBase<ll>;
  constexpr size_t LIM = 1e6;
  Ushi<Node, LIM> G(f,ti);

  unordered_map<int, ll> memo;
  auto hs=
    [&](int x){
      if(!memo.count(x))
        memo[x]=G.xor128();
      return memo[x];
    };

  vector<Node> ws(n);
  for(int i=0;i<n;i++) ws[i]=Node(hs(vs[i]));
  auto rt=G.build(ws);

  for(int i=0;i<q;i++){
    if(ts[i]==1) rt=G.toggle(rt,ls[i],rs[i]);
    if(ts[i]==2) rt=G.set_val(rt,ps[i],hs(xs[i]));
    if(ts[i]==3){
      ll x=G.query(rt,as[i],bs[i]);
      ll y=G.query(rt,cs[i],ds[i]);
      cout<<(x==y?"Yes":"No")<<"\n";
    }
  }
  cout<<flush;
  return 0;
}
/*
  verified on 2019/06/24
  https://www.hackerrank.com/contests/happy-query-contest/challenges/range-sorting-query
*/

signed main(){
  HAPPYQUERY_C();
  return 0;
}
#endif
