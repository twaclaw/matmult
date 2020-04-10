IP := matmult
VERSION := 1.0

all: solution1 
	@echo "IP built successfully."

solution1:
	vivado_hls -f script_solution1.tcl
	cp -rf $(IP)/solution1/impl/ip/*.zip ../../
	cd ../../ && rm -rf $(IP)_$(VERSION) && \
	unzip *.zip -d $(IP)_$(VERSION) && rm *.zip

solution2:
	vivado_hls -f script_solution2.tcl
	cp -rf $(IP)/solution2/impl/ip/*.zip ../../
	cd ../../ && rm -rf $(IP)_$(VERSION) && \
	unzip *.zip -d $(IP)_$(VERSION) && rm *.zip

clean:
	rm -rf $(IP) *.log

