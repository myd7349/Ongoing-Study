#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

source "$DIR/install_libfoo.sh"

cd "$DIR/build"
cmake ..


# References:
# https://stackoverflow.com/questions/59895/get-the-source-directory-of-a-bash-script-from-within-the-script-itself
# https://stackoverflow.com/questions/8352851/how-to-call-shell-script-from-another-shell-script
