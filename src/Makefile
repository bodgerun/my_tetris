include Make_variables.mk Make_patterns.mk 

all: install

tetris.a: clean $(GAME_OBJ_FILES)
	ar -rcs $(GAME_BLD_DIR)/$@ $(GAME_OBJ_FILES)

install: tetris.a $(INTF_OBJ_FILES)
	$(CC) $(CFLAGS) $(INTF_OBJ_FILES) -L. $(GAME_BLD_DIR)/tetris.a \
	  $(LINUX_FLAGS) -lncurses -o $(DST_DIR)/Tetris

uninstall: clean
	$(RM) $(DST_DIR)/*

reinstall: uninstall install

play:
	cd ../dst && ./Tetris

dist: reinstall
	gzip -k $(EXEC)

dvi:
	@echo $(GREEN)$(MSG_DVI)$(RESET)

diagram:
	$(OPEN_HTML) $(GAME_DGR_DIR)/FSM.html

test: clean tetris.a $(TEST_OBJ_FILES)
	$(CC) $(CFLAGS) $(TEST_OBJ_FILES) -L. $(GAME_BLD_DIR)/tetris.a \
    $(TEST_FLAGS) $(CHECK_FLAGS) $(LINUX_FLAGS) -o tests/$@ 
	tests/$@
	$(RM) record.txt

gcov_report: test
	lcov -t "test" -o tests/test.info -c -d .
	genhtml -o tests/report tests/test.info
	$(OPEN_HTML) tests/report/index.html

test_leaks: reinstall
	$(LEAKS)

test_valgrind: reinstall
	$(VALGRIND)

clang:
	cp ../materials/linters/.clang-format .
	$(LINTER) -i $(SRC_CODE_FILES)
	$(RM) .clang-format

test_style:
	cp ../materials/linters/.clang-format .
	$(LINTER) -n $(SRC_CODE_FILES)
	$(RM) .clang-format

test_cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(SRC_CODE_FILES)

clean:
	$(RM) \
	  $(GAME_BLD_DIR)/* \
	  $(GAME_OBJ_DIR)/* \
	  $(INTF_OBJ_DIR)/* \
	  $(TEST_OBJ_DIR)/* \
	  $(TEST_DIR)/test.info \
	  $(TEST_DIR)/test
	$(RM) -r $(TEST_DIR)/report

.PHONY: all \
        install \
        uninstall \
        reinstall \
				play \
        dist \
        dvi \
        diagram \
        test \
        gcov_report \
        test_leaks \
        test_valgrind \
        clang \
        test_style \
        test_cppcheck \
        clean
