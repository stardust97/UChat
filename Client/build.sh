#！/bin/bash
set -o errexit

DIR=`pwd`
if [ -d build ]; then
  rm -rf build
fi

mkdir build

IS_X86=true
IS_ARM=false

IS_DEBUG=false
IS_TEST=false
IS_INSTALL=false

for i in "$@"; do
  if [ "$i" = "-platform=arm6" -o "$i" = "-a6" ]; then
    IS_ARM=true
    IS_X86=false
  elif [ "$i" = "-install=true" -o "$i" = "-i" ]; then
    IS_INSTALL=true
  elif [ "$i" = "-debug=true" -o "$i" = "-d" ]; then
    IS_DEBUG=true
  elif [ "$i" = "-test=true" -o "$i" = "-t" ]; then
    IS_TEST=true
  fi
done

if [ $IS_ARM = true ]; then
  echo "build arm platform"
  # SET compiler path
  # CMAKE_COMMAND="$CMAKE_COMMAND -DCOMPILE_TOOLCHAIN_ROOT=$DIR/../autodrive-arm"
else
  echo "build x86 platform"
fi

if [ $IS_DEBUG = true ]; then
  CMAKE_COMMAND="$CMAKE_COMMAND -DCOMPILE_TOOLCHAIN_ROOT_DEBUG=ON"
  echo "build enable debug "
fi

if [ $IS_TEST = true ]; then
  CMAKE_COMMAND="$CMAKE_COMMAND -DCOMPILE_TOOLCHAIN_ROOT_TEST=ON"
  echo "build enable test "
fi

# Check command exit if success
CheckCommand() {
  if [ $? -ne 0 ]; then
    exit 1;
  fi
}

cd build
cmake .. $CMAKE_COMMAND
CheckCommand
make -j4
CheckCommand
echo "Build Done"
make install
echo "Install Done"
cd $DIR

# Strip
if [ $IS_ARM = true ]; then
  # STRIP_COMMAND=$DIR/../autodrive-arm/gcc-linaro-6.5.0-2018.12-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-strip
  echo "please set STRIP_COMMAND"
else
  STRIP_COMMAND=strip
fi

if [ $IS_DEBUG = false ]; then
#todo
  $STRIP_COMMAND -s build/output/client/bin/*
  echo "strip success"
else 
  echo "build debug version"
fi
