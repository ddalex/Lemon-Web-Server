SRCC:=$(shell find ./src/ -name "*.c")
SRCCXX:=$(shell find ./src/ -name "*.cpp")

OBJC:=$(subst .c,.o,$(addprefix $(BUILDDIR)/, $(subst ./src/,,$(SRCC))))

OBJCXX:=$(subst .c,.o,$(addprefix $(BUILDDIR)/,$(subst ./src/,,$(SRCCXX))))

OBJS:=$(OBJC) $(OBJCXX) 

$(OBJC): $(SRCC)
	$(CC) -o $@ -c $(CFLAGS) $<

$(OBJCXX): $(SRCCXX)
	echo $(OBJCXX)
	$(CXX) -o $@ -c $(CXXFLAGS) $<

$(BUILDDIR)/lemon: $(OBJS)
	$(LD) -o $@ $(LDFLAGS) $<	

