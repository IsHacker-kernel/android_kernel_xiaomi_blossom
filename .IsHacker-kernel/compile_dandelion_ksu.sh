#!/bin/bash

# These are the exact commands used to build the KSU version of the kernel
# To use this script, first move it to ../

export KERNEL_DEFCONFIG="blossom_defconfig"
git clone https://gitlab.com/clangsantoni/zyc_clang clang --depth=1 --branch 21 /tmp/clang
git clone https://android.googlesource.com/platform/prebuilts/clang/host/linux-x86 --depth=1 /tmp/aosp-clang
export PATH="/tmp/aosp-clang/clang-r614150/bin:${PATH}"
clang --version

chmod u+x clean.sh
bash clean.sh

curl -LSs "https://raw.githubusercontent.com/rsuntk/KernelSU/main/kernel/setup.sh" | bash -

export KERNEL_ARCH="arm64"
export ARCH=${KERNEL_ARCH}
export CROSS_COMPILE="/tmp/clang/bin/aarch64-linux-gnu-"
export CC="clang"
export CLANG_TRIPLE="/tmp/clang/bin/aarch64-linux-gnu-"
make O=out CC=clang ARCH=${ARCH} ${KERNEL_DEFCONFIG}
make -j$(nproc) KCFLAGS="-Wno-error=implicit-function-declaration" O=out ARCH=${ARCH} CC=clang CLANG_TRIPLE=${CLANG_TRIPLE} CROSS_COMPILE=${CROSS_COMPILE} LD=ld.lld NM=llvm-nm AR=llvm-ar
