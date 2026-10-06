#!/bin/bash
# Build the HARM image. Usage: docker/build.sh [ref]   (default: dev; e.g. v4 after the release)
ref=${1:-dev}
docker build --platform linux/amd64 --build-arg HARM_REF="$ref" \
    --build-arg CACHE_DATE=$(date +%Y-%m-%d:%H:%M:%S) -t samger/harm:"$ref" "$(dirname "$0")"
