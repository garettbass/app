///usr/bin/env sh $(dirname $0)/../scripts/build.sh -std=c11 -Werror -Wall -Wextra -x c "$0" "$@"; exit $?
#include "../app.inl"

int app_main(void) {
    app_window* window = app_window_acquire();
    app_window_activate(window);
    app_window_set_title(window, "app");
    while (app_update() and app_window_is_open(window));
    app_window_release(window);
    return 0;
}
