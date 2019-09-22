#!/usr/bin/env
cd "$(dirname $0)"
sh "../scripts/build.sh" -std=c++11 -Werror -x c++ "../samples/simple.h" "$@"