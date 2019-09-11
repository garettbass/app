#!/usr/bin/env
sh "$(dirname $0)/compile_c.sh" -v --clean && echo "OK"
sh "$(dirname $0)/compile_c++.sh" -v --clean && echo "OK"