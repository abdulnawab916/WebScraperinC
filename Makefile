# Change 'gcc' to 'clang' or another compiler if you prefer
CC     = gcc
CFLAGS = -Wall -Wextra -pedantic

# The name of your output program
TARGET = scrape

# The name(s) of your source file(s)
SOURCES = scraper.c 

# If you installed libcurl via Homebrew and need custom include or library paths,
# uncomment and update these lines (Intel vs. Apple Silicon):
# CFLAGS  += -I/usr/local/opt/curl/include   # Intel macOS
# LDFLAGS += -L/usr/local/opt/curl/lib       # Intel macOS
# CFLAGS  += -I/opt/homebrew/opt/curl/include   # Apple Silicon
# LDFLAGS += -L/opt/homebrew/opt/curl/lib       # Apple Silicon

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -lcurl

clean:
	rm -f $(TARGET) *.o

