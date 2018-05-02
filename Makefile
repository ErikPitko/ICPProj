.PHONY: compile run clean

all: compile
exe=ICPProj

doxygen: src/DoxyDoc.Doxyfile
	rm -rf doc
	mkdir -p doc
	cd src && doxygen ../src/DoxyDoc.Doxyfile

compile: src
	cd src && qmake ICPProj.pro -r -spec linux-g++-64 CONFIG+=debug CONFIG+=qml_debug CONFIG+=c++14
	$(MAKE) -C src -j$(nproc + nproc/2) && cp src/$(exe) .

run: src/ICPProj
	./$(exe)

clean:
	$(MAKE) -C src clean
	rm -f $(exe)
