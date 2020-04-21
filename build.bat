mkdir build
cd build
cmake ../src -DVCPKG_TARGET_TRIPLET=x64-windows-learn
cmake --build .