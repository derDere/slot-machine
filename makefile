SRC = $(wildcard *.cpp)
APP = "slot-machine"

All: $(APP)
	@echo Done

$(APP): $(SRC)
	g++ -o $(APP) $(SRC) -lncursesw -std=c++17

debug:
	g++ -g -o $(APP) $(SRC) -lncursesw -std=c++17
	gdb -ex run $(APP)

test: $(APP)
	./$(APP)

install: $(APP)
	cp $(APP) /usr/local/bin/$(APP)

uninstall:
	rm /usr/local/bin/$(APP)
