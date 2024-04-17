#!/usr/bin/env bash
set -eux
cd $(dirname $0)
# git ディレクトリを元状態に復帰することでmake distcleanより確実にcleanする
array=(nuttx sdk/apps)
for i in "${array[@]}"
do
  bash -c "cd $i && git reset --hard && git clean -fxd"
done