#!/bin/bash

# These are the exact commands used to build the KSU version of the kernel
# To use this script, first move it to ../

export KERNEL_DEFCONFIG="blossom_defconfig"
git clone https://gitlab.com/clangsantoni/zyc_clang clang --depth=1 --branch 21 /tmp/clang
export PATH="/tmp/clang/bin:${PATH}"
clang --version
chmod u+x clean.sh
bash clean.sh
curl -LSs "https://raw.githubusercontent.com/tiann/KernelSU/main/kernel/setup.sh" | bash -

# Don't force CONFIG_KPROBES since we already have manual hooks
sed -i -e 's/depends on KPROBES && EXT4_FS/depends on EXT4_FS/g' drivers/kernelsu/Kconfig
sed -i -z -e 's/\n    Requires CONFIG_KPROBES for kernel hooking support.//g' drivers/kernelsu/Kconfig

export KERNEL_ARCH="arm64"
export ARCH=${KERNEL_ARCH}
export CROSS_COMPILE="aarch64-linux-gnu-"
export CC="clang"
export CLANG_TRIPLE="aarch64-linux-gnu-"
make O=out CC=clang ARCH=${ARCH} ${KERNEL_DEFCONFIG}
make -j$(nproc) KCFLAGS="-O3 -ffast-math -mcpu=cortex-a53 -mtune=cortex-a53 -march=armv8-a" O=out ARCH=${ARCH} CC=clang CLANG_TRIPLE=${CLANG_TRIPLE} CROSS_COMPILE=${CROSS_COMPILE} LD=ld.lld NM=llvm-nm AR=llvm-ar
