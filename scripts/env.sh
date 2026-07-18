#!/bin/sh

export script_path=$(cd "$(dirname "$0")" && pwd)
export root_path="$script_path/.."
export bin_path="$root_path/bin"
export build_path="$root_path/build"
export build_examples_path="$build_path/examples"
export deps_path="$root_path/deps"
export examples_path="$root_path/examples"
export log_path="$root_path/log"