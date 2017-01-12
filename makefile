CXX = clang++
SDL = -I /Library/Frameworks/SDL2.framework/Headers -I OpenGL -framework SDL2  -F /Library/Frameworks -framework OpenGL
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CXXFLAGS = -Wall -c -std=c++11 -F/Library/Frameworks
LDFLAGS = $(SDL)
EXE = Run_This

all: $(EXE)

$(EXE): main.o camera.o Ray.o Sphere.o Vec_3t.o Display.o Material.o
	$(CXX) $(LDFLAGS) main.o camera.o Ray.o Sphere.o Vec_3t.o Display.o Material.o -o $@

main.o: main.cc
	$(CXX) $(CXXFLAGS) $< -o $@

camera.o: camera.cc
	$(CXX) $(CXXFLAGS) $< -o $@

Ray.o: Ray.cc
	$(CXX) $(CXXFLAGS) $< -o $@

Sphere.o: Sphere.cc
	$(CXX) $(CXXFLAGS) $< -o $@

Vec_3t.o: Vec_3t.cc
	$(CXX) $(CXXFLAGS) $< -o $@

Display.o: display.cc
	$(CXX) $(CXXFLAGS) $< -o $@

Material.o: material.cc
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o && rm $(EXE)
