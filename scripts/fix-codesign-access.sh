#!/bin/bash
# Fix codesign access to Developer ID certificate private key

set -e

CERT_HASH="3B4C000EFEBC6902467D6DC39BC1F093C9745E65"
KEYCHAIN="$HOME/Library/Keychains/login.keychain-db"

echo "Fixing codesign access to Developer ID certificate..."
echo ""

# Find the private key
echo "Looking for private key..."
KEYS=$(security find-key -c "$CERT_HASH" "$KEYCHAIN" 2>&1 | grep "keychain:" | wc -l)

if [ "$KEYS" -eq 0 ]; then
    echo "❌ Private key not found for certificate!"
    echo ""
    echo "You may need to:"
    echo "1. Export the certificate with private key from your other Mac"
    echo "2. Or re-download from Apple Developer portal"
    exit 1
fi

echo "✅ Private key found"
echo ""

# Try to set partition list (will prompt for password)
echo "Setting partition list for private key access..."
echo "⚠️  This will prompt for your keychain password"
echo ""

security set-key-partition-list -S apple-tool:,apple:,codesign: -s -k "$CERT_HASH" "$KEYCHAIN"

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Partition list updated successfully"
    echo ""
    echo "Try signing now:"
    echo "  ./scripts/sign-app.sh"
else
    echo ""
    echo "❌ Failed to update partition list"
    echo ""
    echo "Alternative: Try signing with '-f' flag to force it"
fi
