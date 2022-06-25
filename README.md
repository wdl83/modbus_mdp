MDP Service with support for Modbus over Serial Line protocol
============================================================

Building
--------

```console
git clone --recurse-submodules https://github.com/wdl83/modbus_mdp
cd modbus_mdp
RELEASE=1 make
```
Build artifacts will be placed in *obj* dir, if you have not defined *OBJ_DIR*.

Installing
----------

*DST_DIR* variable can be used to define prefix (must be absolute) path for:

```console
RELEASE=1 DST_DIR=$HOME make install
```

Usage
-----
Worker requires the [**MDP Broker**](https://github.com/wdl83/mdp) address.

Running manually from console (register service with *SERVICE_NAME*).

```console
master_worker -a tcp://BROKER_IP:BROKER_PORT -d /dev/ttyUSB0 -s SERVICE_NAME
```

Running as systemd service. Create .config/systemd/user/SERVICE_NAME.service

```cosnole
[Unit]
Description=MDP Service, Modbus over Serial Line

[Service]
Environment=TRACE_LEVEL=2
Environment=LD_LIBRARY_PATH=$HOME/lib/:$LD_LIBRARY_PATH
ExecStart=$HOME/bin/master_worker -a tcp://BROKER_IP:BROKER_PORT -d /dev/ttyUSB? -s SERVICE_NAME
Restart=on-failure
RestartSec=10s

[Install]
WantedBy=default.target
```

After systemd service file is created enable it:

```console
systemctl --user enable SERVICE_NAME.service
```

and start

```console
systemctl --user start SERVICE_NAME.service
```

Enable systemd to start $USER services at boot (no $USER login required)

```console
loginctl enable-linger $USER
```
