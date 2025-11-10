#!/bin/bash

# Soleil - Certificate Installation Script
# This script installs the Developer ID certificates needed for distribution signing

set -e

CERT_DIR="$HOME/Dropbox/_Musique/_Dev/Certificates"
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

echo "🔐 Installing Developer ID Certificates for Soleil..."
echo ""

# Check if certificate directory exists
if [ ! -d "$CERT_DIR" ]; then
    echo "❌ Certificate directory not found at: $CERT_DIR"
    echo ""
    echo "Checking project directory for certificates..."

    # Check if certificates are in project root
    if ls "$PROJECT_DIR"/*.cer 1> /dev/null 2>&1 || ls "$PROJECT_DIR"/*.p12 1> /dev/null 2>&1; then
        CERT_DIR="$PROJECT_DIR"
        echo "✅ Found certificates in project directory: $CERT_DIR"
    else
        echo "❌ No certificates found in project directory either"
        echo ""
        echo "Please:"
        echo "1. Download your Developer ID certificates from Apple Developer"
        echo "2. Place .cer and .p12 files in: $CERT_DIR"
        echo "   OR place them in the project root directory"
        exit 1
    fi
fi

echo "📁 Certificate directory: $CERT_DIR"
echo ""

# Install Developer ID Application certificate (.cer)
if ls "$CERT_DIR"/*.cer 1> /dev/null 2>&1; then
    echo "📜 Installing Developer ID Application certificate(s)..."
    for cert in "$CERT_DIR"/*.cer; do
        echo "   Installing: $(basename "$cert")"
        security import "$cert" -k ~/Library/Keychains/login.keychain-db -T /usr/bin/codesign
    done
    echo "✅ Certificate(s) installed"
else
    echo "⚠️  No .cer files found in certificate directory"
fi

echo ""

# Install private key (.p12) - will prompt for password
if ls "$CERT_DIR"/*.p12 1> /dev/null 2>&1; then
    echo "🔑 Installing private key..."
    for p12 in "$CERT_DIR"/*.p12; do
        echo "   Installing: $(basename "$p12")"
        echo "   (You will be prompted for the certificate password)"
        security import "$p12" -k ~/Library/Keychains/login.keychain-db -T /usr/bin/codesign
    done
    echo "✅ Private key installed"
else
    echo "⚠️  No .p12 files found in certificate directory"
fi

echo ""
echo "🔍 Verifying installed certificates..."
if security find-identity -v -p codesigning | grep "Developer ID"; then
    echo ""
    echo "✅ Certificate installation complete!"
    echo ""
    echo "Found Developer ID certificate(s):"
    security find-identity -v -p codesigning | grep "Developer ID"
else
    echo ""
    echo "⚠️  No Developer ID certificates found!"
    echo "Please check that you have valid Developer ID certificates."
fi

echo ""
echo "Next steps:"
echo "1. Build your app: faust2caqt Soleil_v1.1.dsp"
echo "2. Sign the app: ./scripts/sign-app.sh"
echo "3. Notarize: ./scripts/notarize.sh"
