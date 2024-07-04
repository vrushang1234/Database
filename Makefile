CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRCDIR = .
BUILDDIR = build
TARGETDIR = bin

SERVER_SOURCES = $(SRCDIR)/server.cpp $(SRCDIR)/hashmap.cpp
CLIENT_SOURCES = $(SRCDIR)/client.cpp

SERVER_OBJECTS = $(SERVER_SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
CLIENT_OBJECTS = $(CLIENT_SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

SERVER_TARGET = $(TARGETDIR)/server
CLIENT_TARGET = $(TARGETDIR)/client

HEADERS = $(SRCDIR)/server.h $(SRCDIR)/client.h $(SRCDIR)/hashmap.h

$(shell mkdir -p $(BUILDDIR))
$(shell mkdir -p $(TARGETDIR))

all: $(SERVER_TARGET) $(CLIENT_TARGET)

$(SERVER_TARGET): $(SERVER_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(CLIENT_TARGET): $(CLIENT_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR) $(TARGETDIR)

.PHONY: all clean
