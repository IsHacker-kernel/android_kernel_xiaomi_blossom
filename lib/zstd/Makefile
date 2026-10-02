obj-$(CONFIG_ZSTD_COMPRESS) += zstd_compress.o
obj-$(CONFIG_ZSTD_DECOMPRESS) += zstd_decompress.o

ccflags-y += -O3 -ffast-math -mcpu=cortex-a53 -mtune=cortex-a53 -march=armv8-a -flto -DLZ4_FREESTANDING=1 -DLZ4_FAST_DEC_LOOP=1

zstd_compress-y := fse_compress.o huf_compress.o compress.o \
		   entropy_common.o fse_decompress.o zstd_common.o
zstd_decompress-y := huf_decompress.o decompress.o \
		     entropy_common.o fse_decompress.o zstd_common.o
