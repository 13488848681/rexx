# Rexx Node Installation Instructions for Ubuntu

## Server specification requirements
Need to keep port **17001、17002、17003** open.

| Type        | vCPU cores | RAM GB | Bandwidth Mbits/s | SSD GB |
|-------------|:----------:|:------:|:-----------------:|:------:|
| Minimum     |      4     |   16   |         10        |   500  |
| Recommended |      8     |   32   |         20        |   500  |


## Building & Installing (about 50 minutes)
All commands need to be executed under **super user mode**.

### Installing from PPA (5 minutes)
Execute the following commands separately. 
```
 sudo su
 apt-get update
 apt-get install automake
 apt-get install autoconf
 apt-get install libtool
 apt-get install g++
 apt-get install libssl-dev
 apt-get install cmake
 apt-get install libbz2-dev
 apt-get install python
 apt-get install unzip
```

### Building from source (35 minutes)

### Cloning the repository (10 minutes)

```
git clone https://github.com/RexxChain/rexx.git
```


### Downloading dependencies & initialization (5 minutes)
```
cd /rexx/build/
./install-build-deps-linux.sh
```


### Building (15 minutes)
```
cd /rexx/
make
```


### Installing the node (5 minutes)
```
cd /rexx/
make install
```

Rexx service will be installed under **/usr/local/rexxchain/**.


Catalog Structure

| Folder | Content                                    |
|--------|--------------------------------------------|
|    bin | Executable program                         |
|  jslib | Third-party js libraries                   |
| config | Configuration profile, including rexx.json |
|   data | Warehouse of ledger data                   |
| script | Activate script                            |
|    log | Running log                                |


### Setting runtime environments (5 minutes)
The runtime environment configuration files are under the following directory.
```
cd /usr/local/rexxchain/config/
```

The following runtime environments are available. 
For details, see **Rexx Runtime environment configuration**.
- rexx.json: Loaded by default after the program starts
- rexx-mainnet.json: Used for the main chain in production environments.
- rexx-testnet.json: Used for testing environments.
- rexx-single.json: Used for single-node development environments.

When executed, Rexx will use **rexx.json** by default, so environments configuration file must be backed up and renamed to **rexx.json** before starting Rexx.
```
cp rexx-testnet.json rexx.json
```

### Setting configuration (5 minutes)
- Setting the boot configuration
Execute the following commands separately.
```
ln -s -f /etc/init.d/rexxd /etc/rc1.d/S99Rexxd
ln -s -f /etc/init.d/rexxd /etc/rc2.d/S99Rexxd
ln -s -f /etc/init.d/rexxd /etc/rc3.d/S99Rexxd
ln -s -f /etc/init.d/rexxd /etc/rc4.d/S99Rexxd
ln -s -f /etc/init.d/rexxd /etc/rc5.d/S99Rexxd
```


- Adding the following line to the end of the **/etc/rc.local** file

`/etc/init.d/rexxd start`


- Changing the file permissions
```
chmod +x /etc/rc.local
```

After setting the boot configuration, you **NEED** to restart the system in order to make this configuration work (It starts Rexx automatically after reboot).

## Operation
### Check Rexx status
`service rexx status`

### Stop Rexx
`service rexx stop`

### Start Rexx
`service rexx start`

### Switch target network
Before switching target network, you need to **stop Rexx** first.
```
service rexx stop
cd /usr/local/rexxchain/config/
cp rexx.json rexx_backup1.json
cp rexx-testnet.json rexx.json
service rexx start
Drop Rexx database
cd /usr/local/rexxchain/bin
./rexx --dropdb
Drop Rexx consensus data
cd /usr/local/rexxchain/bin
./rexx --clear-consensus-status
```

### Get Rexx status details
`curl 127.0.0.1:17002/getModulesStatus`

### Uninstall Rexx
```
cd /rexx
make uninstall
rm -rf /usr/local/rexxchain
rm -rf /rexx
```

### Check Rexx Account information
`http://[IP address]:17002/getAccountBase?address=[Rexx Address]`
