#!/bin/bash

assert()
{
	printf '%-30s:' "\"$1\""
	# bash
	echo -n -e "$1" | bash >cmp 2>&-
	expected=$?
	# minishell
	echo -n -e "$1" | ./minishell >out 2>&-
	actual=$?
	# compare
	diff cmp out >/dev/null && echo -n ' diff OK ' || echo -n ' diff NG '
	# exit status
	if [ "$actual" = "$expected" ]; then
		echo -n ' status OK '
	else
		echo -n " status NG, expected $expected but got $actual "
	fi
	echo
}

# TEST CASE

# Empty line (EOF)
assert ''