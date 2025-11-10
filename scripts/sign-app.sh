#!/bin/bash

# Soleil - Code Signing Script
# Signs the Soleil.app with Developer ID for distribution

set -e

# Configuration
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
ENTITLEMENTS_FILE="$PROJECT_DIR/Soleil.entitlements"

# Default signing identity (from Phil)
CODESIGN_IDENTITY="3B4C000EFEBC6902467D6DC39BC1F093C9745E65"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}🔐 Soleil - Code Signing Script${NC}"
echo ""

# Parse command line arguments
APP_PATH=""
AD_HOC=false

while [[ $# -gt 0 ]]; do
    case $1 in
        --app)
            APP_PATH="$2"
            shift 2
            ;;
        --identity)
            CODESIGN_IDENTITY="$2"
            shift 2
            ;;
        --ad-hoc)
            AD_HOC=true
            shift
            ;;
        -h|--help)
            echo "Usage: $0 [OPTIONS]"
            echo ""
            echo "Sign Soleil.app with Developer ID for distribution"
            echo ""
            echo "Options:"
            echo "  --app PATH        Path to .app bundle (default: builds/apps/Soleil_v1.1.app)"
            echo "  --identity ID     Code signing identity (default: from Phil)"
            echo "  --ad-hoc          Use ad-hoc signing for development (no Developer ID)"
            echo "  -h, --help        Show this help message"
            echo ""
            echo "Examples:"
            echo "  $0                                    # Sign default app with Developer ID"
            echo "  $0 --app Soleil_v1.0.app              # Sign specific app"
            echo "  $0 --ad-hoc                           # Ad-hoc signing for testing"
            echo ""
            exit 0
            ;;
        *)
            echo -e "${RED}Unknown option: $1${NC}"
            echo "Use -h or --help for usage information"
            exit 1
            ;;
    esac
done

# Determine app path
if [ -z "$APP_PATH" ]; then
    # Try to find the latest Soleil app
    if [ -d "$PROJECT_DIR/builds/apps/Soleil_v1.1.app" ]; then
        APP_PATH="$PROJECT_DIR/builds/apps/Soleil_v1.1.app"
    elif [ -d "$PROJECT_DIR/Soleil_v1.1.app" ]; then
        APP_PATH="$PROJECT_DIR/Soleil_v1.1.app"
    elif [ -d "$PROJECT_DIR/builds/apps/Soleil_v1.0.app" ]; then
        APP_PATH="$PROJECT_DIR/builds/apps/Soleil_v1.0.app"
    else
        echo -e "${RED}❌ Error: Cannot find Soleil.app${NC}"
        echo ""
        echo "Please specify the app path with --app or build it first:"
        echo "  faust2caqt Soleil_v1.1.dsp"
        exit 1
    fi
fi

# Verify app exists
if [ ! -d "$APP_PATH" ]; then
    echo -e "${RED}❌ Error: App not found at: $APP_PATH${NC}"
    exit 1
fi

echo -e "${GREEN}App to sign:${NC} $APP_PATH"
echo ""

# Check entitlements file
if [ ! -f "$ENTITLEMENTS_FILE" ]; then
    echo -e "${RED}❌ Error: Entitlements file not found: $ENTITLEMENTS_FILE${NC}"
    exit 1
fi

echo -e "${GREEN}Entitlements:${NC} $ENTITLEMENTS_FILE"
echo ""

# Prepare Qt app (remove problematic plugins that cause signing errors)
if [ "$AD_HOC" = false ]; then
    echo -e "${BLUE}🔧 Preparing Qt app for Developer ID signing...${NC}"
    "$PROJECT_DIR/scripts/prepare-qt-app.sh" "$APP_PATH"
    echo ""
fi

if [ "$AD_HOC" = true ]; then
    # Ad-hoc signing (for development/testing)
    echo -e "${YELLOW}🔓 Using ad-hoc signing (development only)${NC}"
    echo ""

    codesign --force --sign - --deep "$APP_PATH"

    echo ""
    echo -e "${GREEN}✅ Ad-hoc signing complete${NC}"
    echo ""
    echo -e "${YELLOW}⚠️  Note: Ad-hoc signed apps will show 'unidentified developer' warning${NC}"
    echo -e "${YELLOW}   For distribution, use Developer ID signing (remove --ad-hoc flag)${NC}"
else
    # Developer ID signing (for distribution)
    echo -e "${BLUE}🔐 Signing with Developer ID...${NC}"
    echo -e "${GREEN}Identity:${NC} $CODESIGN_IDENTITY"
    echo ""

    # Check if identity exists
    if ! security find-identity -v -p codesigning | grep -q "$CODESIGN_IDENTITY"; then
        echo -e "${RED}❌ Error: Signing identity not found in keychain${NC}"
        echo ""
        echo "Available signing identities:"
        security find-identity -v -p codesigning
        echo ""
        echo "Please run: ./scripts/install-certificates.sh"
        exit 1
    fi

    # Sign components individually (avoids Qt dylib issues)
    "$PROJECT_DIR/scripts/sign-bundle-components.sh" \
        "$APP_PATH" \
        "$CODESIGN_IDENTITY" \
        "$ENTITLEMENTS_FILE"

    echo ""
    echo -e "${BLUE}🔍 Verifying signature...${NC}"

    if codesign -vvv --strict "$APP_PATH" 2>&1 | grep -q "valid on disk"; then
        echo -e "${GREEN}✅ Signature valid${NC}"
    else
        echo -e "${RED}❌ Signature invalid${NC}"
        codesign -vvv --strict "$APP_PATH"
        exit 1
    fi

    echo ""
    echo -e "${GREEN}✅ Code signing complete!${NC}"
    echo ""
    echo -e "${BLUE}Signature details:${NC}"
    codesign -d -vvv "$APP_PATH" 2>&1 | grep -E "(Authority|TeamIdentifier|Identifier|Signed Time)"
fi

echo ""
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo -e "${GREEN}Next steps:${NC}"
echo "1. Test the signed app: open '$APP_PATH'"
echo "2. Notarize for distribution: ./scripts/notarize.sh"
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
