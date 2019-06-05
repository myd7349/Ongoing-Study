2016-12-21T01:49:06+08:00

In Ruby, we may use `fnmatch` like this:

```ruby
C:\Users\myd>irb
irb(main):001:0> File.fnmatch('*.{dll,exe}', 'a.dll', File::FNM_EXTGLOB | File::FNM_CASEFOLD)
=> true
irb(main):002:0> File.fnmatch('*.{dll,exe}', 'a.Exe', File::FNM_EXTGLOB | File::FNM_CASEFOLD)
=> true
```

It seems that Python version of `fnmatch` doesn't support matching pattern shown above.

http://man7.org/linux/man-pages/man3/fnmatch.3.html

http://man7.org/linux/man-pages/man7/glob.7.html
