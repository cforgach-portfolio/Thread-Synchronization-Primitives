#!/usr/bin/bash
mkdir -p src/build
pushd src/build
cmake ..
make -j
make -j
mv SyncPrimitives ../..
popd