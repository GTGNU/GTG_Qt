#!/bin/bash
set -e
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
read qt_sdk_dir

if [ -z "$qt_sdk_dir" ]
then
	qmake_bin="$(which qmake)"
else
	i=0
	for bin in "$qt_sdk_dir"/5.*/*/bin/qmake
	do
		if [ $i = 0 ]
		then
			qmake_bin="$bin"
			i=$((i+1))
		else
			show "### There's more than one qmake binary. Please compile manually." >&2
			exit_with 1
		fi
	done

	if [ ! -e $bin ]
	then
		show "### Could not find qmake ($bin does not exist). Please compile manually" >&2
		exit_with 1
	fi
fi

show
show "> cwd: $PWD"
show "> qmake: $qmake_bin"
show

show_n ">> Continue? "
read ans

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
