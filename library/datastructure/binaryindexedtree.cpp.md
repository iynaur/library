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


# :heavy_check_mark: datastructure/binaryindexedtree.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8dc87745f885a4cc532acd7b15b8b5fe">datastructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/datastructure/binaryindexedtree.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-09 23:51:01 +0900




## Depends on

* :heavy_check_mark: <a href="../tools/fastio.cpp.html">tools/fastio.cpp</a>


## Required by

* :heavy_check_mark: <a href="../linkcuttree/subtree.cpp.html">linkcuttree/subtree.cpp</a>
* :heavy_check_mark: <a href="../string/zalgorithm.cpp.html">string/zalgorithm.cpp</a>
* :heavy_check_mark: <a href="../tools/bigint.cpp.html">tools/bigint.cpp</a>
* :heavy_check_mark: <a href="../tree/eulertourforedge.cpp.html">tree/eulertourforedge.cpp</a>
* :heavy_check_mark: <a href="../tree/eulertourforvertex.cpp.html">tree/eulertourforvertex.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/DSL_2_B.test.cpp.html">test/aoj/DSL_2_B.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj/GRL_5_D.test.cpp.html">test/aoj/GRL_5_D.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/point_add_range_sum.test.cpp.html">test/yosupo/point_add_range_sum.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/vertex_add_path_sum.test.cpp.html">test/yosupo/vertex_add_path_sum.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yosupo/vertex_add_subtree_sum.test.cpp.html">test/yosupo/vertex_add_subtree_sum.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;
#endif
//BEGIN CUT HERE
template<typename T>
struct BIT{
  int n;
  vector<T> bit;
  //1-indexed
  BIT(int n_):n(n_+1),bit(n,0){}

  T sum(int i){
    T s(0);
    for(int x=i;x>0;x-=(x&-x))
      s+=bit[x];
    return s;
  }

  void add(int i,T a){
    if(i==0) return;
    for(int x=i;x<=n;x+=(x&-x))
      bit[x]+=a;
  }

  int lower_bound(int w){
    if(w<=0) return 0;
    int x=0,r=1;
    while(r<n) r<<=1;
    for(int k=r;k>0;k>>=1){
      if(x+k<=n&&bit[x+k]<w){
        w-=bit[x+k];
        x+=k;
      }
    }
    return x+1;
  }

  // [l, r)
  T query(int l,int r){
    return sum(r-1)-sum(l-1);
  }

  T sum0(int i){
    return sum(i+1);
  }

  void add0(int i,T a){
    add(i+1,a);
  }

  T query0(int l,int r){
    return sum(r)-sum(l);
  }
};
//END CUT HERE
#ifndef call_from_test

#define call_from_test
#include "../tools/fastio.cpp"
#undef call_from_test

// lower_bound
signed ARC033_C(){
  int q;
  cin>>q;
  BIT<int> bit(2e5);
  while(q--){
    int t,x;
    cin>>t>>x;
    if(t==1) bit.add(x,1);
    if(t==2){
      int k=bit.lower_bound(x);
      bit.add(k,-1);
      cout<<k<<endl;
    }
  }
  return 0;
}
/*
  verified on 2019/11/11
  https://atcoder.jp/contests/arc033/tasks/arc033_3
*/

signed main(){
  ARC033_C();
  return 0;
}
#endif

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.0/x64/lib/python3.8/site-packages/onlinejudge_verify/main.py", line 175, in main
    subcommand_run(paths=[], jobs=parsed.jobs)
  File "/opt/hostedtoolcache/Python/3.8.0/x64/lib/python3.8/site-packages/onlinejudge_verify/main.py", line 72, in subcommand_run
    onlinejudge_verify.verify.main(paths, marker=marker, timeout=timeout, jobs=jobs)
  File "/opt/hostedtoolcache/Python/3.8.0/x64/lib/python3.8/site-packages/onlinejudge_verify/verify.py", line 71, in main
    exec_command([cxx, *cxxflags, '-I', '.', '-o', shlex.quote(str(directory / 'a.out')), shlex.quote(str(path))])
  File "/opt/hostedtoolcache/Python/3.8.0/x64/lib/python3.8/site-packages/onlinejudge_verify/verify.py", line 26, in exec_command
    subprocess.check_call(command)
  File "/opt/hostedtoolcache/Python/3.8.0/x64/lib/python3.8/subprocess.py", line 364, in check_call
    raise CalledProcessError(retcode, cmd)
subprocess.CalledProcessError: Command '['g++', '-std=c++17', '-O2', '-Wall', '-g', '-I', '.', '-o', '.verify-helper/cache/9a267fd1c42d1001b78ef88b806279fc/a.out', 'test/aoj/DPL_5_C.test.cpp']' returned non-zero exit status 1.

During handling of the above exception, another exception occurred:

Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.0/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 339, in write_contents
    bundler.update(self.file_class.file_path)
  File "/opt/hostedtoolcache/Python/3.8.0/x64/lib/python3.8/site-packages/onlinejudge_verify/bundle.py", line 119, in update
    raise BundleError(path, i + 1, "found codes out of include guard")
onlinejudge_verify.bundle.BundleError: datastructure/binaryindexedtree.cpp: line 5: found codes out of include guard

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
