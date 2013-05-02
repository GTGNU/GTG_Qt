#!/bin/bash
set -e
shopt -s nullglob
trap error EXIT

step=""

function print_help {
	echo "Usage: $0 [MAKE_FLAGS]"
}

function show_n {
	echo -n -e "\033[1m$@\033[0m"
}

function show {
	echo -e "\033[1m$@\033[0m"
}

function run {
	show ">>> $@"
	step="$@"
	$@
}

function clean {
	show ">>> Cleaning"
	rm -rf build
}

function error {
	if [ ! "$step" = "--finish-ok--" ]
	then
		show "### Error running $step" >&2
		exit 1
	fi
}

function exit_with {
	step="--finish-ok--"

	if [ ! "$1" = 0 ]
	then
		clean
	fi

	exit $1
}



if [ "$1" = "-h" ] || [ "$1" = "--help" ]
then
	print_help
	exit_with 0
fi


SCRIPT=$(readlink -f $0)
DIR=$(dirname $SCRIPT)
cd "$DIR"

show_n ">> Qt SDK location (leave empty if not using the SDK): "
read -e qt_sdk_dir

qmake_bins=()

# Find all qmake binaries in the specified location
if [ -z "$qt_sdk_dir" ]
then
	qmake_bins=("$(qtchooser -qt=5 -run-tool=qmake -query QT_INSTALL_BINS)/qmake")
else
	qmake_dirs="$qt_sdk_dir"/5.*/*/bin

	for qmake_dir in ${qmake_dirs[@]}
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
	# Skip, catch the empty variable below
	true

elif [ "${#qmake_bins[@]}" = 1 ]
then
	qmake_bin=${qmake_bins[0]}

else
	# Ask the user which one to use
	show "Please select the qmake binary to use: "
	select bin in "${qmake_bins[@]}"
	do
		qmake_bin="$bin"
	done
fi

# Check if it exists
if [ ! -f "$qmake_bin" ] || [ ! -x "$qmake_bin" ]
then
	show "### Could not find qmake ('$qmake_bin' is not an executable file). Please compile manually" >&2
	exit_with 1
fi

# Confirm
show
show "> cwd: $PWD"
show "> qmake: $qmake_bin"
show

show_n ">> Continue? "
read ans

# Continue
if [ "$ans" = "y" ] || [ "$ans" = "Y" ] || [ "$ans" = "yes" ]
then
	clean
	run mkdir build
	run cd build
	run "$qmake_bin" ..
	run make $@
	run make INSTALL_ROOT=package install

	show Build successful
	exit_with 0

else
	show Aborted
	exit_with 1
fi
