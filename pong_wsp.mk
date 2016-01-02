.PHONY: clean All

All:
	@echo ----------Building project:[ Pong - Debug ]----------
	@"$(MAKE)" -f "Pong.mk"
clean:
	@echo ----------Cleaning project:[ Pong - Debug ]----------
	@"$(MAKE)" -f "Pong.mk" clean
