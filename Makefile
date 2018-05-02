.PHONY: compile run clean

all: compile

doxygen: src/DoxyDoc.Doxyfile
	rm -rf doc
	mkdir -p doc
	cd src && doxygen ../src/DoxyDoc.Doxyfile

compile: src
	cd src && qmake ICPProj.pro -r -spec linux-g++-64 CONFIG+=debug CONFIG+=qml_debug CONFIG+=c++14
	$(MAKE) -C src -j$(nproc + nproc/2)

run: src/ICPProj
	src/ICPProj

clean:
	$(MAKE) -C src clean
	rm -f src/ICPProj
