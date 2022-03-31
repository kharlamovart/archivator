all:
	gcc main.c -o archivator -fsanitize=address
