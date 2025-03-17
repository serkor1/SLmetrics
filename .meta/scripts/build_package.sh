#!/bin/bash
# Script to build and install the package

# Get the check flag from command line arguments
CHECK=$1

# Build the package
echo "⚒️ Building package..."
R CMD build . > /dev/null 2>&1

if [ $? -ne 0 ]; then
    echo "Error: Package build failed."
    exit 1
fi

echo "✅ Package built successfully!"

# Get the tarball name
TARBALL=$(ls *.tar.gz | tail -n 1)

# Check the package if requested
if [ "$CHECK" = "true" ]; then
    echo "🔎 Checking package..."
    R CMD check --no-manual --as-cran "$TARBALL"
    
    # Check if check was successful
    if [ $? -ne 0 ]; then
        echo "Error: Package check failed."
        exit 1
    fi
    
    echo "✅ Package check passed!"
fi

# Install the package
echo "⚒️ Installing package..."
R CMD INSTALL "$TARBALL" > /dev/null 2>&1

if [ $? -ne 0 ]; then
    echo "Error: Package installation failed."
    exit 1
fi

echo "✅ Package installed successfully!"