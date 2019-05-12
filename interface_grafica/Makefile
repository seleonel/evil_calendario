# gcc usado pela simplicidade
COMP = gcc
OBJETOS = main.c
EXECUTAVEL = calendariobin
# c11 caso o compilador default utilize c89
# util para as declarações dentro dos for loops
FLAGS_COMP = -w -std=c11
FLAGS_LINKER = -lm -lim -lcd -liup
all : $(OBJETOS)
	$(COMP) $(OBJETOS) $(FLAGS_COMP) -o $(EXECUTAVEL) $(FLAGS_LINKER)

