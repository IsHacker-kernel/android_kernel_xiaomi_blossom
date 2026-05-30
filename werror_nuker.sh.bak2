#!/bin/bash
# NUKE ALL  AND * flags from ALL Makefiles recursively

echo "Nuking all  and  flags..."

# Find ALL Makefiles (including tools/, arch/, scripts/, etc.)
files=$(find . -type f \( -name "Makefile" -o -name "Makefile.*" \) 2>/dev/null)

modified=0

for f in $files; do
    if grep -qE -- '|' "$f" 2>/dev/null; then
        # Backup original (only once)
        [ ! -f "$f.bak" ] && cp "$f" "$f.bak"
        
        # NUKE all  variants
        sed -i 's///g' "$f"
        sed -i 's/-implicit-function-declaration//g' "$f"
        sed -i 's/-implicit//g' "$f"
        
        # NUKE all  variants (turn warnings back into warnings)
        sed -i 's///g' "$f"
        sed -i 's///g' "$f"
        sed -i 's///g' "$f"
        
        echo "[NUKED] $f"
        ((modified++))
    fi
done

# Also check Kconfig files for Werror options
kconfig_files=$(find . -type f \( -name "Kconfig" -o -name "Kconfig.*" \) 2>/dev/null)

for f in $kconfig_files; do
    if grep -qE -- 'Werror|Wimplicit' "$f" 2>/dev/null; then
        [ ! -f "$f.bak" ] && cp "$f" "$f.bak"
        sed -i 's///g' "$f"
        sed -i 's///g' "$f"
        sed -i 's///g' "$f"
        sed -i 's///g' "$f"
        echo "[NUKED KCONFIG] $f"
        ((modified++))
    fi
done

# Also nuke CONFIG_CC_WERROR in .config files
config_files=$(find . -name ".config" -o -name "defconfig" -o -name "*_defconfig" 2>/dev/null)

for f in $config_files; do
    if grep -q "CONFIG_CC_WERROR=y" "$f" 2>/dev/null; then
        sed -i 's/CONFIG_CC_WERROR=y/CONFIG_CC_WERROR=n/g' "$f"
        echo "[FIXED CONFIG] $f"
        ((modified++))
    fi
done

# Also check for Werror in shell scripts that might set CFLAGS
sh_files=$(find . -maxdepth 2 -name "*.sh" 2>/dev/null)

for f in $sh_files; do
    if grep -qE -- '|' "$f" 2>/dev/null; then
        [ ! -f "$f.bak" ] && cp "$f" "$f.bak"
        sed -i 's///g' "$f"
        sed -i 's///g' "$f"
        sed -i 's///g' "$f"
        sed -i 's///g' "$f"
        echo "[NUKED SH] $f"
        ((modified++))
    fi
done

echo ""
echo "Done! Nuked $modified files."
echo "Backups saved as .bak files."
echo ""
echo "Now rebuild your kernel - warnings will be warnings!"
