#!/usr/bin/env

CMDLINE="$0 $@"

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
    echo "  -g            Generate debug symbols."
    echo "  -o <dir>      Set output directory."
    echo "  -v            Enable verbose output."
    echo "  -x <ext>      Specify source language, e.g.: -x c, -x c++"
    echo "  --clean       Delete build artifacts."
    echo "  --            Run the compiled app, passing along remaining arguments."
    echo ""
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
        -D*|-I*|-O*|-std=*|-W*)
            CFLAGS="$CFLAGS $1"
            shift
        ;;
        -x)
            CFLAGS="$CFLAGS $1 $2"
            shift
            shift
        ;;
        -o)
            APP_BUILD_ROOT="$2"
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
            CFLAGS="$CFLAGS $SOURCE"
            shift
        ;;
    esac
done

if [ ! $SOURCES ]; then
    usage
    exit 1
fi

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
        time "$@" || exit $?
    else
        "$@" || exit $?
    fi
}

#-------------------------------------------------------------------------------

verbose "$CMDLINE"

#-------------------------------------------------------------------------------

APP_MAIN="${SOURCES[0]}"
APP_NAME="$(basename ${APP_MAIN%.*})"
APP_BUILD_ROOT="${APP_BUILD_ROOT:=$(dirname $APP_MAIN)/build}"

SCRIPTS_DIR="$(realpath $(dirname $0))"
TEMPLATES_DIR="$(dirname $SCRIPTS_DIR)/templates"

case $(uname | tr '[:upper:]' '[:lower:]') in
    darwin*)
        BUILD_OS=macos
        APP_BUILD_DIR="$APP_BUILD_ROOT/macos/$APP_NAME.app"
        APP_BIN="$APP_BUILD_DIR/Contents/MacOS/$APP_NAME"
    ;;
    linux*)
        BUILD_OS=linux
        echo "unsupported operating system"
        exit 1
    ;;
    msys*|mingw*)
        BUILD_OS=windows
        APP_BUILD_DIR="$APP_BUILD_ROOT/windows/$APP_NAME"
        APP_BIN="$APP_BUILD_DIR/$APP_NAME.exe"
        CFLAGS="${CFLAGS} -D_CRT_SECURE_NO_WARNINGS"
    ;;
    *)
        echo "unsupported operating system"
        exit 1
    ;;
esac

execute mkdir -p "$APP_BUILD_DIR"
cp -rf "$TEMPLATES_DIR/$BUILD_OS/." "$APP_BUILD_DIR/"

#-------------------------------------------------------------------------------

CC="${CC:=$(command -v cc || command -v gcc || command -v clang)}"

#-------------------------------------------------------------------------------

execute "$CC" $CFLAGS -o "$APP_BIN"

#-------------------------------------------------------------------------------

if [ $RUN ]; then
    echo $''
    execute "$APP_BIN" "$@"
    echo "$APP_BIN" returned "$?"
fi

#-------------------------------------------------------------------------------

if [ $CLEAN ]; then
    execute rm -rf  "$APP_BUILD_ROOT"
fi

#-------------------------------------------------------------------------------

exit

#-------------------------------------------------------------------------------
