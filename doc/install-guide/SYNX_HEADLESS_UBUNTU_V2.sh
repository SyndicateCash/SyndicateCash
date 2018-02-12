#!/bin/bash
# To build a SyndicateQT from https://github.com/SyndicateLabs/Syndicate Repository on to an Ubuntu VPS
# Adds swap and runs the wallet daemon (your first instance)
# to run multiple instances afterwards get guidance from the community (for now) 
# MUST RUN AS ROOT
######################################################################
# PLEASE REVIEW IT BEFORE YOUR RUN IT
######################################################################

clear
echo "Fingers crossed..... Thanks to REFFI for helping us test it :)"
echo "This script builds Syndicated from https://github.com/SyndicateLabs/SyndicateQT Repository on to an Ubuntu 14.04 VPS like Vultr $5"
echo "It also adds 3G of swap space and runs the wallet for your first instance"
echo "This script must be run as root"
echo "Created by community member Bbobb & fully reviewed by the development team."
sleep 5

fallocate -l 3G /swapfile
chmod 600 /swapfile
mkswap /swapfile
swapon /swapfile
echo -e "/swapfile   none    swap    sw    0   0 \n" >> /etc/fstab

apt-get update
apt-get -y install build-essential autoconf automake libtool libboost-all-dev libgmp-dev libssl-dev libcurl4-openssl-dev libevent-dev libdb-dev libdb++-dev git

cd /opt 
rm -rf SyndicateQT
git clone https://github.com/SyndicateLabs/SyndicateQT
cd SyndicateQT/src
chmod +x leveldb/build_detect_platform
chmod +x secp256k1/autogen.sh
make -f makefile.unix USE_UPNP=-
strip Syndicated
cp Syndicated /usr/local/bin
make -f makefile.unix clean
cd
Syndicated
sleep 10
echo -n "Key In a User Name for RPC access (preferably not your computer username) and press [ENTER]: "
read usrnam
echo -n "Key In a LONG RANDOM PASSWORD for the above user and press[ENTER]: "
read usrpas
echo -n "Key In the port your want the RPC to listen on  press[ENTER]: "
read rpcprt
echo -n "Key In the port your want the SYNX Daemon to listen on  press[ENTER]: "
read synxprt
echo -e "rpcuser=$usrnam \nrpcpassword=$usrpas \nrpcallowip=127.0.0.1 \nrpcport=$rpcprt \nport=$synxprt \nserver=1 \nlisten=1 \ndaemon=1 \nlogtimestamps=1 \nmnconflock=0 \naddnode=45.63.43.122:9999 \naddnode=45.32.156.245:9999 \naddnode=108.61.174.206:9999 \naddnode=45.63.62.79:9999 \naddnode=45.63.52.48:9999 \naddnode=45.63.111.165:9999 \naddnode=104.238.133.191:9999 \naddnode=45.32.148.12:9999 \naddnode=45.32.225.152:9999 \naddnode=45.63.27.232:9999 \naddnode=104.238.151.49:9999 \n" > ~/.Syndicate/Syndicate.conf
Syndicated
echo "Hold your horses for 10 sec"
sleep 10
Syndicated getinfo
echo "Need Help? ... Hop on Slack or BTCT https://bitcointalk.org/index.php?topic=1511215.0;topicseen and the community members WILL help you"