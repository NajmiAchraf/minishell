import os
from datetime import datetime


def terminal(command):
	os.system(command)


def main():
	now = datetime.now()
	current_date = now.strftime("%Y-%m-%d %H:%M:%S")

	# terminal('@ECHO OFF')

	print("Choose user :")
	print("1) -> anajmi")
	print("2) -> oaisson")
	user = eval(input("> "))
	if user == 1:
		user = 'anajmi'
	elif user == 2:
		user = 'oaisson'

	print("To manage the git session choose :")
	print("0) -> to merge master in you branch")
	print("1) -> to push in you branch and merge it in master")
	print("2) -> to push in master")
	proccess = eval(input("> "))
	if proccess == 0:
		terminal(f'python3 pyhub/0merge.py {user}')
	elif proccess == 1:
		terminal(f'python3 pyhub/1push_pull_merge.py {user}')
	elif proccess == 2:
		terminal(f'python3 pyhub/2push_master.py {user}')

if __name__ == '__main__':
	main()
