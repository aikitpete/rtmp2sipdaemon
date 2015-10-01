NAME=artmp
VERSION = 1
PATCHLEVEL = 1
SUBLEVEL = 1
EXTRAVERSION ?= 

REL_VERSION=$(VERSION).$(PATCHLEVEL).$(SUBLEVEL)
RELEASE=$(REL_VERSION)$(EXTRAVERSION)

SRCS=$(filter-out $(NAME).cpp, $(wildcard *.cpp)) $(wildcard ../Socket/*.cpp)
HDRS=$(SRCS:.cpp=.h)
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d) $(NAME).d
AUDIO_FILES=$(notdir $(wildcard wav/*.wav))
CXX = g++
CC = gcc
LD = $(CC)
OBJPTH = obj/
CXXFLAGS += -Wall -Wno-reorder -fPIC -g -O2 $(EXTRA_CXXFLAGS)
CFLAGS += -Wall -fPIC -g -O2 $(EXTRA_CFLAGS)

.PHONY: all
all: 
	  $(MAKE) $(NAME)


.PHONY: clean
clean:
	rm -f $(OBJS) $(DEPS) $(NAME) $(NAME).o
	rm -f lib/*.so
	$(MAKE) -C $(PLUGIN_DIR) clean

.PHONY: deps
deps: $(DEPS)

.PHONY: doc
doc:
	rm -Rf doxygen_output; doxygen doxygen_proj ; \
	rm -rf ../doc/doxygen_doc ; mv doxygen_output ../doc/doxygen_doc

.PHONY: fulldoc
fulldoc:
	rm -Rf doxygen_output; doxygen doxygen_fulldoc ; \
	rm -rf ../doc/doxygen_fulldoc ; mv doxygen_output ../doc/doxygen_fulldoc


LDFLAGS += -lstdc++ 

ifdef USE_LIBSAMPLERATE
LDFLAGS +=-lsamplerate
endif

ifdef WITH_ZRTP
LDFLAGS +=-lzrtp -lbn
endif

# implicit rules
%.o : %.cpp %.d
	$(CXX) -c -o $@  $< $(CPPFLAGS) $(CXXFLAGS)

$(NAME): $(NAME).o $(OBJS)
	$(LD) -o $(NAME) $(NAME).o $(OBJS) $(LDFLAGS)


dist: tar

tar: 
	$(TAR) -C .. \
		--exclude=$(notdir $(CURDIR))/ivr \
		--exclude=$(notdir $(CURDIR))/tmp \
		--exclude=.svn* \
		--exclude=.\#* \
		--exclude=*.[do] \
		--exclude=*.la \
		--exclude=*.lo \
		--exclude=*.so \
		--exclude=*.il \
		--exclude=$(notdir $(CURDIR))/sems \
		--exclude=$(notdir $(CURDIR))/build-stamp \
		--exclude=$(notdir $(CURDIR))/configure-stamp \
		--exclude=$(notdir $(CURDIR))/debian/sems-core \
		--exclude=*.gz \
		--exclude=*.bz2 \
		--exclude=*.tar \
		--exclude=*~ \
		-cf - $(notdir $(CURDIR)) | \
			(mkdir -p tmp/_tar1; mkdir -p tmp/_tar2 ; \
			    cd tmp/_tar1; $(TAR) -xf - ) && \
			    mv tmp/_tar1/$(notdir $(CURDIR)) \
			       tmp/_tar2/"$(NAME)-$(RELEASE)" && \
			    (cd tmp/_tar2 && $(TAR) \
			                    -zcf ../../"$(NAME)-$(notdir $(CURDIR))-$(RELEASE)".tar.gz \
			                               "$(NAME)-$(RELEASE)" ) ; \
			    rm -rf tmp/_tar1; rm -rf tmp/_tar2


