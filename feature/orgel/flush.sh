../tools.py clean
tools/config.py -d ../feature feature/orgel feature/startup_script
make
tools/flash.sh -c COM3 -w ../feature/orgel/init.rc
tools/flash.sh -c COM3 nuttx.spk
rm