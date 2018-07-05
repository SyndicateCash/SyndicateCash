# Syndicate Manual Setup Guide
Last update: 2017.09.11

Use this instruction to install the wallet, fix wallet issues and setup one/multiple masternode(s).
This guide is for the creation of separate Controller Wallet & Masternode.
For Security reasons, THIS IS THE PREFERRED way to run a Masternode. By running your Masternode in this way you are protecting
your coins in your private wallet, and are not required to have your local wallet running after the Masternode has been started successfully.
Your coins will be safe if the masternode server gets hacked.

## Table of Content
* [1. The first masternode](#1-the-first-masternode)
	* [1.1 Send the coins to your wallet](#11-send-the-coins-to-your-wallet)
	* [1.2 Install putty and winscp](#12-install-putty-and-winscp)
	* [1.3 VPS setup](#13-vps-setup)
	* [1.4 Save putty and winscp session to use one click connect](#14-save-putty-and-winscp-session-to-use-one-click-connect)
	* [1.5 Secure the server](#15-secure-the-server)
	* [1.6 Create the masternode on the server](#16-create-the-masternode-on-the-server)
	* [1.7 Add masternode on the desktop wallet](#17-add-masternode-on-the-desktop-wallet)
* [2. The Xth masternode](#2-the-xth-masternode)
* [3. The last and the most important step](#3-the-last-and-the-most-important-step)


## 1. The first masternode

### 1.1 Send the coins to your wallet
1. Open Console (Help => Debug window => Console)
1. Create a new address. `getnewaddress Masternode1`
1. Send exactly 5000 coins to this address. (One transaction, pay attention to the fee)
1. Wait for the conformation.
1. Save the transaction id, index `masternode outputs`, and generate and save a new masternode private key `masternode genkey`.
1. You can optionaly encrypt the wallet (Settings => Encypt wallet) for security reasons. Do not forget the password or you lose the coins that you have.
1. Backup `%appdata%/Syndicate/wallet.dat` file. This contains your coins. DO NOT LOSE IT!

### 1.2 Install putty and winscp
1. Download and install [putty](https://the.earth.li/~sgtatham/putty/latest/w64/putty-64bit-0.70-installer.msi)
1. Create a new ssh key.
	- Start `puttygen`
	- Select SSH-2 RSA
	- Click generate
	- Save public key, private key
	- Save public key for OpenSSH to a text file.
1. Download [winscp](https://winscp.net/download/WinSCP-5.9.6-Setup.exe). Not necessary if you can use linux terminal editors.

### 1.3 VPS setup
1. Register on [vultr](https://www.vultr.com/?ref=7205683).
1. Send some money (10$ is enough for two months) to your account to deploy a server. (1 server cost 5$/mo, you can pay with bitcoin)
1. Add your private OpenSSH key (Servers => SSH Key => Add SSH Key).
1. Deploy a new server.
    - Server Type: Ubuntu 14.04  
    - Server Size: 5$/mo, 1GB memory (This server is capable to run 3 masternodes. One masternode need 300-400Mb memory)  
    - Add the private key

### 1.4 Save putty and winscp session to use one click connect
1. Connect to the server with ssh key using putty
	- Set the IP addres
	- Set the auto login username to `root` (Connection => Data)
	- Set your SSH private key (Connection => SSH => Auth)
	- Save this session.
1. Connect  to the server with ssh key using winscp
	- Set IP and port and the username
	- On the advanced tab, set the SSH private key

### 1.5 Secure the server
1. Update the system
	- `apt-get update`
	- `apt-get upgrade`
1. Protect against dictionary attack
	- `apt-get install fail2ban`
1. Disable password authentication. You can login using the ssh key.
	Edit `/etc/ssh/sshd_config` file using winscp.
	Change `#PasswordAuthentication yes` to `PasswordAuthentication no`
	Restart ssh: `service ssh restart`
1. Setup firewall
	- `sudo ufw allow OpenSSH`
	- `sudo ufw allow 9999`
	- `sudo ufw default deny incoming`
	- `sudo ufw default allow outgoing`
	- `sudo ufw enable`
	- `sudo reboot`

### 1.6 Create the masternode on the server
1. Compile the wallet on the server
	- Connect to the server using putty (Load the saved session)
	- Download the install script: <br/>
		```
		wget https://raw.githubusercontent.com/SyndicateLabs/SyndicateAutoVPS/master/SYNX_HEADLESS_UBUNTU_V1.sh
		```
	- Add executable flag: `chmod +x ./SYNX_HEADLESS_UBUNTU_V1.sh`
	- Run the script and wait a few minutes until it completes: `./SYNX_HEADLESS_UBUNTU_V1.sh` (Set the rpc username and the rpc password, rpc port = 22350, synx port = 9999)
	- Stop Syndicated: `Syndicated stop`
	- Intall unzip: `apt-get install unzip`
1. Create a new user: `adduser mn1`. Note: the password is invisible when you are typing it
1. Add user to sudo group: `usermod -a -G sudo mn1`
1. Login to the user: `su mn1`
1. Start the wallet: `Syndicated`
1. Set the rpc username and password on the desktop conf file `%appdata%/Syndicate/Syndicate.conf`

    ```
    rpcuser=[SomeUserName]
    rpcpassword=[HardAndLongPassword]
    ```

1. Set the server config `/home/mn1/.Syndicate/Syndicate.conf` to the following:

    ```
    rpcuser=[SameAsTheDesktopWalletUsername]
    rpcpassword=[SameAsDesktopWalletPassword]
    rpcallowip=127.0.0.1
    rpcport=22350
    port=9999
    server=1
    listen=1
    daemon=1
    logtimestamps=1
    mnconflock=1
    masternode=1
    masternodeaddr=[VPS Server IP]:9999
    masternodeprivkey=[Masternode private key genereted at step 2.1.5]
    ```

1. Add nodes to server config file `/home/mn1/.Syndicate/Syndicate.conf`. (step 1.2.5)
1. Download the boostrap file: `cd && wget https://transfer.sh/t2Xo2/Syndicate_blockchain_2017_09_10.zip`
1. Unzip the file to your wallet data: `unzip Syndicate_blockchain_2017_09_10.zip -d .Syndicate`
1. Delete peers.dat file: `rm /home/mn1/.Syndicate/peers.dat`
1. Start the wallet: `Syndicated`
1. Wait for sync (1h-12h depending on the connections). Check to current block using `Syndicated getinfo` and [http://synx.cryptophi.com/](http://synx.cryptophi.com/)

### 1.7 Add masternode on the desktop wallet

1. Open wallet, wait for sync, unlock wallet
1. Go Masternodes tab
1. Click create
	- Set a name: Masternode1
	- Set the VPS ip and the port: [Ip:Port]
	- Set the generated private key: step 2.1.5
	- Click Add and after click Start
	- Wait 1 day to start receiving coins. Check your the masternode address here: [http://synx.cryptophi.com/](http://synx.cryptophi.com/)
	- Note: You can't edit the masternodes config in the wallet but you can edit the file. `%appdata%/Syndicate/masternode.conf`.

## 2. The Xth masternode

1. Repeat step 2.1
1. Create a new user: `adduser mnX`
1. Add user to sudo group: `usermod -a -G sudo mnX`
1. Login as the user: `su mnX`
1. Copy previous masternode files to home directory: `sudo cp -rf /home/mn1/.Syndicate /home/mnX/`
1. Fix premission issues: `sudo chown -R mnX:mnX /home/mnX/.Syndicate`
1. Delete peers.dat file: `rm /home/mnX/.Syndicate/peers.dat`
1. Edit config file `/home/mnX/.Syndicate/Syndicate.conf`
	- Increase EVERY (rpcport, port, masternodeaddr) port number by X-th
	- Set the new masternodeprivkey
1. Add the new port to firewall: `sudo ufw allow [NewPort]`
1. Start the wallet: `Syndicated`
1. Wait for sync (1h-12h depending on the connections). Check to current block using `Syndicated getinfo` and [http://synx.cryptophi.com/](http://synx.cryptophi.com/)
1. Repeat 2.7 step

## 3. The last and the most important step

Send some love for the the instruction.

| Coin           | Address  |
| ---------------| ---------|
| Syndicate coin | SQaK48Xo9HToqCvG36YZACkFKbmHNamH6T |
| BTC 			 | 1GMWb8sGBrbYweyDnHtMzon56fcmQRb1j  |
| ETH 			 | 0x5E7c58EE90a684202227AB432d27DaAf51BBCA0f |

	
