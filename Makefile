# compilation flags
CC = g++
CFLAGS = -c -std=c++17 -O2 -Wall

OBJDIR := bin
OBJS := $(addprefix $(OBJDIR)/,pmt.o kmp.o shift_or.o sellers.o ukkonen.o)

$(OBJDIR)/%.o : ./src/%.cpp
	$(CC) $(CFLAGS) $(OUTPUT_OPTION) $<

all: $(OBJDIR)/pmt

$(OBJDIR)/pmt: $(OBJS)
	$(CC) $(OBJS) $(OUTPUT_OPTION)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -r bin