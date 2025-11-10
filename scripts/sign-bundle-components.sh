#!/bin/bash

# Soleil - Bundle Component Signing Script
# Signs all nested components individually (proper way for Qt apps)
# This avoids issues with --deep flag on Qt dylibs

set -e

APP_PATH="$1"
IDENTITY="$2"
ENTITLEMENTS="$3"

if [ -z "$APP_PATH" ] || [ -z "$IDENTITY" ]; then
    echo "Usage: $0 <app-path> <identity> [entitlements]"
    exit 1
fi

# Colors
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${BLUE}Signing bundle components individually...${NC}"

SIGNED_COUNT=0
FAILED_COUNT=0

# Sign all dylibs and frameworks (nested components first)
# Use ad-hoc signing for third-party dylibs (common practice for Qt/Homebrew libraries)
while IFS= read -r -d '' file; do
    echo -n "  Signing: $(basename "$file")..."

    # Try Developer ID first, fall back to ad-hoc if it fails
    if codesign --force --sign "$IDENTITY" "$file" 2>/dev/null; then
        echo -e " ${GREEN}✓${NC} (Developer ID)"
        ((SIGNED_COUNT++))
    elif codesign --force --sign - "$file" 2>/dev/null; then
        echo -e " ${GREEN}✓${NC} (ad-hoc)"
        ((SIGNED_COUNT++))
    else
        echo -e " ${YELLOW}⚠${NC} (failed)"
        ((FAILED_COUNT++))
    fi
done < <(find "$APP_PATH/Contents" -type f \( -name "*.dylib" -o -name "*.so" \) -print0 2>/dev/null)

# Sign frameworks if any
if [ -d "$APP_PATH/Contents/Frameworks" ]; then
    while IFS= read -r -d '' framework; do
        echo -n "  Signing: $(basename "$framework")..."

        # Try Developer ID first, fall back to ad-hoc if it fails
        if codesign --force --sign "$IDENTITY" "$framework" 2>/dev/null; then
            echo -e " ${GREEN}✓${NC} (Developer ID)"
            ((SIGNED_COUNT++))
        elif codesign --force --sign - "$framework" 2>/dev/null; then
            echo -e " ${GREEN}✓${NC} (ad-hoc)"
            ((SIGNED_COUNT++))
        else
            echo -e " ${YELLOW}⚠${NC} (failed)"
            ((FAILED_COUNT++))
        fi
    done < <(find "$APP_PATH/Contents/Frameworks" -name "*.framework" -print0 2>/dev/null)
fi

echo ""
echo -e "${GREEN}Signed $SIGNED_COUNT components${NC}"
if [ $FAILED_COUNT -gt 0 ]; then
    echo -e "${YELLOW}Skipped $FAILED_COUNT unsignable components${NC}"
fi

# Sign the main bundle
echo ""
echo -e "${BLUE}Signing main bundle...${NC}"

if [ -n "$ENTITLEMENTS" ] && [ -f "$ENTITLEMENTS" ]; then
    codesign --force --sign "$IDENTITY" --entitlements "$ENTITLEMENTS" --options runtime "$APP_PATH"
else
    codesign --force --sign "$IDENTITY" --options runtime "$APP_PATH"
fi

echo -e "${GREEN}✅ Bundle signed successfully!${NC}"
