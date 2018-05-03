.PHONY: compile run clean pack

all: compile
exe=blockeditor

doxygen: src/DoxyDoc.Doxyfile
	rm -rf doc
	mkdir -p doc
	cd src && doxygen ../src/DoxyDoc.Doxyfile

compile: src
	cd src && qmake ICPProj.pro -r -spec linux-g++-64 CONFIG+=debug CONFIG+=qml_debug CONFIG+=c++14
	$(MAKE) -C src -j$(nproc + nproc/2) && mv src/$(exe) .

run: src/$(exe)
	./$(exe)

clean:
	$(MAKE) -C src clean
	rm -f $(exe)
pack: Makefile src
	tar -cvzf xpetra19-xpitko00.tar.gz src/*.cpp src/*.h src/*.ui src/ICPProj.pro Makefile examples README.txt
