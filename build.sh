#!/bin/sh

# from https://gitee.com/Sipeed/M1s_BL808_example.git 4581c2417d047e5598ab338fbaabff987c3fc9e9

PROJECT_NAME=$1

make CONFIG_CHIP_NAME=BL808 CPU_ID=D0 -j$(nproc) PROJECT_NAME=$PROJECT_NAME
cp build_out/$PROJECT_NAME.bin build_out/d0fw.bin
exit $?
