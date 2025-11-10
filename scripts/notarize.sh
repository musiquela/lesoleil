#!/bin/bash

# Soleil - Notarization Script
# Submits Soleil.app to Apple for notarization

set -e

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
DIST_DIR="$PROJECT_DIR/dist"

# Your Apple Developer credentials (from Phil)
APPLE_ID="keegandewitt@gmail.com"
TEAM_ID="G398H44H6X"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
NC='\033[0m' # No Color

echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo -e "${MAGENTA}🍎 Soleil - Apple Notarization Script${NC}"
echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo ""
echo "This script will:"
echo "1. Create a distribution ZIP file"
echo "2. Submit to Apple for notarization"
echo "3. Wait for notarization to complete"
echo "4. Staple the notarization ticket to the app"
echo ""

# Parse command line arguments
APP_PATH=""
VERSION="1.1"
KEYCHAIN_PROFILE=""

while [[ $# -gt 0 ]]; do
    case $1 in
        --app)
            APP_PATH="$2"
            shift 2
            ;;
        --version)
            VERSION="$2"
            shift 2
            ;;
        --profile)
            KEYCHAIN_PROFILE="$2"
            shift 2
            ;;
        -h|--help)
            echo "Usage: $0 [OPTIONS]"
            echo ""
            echo "Submit Soleil.app to Apple for notarization"
            echo ""
            echo "Options:"
            echo "  --app PATH        Path to .app bundle (default: builds/apps/Soleil_v1.1.app)"
            echo "  --version VER     Version string for ZIP filename (default: 1.1)"
            echo "  --profile NAME    Keychain profile name (default: none, uses env var)"
            echo "  -h, --help        Show this help message"
            echo ""
            echo "Setup:"
            echo "  Option 1 - Environment Variable (Quick):"
            echo "    export NOTARIZATION_PASSWORD='your-app-specific-password'"
            echo ""
            echo "  Option 2 - Keychain Profile (Recommended):"
            echo "    xcrun notarytool store-credentials Soleil-Notarization \\"
            echo "        --apple-id $APPLE_ID \\"
            echo "        --team-id $TEAM_ID \\"
            echo "        --password <app-specific-password>"
            echo ""
            echo "    Then use: $0 --profile Soleil-Notarization"
            echo ""
            echo "Get app-specific password at:"
            echo "  https://appleid.apple.com/account/manage"
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
        VERSION="1.0"
    else
        echo -e "${RED}❌ Error: Cannot find Soleil.app${NC}"
        echo ""
        echo "Please specify the app path with --app or build and sign it first:"
        echo "  faust2caqt Soleil_v1.1.dsp"
        echo "  ./scripts/sign-app.sh"
        exit 1
    fi
fi

# Verify app exists and is signed
if [ ! -d "$APP_PATH" ]; then
    echo -e "${RED}❌ Error: App not found at: $APP_PATH${NC}"
    exit 1
fi

echo -e "${GREEN}App to notarize:${NC} $APP_PATH"
echo ""

# Check if app is signed
echo -e "${BLUE}🔍 Checking code signature...${NC}"
if ! codesign -vvv --deep --strict "$APP_PATH" 2>&1 | grep -q "valid on disk"; then
    echo -e "${RED}❌ Error: App is not properly signed!${NC}"
    echo ""
    echo "Please sign the app first:"
    echo "  ./scripts/sign-app.sh"
    exit 1
fi

echo -e "${GREEN}✅ App is properly signed${NC}"
echo ""

# Check for app-specific password or keychain profile
if [ -z "$KEYCHAIN_PROFILE" ] && [ -z "$NOTARIZATION_PASSWORD" ]; then
    echo -e "${RED}❌ Error: No notarization credentials configured!${NC}"
    echo ""
    echo -e "${YELLOW}Please choose one of these options:${NC}"
    echo ""
    echo "Option 1 - Environment Variable (Quick):"
    echo "  export NOTARIZATION_PASSWORD='your-app-specific-password'"
    echo ""
    echo "Option 2 - Keychain Profile (Recommended):"
    echo "  xcrun notarytool store-credentials Soleil-Notarization \\"
    echo "      --apple-id $APPLE_ID \\"
    echo "      --team-id $TEAM_ID \\"
    echo "      --password <app-specific-password>"
    echo ""
    echo "  Then run: $0 --profile Soleil-Notarization"
    echo ""
    echo "Get app-specific password at:"
    echo "  https://appleid.apple.com/account/manage"
    echo ""
    exit 1
fi

# Create distribution directory
mkdir -p "$DIST_DIR"

echo -e "${BLUE}📦 Creating distribution package...${NC}"
echo ""

# Package the app as ZIP
ZIP_NAME="Soleil-v${VERSION}.zip"
ZIP_PATH="$DIST_DIR/$ZIP_NAME"

echo "   Creating: $ZIP_NAME"
cd "$(dirname "$APP_PATH")"
ditto -c -k --keepParent "$(basename "$APP_PATH")" "$ZIP_PATH"
echo -e "${GREEN}   ✅ Package created${NC}"

# Get file size
ZIP_SIZE=$(du -h "$ZIP_PATH" | awk '{print $1}')
echo "   Size: $ZIP_SIZE"

echo ""
echo -e "${MAGENTA}📤 Submitting to Apple for notarization...${NC}"
echo ""
echo -e "${YELLOW}⏳ This may take several minutes (typically 2-10 minutes)${NC}"
echo ""

# Submit for notarization
if [ -n "$KEYCHAIN_PROFILE" ]; then
    # Use keychain profile
    echo -e "${BLUE}Using keychain profile: $KEYCHAIN_PROFILE${NC}"
    echo ""

    xcrun notarytool submit "$ZIP_PATH" \
        --keychain-profile "$KEYCHAIN_PROFILE" \
        --wait

    NOTARIZE_STATUS=$?
else
    # Use password directly
    echo -e "${BLUE}Using Apple ID: $APPLE_ID${NC}"
    echo ""

    xcrun notarytool submit "$ZIP_PATH" \
        --apple-id "$APPLE_ID" \
        --team-id "$TEAM_ID" \
        --password "$NOTARIZATION_PASSWORD" \
        --wait

    NOTARIZE_STATUS=$?
fi

echo ""

if [ $NOTARIZE_STATUS -eq 0 ]; then
    echo -e "${GREEN}✅ Notarization successful!${NC}"
    echo ""

    # Staple the notarization ticket
    echo -e "${BLUE}📎 Stapling notarization ticket to app...${NC}"

    if xcrun stapler staple "$APP_PATH"; then
        echo -e "${GREEN}✅ Notarization ticket stapled!${NC}"
        echo ""

        # Verify stapling
        if xcrun stapler validate "$APP_PATH" 2>&1 | grep -q "is already signed"; then
            echo -e "${GREEN}✅ Stapler validation passed${NC}"
        else
            echo -e "${YELLOW}⚠️  Stapler validation returned unexpected result${NC}"
        fi
    else
        echo -e "${RED}❌ Failed to staple notarization ticket${NC}"
        echo ""
        echo "The app is notarized, but the ticket couldn't be stapled."
        echo "Users will still be able to run the app if they're connected to the internet."
    fi

    echo ""
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${GREEN}🎉 Notarization complete!${NC}"
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo ""
    echo -e "${GREEN}Notarized app:${NC}"
    echo "  $APP_PATH"
    echo ""
    echo -e "${GREEN}Distribution package:${NC}"
    echo "  $ZIP_PATH ($ZIP_SIZE)"
    echo ""
    echo -e "${GREEN}Next steps:${NC}"
    echo "  • Test the app on a different Mac"
    echo "  • Distribute the ZIP file to users"
    echo "  • Or create an installer with ./scripts/package.sh (if available)"
    echo ""
else
    echo -e "${RED}❌ Notarization failed!${NC}"
    echo ""
    echo "To see the detailed error log, run:"
    echo ""

    if [ -n "$KEYCHAIN_PROFILE" ]; then
        echo "  xcrun notarytool log --keychain-profile $KEYCHAIN_PROFILE <SUBMISSION_ID>"
    else
        echo "  xcrun notarytool log --apple-id $APPLE_ID --team-id $TEAM_ID --password \$NOTARIZATION_PASSWORD <SUBMISSION_ID>"
    fi

    echo ""
    echo "To get recent submissions:"
    echo ""

    if [ -n "$KEYCHAIN_PROFILE" ]; then
        echo "  xcrun notarytool history --keychain-profile $KEYCHAIN_PROFILE"
    else
        echo "  xcrun notarytool history --apple-id $APPLE_ID --team-id $TEAM_ID --password \$NOTARIZATION_PASSWORD"
    fi

    exit 1
fi
