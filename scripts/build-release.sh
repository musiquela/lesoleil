#!/bin/bash

# Soleil - Complete Release Build Script
# Builds, signs, and optionally notarizes Soleil for distribution

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
NC='\033[0m' # No Color

# Configuration
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILDS_DIR="$PROJECT_ROOT/builds/apps"
DIST_DIR="$PROJECT_ROOT/dist"

# Default values
DSP_FILE="Soleil_v1.1.dsp"
VERSION="1.1"
SIGN_CODE=true
NOTARIZE=false
FAUST_BUILDER="faust2caqt"

# Signing configuration (from Phil)
CODESIGN_IDENTITY="3B4C000EFEBC6902467D6DC39BC1F093C9745E65"

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --dsp)
            DSP_FILE="$2"
            shift 2
            ;;
        --version)
            VERSION="$2"
            shift 2
            ;;
        --no-sign)
            SIGN_CODE=false
            shift
            ;;
        --notarize)
            NOTARIZE=true
            shift
            ;;
        --ad-hoc)
            SIGN_CODE=true
            CODESIGN_IDENTITY="-"
            shift
            ;;
        --builder)
            FAUST_BUILDER="$2"
            shift 2
            ;;
        -h|--help)
            echo "Usage: $0 [OPTIONS]"
            echo ""
            echo "Build production-ready Soleil app with code signing and notarization"
            echo ""
            echo "Options:"
            echo "  --dsp FILE        DSP source file (default: Soleil_v1.1.dsp)"
            echo "  --version VER     Version string (default: 1.1)"
            echo "  --builder CMD     Faust builder command (default: faust2caqt)"
            echo "  --no-sign         Skip code signing"
            echo "  --ad-hoc          Use ad-hoc signing for development"
            echo "  --notarize        Submit to Apple for notarization"
            echo "  -h, --help        Show this help message"
            echo ""
            echo "Available Faust builders:"
            echo "  faust2caqt        CoreAudio + Qt (default, recommended)"
            echo "  faust2jaqt        JACK + Qt"
            echo "  faust2au          Audio Unit plugin"
            echo "  faust2vst         VST plugin"
            echo ""
            echo "Examples:"
            echo "  $0                                    # Build with default settings"
            echo "  $0 --notarize                         # Build, sign, and notarize"
            echo "  $0 --ad-hoc                           # Build with ad-hoc signing"
            echo "  $0 --dsp Soleil_v1.0.dsp --version 1.0 # Build specific version"
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

echo -e "${BLUE}╔════════════════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║  Soleil - Production Release Build                ║${NC}"
echo -e "${BLUE}╚════════════════════════════════════════════════════╝${NC}"
echo ""
echo -e "${GREEN}DSP File:${NC} $DSP_FILE"
echo -e "${GREEN}Version:${NC} $VERSION"
echo -e "${GREEN}Builder:${NC} $FAUST_BUILDER"
echo -e "${GREEN}Code Signing:${NC} $([ "$SIGN_CODE" = true ] && echo "✅ Enabled" || echo "❌ Disabled")"
if [ "$SIGN_CODE" = true ]; then
    if [ "$CODESIGN_IDENTITY" = "-" ]; then
        echo -e "${GREEN}Sign Type:${NC} Ad-hoc (development)"
    else
        echo -e "${GREEN}Sign Type:${NC} Developer ID (distribution)"
    fi
fi
echo -e "${GREEN}Notarization:${NC} $([ "$NOTARIZE" = true ] && echo "✅ Enabled" || echo "❌ Disabled")"
echo ""

# Verify DSP file exists
if [ ! -f "$PROJECT_ROOT/$DSP_FILE" ]; then
    echo -e "${RED}❌ Error: DSP file not found: $DSP_FILE${NC}"
    exit 1
fi

# Check if Faust is installed
if ! command -v faust &> /dev/null; then
    echo -e "${RED}❌ Error: Faust is not installed${NC}"
    echo ""
    echo "Please install Faust:"
    echo "  brew install faust"
    exit 1
fi

# Check if the specified builder is available
if ! command -v $FAUST_BUILDER &> /dev/null; then
    echo -e "${RED}❌ Error: $FAUST_BUILDER is not installed${NC}"
    echo ""
    echo "Available Faust tools:"
    command -v faust2caqt &> /dev/null && echo "  ✅ faust2caqt"
    command -v faust2jaqt &> /dev/null && echo "  ✅ faust2jaqt"
    command -v faust2au &> /dev/null && echo "  ✅ faust2au"
    command -v faust2vst &> /dev/null && echo "  ✅ faust2vst"
    exit 1
fi

echo -e "${GREEN}✅ All prerequisites found${NC}"
echo ""

# Create builds directory if it doesn't exist
mkdir -p "$BUILDS_DIR"
mkdir -p "$DIST_DIR"

# Build the app
echo -e "${BLUE}🔨 Building Soleil with $FAUST_BUILDER...${NC}"
echo ""

cd "$PROJECT_ROOT"
START_TIME=$(date +%s)

# Run Faust builder
if $FAUST_BUILDER "$DSP_FILE"; then
    END_TIME=$(date +%s)
    BUILD_TIME=$((END_TIME - START_TIME))
    echo ""
    echo -e "${GREEN}✅ Build complete in ${BUILD_TIME}s${NC}"
else
    echo ""
    echo -e "${RED}❌ Build failed${NC}"
    exit 1
fi

# Determine the app name and move to builds directory
APP_NAME="Soleil_v${VERSION}.app"
if [ -d "Soleil.app" ]; then
    # Move and rename the app
    if [ -d "$BUILDS_DIR/$APP_NAME" ]; then
        echo -e "${YELLOW}⚠️  Removing existing $APP_NAME${NC}"
        rm -rf "$BUILDS_DIR/$APP_NAME"
    fi
    mv "Soleil.app" "$BUILDS_DIR/$APP_NAME"
    APP_PATH="$BUILDS_DIR/$APP_NAME"
elif [ -d "$APP_NAME" ]; then
    # Move to builds directory
    if [ -d "$BUILDS_DIR/$APP_NAME" ]; then
        echo -e "${YELLOW}⚠️  Removing existing $APP_NAME${NC}"
        rm -rf "$BUILDS_DIR/$APP_NAME"
    fi
    mv "$APP_NAME" "$BUILDS_DIR/"
    APP_PATH="$BUILDS_DIR/$APP_NAME"
else
    echo -e "${RED}❌ Error: Built app not found${NC}"
    exit 1
fi

echo -e "${GREEN}App built at:${NC} $APP_PATH"
echo ""

# Code sign the app
if [ "$SIGN_CODE" = true ]; then
    echo -e "${BLUE}🔐 Code signing...${NC}"
    echo ""

    if [ "$CODESIGN_IDENTITY" = "-" ]; then
        # Ad-hoc signing
        "$SCRIPT_DIR/sign-app.sh" --app "$APP_PATH" --ad-hoc
    else
        # Developer ID signing
        if ! security find-identity -v -p codesigning | grep -q "$CODESIGN_IDENTITY"; then
            echo -e "${YELLOW}⚠️  Developer ID not found in keychain${NC}"
            echo ""
            echo "Available signing identities:"
            security find-identity -v -p codesigning
            echo ""
            echo -e "${YELLOW}Installing certificates...${NC}"
            "$SCRIPT_DIR/install-certificates.sh"
            echo ""
        fi

        "$SCRIPT_DIR/sign-app.sh" --app "$APP_PATH" --identity "$CODESIGN_IDENTITY"
    fi

    echo ""
fi

# Notarize the app
if [ "$NOTARIZE" = true ]; then
    if [ "$CODESIGN_IDENTITY" = "-" ]; then
        echo -e "${YELLOW}⚠️  Cannot notarize ad-hoc signed app${NC}"
        echo "Skipping notarization..."
    else
        echo ""
        echo -e "${MAGENTA}🍎 Notarizing with Apple...${NC}"
        echo ""

        "$SCRIPT_DIR/notarize.sh" --app "$APP_PATH" --version "$VERSION"
    fi
fi

# Summary
echo ""
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo -e "${GREEN}🎉 Release build complete!${NC}"
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo ""
echo -e "${GREEN}Built app:${NC}"
echo "  $APP_PATH"
echo ""

if [ "$SIGN_CODE" = true ]; then
    echo -e "${GREEN}Signing status:${NC}"
    if codesign -vvv --deep --strict "$APP_PATH" 2>&1 | grep -q "valid on disk"; then
        echo "  ✅ Signed and valid"

        if [ "$CODESIGN_IDENTITY" = "-" ]; then
            echo "  ⚠️  Ad-hoc signature (development only)"
        else
            echo "  ✅ Developer ID signature (distribution ready)"
        fi
    else
        echo "  ❌ Signature invalid or missing"
    fi
    echo ""
fi

if [ "$NOTARIZE" = true ] && [ "$CODESIGN_IDENTITY" != "-" ]; then
    echo -e "${GREEN}Notarization:${NC}"
    if xcrun stapler validate "$APP_PATH" 2>&1 | grep -q "is already signed"; then
        echo "  ✅ Notarized and stapled"
    else
        echo "  ⚠️  Check notarization script output above"
    fi
    echo ""

    if [ -f "$DIST_DIR/Soleil-v${VERSION}.zip" ]; then
        ZIP_SIZE=$(du -h "$DIST_DIR/Soleil-v${VERSION}.zip" | awk '{print $1}')
        echo -e "${GREEN}Distribution package:${NC}"
        echo "  $DIST_DIR/Soleil-v${VERSION}.zip ($ZIP_SIZE)"
        echo ""
    fi
fi

echo -e "${GREEN}Next steps:${NC}"
if [ "$SIGN_CODE" = false ]; then
    echo "  • Sign the app: ./scripts/sign-app.sh"
fi
if [ "$NOTARIZE" = false ] && [ "$CODESIGN_IDENTITY" != "-" ]; then
    echo "  • Notarize: ./scripts/notarize.sh"
fi
echo "  • Test the app: open '$APP_PATH'"
echo "  • Distribute to users"
echo ""
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
