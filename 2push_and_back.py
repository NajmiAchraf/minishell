import os
from datetime import datetime


def terminal(command):
	os.system(command)


def main():
	now = datetime.now()
	current_date = now.strftime("%Y-%m-%d %H:%M:%S")

	# terminal('@ECHO OFF')

	terminal(f'git add .')
	terminal(f'git commit -m "master branch -> {current_date}"')
	terminal(f'git push origin master')
	terminal(f'git checkout anajmi')


if __name__ == '__main__':
	main()
