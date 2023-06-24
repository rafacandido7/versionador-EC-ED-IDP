CC = gcc
LDFLAGS =
BLDDIR = .
INCDIR = $(BLDDIR)/inc
SRCDIR = $(BLDDIR)/src
OBJDIR = $(BLDDIR)/obj
REPDIR = $(BLDDIR)/.versionador
CFLAGS = -c -w -I$(INCDIR)
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
EXE = versionador

.PHONY: all clean

all: clean $(EXE) run

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJDIR)/*.o -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJDIR)/*.o $(EXE)
	-rm -rf $(REPDIR)

run:
	./$(EXE) iniciar
	# ./$(EXE) adiciona archive1.txt
	# ./$(EXE) registra commit
