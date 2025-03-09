#!/bin/bash
RED="\033[31m"
GREEN="\033[32m"
RESET="\033[0m"
OK=$GREEN"OK"$RESET
NG=$RED"NG"$RESET

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
	COMMAND="$1"
	shift
	printf '%-50s:' "[$COMMAND]"
	# bash
	echo -n -e "$COMMAND" | bash >cmp 2>&-
	expected=$?
	for arg in "$@"
	do
		if [ -z "$arg" ] || [  "${arg:0:5}" = "/bin/"  ] ; then
			continue
		fi
		test -n "$arg" && mv "$arg" "$arg"".cmp"
	done
	# minishell
	echo -n -e "$COMMAND" | ./minishell >out 2>&-
	actual=$?
	for arg in "$@"
	do
		if [ -z "$arg" ] || [  "${arg:0:5}" = "/bin/"  ] ; then
			continue
		fi
		test -n "$arg" && mv "$arg" "$arg"".out"
	done
	# compare
	diff cmp out >/dev/null && echo -e -n " diff $OK " || echo -e -n " diff $NG "
	## exit status
	if [ "$actual" = "$expected" ]; then
		echo -e -n " status $OK "
	else
		echo -e -n " status $NG, expected $expected but got $actual"
	fi
	## redirect file
	if [ "$#" -gt 0 ] && [ -n "$(echo "$@" | tr -d ' ')" ]; then
		for arg in "$@"
		do
			if [ -n "$arg" ]; then
				# もしリダイレクトファイルが両方とも存在しなければ、何もせずスキップ
				if [ ! -f "$arg.cmp" ] && [ ! -f "$arg.out" ]; then
					continue
				fi
				echo -n "  [$arg]  "
				if [ -f "$arg.cmp" ] && [ -f "$arg.out" ]; then
					diff "$arg.cmp" "$arg.out" >/dev/null && echo -e -n "$OK" || echo -e -n "$NG"
				fi
				rm -f "$arg.cmp" "$arg.out"
			fi
		done
	fi
	echo
}
### echo -eはエスケープシーケンスを解釈できる -nは改行なし

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

# Redirect
## Redirect outfile
assert 'echo hell >hello.txt' 'hello.txt'
assert 'echo hello >f1>f2>f3' 'f1' 'f2' 'f3'

cleanup
echo 'all OK'