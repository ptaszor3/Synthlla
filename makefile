OBJECTS = synApp.o synFrame.o synSlider.o synMIDIInput.o synARSD.o synSignalInput.o synEnvelopeInput.o synToneInput.o synEffectRepresentation.o synEffectContext.o synEffectInput.o synSignalInputsManager.o synEffectInputsManager.o
CPPFLAGS = -std=c++17 -fpermissive `wx-config --cxxflags --libs` 

out: $(OBJECTS) libsynthall.a
	g++ $(OBJECTS) -o out ../Synthall/libsynthall.a -lasound -lsfml-window `wx-config --libs aui ``wx-config --cxxflags --libs`

libsynthall.a:
	cd ../Synthall && $(MAKE)
	
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

