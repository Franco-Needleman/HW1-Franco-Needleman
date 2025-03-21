make:
	g++ ej1.cpp -Wall -o main
	valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./main 
	rm main