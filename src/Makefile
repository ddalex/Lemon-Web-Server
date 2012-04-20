DIR:=src
SRCC:=$(shell find ./$(DIR)/ -name "*.c")
SRCCXX:=$(shell find ./$(DIR)/ -name "*.cpp")
HEADXX:=$(shell find ./$(DIR)/ -name "*.h")

OBJC:=$(subst .c,.o,$(addprefix $(BUILDDIR)/, $(subst ./$(DIR)/,,$(SRCC))))

OBJCXX:=$(subst .c,.o,$(addprefix $(BUILDDIR)/,$(subst ./$(DIR)/,,$(SRCCXX))))

OBJS:=$(OBJC) $(OBJCXX) 

$(OBJC): $(BUILDDIR)/%.o : $(DIR)/%.c
	$(CC) -o $@ -c $(CFLAGS) $<

$(OBJCXX): $(BUILDDIR)/%.opp : $(DIR)/%.cpp $(HEADXX)
	$(CXX) -o $@ -c $(CXXFLAGS) $<

$(BUILDDIR)/lemon: $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $(OBJS)	

