#!/bin/bash
if [ $# -eq 0 ]; then
	./pipex Makefile "cat -e" "cat -e" "cat -e" "cat -e" outfile
fi
if [ -n "$1" ]; then
	./pipex heredoc del "cat -e" "cat -e" "cat -e" outfile
fi
