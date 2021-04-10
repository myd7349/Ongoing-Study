[Pipenv & Virtual Environments](https://docs.python-guide.org/dev/virtualenvs/)

[virtualenv](https://www.liaoxuefeng.com/wiki/1016959663602400/1019273143120480)

For example, we can build [ViTables](https://github.com/uvemas/ViTables/issues/79) with `virtualenv` like this:

> git clone https://github.com/uvemas/ViTables
>
> cd ViTables
>
> virtualenv venv
>
> venv\Scripts\activate
>
> pip install -r requirements.txt --proxy http://127.0.0.1:7080

https://github.com/pantsbuild/pex

[pex](https://github.com/pantsbuild/pex#development) uses [tox](https://testrun.org/tox/en/latest/) for test and development automation.

