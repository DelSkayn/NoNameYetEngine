BUILD_TARGET="Debug"

if ["$#" == 0]; then
    BUILD_TARGET="Debug"
else
    BUILD_TARGET="$1"
fi

cd winbuild
cmake -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ -DCMAKE_BUILD_TYPE="$BUILD_TARGET" ../
make -j 12
rsync -u -r ../res/ ./res
