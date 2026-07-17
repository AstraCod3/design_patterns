#!/bin/sh

echo ""
echo "Starting Build ..."
echo ""

# Include the common environment file for paths
. "$(dirname "$0")/env.sh" "$0"

# Function to display the help menu
show_help() {
    echo "Usage: $0 [OPTION]"
    echo ""
    echo "Available options:"
    echo "  -h, --help     Print this menu and exit"
    echo "  debug          Compile the project in Debug mode (with symbols)"
    echo "  release        Compile the project in Release mode (optimized)"
    echo "  examples       Compile only the examples (default true)"
    echo ""
    echo " Compile examples in release mode"
    echo "Example: ./scripts/build.sh example release"
    echo ""
    exit 0
}

# Set a default build type if the user doesn't provide one
build_type="Release"
build_examples="on"

# Parse command line arguments
for arg in "$@"
do
    case "$arg" in
        -h|--help)
            show_help
            ;;
        debug)
            build_type="Debug"
            ;;
        release)
            build_type="Release"
            ;;
        examples)
            build_examples="on"
            ;;
        "")
            # Default behavior when no argument is passed
            ;;
        *)
            echo "Error: Invalid option '$1'"
            echo "Use -h or --help to see available options."
            exit 1
            ;;
    esac
done

current_path=$(pwd)



if [ "$build_examples" = "on" ]; then
    mkdir -p $build_examples_path
    cd "$build_examples_path"
    echo ""
    echo "Building examples"
    cmake "$examples_path" -DCMAKE_BUILD_TYPE="$build_type"
    make
fi

cd $current_path

echo ""
echo "... done!"
echo ""
