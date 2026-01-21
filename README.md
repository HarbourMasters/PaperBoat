# StarRod

### Development

```
cmake -H. -Bbuild -GNinja -DCMAKE_BUILD_TYPE=debug
cmake --build build -j
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