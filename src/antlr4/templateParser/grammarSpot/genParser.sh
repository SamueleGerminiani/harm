java -jar ~/antlr-4.12.0-complete.jar -lib ../../propositionParser/grammar/ spot.g4 -Dlanguage=Cpp 
rm -rf include/*
rm -rf src/*
mv *.h include/
mv *.cpp src/
