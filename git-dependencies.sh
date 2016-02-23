#!/bin/bash
## inih
git clone https://github.com/OSSystems/inih.git ~/inih
cp toolchain-bbb.cmake ~/inih

## openssl
git clone https://github.com/openssl/openssl.git  ~/openssl
cd ~/openssl
git checkout -b 1.0.2-stable remotes/origin/OpenSSL_1_0_2-stable
cd ~

## libcap
git clone http://git.kernel.org/pub/scm/linux/kernel/git/morgan/libcap.git ~/libcap
cd ~/libcap
git checkout -b 2.24 tags/libcap-2.24
cd ~

## alljoyn
git clone https://git.allseenalliance.org/gerrit/core/alljoyn.git ~/alljoyn
cd ~/alljoyn
git checkout -b rb15.04 remotes/origin/RB15.04
cd ~

## influxdb
go get github.com/influxdb/influxdb
cd ~/gocode/src/github.com/influxdata/
go get ./...

## libcurl
git clone https://github.com/curl/curl.git
cd ~/curl
git checkout tags/curl-7_35_0
cd ~
