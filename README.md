# vbmeta-disable-verification

Patch Android vbmeta image and disable verification flags inside.

## Usage

Get prebuilts from [releases](https://github.com/libxzr/vbmeta-disable-verification/releases).

```
$ ./vbmeta-disable-verification vbmeta.img 
Successfully disabled verification on the provided vbmeta image.
```

Give it a vbmeta image and then verification will be disabled on it.

This should be equal to `fastboot --disable-verity --disable-verification flash vbmeta vbmeta.img`. The only difference is that it directly patch the image file. Fastboot doesn't provide the ability to generate an image with verification disabled, but sometimes I need it :) .

## Building

It's easy to build it with [Android NDK](https://developer.android.com/ndk).

```
$ export PATH="/path/to/your/ndk:${PATH}"
$ git clone https://github.com/libxzr/vbmeta-disable-verification
......
$ cd vbmeta-disable-verification
$ ndk-build
......
$ tree libs          
libs
├── arm64-v8a
│   └── vbmeta-disable-verification
├── armeabi-v7a
│   └── vbmeta-disable-verification
├── x86
│   └── vbmeta-disable-verification
└── x86_64
    └── vbmeta-disable-verification
```

## References

- [libavb](https://android.googlesource.com/platform/external/avb/+/refs/tags/android-13.0.0_r15/libavb/avb_vbmeta_image.h)
- [fastboot](https://android.googlesource.com/platform/system/core/+/refs/tags/android-13.0.0_r15/fastboot/fastboot.cpp)

## License

[MIT](LICENSE)
