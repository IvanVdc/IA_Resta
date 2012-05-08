#
# Makefile for compiling Lledo's code for qualitative shape description
# Zoe Falomir Llansola
# November 2007
#
# Updated
# Jon Almazan Almazan
# January 2008
#
# Updated
# Zoe Falomir Llansola
# May 2008
#
# Updated with segment libraries
# Pablo Rodenas Barquero
# December 2008
#
# Updated with orientation libraries
# Zoe Falomir
# May 2009

LIB		= lib
LIBSEG		= lib/segment
OBJECTS 	= lib/objects

NAME		= RecFormas
SOURCE		= $(NAME)$(EXTENSION)
OBJECT		= $(OBJECTS)/$(NAME).o
BIN		= $(NAME)

COMPILER	= g++
EXTENSION	= .cpp

LIBRARIES	=  $(OBJECTS)/FiguresExtractor.o $(OBJECTS)/Point2D.o $(OBJECTS)/shapePt.o $(OBJECTS)/QPoint.o $(OBJECTS)/QualitativeDescriptor.o $(OBJECTS)/Matching.o $(OBJECTS)/utils.o $(OBJECTS)/segment-image.o $(OBJECTS)/segment-graph.o $(OBJECTS)/disjoint-set.o $(OBJECTS)/EdgeDetector.o $(OBJECTS)/Slope.o $(OBJECTS)/ComparedSize.o $(OBJECTS)/FixedOrientation.o $(OBJECTS)/RS.o $(OBJECTS)/RelativeOrientation.o $(OBJECTS)/ComparedDistance.o $(OBJECTS)/Figure.o $(OBJECTS)/Image.o $(OBJECTS)/Similarity.o


# Llibreries Vicent
#X11PATH		= /usr/X11R6
#X11FLAGS	= -I$(X11PATH)/include -L$(X11PATH)/lib -lX11
#LDFLAGS		=-lm -lpthread -Wl,-rpath $(X11PATH)/lib

X11FLAGS = -I/usr/include/X11 -L/usr/lib/X11 -lX11
LDFLAGS= -lm -lpthread -Wl,-rpath /usr/lib/X11
 
FLAGS		= #-O3
OPTIONS		= $(INCLUDES) $(FLAGS) -g #-Wall

TARGET		= $(BIN)

# Opciones segment
INCDIR 		= -I.
DBG    		= -g
OPT    		= -O3
CFLAGS 		= $(OPT) $(INCDIR)
#LINK   = -lm 

all: $(TARGET)

clean:
	rm -f $(BIN)
	rm -f $(OBJECT)
	rm -f $(OBJECTS)/*.o
	
clean-all: clean
	rm -f *~
	rm -f $(LIB)/*~
	rm -f $(LIBSEG)/*~
	rm -f *jpg
	rm -f *ppm

cleanObjects:
	rm $(OBJECT)
	rm $(OBJECTS)/*.o


$(BIN): $(OBJECT) $(LIBRARIES)
	$(COMPILER) $(OBJECT) -o $(NAME) $(LIBRARIES) $(LDFLAGS) $(X11FLAGS)



$(OBJECT): $(SOURCE)
	$(COMPILER) -c $(SOURCE) -o $(OBJECT) $(OPTIONS)



$(OBJECTS)/disjoint-set.o: $(LIBSEG)/disjoint-set.cpp
	$(COMPILER) -c $(LIBSEG)/disjoint-set.cpp -o $(OBJECTS)/disjoint-set.o $(CFLAGS)

$(OBJECTS)/segment-graph.o: $(LIBSEG)/segment-graph.cpp
	$(COMPILER) -c $(LIBSEG)/segment-graph.cpp -o $(OBJECTS)/segment-graph.o $(CFLAGS)

$(OBJECTS)/segment-image.o: $(LIBSEG)/segment-image.cpp
	$(COMPILER) -c $(LIBSEG)/segment-image.cpp -o $(OBJECTS)/segment-image.o $(CFLAGS)

$(OBJECTS)/EdgeDetector.o: $(LIB)/EdgeDetector.cpp 
	$(COMPILER) -c $(LIB)/EdgeDetector.cpp -o $(OBJECTS)/EdgeDetector.o $(OPTIONS)

$(OBJECTS)/Figure.o: $(LIB)/Figure.cpp 
	$(COMPILER) -c $(LIB)/Figure.cpp -o $(OBJECTS)/Figure.o $(OPTIONS)

$(OBJECTS)/FiguresExtractor.o: $(LIB)/FiguresExtractor.cpp 
	$(COMPILER) -c $(LIB)/FiguresExtractor.cpp -o $(OBJECTS)/FiguresExtractor.o $(OPTIONS)

$(OBJECTS)/Image.o: $(LIB)/Image.cpp 
	$(COMPILER) -c $(LIB)/Image.cpp -o $(OBJECTS)/Image.o $(OPTIONS)

$(OBJECTS)/Point2D.o: $(LIB)/Point2D.cpp 
	$(COMPILER) -c $(LIB)/Point2D.cpp -o $(OBJECTS)/Point2D.o $(OPTIONS)

$(OBJECTS)/shapePt.o: $(LIB)/shapePt.cpp 
	$(COMPILER) -c $(LIB)/shapePt.cpp -o $(OBJECTS)/shapePt.o $(OPTIONS)

$(OBJECTS)/QPoint.o: $(LIB)/QPoint.cpp 
	$(COMPILER) -c $(LIB)/QPoint.cpp -o $(OBJECTS)/QPoint.o $(OPTIONS)

$(OBJECTS)/QualitativeDescriptor.o: $(LIB)/QualitativeDescriptor.cpp
	$(COMPILER) -c $(LIB)/QualitativeDescriptor.cpp -o $(OBJECTS)/QualitativeDescriptor.o $(OPTIONS)

$(OBJECTS)/Matching.o: $(LIB)/Matching.cpp
	$(COMPILER) -c $(LIB)/Matching.cpp -o $(OBJECTS)/Matching.o $(OPTIONS)

$(OBJECTS)/utils.o: $(LIB)/utils.cpp
	$(COMPILER) -c $(LIB)/utils.cpp -o $(OBJECTS)/utils.o $(OPTIONS)

$(OBJECTS)/Slope.o: $(LIB)/Slope.cpp
	$(COMPILER) -c $(LIB)/Slope.cpp -o $(OBJECTS)/Slope.o $(OPTIONS)

$(OBJECTS)/ComparedSize.o: $(LIB)/ComparedSize.cpp
	$(COMPILER) -c $(LIB)/ComparedSize.cpp -o $(OBJECTS)/ComparedSize.o $(OPTIONS)

$(OBJECTS)/FixedOrientation.o: $(LIB)/FixedOrientation.cpp
	$(COMPILER) -c $(LIB)/FixedOrientation.cpp -o $(OBJECTS)/FixedOrientation.o $(OPTIONS)

$(OBJECTS)/RS.o: $(LIB)/RS.cpp
	$(COMPILER) -c $(LIB)/RS.cpp -o $(OBJECTS)/RS.o $(OPTIONS)

$(OBJECTS)/RelativeOrientation.o: $(LIB)/RelativeOrientation.cpp
	$(COMPILER) -c $(LIB)/RelativeOrientation.cpp -o $(OBJECTS)/RelativeOrientation.o $(OPTIONS)

$(OBJECTS)/ComparedDistance.o: $(LIB)/ComparedDistance.cpp
	$(COMPILER) -c $(LIB)/ComparedDistance.cpp -o $(OBJECTS)/ComparedDistance.o $(OPTIONS)

$(OBJECTS)/Similarity.o: $(LIB)/Similarity.cpp
	$(COMPILER) -c $(LIB)/Similarity.cpp -o $(OBJECTS)/Similarity.o $(OPTIONS)
