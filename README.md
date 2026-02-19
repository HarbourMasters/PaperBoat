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

# Configuration

### Default keyboard configuration
| N64 | A | B | Z | Start | Analog stick | C buttons | D-Pad |
| - | - | - | - | - | - | - | - |
| Keyboard | X | C | Z | Space | WASD | Arrow keys | TFGH |

### Other shortcuts
| Keys | Action |
| - | - |
| Esc | Toggle menu |
| Ctrl+R | Reset (inside levels) |
| F11 | Fullscreen |
| Tab | Toggle Alternate assets |
