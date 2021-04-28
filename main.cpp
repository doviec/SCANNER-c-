#include "scanner.h"


#include <iostream>
#include <set>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Usage: " << argv[0] << "--tokens | --xref  filename" << endl;
		return 1;
	}
	ifstream inputFile(argv[2]);
	if (! inputFile) {
		cout << "Unable to open input file " << argv[2] << endl;
		return 1;
	}

	// Token token(QUESTION, "?");
	// token.printToken();
	// cout << "Text: " << token.getText() << endl;
	// cout << "Type: " <<token.getType() << endl;

	// varToken vt("var");
	// vt.printToken();
	// cout << "Var Text: " << vt.getText() << endl;
	// cout << "Var Type: " <<vt.getType() << endl;
	// vt.add_line(5);
	// vt.add_line(5);
	// vt.add_line(6);	
	// shared_ptr<set<int>> myset = vt.getLines();
	//    for (auto it = myset->begin(); it !=myset->end(); ++it)
	//    {
	// 	 cout << ' ' << *it;
	//    }
    // cout << " " << endl;

	// SymbolTable myTable;


	SymbolTable symTab;			// create symbol table
	Scanner scanner(inputFile, symTab);	// create scanner
	shared_ptr<Token> tokenp;		// pointer to token object
	if (argv[1] == string("-t") || argv[1] == string("--tokens")) { // output tokens
		cout << "Type\tText\n\n";
		while(tokenp = scanner.nextToken()) {
			tokenp->printToken();
		}
	}

	if (argv[1] == string("-x") || argv[1] == string("--xref")) {	// output cross-reference
		while(tokenp = scanner.nextToken())                     // scan the whole file
			;			
		cout << "Variable\tLines\n\n";
		symTab.xref();
	}
	inputFile.close();
}

