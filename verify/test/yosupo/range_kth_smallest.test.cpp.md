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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: test/yosupo/range_kth_smallest.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0b58406058f6619a0f31a172defc0230">test/yosupo</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/range_kth_smallest.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-05 21:02:53+09:00


* see: <a href="https://judge.yosupo.jp/problem/range_kth_smallest">https://judge.yosupo.jp/problem/range_kth_smallest</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/datastructure/waveletmatrix.cpp.html">datastructure/waveletmatrix.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "../../datastructure/waveletmatrix.cpp"
#undef call_from_test

signed main(){
  cin.tie(0);
  ios::sync_with_stdio(0);

  int n,q;
  cin>>n>>q;

  vector<int> as(n);
  for(int i=0;i<n;i++) cin>>as[i];

  WaveletMatrix<int, 30> wm(as);

  for(int i=0;i<q;i++){
    int l,r,k;
    cin>>l>>r>>k;
    cout<<wm.rquantile(l,r,k)<<"\n";
  }
  cout<<flush;
  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo/range_kth_smallest.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#line 1 "test/yosupo/../../datastructure/waveletmatrix.cpp"

#line 3 "test/yosupo/../../datastructure/waveletmatrix.cpp"
using namespace std;
#endif
/**
 * @docs docs/waveletmatrix.md
 */
//BEGIN CUT HERE
struct FullyIndexableDictionary{
  int len,blk;
  vector<unsigned> bit;
  vector<int> sum;

  FullyIndexableDictionary(){}
  FullyIndexableDictionary(int len)
    :len(len),blk((len+31)>>5),bit(blk,0),sum(blk,0){}

  void set(int k){
    bit[k>>5]|=1u<<(k&31);
  }

  void build(){
    sum[0]=0;
    for(int i=1;i<blk;i++)
      sum[i]=sum[i-1]+__builtin_popcount(bit[i-1]);
  }

  bool operator[](int k) const{
    return bool((bit[k>>5]>>(k&31))&1);
  }

  int rank(int k){
    return sum[k>>5]+__builtin_popcount(bit[k>>5]&((1u<<(k&31))-1));
  }

  int rank(bool v,int k){
    return (v?rank(k):k-rank(k));
  }

  int select(bool v,int k){
    if(k<0||rank(v,len)<=k) return -1;
    int l=0,r=len;
    while(l+1<r){
      int m=(l+r)>>1;
      if(rank(v,m)>=k+1) r=m;
      else l=m;
    }
    return r-1;
  }

  int select(bool v,int i,int l){
    return select(v,i+rank(v,l));
  }
};

template<class T,int MAXLOG>
struct WaveletMatrix{
  int len;
  FullyIndexableDictionary mat[MAXLOG];
  int zs[MAXLOG],buff1[MAXLOG],buff2[MAXLOG];
  static const T npos=-1;

  WaveletMatrix(vector<T> data){
    len=data.size();
    vector<T> ls(len),rs(len);
    for(int dep=0;dep<MAXLOG;dep++){
      mat[dep]=FullyIndexableDictionary(len+1);
      int p=0,q=0;
      for(int i=0;i<len;i++){
        bool k=(data[i]>>(MAXLOG-(dep+1)))&1;
        if(k) rs[q++]=data[i],mat[dep].set(i);
        else  ls[p++]=data[i];
      }
      zs[dep]=p;
      mat[dep].build();
      swap(ls,data);
      for(int i=0;i<q;i++) data[p+i]=rs[i];
    }
  }

  T access(int k){
    T res=0;
    for(int dep=0;dep<MAXLOG;dep++){
      bool bit=mat[dep][k];
      res=(res<<1)|bit;
      k=mat[dep].rank(bit,k)+zs[dep]*dep;
    }
    return res;
  }

  // return the number of v in [0,k)
  int rank(T v,int k){
    int l=0,r=k;
    for(int dep=0;dep<MAXLOG;dep++){
      buff1[dep]=l;buff2[dep]=r;
      bool bit=(v>>(MAXLOG-(dep+1)))&1;
      l=mat[dep].rank(bit,l)+zs[dep]*bit;
      r=mat[dep].rank(bit,r)+zs[dep]*bit;
    }
    return r-l;
  }

  // return the position of k-th v
  int select(T v,int k){
    rank(v,len);
    for(int dep=MAXLOG-1;dep>=0;dep--){
      bool bit=(v>>(MAXLOG-(dep+1)))&1;
      k=mat[dep].select(bit,k,buff1[dep]);
      if(k>=buff2[dep]||k<0) return -1;
      k-=buff1[dep];
    }
    return k;
  }

  int select(T v,int k,int l){
    return select(v,k+rank(v,l));
  }

  // return k-th largest value in [l,r)
  T quantile(int l,int r,int k){
    if(r-l<=k||k<0) return -1;
    T res=0;
    for(int dep=0;dep<MAXLOG;dep++){
      int p=mat[dep].rank(1,l);
      int q=mat[dep].rank(1,r);
      if(q-p>k){
        l=p+zs[dep];
        r=q+zs[dep];
        res|=T(1)<<(MAXLOG-(dep+1));
      }else{
        k-=(q-p);
        l-=p;
        r-=q;
      }
    }
    return res;
  }

  T rquantile(int l,int r,int k){
    return quantile(l,r,r-l-k-1);
  }

  int freq_dfs(int d,int l,int r,T val,T a,T b){
    if(l==r) return 0;
    if(d==MAXLOG) return (a<=val&&val<b)?r-l:0;
    T nv=T(1)<<(MAXLOG-d-1)|val;
    T nnv=((T(1)<<(MAXLOG-d-1))-1)|nv;
    if(nnv<a||b<=val) return 0;
    if(a<=val&&nnv<b) return r-l;
    int lc=mat[d].rank(1,l),rc=mat[d].rank(1,r);
    return freq_dfs(d+1,l-lc,r-rc,val,a,b)
      +freq_dfs(d+1,lc+zs[d],rc+zs[d],nv,a,b);
  }

  // return number of points in [left, right) * [lower, upper)
  int rangefreq(int left,int right,T lower,T upper){
    return freq_dfs(0,left,right,0,lower,upper);
  }

  pair<int, int> ll(int l,int r,T v){
    int res=0;
    for(int dep=0;dep<MAXLOG;dep++){
      buff1[dep]=l;buff2[dep]=r;
      bool bit=(v>>(MAXLOG-(dep+1)))&1;
      if(bit) res+=r-l+mat[dep].rank(bit,l)-mat[dep].rank(bit,r);
      l=mat[dep].rank(bit,l)+zs[dep]*bit;
      r=mat[dep].rank(bit,r)+zs[dep]*bit;
    }
    return make_pair(res,r-l);
  }

  int lt(int l,int r,T v){
    auto p=ll(l,r,v);
    return p.first;
  }

  int le(int l,int r,T v){
    auto p=ll(l,r,v);
    return p.first+p.second;
  }

  T succ(int l,int r,T v){
    int k=le(l,r,v);
    return k==r-l?npos:rquantile(l,r,k);
  }

  T pred(int l,int r,T v){
    int k=lt(l,r,v);
    return k?rquantile(l,r,k-1):npos;
  }
};
//END CUT HERE
#ifndef call_from_test
//INSERT ABOVE HERE
signed main(){
  return 0;
}
#endif
#line 8 "test/yosupo/range_kth_smallest.test.cpp"
#undef call_from_test

signed main(){
  cin.tie(0);
  ios::sync_with_stdio(0);

  int n,q;
  cin>>n>>q;

  vector<int> as(n);
  for(int i=0;i<n;i++) cin>>as[i];

  WaveletMatrix<int, 30> wm(as);

  for(int i=0;i<q;i++){
    int l,r,k;
    cin>>l>>r>>k;
    cout<<wm.rquantile(l,r,k)<<"\n";
  }
  cout<<flush;
  return 0;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
