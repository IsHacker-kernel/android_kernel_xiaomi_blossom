#!/bin/bash

# These are the exact commands used to build the KSU version of the kernel
# To use this script, first move it to ../

export KERNEL_DEFCONFIG="blossom_defconfig"
git clone https://gitlab.com/LeCmnGend/clang --depth=1 --branch clang-19 /tmp/clang
export PATH="/tmp/clang/bin:${PATH}"
clang --version
chmod u+x clean.sh
bash clean.sh
curl -LSs "https://raw.githubusercontent.com/ReSukiSU/ReSukiSU/main/kernel/setup.sh" | bash
export KERNEL_ARCH="arm64"
export ARCH=${KERNEL_ARCH}
export CROSS_COMPILE="aarch64-linux-gnu-"
export CC="clang"
export CLANG_TRIPLE="aarch64-linux-gnu-"
make O=out CC=clang ARCH=${ARCH} ${KERNEL_DEFCONFIG}
make -j$(nproc) KCFLAGS="-O3 -ffast-math -mcpu=cortex-a53 -mtune=cortex-a53 -mfpu=asimd-vfpv4 -march=armv8-a" O=out ARCH=${ARCH} CC=clang CLANG_TRIPLE=${CLANG_TRIPLE} CROSS_COMPILE=${CROSS_COMPILE} LD=ld.lld NM=llvm-nm AR=llvm-ar
