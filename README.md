# StarRod

### Development

```
cmake -H. -Bbuild-cmake -GNinja -DCMAKE_BUILD_TYPE=debug
cmake --build build-cmake -j
```

Then:

```
ninja -C ./build
```


#### Torch Utilities


```
./tools/generate-o2r.sh
```

```
./external/torch/build-cmake/torch modding export baserom.z64 -d ./extracted 2>&1
```