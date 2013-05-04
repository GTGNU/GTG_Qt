# Expects functions print_help and clean to be defined
set -e
shopt -s nullglob

trap error_handler EXIT

script_location=$(readlink -f $0)

known_components=(editor game)
step=""

component=""
component_dir=""

function show_n {
	echo -n -e "\033[1m$@\033[0m"
}

function show {
	echo -e "\033[1m$@\033[0m"
}

function show_error {
	show "\033[31m### $@" >&2
}


function run {
	step="$@"
	show "\033[32m>>> $@"
	"$@"
}


function exit_with {
	# Cleanup if error after the process has started
	if [ "$1" != "0" ] && [ ! -z "$step" ]
	then
		clean
	fi

	# error_handler is called
	step="--finish-ok--"
	exit $1
}

function error_handler {
	if [ "$step" != "--finish-ok--" ]
	then
		show_error "Error running '${step}'"
		clean
		exit 1
	fi
}


function argv_help_flag {
	# Help flag
	if [ "$1" = "-h" ] || [ "$1" = "--help" ]
	then
		print_help
		exit_with 0
	fi
}

# Scan argv for the object component and check that it's known
function argv_component_arg {
	component="$1"

	set +e
	for i in "${known_components[@]}"
	do
		echo $i
	done | grep '^'"$component"'$' >/dev/null

	if [ $? != 0 ]
	then
		show_error "Unknown component '${component}'"
		print_help
		exit_with 1
	fi
	set -e

	component_dir=$(dirname $script_location)
	component_dir="$component_dir/$component"

	if [ ! -d "$component_dir" ]
	then
		show_error "Component directory does not exist: $component_dir"
		print_help
		exit_with 1
	fi
}

