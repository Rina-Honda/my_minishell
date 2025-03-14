#!/bin/bash
RED="\033[31m"
GREEN="\033[32m"
RESET="\033[0m"
YELLOW="\033[33m"
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

print_desc()
{
	echo -e $YELLOW"$1"$RESET
}

cleanup()
{
	rm -f cmp out a.out print_args infinite_loop
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

## Redirect infile
assert 'cat <Makefile'
echo hello >f1
echo world >f2
echo 42Tokyo >f3
assert 'cat <f1<f2<f3'
rm -f f1 f2 f3
assert 'cat <hoge'

## Appending Redirect outfile
assert 'pwd >>pwd.txt' 'pwd.txt'
assert 'pwd >>pwd.txt \n pwd >>pwd.txt' 'pwd.txt'

## Here Document infile
assert 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF<<eof\nhello\nworld\nEOF\neof\nNOPRINT'
assert 'cat <<EOF\nhello\nworld'
assert 'cat <<E"O"F\nhello\nworld\nEOF\nNOPRINT'

## Pipe
assert 'cat Makefile | grep minishell'
assert 'cat | cat | ls\n\n'

## Expand Variable
assert 'echo $USER'
#assert 'echo $USER$PATH$TERM'
assert 'echo "$USER $PATH   $TERM"'

## Special Parameter $?
assert 'echo $?'
assert 'invalid\necho $?\necho $?'
assert 'exit42\necho $?\necho $?'
assert 'exit42\n\necho $?\necho $?'

# Signal handling
echo "int main() { while (1) ; }" | gcc -xc -o infinite_loop -

## Signal to shell process
print_desc "SIGTERM to SHELL"
(sleep 0.01; pkill -SIGTERM bash;
 sleep 0.01; pkill -SIGTERM minishell) &
assert './infinite_loop' 2>/dev/null

print_desc "SIGQUIT to SHELL"
(sleep 0.01; pkill -SIGQUIT bash;
 sleep 0.01; pkill -SIGTERM bash;
 sleep 0.01; pkill -SIGQUIT minishell;
 sleep 0.01; pkill -SIGTERM minishell) &
assert './infinite_loop' 2>/dev/null

print_desc "SIGINT to SHELL"
(sleep 0.01; pkill -SIGINT bash;
 sleep 0.01; pkill -SIGTERM bash;
 sleep 0.01; pkill -SIGINT minishell;
 sleep 0.01; pkill -SIGTERM minishell) &
assert './infinite_loop' 2>/dev/null

## Signal to child process
print_desc "SIGTERM to child process"
(sleep 0.01; pkill -SIGTERM infinite_loop;
 sleep 0.01; pkill -SIGTERM infinite_loop) &
assert './infinite_loop'

print_desc "SIGINT to child process"
(sleep 0.01; pkill -SIGINT infinite_loop;
 sleep 0.01; pkill -SIGINT infinite_loop) &
assert './infinite_loop'

print_desc "SIGQUIT to child process"
(sleep 0.01; pkill -SIGQUIT infinite_loop;
 sleep 0.01; pkill -SIGQUIT infinite_loop) &
assert './infinite_loop'

print_desc "SIGUSR1 to child process"
(sleep 0.01; pkill -SIGUSR1 infinite_loop;
 sleep 0.01; pkill -SIGUSR1 infinite_loop) &
assert './infinite_loop'

# Builtin
## exit
assert 'exit'
assert 'exit 42'
assert 'exit ""'
assert 'exit hello'
assert 'exit 42Tokyo'
assert 'exit 1 2'

cleanup