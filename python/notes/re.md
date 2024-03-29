[Regular Expression HOWTO](https://docs.python.org/3/howto/regex.html)

[How can I check if a URL is absolute using Python?](https://stackoverflow.com/questions/8357098/how-can-i-check-if-a-url-is-absolute-using-python)

>Please DON'T use a regex just to check that a string starts with some known prefix. Use the startswith method of a string for that.

Character class support:
- [Can I mix character classes in Python RegEx?](https://stackoverflow.com/questions/12349118/can-i-mix-character-classes-in-python-regex)

Regular expressions for China mobile phone numbers:
- [china-mobile-phone-regexp](https://github.com/node-modules/china-mobile-phone-regexp/blob/master/index.js)

SemVer:
- [Is there a suggested regular expression (RegEx) to check a SemVer string?](https://semver.org/#is-there-a-suggested-regular-expression-regex-to-check-a-semver-string) - [vcpkg uses this RE](https://github.com/microsoft/vcpkg/pull/13777/files)

[Regexp for a double](https://stackoverflow.com/questions/10516967/regexp-for-a-double)

import tokenize; tokenize.Pointfloat; tokenize.Expfloat

https://github.com/triton-inference-server/client/blob/d07efb84f938bce126e4d0a0541629113ffe6d53/src/python/library/build_wheel.py#L51-L66

> ```python
> def sed(pattern, replace, source, dest=None):
>     fin = open(source, 'r')
>     if dest:
>         fout = open(dest, 'w')
>     else:
>         fd, name = mkstemp()
>         fout = open(name, 'w')
> 
>     for line in fin:
>         out = re.sub(pattern, replace, line)
>         fout.write(out)
> 
>     fin.close()
>     fout.close()
>     if not dest:
>         shutil.copyfile(name, source)
> ```

Regex for datetime:

- [YYYY-MM-DD](https://www.regextester.com/96683)

  > [12]\d{3}-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01])

- Regular Expressions Cookbook 4.5. Accurately Validate Traditional Date Formats: https://www.oreilly.com/library/view/regular-expressions-cookbook/9780596802837/ch04s05.html

https://github.com/daviddrysdale/python-phonenumbers/blob/dev/python/phonenumbers/re_util.py

https://github.com/bee-san/pyWhat
