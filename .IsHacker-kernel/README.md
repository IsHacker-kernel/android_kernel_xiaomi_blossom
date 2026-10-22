<center>
<img src="branding.png">
<pre> *
 * Your warranty is now void.
 *
 * I am not responsible for bricked devices, dead SD cards,
 * thermonuclear war, or you getting fired because the alarm app failed. Please
 * do some research if you have any concerns about features included in this kernel
 * before flashing it! YOU are choosing to make these modifications, and if
 * you point the finger at me for messing up your device, I will laugh at you.
 *
</pre>
<b>IsHacker kernel</b> is a custom Linux kernel designed specifically for low-end and/or old Android devices to improve their usability, performance and, in some cases, even battery life.
</center>

# General features (with explanation)
These features are common accross all supported devices.

**1. No Slop and full source disclosure:** All code and modifications in the kernel, including this README, is written by a human. No LLMs are used for any kind of assistance for programming, code verification or writting text (like this one). Further, all kernels released under this project will have their source disclosed in a git repo (as required by the GPL) **along with the shell script containing the exact commands used to build the kernel**. The shell scripts are in the **.IsHacker-kernel/** directory inside the kernel source.

**2. Overclocking:** The kernels will come with CPU, GPU or, if possible, RAM OC to improve performance. The TX power of the WiFi chip/cellular modem may also be increased for better signal reception. Thus, it is recommended to use phone coolers/custom cooling equipment with these kernels to avoid hardware damage due to overheating.

**3. No Low Memory Killer/LMKD:** Android's Low Memory Killer (userspace lmkd or in-kernel driver) will be removed or disabled. This saves battery by reducing CPU overhead of scanning the memory and killing processes, and by preventing the "kill and reload from flash" situation for cached apps. Also, no automatic killing of background/minimized apps means improved multitasking and productivity, just like how minimized programs don't just automatically get closed due to "low memory" on any Desktop operating systems. **The default Linux OOM killer remains enabled.**

**4. Better memory management:** Featured like Multi-generational LRU (MGLRU), Parallelized kcompressd, etc will be included to improve memory management and increase responsiveness under low memory conditions.

**5. No thermal/power throttling:** Absurd thermal/power throttling "features" (like the one on Mediatek devices) will be removed to let the device utilize its full potential. Again, external cooling is recommended (but NOT enforced, unlike thermal throttling ;) It's your choice) to prevent hardware damage due to overheating.

**6. Compiler optimizations:** The kernels are compiled using clang (rather than GCC) and often include Link-time Optimization (LTO) and CPU/arch-specific optimizations. -O3 and -ffast-math flags are also applied wherever necessary. Most debugging flags and kernel configs are also disabled to reduce runtime overhead.

**7. Additional features:** WireGuard, Kali NetHunter modules, KVM, backports from mainline kernels and other additional features may also be included in the kernels.

**8. Official KSU only:** Wherever KernelSU is integrated as the in-kernel root solution, only the official KernelSU or a backport of it (such as the [fork by backslashxx](https://github.com/backslashxx/KernelSU)) will be used, and not derivatives like KSU-Next or (Re)SukiSu. This is because the official version is the most lightweight and the most stable one, due to unavailability of "root hiding" features.

**But I want to hide root to use "banking" apps!!!**

Please listen to this carefully. Root access is an essential part of every OS, and it is not at all wrong to have it. In fact, any OS is incomplete without superuser rights. If an app refuses to work becuase tour phone has root access, the developer has some serious issues and it is morally wrong to use such apps. If your banking app detects root, you can use net-banking in the browser. And no, root does not "compromise your device's security and privacy", rather in most cases, it actually improves them, significantly. Please do **NOT** fall for such propaganda!

# Device-specific features
1. Compiled on my own PC running Linux Mint 22.3, and not on Github Actions or Docker
2. Compiled with full LTO, Polly, -O3, -ffast-math and CPU-specific optimization flags
3. Added WireGuard
4. Upstreamed kernel to 4.19.325
5. CPU Overclock: +200 MHz BIG (Stock: 2001 MHz), +200 MHz LITTLE (Stock: 1500 MHz), +200 MHz CCI (Ring/Cache frequency) (Stock: 1048 MHz)
6. GPU Overclock: +30 MHz (Stock 650 MHz)
7. Added MGLRU, kshrinkd and parallelized (multi-threaded) kcompressd
8. Removed a lot of debugging code and improved memory management by cherry-picking danya2271's commits from Kuroneko
9. Removed bcct chrlmt charging speed throttling
10. Removed Mediatek's absurd thermal throttling feature (i.e mtk_atm_cooler) and removed krtatm
11. Disabled EEM, PPM, PBM, FPSGO, and power throttling
12. Faster camera opening
13. Fixed many vulnerabilities and bugs
14. Default CPU governor is performance
15. Completely disabled Android LMKD/Low Memory Killer through in-kernel dummy driver (Linux's default OOM killer remains enabled)
16. Prevents "libperfmgr" (e.g in CrDroid) from tampering with CPU frequency and scheduling settings by adding dummy kobjects
17. Manual KSU integration without Kprobes or Kallsyms (for KSU version)
18. Improved ZRAM speed through updated LZ4 driver
19. Enabled Swap VMA readahead by default
20. Disabled Panic on OOPS
21. Better USB tethering speed
22. Disabled WiFi Gen4M dynamic TX power switching (TX power is now locked at NAX)
23. Increased MD1 TX power to 5500 mW (Stock: 4000 mW)
24. Disabled unnecessary sound drivers
25. Disabled charger2, bcct, btsmdpa and wmt thermal sensors
26. RCU improvements
27. Added around 10MB extra RAM by removing debugging/unnecessary memory reservations from DTS
28. Added SRANDOM driver for faster /dev/urandom and /dev/random reading
29. Improved GPU performance by optimizing the code (other than the OC)
30. Video Encoder/Decoder improvements - you can play 1080p 60FPS VP9 videos on m.youtube.com without too much buffering

# Download
1. KSU version: https://github.com/IsHacker-kernel/android_kernel_xiaomi_blossom/releases/download/v1.0/IsHacker-kernel-v1.0-blossom-KSU.zip (Manager APK: https://github.com/backslashxx/KernelSU/releases/download/v3.3.1%2B22/KernelSU_v3.3.1+22_32702-release.apk)
2. Non-KSU version: https://github.com/IsHacker-kernel/android_kernel_xiaomi_blossom/releases/download/v1.0/IsHacker-kernel-v1.0-blossom-VANILLA.zip

# Kernel source
[android_kernel_xiaomi_blossom](https://github.com/IsHacker-kernel/android_kernel_xiaomi_blossom)

# Bugs
Everything else work as intended except for the listed bugs.

1. Deep sleep does not work properly, which causes very high idle battery drain (around 40% overnight)

# Credits
## Base kernel
https://github.com/Iam-nishan/Jujutsu-kernel
## Commits (cherry-picked from these repos)
1. https://github.com/quangwang123/QKernel
2. https://github.com/danya2271/kuroneko_r_mt6765
3. https://github.com/danya2271/mt6765_kuroneko_x
4. https://github.com/shinichi-c/Dynamic_kernel_4.19_oneplus_sdm845
5. https://github.com/physwizz/A042-U-u6-u8
6. https://github.com/KarlosComK/CKernel
7. https://github.com/plmzaq2112/android_kernel_mt6765
