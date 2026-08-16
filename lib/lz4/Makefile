ccflags-y += -O3 -ffast-math -mcpu=cortex-a53 -mtune=cortex-a53 -mfpu=asimd-vfpv4 -march=armv8-a -flto -DLZ4_FREESTANDING=1 -DLZ4_FAST_DEC_LOOP=1

obj-y += lz4.o
obj-$(CONFIG_CRYPTO_LZ4HC) += lz4hc.o

obj-$(CONFIG_ARM64) += $(addprefix lz4armv8/, lz4accel.o lz4armv8.o)
