#!/bin/bash

cat <<EOF | gcc -xc -o a.out -
#include <stdio.h>
int main() { printf("hello from a.out\n"); }
EOF

cleanup()
{
	rm -f cmp out a.out
}

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
	diff cmp out  && echo -n ' diff OK ' || echo -n ' diff NG '
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

# Absolute path
assert '/bin/pwd'
assert '/bin/echo'

# command
assert 'pwd'
assert 'echo'
assert 'ls'
assert './a.out'

# no such command
assert 'a.out' # カレントディレクトリはPATH変数の値にないので実行不可の仕様
assert 'nosuchfile'

# Tokenize
assert 'ls /'
assert 'echo hello    world     '
assert 'nosuchfile\n\n'

cleanup
echo 'all OK'