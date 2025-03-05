#!/bin/bash

cat <<EOF | gcc -xc -o a.out -
#include <stdio.h>
int main() { printf("hello from a.out\n"); }
EOF

cat <<EOF | gcc -xc -o print_args -
#include <stdio.h>
int main(int argc, char **argv)
{
	for (int i = 0; argv[i]; i++)
		printf("argv[%d] = %s\n", i, argv[i]);
}
EOF

cleanup()
{
	rm -f cmp out a.out print_args
}

assert()
{
	printf '%-50s:' "[$1]"
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
## unquoted word
assert 'ls /'
assert 'echo hello    world     '
assert 'nosuchfile\n\n'

## single quote
assert 'echo 'hello''
assert 'echo hello'world''
assert "./print_args 'hello   world' '42Tokyo'"
assert "echo 'hello   world' '42Tokyo'"
assert "echo '\"hellow   world\"' '42Tokyo'"

## double quote
assert './print_args "hello    world" "42Tokyo"'
assert 'echo "hello    world" "42Tokyo"'
assert "echo \"'hello   world'\" \"42Tokyo\""

## combination
assert "echo hello'     world'"
assert "echo hello'    world   '\"   42Tokyo   \""

## syntax error
assert "echo 'a"
assert 'echo "b'

cleanup
echo 'all OK'