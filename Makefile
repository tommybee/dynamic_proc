TARGET		= procdemo
MY_HOME     =.
ORACLE_HOME	=/C/DEV/COMP/OracleClient32
CC			= gcc
CXX			= g++
EXE			= demo
PROC		= proc
RM			= rm -rf
COPY		= cp
ECHO		= echo
C_LIBS		= -L$(ORACLE_HOME) -loci12  -lorasql12 
         
CPP_LIBS	= -L$(ORACLE_HOME) -loci12  -lorasql12 
             
PROCPPINC	= include=$(ORACLE_HOME)/precomp \
			include=$(ORACLE_HOME)/sdk/include \
			include=/mingw/i686-w64-mingw32/include
                 
PROCINC		=include=$(ORACLE_HOME)/precomp \
			include=$(ORACLE_HOME)/sdk/include \
			include=/mingw/i686-w64-mingw32/include
			
CFLAGS		= -D_DEBUG -D_REENTRANT  -c -g -r -w -O
CINCL		= -I. -I$(ORACLE_HOME)/sdk/include 
CXXFLAGS    = -pipe -Wall -W -O2 -DNO_DEBUG 
CXXINCL		= -I. -I$(ORACLE_HOME)/sdk/include 
OBJ_OPT		= -D_CRON -D_DEBUG
#ORA_OPT		= PARSE=PARTIAL RELEASE_CURSOR=YES MODE=ANSI CODE=CPP
ORA_OPT	= PARSE=NONE RELEASE_CURSOR=YES MODE=ANSI
OBJECTS		= $(TARGET).o
ORA_GARBAGE	= *.dcl *.cod *.cud *.lis

######## implicit rules
.SUFFIXES: .pc .c .cpp
.pc.c:
	@$(ECHO) "@$(PROC) iname=$< $(PROCINC) $(ORA_OPT)"
	@$(PROC) iname=$< $(PROCINC) $(ORA_OPT)
 
.c.o:
	@$(ECHO) "@$(CC)  $(CFLAGS) -c $< -o $@..c...compile"
	@$(CC)  $(CFLAGS) $(CINCL) -c $< -o $@
	
.pc.cpp:
	@$(ECHO) "@$(PROC) iname=$< $(PROCPPINC) $(ORA_OPT)"
	@$(PROC) iname=$< $(PROCPPINC) $(ORA_OPT)
	
.cpp.o:
	@$(ECHO) "@$(CXX)  $(CFLAGS) -c $(CXXINCL) $< -o $@...cpp..compile"
	@$(CXX)  $(CFLAGS) -c $(CXXINCL) $< -o $@
	
####### build rules
all:	$(TARGET)
$(TARGET):	$(OBJECTS)
	@$(ECHO) "@$(CXX) $(OBJ_OPT) -o $(EXE) $(OBJECTS) $(CPP_LIBS)  ....linking.."
	@$(CC) $(OBJ_OPT) -o $(EXE) $(OBJECTS) $(CPP_LIBS)
	
clean:
	@$(RM) $(EXE) $(OBJECTS) $(ORA_GARBAGE)