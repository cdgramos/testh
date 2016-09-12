# This makefile is used to generate the TestH API documentation.
# The documentation currently in use is cldoc.
# Quick guide about code documentation in cldoc here: http://jessevdk.github.io/cldoc/documenting.html
# The documentation is generated using only the header files.
# Options:
# make clean -> remove the documentation files
# make run -> generates the documentation

HEADERS = $(wildcard ./include/*.h)
OUTPUTDIR = ./documentation

OBJECTS = ${SOURCES:.c=.o}
CXXFLAGS = 

COMMON_DOC_FLAGS = --report --merge docs --output $(OUTPUTDIR) $(HEADERS)

make:
	@echo "\nThis makefile is used to generate the TestH API documentation using the CLDOC documentation generator";
	@echo "Use the following options:";
	@echo "make clean -> to remove the generated documentation files";
	@echo "make run -> to generate the API documentation";
	@echo "\nTake a look at http://jessevdk.github.io/cldoc/documenting.html for more information on CLDOC\n";


clean:
	rm -f ./documentation/*.html
	rm -f ./documentation/*.json
	rm -f ./documentation/xml/*.xml


run:
	@echo "Generating documentation..."; \
	cldoc generate $(CXXFLAGS) -- $(COMMON_DOC_FLAGS)
