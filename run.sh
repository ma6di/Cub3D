#!/bin/bash

cd program
# Build the bonus version
make bonus || { echo "Build failed."; exit 1; }

# Run the binary
./cub3D_bonus

