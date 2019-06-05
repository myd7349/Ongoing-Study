Moved to https://github.com/myd7349/libsodium-cmake via:

```bash
git clone https://github.com/myd7349/Ongoing-Study.git
pushd Ongoing-Study
git subtree split -P cpp/CMake/libsodium -b libsodium-cmake
popd

mkdir libsodium-cmake
cd libsodium-cmake
git init
git pull ../Ongoing-Study libsodium-cmake
git remote add origin https://github.com/myd7349/libsodium-cmake.git
git push origin -u master
```
