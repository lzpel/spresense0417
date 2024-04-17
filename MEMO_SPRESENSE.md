## build tips

### UbuntuからWifi接続

UbuntuからWIFI接続：インストール

```shell
curl -O https://github.com/sakai135/wsl-vpnkit/releases/download/v0.4.1/wsl-vpnkit.tar.gz
wsl --import wsl-vpnkit --version 2 $env:USERPROFILE\wsl-vpnkit wsl-vpnkit.tar.gz
```

UbuntuからWIFI接続：起動中は接続できるようになる

```shell
wsl.exe -d wsl-vpnkit --cd /app wsl-vpnkit
```

### ビルドと通信

```shell
## terminal毎に一度
source ~/spresenseenv/setup
## build
cd spresense/sdk
tools/config.py examples/hello
make -j
tools/flash.sh -c COM5 nuttx.spk
```

シリアル通信：

```shell
~/Programs/plink -serial COM5 -sercfg 115200,8,1,N,N
```

### アプリの追加方法

```shell
cd spresense/sdk
tools/mkappsdir.py myapps "My Apps"
tools/mkcmd.py -d myapps myfirstapp "My first app example"
```

アプリの設定
```shell
tools/config.py -d ../myapps default
# 以下同文
make -j
tools/flash.sh -c COM5 nuttx.spk
```

### clean

shell scriptを用意した

```shell
../distclean.sh
```

## defconfigとソースコードの対応

sdk/tools/config.pyの91行目に
```python
    def __get_defconfig(self, path):
        print(os.path.abspath(path))
```
と書けば