CC = gcc
CFLAGS = -Iinclude -Ilib -DPROJECT_ROOT=\"$(shell pwd)\"
SRCDIR = src
LIBDIR = lib
OBJDIR = obj
BINDIR = bin

SRCS = $(SRCDIR)/address_book_fops.c $(SRCDIR)/address_book_menu.c $(SRCDIR)/main.c
OBJS = $(OBJDIR)/address_book_fops.o $(OBJDIR)/address_book_menu.o $(OBJDIR)/main.o

all: $(BINDIR)/addressbook

$(BINDIR)/addressbook: $(OBJS)
	$(CC) $(OBJS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

debug1: $(OBJDIR)/address_book_fops.o $(OBJDIR)/address_book_menu.o $(OBJDIR)/unity.o $(OBJDIR)/test_address_book_Ish.o
	$(CC) $^ -o $(BINDIR)/test1

debug2: $(OBJDIR)/address_book_fops.o $(OBJDIR)/address_book_menu.o $(OBJDIR)/unity.o $(OBJDIR)/test_address_book_get_option_Chris.o
	$(CC) $^ -o $(BINDIR)/test2

debug3: $(OBJDIR)/address_book_fops.o $(OBJDIR)/address_book_menu.o $(OBJDIR)/unity.o $(OBJDIR)/test_address_book_list_contacts_Chris.o
	$(CC) $^ -o $(BINDIR)/test3

debug4: $(OBJDIR)/address_book_fops.o $(OBJDIR)/address_book_menu.o $(OBJDIR)/unity.o $(OBJDIR)/test_address_book_search_contact_Ricardo.o
	$(CC) $^ -o $(BINDIR)/test4

debug6: $(OBJDIR)/address_book_fops.o $(OBJDIR)/address_book_menu.o $(OBJDIR)/unity.o $(OBJDIR)/test_address_book_Viknesh.o
	$(CC) $^ -o $(BINDIR)/test6

$(OBJDIR)/unity.o: $(LIBDIR)/unity.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/*
