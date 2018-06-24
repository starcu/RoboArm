if [ -d "build" ]; then
	rm -rf build
fi
mkdir build && cd build
if [[ $1 = "release" ]]; then
	build_type="Release"
else
	build_type="Debug"
fi

echo "-- Build type" $build_type

cmake -DCMAKE_BUILD_TYPE=$build_type ../