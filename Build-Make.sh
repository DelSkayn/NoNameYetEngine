BUILD_TARGET="Debug"

if ["$#" == 0]; then
    BUILD_TARGET="Debug"
else
    BUILD_TARGET="$1"
fi

if [ ! -d "build" ]; then
    mkdir build
fi
cd build
cmake -DCMAKE_BUILD_TYPE="$BUILD_TARGET" ../
make -j 8 
rsync -v -u -r ../res/ ./res
