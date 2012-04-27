DIR:=tests
SRCC_T:=$(shell find ./$(DIR)/ -name "*.c")
SRCCXX_T:=$(shell find ./$(DIR)/ -name "*.cpp")
HEADXX_T:=$(shell find ./$(DIR)/ -name "*.h")

OBJC_T:=$(subst .c,.o,$(addprefix $(BUILDDIR)/, $(subst ./$(DIR)/,,$(SRCC_T))))

OBJCXX_T:=$(subst .c,.o,$(addprefix $(BUILDDIR)/,$(subst ./$(DIR)/,,$(SRCCXX_T))))

OBJS_T:=$(OBJC_T) $(OBJCXX_T) 

$(OBJC_T): $(BUILDDIR)/%.o : $(DIR)/%.c
	$(CC) -o $@ -c $(CFLAGS) $<

$(OBJCXX_T): $(BUILDDIR)/%.opp : $(DIR)/%.cpp $(HEADXX_T)
	$(CXX) -o $@ -c $(CXXFLAGS) $<

TESTS:=\
 t1_queue\



TESTLIST:=$(addprefix $(BUILDDIR)/, $(TESTS))

tests: $(TESTLIST) 

# manually define each test build rules

$(BUILDDIR)/t1_queue: $(OBJS_T) $(addprefix $(BUILDDIR)/, Exception.opp)
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $(addprefix $(BUILDDIR)/, t1_queue.opp Exception.opp ) 

