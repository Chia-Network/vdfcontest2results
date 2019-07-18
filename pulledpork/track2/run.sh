#!/bin/sh
exec cgexec -g cpuset:/vdfonly ./vdf $1 $2

