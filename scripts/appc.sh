#!/usr/bin/env

CMDLINE="$0 $@"

#-------------------------------------------------------------------------------

function verbose {
    if [ $VERBOSE ]; then
        echo "$@"
    fi
}

#-------------------------------------------------------------------------------

function execute {
    verbose "$@"
    if [ $TIME ]; then
        time "$@"
    else
        "$@"
    fi
}

#-------------------------------------------------------------------------------

function realpath {
    local path="${1//\\//}"
    if [ "$path" == "." ]; then
        echo "$(pwd)"
    elif [ "$path" == ".." ]; then
        echo "$(dirname "$(pwd)")"
    else
        echo "$(cd "$(dirname "$path")"; pwd)/$(basename "$path")"
    fi
}

#-------------------------------------------------------------------------------

if [ -z "$CC" ]; then
    CC="$(which cc)"
    if [ ! -f "$CC" ]; then
        CC="$(which gcc)"
        if [ ! -f "$CC" ]; then
            CC="$(which clang)"
        fi
    fi
fi

#-------------------------------------------------------------------------------

# CFLAGS="${CFLAGS:=-Werror}"

#-------------------------------------------------------------------------------

function usage {
    echo "Usage:"
    echo ""
    echo "  sh $0 [options] <sources> [-- ...]"
    echo ""
    echo "Options:"
    echo ""
    echo "  -std=<...>    Set C/C++ standard, e.g "
    echo "  -D<...>[=...] Define preprocessor macro, e.g.: -DNDEBUG=1"
    echo "  -O<...>       Set optimization level, e.g.: -O0, -O1, -O2, -O3, -Ofast, -Os"
    echo "  -o <...>      Specify output path."
    echo "  -g            Generate debug symbols."
    echo "  -v            Enable verbose output."
    echo "  -x <ext>      Specify source language, e.g.: -x c, -x c++"
    echo "  --clean       Delete build artifacts."
    echo "  --            Run the compiled app, passing along remaining arguments."
    echo ""
}

#-------------------------------------------------------------------------------

SOURCES=()
while [ $# -gt 0 ]; do
    case $1 in
        -h|--help)
            usage
            exit 1
        ;;
        -g)
            CFLAGS="$CFLAGS $1 -D_DEBUG=1"
            shift
        ;;
        -D*|-O*|-std=*|-W*)
            CFLAGS="$CFLAGS $1"
            shift
        ;;
        -o)
            APP_BIN="$2"
            shift
            shift
        ;;
        -x)
            CFLAGS="$CFLAGS $1 $2"
            shift
            shift
        ;;
        -t)
            TIME=YES
            shift
        ;;
        -v)
            VERBOSE=YES
            CFLAGS="$CFLAGS -DVERBOSE=1"
            shift
        ;;
        --clean)
            CLEAN=YES
            shift
        ;;
        --)
            RUN=YES
            CLEAN=YES
            shift
            break
        ;;
        -*)
            echo "unrecognized option: $1"
            echo ""
            usage
            exit 1
        ;;
        *)
            SOURCE="$(realpath $1)"
            SOURCES+=("$SOURCE")
            shift
        ;;
    esac
done

if [ ! $SOURCES ]; then
    usage
    exit 1
fi

#-------------------------------------------------------------------------------

verbose "$CMDLINE"

#-------------------------------------------------------------------------------

APP_MAIN="${SOURCES[0]}"
APP_ROOT="$(dirname $APP_MAIN)"
APP_NAME="$(basename ${APP_MAIN%.*})"

case $(uname | tr '[:upper:]' '[:lower:]') in
    linux*)
        APP_HOST_OS=linux
    ;;
    darwin*)
        APP_HOST_OS=macos
    ;;
    msys*|mingw*)
        APP_HOST_OS=windows
        CFLAGS="${CFLAGS} -D_CRT_SECURE_NO_WARNINGS"
        APP_EXT=".exe"
    ;;
    *)
        echo "unrecognized operating system"
        exit 1
    ;;
esac

APP_BIN="${APP_BIN:=$APP_ROOT/$APP_NAME$APP_EXT}"

#-------------------------------------------------------------------------------

COMPILE="$CC $CFLAGS ${SOURCES[@]} -o $APP_BIN"
execute $COMPILE
STATUS=$?
if [ $STATUS -gt 0 ]; then exit $STATUS; fi

#-------------------------------------------------------------------------------

if [ $RUN ]; then
    echo $''
    verbose "$APP_BIN" "$@"
    "$APP_BIN" "$@"
    STATUS=$?
    echo $''
    echo "$APP_BIN" returned "$STATUS"
fi

if [ $CLEAN ]; then
    rm -f  "${APP_BIN}"
    rm -f  "${APP_BIN%.*}.ilk"
    rm -f  "${APP_BIN%.*}.pdb"
    rm -rf "${APP_BIN%.*}.dSYM"
fi

#-------------------------------------------------------------------------------

exit $STATUS

#-------------------------------------------------------------------------------
