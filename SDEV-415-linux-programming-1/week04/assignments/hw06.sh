#!/bin/bash
set -x #echo on

ls /usr/local/ > ~/ls_output.txt

echo ~/
ls ~/

wc -l ~/ls_output.txt

ls /usr/local/ | wc -l