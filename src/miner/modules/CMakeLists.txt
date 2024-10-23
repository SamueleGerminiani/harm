
#Trace reader
SET(TR_SRC src/traceReader/interface/TraceReader.cc
	src/traceReader/vcdTraceReader/VCDtraceReader.cc
	src/traceReader/vcdTraceReader/VCDParser.cpp
	src/traceReader/vcdTraceReader/VCDScanner.cpp
	src/traceReader/vcdTraceReader/VCDFile.cpp
	src/traceReader/vcdTraceReader/VCDValue.cpp
	src/traceReader/vcdTraceReader/VCDFileParser.cpp
	src/traceReader/csvTraceReader/CSVtraceReader.cc
	)
add_library(traceReader ${TR_SRC} )
target_include_directories(traceReader PUBLIC 
	include/traceReader/interface/
	include/traceReader/vcdTraceReader/
	include/traceReader/csvTraceReader/
	../../csv-parser/include/
	)

target_link_libraries(traceReader csv varParser propositionParser miner_utils)

#Context miner
SET(CR_SRC src/contextMiner/interface/ContextMiner.cc
    src/contextMiner/manualDefinition/ManualDefinition.cc)
add_library(contextMiner ${CR_SRC} )
target_include_directories(contextMiner PUBLIC include/contextMiner/interface/ include/contextMiner/manualDefinition/ ../../rapidxml/include)

target_link_libraries(contextMiner temporalParser propositionParser miner_utils)


#TLMiner
SET(CR_SRC src/propertyMiner/interface/PropertyMiner.cc
    src/propertyMiner/TLMiner/TLMiner.cc
	src/propertyMiner/TLMiner/AntecedentGenerator.cc
	src/propertyMiner/TLMiner/supportMethods.cc
    )

add_library(propertyMiner ${CR_SRC} )
target_link_libraries(propertyMiner temporalParser miner_utils clustering)

target_include_directories(propertyMiner PUBLIC include/propertyMiner/interface/ include/propertyMiner/TLMiner/)

#Property Qualifier
SET(CR_SRC src/propertyQualification/interface/PropertyQualifier.cc src/propertyQualification/qualifier/Qualifier.cc)
add_library(propertyQualification ${CR_SRC} )
target_link_libraries(propertyQualification temporalParser fort traceReader miner_utils set_cover)

target_include_directories(propertyQualification PUBLIC include/propertyQualification/interface/
	include/propertyQualification/qualifier/)

target_link_libraries(propertyQualification miner)

#Modules
add_library(modules INTERFACE)
target_link_libraries(modules INTERFACE traceReader contextMiner propertyMiner propertyQualification)
