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
	print("2) -> oaissoun")
	try:
		user = eval(input("> "))
	except Exception:
		user = -1
	if user == 1:
		user = 'anajmi'
	elif user == 2:
		user = 'oaissoun'
	else:
		print("you must choose only one of suggested choises")
		return

	print("To manage the git session choose :")
	print("0) -> to merge master in your branch")
	print("1) -> to commit & push in your branch, merge in master")
	print("2) -> to push in master")
	try:
		proccess = eval(input("> "))
	except Exception:
		proccess = -1
	if proccess == 0:
		terminal(f'python3 pyhub/0merge.py {user}')
	elif proccess == 1:
		terminal(f'python3 pyhub/1push_pull_merge.py {user}')
	elif proccess == 2:
		terminal(f'python3 pyhub/2push_master.py {user}')
	else:
		print("you must choose only one of suggested choises")

if __name__ == '__main__':
	main()
