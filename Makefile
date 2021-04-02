CC=g++
CFLAGS=`wx-config --cxxflags`
LDFLAGS=`wx-config --libs`
EXEC=App #peut etre App.exe sur windows

all: $(EXEC)

App: main.o MyHistogram.o MyImage.o MyRotateDialog.o MyThresholdDialog.o #Changez le nom ici aussi
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: main.cpp MyThresholdDialog.hpp MyRotateDialog.hpp MyHistogram.hpp MyImage.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

MyHistogram.o: MyHistogram.cpp MyHistogram.hpp MyImage.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

MyImage.o: MyImage.cpp MyImage.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

MyThresholdDialog.o: MyThresholdDialog.cpp MyThresholdDialog.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

MyRotateDialog.o: MyRotateDialog.cpp MyRotateDialog.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o