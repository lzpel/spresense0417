#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import sys
import os
import subprocess


def clean(argv):
    def git_recover(path):
        call("bash", "-c", "cd {} && git reset --hard && git clean -fxd".format(path))

    git_recover(root("nuttx"))
    git_recover(root("sdk/apps"))


def mkapp(argv):
    apptypes=["device", "examples", "feature"]
    for i in argv:
        config_name = i.split("/")
        if not (len(config_name) >= 2 and config_name[-2] in apptypes):
            print("config_name should be {{APPDIR={}}}/{}".format("|".join(apptypes),"{APPNAME}"))
        else:
            appdir=os.path.abspath(os.path.join(*config_name))
            approot=os.path.abspath(os.path.join(*config_name, ".."))
            call(root("sdk", "tools", "mkappsdir.py"), approot, "approot for {}".format(approot))
            call(root("sdk", "tools", "mkcmd.py"), "-d", approot, config_name[-1], "application {}".format(config_name[-1]))
            call("cp", "-r", os.path.join(appdir, "configs"), approot)
            call("rm", "-rf", os.path.join(appdir, "configs"))



def main(argv):
    if argv[0] == "clean":
        clean(argv[1:])
    elif argv[0] == "mkapp":
        mkapp(argv[1:])
    else:
        call(*argv)


# pyshell基礎20240418
def root(*path_element):
    return os.path.abspath(os.path.join(sys.argv[0], "..", *path_element))


def call(*argv):
    print(*['"{}"'.format(i) if " " in i else i for i in argv])
    return subprocess.call(argv)


if __name__ == "__main__":
    main(sys.argv[1:])
