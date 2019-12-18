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


# :warning: mod/tetration.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ad148a3ca8bd0ef3b48c52454c493ec5">mod</a>
* <a href="{{ site.github.repository_url }}/blob/master/mod/tetration.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-17 20:42:16 +0900




## Depends on

* :heavy_check_mark: <a href="../math/totient.cpp.html">math/totient.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "../math/totient.cpp"
#undef call_from_test

#endif
//BEGIN CUT HERE
template<typename T>
T mpow(T a,T n,T m,T &f){
  using ull = unsigned long long;
  if(a==1||n==0) return 1;
  ull v=1,x=a,z=m;
  f|=x>=z;
  x%=m;
  while(1){
    if(n&1) v*=x;
    if(v>=z) f=1,v%=m;
    n>>=1;
    if(!n) break;
    x=x*x;
    if(x>=z) f=1,x%=m;
  }
  return v;
}

template<typename T>
T tetration(T a,T n,T m,T &f){
  if(a==0) return ~n&1;
  if(m==1) return f=1;
  if(a==1||n==0) return 1;
  if(n==1){
    f|=a>=m;
    return a%m+f*m;
  }
  T z=tetration(a,n-1,totient(m),f);
  T r=mpow(a,z,m,f);
  return r+f*m;
}

template<typename T>
T tetration(T a,T n,T m){
  T f=0;
  return tetration(a,n,m,f)%m;
}
//END CUT HERE
#ifndef call_from_test
//INSERT ABOVE HERE

signed YUKI_181(){
  int a,n,m;
  cin>>a>>n>>m;
  cout<<tetration(a,n,m)<<endl;
  return 0;
}
/*
  verified on 2019/12/17
  https://yukicoder.me/problems/no/181
*/

signed SUMMERFES2018_F(){
  using ll = long long;

  ll a,m,k;
  cin>>a>>m>>k;
  ll ans=0;

  k--;
  for(ll i=0,p=-1;i<k;i++){
    ll x=tetration(a,i,m);
    if(p==x){
      ans+=(k-i)%m*x%m;
      ans%=m;
      break;
    }
    ans+=x;
    ans%=m;
    p=x;
  }
  cout<<ans<<endl;
  return 0;
}
/*
  verified on 2019/12/17
  https://atcoder.jp/contests/summerfes2018-div1/tasks/summerfes2018_f
*/

signed SPOJ_POWTOW(){
  using ll = long long;

  int T;
  cin>>T;
  while(T--){
    ll a,n,f=0;
    cin>>a>>n;
    stringstream ss;
    ss<<tetration(a,n,ll(1e9),f)%ll(1e9);
    auto s=ss.str();
    if(f){
      while(s.size()<9u) s='0'+s;
      cout<<"..."<<s<<endl;
    }else{
      cout<<s<<endl;
    }
  }
  return 0;
}
/*
  verified on 2019/10/08
  https://www.spoj.com/problems/POWTOW/
*/

signed SPOJ_MTETRA(){
  using ll = long long;
  int T;
  cin>>T;
  while(T--){
    ll a,n,m;
    cin>>a>>n>>m;
    cout<<tetration(a,n,m)<<endl;;
  }
  return 0;
}
/*
  verified on 2019/10/08
  https://www.spoj.com/problems/MTETRA/
*/

signed main(){
  //YUKI_181();
  //SUMMERFES2018_F();
  //SPOJ_POWTOW();
  //SPOJ_MTETRA();
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
  File "/opt/hostedtoolcache/Python/3.8.0/x64/lib/python3.8/site-packages/onlinejudge_verify/bundle.py", line 150, in update
    self.update(self._resolve(included, included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.0/x64/lib/python3.8/site-packages/onlinejudge_verify/bundle.py", line 52, in _resolve
    raise BundleError(path, -1, "no such header")
onlinejudge_verify.bundle.BundleError: ../math/totient.cpp: line -1: no such header

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
