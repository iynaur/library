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


# :warning: algorithm/onlineoffline.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/onlineoffline.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-17 15:56:23 +0900




## Depends on

* :heavy_check_mark: <a href="../tools/fastio.cpp.html">tools/fastio.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;
#endif
//BEGIN CUT HERE
namespace OnlineOffline{
  vector<int> used;

  template<typename T,typename F>
  void induce(int l,int r,int a,int b,vector<T> &dp,F dist){
    if(l==r) return;
    int m=(l+r)>>1;
    int idx=a;
    T res=dp[idx+1]+dist(idx,m);
    for(int i=a;i<b;i++){
      T tmp=dp[i+1]+dist(i,m);
      if(tmp<res) res=tmp,idx=i;
    }
    if(!used[m]) dp[m]=res,used[m]=1;
    else dp[m]=min(dp[m],res);
    induce(l,m,a,idx+1,dp,dist);
    induce(m+1,r,idx,b,dp,dist);
  }

  template<typename T,typename F>
  void solve(int l,int r,vector<T> &dp,F dist){
    if(l+1==r){
      if(!used[l]) dp[l]=dp[r]+dist(l,l),used[l]=1;
      else dp[l]=min(dp[l],dp[r]+dist(l,l));
      return;
    }
    int m=(l+r)>>1;
    solve(m,r,dp,dist);
    induce(l,m,m,r,dp,dist);
    solve(l,m,dp,dist);
  }

  // dp[i] = min_{i<j} dist(i,j-1) + dp[j]
  template<typename T,typename F>
  T solve(int n,F dist){
    vector<T> dp(n+1,0);
    used.assign(n+1,0);
    used[n]=1;
    solve(0,n,dp,dist);
    return dp[0];
  }
};
//END CUT HERE
#ifndef call_from_test

#define call_from_test
#include "../tools/fastio.cpp"
#undef call_from_test

//INSERT ABOVE HERE
using ll = long long;
signed YUKI_703(){
  int n;
  cin>>n;
  vector<ll> as(n),xs(n),ys(n);
  for(int i=0;i<n;i++) cin>>as[i];
  for(int i=0;i<n;i++) cin>>xs[i];
  for(int i=0;i<n;i++) cin>>ys[i];

  auto dist=
    [&](int i,int j)->ll{
      ll s=abs(as[i]-xs[j]);
      ll t=abs(ys[j]);
      return s*s+t*t;
    };

  cout<<OnlineOffline::solve<ll>(n,dist)<<endl;
  return 0;
}
/*
  verified on 2019/12/17
  https://yukicoder.me/problems/no/703
*/

signed YUKI_704(){
  int n;
  cin>>n;
  vector<ll> as(n),xs(n),ys(n);
  for(int i=0;i<n;i++) cin>>as[i];
  for(int i=0;i<n;i++) cin>>xs[i];
  for(int i=0;i<n;i++) cin>>ys[i];

  auto dist=
    [&](int i,int j)->ll{
      ll s=abs(as[i]-xs[j]);
      ll t=abs(ys[j]);
      return s+t;
    };

  cout<<OnlineOffline::solve<ll>(n,dist)<<endl;
  return 0;
}
/*
  verified on 2019/12/17
  https://yukicoder.me/problems/no/704
*/

signed YUKI_705(){
  int n;
  cin>>n;
  vector<ll> as(n),xs(n),ys(n);
  for(int i=0;i<n;i++) cin>>as[i];
  for(int i=0;i<n;i++) cin>>xs[i];
  for(int i=0;i<n;i++) cin>>ys[i];

  auto dist=
    [&](int i,int j)->ll{
      ll s=abs(as[i]-xs[j]);
      ll t=abs(ys[j]);
      return s*s*s+t*t*t;
    };

  cout<<OnlineOffline::solve<ll>(n,dist)<<endl;
  return 0;
}
/*
  verified on 2019/12/17
  https://yukicoder.me/problems/no/705
*/


signed main(){
  //YUKI_703();
  //YUKI_704();
  //YUKI_705();
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
onlinejudge_verify.bundle.BundleError: algorithm/onlineoffline.cpp: line 5: found codes out of include guard

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
