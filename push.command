#!/bin/sh
filepath=$(cd "$(dirname "$0")"; pwd)
source $filepath/cfg.config
cd ${route}
git add --all
git commit -m "`date '+%Y-%m-%d %H:%M:%S'`"
git push origin ${remote_branch}