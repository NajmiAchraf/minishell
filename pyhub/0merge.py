import os, sys
from datetime import datetime


def terminal(command):
	os.system(command)


def main(user):
	now = datetime.now()
	current_date = now.strftime("%Y-%m-%d %H:%M:%S")

	# terminal('@ECHO OFF')

	terminal(f'git checkout master')
	terminal(f'git pull origin master')
	terminal(f'git checkout {user}')
	terminal(f'git merge master')


if __name__ == '__main__':
	main(sys.argv[1])
