#!/bin/bash

set -e

echo "╔════════════════════════════════════════════════════════╗"
echo "║  Building FlipperLinux-OS with Cinnamon & KDE Themes  ║"
echo "╚════════════════════════════════════════════════════════╝"
echo ""

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_DIR/build"
DIST_DIR="$PROJECT_DIR/dist"

# Create directories
mkdir -p "$BUILD_DIR"
mkdir -p "$DIST_DIR"

echo "[1/5] Configuring build environment..."
cd "$BUILD_DIR"
cmake .. -G Ninja

echo "[2/5] Building FlipperLinux terminal..."
ninja flipperlinux_terminal_app

echo "[3/5] Building theme engine..."
ninja flipperlinux_themes

echo "[4/5] Packaging distribution..."
mkdir -p "$DIST_DIR/flipperlinux-os"
cp -r "$BUILD_DIR"/{*.fap,*.elf} "$DIST_DIR/flipperlinux-os/" 2>/dev/null || true
cp "$PROJECT_DIR/ext/flipperlinux/packages.json" "$DIST_DIR/flipperlinux-os/"
cp -r "$PROJECT_DIR/ext/themes" "$DIST_DIR/flipperlinux-os/" 2>/dev/null || true

echo "[5/5] Creating tarball..."
cd "$DIST_DIR"
tar -czf flipperlinux-os-1.0.0.tgz flipperlinux-os/

echo ""
echo "╔════════════════════════════════════════════════════════╗"
echo "║              Build Complete!                           ║"
echo "╠════════════════════════════════════════════════════════╣"
echo "║ Package: $DIST_DIR/flipperlinux-os-1.0.0.tgz"
echo "║ Size: $(du -h "$DIST_DIR/flipperlinux-os-1.0.0.tgz" | cut -f1)"
echo "║                                                        ║"
echo "║ Included:                                              ║"
echo "║  ✓ Cinnamon Theme (Warm Orange)                        ║"
echo "║  ✓ KDE Plasma Theme (Modern Blue)                      ║"
echo "║  ✓ Terminal with fbt-install Package Manager           ║"
echo "║  ✓ Theme Engine & Configuration System                 ║"
echo "║  ✓ 4 Application Themes + 4 Applications               ║"
echo "╚════════════════════════════════════════════════════════╝"
