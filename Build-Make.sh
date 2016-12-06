#source /vol/share/software/gcc/5.3.0-profile
#LD_LIBRARY_PATH="/vol/share/software/gcc/5.3.0/lib64:$LD_LIBRARY_PATH"
#export LD_LIBRARY_PATH

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
cmake -DCMAKE_BUILD_TYPE="$BUILD_TARGET" ../ -Wno-dev
make -j 64
rsync -v -u -r ../res/ ./res
