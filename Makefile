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

clean:
	rm -f ./documentation/*.html
	rm -f ./documentation/*.json
	rm -f ./documentation/xml/*.xml

run:
	@echo "Generating documentation..."; \
	cldoc generate $(CXXFLAGS) -- $(COMMON_DOC_FLAGS)