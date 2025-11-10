#!/bin/bash

# Soleil - Qt App Preparation Script
# Fixes known Qt plugin signing issues by removing problematic image format plugins
# These plugins cause errSecInternalComponent errors with Developer ID signing

set -e

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

APP_PATH="$1"

if [ -z "$APP_PATH" ]; then
    echo -e "${RED}Usage: $0 <path-to-app>${NC}"
    exit 1
fi

if [ ! -d "$APP_PATH" ]; then
    echo -e "${RED}Error: App not found at: $APP_PATH${NC}"
    exit 1
fi

echo -e "${BLUE}🔧 Preparing Qt app for code signing...${NC}"
echo -e "${GREEN}App:${NC} $APP_PATH"
echo ""

# Known problematic Qt plugins that cause errSecInternalComponent
PROBLEMATIC_PLUGINS=(
    "imageformats/libqico.dylib"
    "imageformats/libqmacheif.dylib"
    "imageformats/libqmacjp2.dylib"
)

PLUGINS_DIR="$APP_PATH/Contents/PlugIns"
REMOVED_COUNT=0

if [ ! -d "$PLUGINS_DIR" ]; then
    echo -e "${YELLOW}⚠️  No PlugIns directory found${NC}"
    exit 0
fi

echo -e "${BLUE}Checking for problematic Qt plugins...${NC}"

for plugin in "${PROBLEMATIC_PLUGINS[@]}"; do
    PLUGIN_PATH="$PLUGINS_DIR/$plugin"
    if [ -f "$PLUGIN_PATH" ]; then
        echo -e "  ${YELLOW}Removing:${NC} $(basename "$PLUGIN_PATH")"
        rm "$PLUGIN_PATH"
        ((REMOVED_COUNT++))
    fi
done

if [ $REMOVED_COUNT -gt 0 ]; then
    echo ""
    echo -e "${GREEN}✅ Removed $REMOVED_COUNT problematic plugin(s)${NC}"
    echo -e "${BLUE}Note:${NC} These are non-essential image format plugins (ICO, HEIF)"
    echo -e "${BLUE}     Your audio app will work perfectly without them${NC}"
else
    echo -e "${GREEN}✅ No problematic plugins found${NC}"
fi

echo ""
echo -e "${BLUE}Removing all existing signatures from bundle...${NC}"
# Remove all signatures from the bundle to start fresh
# This fixes "unable to build chain" errors from corrupted ad-hoc signatures
find "$APP_PATH" -type f \( -name "*.dylib" -o -name "*.so" -o -name "*.framework" \) -exec codesign --remove-signature {} \; 2>/dev/null || true

# Also remove signature from main executable
if [ -f "$APP_PATH/Contents/MacOS"/* ]; then
    codesign --remove-signature "$APP_PATH" 2>/dev/null || true
fi

echo -e "${GREEN}✅ App is ready for code signing!${NC}"
