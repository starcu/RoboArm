if [ $1 = release ]; then
    echo "Release build started..."
    cd cmake-build-release-remoterpi
else
    echo "Debug build started..."
    cd cmake-build-debug-remoterpi
fi
make -j2
