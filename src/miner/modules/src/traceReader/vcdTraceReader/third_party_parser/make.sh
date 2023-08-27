FB_DIR=flex_bison_src
DEST_SRC_DIR=../
DEST_H_DIR=../../../../include/traceReader/vcdTraceReader/

LEX_SRC=$FB_DIR/VCDScanner.l
LEX_OUT=$DEST_SRC_DIR/VCDScanner.cpp
LEX_HEADER=$DEST_H_DIR/VCDScanner.hpp

YAC_SRC=$FB_DIR/VCDParser.ypp
YAC_OUT=$DEST_SRC_DIR/VCDParser.cpp
YAC_HEADER=$DEST_H_DIR/VCDParser.hpp


bison -v --defines=$YAC_HEADER $YAC_SRC -o $YAC_OUT
flex  -P VCDParser --header-file=$LEX_HEADER -o $LEX_OUT $LEX_SRC
mv ../location.hh ../../../../include/traceReader/vcdTraceReader/
