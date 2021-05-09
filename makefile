OBJECTS = synApp.o synFrame.o synSlider.o synARSD.o synSignalInput.o
CPPFLAGS = `wx-config --cxxflags --libs`

out: $(OBJECTS)
	g++ $(OBJECTS) -o out ../Synthall/libsynthall.a -lasound -lsfml-window `wx-config --cxxflags --libs`
	
clean:
	rm *.o
	rm out
	
cc:
	clear
	make out

git: out
	make clean
	git add .
	git commit
	git push
