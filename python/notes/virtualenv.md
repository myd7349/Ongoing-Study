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

- [How can i create a new virtualenv using proxy? · Issue #1156 · pypa/virtualenv · GitHub](https://github.com/pypa/virtualenv/issues/1156)
  
  > ```
  > mkdir -p /opt/pypi/downloads
  > pushd /opt/pypi/downloads
  > pip download --no-cache --proxy http://proxy:3128 setuptools wheel pip
  > popd
  > virtualenv --no-download --extra-search-dir /opt/pypi/downloads virtualenv
  > ```

https://github.com/Z3Prover/z3

```bash
virtualenv venv
source venv/bin/activate
python scripts/mk_make.py --python
cd build
make
make install
# You will find Z3 and the Python bindings installed in the virtual environment
venv/bin/z3 -h
...
python -c 'import z3; print(z3.get_version_string())'
# ...
```
