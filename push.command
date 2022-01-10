#!/bin/sh
git add --all
git commit -m "`date '+%Y%m%d %H%M%S'`"
git push origin/master