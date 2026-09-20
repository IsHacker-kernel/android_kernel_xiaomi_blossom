#!/bin/bash

# These are the exact commands used to build the non-KSU version of the kernel
# To use this script, first move it to ../

export KERNEL_DEFCONFIG="blossom_defconfig"
export KERNEL_ARCH="arm64"
sed -i -e 's/CONFIG_KSU=y/# CONFIG_KSU is not set/g' arch/${KERNEL_ARCH}/configs/${KERNEL_DEFCONFIG}
rm -rf KernelSU
mv drivers/android/dummy_lmk.c drivers/android/lowmemorykiller.c
git clone https://gitlab.com/clangsantoni/zyc_clang clang --depth=1 --branch 21 /tmp/clang
git clone https://android.googlesource.com/platform/prebuilts/clang/host/linux-x86 --depth=1 /tmp/aosp-clang
export PATH="/tmp/aosp-clang/clang-r614150/bin:${PATH}"
clang --version
export ARCH=${KERNEL_ARCH}
export CROSS_COMPILE="/tmp/clang/bin/aarch64-linux-gnu-"
export CC="clang"
export CLANG_TRIPLE="/tmp/clang/bin/aarch64-linux-gnu-"
make O=out CC=clang ARCH=${ARCH} ${KERNEL_DEFCONFIG}
make -j$(nproc) KCFLAGS="-Wno-error=implicit-function-declaration -O3 -march=armv8-a+crc+crypto -mcpu=cortex-a53+crypto+crc+fp+simd -mtune=cortex-a53" O=out ARCH=${ARCH} CC=clang CLANG_TRIPLE=${CLANG_TRIPLE} CROSS_COMPILE=${CROSS_COMPILE} LD=ld.lld NM=llvm-nm AR=llvm-ar OBJCOPY=llvm-objcopy OBJDUMP=llvm-objdump STRIP=llvm-strip
