import os
from datetime import datetime


def terminal(command):
	os.system(command)


def main():
	now = datetime.now()
	current_date = now.strftime("%Y-%m-%d %H:%M:%S")

	# terminal('@ECHO OFF')

	terminal(f'git checkout anajmi')
	terminal(f'git merge master')


if __name__ == '__main__':
	main()
