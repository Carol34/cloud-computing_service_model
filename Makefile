all : 
	g++ -o servera serverA.cpp
	g++ -o serverb serverB.cpp
	g++ -o serverc serverC.cpp
	g++ -o awsd aws.cpp
	g++ -o client client.cpp
serverA:   
	./servera
serverB:  
	./serverb
serverC:    
	./serverc
aws :  
	./awsd 
