$(GAME_OBJ_DIR)/%.o: $(GAME_MOD_DIR)/%.c $(GAME_HDR_DIR)/*.h
	$(CC) $(CFLAGS) -c $< $(TEST_FLAGS) $(LINUX_FLAGS) -o $@

$(INTF_OBJ_DIR)/%.o: $(INTF_MOD_DIR)/%.c $(INTF_HDR_DIR)/*.h
	$(CC) $(CFLAGS) -c $< $(LINUX_FLAGS) -o $@ 

$(TEST_OBJ_DIR)/%.o: $(TEST_MOD_DIR)/%.c $(TEST_MOD_DIR)/test.h
	$(CC) $(CFLAGS) -c $< $(LINUX_FLAGS) -o $@
