#!/bin/bash

function print_help {
	echo "Usage: $0 component"
	echo "  Known components: ${known_components[@]}"
}

function clean {
	true
}


source helpers.sh

argv_help_flag "$@"
argv_component_arg "$@"

run cd "$component_dir/build/package"

if [ $component == "game" ]; then
	run ./gtg
elif [ $component == "editor" ]; then
	run ./editor
fi

exit_with $?
