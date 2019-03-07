#/bin/bash

#git fetch --all;
#git reset --hard origin/release/1.0.0.0
#git reset --hard origin/develop

DATE=$(date +%Y_%m%d_%H%M)

cd ../../
rm -rf pack/
echo 'make clean'
make clean

echo "make clean build"
make clean_build


#update git

version=`git log |grep commit |head -1`
echo 'version: ' + $version

#get shortest hash
v=${version:7:7}

#make 
make rexx_version=$v

mkdir -p pack
cd pack/
rm -rf rexxchain/
mkdir rexxchain
mkdir rexxchain/config
mkdir rexxchain/data
mkdir rexxchain/jslib
mkdir rexxchain/bin
mkdir rexxchain/log
mkdir rexxchain/scripts
mkdir rexxchain/coredump
cp ../build/win32/jslib/jslint.js rexxchain/jslib/
cp ../build/win32/config/rexx-mainnet.json rexxchain/config/
cp ../build/win32/config/rexx-testnet.json rexxchain/config/
cp ../build/win32/config/rexx-single.json  rexxchain/config/
cp ../build/win32/config/ReadMe.txt  rexxchain/config/
cp ../deploy/rexx  rexxchain/scripts/
cp ../deploy/rexxd  rexxchain/scripts/
cp ../deploy/start-stop-daemon  rexxchain/scripts/
cp ../bin/rexx rexxchain/bin/
cp ../bin/rexxd rexxchain/bin/
cp ../src/3rd/v8_target/linux/*.bin rexxchain/bin/
cp ../src/3rd/v8_target/linux/*.dat rexxchain/bin/

chmod +x rexxchain/scripts/*

tar czvf rexxchain-linux-$DATE-$v.tar.gz rexxchain/
rm -rf rexxchain/

echo "build ok...."



