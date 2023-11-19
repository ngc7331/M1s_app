#!/bin/bash

BL_SDK_PATH=${BL_SDK_PATH:-$(realpath ../../M1s_BL808_SDK)}
PATCH_PATH=$(pwd)

cd ${BL_SDK_PATH} && \
git apply ${PATCH_PATH}/*.patch
