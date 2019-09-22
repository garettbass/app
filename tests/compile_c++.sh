#!/usr/bin/env
sh "$(dirname $0)/../scripts/build.sh" -std=c++11 -Werror -x c++ "$(dirname $0)/../samples/simple.h" "$@"