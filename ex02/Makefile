NAME=PmergeMe

CXX=c++
CPPFLAGS=-I.
CXXFLAGS=-Wall -Wextra -Werror -g -std=c++98 -pedantic-errors
SRCS=main.cpp FordJohnson.cpp IdxValue.cpp PairIndex.cpp
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
