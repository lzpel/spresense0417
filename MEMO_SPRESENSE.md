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

## mytool.py

shell scriptを用意した

```shell
../mytool.py clean
../mytool.py mkapp ../feature/myhello
tools/config.py -d ../feature feature/myhello
# 以下同文
make -j
tools/flash.sh -c COM5 nuttx.spk
```

### defconfigとソースコードの対応

sdk/tools/config.pyの91行目に
```python
    def __get_defconfig(self, path):
        print(os.path.abspath(path))
```
と書けば

### rust

```
rustup target add thumbv7em-none-eabihf
```

sdk/configs/examples/hello/defconfig
```
+EXAMPLES_HELLO_RUST=y
```
と追記すればrustもコンパイルされる

RUSTC:  hello_rust_main.rs error[E0463]: can't find crate for `core`
  |
  = note: the `thumbv7em-none-eabihf` target may not be installed
  = help: consider downloading the target with `rustup target add thumbv7em-none-eabihf`

```
. ~/spresenseenv/setup
# or arm-none-eabi-gcc: command not found
./tools/config.py examples/hello
make
./tools/flash.sh -c COM5 nuttx.spk
```

```
$ ~/Programs/plink -serial COM5 -sercfg 115200,8,1,N,N

NuttShell (NSH) NuttX-12.3.0
nsh> hello_rust
Hello, Rust!!
```

https://github.com/apache/nuttx/pull/5566#issuecomment-1049585330
```
Understand. It's reasonable to enable the bare-metal usage in the first step. In the next step, I guess a special cargo with the embedded OS in mind may be a good option. It will be great that we can build up a packet manager for IoT space, since all devices can get the huge packet directly.
```
