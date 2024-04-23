#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import sys
import os
import subprocess


class PyShell:
    subcommands = {}

    def subcommand(self, func):
        def wrapper(*args, **kwargs):
            print("Command: ", func.__name__)
            return func(*args, **kwargs)

        self.subcommands[func.__name__] = wrapper
        return wrapper

    def command(self, *argv):
        print(*['"{}"'.format(i) if " " in i else i for i in argv])
        return subprocess.call(argv)

    def path_from_this(self, *path_element):
        return os.path.abspath(os.path.join(sys.argv[0], "..", *path_element))

    def main(self, *argv):
        if not argv:
            argv = sys.argv[1:]
        if argv[0] in self.subcommands:
            self.subcommands[argv[0]](argv[1:])
        else:
            print("unrecognized commands: {}".format(" ".join(argv)))
            print("available commands: {}".format(" ".join(self.subcommands)))


ps = PyShell()


@ps.subcommand
def clean(argv):
    def git_recover(path):
        # gitの状態を復元
        ps.command("bash", "-c", "cd {} && git reset --hard && git clean -fxd".format(path))

    git_recover(ps.path_from_this("nuttx"))
    git_recover(ps.path_from_this("sdk/apps"))


@ps.subcommand
def mkapp(argv):
    apptypes = ["device", "examples", "feature"]
    for i in argv:
        config_name = i.split("/")
        if not (len(config_name) >= 2 and config_name[-2] in apptypes):
            print("config_name should be {{APPDIR={}}}/{}".format("|".join(apptypes), "{APPNAME}"))
        else:
            appdir = os.path.abspath(os.path.join(*config_name))
            approot = os.path.abspath(os.path.join(*config_name, ".."))
            ps.command(ps.path_from_this("sdk", "tools", "mkappsdir.py"), approot, "approot for {}".format(approot))
            ps.command(ps.path_from_this("sdk", "tools", "mkcmd.py"), "-d", approot, config_name[-1],
                       "application {}".format(config_name[-1]))
            ps.command("cp", "-r", os.path.join(appdir, "configs"), approot)
            ps.command("rm", "-rf", os.path.join(appdir, "configs"))


# pyshell基礎20240418


if __name__ == "__main__":
    ps.main()
