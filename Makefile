#Compilier options
CC=g++
CFLAGS=-Wall -lm
#Executable name (change it!)
PROG=nbody
#Directories configuration
#All the temporary files you don't care about will be dump here
BUILDDIR=./build
#The executable will be genreted there
BINDIR=./bin
#All the backups are saved in this one
SAVEDIR=./backup
#The directory that contains all your source files
SRCDIR=./src
#And finally the directory that will contain the documentation
DOCDIR=./doc
#Name of doxygen configuration file
DOXYFILE=Doxyfile

SRC := $(shell ls $(SRCDIR)/*.cpp)
DEPS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.d, $(SRC))
OBJ=$(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o, $(SRC))
RM=rm -Rfv

#Because of fun
fileIndex=1
nbFiles=0

.PHONY: all
all: compile

#Building required directories
$(BUILDDIR):
	@mkdir $@

$(BINDIR):
	@mkdir $@

$(SAVEDIR):
	@mkdir $@

#Main target, links the object files together and builds the executable
$(BINDIR)/$(PROG):$(BUILDDIR)/.stamp $(OBJ) | $(BINDIR)
	@tput setaf 5
	@echo Compiling...
	@tput setaf 7
	$(CC) $(CFLAGS) -o $@ $(OBJ)

#Getting the total amount of modified files
$(BUILDDIR)/.stamp: $(SRC) | $(BUILDDIR)
		$(foreach f, $?, $(eval nbFiles=$(shell echo $$(($(nbFiles)+1)))))
		@touch $(BUILDDIR)/.stamp

#Compiles the object files and creates the dependencies file
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	@echo "Resolving dependencies of $<"
	@$(CC) $(CFLAGS) -MF"$(BUILDDIR)/$*.d" -MG -MM -MT"$(BUILDDIR)/$*.d" -MT"$@" "$<"
	@echo Building [$(fileIndex)/$(nbFiles)] $<
	$(eval fileIndex=$(shell echo $$(($(fileIndex)+1))))
	@$(CC) $(CFLAGS) -c -o $@ $<

#Checks if we need to rebuild some *.o due to change in dependencies
-include $(BUILDDIR)/*.d

#Sometimes useful, most of the time useless but we still like it <3
.PHONY: compile
compile: $(BINDIR)/$(PROG)

#Runs the program, required the code to be compiled, displays an aproximated time of execution
.PHONY: run
run: $(BINDIR)/$(PROG)
	@tput setaf 1
	@echo Running $(BINDIR)/$(PROG)...
	@tput setaf 7
	$(eval beginTime=$(shell date +%s%N))
	@$(BINDIR)/$(PROG)
	$(eval endTime=$(shell date +%s%N))
	@tput setaf 6
	@echo
	@echo Terminated in $$(echo $(endTime) $(beginTime) | awk '{printf ($$1-$$2)/1000000000}')s with code $$?
	@tput setaf 7

#Generates doxygen configuration file with INPUT tag set to the source directory and
#OUTPUT_DIRECTORY tag set to the documentation directory (no kidding)
$(DOXYFILE):
	@doxygen -g $@
	@echo Setting the input directory to $(SRCDIR)
	@sed -i -r 's/^(INPUT\s*=).*$$/\1 $(subst /,\/, $(SRCDIR))/' $@
	@echo Setting the ouput directory to $(DOCDIR)
	@sed -i -r 's/^(OUTPUT_DIRECTORY\s*=).*$$/\1 $(subst /,\/, $(DOCDIR))/' $@

#Generates the actual documentation
.PHONY: doc
doc: $(DOXYFILE)
	doxygen $(DOXYFILE)

#Makes backup, sometimes a good idea...
.PHONY: save
save: | $(SAVEDIR)
	@cd $(SRCDIR)/..
	tar cvfz $(SAVEDIR)/$(PROG)-$(shell date +%d-%m-%Y_%H:%M:%S).tar.gz $(shell basename $(SRCDIR))

#Deletes stuff
.PHONY: clean
clean:
	$(RM) $(BUILDDIR)
	$(RM) $(DOCDIR)
	$(RM) $(BINDIR)

#Displays random information about this Makefile
.PHONY: info
info:
	@echo $(PROG)
	@echo ---------------
	@echo srcdir=$(SRCDIR)
	@echo src=$(SRC)
	@echo builddir=$(BUILDDIR)
	@echo bindir=$(BINDIR)
	@echo Compilier : $(CC)
	@echo Flags : $(CFLAGS)
	@echo docdir=$(DOCDIR)
	@echo doxyfile=$(DOXYFILE)
	@echo savedir=$(SAVEDIR)
