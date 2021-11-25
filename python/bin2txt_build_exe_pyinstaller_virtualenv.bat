mkdir build\bin2txt-pyinstaller-virtualenv
pushd build\bin2txt-pyinstaller-virtualenv

copy /b ..\..\bin2txt.py .\bin2txt.py
copy /b ..\..\math_eval_v1.py .\math_eval_v1.py
copy /b ..\..\unpacker.py .\unpacker.py
copy /b ..\..\fileutil.py .\fileutil.py

mkdir pypi\downloads
pushd pypi\downloads
pip download --no-cache --proxy http://127.0.0.1:7080 pyparsing pyinstaller
popd

virtualenv --no-download --extra-search-dir=pypi\downloads bin2txt-venv
.\bin2txt-venv\Scripts\activate.bat

:: pip install pyparsing
:: pip install pyinstaller
:: pyinstaller bin2txt.py --workpath build\bin2txt\pyinstaller\build --specpath build\bin2txt\pyinstaller\build --distpath build\bin2txt\pyinstaller\ --noconfirm --onefile


:: References:
:: [How can i create a new virtualenv using proxy?](https://github.com/pypa/virtualenv/issues/1156)
