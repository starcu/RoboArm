if [ $1 = "release" ]; then
	build_type="Release"
	dir="cmake-build-release-remoterpi"
else
	build_type="Debug"
	dir="cmake-build-debug-remoterpi"
fi

if [ -d $dir ]; then
        rm -rf $dir
fi
mkdir $dir && cd $dir

echo "-- Build type" $build_type

cmake -DCMAKE_BUILD_TYPE=$build_type ../
