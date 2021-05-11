OBJECTS = synApp.o synFrame.o synSlider.o synARSD.o synInput.o synInputsManager.o synAllInputsManager.o
CPPFLAGS = -std=c++17 `wx-config --cxxflags --libs` 

out: $(OBJECTS)
	g++ $(OBJECTS) -o out ../Synthall/libsynthall.a -lasound -lsfml-window `wx-config --libs aui ``wx-config --cxxflags --libs`
	
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

