CXX=clang++
CXXFLAGS=-std=c++20 -I. -W -Wall
LDFLAGS=-lSDL2

NAME=jc-808

OBJ =	amp_env.o	\
	audio_engine.o	\
	clap.o		\
	closed_hat.o	\
	envelope.o	\
	filter.o	\
	instrument.o	\
	kick.o		\
	main.o		\
	pitch_env.o	\
	sequencer.o	\
	snare.o		\
	timer.o

$(NAME): $(OBJ)
	$(CXX) $(LDFLAGS) -o $(NAME) $(OBJ)

all: $(NAME)

%.o: %.c
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	rm -f *.o
	rm -f $(NAME)

re: clean all
