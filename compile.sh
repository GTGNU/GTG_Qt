#!/bin/bash

function print_help {
	echo "Usage: $0 component $@"
	echo "  Known components: ${known_components[@]}"
}

function clean {
	show "\033[33m>>> Cleaning"
	rm -rf build
}


source helpers.sh

argv_help_flag "$@"
argv_component_arg "$@"

cd "$component_dir"


# Get make flags
make_flags=("$@")
unset -v 'make_flags[0]'
make_flags_printable=$(printf "'%s' " "${make_flags[@]}")


# Support building with the Qt SDK
show_n ">> Qt SDK location (leave empty if not using the SDK): "
read -e qt_sdk_dir



# Find all qmake binaries in the specified location
qmake_bins=()

if [ -z "$qt_sdk_dir" ]
then
	# Use system's Qt5
	qmake_bins=("$(qtchooser -qt=5 -run-tool=qmake -query QT_INSTALL_BINS)/qmake")
else
	# Use Qt SDK
	qmake_dirs=("$qt_sdk_dir"/5.*/*/bin)

	for qmake_dir in "${qmake_dirs[@]}"
	do
		qmake_path="$qmake_dir/qmake"
		if [ -e "$qmake_path" ]
		then
			qmake_bins=("${qmake_bins[@]}" "$qmake_path")
		fi
	done
fi

# Select the binary automatically if only one
if [ "${#qmake_bins[@]}" = 0 ]
then
	# Skip, error is handled later
	true

elif [ "${#qmake_bins[@]}" = 1 ]
then
	# Choose the first binary if only one qmake is found
	qmake_bin="${qmake_bins[0]}"

else
	# Ask the user which one to use
	show "Please select the qmake binary to use: "
	select bin in "${qmake_bins[@]}"
	do
		qmake_bin="$bin"
	done
fi

# Check if the result it exists
if [ ! -f "$qmake_bin" ] || [ ! -x "$qmake_bin" ]
then
	show_error "Could not find qmake ('$qmake_bin' is not an executable file). Please compile manually"
	exit_with 1
fi



# Confirm before proceeding
show
show "> component:       $component"
show "> build directory: $PWD"
show "> qmake binary:    $qmake_bin"
show "> make flags (${#make_flags[@]}):  ${make_flags_printable[@]}"
show

show_n ">> Continue? "
read ans



# Main action
if [ "$ans" = "y" ] || [ "$ans" = "Y" ] || [ "$ans" = "yes" ]
then
	clean
	run mkdir build
	run cd build
	run "$qmake_bin" ..
	run make "${make_flags[@]}"
	run make INSTALL_ROOT=package install

	show "Build successful"
	exit_with 0

else
	show_error "Aborted"
	exit_with 1
fi
