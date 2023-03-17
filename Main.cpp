#include <iostream>
#include <fstream>
using namespace std;

void removeNextCommentBlock(fstream &code, string &textResult)
{
  char c;
  int lastIndex = textResult.size()
    ? textResult.size() - 1
    : 0;
  while (code.get(c) && (textResult[lastIndex] != 42 && c != 47));
  textResult.erase(textResult.size() - 1, 1);
}

void removeNextCommentLine(fstream &code, string &textResult)
{
  char c;
  while (code.get(c) && c != 10);
  textResult.erase(textResult.size() - 1, 1);
}

int main() 
{
	char c;
	int lastIndex;
	string textResult = " ";
	fstream code ("Teste.cmp", fstream::in);
	fstream codeResult ("Teste1.cmp", fstream::out);
		
	if (!code) {
		perror("Error: ");
		return(-1);
	}

	while (code.get(c)) {
    lastIndex = textResult.size()
      ? textResult.size() - 1
      : 0;

    // Remove excess spaces and lines
		if (c == 9 || c == 10 || c == 32) {
      if (textResult[lastIndex] != 9 && textResult[lastIndex] != 10 && textResult[lastIndex] != 32) {
        textResult += c;
			}
    }

    // Remove comment block
    else if (textResult[lastIndex] == 47 && c == 42) {
      removeNextCommentBlock(code, textResult);
    }

    // Remove comment line
    else if (textResult[lastIndex] == 47 && c == 47) {
      removeNextCommentLine(code, textResult);
    }
    
    else {
      textResult += c;
    }
	}

	textResult.erase(0, 1);
  codeResult << textResult;

  code.close();
  codeResult.close();
	
	return 0;
}