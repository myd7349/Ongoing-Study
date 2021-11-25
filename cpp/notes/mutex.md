1. [Recursive (Re-entrant) Locks](https://blog.stephencleary.com/2013/04/recursive-re-entrant-locks.html)
   
   [递归锁的缺点](https://mthli.xyz/recursive-re-entrant-locks/) - [GitHub](https://github.com/mthli/blog/blob/master/content/blog/recursive-re-entrant-locks/index.md)
   
   https://twitter.com/mth_li/status/1449938778823426054
   
   > 之前在翻阅 WebRTC 新版本代码的时候，发现 Google 基本把递归锁（可重入）改成非递归（不可重入）的形式了。

2. mutex
   
   https://twitter.com/middlefeng/status/1494426825128243206
   
   > atomic 和 mutex 一样，都是最简单的强制同步 cache。唯一的区别是没有 sleep list 不能挂起。mutex 没有 race 的时候就是一个 atomic
