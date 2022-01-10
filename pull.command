#!/bin/sh
filepath=$(cd "$(dirname "$0")"; pwd)
source $filepath/cfg.config
cd ${route}
git pull origin ${remote_branch}