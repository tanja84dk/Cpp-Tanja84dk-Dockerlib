BUILD_FOLDER := build
CACHE_FOLDER := /home/buildclient/.cache/ccache
CPM_CACHE := /home/buildclient/.cache/CPM


CLEAN_LIST := build/ \
			  /home/buildclient/.cache/ccache/* \
			  /home/buildclient/.cache/CPM/*

# default rule
default: clean-build

clean-build:
	@echo Deleting ${BUILD_FOLDER}/
	@rm -r ${BUILD_FOLDER}/
.PHONY: clean-build

clean-cpm:
	@echo Deleting ${CPM_CACHE}/*
	@rm -r ${CPM_CACHE}/*
.PHONY: clean-cpm

clean-cache:
	@echo Deleting ${CACHE_FOLDER}/*
	@rm -r ${CACHE_FOLDER}/*
.PHONY: clean-cache

clean-all:
	make -j 3 clean-build clean-cpm clean-cache
.PHONY: clean-all
