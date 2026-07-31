NAME=btc

CXX=c++
CPPFLAGS=-I.
CXXFLAGS=-Wall -Wextra -Werror -std=c++98 -pedantic-errors
SRCS=main.cpp CSVParser.cpp Date.cpp DBFile.cpp Error.cpp InputFile.cpp ParseDate.cpp ParseValue.cpp to_string.cpp
OBJS=$(SRCS:.cpp=.o)

all: $(NAME)

%.o : %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS) $(NAME)

re: fclean all

.PHONY: all clean fclean re
