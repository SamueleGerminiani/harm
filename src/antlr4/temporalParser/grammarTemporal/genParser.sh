java -jar $1 -lib ../../propositionParser/grammar/ temporal.g4 -Dlanguage=Cpp 
rm -rf include/*
rm -rf src/*
mv *.h include/
mv *.cpp src/
