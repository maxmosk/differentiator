.PHONY: all clean debug release run

include CMakefile

#Compiler flags
CFLAGS=$(CFLAGS_WARNINGS) $(CFLAGS_SYNTAX)
CCLDFLAGS=$(CFLAGS_LINK)


SOURCEDIR=src/code
HEADERDIR=src/include
BUILDDIR=build
SOURCES=$(wildcard $(SOURCEDIR)/*.c)
HEADFILES=$(wildcard $(HEADERDIR)/*.h)
OBJFILES=$(patsubst $(SOURCEDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))
EXECUTABLE=$(BUILDDIR)/dtor


all: $(BUILDDIR) $(EXECUTABLE)


debug: CFLAGS+= $(CFLAGS_FLAGS) $(CFLAGS_DEBUG) -lasan
debug: all

release: CFLAGS+= -D NDEBUG -D NDEBUG_LOG
release: all


$(BUILDDIR):
	mkdir $(BUILDDIR)

$(EXECUTABLE): $(OBJFILES)
	$(CC) $(CCLDFLAGS) $(CFLAGS) -o $@ $(BUILDDIR)/*.o

$(OBJFILES): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.c $(HEADFILES)
	$(CC) -c $(CFLAGS) -I$(HEADERDIR) -o $@ $<

run: $(EXECUTABLE)
	@cd $(BUILDDIR); ./dtor
	@echo '\documentclass{article}' >>main.tex
	@echo '\usepackage[utf8]{inputenc}' >>main.tex
	@echo '\usepackage{amsmath}' >>main.tex
	@echo '\begin{document}' >>main.tex
	@cat build/texdump.tex >>main.tex
	@echo '\end{document}' >>main.tex
	@pdflatex main.tex &>/dev/null
	@atril main.pdf
	@yes | rm main.log main.aux main.pdf main.tex


clean:
	rm -rf $(BUILDDIR)
