// Preston Stepic
#include <map>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <bitset>
#include <string>
#include <stdio.h>
#include <ctype.h>

using namespace std;

// function to remove all white space and comments
string removeSpaceComments(string s){
	
	// variable to hold the value of the string to be returned
	string outputString = "";
	
	// count that will contain the current index of the string
	int count = 0;
	
	// while loop to run until the end of the string is reached
	// or a / is reached indicating the start of a comment 
	while((count != s.length()) && (s[count] != '/')){
		
		// if the current character is not a space, tab, nor a return
		// add it to the output string 
		if((s[count] != ' ') && (s[count] != 9) && (s[count] != 13)){
			outputString = outputString + s[count];
		}
		
		// increase the index of the string once
		count++;
		
	}
	
	// return the output string
	return outputString;
}

// function to translate c instruction
vector<string> translateC(string instruction){
	// variables to find location of = and ;
	int locationEqual;
	int locationSemiColon;
	
	// variables to hold each element of the instruction
	string funcDest;
	string funcComp;
	string funcJump;
	
	// vector to be outputted
	vector<string> outputVector;
	
	// if the instruction has both a ; and =
	if((instruction.find(';') != std::string::npos) && (instruction.find('=') != std::string::npos)){
		
		// find location of =
		locationEqual = instruction.find('=');
		
		// find location of ;
		locationSemiColon = instruction.find(';');
		
		// assign each part of instruction to the correct part of the string
		funcDest = instruction.substr(0,locationEqual);
		funcComp = instruction.substr(locationEqual+1,locationSemiColon - (locationEqual+1));
		funcJump = instruction.substr(locationSemiColon + 1, 3);
	}
	
	// if the instruction just has an =
	else if((instruction.find(';') == std::string::npos) && (instruction.find('=') != std::string::npos )){
		
		// find the = sign
		locationEqual = instruction.find('=');
		
		// assign dest and comp to the proper substrings
		funcDest = instruction.substr(0, locationEqual);
		funcComp = instruction.substr(locationEqual+1, instruction.length() - (locationEqual + 1));
		
		// jump will be null bc it isn't there
		funcJump = "null";
	}
	
	// if there is only a semicolon
	else if((instruction.find(';') != std::string::npos) && (instruction.find('=') == std::string::npos)){
		
		// find the semicolon
		locationSemiColon = instruction.find(';');
		
		// assign jump and comp to the proper substrings
		funcComp = instruction.substr(0, locationSemiColon);
		funcJump = instruction.substr(locationSemiColon+1, 3);
		
		// dest will be null
		funcDest = "null";
	}
	
	// add each component to the output vector and return
	outputVector.push_back(funcComp);
	outputVector.push_back(funcDest);
	outputVector.push_back(funcJump);
	
	return outputVector;
}


// function to convert to binary given a string
string convertToBinaryS(string numString){
	
	// convert string to number
	int num = stoi(numString);
	
	// get binary value of num
	bitset<16> binaryVal(num);
	
	// convert and return binary to string
	return binaryVal.to_string();
}

// function to convert to binary given an integer
string convertToBinaryI(int num){
	
	// convert int to binary
	bitset<16> binaryVal(num);
	
	// convert and return binary to string
	return binaryVal.to_string();
}


// function to determine if a word is in a vector
bool isContained(vector<string>	vec, string word){
	bool returnBool;
	
	// loop through entire vector
	for(int i = 0; i < vec.size(); i++){
		
		// if word found return true
		if(vec.at(i) == word){
			return true;
		}
		
		// else set returnBool to false
		else{
			returnBool = false;
		}
	}
	
	// return returnBool
	return returnBool;
}
		
		
		


// main function that will assemble asm inctructions
// into hack code
// will take in a file name from the command line
int main(int argc, char** argv) {
	
	// map to hold all the C-instruction comp instructions
	// and their cooresponding hack binary values
	map<string, string> comp;
	
	// add each C-instruction to the map with cooresponding binary value
	comp.insert(pair<string, string> ("0", "0101010"));
	comp.insert(pair<string, string> ("1", "0111111"));
	comp.insert(pair<string, string> ("-1", "0111010"));
	comp.insert(pair<string, string> ("D", "0001100"));
	comp.insert(pair<string, string> ("A", "0110000"));
	comp.insert(pair<string, string> ("!D", "0001101"));
	comp.insert(pair<string, string> ("!A", "0110001"));
	comp.insert(pair<string, string> ("-D", "0001111"));
	comp.insert(pair<string, string> ("-A", "0110011"));
	comp.insert(pair<string, string> ("D+1", "0011111"));
	comp.insert(pair<string, string> ("A+1", "0110111"));
	comp.insert(pair<string, string> ("D-1", "0001110"));
	comp.insert(pair<string, string> ("A-1", "0110010"));
	comp.insert(pair<string, string> ("D+A", "0000010"));
	comp.insert(pair<string, string> ("D-A", "0010011"));
	comp.insert(pair<string, string> ("A-D", "0000111"));
	comp.insert(pair<string, string> ("D&A", "0000000"));
	comp.insert(pair<string, string> ("D|A", "0010101"));
	comp.insert(pair<string, string> ("M", "1110000"));
	comp.insert(pair<string, string> ("!M", "1110001"));
	comp.insert(pair<string, string> ("-M", "1110011"));
	comp.insert(pair<string, string> ("M+1", "1110111"));
	comp.insert(pair<string, string> ("M-1", "1110010"));
	comp.insert(pair<string, string> ("D+M", "1000010"));
	comp.insert(pair<string, string> ("D-M", "1010011"));
	comp.insert(pair<string, string> ("M-D", "1000111"));
	comp.insert(pair<string, string> ("D&M", "1000000"));
	comp.insert(pair<string, string> ("D|M", "1010101"));
	
	// map to hold all the C-instruction jump instructions
	// and their cooresponding hack binary values
	map<string, string> jump;
	
	// add each jump instruction to the map with cooresponding binary value
	jump.insert(pair<string, string> ("null", "000"));
	jump.insert(pair<string, string> ("JGT", "001"));
	jump.insert(pair<string, string> ("JEQ", "010"));
	jump.insert(pair<string, string> ("JGE", "011"));
	jump.insert(pair<string, string> ("JLT", "100"));
	jump.insert(pair<string, string> ("JNE", "101"));
	jump.insert(pair<string, string> ("JLE", "110"));
	jump.insert(pair<string, string> ("JMP", "111"));
	
	// map to hold all the C-instruction dest instructions
	// and their cooresponding hack binary values
	map<string, string> dest;
	
	// add each dest instruction to the map with cooresponding binary value
	dest.insert(pair<string, string> ("null", "000"));
	dest.insert(pair<string, string> ("M", "001"));
	dest.insert(pair<string, string> ("D", "010"));
	dest.insert(pair<string, string> ("MD", "011"));
	dest.insert(pair<string, string> ("A", "100"));
	dest.insert(pair<string, string> ("AM", "101"));
	dest.insert(pair<string, string> ("AD", "110"));
	dest.insert(pair<string, string> ("AMD", "111"));
	
	// map to hold all variables
	map<string, int> variables;
	
	// initialize map with known memory locations of KBD and SCREEN
	variables.insert(pair<string, int> ("SCREEN", 16384));
	variables.insert(pair<string, int> ("KBD", 24576));
	variables.insert(pair<string, int> ("SP", 0));
	variables.insert(pair<string, int> ("LCL", 1));
	variables.insert(pair<string, int> ("ARG", 2));
	variables.insert(pair<string, int> ("THIS", 3));
	variables.insert(pair<string, int> ("THAT", 4));
	
	// vector representing the dedicated registers
	vector<string> registers;
	registers.push_back("@R0");
	registers.push_back("@R1");
	registers.push_back("@R2");
	registers.push_back("@R3");
	registers.push_back("@R4");
	registers.push_back("@R5");
	registers.push_back("@R6");
	registers.push_back("@R7");
	registers.push_back("@R8");
	registers.push_back("@R9");
	registers.push_back("@R10");
	registers.push_back("@R11");
	registers.push_back("@R12");
	registers.push_back("@R13");
	registers.push_back("@R14");
	registers.push_back("@R15");
	
	// string to hold the name of the file
	string fileIn = "";
	
	// the file name should be the second value in argv
	if(argc == 2){
		fileIn = argv[1];
	}
	
	// give an error if input file is not found
	else{
		cout<<"Error: No input file on command line";
		return -1;
	}
	
	
	// open the input file
	ifstream asmFile;
	asmFile.open(fileIn);
	
	// make sure the file was opened
	// if it wasn't give an error
	if(asmFile.is_open() == false){
		cout<<"File could not be opened";
		return -1;
	}
	
	
	//string to hold one line of the input file
	string tempLine;
	
	// vector to hold all stripped instructions from the input file
	vector<string> instructions;
	
	// instructions will store all the assembly instructions
	// with no whitespace nor comments
	
	// variable to hold a temporary stripped string from the input file
	string tempString;
	
	// while loop to run until the end of the file is reached
	// getline will return a line from the file and store it in tempLine
	while(getline(asmFile, tempLine)){
		
		// if the line does not start with / (a comment line) "\n" a blank line
		// or a tab (ASCII = 13)
		if((tempLine[0] != '/') && (tempLine != "\n") && (tempLine[0] != 13)){
			
			// tempString equals the stripped line from the file
			tempString = removeSpaceComments(tempLine);
			
			// if the string length is not 0
			// add it to the instructions vector
			// if the length is 0 then the line was blank and should not be included
			if(tempString.length() != 0){
				instructions.push_back(tempString);
			}
		}
		
	}
	
	// close the input file
	asmFile.close();
	
	
	/*for(int i = 0; i < instructions.size(); i++){
		cout<<instructions.at(i)<<endl;
	}*/
	
	// first pass through instructions
	// assign label variables to addresses corresponding to the line they appear
	string firstPassString;
	string labelName;
	
	// variable to recognize when the first label was found
	int firstLabel = 0;
	
	// count to keep track of label's memory address
	int count = 0;
	
	// loop through all instructions
	for(int i = 0; i < instructions.size(); i++){
		
		// assign a temporary string variable to the current instruction
		firstPassString = instructions.at(i);
		
		// if the instruction starts with ( then assign it a new mem location
		// cooresponding to it's line
		if((firstPassString[0] == '(') && (firstLabel == 0)){
			// label name is the substring between ()
			labelName = firstPassString.substr(1, firstPassString.length() - 2);
			
			// insert the label name and memory location into the variables map
			variables.insert(pair<string, int> (labelName, i));
			
			// first label was found
			firstLabel = 1;
			
			// increment count
			count++;
		}
		
		// find the rest of the labels
		else if(firstPassString[0] == '('){
			labelName = firstPassString.substr(1, firstPassString.length() - 2);
			// location is i-count because the labels don't coount as lines
			variables.insert(pair<string, int> (labelName, i-count));
			count++;
		}
	}
	
	// nextLocation represents the next available memory address for a variable
	int nextLocation = 16;
	
	// variables to keep track of symbol names
	string secondPassString;
	string symbolName;
	for(int i = 0; i < instructions.size(); i++){
		secondPassString = instructions.at(i);
		
		// if the string has a letter after @ and is not already defined in the map and doesn't represent a register and isn't a label symbol
		if((isalpha(secondPassString[1])) && (variables.count(secondPassString.substr(1, secondPassString.length() -1)) == 0) && (isContained(registers, secondPassString) == false)  && (secondPassString[0] == '@')){
			// symbol name is the substring after @
			symbolName = secondPassString.substr(1, secondPassString.length() - 1);
			
			// insert the new symbol into the map
			variables.insert(pair<string, int> (symbolName, nextLocation));
			
			// increase the next available mem location by 1
			nextLocation++;
		}
	}
	
	// variable to represent the current instruction
	string tempInstruction;
	
	// vector representing the components of a c instruction
	vector<string> CInstruction;
	
	// vector representing the final hack instructions
	vector<string> hackInstructions;
	
	// variables to represent each component of the instruction
	string compInstr;
	string destInstr;
	string jumpInstr;
	
	// variables used for naming and binary values
	string varInstr;
	string varName;
	int varValue;
	string binaryExp;
	// interpret each instruction in instructions
	for(int i = 0; i < instructions.size(); i++){
		// assign tempInstruction to the current instruction
		tempInstruction = instructions.at(i);
		
		// reset the CInstruction vector
		CInstruction.clear();
		
		// if a c instruction no @ nor (
		if((tempInstruction[0] != '@') && (tempInstruction[0] != '(')){
			
			// translate the C-instruction and store it in CInstruction
			CInstruction = translateC(tempInstruction);
			
			// breakup the instruction into respectful parts
			compInstr = CInstruction.at(0);
			destInstr = CInstruction.at(1);
			jumpInstr = CInstruction.at(2);
			
			// create the proper c-instruction string
			binaryExp = "111" + (comp.find(compInstr)->second) + (dest.find(destInstr)->second) + (jump.find(jumpInstr)->second);
			
			// add the instruction to the final hack vector
			hackInstructions.push_back(binaryExp);
			
		}
		// if a register value
		else if(isContained(registers, tempInstruction)){
			// the location of the register is after @R
			varInstr = tempInstruction.substr(2, tempInstruction.length() - 2);
			
			// convert to binary
			binaryExp = convertToBinaryS(varInstr);
			
			// add to hack instructions
			hackInstructions.push_back(binaryExp);
		}
		
		// if a user-defined symbol
		else if((tempInstruction[0] != '(') && (variables.count(tempInstruction.substr(1, tempInstruction.length() -1))) > 0){
			// symbol name comes after @
			varName = tempInstruction.substr(1, tempInstruction.length() -1);
			
			// get the memory location from the variables map
			varValue = variables.find(varName)->second;
			
			// convert to binary
			binaryExp = convertToBinaryI(varValue);
			
			// add to hack instructions
			hackInstructions.push_back(binaryExp);
			
		}
		
		// if a memory address
		else if(tempInstruction[0] != '('){
			
			// address comes after @
			varName = tempInstruction.substr(1, tempInstruction.length() - 1);
			
			// convert to Binary
			binaryExp = convertToBinaryS(varName);
			
			// add to hack instructions
			hackInstructions.push_back(binaryExp);
		}
		
	}
	
	// debug
	/*for(int i = 0; i < hackInstructions.size(); i++){
		cout<<hackInstructions.at(i)<<endl;
	}
	*/	
	
			
	cout<<"writing to file"<<endl;
	
	// assign the output file to the same name as asm 
	// removing asm and replacing with hack
	string outFile = fileIn.erase(fileIn.length() - 3, 3) + "hack";
	
	// open the hackfile
	ofstream hackFile;
	hackFile.open(outFile);
	
	// insert each hack instruction into the file
	for(int i = 0; i < hackInstructions.size();i++){
		hackFile << hackInstructions.at(i) << "\n";
	}
	// close the file
	hackFile.close();		
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	