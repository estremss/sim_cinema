SRC_DIR = src
OBJ_DIR = obj

EXE = main
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp))
INC_FILES = $(wildcard include/*.hpp)
SAVE_DATA_FILES = $(SAVE_DATA_DIR)/liste_films.txt $(SAVE_DATA_DIR)/liste_seances.txt
SAVE_DATA_DIR = src/save_data

CXXFLAGS = -Wall -Iinclude -c

# Edition des liens
$(EXE): $(OBJ_FILES) $(SAVE_DATA_FILES)
	@echo "\nEdition des liens"
	g++ $(OBJ_FILES) -o $@
	@echo "\nTappez ./$@ pour exécuter le programme"

# Compilation des .cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_FILES) | $(OBJ_DIR)
	g++ $(CXXFLAGS) $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(SAVE_DATA_FILES): | $(SAVE_DATA_DIR)
	touch $(SAVE_DATA_FILES)

$(SAVE_DATA_DIR):
	mkdir -p $(SAVE_DATA_DIR)

run: $(EXE)
	./$<

clean:
	rm -f $(EXE)
	rm -rf $(OBJ_DIR)

.PHONY: clean