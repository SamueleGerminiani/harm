#!/bin/bash
# Build the HARM image. Usage: docker/build.sh [ref]   (default: v4, the release; e.g. dev for a newer build)
ref=${1:-v4}
tag=${ref//\//-}   # an image tag cannot contain '/' (a branch like ms/H11d-tools)
docker build --platform linux/amd64 --build-arg HARM_REF="$ref" \
    --build-arg CACHE_DATE=$(date +%Y-%m-%d:%H:%M:%S) -t samger/harm:"$tag" "$(dirname "$0")"
