#!/bin/bash

# These are the exact commands used to build the non-KSU version of the kernel
# To use this script, first move it to ../

export KERNEL_DEFCONFIG="blossom_defconfig"
export KERNEL_ARCH="arm64"
sed -i -e 's/CONFIG_KSU=y/CONFIG_KSU=n/g' arch/${KERNEL_ARCH}/configs/${KERNEL_DEFCONFIG}
sed -i -e 's/CCONFIG_KSU_MANUAL_HOOK=y/CONFIG_KSU_MANUAL_HOOK=n/g' arch/${KERNEL_ARCH}/configs/${KERNEL_DEFCONFIG}
git clone https://gitlab.com/LeCmnGend/clang --depth=1 --branch clang-19 /tmp/clang
export PATH="/tmp/clang/bin:${PATH}"
clang --version
export ARCH=${KERNEL_ARCH}
export CROSS_COMPILE="aarch64-linux-gnu-"
export CC="clang"
export CLANG_TRIPLE="aarch64-linux-gnu-"
make O=out CC=clang ARCH=${ARCH} ${KERNEL_DEFCONFIG}
make -j5 KCFLAGS="-O3 -ffast-math -mcpu=cortex-a53 -mtune=cortex-a53 -mfpu=asimd-vfpv4 -march=armv8-a" O=out ARCH=${ARCH} CC=clang CLANG_TRIPLE=${CLANG_TRIPLE} CROSS_COMPILE=${CROSS_COMPILE} LD=ld.lld NM=llvm-nm AR=llvm-ar
